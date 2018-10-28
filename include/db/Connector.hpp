#pragma once

#include "db/ConnectorIface.hpp"

#include <mongocxx/v_noabi/mongocxx/client.hpp>
#include <mongocxx/v_noabi/mongocxx/instance.hpp>

#include <memory>

namespace service::db
{
    class ConnectionStringProviderIface;

    class Connector : public ConnectorIface
    {
      public:
        explicit Connector( std::unique_ptr< ConnectionStringProviderIface > connectionStringProvider );
        ~Connector() override;

        void insertOneDocument( const std::string & collectionName, const bsoncxx::document::value & doc_value ) const override;

      private:
        std::unique_ptr< mongocxx::instance > _instance;
        std::unique_ptr< mongocxx::client > _client;
    };
} // namespace service::db
