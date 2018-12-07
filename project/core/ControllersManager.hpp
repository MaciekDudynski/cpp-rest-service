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
        explicit ControllersManager( std::shared_ptr< service::db::Connector > dbConnector );
        ~ControllersManager() = default;

        void loadControllers();
        void registerControllers( DispatcherIface & dispatcher );
        void unloadControllers();

      private:
        std::shared_ptr< service::db::Connector > _dbConnector;
        std::map< std::string, ControllerLoader > _loaders                       = {};
        std::map< std::string, std::shared_ptr< ControllerIface > > _controllers = {};
    };
} // namespace service
