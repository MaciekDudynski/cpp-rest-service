#include "ControllersManager.hpp"

#include "cfg/Configuration.hpp"

#include <filesystem>
#include <iostream>

namespace service
{
    void ControllersManager::loadControllers()
    {
        for( auto & lib : std::filesystem::directory_iterator( utils::install_path() + "/controllers" ) )
        {
            std::cout << "Creating loader for: " << lib << std::endl;

            _controllers.emplace( lib.path(), ControllerLoader( lib.path() ) );
        }
        for( auto & controller : _controllers )
        {
            std::cout << "Loading: " << controller.first << std::endl;

            controller.second.DLOpenLib();
        }
    }

    // _controllers.end()->second.DLGetInstance();

    void ControllersManager::unloadControllers()
    {
        for( auto & controller : _controllers )
        {
            std::cout << "Unloading: " << controller.first << std::endl;

            controller.second.DLCloseLib();
        }
    }

} // namespace service
