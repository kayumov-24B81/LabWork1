/* Kayumov Airat st128100@student.spbu.ru
   This is header file for rotate_left.cpp file and contains declaration of rotate_left function.
*/
#ifndef ROTATE_LEFT_HPP
#define ROTATE_LEFT_HPP

#include "bmp.hpp"

void rotate_left(BMP_HEADER &bmp_header, DIB_HEADER &dib_header, std :: vector<unsigned char>& pixels, std :: vector<unsigned char>& color_palette, bool &was_rotated);

#endif
