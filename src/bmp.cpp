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

    std::cout << "BMP file loaded successfully." << std::endl;
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