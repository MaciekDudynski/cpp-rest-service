#pragma once

#include "db/ConnectionStringProviderIface.hpp"

namespace service::db
{
    class ConnectionStringProvider : public ConnectionStringProviderIface
    {
      public:
        explicit ConnectionStringProvider();
        ~ConnectionStringProvider() override;

        std::string connectionString() const override;
    };
} // namespace service::db
