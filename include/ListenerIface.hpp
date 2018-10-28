#pragma once

#include <string>

namespace service
{
    enum class ListenerState
    {
        Started,
        Stopped
    };

    class ListenerIface
    {
      public:
        virtual ~ListenerIface() = default;

        virtual void start() = 0;
        virtual void stop()  = 0;
    };
} // namespace service
