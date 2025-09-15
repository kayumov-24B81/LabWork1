/* Kayumov Airat st128100@student.spbu.ru
   This file contains declaration of BMP_HEADER and DIB_HEADER structures and Image class. Both redacted and clean image data are contained inside Image object to reduce the number of calculations. All functions optimized using multithreading have their single-threaded versions preserved.
*/
#include <string>
#include "matrix.hpp"
#include <filesystem>


#ifndef BMP_HPP
#define BMP_HPP

#pragma pack(push,  1)

struct BMP_HEADER
{
    unsigned short header_field;
    unsigned bmp_size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned pixel_data_address;
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

class Image
{
private:
    BMP_HEADER bmpHeader;
    DIB_HEADER dibHeader;
    std::vector<unsigned char> colorPalette;
    std :: vector<unsigned char> originalPixels;
    std::vector<unsigned char> pixels;
public:
    Image();
    void read(std :: string fileName);
    void write(std :: string fileName);
    void rotateLeft();
    void rotateLeftWThreads();
    void rotateRight();
    void rotateRightWThreads();
    void applyGaussianFilter(std :: vector<std :: vector<float>> matrix);
    void applyGaussianFilterWThreads(std :: vector<std :: vector<float>> matrix);
};


#endif
