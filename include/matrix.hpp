/* Kayumov Airat st128100@student.spbu.ru
   This file contains declaration of Matrix class. All functions optimized using multithreading have their single-threaded versions preserved.
*/
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>

/**
 * @class Matrix
 * @brief Matrix class with needed methods
 * 
 * This class represents a matrix along with the methods
 * needed to convert it to a Gaussian matrix. This class doesn't contain methods
 * that change the image data.
 */

class Matrix
{
private:
    std :: vector<std :: vector<float>> matrixContents; ///< 2D vector representating Matrix
    float sum; ///< Sum of values ​​in all cells required for matrix normalization
public:
    /// @brief Matrix constructor
    Matrix(short radius);
    /// @brief Fills the matrix according to the Gauss formula
    void fillGaussianMatrix(float sigma);
    /** @brief Multi threads implementation of fillGaussianMatrix method
    *
    * Multi threads implementation of fillGaussianMatrix method
    * uses all available threads. Multithreading is implemented in the form of a vector of 
    * threads containing lambda functions, working on a precalculated
    * number of rows (the last thread takes all the remaining rows).
    **/
    void fillGaussianMatrixWThreads(float sigma);
    /// @brief Matrix normalization
    void normalize();
    /// @brief Getter for matrixContents field.
    std :: vector<std :: vector<float>> getContents();
};
    
#endif
