#pragma once

#include "ControllerBase.hpp"

namespace web::json
{
    class value;
}

namespace service::controllers
{
    class Logout : public ControllerBase
    {
      public:
        Logout( std::shared_ptr< db::Connector > dbConnector );
        ~Logout() override;

      private:
        void handlePost( const web::http::http_request & message ) const override;
    };
} // namespace service::controllers
