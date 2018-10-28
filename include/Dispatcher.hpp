#pragma once

#include "DispatcherIface.hpp"

#include <cpprest/http_msg.h>

#include <map>

namespace service
{
    class ControllerIface;

    class Dispatcher : public DispatcherIface
    {
      public:
        explicit Dispatcher();
        ~Dispatcher() override;

        //        std::vector< std::string > requestPath( const web::http::http_request & message ) const;

        void registerController( std::unique_ptr< ControllerIface > controller ) override;

        void handleMessage( const web::http::http_request & message ) const override;

      private:
        std::map< std::string, std::unique_ptr< ControllerIface > > _registeredControllers;
    };
} // namespace service
