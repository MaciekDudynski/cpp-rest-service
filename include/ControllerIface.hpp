#pragma once

#include <string>

namespace web
{
    namespace http
    {
        class http_request;
    }
} // namespace web

namespace rest
{
    class ControllerIface
    {
      public:
        virtual ~ControllerIface() = default;

        virtual void handleMessage( const std::string & method, web::http::http_request message ) const = 0;
    };
} // namespace rest
