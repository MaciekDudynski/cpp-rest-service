#include "ListenerFactory.hpp"
#include "ListenerIface.hpp"
#include "utils/UserInterruptHandler.hpp"

#include <iostream>

int main()
{
    service::utils::UserInterruptHandler::hookSIGINT();

    std::cout << "Creating listener..." << std::endl;
    auto listenerFactory = std::make_unique< service::ListenerFactory >();
    auto listener        = listenerFactory->createListener();

    listener->start();

    service::utils::UserInterruptHandler::waitForUserInterrupt();

    listener->stop();

    return 0;
}
