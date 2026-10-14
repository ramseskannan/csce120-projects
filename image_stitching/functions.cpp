#include <cmath>
#include <iostream>
#include <vector>
#include <limits>
#include "functions.h"


double error_calculation(const Image& image1,
                         const Corner& image1_corner,
                         const Image& image2,
                         const Corner& image2_corner) {
    // TODO(student): Complete error calculation function.
    //images should be non-empty so we check and return infinity to indicate invalid comparison
    if (image1.empty() || image1[0].empty() || image2.empty() || image2[0].empty()){
        return std::numeric_limits<double>::infinity();
    }

    //aquring the dimensions for both image 1 and 2. width is columns, height is rows
    size_t img1_w = image1.size();
    size_t img1_h = image1[0].size();
    size_t img2_w = image2.size();
    size_t img2_h = image2[0].size();

    //caluclaring the radius
    int radius = ERROR_NEIGHBORHOOD_SIZE / 2;

    //what is the total error
    double total_e = 0.0;

    //we checl a;; the pixel sin a square patch arodun the cornor point. 
    //interate through the neighboorhood offsets
    //dy is vertical and dx is horizontal
    for (int dy = -radius; dy<= radius; dy++){

        for(int dx = -radius; dx <= radius; dx++){

            //caculating the integer coords of the corresponding pixel
            int x1= (int)image1_corner.x + dx;
            int y1= (int)image1_corner.y + dy;
            int x2= (int)image2_corner.x + dx;
            int y2= (int)image2_corner.y + dy;

            //now we check if the pixel of image 1 and 2 is out of bounds
            if(x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0 || x1 >= static_cast<int>(img1_w) ||
            y1 >= static_cast<int>(img1_h) || x2 >= static_cast<int>(img2_w) || y2 >= static_cast<int>(img2_h)){
                return std::numeric_limits<double>::infinity();
            }

            //getting pizels at the corresponging positions
            Pixel p_1 = image1[x1][y1];
            Pixel p_2 = image2[x2][y2];

            //now we caluclate the color differences
            int d_red = static_cast<int>(p_1.red) - static_cast<int>(p_2.red); //for red
            int d_green = static_cast<int>(p_1.green) - static_cast<int>(p_2.green); //for green
            int d_blue = static_cast<int>(p_1.blue) - static_cast<int>(p_2.blue); //for blue

            //this gives us a measure of hwo different the two patches are
            total_e += static_cast<double>(d_red * d_red + d_green * d_green + d_blue * d_blue); //now this adds squared diferens to total error
        }
    }
    //this returns the total error as a double
    return total_e;
}
std::vector<CornerPair> match_corners(const Image& image1,
                                      const std::vector<Corner>& image1_corners,
                                      const Image& image2,
                                      const std::vector<Corner>& image2_corners) {

    // TODO(student): Complete key points matching algorithm
    //intialize the result vector (thats what we are supposed to return)
    std::vector<CornerPair> result;

    //get the number of corners for each image
    size_t n_1 = image1_corners.size();
    size_t n_2 = image2_corners.size();
    
    //this exits early if the image has no cornors to match
    if (n_1 == 0 || n_2 == 0){
        return result;
    }
    //nthis is infinity
    const double INF = std::numeric_limits<double>::infinity();

    //image dimensions
    size_t img1_w = image1.size();
    size_t img2_w = image2.size();
    //array to store errors 1D
    std::vector<double> errors(n_1 * n_2, INF);
    for (size_t row = 0; row < n_1; row++){
        const Corner& c1 = image1_corners[row];
        //H1 only considering the cornors in the right half of image 1, this assumes image2 overlaps with the right side of image1
        if (c1.x < img1_w / 2.0){
                continue;
            }
        for(size_t col = 0; col < n_2; col++){
            const Corner& c2 = image2_corners[col];
            //h2: only consider cornors in the left half of image2
            //this complements H1 
            if (c2.x > img2_w / 2.0){
                continue;
            }
            //h3, only match cornors with similar y coords
            if (std::abs((double)c1.y - (double)c2.y) > 100.0){
                continue;
            }
            errors[row * n_2 + col] = error_calculation(image1, c1, image2, c2);
            }
    }

    //this is the greedy matching alg
    //it finds the best unmatched pair repeatedly
    while (true){
        double best_error = INF;
        size_t best_row = 0;
        size_t best_col = 0;

        //scanning for the unmatched pair
        for (size_t row = 0; row < n_1; row++){
            for(size_t col = 0; col < n_2; col++){
                if (errors[row * n_2 + col] < best_error){
                    best_error = errors[row * n_2 + col];
                    best_row = row;
                    best_col = col;
                }
            }
        }
        //this stops if no valid pair found
        if (!std::isfinite(best_error)) break;
            //we have to track the matches so lets match it
            CornerPair pair;
            pair.image1_corner = image1_corners[best_row];
            pair.image2_corner = image2_corners[best_col];
            pair.error = best_error;
            result.push_back(pair);
            //npw we invalidate this row and column to move to the next
            for (size_t col = 0; col < n_2; col++){
                errors[best_row * n_2 + col] = INF;
            }
            //set all errors in this column to infinity
            for (size_t row = 0; row < n_1; row++){
                errors[row * n_2 + best_col] = INF;
            }
        }
        //return the matched pairs
        return result;
    }
   
