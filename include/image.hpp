/* Kayumov Airat st128100@student.spbu.ru
   This file contains declaration of BMP_HEADER and DIB_HEADER structures and Image class. Both redacted and clean image data are contained inside Image object to reduce the number of calculations. All functions optimized using multithreading have their single-threaded versions preserved.
*/
#include <string>
#include "matrix.hpp"
#include <filesystem>


#ifndef BMP_HPP
#define BMP_HPP

#pragma pack(push,  1)


/**
 * @struct BMP_HEADER
 * @brief Structure that represents BMP header
 */
struct BMP_HEADER
{
    unsigned short header_field;
    unsigned bmp_size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned pixel_data_address;
};

/**
 * @struct DIB_HEADER
 * @brief Structure that represents DIB header
 */
struct DIB_HEADER
{
    unsigned dib_size;
    int width;
    int height;
    unsigned short color_planes;
    unsigned short bits_per_pixel;
    unsigned compression_method;
    unsigned image_size;
    int x_pixel_per_metre;
    int y_pixel_per_metre;
    unsigned colors_amount;
    unsigned important_colors_amount;
};
#pragma pack(pop)



/**
 * @class Image
 * @brief Class that represents BMP Image with needed methods
 * 
 * This class represents BMP Image with both headers and pixel data. Pixel data 
 * is stored in two vectors (edited and unedited) to remove the need to read an image each time.
 * This class contains all methods that change the image data.
 */
class Image
{
private:
    BMP_HEADER bmpHeader; ///< BMP header of the image
    DIB_HEADER dibHeader; ///< DIB header of the image
    std::vector<unsigned char> colorPalette; ///< Color palette of BMP image (needed for 8bit)
    std :: vector<unsigned char> originalPixels; ///< Vector with unedited pixels data.
    std::vector<unsigned char> pixels; ///< Vector with edited pixels data (write method uses only this vector)
public:
    /// @brief Image constructor
    Image(); 
    /**
    * @brief Method that reads an selected image and writes its contents to a Image class object
    * 
    * Method that reads an selected image and writes its contents to a Image class object.
    * The method supports reading files with sizes not multiples of 4 and uses padding with zeros.
    */
    void read(std :: string fileName);
    /**
    * @brief Method that writes image data from Image class object into selected file.
    * 
    * Method that writes image data from Image class object into selected file.
    * The method supports writing files with sizes not multiples of 4 and uses padding with zeros.
    */
    void write(std :: string fileName);
    /// @brief Method used to rotate captured image by 90 degrees left
    void rotateLeft();
    /** @brief Multi thread implementation of rotateLeft method
    *
    * Multi thread implementation of rotateLeft method. This method
    * uses all available threads. Multithreading is implemented in the form of a vector of 
    * threads containing lambda functions, working on a precalculated
    * number of rows (the last thread takes all the remaining rows).
    **/
    void rotateLeftWThreads();
    /// @brief Method used to rotate captured image by 90 degrees right
    void rotateRight();
    /** @brief Multi thread implementation of rotateRight method
    *
    * Multi thread implementation of rotateRight method. This method
    * uses all available threads. Multithreading is implemented in the form of a vector of 
    * threads containing lambda functions, working on a precalculated
    * number of rows (the last thread takes all the remaining rows).
    **/
    void rotateRightWThreads();
    /// @brief Method used to apply gaussian filter to captured image using gaussian matrix passed in an argument
    void applyGaussianFilter(std :: vector<std :: vector<float>> matrix);
    /** @brief Multi threads implementation of applyGaussianFilter method
    *
    * Multi threads implementation of applyGaussianFilter method
    * uses all available threads. Multithreading is implemented in the form of a vector of 
    * threads containing lambda functions, working on a precalculated
    * number of rows (the last thread takes all the remaining rows).
    **/
    void applyGaussianFilterWThreads(std :: vector<std :: vector<float>> matrix);
};


#endif
