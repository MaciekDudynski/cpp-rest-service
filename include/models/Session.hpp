#pragma once

#include "ModelIface.hpp"

namespace web::json
{
    class value;
}

namespace pqxx
{
    class row;
}

namespace service::models
{
    class Session : public ModelIface
    {
      public:
        explicit Session( std::optional< long > id,
          std::optional< std::string > token,
          std::optional< long > userId,
          std::optional< std::string > ip,
          std::optional< long > timestamp );
        explicit Session( const web::json::value & body, const std::string & ip );
        explicit Session( const pqxx::row & row );
        ~Session() override;

        const std::optional< long > & id() const;
        const std::optional< std::string > & token() const;
        const std::optional< long > & userId() const;
        const std::optional< std::string > & ip() const;
        const std::optional< long > & timestamp() const;

        std::map< std::string, std::string > serialize() const override;

        std::string tableName() const override;

      private:
        std::optional< long > _id           = {};
        std::optional< std::string > _token = {};
        std::optional< long > _userId       = {};
        std::optional< std::string > _ip    = {};
        std::optional< long > _timestamp    = {};
    };
} // namespace service::models
