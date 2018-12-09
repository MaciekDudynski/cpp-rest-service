#pragma once

#include "controllers/api/ControllerIface.hpp"

#include <memory>

namespace web
{
    namespace json
    {
        class value;
    }

} // namespace web

namespace service
{
    namespace db
    {
        class Connector;
    }

    void sendResponse( const web::http::http_request & message, const unsigned short & statusCode );
    void sendResponse( const web::http::http_request & message, const unsigned short & statusCode, const web::json::value & body );

    class ControllerBase : public ControllerIface
    {
      public:
        ControllerBase( const std::string & relativePath, std::shared_ptr< db::Connector > dbConnector );
        virtual ~ControllerBase() override;

        void handleMessage( const web::http::http_request & message ) const override;

        const std::string & relativePath() const override;

      protected:
        virtual void handleGet( const web::http::http_request & message ) const;
        virtual void handlePost( const web::http::http_request & message ) const;

        void handleUnknown( const web::http::http_request & message ) const;

        web::json::value responseNotImpl( const web::http::http_request & message ) const;

        std::string _relativePath;
        std::shared_ptr< db::Connector > _dbConnector;
    };
} // namespace service
