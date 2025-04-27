#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include "yuv420frame.h"


class YUV420
{
public:
    YUV420(const std::string &filename, int width, int height);
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    std::vector<YUV420Frame>& getFrames() { return frames; }
    void save(const std::string &filename);
private:
    int width;
    int height;
    std::vector<YUV420Frame> frames;
};
