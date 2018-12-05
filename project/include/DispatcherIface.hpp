#pragma once

#include <memory>

namespace web::http
{
    class http_request;
}

namespace service
{
    class ControllerIface;

    class DispatcherIface
    {
      public:
        virtual ~DispatcherIface() = default;

        virtual void registerController( std::unique_ptr< ControllerIface > controller ) = 0;

        virtual void handleMessage( const web::http::http_request & message ) const = 0;
    };
} // namespace service
