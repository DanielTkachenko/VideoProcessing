#ifndef YUV420DATA_H
#define YUV420DATA_H

#include <vector>

#pragma pack(push, 1)

struct YUV420Frame
{
    std::vector<uint8_t> yPlane; // Y plane
    std::vector<uint8_t> uPlane; // U plane
    std::vector<uint8_t> vPlane; // V plane
};

#pragma pack(pop)

#endif // YUV420DATA_H