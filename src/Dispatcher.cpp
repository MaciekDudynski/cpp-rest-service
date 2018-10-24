#include "Dispatcher.hpp"

#include "NetworkInfoProvider.hpp"
#include <cpprest/uri.h>

namespace rest
{
    Dispatcher::Dispatcher( const std::string & endpoint )
     : _networkInfoProvider{ std::make_unique< NetworkInfoProvider >() }, _registeredControllers{}
    {
        web::uri endpointURI( endpoint );
        web::uri_builder endpointBuilder;

        endpointBuilder.set_scheme( endpointURI.scheme() );
        if( endpointURI.host() == "host_auto_ip4" )
        {
            endpointBuilder.set_host( _networkInfoProvider->hostIP4() );
        }
        else if( endpointURI.host() == "host_auto_ip6" )
        {
            endpointBuilder.set_host( _networkInfoProvider->hostIP6() );
        }
        endpointBuilder.set_port( endpointURI.port() );
        endpointBuilder.set_path( endpointURI.path() );

        _listener = std::make_unique< web::http::experimental::listener::http_listener >( endpointBuilder.to_uri() );
    }

    std::string Dispatcher::endpoint() const
    {
        return _listener->uri().to_string();
    }

    pplx::task< void > Dispatcher::accept()
    {
        initHandlers();
        return _listener->open();
    }

    pplx::task< void > Dispatcher::shutdown()
    {
        return _listener->close();
    }

    std::vector< std::string > Dispatcher::requestPath( const web::http::http_request & message ) const
    {
        auto relativePath = web::uri::decode( message.relative_uri().path() );
        return web::uri::split_path( relativePath );
    }

    void Dispatcher::registerController( std::unique_ptr< ControllerIface > controller )
    {
        _registeredControllers.emplace( controller->relativePath(), std::move( controller ) );
    }

    void Dispatcher::initHandlers()
    {
        _listener->support(
          web::http::methods::GET, std::bind( &Dispatcher::handleMessage, this, web::http::methods::GET, std::placeholders::_1 ) );
        _listener->support(
          web::http::methods::PUT, std::bind( &Dispatcher::handleMessage, this, web::http::methods::PUT, std::placeholders::_1 ) );
        _listener->support(
          web::http::methods::POST, std::bind( &Dispatcher::handleMessage, this, web::http::methods::POST, std::placeholders::_1 ) );
        _listener->support(
          web::http::methods::DEL, std::bind( &Dispatcher::handleMessage, this, web::http::methods::DEL, std::placeholders::_1 ) );
        _listener->support(
          web::http::methods::PATCH, std::bind( &Dispatcher::handleMessage, this, web::http::methods::PATCH, std::placeholders::_1 ) );
    }

    void Dispatcher::handleMessage( const std::string & method, const web::http::http_request & message )
    {
        std::cout << "Dispatcher is handling: " << method << " on " << message.relative_uri().path() << std::endl;

        auto foundControllerIt = _registeredControllers.find( message.relative_uri().path() );
        if( foundControllerIt != _registeredControllers.end() )
        {
            foundControllerIt->second->handleMessage( method, message );
        }
        else
        {
            std::cout << "Dispatcher didn't found suitable controller." << std::endl;
        }
    }

} // namespace rest
