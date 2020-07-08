#include "SPNetworkMoudle.hpp"
#include <SPNetworkCore.hpp>
#include <SPNetworkSender.hpp>

using namespace SPNetwork;
using namespace SPCore_Module;

static SPNetworkCore* g_networkCore = 0;

SPNetworkModule::SPNetworkModule() : SPModule(false)
{
    g_networkCore = new SPNetworkCore();
    InitModuleWithName("_SPNetworkModule");
    RegisterMethod("_SendData", &SendData);
    RegisterMethod("", 0);
}

PyObject* SPNetworkModule::SendData(PyObject* self, PyObject* const* args, Py_ssize_t len)
{
    if (len == 2)
    {
        PyObject* senderObj = args[0];
        char* addr = PyBytes_AsString(PyUnicode_AsUTF8String(PyObject_GetAttrString(senderObj, "_Addr")));
        long port = PyLong_AsLong(PyObject_GetAttrString(senderObj, "_Port"));
        char* data = PyBytes_AsString(PyUnicode_AsUTF8String(args[1]));
        SPNetworkSender sender(addr, port, g_networkCore);
        return PyLong_FromLong(sender.SendData(data, strlen(data) + 1));
    }
    return PyLong_FromLong(-1);
}

SPNetworkModule::~SPNetworkModule()
{
    delete g_networkCore;
    g_networkCore = 0;
}