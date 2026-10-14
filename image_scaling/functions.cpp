#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <string>
#include "functions.h"

Image load_image(const std::string& fname) {
    // TODO(student): implement image loading
    //PPM files store pizels row- by row, however we hav eto store them in column major order
    //so that means we read row by row but store as foto[column][row]
    //checking if the filename is empty
    if(fname.empty()){
        throw std::runtime_error("Invalid filename");
    }

    //this opens the file for reading in
    std::ifstream file(fname);

    //checking to see if file cannot be opened
    if (!file.is_open()){
        throw std::runtime_error("Failed to open " + fname); //what were supposed to output for this error
    }

    //checking to see if the file type is missing

    std::string type;
    if(!(file >> type)) {
        throw std::runtime_error("Failed to read type"); //what were supposed to output for this error

    }

    //checking to see if the file tpy eis P3 or p3

    if(type != "P3" && type != "p3"){
        throw std::runtime_error("Invalid type " +type);
    }


    /*ensuring that both dimensions should be positive integers that are 
    less than or equal to the maxs that we checked in the other .cpp file. 
    we have to throw a runtime error if either dimension is missing or invalid

    */
    size_t width, height;
    if (!(file >> width >> height)){
        throw std::runtime_error("Invalid dimensions");
    }

    //now this checks if they are within that range we stated above
    if (width <= 0 || height <= 0 || width > MAX_WIDTH || height > MAX_HEIGHT){
        throw std::runtime_error("Invalid dimensions");
    }

    //now we are reading the max color value
    
    //if the max color value is missing or less than 1 or greater than 255
    //first we must read the max color value
    int max_color_value;
    if(!(file >> max_color_value)){
        throw std::runtime_error("Invalid max color");
    }
    //now we check if its between the range
    if(max_color_value < 1 || max_color_value > 255){
        throw std::runtime_error("Invalid max color");
    }

    //next each pixel should be 3 (red, green, and blue) non-negative integers 
    //less than the max color value. if there is an invalid pixel value
    //throw runtime errror

    //using a 2d vector because an image is a vector of vectors
    //represents the pixles
    Image foto(width, std::vector<Pixel>(height));  //using width and hiegh colums and rows

    //initialzing the colors
    int r;
    int g;
    int b;

    for (size_t rows = 0; rows < height; rows++ ){ //interating through rows

        for(size_t columns = 0; columns < width; columns++){ //interating through colums

            //reading the red val
            if(!(file >> r)){
                throw std::runtime_error("Not enough values"); //throwing error if not enough vals
            }
            //checking red val
            if(r < 0 || r > max_color_value){
                throw std::runtime_error("Invalid color value");
            
            }
            //reading green val
            if(!(file >> g)){
                throw std::runtime_error("Not enough values"); //throwing error if not enough vals
            }
            //checking green val
            if(g < 0 || g > max_color_value){ //comparing it to the range
                throw std::runtime_error("Invalid color value"); //throws error
            }
            //read blue 
            if(!(file >> b)){
                throw std::runtime_error("Not enough values"); //throwing error if not enough vals
            }
            //checking red val
            if(b < 0 || b > max_color_value){
                throw std::runtime_error("Invalid color value");
            }

            //storing the values in the 2d vector if it passed all tests
            foto[columns][rows].red = static_cast<uint8_t>(r);
            foto[columns][rows].green = static_cast<uint8_t>(g);
            foto[columns][rows].blue = static_cast<uint8_t>(b);
        
        }
    }

    //check if there are extra pixel values 
    int value_check;
    if (file >> value_check) {
        throw std::runtime_error("Too many values"); 
    }

    //return the loaded image

   return foto;
}

void output_image(const std::string& filename,
                  const Image& image) {
    if (filename.empty()) {

        //check if the filname is empty
        throw std::invalid_argument("Invalid filename");
    }
    
    if (image.empty() || image[0].empty()) {
        //checking if the iamge is empty
        throw std::invalid_argument("Invalid image");
    }

    //now we open the file for writing
    std::ofstream output_file(filename);
    //now chekcking if it is opened correctly
    if (!output_file.is_open()) {
        throw std::invalid_argument("Failed to open " + filename);
    }
    //get width of the image, making it the number of columns
    size_t width = image.size();
    //now getting the heigh of the image which translates into the number of rows
    size_t height = image[0].size();

    //now writing the file tpye: P3
    output_file << "P3\n";
    //the is writing the wdith and heigh to the file
    output_file << width << " " << height << "\n";
    //this is writing the max color value to the file
    output_file << "255\n";

    //now using the width and heigh 2d array we implement through rows and columns
    for (size_t rows = 0; rows < height; rows++){
        //looping through the colums
        for(size_t columns = 0; columns < width; columns++ ){
            //writing the red green and blue value

            output_file << static_cast<int>(image[columns][rows].red) << " ";
            output_file << static_cast<int>(image[columns][rows].green) << " ";
            output_file << static_cast<int>(image[columns][rows].blue) << " ";

            //this is adding a space between the pixels
            if(columns < width - 1){
                output_file << " ";
            }
        }

        //this ends the row with a new lone, necessary for reading and writing file
        output_file << "\n";
    }
}

