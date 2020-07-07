#include <Python.h>
#include <stdlib.h>
#include <stdio.h>
#include <SPCoreEngine.hpp>
#include <Module/SPModule.hpp>
#include <Module/Build/Test/TestModule.hpp>
#include <Module/SPModuleManager.hpp>
#include <Module/Build/Image/SPImageModule.hpp>
#include <ImageSys.hpp>

#include <SPNetworkCore.hpp>
#include <SPNetworkSender.hpp>
using namespace ImageSys;
using namespace SPCore;
using namespace SPCore_Module;
using namespace SPNetwork;

int main(int argc, char** argv)
{
    SPNetworkCore* netcore = new SPNetworkCore();
    SPNetworkSender* sender = new SPNetworkSender("127.0.0.1", 27015, netcore);
    const char* tData = "SPNetworkSender";
    sender->SendData(tData, strlen(tData) + 1);

#pragma region argv
    if (argc > 1)
    {
        char* settings = argv[1];

        if (strlen(settings) == 2)
        {
            if (settings[0] == '1')
            {
                printf("As Server\n");
            }
            else
            {
                printf("As Client\n");
            }

            printf("Distribution To : %d\n", settings[1] - '0');
        }

    }
#pragma endregion

    SPModule* imageRawModule = new SPModule(false);
    imageRawModule->InitModuleWithFile("SPScript.Module.ImageSys.SPImageModule");
    SPModuleManager::SharedInstance()->RegisterModule(imageRawModule);

    SPImageModule* imageModule = new SPImageModule();
    imageModule->AttachTo(imageRawModule);

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

    delete netcore;
    delete sender;
    system("pause");
}