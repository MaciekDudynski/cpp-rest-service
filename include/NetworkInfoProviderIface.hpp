#pragma once

#include <string>

namespace rest
{
    class NetworkInfoProviderIface
    {
      public:
        virtual ~NetworkInfoProviderIface() = default;

        virtual std::string hostIP4() const = 0;
        virtual std::string hostIP6() const = 0;
        virtual std::string hostName() const = 0;
    };

} // namespace rest
