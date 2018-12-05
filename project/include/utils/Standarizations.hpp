#pragma once

#include <map>
#include <string>

namespace web::json
{
    class value;
}

namespace service::utils
{
    std::map< std::string, std::string > toStandardMap( const web::json::value & json );
}
