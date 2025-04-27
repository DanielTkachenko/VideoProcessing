#pragma once

#include <iostream>
#include <vector>
#include "yuv420.h"

class OverlayProcessor
{
public:
    static void overlay(YUV420Frame &background, const YUV420Frame &overlay, int x, int y);
};