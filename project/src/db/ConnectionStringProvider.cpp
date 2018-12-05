#include "db/ConnectionStringProvider.hpp"

#include "utils/Configuration.hpp"

#include <algorithm>
#include <fstream>

namespace service::db
{
    ConnectionStringProvider::ConnectionStringProvider()
    {
    }

    ConnectionStringProvider::~ConnectionStringProvider()
    {
    }

    std::string ConnectionStringProvider::connectionString() const
    {
        auto path = service::utils::install_path() + "/cfg/db_connection_string";

        auto file             = std::ifstream( path );
        auto connectionString = std::string( ( std::istreambuf_iterator< char >( file ) ), ( std::istreambuf_iterator< char >() ) );
        connectionString.erase( std::remove( connectionString.begin(), connectionString.end(), '\n' ), connectionString.end() );
        file.close();

        return connectionString;
    }

} // namespace service::db
