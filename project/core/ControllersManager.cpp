#include "ControllersManager.hpp"

#include "cfg/Configuration.hpp"
#include "core/DispatcherIface.hpp"

#include <filesystem>
#include <iostream>

namespace service
{
    void ControllersManager::loadControllers()
    {
        for( auto & lib : std::filesystem::directory_iterator( utils::install_path() + "/controllers" ) )
        {
            std::cout << "Creating loader for: " << lib << std::endl;

            _loaders.emplace( lib.path(), ControllerLoader( lib.path() ) );
        }
        for( auto & loader : _loaders )
        {
            std::cout << "Loading: " << loader.first << std::endl;

            loader.second.DLOpenLib();
            _controllers.emplace( loader.first, loader.second.DLGetInstance() );
        }
    }

    void ControllersManager::registerControllers( DispatcherIface & dispatcher )
    {
        for( const auto & controller : _controllers )
        {
            dispatcher.registerController( controller.second.get() );
        }
    }

    void ControllersManager::unloadControllers()
    {
        for( auto & loader : _loaders )
        {
            std::cout << "Unloading: " << loader.first << std::endl;

            _controllers.erase( loader.first );
            loader.second.DLCloseLib();
            _loaders.erase( loader.first );
        }
    }

} // namespace service
