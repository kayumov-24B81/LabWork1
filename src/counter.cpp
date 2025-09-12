#include "image.hpp"
#include "matrix.hpp"
#include "counter.hpp"
#include <iostream>
#include <thread>

int main(int argc, char* argv[])
{
    std :: string filename = "images/";
    if(argc > 1)
    {
         filename += std :: string(argv[1]);
    }
    
    else
    {
        std :: cerr << "Error: no testing image is provided" << std :: endl;
        return 1;
    }
    Image Image;
    Image.read(filename);
    
    unsigned threads_amount = std :: thread :: hardware_concurrency();
    std :: cout << "Active threads : " << threads_amount << std :: endl;
    int iterations = 5;
    std :: cout << "Iterations amount: " << iterations << std :: endl;
    const int matrix_size = 10;
    const float sigma = 2.0;
    Matrix matrix(matrix_size);
    std :: cout << "Matrix size: " << matrix_size << std :: endl;
    std :: cout << "Sigma parameter: " << sigma << std :: endl;
    
    std :: cout << "=== MULTI THREAD TESTING ===" << std :: endl;
    
    double right_time = measureOperation([&]() 
    {
        for (int i = 0; i < iterations; ++i) 
        {
            Image.rotateRightWThreads();
        }
    });
    
    double left_time = measureOperation([&]() 
    {
        for (int i = 0; i < iterations; ++i) 
        {
            Image.rotateLeftWThreads();
        }
    });
    
    double fill_time = measureOperation([&]() 
    {
        for (int i = 0; i < iterations; ++i) 
        {
            matrix.fillGaussianMatrixWThreads(sigma);
        }
    });
    
    double filter_time = measureOperation([&]() 
    {
        for (int i = 0; i < iterations; ++i) 
        {
            Image.applyGaussianFilterWThreads(matrix.getContents());
        }
    });
    
    
    std :: cout << "Rotate right: " << right_time / iterations << "ms" << std :: endl;
    std :: cout << "Rotate left: " << left_time / iterations << "ms" << std :: endl;
    std :: cout << "Fill matrix: " << fill_time / iterations << "ms" << std :: endl;
    std :: cout << "Apply filter: " << filter_time / iterations << "ms" << std :: endl;
    std :: cout << "Total time: " << (right_time + left_time + fill_time + filter_time) / iterations << "ms" << std :: endl;
    
    std :: cout << "=== SINGLE THREAD TESTING ===" << std :: endl;
    
    right_time = measureOperation([&]() 
    {
        for (int i = 0; i < iterations; ++i) 
        {
            Image.rotateRight();
        }
    });
    
    left_time = measureOperation([&]() 
    {
        for (int i = 0; i < iterations; ++i) 
        {
            Image.rotateLeft();
        }
    });

    fill_time = measureOperation([&]() 
    {
        for (int i = 0; i < iterations; ++i) 
        {
            matrix.fillGaussianMatrix(sigma);
        }
    });
    
    filter_time = measureOperation([&]() 
    {
        for (int i = 0; i < iterations; ++i) 
        {
            Image.applyGaussianFilter(matrix.getContents());
        }
    });
    
    std :: cout << "Rotate right: " << right_time / iterations << "ms" << std :: endl;
    std :: cout << "Rotate left: " << left_time / iterations << "ms" << std :: endl;
    std :: cout << "Fill matrix: " << fill_time / iterations << "ms" << std :: endl;
    std :: cout << "Apply filter: " << filter_time / iterations << "ms" << std :: endl;
    std :: cout << "Total time: " << (right_time + left_time + fill_time + filter_time) / iterations << "ms" << std :: endl;
}
        
