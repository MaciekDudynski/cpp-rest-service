#pragma once

namespace rest
{
    class UserInterruptHandler
    {
      public:
        static void hookSIGINT();
        static void handleUserInterrupt( int signal );
        static void waitForUserInterrupt();
    };
} // namespace rest
