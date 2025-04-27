#include <iostream>
#include "bmp.h"
#include "yuv420.h"
#include "yuv420frame.h"
#include "overlayprocessor.h"
#include "imageconverter.h"

int main(int argc, char* argv[])
{
    if (argc < 6)
    {
        std::cerr << "Usage: " << argv[0] << " <bmpFileName>" << " <inputYUVFileName>" << " <yuvFilewidth>" << " <yuvFileHeight>" << " <resultYUVFileName>" << std::endl;
        return 1;
    }
    
    
    std::string bmpFileName = argv[1];
    std::string yuvFileName = argv[2];
    int yuvFileWidth = std::stoi(argv[3]);
    int yuvFileHeight = std::stoi(argv[4]);
    std::string resultFilename = argv[5];
    

    try
    {
        YUV420 yuv(yuvFileName, yuvFileWidth, yuvFileHeight);
        BMP bmp(bmpFileName);

        YUV420Frame yuvFrame = ImageConverter::convertBMPToYUV420(bmp);

        int counter = 0;
        for(auto& frame : yuv.getFrames())
        {
            OverlayProcessor::overlay(frame, yuvFrame, 0, 0);
            std:: cout << "\rFrames processed: " << ++counter << " / " << yuv.getFrames().size() << std::flush;
        }
        std:: cout << std::endl;
        
        yuv.save(resultFilename);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}