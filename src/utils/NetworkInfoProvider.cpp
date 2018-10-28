#include "utils/NetworkInfoProvider.hpp"

namespace service::utils
{
    std::string NetworkInfoProvider::hostIP4() const
    {
        return hostIP( AF_INET );
    }

    std::string NetworkInfoProvider::hostIP6() const
    {
        return hostIP( AF_INET6 );
    }

    std::string NetworkInfoProvider::hostName() const
    {
        return boost::asio::ip::host_name();
    }

    boost::asio::ip::tcp::resolver::iterator NetworkInfoProvider::queryHostInetInfo() const
    {
        boost::asio::io_service ios;
        boost::asio::ip::tcp::resolver resolver( ios );
        boost::asio::ip::tcp::resolver::query query( boost::asio::ip::host_name(), "" );
        return resolver.resolve( query );
    }

    std::string NetworkInfoProvider::hostIP( unsigned short family ) const
    {
        auto hostInetInfo = queryHostInetInfo();
        boost::asio::ip::tcp::resolver::iterator end;
        while( hostInetInfo != end )
        {
            boost::asio::ip::tcp::endpoint ep = *hostInetInfo++;
            sockaddr sa                       = *ep.data();
            if( sa.sa_family == family )
            {
                return ep.address().to_string();
            }
        }
        return nullptr;
    }
} // namespace service::utils
