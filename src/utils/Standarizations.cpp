#include "utils/Standarizations.hpp"

#include <cpprest/json.h>

namespace service::utils
{
    std::map< std::string, std::string > toStandardMap( const web::json::value & json )
    {
        std::map< std::string, std::string > map;

        return map;
    }
} // namespace service::utils
