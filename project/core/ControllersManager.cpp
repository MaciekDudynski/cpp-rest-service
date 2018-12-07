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
            std::cout << "Loading: " << lib << std::endl;

            _controllers.emplace( lib.path(), ControllerLoader( lib.path() ) );
            _controllers.end()->second.DLOpenLib();
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
