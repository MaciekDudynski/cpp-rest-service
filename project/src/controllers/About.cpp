#include "controllers/About.hpp"

#include "db/Connector.hpp"

#include <cpprest/http_msg.h>
#include <cpprest/json.h>

namespace service::controllers
{
    About::About( std::shared_ptr< db::Connector > dbConnector ) : ControllerBase( "/about", dbConnector )
    {
    }

    About::~About()
    {
    }

    void About::handleGet( const web::http::http_request & message ) const
    {
        auto response              = web::json::value::object();
        response[ "service_name" ] = web::json::value::string( "cpp-rest-service" );
        response[ "author_name" ]  = web::json::value::string( "Maciej Dudyński" );
        response[ "author_email" ] = web::json::value::string( "maciekdudynski@gmail.com" );
        message.reply( web::http::status_codes::OK, response );
    }

} // namespace service::controllers
