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


  std::vector <std::vector <int >> calculateHist(Mat& img)

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




std::vector <int > normalizeHistogram(std::vector <int > arr,int height) /*normalize histogram values to fit in the plot image */ {
    auto max_value = *max_element(arr.begin(), arr.end());
    auto min_value = *min_element(arr.begin(), arr.end());
    std::vector <int > normalized_arr;
    for (int i = 0; i < arr.size(); i++)
    {
        normalized_arr.push_back(((arr[i] - min_value) * height / (max_value - min_value)));
    }
    
    return normalized_arr;


}



/// plotting histogram
Mat drawGreyHist(std::vector <int > hist) {
    int binSize = 2;
    int  rows = 500;
    int cols = hist.size() * binSize;

    Mat3b plot = Mat3b(rows, cols, Vec3b(1, 1, 1));
    std::vector <int > histnorm = normalizeHistogram(hist, rows);

    for (int i = 1; i < hist.size(); ++i)
    {
       
        int h = rows - histnorm[i];
        //rectangle(plot, Point(i * binSize, h), Point((i + 1) * binSize - 1, rows), (i % 2) ? Scalar(250, 0, 0) : Scalar(200, 0, 0), FILLED);
        line(plot, Point(binSize * (i - 1), rows - histnorm[i - 1]),
            Point(binSize * (i), rows - histnorm[i]),
            Scalar(255, 0, 0), 2, 8, 0);


    }
    return plot;

}

Mat drawGBRHist(std::vector <int > blue_hist, std::vector <int > green_hist ,std::vector <int > red_hist) {

    int binSize = 2;
    int  rows = 500; 
    int cols = blue_hist.size() * binSize;
    Mat3b plot = Mat3b(rows, cols, Vec3b(1, 1, 1));
    std::vector <int > blue=normalizeHistogram(blue_hist,rows);
    std::vector <int > green = normalizeHistogram(green_hist, rows);
    std::vector <int > red = normalizeHistogram(red_hist, rows);


    for (int i = 1; i < blue_hist.size(); i++)
    {
     
        line(plot, Point(binSize * (i - 1), rows - blue[i-1]),
            Point(binSize * (i), rows - blue[i]),
            Scalar(255, 0, 0), 2, 8, 0);
        line(plot, Point(binSize * (i - 1), rows - green[i-1]),
            Point(binSize * (i), rows - green[i]),
            Scalar(0, 255, 0), 2, 8, 0);
        line(plot, Point(binSize * (i - 1), rows - red[i-1]),
            Point(binSize * (i), rows - red[i]),
            Scalar(0, 0, 255), 2, 8, 0);
    }
    return plot;
}
  
  
  
 
  int main()
    {
        std::string image_path = "C:/Users/Hager/Downloads/Test_images/images.jpeg";
       Mat img = imread(image_path, IMREAD_COLOR);
      
      if (img.empty()) 
        {
            std::cout << "Could not read the image: " << image_path << std::endl;
            return 1;
        }
        
       Mat histogram;
       Mat cumulative_histogram;
       std::vector <std::vector <int > > hist = calculateHist(img);

       if (img.channels() == 3)/*if image is in gbr*/ {



           std::vector <int > acc_blue_hist = accumulate(hist[0]);
           std::vector <int > acc_green_hist = accumulate(hist[1]);
           std::vector <int > acc_red_hist = accumulate(hist[2]);
           histogram = drawGBRHist(hist[0], hist[1], hist[2]);
           cumulative_histogram = drawGBRHist(acc_blue_hist, acc_green_hist, acc_red_hist);
       }


       else  {

           std::vector <int > acc_grey_hist = accumulate(hist[0]);
           histogram = drawGreyHist(hist[0]);
           cumulative_histogram = drawGreyHist(acc_grey_hist);



       }

       imshow("histogram", histogram); 
       imshow("cumulative histogram", cumulative_histogram);
      
        
    


          waitKey();

            return 0;
   

}
