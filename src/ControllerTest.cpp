#include "ControllerTest.hpp"

#include "db/ConnectorIface.hpp"

#include <cpprest/http_msg.h>
#include <cpprest/json.h>

namespace service
{
    ControllerTest::ControllerTest( std::shared_ptr< db::ConnectorIface > dbConnector ) : ControllerBase( "/test", dbConnector )
    {
    }

    ControllerTest::~ControllerTest()
    {
    }

    void ControllerTest::handleMessage( web::http::http_request message ) const
    {
        message.reply( web::http::status_codes::NotImplemented, responseNotImpl( message ) );
    }

} // namespace service
