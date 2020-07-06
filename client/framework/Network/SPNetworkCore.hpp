#ifndef SP_Network_Core_Hpp
#define SP_Network_Core_Hpp

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <string>

namespace SPNetwork
{
    class SPNetworkSender;
    class SPNetworkCore
    {
        friend SPNetworkSender;
    public:
        SPNetworkCore();
        ~SPNetworkCore();

    protected:
        int _SenderSend(SPNetworkSender*, char* data, unsigned int size);
    private:
        SOCKET _socket;
        addrinfo* _addrInfo;
    };
};

#endif