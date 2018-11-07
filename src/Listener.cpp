#include "Listener.hpp"

#include "DispatcherIface.hpp"
#include "utils/NetworkInfoProviderIface.hpp"

#include <cpprest/http_listener.h>
#include <cpprest/uri.h>

#include <iostream>

namespace service
{
    Listener::Listener( const std::string & endpoint,
      std::unique_ptr< utils::NetworkInfoProviderIface > networkInfoProvider,
      std::unique_ptr< DispatcherIface > dispatcher )
     : _networkInfoProvider{ std::move( networkInfoProvider ) },
       _dispatcher{ std::move( dispatcher ) },
       _currentState{ ListenerState::Stopped }
    {
        /// @todo create UriProvider
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

        _listener->support( [& dispatcher = *_dispatcher]( const auto && message ) { dispatcher.handleMessage( message ); } );
    }

    Listener::~Listener()
    {
        stop();
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
                _currentState = ListenerState::Started;
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
                _currentState = ListenerState::Stopped;
                std::cout << "Listener stopped." << std::endl;
                break;
            case ListenerState::Stopped:
                std::cout << "Listener already stopped." << std::endl;
                break;
        }
    }

} // namespace service
