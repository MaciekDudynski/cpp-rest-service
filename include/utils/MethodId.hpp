#pragma once

namespace web::http
{
    class http_request;
}

namespace service::utils
{
    enum class MethodId
    {
        Get,
        Post,
        UNKNOWN
    };

    MethodId getMethodId( const web::http::http_request & message );
} // namespace service::utils
