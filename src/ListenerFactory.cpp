#include "ListenerFactory.hpp"

#include "Dispatcher.hpp"
#include "Listener.hpp"
#include "db/ConnectorFactory.hpp"
#include "db/ConnectorIface.hpp"
#include "utils/NetworkInfoProvider.hpp"

#include "controllers/Test.hpp"

namespace service
{
    ListenerFactory::ListenerFactory()
    {
    }

    ListenerFactory::~ListenerFactory()
    {
    }

    std::unique_ptr< ListenerIface > ListenerFactory::createListener() const
    {
        auto netInfoProvider = std::make_unique< utils::NetworkInfoProvider >();

        std::cout << "ListenerFactory is creating dispatcher..." << std::endl;

        auto dispatcher = std::make_unique< Dispatcher >();

        std::cout << "ListenerFactory is creating DB connector..." << std::endl;

        auto dbConnectorFactory = std::make_unique< db::ConnectorFactory >();
        auto dbConnector        = std::shared_ptr< db::ConnectorIface >( dbConnectorFactory->createConnector() );

        std::cout << "ListenerFactory is creating and registering controllers..." << std::endl;

        auto testController = std::make_unique< controllers::Test >( dbConnector );
        dispatcher->registerController( std::move( testController ) );

        std::cout << "ListenerFactory is creating listener..." << std::endl;

        auto listener =
          std::make_unique< Listener >( "http://host_auto_ip4:6502/api", std::move( netInfoProvider ), std::move( dispatcher ) );

        std::cout << "ListenerFactory created listener." << std::endl;

        return std::move( listener );
    }

} // namespace service
