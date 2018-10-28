#pragma once

#include <memory>

namespace service::db
{
    class ConnectorIface;

    class ConnectorFactory
    {
      public:
        explicit ConnectorFactory();
        ~ConnectorFactory();

        std::unique_ptr< ConnectorIface > createConnector() const;
    };
} // namespace service::db
