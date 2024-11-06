/* Kayumov Airat st128100@student.spbu.ru
   This is apply_filter.cpp file. It contains apply_filter function that applies gaussian filter to image in memory and then calls write function. Matrix is created with create_matrix function. Parameters for create_matrix function are requested in this function.
*/
#include <vector>
#include "apply_filter.hpp"
#include "create_matrix.hpp"
#include "write.hpp"

void apply_filter(BMP_HEADER &bmp_header, DIB_HEADER &dib_header, std :: vector<unsigned char>& pixels, std :: vector<unsigned char>& color_palette, short radius, float sigma)
{
    std :: vector<std :: vector<float>> matrix = create_matrix(radius, sigma);
    std :: vector<unsigned char> filtered(pixels.size());
    
    for(int y = 0; y < dib_header.height; ++y)
    {
        for(int x = 0; x < dib_header.width; ++x)
        {
            double blurred_pixel = 0.0;
            
            for(short my = -radius; my <= radius; ++my)
            {
                for(short mx = -radius; mx <= radius; ++ mx)
                {
                    int newx = std :: min(std :: max(x + mx, 0), dib_header.width - 1);
                    int newy = std :: min(std :: max(y + my, 0), dib_header.height - 1);
                    
                    blurred_pixel += pixels[newx + newy*dib_header.width] * matrix[mx + radius][my + radius];
                }
            }
            
            filtered[x + y*dib_header.width] = static_cast<unsigned char>(blurred_pixel);
        }
    }
    write(bmp_header, dib_header, filtered, color_palette, "filtered.bmp");
}
    





