#pragma once

#include "ControllerBase.hpp"

namespace web::json
{
    class value;
}

namespace service
{
    class ControllerTest : public ControllerBase
    {
      public:
        ControllerTest( std::shared_ptr< db::ConnectorIface > dbConnector );
        ~ControllerTest() override;

        void handleMessage( web::http::http_request message ) const override;
    };
} // namespace service
