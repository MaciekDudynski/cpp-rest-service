#include <UserInterruptHandler.hpp>

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <signal.h>

static std::condition_variable _condition;
static std::mutex _mutex;

namespace rest
{
    void UserInterruptHandler::hookSIGINT()
    {
        signal( SIGINT, handleUserInterrupt );
    }

    void UserInterruptHandler::handleUserInterrupt( int signal )
    {
        if( signal == SIGINT )
        {
            std::cout << std::endl << "Stopping server (SIGINT trapped)..." << std::endl;
            _condition.notify_one();
        }
    }

    void UserInterruptHandler::waitForUserInterrupt()
    {
        std::unique_lock< std::mutex > lock{ _mutex };
        _condition.wait( lock );
        std::cout << "Stopping server..." << std::endl;
        lock.unlock();
    }

} // namespace rest
