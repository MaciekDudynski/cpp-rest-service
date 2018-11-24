#include "models/User.hpp"

#include <cpprest/json.h>

namespace service::models
{
    User::User( const web::json::value & body )
    {
        _login    = body.at( "login" ).as_string();
        _password = body.at( "password" ).as_string();
    }

    User::~User()
    {
    }

    std::map< std::string, std::string > User::serialize() const
    {
        std::map< std::string, std::string > object;

        object.emplace( "login", _login );
        object.emplace( "password", _password );

        return object;
    }

    std::string User::tableName() const
    {
        return "users";
    }

} // namespace service::models
