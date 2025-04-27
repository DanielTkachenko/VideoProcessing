#pragma once

#include <vector>

#pragma pack(push, 1)

struct YUV420Frame
{
    std::vector<uint8_t> yPlane;
    std::vector<uint8_t> uPlane;
    std::vector<uint8_t> vPlane;
    int width;
    int height;
};

#pragma pack(pop)