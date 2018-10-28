#include "db/ConnectorFactory.hpp"

#include "db/ConnectionStringProvider.hpp"
#include "db/Connector.hpp"

#include <iostream>

namespace service::db
{
    ConnectorFactory::ConnectorFactory()
    {
    }

    ConnectorFactory::~ConnectorFactory()
    {
    }

    std::unique_ptr< ConnectorIface > ConnectorFactory::createConnector() const
    {
        std::cout << "ConnectorFactory is creating DB ceonnection string provider..." << std::endl;

        auto connectionStringProvider = std::make_unique< ConnectionStringProvider >();

        std::cout << "ConnectorFactory is creating DB connector..." << std::endl;

        auto connector = std::make_unique< Connector >( std::move( connectionStringProvider ) );

        std::cout << "ConnectorFactory created DB connector." << std::endl;

        return std::move( connector );
    }

} // namespace service::db