void map_coordinates(const Matrix& H,
                     size_t x,
                     size_t y,
                     double& mapped_x,
                     double& mapped_y) {
    // TODO(student): Complete map function with homography

    //vaildating H if its at least 3x3
    if (H.size()< 3 || H[0].size() < 3 || H[1].size() < 3 || H[2].size() < 3){
        mapped_x = std::numeric_limits<double>::infinity();
        mapped_y = std::numeric_limits<double>::infinity();
        return;
    }
    //converting input coords to doubles
    double X = static_cast<double>(x);
    double Y = static_cast<double>(y);

    //computing homogenous corrdinates u, v, w
    double u = H[0][0] * X + H[0][1] * Y + H[0][2];
    double v = H[1][0] * X + H[1][1] * Y + H[1][2]; 
    double w = H[2][0] * X + H[2][1] * Y + H[2][2];
    
    //check if w is very close to 0
    const double EPS = 1e-12;
    if (std::abs(w) < EPS){
        //invalid transformation, we return infinity
        mapped_x = std::numeric_limits<double>::infinity();
        mapped_y = std::numeric_limits<double>::infinity();
        return;
    }
    //converting from homogenous to cartesian coords
    //divide by w to get the final mapped coords
    mapped_x = u/w;
    mapped_y = v/w;

}

Image merge_images(const Image& image1,
                   const Image& image2,
                   const std::vector<std::vector<double>>& H) {
    // TODO(student): Complete merge function.
    //if image 1 is empty, we return empty result

    //1. new buffer for merge image: 1.75 x width of image 1, 1.5 x height of image 1
    if (image1.empty() || image1[0].empty()){
        return {};
    }
    //get the dimensions of both images
    size_t img1_w = image1.size();
    size_t img1_h = image1[0].size();
    size_t img2_w = image2.size();
    size_t img2_h = image2[0].size();

    //1.75x width and 1.5x height to accodomate tranformed iamge2
    size_t out_w = static_cast<size_t>(floor(1.75 * img1_w));
    size_t out_h = static_cast<size_t>(floor(1.5 * img1_h));

    //intialize the output canvas with black pixel
    Image output;
    output.resize(out_w);
    for (size_t x = 0; x < out_w; x++){
        output[x].resize(out_h);
        for (size_t y = 0; y < out_h; y++){
            //sets all channels to 0
            output[x][y].red = 0;
            output[x][y].green = 0;
            output[x][y].blue = 0;

        }
    }

    //copying image 1 into top left corner of the canvas, this preserves image1 in its original position
    for (size_t x = 0; x < img1_w && x < out_w; x++){
        for (size_t y = 0; y < img1_h && y < out_h; y++){
            output[x][y] = image1[x][y];
        }
    }
    //now we check if iamge 2 is empty or H invalid, we return the canvas with just iamge1
    if (image2.empty() || image2[0].empty() || H.size() < 3 || H[0].size() < 3){
        return output;

    }

    //for each of thepixels in the output canvas, map into iamge2 anf sample

    for (size_t x = 0; x < out_w; x++){
        for(size_t y = 0; y < out_h; y++){
            double mx = 0.0;
            double my = 0.0;

            map_coordinates(H, x, y, mx, my);

            //if the mapping is invalid, skip sampling ijamge 2
            if (!std::isfinite(mx) || !std::isfinite(my)) {
                continue;
            }
            //check if mapped coordinate lies inside iamge2 bounds
            if (mx < 0.0 || my < 0.0 || mx >= static_cast<double>(img2_w) || my >= static_cast<double>(img2_h)){
                continue;
            }
            //sample image 2 at mx my using bicubic interpolation (like how we did for image scalign)
            Pixel p2 = bicubic_interpolation(image2, mx, my);

            //now determine wheter iamge1 contributes at this canvas pixel 
            bool has_img1 = (x < img1_w && y < img1_h);

            if (has_img1){
                //average the two pixels per chanel this is simple blending
                const Pixel& p1 = output[x][y];
                int r = static_cast<int>(p1.red) + static_cast<int>(p2.red);
                int g = static_cast<int>(p1.green) + static_cast<int>(p2.green);
                int b = static_cast<int>(p1.blue) + static_cast<int>(p2.blue);

                //average the clamp to [0, 255]
                Pixel out_p;
                out_p.red = static_cast<uint8_t>((r) / 2);
                out_p.green = static_cast<uint8_t>((g) / 2);
                out_p.blue = static_cast<uint8_t>((b) / 2);

                output[x][y] = out_p;
            } else {
                //only image 2 contributes
                output[x][y] = p2;
            }
            
        }
    }
    return output;
}
