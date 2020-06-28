#ifndef SP_Module_Hpp
#define SP_Module_Hpp

#include <string>
#include <Python.h>
#include <vector>
#include <map>

namespace SPCore_Module
{
    enum class SPModuleType
    {
        SPModuleType_FromFile = 0,
        SPModuleType_FromBuild = 1,
    };

    class SPModuleManager;

    class SPModule
    {
        friend SPModuleManager;
    public:
        std::string Name;

        SPModule(bool isMainModule = false);

        void InitModuleWithFile(std::string fileName);

        void InitModuleWithName(std::string name);

        void AttachTo(SPModule* m);

        SPModuleType GetModuleType()
        {
            return _moduleType;
        }

        virtual ~SPModule();

        PyObject* Invoke(std::string name, char* format = 0, PyObject* args = 0);

    protected:
        void RegisterMethod(const char* name, _PyCFunctionFast imp);
        PyObject* _BuildModule();

        bool isMainModule;
    private:
        SPModuleType _moduleType;
        PyObject* _moduleObj;

        std::vector<PyMethodDef> _methodDef;

        std::vector<SPModule*> _attachedModules;

        std::map<std::string, PyObject*> _cachedFunc;
    };
}

#endif