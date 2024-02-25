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


std::vector <int > accumulate(std:: vector <int > arr) /*cumulative curve*/
{
    std::vector <int > acc_arr;
    acc_arr.push_back(arr[0]);
    for (int i = 1; i < arr.size(); i++)
    {
        acc_arr.push_back(arr[i]+ acc_arr[i-1]);
    }
    return acc_arr;
}



Mat Greyscale(Mat& img) 
{



    if (img.empty())
    {   
        Mat img2; 
        img2 = Mat(200,200, CV_8UC1,1);
        return img2;
    }
  

    if (img.channels() == 3)/*if image is in gbr*/ {

        Mat img2;
        img2 = Mat(img.rows, img.cols, CV_8UC1, 255);
        for (int i = 0; i < img.rows; i++)
        {
            for (int j = 1; j < img.cols; j++)
            {
                Vec3b bgr = img.at< Vec3b>(i, j);

                img2.at< uchar>(i, j) = {
                   (unsigned char) ((bgr[0] + bgr[1] + bgr[2]) / 3)
                };


            }

        }
        return img2;
       
    }


    else {
        return img;


    }

   

}


float Normalised_Cross_Correlation(const std::vector<double>& desc_image1, const std::vector<double>& desc_image2)
{   

    float sum1 = 0;
    float sqsum1 = 0;
    float sqsum2 = 0;
    float Fm;
    float Sm;
    int size = desc_image1.size();


    if (desc_image1.size() != desc_image2.size()) {
        //      Return -1 to indicate error (features have different sizes)
        return -1;
    }


    Fm = accumulate(desc_image1.begin(), desc_image1.end(), 0.0) / size;
    Sm = accumulate(desc_image2.begin(), desc_image2.end(), 0.0) / size;


  
    for (int i = 0; i <size; i++) {


        sum1 += ((desc_image1[i] - Fm) * (desc_image2[i] - Sm));
        sqsum1 += pow((desc_image1[i] - Fm), 2);
        sqsum2 += pow((desc_image2[i] - Sm), 2);
    }

    float result = (sum1 / (sqrt(sqsum1 * sqsum2)));

    return result;

}




void template_match(cv::Mat img, cv::Mat target)
{

    if (img.rows < target.rows || img.cols < target.cols) {
        return;
    }

    Mat out= img.clone();
    float threshold = 0.8;

    img = Greyscale(img); // original image
    target = Greyscale(target); // target image to be found in orignial image


    std::vector <std::vector <float >>  res;
    std::vector <float > row(img.cols, 0);
    res.resize(img.rows, row);

    int tar_height = target.rows;
    int tar_width = target.cols;


    for (int y = 0; y < img.rows - tar_height; y++)
    {
        for (int x = 0; x < img.cols- tar_width; x++)
        {   
            // crop part of original image (region of interest) and compare it to target image
            Mat temp = img.clone();
            Rect myROI(x, y,  tar_width, tar_height);
            Mat roi = temp(myROI);

            res[y][x] = Normalised_Cross_Correlation(roi, target); // find NCC for the cropped part (region of interest)




        }
    }

    vector<vector<int>> areas;

    for (int i = 0; i < res.size(); i++) {

        for (int j = 0; j < res[0].size(); j++) {

            if (res[i][j] > threshold) { // find indices where res value (> threshld ), this threshold can increase or decrease!
                areas.push_back({ i,j });// push these indices in a vector
            }
        }
    }
       

        // draw rectangles at indices found.
        for (int i = 0; i < areas.size(); i++)
        {

            Point top_left, bottom_right;
            top_left.x = areas[i][1];
            top_left.y = areas[i][0];
            bottom_right.x = top_left.x + tar_width;
            bottom_right.y = top_left.y + tar_height;
            rectangle(out, top_left, bottom_right, Scalar(0, 0, 255), 2);
       
        }

        imshow("out", out);

};








   int main()
    {
        std::string image1_path = "mario.png";
        std::string image2_path = "mariocoini.png";

        Mat img1 = imread(image1_path, IMREAD_COLOR);
        Mat img2 = imread(image2_path, IMREAD_COLOR);

        template_match(img1, img2);

        waitKey();
        return 0;
   

}










