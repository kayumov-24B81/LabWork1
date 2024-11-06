/* Kayumov Airat st128100@student.spbu.ru
   This is header file for apply_filter.cpp file and contains declaration of apply_filter function.
*/
#ifndef APPLY_FILTER_HPP
#define APPLY_FILTER_HPP

#include "bmp.hpp"

void apply_filter(BMP_HEADER &bmp_header, DIB_HEADER &dib_header, std :: vector<unsigned char>& pixels, std :: vector<unsigned char>& color_palette, short radius, float sigma);

#endif
