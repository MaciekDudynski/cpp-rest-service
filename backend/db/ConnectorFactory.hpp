#pragma once

#include <memory>

namespace service::db
{
    class Connector;

    class ConnectorFactory
    {
      public:
        explicit ConnectorFactory();
        ~ConnectorFactory();

        std::unique_ptr< Connector > createConnector() const;
    };
} // namespace service::db
