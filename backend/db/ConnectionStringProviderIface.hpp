#pragma once

#include <string>

namespace service::db
{
    class ConnectionStringProviderIface
    {
      public:
        virtual ~ConnectionStringProviderIface() = default;

        virtual std::string connectionString() const = 0;
    };
} // namespace service::db
