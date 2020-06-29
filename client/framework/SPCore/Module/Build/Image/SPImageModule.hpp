#ifndef SP_Image_Module_Hpp
#define SP_Image_Module_Hpp

#include <Module/SPModule.hpp>

namespace SPCore_Module
{
    class SPImageModule : public SPModule
    {
    public:
        SPImageModule();

        static PyObject* LoadImage(PyObject* self, PyObject* const* args, Py_ssize_t len);

    private:
        static bool isValid(PyObject* o);
    };
}

#endif