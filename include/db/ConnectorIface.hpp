#pragma once

namespace service::db
{
    class ConnectorIface
    {
      public:
        virtual ~ConnectorIface() = default;

        virtual void testConnection() const = 0;
    };
} // namespace service::db
