#pragma once

#include "models/ModelIface.hpp"

#include <iostream>
#include <memory>
#include <pqxx/pqxx>

namespace service
{
    class ModelIface;

    namespace db
    {
        class ConnectionStringProviderIface;

        class Connector
        {
          public:
            explicit Connector( std::unique_ptr< ConnectionStringProviderIface > connectionStringProvider );
            ~Connector();

            bool insert( const ModelIface & object ) const;

            bool remove( const ModelIface & filter ) const;

            template< typename Model, typename = std::enable_if< std::is_base_of< ModelIface, Model >::value > >
            std::vector< Model > select( const ModelIface & filter ) const
            {
                const auto & serializedFilter = filter.serialize();

                std::string cmd = "SELECT * FROM " + filter.tableName() + " WHERE ";

                for( auto lineIt = serializedFilter.begin(); lineIt != serializedFilter.end(); lineIt = std::next( lineIt ) )
                {
                    if( lineIt != serializedFilter.begin() )
                    {
                        cmd += " AND ";
                    }
                    cmd += lineIt->first + "='" + lineIt->second + "'";
                }

                std::cout << "DB connector is executing command: " << cmd << std::endl;

                pqxx::work job( *_connection );
                std::vector< Model > models;

                try
                {
                    const auto & result = job.exec( cmd );
                    job.commit();

                    for( const auto & row : result )
                    {
                        models.push_back( Model( row ) );
                    }
                }
                catch( const std::exception & e )
                {
                    std::cout << "DB connector command execution returned: " << e.what() << std::endl;
                }

                return models;
            }

            template< typename Model, typename = std::enable_if< std::is_base_of< ModelIface, Model >::value > >
            bool update( const Model & filter, const Model & object ) const
            {
                const auto & serializedFilter = filter.serialize();
                const auto & serializedObject = object.serialize();

                std::string cmd1 = "UPDATE " + object.tableName() + " SET (";
                std::string cmd2 = ") = (";
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

                std::string cmd3 = " WHERE ";

                for( auto lineIt = serializedFilter.begin(); lineIt != serializedFilter.end(); lineIt = std::next( lineIt ) )
                {
                    if( lineIt != serializedFilter.begin() )
                    {
                        cmd3 += " AND ";
                    }
                    cmd3 += lineIt->first + "='" + lineIt->second + "'";
                }

                auto cmd = cmd1 + cmd2 + ")" + cmd3;

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

          private:
            std::unique_ptr< pqxx::connection > _connection;
        };
    } // namespace db
} // namespace service
