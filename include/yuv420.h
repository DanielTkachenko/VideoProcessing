#pragma once

#ifndef YUV420_H
#define YUV420_H

#include <vector>
#include <iostream>
#include <fstream>
#include "yuv420data.h"
#include "bmp.h"


class YUV420
{
public:
    YUV420(const std::string &filename, int width, int height);
    void overlayPicture(const BMP &picture);
    void save(const std::string &filename);
private:
    int width;
    int height;
    std::vector<YUV420Frame> frames;
};

#endif // YUV420_H