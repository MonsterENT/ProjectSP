#include "SPImageModule.hpp"
#include <ImageSys.hpp>
using namespace SPCore_Module;

#define id_width "width"
#define id_height "height"
#define id_comp "comp"

SPImageModule::SPImageModule() : SPModule(false)
{
    InitModuleWithName("_SPImageModule");
    RegisterMethod("_LoadImage", &LoadImage);
    RegisterMethod("", 0);
}

//arg[0] Py Defined Object //arg[1] fileName
PyObject* SPImageModule::LoadImage(PyObject* self, PyObject* const* args, Py_ssize_t len)
{
    if (len == 2)
    {
        PyObject* rawObj = args[0];
        if (isValid(rawObj))
        {
            char* fileName = PyBytes_AsString(args[1]);
            int width = 0, height = 0, comp = 0;
            unsigned char* data = ImageSys::LoadImageFromFile(fileName, &width, &height, &comp);
            //Resovle Data And Set To PyObject

            //
            PyObject_SetAttrString(rawObj, id_width, PyLong_FromLong(width));
            PyObject_SetAttrString(rawObj, id_height, PyLong_FromLong(height));
            PyObject_SetAttrString(rawObj, id_comp, PyLong_FromLong(comp));

            ImageSys::FreeData(data);
            return Py_True;
        }
    }
    return Py_False;
}
bool SPImageModule::isValid(PyObject* o)
{
    return PyObject_HasAttrString(o, id_width) &&
        PyObject_HasAttrString(o, id_height) &&
        PyObject_HasAttrString(o, id_comp);
}
