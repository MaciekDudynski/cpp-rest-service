#pragma once

#include "ControllerBase.hpp"

namespace web::json
{
    class value;
}

namespace service::controllers
{
    class Login : public ControllerBase
    {
      public:
        Login( std::shared_ptr< db::Connector > dbConnector );
        ~Login() override;

      private:
        void handlePost( const web::http::http_request & message ) const override;
    };
} // namespace service::controllers
