#pragma once

#include "ListenerFactoryIface.hpp"

#include <memory>

namespace rest
{
    class ListenerIface;

    class ListenerFactory : public ListenerFactoryIface
    {
      public:
        explicit ListenerFactory();
        ~ListenerFactory() override;

        std::unique_ptr< ListenerIface > createListener() const;
    };
} // namespace rest
