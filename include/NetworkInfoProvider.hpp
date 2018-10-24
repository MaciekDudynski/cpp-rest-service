#pragma once

#include "NetworkInfoProviderIface.hpp"
#include <boost/asio.hpp>

namespace rest
{
    class NetworkInfoProvider : public NetworkInfoProviderIface
    {
      public:
        std::string hostIP4() const override;
        std::string hostIP6() const override;
        std::string hostName() const override;

      private:
        boost::asio::ip::tcp::resolver::iterator queryHostInetInfo() const;
        std::string hostIP( unsigned short family ) const;
    };

} // namespace rest
