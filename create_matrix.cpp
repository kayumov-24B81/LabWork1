#include <iostream>
#include <vector>
#include <cmath>
#include "bmp.hpp"

std :: vector<std :: vector<float>> create_matrix(int radius, float sigma)
{
    float sum = 0.0;
    
    std :: vector<std :: vector<float>> matrix(radius * 2 + 1);
    
    for(int i = 0; i < radius * 2 + 1; ++i)
    {
        matrix[i].resize(radius * 2 + 1);
    }
    
    for(int x = -radius; x <= radius; ++x)
    {
        for(int y = -radius; y <= radius; ++y)
        {
            matrix[x + radius][y + radius] = (1 / (2 * 3.14 * sigma)) * exp(-1*(x * x + y * y) / (2 * sigma * sigma));
            sum += matrix[x + radius][y + radius];
        }
    }
    
    for(int x = 0; x < radius * 2 + 1; ++x)
    {
        for(int y = 0; y < radius * 2 + 1; ++y)
        {
            matrix[x][y] = matrix[x][y] / sum;
        }
    }
    
    return matrix;
}

