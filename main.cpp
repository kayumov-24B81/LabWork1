/* Kayumov Airat st128100@student.spbu.ru
   This is main.cpp file. All storages with bmp file information are initialized here, so it's easier to adress to file information from different functions called here. Besides this, it also reads variables needed for gaussian matrix creation from console.
*/

#include <vector>
#include <iostream>
#include "read.hpp"
#include "rotate_right.hpp"
#include "rotate_left.hpp"
#include "apply_filter.hpp"

int main()
{
    BMP_HEADER bmp_header;
    DIB_HEADER dib_header;
    
    bool was_rotated = false;

    std::vector<unsigned char> pixels;
    std::vector<unsigned char> color_palette(256 * 4);
    
    read(bmp_header, dib_header, pixels, color_palette, "source.bmp");
    
    rotate_right(bmp_header, dib_header, pixels, color_palette, was_rotated);
    
    rotate_left(bmp_header, dib_header, pixels, color_palette, was_rotated);
    
    short radius = 0;
    float sigma = 0.0;
    
    std :: cout << "Please enter radius and sigma parameter of gaussian matrix" << std :: endl;
    
    std :: cin >> radius >> sigma;
    
    read(bmp_header, dib_header, pixels, color_palette, "rotated_left.bmp");
    
    apply_filter(bmp_header, dib_header, pixels, color_palette, radius, sigma);
    
    return 0;
}
