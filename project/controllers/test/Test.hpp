#pragma once

#include "controllers/base/ControllerBase.hpp"

namespace web::json
{
    class value;
}

namespace service::controllers
{
    class About : public ControllerBase
    {
      public:
        About();
        ~About() override;

      private:
        void handleGet( const web::http::http_request & message ) const override;
    };
} // namespace service::controllers
