#include "controllers/base/utils/MethodId.hpp"

#include <cpprest/http_msg.h>

namespace service::utils
{
    MethodId getMethodId( const web::http::http_request & message )
    {
        const auto & method = message.method();

        if( method == web::http::methods::GET )
            return MethodId::Get;
        else if( method == web::http::methods::POST )
            return MethodId::Post;
        else
            return MethodId::UNKNOWN;
    }

} // namespace service::utils
