#ifndef Test_Module_Hpp
#define Test_Module_Hpp

#include <Module/SPModule.hpp>

class TestModule : public SPCore_Module::SPModule
{
public:
    TestModule() : SPModule(false)
    {
        InitModuleWithName("TestModule");
        RegisterMethod("Func0", &Func0);
        RegisterMethod("Func1", &Func1);
        RegisterMethod("", 0);
    }

    static PyObject* Func0(PyObject* self, PyObject* const* args, Py_ssize_t len)
    {
        if (len == 2)
        {
            printf("%ld + %ld = %d\n", PyLong_AsLong(args[0]), PyLong_AsLong(args[1]), 
                PyLong_AsLong(args[0]) + PyLong_AsLong(args[1]));
        }
        return Py_True;
    }

    static PyObject* Func1(PyObject* self, PyObject* const* args, Py_ssize_t len)
    {
        if (len == 1)
        {
            PyObject* o = args[0];

            if (o && PyObject_HasAttrString(o, "code"))
            {
                PyObject* code = PyObject_GetAttrString(o, "code");
                printf("%ld\n", PyLong_AsLong(code));
            }
        }
        return Py_True;
    }
};

#endif
