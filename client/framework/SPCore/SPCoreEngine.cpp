#include "SPCoreEngine.hpp"
#include <Python.h>

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
    //Init Module
    Py_Initialize();
}


SPCoreEngine::~SPCoreEngine()
{
    Py_Finalize();
}
