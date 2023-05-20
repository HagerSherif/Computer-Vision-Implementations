
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



int main()
    {
        std::string image_path = "C:/Users/Hager/Downloads/Test_images/young.jpg";
       Mat img = imread(image_path, IMREAD_COLOR);
      
       img = Greyscale(img);

        if (img.empty()) 
        {
            std::cout << "Could not read the image: " << image_path << std::endl;
            return 1;
        }
        
        imshow ("Greyscale",img);

          waitKey();

          return 0;
   

}
