#include "SPDataPacker.hpp"
using namespace SPNetwork;

SPDataPacker::SPDataPacker(int size)
{
    _Size = size;
    _Offset = 0;
    _Data = new char[size];
}

int SPDataPacker::AddObjectWithSize(void* data, int size)
{
    if (_Data == 0 || _Offset + size > _Size)
    {
        return -1;
    }

    memcpy(_Data + _Offset, data, size * sizeof(char));

    return _Offset + size;
}

int SPDataPacker::GetOffset()
{
    return _Offset;
}

SPDataPacker::~SPDataPacker()
{
    if (_Data != 0)
    {
        delete[] _Data;
    }
}