#include "SPModule.hpp"
using namespace SPCore_Module;

SPModule::SPModule(bool isMainModule)
{
    _moduleObj = 0;
    _moduleType = SPModuleType::SPModuleType_FromBuild;
    this->isMainModule = isMainModule;
}

void SPModule::InitModuleWithFile(std::string fileName)
{
    Name = fileName;
    _moduleType = SPModuleType::SPModuleType_FromFile;
}

void SPModule::InitModuleWithName(std::string name)
{
    Name = name;
    _moduleType = SPModuleType::SPModuleType_FromBuild;
}

PyObject* SPModule::_BuildModule()
{
    if (_moduleType == SPModuleType::SPModuleType_FromBuild)
    {
        _moduleDef.m_base = PyModuleDef_HEAD_INIT;
        _moduleDef.m_name = Name.c_str();
        _moduleDef.m_doc = NULL;
        _moduleDef.m_size = -1;
        _moduleDef.m_methods = &_methodDef[0];
        _moduleDef.m_slots = NULL;
        _moduleDef.m_traverse = NULL;
        _moduleDef.m_clear = NULL;
        _moduleDef.m_free = NULL;
        _moduleObj = PyModule_Create(&_moduleDef);
    }
    else if (_moduleType == SPModuleType::SPModuleType_FromFile)
    {
        PyObject* t = PyUnicode_DecodeFSDefault(Name.c_str());
        _moduleObj = PyImport_Import(t);
        Py_CLEAR(t);
    }
    return _moduleObj;
}

void SPModule::AttachTo(SPModule* m)
{
    m->_attachedModules.push_back(this);
}

SPModule::~SPModule()
{
    for (int i = 0; i < _attachedModules.size(); i++)
    {
        PyObject_DelAttrString(_moduleObj, _attachedModules[i]->Name.c_str());
        delete _attachedModules[i];
    }

    std::map<std::string, PyObject*>::iterator it = _cachedFunc.begin();
    while (it != _cachedFunc.end())
    {
        Py_XDECREF(it->second);
        it++;
    }

    _attachedModules.clear();
    _cachedFunc.clear();
    Py_XDECREF(_moduleObj);
}

void SPModule::RegisterMethod(const char* name, _PyCFunctionFast imp)
{
    PyMethodDef desc;
    if (imp == 0)
    {
        desc.ml_doc = 0;
        desc.ml_name = 0;
        desc.ml_meth = 0;
        desc.ml_flags = 0;
    }
    else
    {
        desc.ml_doc = NULL;
        desc.ml_name = name;
        desc.ml_meth = (PyCFunction)imp;
        desc.ml_flags = METH_FASTCALL;
    }
    _methodDef.push_back(desc);
}

PyObject* SPModule::Invoke(std::string name, char* format, PyObject* args)
{
    PyObject* callableObj = 0;
    PyObject* ret = 0;

    std::map<std::string, PyObject*>::iterator it =_cachedFunc.find(name);
    if (it != _cachedFunc.end())
    {
        callableObj = it->second;
    }
    else
    {
        callableObj = PyObject_GetAttrString(_moduleObj, name.c_str());
        if (callableObj && PyCallable_Check(callableObj))
        {
            std::pair<std::string, PyObject*> p(name, callableObj);
            _cachedFunc.insert(p);
        }
        else
        {
            callableObj = 0;
        }
    }

    if (callableObj)
    {
        ret = PyObject_CallFunction(callableObj, format, args);
    }

    return ret;
}