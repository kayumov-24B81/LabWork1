#include <vector>
#include "bmp.hpp"

void rotate_right(BMP_HEADER &bmp_header, DIB_HEADER &dib_header, std :: vector<unsigned char>& pixels, std :: vector<unsigned char>& color_palette, bool &was_rotated)
{
    std :: vector<unsigned char> rotated(pixels.size());
    
    for(int y = 0; y < dib_header.height; ++y)
    {
        for(int x = 0; x < dib_header.width; ++x)
        {
            rotated[y + (dib_header.width - 1 - x)*dib_header.height] = pixels[x + y*dib_header.width];
        }
    }
    
    if(not(was_rotated))
    {
        int temp = dib_header.width;
        dib_header.width = dib_header.height;
        dib_header.height = temp;
    }
    
    was_rotated = not(was_rotated);
    
    write(bmp_header, dib_header, rotated, color_palette, "rotated_right.bmp");
}
    
