/* Kayumov Airat st128100@student.spbu.ru
   This file contains defenition of Matrix class methods. Matrix creation, filling and normalization were splitted in three functions.
*/

#include "matrix.hpp"
#include <cmath>
#include <thread>

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
    sum = 0;
    
    for(short x = -radius; x <= radius; ++x)
    {
        for(short y = -radius; y <= radius; ++y)
        {
            matrixContents[x + radius][y + radius] = (1 / (2 * 3.14 * sigma)) * exp(-1*(x * x + y * y) / (2 * sigma * sigma));
            sum += matrixContents[x + radius][y + radius];
        }
    }
}

void Matrix :: fillGaussianMatrixWThreads(float sigma)
{
    short radius = matrixContents.size() / 2;
    sum = 0;
    
    const int size = 2 * radius + 1;
    const float a = 2 * 3.14 * sigma * sigma;
    const float b = 2 * sigma * sigma;
    
    unsigned threads_amount = std :: thread :: hardware_concurrency();
    std :: vector<std :: thread> threads;
    std :: vector<float> partial_sums(threads_amount, 0);
    
    int total_rows = 2 * radius + 1;
    int rows_per_thread = total_rows / threads_amount;
    
    
    for(unsigned t = 0; t < threads_amount; ++t)
    {
        int start_idx = -radius + t * rows_per_thread;
        int end_idx = start_idx + rows_per_thread;
        if(t == threads_amount - 1) end_idx = radius + 1;
        
        threads.emplace_back([&, start_idx, end_idx, t, radius, size, a, b]()
        {
            float local_sum = 0;
            
            for(int x = start_idx; x < end_idx; ++x)
            {
                for(int y = -radius; y <= radius; ++y)
                {
                    float value = (1.0 / a) * exp(-1.0 * (x * x + y * y) / b);
                    matrixContents[x + radius][y + radius] = value;
                    local_sum += value;
                }
            }
            
            partial_sums[t] = local_sum;
        });
    }
    
    for(auto& thread : threads)
    {
        thread.join();
    }
    
    for(float partial : partial_sums)
    {
        sum += partial;
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





