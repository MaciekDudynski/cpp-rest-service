#pragma once

#include "ControllerBase.hpp"

namespace web::json
{
    class value;
}

namespace service::controllers
{
    class About : public ControllerBase
    {
      public:
        About( std::shared_ptr< db::ConnectorIface > dbConnector );
        ~About() override;

        void handleMessage( web::http::http_request message ) const override;
    };
} // namespace service::controllers
