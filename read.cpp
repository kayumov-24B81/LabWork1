/* Kayumov Airat st128100@student.spbu.ru
   This is read.cpp file. This file contains read function, that writes bmp file into memory (except for editors information). All containers and vectors are adressed through references. It also can consider padding and doesn't write padding bytes. This file also changes value of the offset from Bitmap file header and image size from DIB header to match the size of image contained in memory. This is needed because editors information is not saved.
*/

#include <vector>
#include <fstream>
#include "read.hpp"

void read(BMP_HEADER &bmp_header, DIB_HEADER &dib_header, std :: vector<unsigned char> &pixels, std :: vector<unsigned char> &color_palette, const char* fname)
{
    std :: ifstream text;
    
    text.open(fname, std :: ios_base :: binary);
    
    text.read((char*)&bmp_header, sizeof(bmp_header));
    text.read((char*)&dib_header, sizeof(dib_header));
    
    text.read((char*)color_palette.data(), 256*4);
    
    text.seekg(bmp_header.pixel_data_address, text.beg);
    
    dib_header.dib_size = sizeof(dib_header);
    bmp_header.pixel_data_address = dib_header.dib_size + sizeof(bmp_header) + color_palette.size();
    bmp_header.bmp_size = bmp_header.pixel_data_address;
    
    pixels.resize((dib_header.bits_per_pixel * dib_header.width * dib_header.height) / 8);
    
    
    if(dib_header.width % 4 == 0)
    {
        text.read((char*)pixels.data(), pixels.size());
        bmp_header.bmp_size += pixels.size();
    }
    
    else
    {
        unsigned row_size = (dib_header.bits_per_pixel * dib_header.width) / 8;
        unsigned padding_size = 0;
        
        while((row_size + padding_size) % 4 != 0)
        {
            ++padding_size;
        }
        
        unsigned char *padding = new unsigned char[padding_size];
        
        for(int y = 0; y < dib_header.height; ++y)
        {
            text.read((char*)(pixels.data() + y*row_size), row_size);
            text.read((char*)padding, padding_size);
        }
        
        bmp_header.bmp_size += pixels.size() + dib_header.height * sizeof(unsigned char) * padding_size;

        delete [] padding;
     }
     
}
        
        
        
        
        
        
    
    
