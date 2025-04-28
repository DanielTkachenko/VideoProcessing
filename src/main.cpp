#include <iostream>
#include "bmp.h"
#include "yuv420.h"
#include "yuv420frame.h"
#include "imageconverter.h"
#include "videoimageblender.h"

int main(int argc, char* argv[])
{
    if (argc < 6)
    {
        std::cerr << "Usage: " << argv[0] << " <bmpFileName>" << " <inputYUVFileName>" << " <yuvFilewidth>" << " <yuvFileHeight>" << " <resultYUVFileName>" << std::endl;
        return 1;
    }

    try
    {
        std::string bmpFileName = argv[1];
        std::string yuvFileName = argv[2];
        int yuvFileWidth = std::stoi(argv[3]);
        int yuvFileHeight = std::stoi(argv[4]);
        std::string resultFilename = argv[5];

        YUV420 yuv(yuvFileName, yuvFileWidth, yuvFileHeight);
        BMP bmp(bmpFileName);

        YUV420Frame yuvFrame = ImageConverter::convertBMPToYUV420(bmp);

        VideoImageBlender::blend(yuv, yuvFrame);
        
        yuv.save(resultFilename);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}