#pragma once

#include <string>

namespace rest
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

        virtual std::string endpoint() const        = 0;
        virtual const ListenerState & state() const = 0;

        virtual void start() = 0;
        virtual void stop()  = 0;
    };
} // namespace rest
