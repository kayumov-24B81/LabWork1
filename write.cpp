#include <vector>
#include <fstream>
#include "bmp.hpp"

void write(BMP_HEADER &bmp_header, DIB_HEADER &dib_header, std :: vector<unsigned char> &pixels, std :: vector<unsigned char> &color_palette, const char* fname)
{
    std :: ofstream text;
    
    text.open(fname, std :: ios_base :: binary);
    
    text.write((char*)&bmp_header, sizeof(bmp_header));
    text.write((char*)&dib_header, sizeof(dib_header));
    
    text.write((char*)color_palette.data(), 256 * 4);
    
    if(dib_header.width % 4 == 0)
    {
        text.write((char*)pixels.data(), pixels.size());
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
            text.write((char*)(pixels.data() + y*dib_header.width), row_size);
            text.write((char*)padding, padding_size);
        }
        
        delete [] padding;
    }
}
        
        
        
        
        
        
        
