#include "Controller.hpp"

#include "db/Connector.hpp"

#include <cpprest/http_msg.h>
#include <cpprest/json.h>

extern "C"
{
    service::controllers::Controller * allocator( std::shared_ptr< service::db::Connector > dbConnector )
    {
        return new service::controllers::Controller( dbConnector );
    }

    void deleter( service::controllers::Controller * ptr )
    {
        delete ptr;
    }
}

namespace service::controllers
{
    Controller::Controller( std::shared_ptr< db::Connector > dbConnector ) : ControllerBase( "/about", dbConnector )
    {
    }

    void Controller::handleGet( const web::http::http_request & message ) const
    {
        auto response              = web::json::value::object();
        response[ "service_name" ] = web::json::value::string( "cpp-rest-service" );
        response[ "author_name" ]  = web::json::value::string( "Maciej Dudyński" );
        response[ "author_email" ] = web::json::value::string( "maciekdudynski@gmail.com" );
        sendResponse( message, web::http::status_codes::OK, response );
    }

} // namespace service::controllers
