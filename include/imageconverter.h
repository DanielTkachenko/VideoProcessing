#pragma once
#include <cstdint>
#include "bmp.h"
#include "yuv420frame.h"

class ImageConverter
{
public:
    static YUV420Frame convertBMPToYUV420(const BMP &bmpFile, int numThreads = 4);
};