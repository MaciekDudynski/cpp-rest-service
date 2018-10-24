#pragma once

#include "ControllerIface.hpp"
#include "NetworkInfoProviderIface.hpp"
#include <cpprest/http_listener.h>
#include <map>
#include <pplx/pplxtasks.h>
#include <string>
#include <vector>

namespace rest
{
    class ControllerIface;

    class Dispatcher
    {
      public:
        explicit Dispatcher( const std::string & endpoint );
        ~Dispatcher() = default;

        std::string endpoint() const;
        pplx::task< void > accept();
        pplx::task< void > shutdown();

        std::vector< std::string > requestPath( const web::http::http_request & message ) const;

        void registerController( std::unique_ptr< ControllerIface > controller );

      private:
        void initHandlers();
        void handleMessage( const std::string & method, const web::http::http_request & message );

        std::unique_ptr< web::http::experimental::listener::http_listener > _listener;
        std::unique_ptr< NetworkInfoProviderIface > _networkInfoProvider;
        std::map< std::string, std::unique_ptr< ControllerIface > > _registeredControllers;
    };
} // namespace rest
