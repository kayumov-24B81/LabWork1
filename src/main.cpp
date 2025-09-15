/* Kayumov Airat st128100@student.spbu.ru
   This is main.cpp file. All launch parameters are processed here. Further all actions are performed using Image and Matrix class methods.
*/

#include "image.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    bool rotate_right = false;
    bool rotate_left = false;
    bool apply_filter = false;
    bool use_threads = false;
    std :: string filename = "images/source.bmp";
    
    for(int i = 0; i < argc; ++i)
    {
        std :: string arg(argv[i]);
        if(arg == "--rotate-right") rotate_right = true;
        else if(arg == "--rotate-left") rotate_left = true;
        else if(arg == "--apply-filter") apply_filter = true;
        else if(arg == "--threads") use_threads = true;
        else if(arg.find(".bmp") != std::string::npos) filename = "images/" + arg;
    }
    
    if(not(rotate_right || rotate_left || apply_filter))
    {
        std :: cout << "None of the launch parameters were specified." << std :: endl;
        std :: cout << "Available options: " << std :: endl;
        std :: cout << "1. --rotate-right - rotate image right by 90 degrees and save;" << std :: endl;
        std :: cout << "2. --rotate-left - rotate image left by 90 degrees and save;" << std :: endl;
        std :: cout << "3. --apply-filter - apply gaussian filter to the image;" << std :: endl;
        std :: cout << "4. --threads - enable usage of multiple threads;" << std :: endl;
        return 0;
    }
    else
    {
        Image Image;
        try
        {
            Image.read(filename);
        }
        catch(std::string exception)
        {
            std :: cout << "Error reading file: " << exception << std :: endl;
        }

        
        if(rotate_left)
        {
            if(use_threads) Image.rotateLeftWThreads();
            else Image.rotateLeft();
            Image.write("rotated_left.bmp");
        }
        if(rotate_right)
        {
            if(use_threads) Image.rotateRightWThreads();
            else Image.rotateRight();
            Image.write("rotated_right.bmp");
        }
        if(apply_filter)
        {      
            int size = 0;
            std :: cout << "Enter the size of the gaussian matrix:" << std :: endl;
            std :: cin >> size;
            
            Matrix gaussianMatrix(size);
            if(use_threads) gaussianMatrix.fillGaussianMatrixWThreads(2.0);
            else gaussianMatrix.fillGaussianMatrix(2.0);
            gaussianMatrix.normalize();

            if(use_threads) Image.applyGaussianFilterWThreads(gaussianMatrix.getContents());
            else Image.applyGaussianFilter(gaussianMatrix.getContents());
            Image.write("filtered.bmp");
        }
    }
}
