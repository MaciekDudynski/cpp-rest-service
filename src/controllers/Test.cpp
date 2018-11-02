#include "controllers/Test.hpp"

#include "db/ConnectorIface.hpp"

#include <cpprest/http_msg.h>
#include <cpprest/json.h>

namespace service::controllers
{
    Test::Test( std::shared_ptr< db::ConnectorIface > dbConnector ) : ControllerBase( "/test", dbConnector )
    {
    }

    Test::~Test()
    {
    }

    void Test::handleMessage( web::http::http_request message ) const
    {
        message.reply( web::http::status_codes::NotImplemented, responseNotImpl( message ) );
    }

} // namespace service::controllers
