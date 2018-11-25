#pragma once

#include "ModelIface.hpp"

#include <pqxx/pqxx>

#include <memory>

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

                pqxx::work job( *_connection );
                const auto & result = job.exec( cmd );
                job.commit();

                std::vector< Model > models;
                for( const auto & row : result )
                {
                    models.push_back( Model( row ) );
                }
                return models;
            }

          private:
            std::unique_ptr< pqxx::connection > _connection;
        };
    } // namespace db
} // namespace service
