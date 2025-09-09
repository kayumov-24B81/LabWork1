/* This file contains definition of Image class methods. Now all functions only interact with contents of given object. No arguments, associated with contents of file are taken. Read and write methods first interact with headers of the file and color palette, then read/write pixels information with or without padding with zeros.
*/

#include "image.hpp"
#include <fstream>
#include <thread>
#include <algorithm>

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
    
    originalPixels.resize((dibHeader.bits_per_pixel * dibHeader.width * dibHeader.height) / 8);
    
    if(dibHeader.width % 4 == 0)
    {
        file.read((char*)originalPixels.data(), originalPixels.size());
        bmpHeader.bmp_size += originalPixels.size();
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
            file.read((char*)(originalPixels.data() + y*row_size), row_size);
            file.read((char*)padding, padding_size);
        }
        
        bmpHeader.bmp_size += originalPixels.size() + dibHeader.height * sizeof(unsigned char) * padding_size;

        delete [] padding;
    }
    pixels.resize(originalPixels.size());
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
    const int height = dibHeader.height;
    const int width = dibHeader.width;
    
    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            int original_index = x + y*width;
            int rotated_index = height - 1 - y + x*height;
            pixels[rotated_index] = originalPixels[original_index];
        }
    }
    
    std::swap(dibHeader.width, dibHeader.height);
}


void Image :: rotateLeftWThreads()
{
    const int height = dibHeader.height;
    const int width = dibHeader.width;
    
    unsigned threads_amount = std :: thread :: hardware_concurrency();
    if(threads_amount == 0) threads_amount = 4;
    
    std :: vector<std :: thread> threads;
    int rows_per_thread = height / threads_amount;
    
    for(unsigned t = 0; t < threads_amount; ++t)
    {
        int start_y = t * rows_per_thread;
        int end_y = start_y + rows_per_thread;
        if(t == threads_amount - 1) end_y = height;
        
        threads.emplace_back([&, start_y, end_y]()
        {
           for(int y = start_y; y < end_y; ++y)
           {
               for(int x = 0; x < width; ++x)
               {
                   int original_index = x + y*width;
                   int rotated_index = height - 1 - y + x*height;
                   pixels[rotated_index] = originalPixels[original_index];
               }
            }
         });
    }
    
    for (auto& thread : threads)
    {
        thread.join();
    }
    
    std::swap(dibHeader.width, dibHeader.height);
}

void Image :: rotateRight()
{
    const int height = dibHeader.height;
    const int width = dibHeader.width;
    
    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            int original_index = x + y * width;
            int rotated_index = y + (width - 1 - x) * height;
            pixels[rotated_index] = originalPixels[original_index];
        }
    }
    
    std::swap(dibHeader.width, dibHeader.height);
}

void Image :: rotateRightWThreads()
{
    const int height = dibHeader.height;
    const int width = dibHeader.width;
    
    unsigned threads_amount = std :: thread :: hardware_concurrency();
    if(threads_amount == 0) threads_amount = 4;
    
    std :: vector<std :: thread> threads;
    int rows_per_thread = height / threads_amount;
    
    for(unsigned t = 0; t < threads_amount; ++t)
    {
        int start_y = t * rows_per_thread;
        int end_y = start_y + rows_per_thread;
        if(t == threads_amount - 1) end_y = height;
        
        threads.emplace_back([&, start_y, end_y]()
        {
           for(int y = start_y; y < end_y; ++y)
           {
               for(int x = 0; x < width; ++x)
               {
                   int original_index = x + y * width;
                   int rotated_index = y + (width - 1 - x) * height;
                   pixels[rotated_index] = originalPixels[original_index];
               }
            }
         });
    }
    
    for (auto& thread : threads)
    {
        thread.join();
    }
    
    std::swap(dibHeader.width, dibHeader.height);
}

void Image :: applyGaussianFilter(std :: vector<std :: vector<float>> matrix)
{
    short radius = matrix.size() / 2;
    const int width = dibHeader.width;
    const int height = dibHeader.height;
    
    auto clamp_x = [width](int x)
    {
        return std::min(std::max(x, 0), width - 1);
    };
    auto clamp_y = [height](int y)
    {
        return std::min(std::max(y, 0), height - 1);
    };
    
    for(int y = 0; y < height; ++y)
    {
        const int y_times_width = y * width;
        for(int x = 0; x < width; ++x)
        {
            double blurred_pixel = 0.0;
            
            for(short my = -radius; my <= radius; ++my)
            {
                int newy = clamp_y(y + my);
                int newy_times_width = newy * width;
                for(short mx = -radius; mx <= radius; ++ mx)
                {
                    int newx = clamp_x(x + mx);
                    blurred_pixel += originalPixels[newx + newy_times_width] * matrix[mx + radius][my + radius];
                }
            }            
            pixels[x + y_times_width] = static_cast<unsigned char>(blurred_pixel);
        }
    }
}

void Image :: applyGaussianFilterWThreads(std :: vector<std :: vector<float>> matrix)
{
    short radius = matrix.size() / 2;
    const int width = dibHeader.width;
    const int height = dibHeader.height;
    
    auto clamp_x = [width](int x)
    {
        return std::min(std::max(x, 0), width - 1);
    };
    auto clamp_y = [height](int y)
    {
        return std::min(std::max(y, 0), height - 1);
    };
    
    unsigned threads_amount = std :: thread :: hardware_concurrency();
    std :: vector<std :: thread> threads;
    int rows_per_thread = height / threads_amount;
    
    for(unsigned t = 0; t < threads_amount; ++t)
    {
        int start_y = t * rows_per_thread;
        int end_y = start_y + rows_per_thread;
        if(t == threads_amount - 1) end_y = height;
        
        threads.emplace_back([&, start_y, end_y, radius, width, height, clamp_x, clamp_y]()
        {
            for(int y = start_y; y < end_y; ++y)
            {
                const int y_times_width = y * width;
                
                for(int x = 0; x < width; ++x)
                {
                    double blurred_pixel = 0;
                    for(short my = -radius; my <= radius; ++my)
                    {
                        int newy = clamp_y(y + my);
                        int newy_times_width = newy * width;
                        
                        for(short mx = -radius; mx <= radius; ++mx)
                        {
                            int newx = clamp_x(x + mx);
                            blurred_pixel += originalPixels[newx + newy_times_width] * matrix[mx + radius][my + radius];
                        }
                    }
                    pixels[x + y_times_width] = static_cast<unsigned char>(blurred_pixel);
                }
            }
        });
    }
    
    for(auto& thread : threads)
    {
        thread.join();
    }
}

