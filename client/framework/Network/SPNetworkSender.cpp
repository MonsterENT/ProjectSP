#include "SPNetworkSender.hpp"
#include "SPNetworkCore.hpp"
#include <string>
using namespace SPNetwork;

SPNetworkSender::SPNetworkSender(const char* addr, unsigned short port, SPNetworkCore* core)
{
    int size = sizeof(char) * (strlen(addr) + 1);
    _Addr = new char[size];
    memcpy(_Addr, addr, size);
    _Port = port;
    _RefCore = core;
}

int SPNetworkSender::SendData(const char* data, unsigned int size)
{
    return _RefCore->_SenderSend(this, data, size);
}

SPNetworkSender::~SPNetworkSender()
{
    if (_Addr != 0)
    {
        delete[] _Addr;
        _Addr = 0;
    }
}