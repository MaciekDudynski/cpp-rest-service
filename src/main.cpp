#include "Dispatcher.hpp"
#include "UserInterruptHandler.hpp"
#include <iostream>

int main()
{
    rest::UserInterruptHandler::hookSIGINT();

    auto dispatcher = std::make_unique< rest::Dispatcher >( "http://host_auto_ip4:6502/api" );
    dispatcher->accept().wait();
    std::cout << "Dispatcher listening for requests at: " << dispatcher->endpoint() << std::endl;

    rest::UserInterruptHandler::waitForUserInterrupt();

    dispatcher->shutdown().wait();

    return 0;
}
