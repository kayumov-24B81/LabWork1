#include <vector>
#include <iostream>
#include "bmp.hpp"

int main()
{
    BMP_HEADER bmp_header;
    DIB_HEADER dib_header;
    
    std::vector<unsigned char> pixels;
    std::vector<unsigned char> color_palette(256 * 4);
    
    read(bmp_header, dib_header, pixels, color_palette, "source.bmp");
    rotate_right(bmp_header, dib_header, pixels, color_palette, "source.bmp");
    
    return 0;
}
