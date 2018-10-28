#include "Dispatcher.hpp"

#include "ControllerIface.hpp"

#include <cpprest/uri.h>

namespace service
{
    Dispatcher::Dispatcher() : _registeredControllers{}
    {
    }

    Dispatcher::~Dispatcher()
    {
    }

    //    std::vector< std::string > Dispatcher::requestPath( const web::http::http_request & message ) const
    //    {
    //        auto relativePath = web::uri::decode( message.relative_uri().path() );
    //        return web::uri::split_path( relativePath );
    //    }

    void Dispatcher::registerController( std::unique_ptr< ControllerIface > controller )
    {
        _registeredControllers.emplace( controller->relativePath(), std::move( controller ) );
    }

    void Dispatcher::handleMessage( const web::http::http_request & message ) const
    {
        std::cout << "Dispatcher is handling: " << message.method() << " on " << message.relative_uri().path() << std::endl;

        auto foundControllerIt = _registeredControllers.find( message.relative_uri().path() );
        if( foundControllerIt != _registeredControllers.end() )
        {
            std::cout << "Dispatcher found suitable controller." << std::endl;
            foundControllerIt->second->handleMessage( message );
        }
        else
        {
            std::cout << "Dispatcher didn't found suitable controller. Available endpoints:" << std::endl;

            auto response               = web::json::value::object();
            response[ "service_name" ]  = web::json::value::string( "CppRestService" );
            response[ "relative_path" ] = web::json::value::string( message.relative_uri().to_string() );
            response[ "http_method" ]   = web::json::value::string( message.method() );
            std::vector< web::json::value > availableEndpoints;
            for( const auto & controller : _registeredControllers )
            {
                std::cout << controller.second->relativePath() << std::endl;
                availableEndpoints.emplace_back( controller.second->relativePath() );
            }
            response[ "available_endpoints" ] = web::json::value::array( availableEndpoints );
            message.reply( web::http::status_codes::NotFound, response );
        }
    }

} // namespace service
