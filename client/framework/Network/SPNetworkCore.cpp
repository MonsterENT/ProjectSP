#include "SPNetworkCore.hpp"
#include "SPNetworkSender.hpp"
using namespace SPNetwork;


#pragma comment(lib, "Ws2_32.lib")

SPNetworkCore::SPNetworkCore()
{
    WSAData wsaData;
    int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (ret != 0)
    {
        return;
    }

    _socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (_socket == INVALID_SOCKET) {
        freeaddrinfo(_addrInfo);
        WSACleanup();
        return;
    }
}

int SPNetworkCore::_SenderSend(SPNetworkSender* sender, char* data, unsigned int size)
{
    int errorCode = -1;
    sockaddr_in to_addr;
    ZeroMemory(&to_addr, sizeof(sockaddr_in));
    to_addr.sin_family = AF_INET;
    to_addr.sin_port = htons(sender->_Port);
    errorCode = inet_pton(AF_INET, sender->_Addr, &to_addr.sin_addr);
    if (errorCode != 1)
    {
        return -1;
    }
    errorCode = sendto(_socket, data, size, 0, (sockaddr*)&to_addr, sizeof(sockaddr));
    return errorCode;
}

SPNetworkCore::~SPNetworkCore()
{
    if (_socket != INVALID_SOCKET) {
        closesocket(_socket);
        freeaddrinfo(_addrInfo);
        WSACleanup();
    }
}