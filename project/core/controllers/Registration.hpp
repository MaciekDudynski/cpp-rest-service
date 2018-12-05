#pragma once

#include "ControllerBase.hpp"

namespace web::json
{
    class value;
}

namespace service::controllers
{
    class Registration : public ControllerBase
    {
      public:
        Registration( std::shared_ptr< db::Connector > dbConnector );
        ~Registration() override;

      private:
        void handlePost( const web::http::http_request & message ) const override;
    };
} // namespace service::controllers