double map_coordinates(size_t source_dimension,
                       size_t target_dimension,
                       size_t pixel_coordinate) {
    // TODO(student): implement mapping function.

    //checking is the source dimension

    if (source_dimension <= 0) {
        throw std::invalid_argument("Invalid dimension");
    }

    //checking if the target dimension is valid
    if (target_dimension <= 1) {
        throw std::invalid_argument("Invalid dimension");
    }

    //check if the pixel coordinates is within the bounds given
    if (pixel_coordinate >= target_dimension) {
        throw std::invalid_argument("Invalid coordinate");
    }

    //we are supposed to return x or y coord of the location where the pixel maps in the source image
    //we have to use the mapping formula given

    return static_cast<double>(source_dimension - 1) / static_cast<double>(target_dimension - 1) * static_cast<double>(pixel_coordinate);

}

Pixel bicubic_interpolation(const Image& source_image,
                            double x,
                            double y) {
    //this using the 16 surrounding pixiels to estimate the color
    //we hace to get the 4 intermediate pizels and interpolate vertically using those pizels
    // TODO(student): Implement bicubic interpolation

    //first like every other function check if the image is empty
    if (source_image.empty() || source_image[0].empty()) {
        throw std::invalid_argument("Invalid image");
    }
    //retrieving the width of the image
    size_t width = source_image.size();
    //retrieving the heigh of the image
    size_t height = source_image[0].size();

    //check if the coords are within the bounds

    if(x < 0 || x >= width || y < 0 || y >= height){
        throw std::invalid_argument("Invalid coordinate");
    }

    //get the x and y coord
    int xint = static_cast<int>(std::floor(x));
    int yint = static_cast<int>(std::floor(y));

    //we have to get the fractional of each coordinate now, has to be double
    double x_final = x - xint;
    double y_final = y - yint;

    //array to hold 4 intermediate pixel 

    Pixel intermediate_pixels[4];

    //looping through the 4 rows looking at y
    for(int i = 0; i < 4; i++){

        int yr = yint - 1 + i;

        //keeping it within image bounds
        if (yr < 0) yr = 0;
        if (yr >= static_cast<int>(height)) yr = height - 1;

        //now for the row at the columns, x vals are looked at

        Pixel p1, p2, p3, p4;
        //first pixel: column x_0 -1
        int col = xint - 1;
        if (col < 0) col = 0;
        if (col >= static_cast<int>(width)) col = width - 1;
        p1 = source_image[col][yr];

        //second pizel
        col = xint;
        if (col < 0) col = 0;
        if (col >= static_cast<int>(width)) col = width - 1;
        p2 = source_image[col][yr];
        //third pixel
        col = xint + 1;
        if (col < 0) col = 0;
        if (col >= static_cast<int>(width)) col = width - 1;
        p3 = source_image[col][yr];

        col = xint + 2;
        if (col < 0) col = 0;
        if (col >= static_cast<int>(width)) col = width - 1;
        p4 = source_image[col][yr];

        //using the bicubic interpolation horizontally across the 4 pixels we did above
        //x_final is the fractional part telling us where between pixels we are (we saw this in the document)
        intermediate_pixels[i] = bicubic_pixel(x_final, p1, p2, p3, p4);
    }

    //now we do it vertically (that for loop we had above)

    Pixel result = bicubic_pixel(y_final, intermediate_pixels[0], intermediate_pixels[1], intermediate_pixels[2], intermediate_pixels[3]);

    //reutring the result of the final interpolated pizel we have created
    return result;
}

Image scale_image(const Image& source_image,
                  size_t target_width,
                  size_t target_height) {
    //basically for each pixel in the target image, map its position back the source inage
    //then we use the bicubic interpolation to estimate the color at that specific mapped position
    // TODO(student): add loops to calculate scaled images
    //checking if source image is empty

    if(source_image.empty() || source_image[0].empty()){
        throw std::invalid_argument("Invalid image");

    }

    //check if the target dimensiomn are valid!!!!!
    if (target_height <= 0 || target_width <= 0 || target_height > MAX_HEIGHT || target_width > MAX_WIDTH){
        throw std::invalid_argument("Invalid dimension");
    }   

    //getting the sourece image width and height
    size_t source_width = source_image.size();

    size_t source_height = source_image[0].size();
    //create an empty target image (what we are producing)
    Image result(target_width, std::vector<Pixel>(target_height));

    //looping through the columns and rows in the target image
    for (size_t columns = 0; columns < target_width; columns++){
        for (size_t rows = 0; rows < target_height; rows++){

            //map the target x and y coords to source image
            double source_x = map_coordinates(source_width, target_width, columns);
            double source_y = map_coordinates(source_height, target_height, rows);

            //now we interpoalte the pizel color and store it in the result vector
            result[columns][rows] = bicubic_interpolation(source_image, source_x, source_y);

        }

    }

    return result;
}
