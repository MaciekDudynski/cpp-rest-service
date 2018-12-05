#include "controllers/Registration.hpp"

#include "db/Connector.hpp"
#include "models/User.hpp"

#include <cpprest/http_msg.h>
#include <cpprest/json.h>
#include <iostream>

namespace service::controllers
{
    Registration::Registration( std::shared_ptr< db::Connector > dbConnector ) : ControllerBase( "/registration", dbConnector )
    {
    }

    Registration::~Registration()
    {
    }

    void Registration::handlePost( const web::http::http_request & message ) const
    {
        std::cout << "Registration controller is handling message..." << std::endl;

        message.extract_json()
          .then( [&message, &db = _dbConnector]( const web::json::value & body ) {
              auto response = web::json::value::object();

              if( body.has_string_field( "login" ) && body.has_string_field( "password" ) )
              {
                  auto user = models::User( body );

                  if( db->insert( user ) )
                  {
                      message.reply( web::http::status_codes::Created, response );
                      return;
                  }
                  else
                  {
                      message.reply( web::http::status_codes::Conflict, response );
                      return;
                  }
              }
              else
              {
                  message.reply( web::http::status_codes::BadRequest, response );
                  return;
              }
          } )
          .wait();
    }

} // namespace service::controllers
