#ifndef SP_Data_Packer_Hpp
#define SP_Data_Packer_Hpp

#include <string>

namespace SPNetwork
{
    class SPDataPacker
    {
    public:
        SPDataPacker(int size);
        int AddObjectWithSize(void* data, int size);
        int GetOffset();
        ~SPDataPacker();
    private:
        int _Size;
        int _Offset;
        char* _Data;
    };
}

#endif