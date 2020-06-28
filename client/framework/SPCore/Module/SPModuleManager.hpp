#ifndef SP_Module_Manager_Hpp
#define SP_Module_Manager_Hpp

#include <string>
#include <Python.h>
#include "SPModule.hpp"
#include <vector>

namespace SPCore
{
    class SPCoreEngine;
}

namespace SPCore_Module
{
    class SPModuleManager
    {
        friend SPCore::SPCoreEngine;
    public:
        static SPModuleManager* SharedInstance();

        SPModuleManager()
        {
            _mainModule = 0;
        }

        void RegisterModule(SPModule* m);

    protected:
        void Build();
    private:
        std::vector<SPModule*> _moduleList;
        SPModule* _mainModule;
    };
}

#endif