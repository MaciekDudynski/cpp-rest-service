#pragma once

#include <memory>
#include <string>

namespace service
{
    namespace db
    {
        class Connector;
    }
    class ControllerIface;

    class ControllerLoader
    {
      public:
        ControllerLoader( std::string const & pathToLib );

        ~ControllerLoader() = default;

        void DLOpenLib();

        std::shared_ptr< ControllerIface > DLGetInstance();

        void DLCloseLib();

      private:
        void * _handle;
        std::string _pathToLib;
    };
} // namespace service
