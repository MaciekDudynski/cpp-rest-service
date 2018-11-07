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
        message.extract_json().then( [message]( const web::json::value & body ) {
            auto response = web::json::value::object();

            message.reply( web::http::status_codes::BadRequest, response );
        } );

        //        auto response              = web::json::value::object();
        //        response[ "service_name" ] = web::json::value::string( "cpp-rest-service" );
        //        response[ "author_name" ]  = web::json::value::string( "Maciej Dudyński" );
        //        response[ "author_email" ] = web::json::value::string( "maciekdudynski@gmail.com" );
        //        message.reply( web::http::status_codes::OK, response );
    }

} // namespace service::controllers
