#include <vector>
#include "bmp.hpp"

void apply_filter(BMP_HEADER &bmp_header, DIB_HEADER &dib_header, std :: vector<unsigned char>& pixels, std :: vector<unsigned char>& color_palette, int radius, float sigma)
{
    std :: vector<std :: vector<float>> matrix = create_matrix(radius, sigma);
    std :: vector<unsigned char> filtered(pixels.size());
    
    for(int y = 0; y < dib_header.height; ++y)
    {
        for(int x = 0; x < dib_header.width; ++x)
        {
            double blurred_pixel = 0.0;
            
            for(int my = -radius; my <= radius; ++my)
            {
                for(int mx = -radius; mx <= radius; ++ mx)
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
    





