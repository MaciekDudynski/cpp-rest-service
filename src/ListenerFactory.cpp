#include "ListenerFactory.hpp"

#include "Dispatcher.hpp"
#include "Listener.hpp"
#include "NetworkInfoProvider.hpp"

namespace rest
{
    ListenerFactory::ListenerFactory()
    {
    }

    ListenerFactory::~ListenerFactory()
    {
    }

    std::unique_ptr< ListenerIface > ListenerFactory::createListener() const
    {
        std::cout << "ListenerFactory is creating listener..." << std::endl;

        auto netInfoProvider = std::make_unique< NetworkInfoProvider >();
        auto dispatcher      = std::make_unique< Dispatcher >();
        auto listener =
          std::make_unique< Listener >( "http://host_auto_ip4:6502/api", std::move( netInfoProvider ), std::move( dispatcher ) );

        std::cout << "ListenerFactory created listener." << std::endl;

        return std::move( listener );
    }

} // namespace rest
