#ifndef BMP_HPP
#define BMP_HPP

#pragma pack(push,  1)

struct BMP_HEADER
{
    unsigned short header_field;
    unsigned bmp_size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixel_data_address;
};

struct DIB_HEADER
{
    unsigned dib_size;
    int width;
    int height;
    unsigned short color_planes;
    unsigned short bits_per_pixel;
    unsigned compression_method;
    unsigned image_size;
    int x_pixel_per_metre;
    int y_pixel_per_metre;
    unsigned colors_amount;
    unsigned important_colors_amount;
};

#pragma pack(pop)






#endif
