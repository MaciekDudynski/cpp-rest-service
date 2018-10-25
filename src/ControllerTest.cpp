#include "ControllerTest.hpp"

#include <cpprest/http_msg.h>
#include <cpprest/json.h>

namespace rest
{
    ControllerTest::ControllerTest() : ControllerBase( "/test" )
    {
    }

    ControllerTest::~ControllerTest()
    {
    }

    void ControllerTest::handleMessage( web::http::http_request message ) const
    {
        message.reply( web::http::status_codes::NotImplemented, responseNotImpl( message ) );
    }

} // namespace rest
