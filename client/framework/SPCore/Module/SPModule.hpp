#ifndef SP_Module_Hpp
#define SP_Module_Hpp

#include <string>
#include <Python.h>
#include <vector>

namespace SPCore
{
    enum class SPModuleType
    {
        SPModuleType_FromFile = 0,
        SPModuleType_FromBuild = 1,
    };

    class SPModule
    {
    public:
        std::string Name;

        SPModule()
        {
        }

        void InitModuleWithFile(std::string fileName);

        void InitModuleWithName(std::string name);

        
        virtual void BuildModule();

        SPModuleType GetModuleType()
        {
            return _moduleType;
        }

        virtual ~SPModule();

    private:
        SPModuleType _moduleType;
        PyObject* _moduleObj;

        std::vector<PyMethodDef> _methodDef;
        PyModuleDef _moduleDef;
    };
}

#endif