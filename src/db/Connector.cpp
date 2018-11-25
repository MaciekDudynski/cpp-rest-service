#include "db/Connector.hpp"

#include "db/ConnectionStringProviderIface.hpp"

namespace service::db
{
    Connector::Connector( std::unique_ptr< ConnectionStringProviderIface > connectionStringProvider )
    {
        std::cout << "DB connector is getting connection string..." << std::endl;
        auto connectionString = connectionStringProvider->connectionString();

        std::cout << "DB connector is creating connection..." << std::endl;
        _connection = std::make_unique< pqxx::connection >( connectionString );
    }

    Connector::~Connector()
    {
    }

    bool Connector::insert( const ModelIface & object ) const
    {
        const auto & serializedObject = object.serialize();

        std::string cmd1 = "INSERT INTO " + object.tableName() + " (";
        std::string cmd2 = ") VALUES (";
        for( auto lineIt = serializedObject.begin(); lineIt != serializedObject.end(); lineIt = std::next( lineIt ) )
        {
            if( lineIt != serializedObject.begin() )
            {
                cmd1 += ", ";
                cmd2 += ", ";
            }
            cmd1 += lineIt->first;
            cmd2 += "'" + lineIt->second + "'";
        }

        auto cmd = cmd1 + cmd2 + ")";
        std::cout << "DB connector is executing command: " << cmd << std::endl;

        pqxx::work job( *_connection );
        try
        {
            job.exec( cmd );
            job.commit();
        }
        catch( const std::exception & e )
        {
            std::cout << "DB connector command execution returned: " << e.what() << std::endl;
            return false;
        }

        return true;
    }

} // namespace service::db
