/* Kayumov Airat st128100@student.spbu.ru
   This is main.cpp file. Mainly in calls methods of Image and Matrix class. Reads source image, rotates if left, writes, reads source image again, rotates it right, writes, applies filter, writes.
*/

#include "image.hpp"

int main()
{
    Image Image;
    
    Image.read("source.bmp");
    Image.rotateLeft();
    Image.write("rotated_left.bmp");
    
    Image.read("source.bmp");
    Image.rotateRight();
    Image.write("rotated_right.bmp");
    
    Matrix gaussianMatrix(5);
    gaussianMatrix.fillGaussianMatrix(2.0);
    gaussianMatrix.normalize();
    
    Image.applyGaussianFilter(gaussianMatrix.getContents());
    Image.write("filtered.bmp");
}
