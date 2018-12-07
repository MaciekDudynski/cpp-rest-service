#pragma once

#include "ControllerLoader.hpp"

#include <map>
#include <memory>

namespace service
{
    class ControllerLoader;
    class ControllerIface;
    class DispatcherIface;

    class ControllersManager
    {
      public:
        explicit ControllersManager() = default;
        ~ControllersManager()         = default;

        void loadControllers();
        void registerControllers( DispatcherIface & dispatcher );
        void unloadControllers();

      private:
        std::map< std::string, ControllerLoader > _loaders                       = {};
        std::map< std::string, std::shared_ptr< ControllerIface > > _controllers = {};
    };
} // namespace service
