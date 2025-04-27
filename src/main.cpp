#include <iostream>
#include "bmp.h"
#include "yuv420.h"
#include "yuv420frame.h"
#include "overlayprocessor.h"
#include "imageconverter.h"

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        std::cerr << "Usage: " << argv[0] << " <bmpFileName>" << " <inputYUVFileName>" << " <resultYUVFileName>" << std::endl;
        return 1;
    }
    
    
    std::string bmpFileName = argv[1];
    std::string yuvFileName = argv[2];
    std::string resultFilename = argv[3];
    

    try
    {
        YUV420 yuv(yuvFileName, 352, 288);
    BMP bmp(bmpFileName);

    YUV420Frame yuvFrame = ImageConverter::convertBMPToYUV420(bmp);

    for(auto& frame : yuv.getFrames())
    {
        OverlayProcessor::overlay(frame, yuvFrame, 0, 0);
    }
    std::cout << "Overlaying finished" << std::endl;
    yuv.save(resultFilename);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}