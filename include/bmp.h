#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#pragma pack(push, 1)

struct BMPHeader
{
    uint16_t fileType;
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offsetBits;
};

struct DIBHeader
{
    uint32_t size;
    int32_t  width;
    int32_t  height;
    uint16_t planes;
    uint16_t bitCount;
    uint32_t compression;
    uint32_t sizeImage;
    int32_t  xPixelsPerMeter;
    int32_t  yPixelsPerMeter;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
};
struct PixelData
{
    uint8_t b;
    uint8_t g;
    uint8_t r;
};

#pragma pack(pop)


class BMP
{
public:
    BMP(const std::string& filename);
    int getWidth() const { return dibHeader.width; }
    int getHeight() const { return dibHeader.height; }
    const std::vector<PixelData>& getRawData() const { return pixelData; }
    void save(const std::string& filename);
private:
    BMPHeader bmpHeader;
    DIBHeader dibHeader;
    std::vector<PixelData> pixelData;
};