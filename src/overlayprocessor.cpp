#include "overlayprocessor.h"

void OverlayProcessor::overlay(YUV420Frame &background, const YUV420Frame &overlay, int x, int y)
{
    std::cout << "Overlaying picture..." << std::endl;
    if(overlay.width > background.width || overlay.height > background.height)
    {
        std::cerr << "Picture size exceeds YUV frame size." << std::endl;
        return;
    }
    if (x < 0 || y < 0 || overlay.width + x > background.width || overlay.height + y > background.height)
    {
        std::cerr << "Overlay position out of bounds." << std::endl;
        return;
    }
    
    for (int i = 0; i < overlay.height; ++i)
    {
        for (int j = 0; j < overlay.width; ++j)
        {
            //std:: cout << "overlay i: " << i << " j: " << j << std::endl;
            background.yPlane[i*background.width + j] = overlay.yPlane[i*overlay.width + j];
            background.uPlane[(i/2)*(background.width/2) + (j/2)] = overlay.uPlane[(i/2)*(overlay.width/2) + (j/2)];
            background.vPlane[(i/2)*(background.width/2) + (j/2)] = overlay.vPlane[(i*overlay.width + j)/2];
        }
    }
    std::cout << "Overlaying frame finished"  << std::endl;
}