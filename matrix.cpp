/* Kayumov Airat st128100@student.spbu.ru
   This file contains defenition of Matrix class methods. Matrix creation, filling and normalization were splitted in three functions.
*/

#include "matrix.hpp"
#include <cmath>

Matrix :: Matrix(short radius)
{
    matrixContents.resize(radius*2 + 1);
    
    for(short i = 0; i < radius * 2 + 1; ++i)
    {
        matrixContents[i].resize(radius * 2 + 1);
    }
}

void Matrix :: fillGaussianMatrix(float sigma)
{
    short radius = matrixContents.size() / 2;
    
    for(short x = -radius; x <= radius; ++x)
    {
        for(short y = -radius; y <= radius; ++y)
        {
            matrixContents[x + radius][y + radius] = (1 / (2 * 3.14 * sigma)) * exp(-1*(x * x + y * y) / (2 * sigma * sigma));
            sum += matrixContents[x + radius][y + radius];
        }
    }
}

void Matrix :: normalize()
{
    short radius = matrixContents.size() / 2; 
    for(short x = 0; x < radius * 2 + 1; ++x)
    {
        for(short y = 0; y < radius * 2 + 1; ++y)
        {
            matrixContents[x][y] = matrixContents[x][y] / sum;
        }
    }
}

std :: vector<std :: vector<float>> Matrix :: getContents()
{
    return matrixContents;
}





