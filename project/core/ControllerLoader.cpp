#include "ControllerLoader.hpp"

#include "controllers/api/ControllerIface.hpp"

#include <dlfcn.h>
#include <iostream>

namespace service
{
    ControllerLoader::ControllerLoader( const std::string & pathToLib ) : _handle( nullptr ), _pathToLib( pathToLib )
    {
    }

    void ControllerLoader::DLOpenLib()
    {
        if( !( _handle = dlopen( _pathToLib.c_str(), RTLD_NOW | RTLD_LAZY ) ) )
        {
            std::cerr << dlerror() << std::endl;
        }
    }

    std::shared_ptr< ControllerIface > ControllerLoader::DLGetInstance()
    {
        using allocClass  = ControllerIface * ( * ) ();
        using deleteClass = void ( * )( ControllerIface * );

        auto allocFunc  = reinterpret_cast< allocClass >( dlsym( _handle, "allocator" ) );
        auto deleteFunc = reinterpret_cast< deleteClass >( dlsym( _handle, "deleter" ) );

        if( !allocFunc || !deleteFunc )
        {
            DLCloseLib();
            std::cerr << dlerror() << std::endl;
        }

        return std::shared_ptr< ControllerIface >( allocFunc(), [deleteFunc]( ControllerIface * p ) { deleteFunc( p ); } );
    }

    void ControllerLoader::DLCloseLib()
    {
        if( dlclose( _handle ) != 0 )
        {
            std::cerr << dlerror() << std::endl;
        }
    }

} // namespace service
