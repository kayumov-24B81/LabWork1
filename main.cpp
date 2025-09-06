/* Kayumov Airat st128100@student.spbu.ru
   This is main.cpp file. All storages with bmp file information are initialized here, so it's easier to adress to file information from different functions called here. Besides this, it also reads variables needed for gaussian matrix creation from console.
*/

#include "image.hpp"
#include <iostream>

int main()
{
    Image Image;
    
    Image.read("source.bmp");
    Image.rotateLeft();
    Image.write("rotated_left.bmp");
    
    Image.read("source.bmp");
    Image.rotateRight();
    Image.write("rotated_right.bmp");
    
    
    int size = 0;
    std :: cout << "Enter the size of the gaussian matrix:" << std :: endl;
    std :: cin >> size;
    
    Matrix gaussianMatrix(size);
    gaussianMatrix.fillGaussianMatrix(2.0);
    gaussianMatrix.normalize();
    
    Image.applyGaussianFilter(gaussianMatrix.getContents());
    Image.write("filtered.bmp");
}
