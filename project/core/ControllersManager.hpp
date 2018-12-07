#pragma once

#include "ControllerLoader.hpp"

#include <map>
#include <memory>

namespace service
{
    class ControllerLoader;
    class ControllerIface;

    class ControllersManager
    {
      public:
        explicit ControllersManager() = default;
        ~ControllersManager()         = default;

        void loadControllers();
        void unloadControllers();

      private:
        std::map< std::string, ControllerLoader > _controllers;
    };
} // namespace service
