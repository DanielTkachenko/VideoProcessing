#pragma once

#ifndef BMP_H
#define BMP_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "yuv420data.h"

#pragma pack(push, 1) // Ensure no padding between struct members

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
    YUV420Frame getYUVData() const { return yuvData; }
    int getWidth() const { return dibHeader.width; }
    int getHeight() const { return dibHeader.height; }
    void intoYUV();
    void save(const std::string& filename);
    void saveYUV(const std::string& filename);
private:
    BMPHeader bmpHeader;
    DIBHeader dibHeader;
    std::vector<PixelData> pixelData;
    YUV420Frame yuvData;
};

#endif // BMP_H