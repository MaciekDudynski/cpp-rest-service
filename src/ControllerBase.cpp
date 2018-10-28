#include "ControllerBase.hpp"

#include <cpprest/http_msg.h>
#include <cpprest/json.h>

namespace service
{
    ControllerBase::ControllerBase( const std::string & relativePath, std::shared_ptr< db::ConnectorIface > dbConnector )
     : _relativePath{ relativePath }, _dbConnector{ dbConnector }
    {
    }

    ControllerBase::~ControllerBase()
    {
    }

    const std::string & ControllerBase::relativePath() const
    {
        return _relativePath;
    }

    web::json::value ControllerBase::responseNotImpl( const web::http::http_request & message ) const
    {
        auto response               = web::json::value::object();
        response[ "service_name" ]  = web::json::value::string( "CppRestService" );
        response[ "relative_path" ] = web::json::value::string( relativePath() );
        response[ "http_method" ]   = web::json::value::string( message.method() );
        return response;
    }
} // namespace service
