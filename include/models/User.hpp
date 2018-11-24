#pragma once

#include "ModelIface.hpp"

namespace web::json
{
    class value;
}

namespace service::models
{
    class User : public ModelIface
    {
      public:
        explicit User( const web::json::value & body );
        ~User() override;

        std::map< std::string, std::string > serialize() const override;

        std::string tableName() const override;

      private:
        std::string _login;
        std::string _password;
    };
} // namespace service::models
