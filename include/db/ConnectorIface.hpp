#pragma once

#include <string>

namespace service
{
    class ModelIface;

    namespace db
    {
        class ConnectorIface
        {
          public:
            virtual ~ConnectorIface() = default;

            virtual bool insert( const ModelIface & object ) const = 0;
        };
    } // namespace db
} // namespace service
