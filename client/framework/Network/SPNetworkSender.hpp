#ifndef SP_Network_Sender_Hpp
#define SP_Network_Sender_Hpp
#include <string>

namespace SPNetwork
{
    class SPNetworkCore;
    class SPNetworkSender
    {
        friend SPNetworkCore;
    public:
        SPNetworkSender(const char* addr, unsigned short port, SPNetworkCore* core);

        int SendData(const char* data, unsigned int size);

        ~SPNetworkSender();
    private:
        SPNetworkCore* _RefCore;
        unsigned short _Port;
        char* _Addr;
    };
}

#endif