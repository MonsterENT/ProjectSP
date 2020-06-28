#include "SPModuleManager.hpp"
using namespace SPCore_Module;

static SPModuleManager* g_instance = 0;

SPModuleManager* SPModuleManager::SharedInstance()
{
    if (g_instance == 0)
    {
        g_instance = new SPModuleManager();
    }
    return g_instance;
}

void SPModuleManager::RegisterModule(SPModule* m)
{
    if (m->GetModuleType() == SPModuleType::SPModuleType_FromFile)
    {
        if (_mainModule == 0 && m->isMainModule)
        {
            _mainModule = m;
        }
        _moduleList.push_back(m);
    }
}

void SPModuleManager::Build()
{
    for (int i = 0; i < _moduleList.size(); i++)
    {
        SPModule* moduleObj = _moduleList[i];
        PyObject* raw_moduleObj = moduleObj->_BuildModule();

        for (int idx = 0; idx < moduleObj->_attachedModules.size(); idx++)
        {
            SPModule* o = moduleObj->_attachedModules[idx];
            if (o->GetModuleType() == SPModuleType::SPModuleType_FromBuild)
            {
                PyObject_SetAttrString(raw_moduleObj, o->Name.c_str(), o->_BuildModule());
            }
        }
    }
}