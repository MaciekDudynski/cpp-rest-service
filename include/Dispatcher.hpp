#pragma once

#include <NetworkInfoProviderIface.hpp>
#include <cpprest/http_listener.h>
#include <pplx/pplxtasks.h>
#include <string>
#include <vector>

namespace rest
{
    class Dispatcher
    {
      public:
        explicit Dispatcher( const std::string & endpoint );
        ~Dispatcher() = default;

        std::string endpoint() const;
        pplx::task< void > accept();
        pplx::task< void > shutdown();

        std::vector< std::string > requestPath( const web::http::http_request & message ) const;

      private:
        void initHandlers();
        void handleMessage( const std::string & method, const web::http::http_request & message );

        std::unique_ptr< web::http::experimental::listener::http_listener > _listener;
        std::unique_ptr< NetworkInfoProviderIface > _networkInfoProvider;
    };
} // namespace rest
