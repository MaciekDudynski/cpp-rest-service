#pragma once

#include <string>

namespace web
{
    namespace http
    {
        class http_request;
    }
} // namespace web

namespace service
{
    class ControllerIface
    {
      public:
        virtual ~ControllerIface() = default;

        virtual const std::string & relativePath() const                    = 0;
        virtual void handleMessage( web::http::http_request message ) const = 0;
    };
} // namespace service
