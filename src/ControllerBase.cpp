#include "ControllerBase.hpp"

#include "utils/MethodId.hpp"

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

    void ControllerBase::handleMessage( const web::http::http_request & message ) const
    {
        switch( utils::getMethodId( message ) )
        {
            case utils::MethodId::Get:
                handleGet( message );
                break;
            case utils::MethodId::Post:
                handlePost( message );
                break;
            case utils::MethodId::UNKNOWN:
                handleUnknown( message );
                break;
        }

        std::cout << "Controller finnished handling message." << std::endl;
    }

    const std::string & ControllerBase::relativePath() const
    {
        return _relativePath;
    }

    void ControllerBase::handleGet( const web::http::http_request & message ) const
    {
        message.reply( web::http::status_codes::NotImplemented, responseNotImpl( message ) );
    }

    void ControllerBase::handlePost( const web::http::http_request & message ) const
    {
        message.reply( web::http::status_codes::NotImplemented, responseNotImpl( message ) );
    }

    void ControllerBase::handleUnknown( const web::http::http_request & message ) const
    {
        message.reply( web::http::status_codes::NotImplemented, responseNotImpl( message ) );
    }

    web::json::value ControllerBase::responseNotImpl( const web::http::http_request & message ) const
    {
        auto response               = web::json::value::object();
        response[ "service_name" ]  = web::json::value::string( "cpp-rest-service" );
        response[ "relative_path" ] = web::json::value::string( relativePath() );
        response[ "http_method" ]   = web::json::value::string( message.method() );
        return response;
    }
} // namespace service
