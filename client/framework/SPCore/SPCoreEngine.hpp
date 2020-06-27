#ifndef SP_Core_Engine_Hpp
#define SP_Core_Engine_Hpp

namespace SPCore
{
    class SPCoreEngine
    {
    public:
        static SPCoreEngine* SharedInstance();
        SPCoreEngine();
        ~SPCoreEngine();
    };
}

#endif