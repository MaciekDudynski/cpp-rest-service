#pragma once

#include "ListenerFactoryIface.hpp"

namespace rest
{
    class ListenerFactory : public ListenerFactoryIface
    {
      public:
        explicit ListenerFactory();
        ~ListenerFactory() override;
    };
} // namespace rest
