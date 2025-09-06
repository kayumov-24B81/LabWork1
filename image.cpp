/* This file contains definition of Image class methods. Now all functions only interact with contents of given object. No arguments, associated with contents of file are taken. Read and write methods first interact with headers of the file and color palette, then read/write pixels information with or without padding with zeros.
*/

#include "image.hpp"
#include <fstream>

Image :: Image()
{
     colorPalette.resize(256*4);
}

void Image :: read(std :: string fileName)
{
    std :: ifstream file;
    file.open(fileName, std :: ios_base :: binary);
    
    file.read((char*)&bmpHeader, sizeof(bmpHeader));
    file.read((char*)&dibHeader, sizeof(dibHeader));
    file.read((char*)colorPalette.data(), 256*4);
    
    file.seekg(bmpHeader.pixel_data_address, file.beg);
    
    dibHeader.dib_size = sizeof(dibHeader);
    bmpHeader.pixel_data_address = dibHeader.dib_size + sizeof(bmpHeader) + colorPalette.size();
    bmpHeader.bmp_size = bmpHeader.pixel_data_address;
    
    pixels.resize((dibHeader.bits_per_pixel * dibHeader.width * dibHeader.height) / 8);
    
    if(dibHeader.width % 4 == 0)
    {
        file.read((char*)pixels.data(), pixels.size());
        bmpHeader.bmp_size += pixels.size();
    }
    else
    {
        unsigned row_size = (dibHeader.bits_per_pixel * dibHeader.width) / 8;
        unsigned padding_size = 0;
        
        while((row_size + padding_size) % 4 != 0)
        {
            ++padding_size;
        }
        
        unsigned char *padding = new unsigned char[padding_size];
        
        for(int y = 0; y < dibHeader.height; ++y)
        {
            file.read((char*)(pixels.data() + y*row_size), row_size);
            file.read((char*)padding, padding_size);
        }
        
        bmpHeader.bmp_size += pixels.size() + dibHeader.height * sizeof(unsigned char) * padding_size;

        delete [] padding;
    }
}

void Image :: write(std :: string fileName)
{
    std :: ofstream file;
    file.open(fileName, std :: ios_base :: binary);
    file.write((char*)&bmpHeader, sizeof(bmpHeader));
    file.write((char*)&dibHeader, sizeof(dibHeader));
    file.write((char*)colorPalette.data(), 256 * 4);
    
    if(dibHeader.width % 4 == 0)
    {
        file.write((char*)pixels.data(), pixels.size());
    }
    else
    {
        unsigned row_size = (dibHeader.bits_per_pixel * dibHeader.width) / 8;
        unsigned padding_size = 0;
        
        while((row_size + padding_size) % 4 != 0)
        {
            ++padding_size;
        }
        
        unsigned char *padding = new unsigned char[padding_size];
        
        for(int y = 0; y < dibHeader.height; ++y)
        {
            file.write((char*)(pixels.data() + y*dibHeader.width), row_size);
            file.write((char*)padding, padding_size);
        }
        
        delete [] padding;
    }
}

void Image :: rotateLeft()
{
    std :: vector<unsigned char> originalPixels(pixels);
    
    for(int y = 0; y < dibHeader.height; ++y)
    {
        for(int x = 0; x < dibHeader.width; ++x)
        {
            pixels[(dibHeader.height - 1 - y) + x*dibHeader.height] = originalPixels[x + y*dibHeader.width];
        }
    }
    
    int temp = dibHeader.width;
    dibHeader.width = dibHeader.height;
    dibHeader.height = temp;;
}

void Image :: rotateRight()
{
    std :: vector<unsigned char> originalPixels(pixels);
    
    for(int y = 0; y < dibHeader.height; ++y)
    {
        for(int x = 0; x < dibHeader.width; ++x)
        {
            pixels[y + (dibHeader.width - 1 - x)*dibHeader.height] = originalPixels[x + y*dibHeader.width];
        }
    }
    
    int temp = dibHeader.width;
    dibHeader.width = dibHeader.height;
    dibHeader.height = temp;
}

void Image :: applyGaussianFilter(std :: vector<std :: vector<float>> matrix)
{
    std :: vector<unsigned char> originalPixels(pixels);
    short radius = matrix.size() / 2;
    
    for(int y = 0; y < dibHeader.height; ++y)
    {
        for(int x = 0; x < dibHeader.width; ++x)
        {
            double blurred_pixel = 0.0;
            
            for(short my = -radius; my <= radius; ++my)
            {
                for(short mx = -radius; mx <= radius; ++ mx)
                {
                    int newx = std :: min(std :: max(x + mx, 0), dibHeader.width - 1);
                    int newy = std :: min(std :: max(y + my, 0), dibHeader.height - 1);
                    
                    blurred_pixel += originalPixels[newx + newy*dibHeader.width] * matrix[mx + radius][my + radius];
                }
            }            
            pixels[x + y*dibHeader.width] = static_cast<unsigned char>(blurred_pixel);
        }
    }
}
