#pragma once

#include "db/ConnectorIface.hpp"

#include <pqxx/pqxx>

#include <memory>

namespace service::db
{
    class ConnectionStringProviderIface;

    class Connector : public ConnectorIface
    {
      public:
        explicit Connector( std::unique_ptr< ConnectionStringProviderIface > connectionStringProvider );
        ~Connector() override;

        bool insert( const ModelIface & object ) const override;

      private:
        std::unique_ptr< pqxx::connection > _connection;
    };
} // namespace service::db
