#pragma once

#include "ControllerIface.hpp"

#include <memory>

namespace web::json
{
    class value;
}

namespace service
{
    namespace db
    {
        class ConnectorIface;

    }

    class ControllerBase : public ControllerIface
    {
      public:
        ControllerBase( const std::string & relativePath, std::shared_ptr< db::ConnectorIface > dbConnector );
        virtual ~ControllerBase() override;

        const std::string & relativePath() const override;

      protected:
        web::json::value responseNotImpl( const web::http::http_request & message ) const;

        std::string _relativePath;
        std::shared_ptr< db::ConnectorIface > _dbConnector;
    };
} // namespace service
