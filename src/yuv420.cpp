#include "yuv420.h"

YUV420::YUV420(const std::string &filename, int width, int height) : width(width), height(height)
{
    std::cout << "Loading YUV file..." << std::endl;
    std::ifstream yuvFile(filename, std::ios::binary);
    if (!yuvFile.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    size_t frameSize = width * height;
    size_t chromaSize = (width / 2) * (height / 2);
    while (true)
    {
        YUV420Frame frame;
        frame.yPlane.resize(frameSize);
        frame.uPlane.resize(chromaSize);
        frame.vPlane.resize(chromaSize);
        
        yuvFile.read(reinterpret_cast<char*>(frame.yPlane.data()), frameSize);
        yuvFile.read(reinterpret_cast<char*>(frame.uPlane.data()), chromaSize);
        yuvFile.read(reinterpret_cast<char*>(frame.vPlane.data()), chromaSize);
        frame.width = width;
        frame.height = height;
        frames.push_back(std::move(frame));

        if (yuvFile.eof())
            break;
    }
    yuvFile.close();
    std::cout << "YUV file loaded successfully." << std::endl;
}

void YUV420::save(const std::string &filename)
{
    std::cout << "Saving YUV file..." << std::endl;
    std::ofstream yuvFile(filename, std::ios::binary);
    if (!yuvFile.is_open())
    {
        std::cerr << "Error opening output file." << std::endl;
        return;
    }
    
    for (const auto& frame : frames)
    {
        yuvFile.write(reinterpret_cast<const char*>(frame.yPlane.data()), frame.yPlane.size());
        yuvFile.write(reinterpret_cast<const char*>(frame.uPlane.data()), frame.uPlane.size());
        yuvFile.write(reinterpret_cast<const char*>(frame.vPlane.data()), frame.vPlane.size());
    }
    
    yuvFile.close();
    std::cout << "YUV file saved successfully." << std::endl;
}