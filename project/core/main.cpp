#include "ControllersManager.hpp"
#include "Dispatcher.hpp"
#include "Listener.hpp"
#include "db/Connector.hpp"
#include "db/ConnectorFactory.hpp"
#include "utils/NetworkInfoProvider.hpp"
#include "utils/UserInterruptHandler.hpp"

//#include "controllers/About.hpp"
//#include "controllers/Login.hpp"
//#include "controllers/Logout.hpp"
//#include "controllers/Registration.hpp"

#include <iostream>

int main()
{
    service::utils::UserInterruptHandler::hookSIGINT();

    std::cout << "Creating network info provider..." << std::endl;

    auto netInfoProvider = std::make_unique< service::utils::NetworkInfoProvider >();

    std::cout << "Creating dispatcher..." << std::endl;

    auto dispatcher = std::make_unique< service::Dispatcher >();

    std::cout << "Creating DB connector..." << std::endl;

    auto dbConnectorFactory = std::make_unique< service::db::ConnectorFactory >();
    auto dbConnector        = std::shared_ptr< service::db::Connector >( dbConnectorFactory->createConnector() );

    std::cout << "Loading controllers..." << std::endl;

    auto controllersManager = std::make_unique< service::ControllersManager >();
    controllersManager->loadControllers();

    std::cout << "Registering controllers..." << std::endl;

    //        auto aboutController = std::make_unique< controllers::About >( dbConnector );
    //        dispatcher->registerController( std::move( aboutController ) );
    //        auto registrationController = std::make_unique< controllers::Registration >( dbConnector );
    //        dispatcher->registerController( std::move( registrationController ) );
    //        auto loginController = std::make_unique< controllers::Login >( dbConnector );
    //        dispatcher->registerController( std::move( loginController ) );
    //        auto logoutController = std::make_unique< controllers::Logout >( dbConnector );
    //        dispatcher->registerController( std::move( logoutController ) );

    std::cout << "Creating listener..." << std::endl;

    auto listener =
      std::make_unique< service::Listener >( "http://host_auto_ip4:6502/api", std::move( netInfoProvider ), std::move( dispatcher ) );

    listener->start();

    service::utils::UserInterruptHandler::waitForUserInterrupt();

    listener->stop();

    std::cout << "Unloading controllers..." << std::endl;

    controllersManager->unloadControllers();

    return 0;
}
