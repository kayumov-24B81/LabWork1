/* Kayumov Airat st128100@student.spbu.ru
   This is header file for read.cpp file and contains declaration of read function.
*/
#ifndef READ_HPP
#define READ_HPP

#include "bmp.hpp"

void read(BMP_HEADER &bmp_header, DIB_HEADER &dib_header, std :: vector<unsigned char>& pixels, std :: vector<unsigned char>& color_palette, const char* fname);

#endif
