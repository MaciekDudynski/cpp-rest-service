#pragma once

#include <memory>

namespace service
{
    class ListenerIface;

    class ListenerFactory
    {
      public:
        explicit ListenerFactory();
        ~ListenerFactory();

        std::unique_ptr< ListenerIface > createListener() const;
    };
} // namespace service
