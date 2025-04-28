#include "imageconverter.h"
#include <vector>
#include <thread>

void convertChunk(const std::vector<PixelData> &rawData, YUV420Frame &yuvFrame, int startY, int endY, int width)
{
    for(size_t i = startY; i < endY; ++i)
    {
        for (size_t j = 0; j < width; ++j)
        {
            PixelData pixel = rawData[i * width + j];

            // Convert RGB to YUV
            uint8_t y = (0.299 * pixel.r + 0.587 * pixel.g + 0.114 * pixel.b);
            uint8_t u = (128 - 0.14713 * pixel.r - 0.28886 * pixel.g + 0.436 * pixel.b);
            uint8_t v = (128 + 0.615 * pixel.r - 0.51499 * pixel.g - 0.10001 * pixel.b);

            yuvFrame.yPlane[i * width + j] = y;

            if (i % 2 == 0 && j % 2 == 0) // Subsampling for U and V planes
            {
                yuvFrame.uPlane[(i / 2) * (width / 2) + (j / 2)] = u;
                yuvFrame.vPlane[(i / 2) * (width / 2) + (j / 2)] = v;
            }
        }
    }
}

YUV420Frame ImageConverter::convertBMPToYUV420(const BMP &bmpFile, int numThreads)
{
    std::cout << "Converting BMP to YUV420 format..." << std::endl;
    
    std::vector<std::thread> threads;

    YUV420Frame yuvFrame;
    int width = bmpFile.getWidth();
    int height = bmpFile.getHeight();
    yuvFrame.width = width;
    yuvFrame.height = height;
    const std::vector<PixelData>& rawData = bmpFile.getRawData();
    yuvFrame.yPlane.resize(width * height);
    yuvFrame.uPlane.resize((width / 2) * (height / 2));
    yuvFrame.vPlane.resize((width / 2) * (height / 2));

    for(size_t i = 0; i < numThreads; ++i)
    {
        int startY = (height / numThreads) * i;
        int endY = (i == numThreads - 1) ? height : (height / numThreads) * (i + 1);
        threads.emplace_back(std::thread(&convertChunk, std::ref(rawData), std::ref(yuvFrame), startY, endY, width));
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Successfully converted BMP to YUV420!" << std::endl;
    return yuvFrame;
}

