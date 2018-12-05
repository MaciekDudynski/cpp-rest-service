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
    class User : public ModelIface
    {
      public:
        explicit User( std::optional< long > id, std::optional< std::string > login, std::optional< std::string > password );
        explicit User( const web::json::value & body );
        explicit User( const pqxx::row & row );
        ~User() override;

        const std::optional< long > & id() const;
        const std::optional< std::string > & login() const;

        std::map< std::string, std::string > serialize() const override;

        std::string tableName() const override;

      private:
        std::optional< long > _id              = {};
        std::optional< std::string > _login    = {};
        std::optional< std::string > _password = {};
    };
} // namespace service::models
