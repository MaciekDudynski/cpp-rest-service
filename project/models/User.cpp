#include "User.hpp"

#include <cpprest/json.h>
#include <pqxx/row>

namespace service::models
{
    User::User( std::optional< long > id, std::optional< std::string > login, std::optional< std::string > password )
     : _id{ id }, _login{ login }, _password{ password }
    {
    }

    User::User( const web::json::value & body )
    {
        _login    = body.at( "login" ).as_string();
        _password = body.at( "password" ).as_string();
    }

    User::User( const pqxx::row & row )
    {
        _id       = row.at( row.column_number( "id" ) ).as< long >();
        _login    = row.at( row.column_number( "login" ) ).as< std::string >();
        _password = row.at( row.column_number( "password" ) ).as< std::string >();
    }

    User::~User()
    {
    }

    const std::optional< long > & User::id() const
    {
        return _id;
    }

    const std::optional< std::string > & User::login() const
    {
        return _login;
    }

    std::map< std::string, std::string > User::serialize() const
    {
        std::map< std::string, std::string > object;

        if( _id.has_value() )
            object.emplace( "id", std::to_string( _id.value() ) );
        if( _login.has_value() )
            object.emplace( "login", _login.value() );
        if( _password.has_value() )
            object.emplace( "password", _password.value() );

        return object;
    }

    std::string User::tableName() const
    {
        return "users";
    }

} // namespace service::models
