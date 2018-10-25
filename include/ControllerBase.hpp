#pragma once

#include "ControllerIface.hpp"

namespace web::json
{
    class value;
}

namespace rest
{
    class ControllerBase : public ControllerIface
    {
      public:
        ControllerBase( const std::string & relativePath );
        virtual ~ControllerBase() override;

        const std::string & relativePath() const override;

      protected:
        web::json::value responseNotImpl( const web::http::http_request & message ) const;

        std::string _relativePath;
    };
} // namespace rest
