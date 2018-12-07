#pragma once

#include "controllers/base/ControllerBase.hpp"

namespace web::json
{
    class value;
}

namespace service::controllers
{
    class Controller : public ControllerBase
    {
      public:
        Controller( std::shared_ptr< db::Connector > dbConnector );
        ~Controller() override = default;

      private:
        void handlePost( const web::http::http_request & message ) const override;
    };
} // namespace service::controllers
