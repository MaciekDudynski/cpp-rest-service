#include "models/Session.hpp"

#include <cpprest/json.h>
#include <pqxx/row>

namespace service::models
{
    Session::Session( std::optional< long > id,
      std::optional< std::string > token,
      std::optional< long > userId,
      std::optional< std::string > ip,
      std::optional< long > timestamp )
     : _id{ id }, _token{ token }, _userId{ userId }, _ip{ ip }, _timestamp{ timestamp }
    {
    }

    Session::Session( const pqxx::row & row )
    {
        _id        = row.at( row.column_number( "id" ) ).as< long >();
        _token     = row.at( row.column_number( "token" ) ).as< std::string >();
        _userId    = row.at( row.column_number( "user_id" ) ).as< long >();
        _ip        = row.at( row.column_number( "ip" ) ).as< std::string >();
        _timestamp = row.at( row.column_number( "time" ) ).as< long >();
    }

    Session::~Session()
    {
    }

    const std::optional< long > & Session::id() const
    {
        return _id;
    }

    const std::optional< std::string > & Session::token() const
    {
        return _token;
    }

    const std::optional< long > & Session::userId() const
    {
        return _userId;
    }

    const std::optional< std::string > & Session::ip() const
    {
        return _ip;
    }

    const std::optional< long > & Session::timestamp() const
    {
        return _timestamp;
    }

    std::map< std::string, std::string > Session::serialize() const
    {
        std::map< std::string, std::string > object;

        if( _id.has_value() )
            object.emplace( "id", std::to_string( _id.value() ) );
        if( _token.has_value() )
            object.emplace( "token", _token.value() );
        if( _userId.has_value() )
            object.emplace( "user_id", std::to_string( _userId.value() ) );
        if( _ip.has_value() )
            object.emplace( "ip", _ip.value() );
        if( _timestamp.has_value() )
            object.emplace( "time", std::to_string( _timestamp.value() ) );

        return object;
    }

    std::string Session::tableName() const
    {
        return "sessions";
    }

} // namespace service::models
