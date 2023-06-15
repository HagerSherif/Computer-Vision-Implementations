#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <opencv2/features2d/features2d.hpp>
#include <numeric>



using namespace cv;
using namespace std;



std::vector <std::vector <int >> calculateHist(Mat& img)   /*loops on pixels and count number of each value from 0 to 250 */

{
    std::vector <std::vector <int > > hist;
    if (img.channels() == 3)/*if image is in gbr*/ {
       
        std::vector <int > row(256, 0);
        hist.resize(3, row);
        for (int i = 0; i < img.rows; i++) {

            for (int j = 0; j < img.cols; j++)
            {   
                Vec3b bgr = img.at< Vec3b>(i, j);
                hist[0][(int)bgr[0]] += 1;
                hist[1][(int)bgr[1]] += 1;
                hist[2][(int)bgr[2]] += 1;

            }
        }

    }
    else {
        std::vector <int > row(256, 0);
        hist.resize(1, row);
        for (int i = 0; i < img.rows; i++) {

            for (int j = 0; j < img.cols; j++)
            {
                hist[0][(int)img.at<uchar>(i, j)] += 1;

            }
        }
    }

    return hist;

}





std::vector <float > Equalize(std::vector <int > hist ,int numOfPixels) {   
    std::vector <float > new_hist;
    /// Find probability mass function of histogram
    for (int i = 0; i < hist.size(); i++)
    {
        float num = (float)hist[i] / (float)numOfPixels;
        new_hist.push_back( num);
    }
    /// Find cumulative distribution function 
    for (int i = 1; i < new_hist.size(); i++)
    {
        float temp = new_hist[i];
        new_hist[i] = (new_hist[i - 1] + new_hist[i]);
    }
    /// Multiply cumulative distribution function by maximmum intensity value
    for (int i = 1; i < new_hist.size(); i++)
    {
        new_hist[i] = (floor(255 * new_hist[i]));
    }

  return new_hist;  /// maps input pixels to output pixels
}







void ImageEqualization(Mat& img, Mat& dst)
{    
    if (img.empty())
    {
        dst = Mat(200, 200, CV_8UC1, 1);
       
    }

    int numOfPixels = img.rows * img.cols;
    std::vector <std::vector <int > > hist = calculateHist(img);

    if (img.channels() == 3)/*if image is in gbr*/ {

        dst = Mat(img.rows, img.cols, CV_8UC3);
        std::vector <float > blueMap = Equalize(hist[0], numOfPixels); // return mapped values
        std::vector <float > greenMap = Equalize(hist[1], numOfPixels);
        std::vector <float >  redMap = Equalize(hist[2], numOfPixels);


        for (int i = 0; i < img.rows; i++)
        {
            for (int j = 0; j < img.cols; j++)
            {
                Vec3b bgr = img.at< Vec3b>(i, j);

                dst.at< Vec3b>(i, j) = {
                    (unsigned char)blueMap[bgr[0]],
                     (unsigned char)greenMap[bgr[1]],
                     (unsigned char)redMap[bgr[2]]

                };
            }
        }
    }

    else /*else image is in greyscale*/ {

        dst = Mat(img.rows, img.cols, CV_8UC1);
        std::vector <float >  greyMap = Equalize(hist[0], numOfPixels);


        for (int i = 0; i < img.rows; i++)
        {
            for (int j = 0; j < img.cols; j++)
            {
                uchar bgr = img.at< uchar>(i, j);
                dst.at< uchar>(i, j) = {
                    (unsigned char) greyMap[bgr],
                };

            }
        }
    }  
}



  int main()
    {
       Mat img = imread("example.jpg", IMREAD_COLOR);
      
        if (img.empty()) 
        {
            std::cout << "Could not read the image: " << image_path << std::endl;
            return 1;
        }
    


   
        Mat dst;
        ImageEqualization(img,dst);
        imshow("equalized", dst);
    
        waitKey();
        return 0;
   

}
