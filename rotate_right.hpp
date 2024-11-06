/* Kayumov Airat st128100@student.spbu.ru
   This is header file for rotate_right.cpp file and contains declaration of rotate_right function.
*/
#ifndef ROTATE_RIGHT_HPP
#define ROTATE_RIGHT_HPP

#include "bmp.hpp"

void rotate_right(BMP_HEADER &bmp_header, DIB_HEADER &dib_header, std :: vector<unsigned char>& pixels, std :: vector<unsigned char>& color_palette, bool &was_rotated);

#endif
