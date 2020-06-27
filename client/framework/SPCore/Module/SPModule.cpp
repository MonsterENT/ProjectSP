#include "SPModule.hpp"
using namespace SPCore;

void SPModule::InitModuleWithFile(std::string fileName)
{
    Name = fileName;
    _moduleType = SPModuleType::SPModuleType_FromFile;
    PyObject* t = PyBytes_FromString(fileName.c_str());
    _moduleObj = PyImport_Import(t);
    Py_XDECREF(t);
}

void SPModule::InitModuleWithName(std::string name)
{
    Name = name;
    _moduleType = SPModuleType::SPModuleType_FromBuild;




}

void SPModule::BuildModule()
{
    if (_moduleType == SPModuleType::SPModuleType_FromBuild)
    {
        _moduleDef.m_base = PyModuleDef_HEAD_INIT; //Always
        _moduleDef.m_name = Name.c_str();
        _moduleDef.m_doc = NULL;
        _moduleDef.m_size = -1;//
        //_moduleDef.m_methods = 
        _moduleDef.m_slots = NULL;
        _moduleDef.m_traverse = NULL;
        _moduleDef.m_clear = NULL;
        _moduleDef.m_free = NULL;

        _moduleObj = PyModule_Create(&_moduleDef);
        PyModule_AddObject(_moduleObj, _moduleDef.m_name, 0);
        
    }

}

SPModule::~SPModule()
{
    Py_XDECREF(_moduleObj);
}