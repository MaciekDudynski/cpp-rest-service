#include "Dispatcher.hpp"

#include "ControllerIface.hpp"
#include "NetworkInfoProvider.hpp"

#include <cpprest/uri.h>

namespace rest
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
            std::cout << "Dispatcher didn't found suitable controller." << std::endl;
        }
    }

} // namespace rest
