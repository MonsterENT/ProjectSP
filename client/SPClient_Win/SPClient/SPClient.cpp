#include <Python.h>
#include <stdlib.h>
#include <stdio.h>
#include <SPCoreEngine.hpp>
#include <Module/SPModule.hpp>

using namespace SPCore;
static PyObject* moduleObj;
static PyObject* Sys_Print(PyObject* self, PyObject* const* args, Py_ssize_t len)
{
    if (moduleObj == self)
    {
        printf("same\n");
    }
    if (len != 2)
    {
        return Py_False;
    }
    long arg0 = PyLong_AsLong(args[0]);
    long arg1 = PyLong_AsLong(args[1]);

    printf("SP_SysCallBack : %d\n", arg0 + arg1);
    return Py_True;
}

static PyObject* Sys_Check(PyObject* self, PyObject* const* args, Py_ssize_t len)
{
    if (moduleObj == self)
    {
        printf("same\n");
    }

    PyObject* instance = args[0];
    //Pyobject_
    //PyMethod_New()
    //PyObject_GetAttr

    if (PyObject_HasAttrString(instance, "code"))
    {
        PyObject* code = PyObject_GetAttrString(instance, "code");
        printf("%ld\n", PyLong_AsLong(code));
        //Py_XDECREF(code);
        //Py_XDECREF(instance);
    }

    return Py_True;
}


static PyMethodDef methodDef[3];
static PyModuleDef moduleDef;



static PyObject* SP_Sys()
{
    moduleObj = PyModule_Create(&moduleDef);
    return moduleObj;
}

int main()
{ 
    SPModule d;
    //Setup
    methodDef[0].ml_doc = NULL;
    methodDef[0].ml_name = "sys_print";
    methodDef[0].ml_meth = (PyCFunction)&Sys_Print;
    methodDef[0].ml_flags = METH_FASTCALL;

    methodDef[1].ml_doc = NULL;
    methodDef[1].ml_name = "sys_check";
    methodDef[1].ml_meth = (PyCFunction)&Sys_Check;
    methodDef[1].ml_flags = METH_FASTCALL;

    methodDef[2].ml_doc = NULL;
    methodDef[2].ml_name = NULL;
    methodDef[2].ml_meth = NULL;
    methodDef[2].ml_flags = NULL;

    moduleDef.m_base = PyModuleDef_HEAD_INIT; //Always
    moduleDef.m_name = "sp_sys";
    moduleDef.m_doc = NULL;
    moduleDef.m_size = -1;//
    moduleDef.m_methods = methodDef;
    moduleDef.m_slots = NULL;
    moduleDef.m_traverse = NULL;
    moduleDef.m_clear = NULL;
    moduleDef.m_free = NULL;

    
    //PyImport_AppendInittab("sp_sys", &SP_Sys);
    Py_Initialize();
    
    //PyObject* spam = PyErr_NewException("spam.error", NULL, NULL);
    //Py_INCREF(spam);
    //int ret = PyModule_AddObject(SP_Sys(), "sp_sys", spam);
    //int ret = PyState_AddModule(SP_Sys(), &moduleDef);
    PyObject* pModule = NULL;
    PyObject* pModuleName = PyUnicode_DecodeFSDefault("main");
    pModule = PyImport_Import(pModuleName);
    Py_DECREF(pModuleName);

    int ret = PyObject_SetAttrString(pModule, "sp_sys", SP_Sys());

    PyObject* pFunc = PyObject_GetAttrString(pModule, "kernel");
    PyObject* pValue = NULL;
    if (pFunc && PyCallable_Check(pFunc))
    {
        pValue = PyObject_CallObject(pFunc, NULL);
    }

    //PyObject* pFuncPyPrint = PyObject_GetAttrString(pModule, "data_print");
    //pFunc = PyObject_GetAttrString(pModule, "on_pre_process");
    //pValue = PyObject_CallObject(pFunc, NULL);
    //if (pValue)
    //{
    //    int len = PyList_GET_SIZE(pValue);
    //    for (int i = 0; i < len; i++)
    //    {
    //        PyObject_CallFunction(pFuncPyPrint, "O", PyList_GetItem(pValue, i));
    //    }
    //}


    Py_XDECREF(pValue);
    Py_XDECREF(pFunc);
    Py_XDECREF(pModule);
    Py_Finalize();

    system("pause");
}