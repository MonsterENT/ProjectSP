#include <Python.h>
#include <stdlib.h>
#include <stdio.h>
#include <SPCoreEngine.hpp>
#include <Module/SPModule.hpp>
#include <Module/Build/Test/TestModule.hpp>
#include <Module/SPModuleManager.hpp>

using namespace SPCore;
using namespace SPCore_Module;

int main()
{ 
    SPModule* mainModule = new SPModule(true);
    mainModule->InitModuleWithFile("main");
    SPModuleManager::SharedInstance()->RegisterModule(mainModule);

    TestModule* testModule = new TestModule();
    testModule->AttachTo(mainModule);

    SPCoreEngine* engine = SPCoreEngine::SharedInstance();

    PyObject* ret = NULL;
    ret = mainModule->Invoke("kernel");
    Py_CLEAR(ret);

    delete mainModule;
    delete engine;
    system("pause");
}