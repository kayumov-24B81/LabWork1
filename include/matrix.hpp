/* Kayumov Airat st128100@student.spbu.ru
   This file contains declaration of Matrix class. All functions optimized using multithreading have their single-threaded versions preserved.
*/

#include <vector>

#ifndef MATRIX_HPP
#define MATRIX_HPP

class Matrix
{
private:
    std :: vector<std :: vector<float>> matrixContents;
    float sum;
public:
    Matrix(short radius);
    void fillGaussianMatrix(float sigma);
    void fillGaussianMatrixWThreads(float sigma);
    void normalize();
    std :: vector<std :: vector<float>> getContents();
};
    
#endif
