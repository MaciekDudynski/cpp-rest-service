#include "Listener.hpp"

#include "DispatcherIface.hpp"
#include "NetworkInfoProviderIface.hpp"

#include <cpprest/http_listener.h>
#include <cpprest/uri.h>

#include <iostream>

namespace rest
{
    Listener::Listener( const std::string & endpoint,
      std::unique_ptr< NetworkInfoProviderIface > networkInfoProvider,
      std::unique_ptr< DispatcherIface > dispatcher )
     : _networkInfoProvider{ std::move( networkInfoProvider ) },
       _dispatcher{ std::move( dispatcher ) },
       _currentState{ ListenerState::Stopped }
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

        _listener->support( std::bind( &DispatcherIface::handleMessage, _dispatcher, std::placeholders::_1 ) );
    }

    Listener::~Listener()
    {
        stop();
    }

    std::string Listener::endpoint() const
    {
        return _listener->uri().to_string();
    }

    const ListenerState & Listener::state() const
    {
        return _currentState;
    }

    void Listener::start()
    {
        switch( _currentState )
        {
            case ListenerState::Started:
                std::cout << "Listener already started." << std::endl;
                break;
            case ListenerState::Stopped:
                std::cout << "Starting listener..." << std::endl;
                _listener->open();
                std::cout << "Listening started at: " << _listener->uri().to_string() << std::endl;
                break;
        }
    }

    void Listener::stop()
    {
        switch( _currentState )
        {
            case ListenerState::Started:
                std::cout << "Stoping listener..." << std::endl;
                _listener->close();
                std::cout << "Listener stopped." << std::endl;
                break;
            case ListenerState::Stopped:
                std::cout << "Listener already stopped." << std::endl;
                break;
        }
    }

} // namespace rest
