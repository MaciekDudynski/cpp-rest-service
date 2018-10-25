#include "ListenerFactory.hpp"
#include "ListenerIface.hpp"
#include "UserInterruptHandler.hpp"

#include <iostream>

int main()
{
    rest::UserInterruptHandler::hookSIGINT();

    std::cout << "Creating listener..." << std::endl;
    auto listenerFactory = std::make_unique< rest::ListenerFactory >();
    auto listener        = listenerFactory->createListener();
    listener->start();

    rest::UserInterruptHandler::waitForUserInterrupt();

    listener->stop();

    return 0;
}
