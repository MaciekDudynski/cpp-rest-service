#include "controllers/Registration.hpp"

#include "db/ConnectorIface.hpp"

#include <cpprest/http_msg.h>
#include <cpprest/json.h>
#include <iostream>

namespace service::controllers
{
    Registration::Registration( std::shared_ptr< db::ConnectorIface > dbConnector ) : ControllerBase( "/registration", dbConnector )
    {
    }

    Registration::~Registration()
    {
    }

    void Registration::handlePost( const web::http::http_request & message ) const
    {
        message.extract_json().then( [message, &db = *_dbConnector]( const web::json::value & body ) {
            auto response = web::json::value::object();

            if( body.has_string_field( "login" ) && body.has_string_field( "password" ) )
            {
                const auto & login    = body.at( "login" ).as_string();
                const auto & password = body.at( "password" ).as_string();

                auto builder                       = bsoncxx::builder::stream::document{};
                bsoncxx::document::value doc_value = builder << "login" << login << "password" << password
                                                             << bsoncxx::builder::stream::finalize;

                db.insertOneDocument( "users", doc_value );

                message.reply( web::http::status_codes::Created, response );
            }
            else
            {
                message.reply( web::http::status_codes::BadRequest, response );
            }
        } );
    }

} // namespace service::controllers
