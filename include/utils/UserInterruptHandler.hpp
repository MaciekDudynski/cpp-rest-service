#pragma once

namespace service::utils
{
    class UserInterruptHandler
    {
      public:
        static void hookSIGINT();
        static void handleUserInterrupt( int signal );
        static void waitForUserInterrupt();
    };
} // namespace service::utils
