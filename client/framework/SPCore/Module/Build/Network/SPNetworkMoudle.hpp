#ifndef SP_Network_Module_Hpp
#define SP_Network_Module_Hpp

#include <Module/SPModule.hpp>

namespace SPCore_Module
{
    class SPNetworkModule : public SPModule
    {
    public:
        SPNetworkModule();
        ~SPNetworkModule();
    private:
        static PyObject* SendData(PyObject* self, PyObject* const* args, Py_ssize_t len);
    };
}

#endif
