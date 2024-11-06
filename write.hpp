/* Kayumov Airat st128100@student.spbu.ru
   This is header file for write.cpp file and contains declaration of write function.
*/
#ifndef WRITE_HPP
#define WRITE_HPP

#include "bmp.hpp"

void write(BMP_HEADER &bmp_header, DIB_HEADER &dib_header, std :: vector<unsigned char>& pixels, std :: vector<unsigned char>& color_palette, const char* fname);

#endif
