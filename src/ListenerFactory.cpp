#include "ListenerFactory.hpp"

#include "Dispatcher.hpp"
#include "Listener.hpp"
#include "NetworkInfoProvider.hpp"

#include "ControllerTest.hpp"

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
        auto netInfoProvider = std::make_unique< NetworkInfoProvider >();

        std::cout << "ListenerFactory is creating dispatcher..." << std::endl;

        auto dispatcher = std::make_unique< Dispatcher >();

        std::cout << "ListenerFactory is creating and registering controllers..." << std::endl;

        auto testController = std::make_unique< ControllerTest >();
        dispatcher->registerController( std::move( testController ) );

        std::cout << "ListenerFactory is creating listener..." << std::endl;

        auto listener =
          std::make_unique< Listener >( "http://host_auto_ip4:6502/api", std::move( netInfoProvider ), std::move( dispatcher ) );

        std::cout << "ListenerFactory created listener." << std::endl;

        return std::move( listener );
    }

} // namespace rest
