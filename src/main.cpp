#include <iostream>
#include "bmp.h"
#include "yuv420.h"

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <bmpFileName>" << " <yuvFileName>" << std::endl;
        return 1;
    }

    for (size_t i = 0; i < argc; i++)
    {
        std::cout << "argv[" << i << "] = " << argv[i] << std::endl;
    }
    
    
    std::string bmpFileName = argv[1];
    std::string yuvFileName = argv[2];
    

    YUV420 yuv(yuvFileName, 352, 288);
    BMP bmp(bmpFileName);
    //bmp.saveYUV("C:\\Users\\Admin\\Downloads\\savedpic.yuv");
    //bmp.save("C:\\Users\\Admin\\Downloads\\savepic.bmp");
    //std::cout << "BMP width: " << bmp.getWidth() << ", height: " << bmp.getHeight() << std::endl;
    yuv.overlayPicture(bmp);
    std::cout << "YUV width: " << std::endl;
    yuv.save("C:\\Users\\Admin\\Downloads\\saved11.yuv");
    
    return 0;
}