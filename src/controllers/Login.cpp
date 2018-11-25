#include "controllers/Login.hpp"

#include "db/Connector.hpp"
#include "models/Session.hpp"
#include "models/User.hpp"

#include <chrono>
#include <cpprest/http_msg.h>
#include <cpprest/json.h>
#include <iostream>

namespace
{
    std::string randomString( size_t length )
    {
        auto randchar = []() -> char {
            const char charset[]   = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
            const size_t max_index = ( sizeof( charset ) - 1 );
            return charset[ rand() % max_index ];
        };
        std::string str( length, 0 );
        std::generate_n( str.begin(), length, randchar );
        return str;
    }

    inline long currentTimestamp()
    {
        return std::chrono::duration_cast< std::chrono::milliseconds >( std::chrono::system_clock::now().time_since_epoch() ).count();
    }
} // namespace

namespace service::controllers
{
    Login::Login( std::shared_ptr< db::Connector > dbConnector ) : ControllerBase( "/login", dbConnector )
    {
    }

    Login::~Login()
    {
    }

    void Login::handlePost( const web::http::http_request & message ) const
    {
        std::cout << "Login controller is handling message..." << std::endl;

        message.extract_json()
          .then( [&message, &db = _dbConnector]( const web::json::value & body ) {
              auto response = web::json::value::object();

              if( body.has_string_field( "login" ) && body.has_string_field( "password" ) )
              {
                  const auto & userFilter = models::User( body );
                  const auto foundUsers   = db->select< models::User >( userFilter );

                  if( foundUsers.size() == 1 )
                  {
                      const auto & user = foundUsers.at( 0 );

                      const auto & session =
                        models::Session( {}, randomString( 30 ), user.id(), message.remote_address(), currentTimestamp() );

                      if( db->insert( session ) )
                      {
                          response[ "token" ] = web::json::value::string( session.token().value() );

                          message.reply( web::http::status_codes::OK, response );
                      }
                      else
                      {
                          message.reply( web::http::status_codes::InternalError, response );
                      }
                  }
                  else
                  {
                      message.reply( web::http::status_codes::Unauthorized, response );
                  }
              }
              else
              {
                  message.reply( web::http::status_codes::BadRequest, response );
              }
          } )
          .wait();
    }

} // namespace service::controllers
