#ifndef IMAGE_SYS_HPP
#define IMAGE_SYS_HPP

#include <string>

namespace ImageSys
{
    unsigned char* LoadImageFromFile(std::string path, int* width, int* height, int* comp);
    void FreeData(void* data);
}

#endif