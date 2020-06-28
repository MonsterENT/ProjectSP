#include "SPCoreEngine.hpp"
#include <Python.h>
#include "Module/SPModuleManager.hpp"
using namespace SPCore_Module;
using namespace SPCore;

static SPCoreEngine* g_instancing = 0;

SPCoreEngine* SPCoreEngine::SharedInstance()
{
    if(g_instancing == 0)
    {
        g_instancing = new SPCoreEngine;
    }
    return g_instancing;
}

SPCoreEngine::SPCoreEngine()
{
    Py_Initialize();
    SPModuleManager::SharedInstance()->Build(); 
}

SPCoreEngine::~SPCoreEngine()
{
    Py_Finalize();
}
