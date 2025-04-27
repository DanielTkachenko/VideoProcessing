#include "bmp.h"

BMP::BMP(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open BMP file.");
    }

    // Read BMP header
    file.read(reinterpret_cast<char*>(&bmpHeader), sizeof(bmpHeader));
    if (bmpHeader.fileType != 0x4D42) // 'BM'
    {
        throw std::runtime_error("Not a valid BMP file.");
    }
    // Read DIB header
    file.read(reinterpret_cast<char*>(&dibHeader), sizeof(dibHeader));
    if (dibHeader.bitCount != 24)
    {
        throw std::runtime_error("Only 24-bit BMP files are supported.");
    }
    if (dibHeader.compression != 0)
    {
        throw std::runtime_error("Only uncompressed BMP files are supported.");
    }

    // Read pixel data
    file.seekg(bmpHeader.offsetBits, std::ios::beg);
    pixelData.resize(dibHeader.width * dibHeader.height);
    
    int rowSize = (dibHeader.width * 3 + 3) & ~3;

    for (int i = 0; i < dibHeader.height; ++i)
    {
        for (int j = 0; j < dibHeader.width; ++j)
        {
            file.read(reinterpret_cast<char*>(&pixelData[i * dibHeader.width + j]), sizeof(PixelData));
        }
        
        file.ignore(rowSize - dibHeader.width * sizeof(PixelData));
    }
    
    file.close();

    intoYUV(); // Convert to YUV format immediately after loading

    std::cout << "BMP file loaded successfully." << std::endl;
}

void BMP::intoYUV()
{
    std::cout << "Converting BMP to YUV420 format..." << std::endl;
    yuvData.yPlane.resize(dibHeader.width * dibHeader.height);
    yuvData.uPlane.resize((dibHeader.width / 2) * (dibHeader.height / 2));
    yuvData.vPlane.resize((dibHeader.width / 2) * (dibHeader.height / 2));

    std::vector<float> uTemp((dibHeader.width / 2) * (dibHeader.height / 2), 0.0f);
    std::vector<float> vTemp((dibHeader.width / 2) * (dibHeader.height / 2), 0.0f);

    // Convert RGB to YUV420 format
    for(int i = 0; i < dibHeader.height; ++i)
    {
        for (int j = 0; j < dibHeader.width; ++j)
        {
            PixelData& pixel = pixelData[i * dibHeader.width + j];
            uint8_t b = pixel.b;
            uint8_t g = pixel.g;
            uint8_t r = pixel.r;
            

            // Convert RGB to YUV
            uint8_t y = (0.299 * r + 0.587 * g + 0.114 * b);
            uint8_t u = (128 - 0.14713 * r - 0.28886 * g + 0.436 * b);
            uint8_t v = (128 + 0.615 * r - 0.51499 * g - 0.10001 * b);

            yuvData.yPlane[i * dibHeader.width + j] = y;

            if (i % 2 == 0 && j % 2 == 0) // Subsampling for U and V planes
            {
                yuvData.uPlane[(i / 2) * (dibHeader.width / 2) + (j / 2)] = u;
                yuvData.vPlane[(i / 2) * (dibHeader.width / 2) + (j / 2)] = v;
            }
        }
    }

    std::cout << "Conversion to YUV420 format completed." << std::endl;
}



void BMP::save(const std::string& filename)
{
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open output YUV file.");
    }
    file.write(reinterpret_cast<const char*>(&bmpHeader), sizeof(bmpHeader));
    file.write(reinterpret_cast<const char*>(&dibHeader), sizeof(dibHeader));

    // Write pixel data
    int rowSize = (dibHeader.width * 3 + 3) & ~3;
    for (int i = 0; i < dibHeader.height; ++i)
    {
        for (int j = 0; j < dibHeader.width; ++j)
        {
            file.write(reinterpret_cast<const char*>(&pixelData[i * dibHeader.width + j]), sizeof(PixelData));
        }
        
        // Padding to the next 4-byte boundary
        unsigned char padding[3] = { 0, 0, 0 };
        file.write(reinterpret_cast<const char*>(padding), rowSize - dibHeader.width * sizeof(PixelData));
    }

    file.close();
    std::cout << "BMP file saved successfully." << std::endl;
}

void BMP::saveYUV(const std::string& filename)
{
    std::ofstream yuvFile(filename, std::ios::binary);
    if (!yuvFile.is_open())
    {
        throw std::runtime_error("Could not open output YUV file.");
    }
    yuvFile.write(reinterpret_cast<const char*>(yuvData.yPlane.data()), yuvData.yPlane.size());
    yuvFile.write(reinterpret_cast<const char*>(yuvData.uPlane.data()), yuvData.uPlane.size());
    yuvFile.write(reinterpret_cast<const char*>(yuvData.vPlane.data()), yuvData.vPlane.size());
    yuvFile.close();
    std::cout << "YUV file saved successfully." << std::endl;
}