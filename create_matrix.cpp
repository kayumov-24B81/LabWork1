/* Kayumov Airat st128100@student.spbu.ru
   This is create_matrix.cpp file. It contains create_matrix function that takes radius of matrix and sigma variable as parameters to create and normalize gaussian matrix. This function returns matrix (2d vector with floats). This function ins't called by itself in main.cpp file, but in apply_filter function from apply_filter.cpp
*/
#include <vector>
#include <cmath>
#include "create_matrix.hpp"

std :: vector<std :: vector<float>> create_matrix(short radius, float sigma)
{
    float sum = 0.0;
    
    std :: vector<std :: vector<float>> matrix(radius * 2 + 1);
    
    for(short i = 0; i < radius * 2 + 1; ++i)
    {
        matrix[i].resize(radius * 2 + 1);
    }
    
    for(short x = -radius; x <= radius; ++x)
    {
        for(short y = -radius; y <= radius; ++y)
        {
            matrix[x + radius][y + radius] = (1 / (2 * 3.14 * sigma)) * exp(-1*(x * x + y * y) / (2 * sigma * sigma));
            sum += matrix[x + radius][y + radius];
        }
    }
    
    for(short x = 0; x < radius * 2 + 1; ++x)
    {
        for(short y = 0; y < radius * 2 + 1; ++y)
        {
            matrix[x][y] = matrix[x][y] / sum;
        }
    }
    
    return matrix;
}

