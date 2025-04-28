#pragma once

#include <vector>
#include <thread>
#include <atomic>
#include "yuv420.h"
#include "yuv420frame.h"
#include "overlayprocessor.h"

class VideoImageBlender
{
public:
    static void blend(YUV420 &videoFile, const YUV420Frame &imageFile, int numThreads = 4);
};