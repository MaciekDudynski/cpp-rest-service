#pragma once

#include "ControllerBase.hpp"

namespace web::json
{
    class value;
}

namespace rest
{
    class ControllerTest : public ControllerBase
    {
      public:
        ControllerTest();
        ~ControllerTest() override;

        void handleMessage( web::http::http_request message ) const override;
    };
} // namespace rest
