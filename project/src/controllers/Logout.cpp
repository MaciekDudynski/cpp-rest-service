#include "controllers/Logout.hpp"

#include "db/Connector.hpp"
#include "models/Session.hpp"

#include <cpprest/http_msg.h>
#include <cpprest/json.h>
#include <iostream>

namespace service::controllers
{
    Logout::Logout( std::shared_ptr< db::Connector > dbConnector ) : ControllerBase( "/logout", dbConnector )
    {
    }

    Logout::~Logout()
    {
    }

    void Logout::handlePost( const web::http::http_request & message ) const
    {
        std::cout << "Logout controller is handling message..." << std::endl;

        message.extract_json()
          .then( [&message, &db = _dbConnector]( const web::json::value & body ) {
              if( body.has_string_field( "token" ) )
              {
                  const auto & sessionsFilter = models::Session( {}, body.at( "token" ).as_string(), {}, message.remote_address(), {} );

                  const auto & foundSessions = db->select< models::Session >( sessionsFilter );

                  if( foundSessions.size() == 0 )
                  {
                      message.reply( web::http::status_codes::Unauthorized );
                      return;
                  }
                  else if( foundSessions.size() == 1 )
                  {
                      const auto & session = foundSessions.at( 0 );

                      if( db->remove( session ) )
                      {
                          message.reply( web::http::status_codes::OK );
                          return;
                      }
                      else
                      {
                          message.reply( web::http::status_codes::InternalError );
                          return;
                      }
                  }
                  else
                  {
                      /// @todo remove all user sessions from DB
                      message.reply( web::http::status_codes::InternalError );
                      return;
                  }
              }
              else
              {
                  message.reply( web::http::status_codes::BadRequest );
                  return;
              }
          } )
          .wait();
    }

} // namespace service::controllers
