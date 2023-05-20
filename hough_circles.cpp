
Mat hough_circle(cv::Mat _img,int rmin,int rmax,int bin_threshold)
{
    Mat img;
    Canny(_img, img, 100, 200);

    int height = img.rows;
    int width = img.cols;
 
    vector<vector<int>>circle_candidates;
    map<vector<int>, int> accumulator;
    map<vector<int>, int>::iterator itr;


    for (int r = rmin; r < rmax; r++)
    {
        for (int t = 0; t < 360; t += 5) 
        {        
            circle_candidates.push_back({ r,(int)(r * cos(t*DEG2RAD )),(int)(r * sin(t * DEG2RAD)) });
        }
    }    
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (img.at<uchar>(y, x) != 0) {
    
                    for (int i = 0; i < circle_candidates.size(); i++)
                    {
                        int x_center = x + circle_candidates[i][1];
                        int y_center = y + circle_candidates[i][2];
                        int radius=circle_candidates[i][0] ;
                        accumulator[{x_center, y_center, radius}] += 1;
                    }
                }
            }
        }
         
            Mat output_img = _img.clone();
            vector<vector<int>>out_circles;
    
            for (itr = accumulator.begin(); itr != accumulator.end(); ++itr)

            { 
                vector<int> candidate_circle = itr->first;
               int x = candidate_circle[0];
               int y= candidate_circle[1];
               int r = candidate_circle[2];
               int current_vote_percentage =  (itr->second) ; 
            
               if (current_vote_percentage >= bin_threshold && y>0 && y<height && x>0 && x<width) {

                   out_circles.push_back({ x,y,r,current_vote_percentage });
    
               }    
            }
           for (int i = 0; i < out_circles.size(); i++)
            {  
                Point center;
                center.x = out_circles[i][0];
                center.y = out_circles[i][1];
                circle(output_img, center, out_circles[i][2], Scalar(255, 0,0), 1, LINE_AA);
            }
    
    
    
           return output_img;
    
}






    int main()
    {
        std::string image_path = "C:/Users/Hager/Downloads/Test_images/coins.png";
       Mat img = imread(image_path, IMREAD_COLOR);
      
       if (img.empty()) 
        {
            std::cout << "Could not read the image: " << image_path << std::endl;
            return 1;
        }
       
      // defining minimum and maximum circles radii to search for,
      //threshold indicates minimum accumulator votes, A higher threshold will result in fewer false positives but may also miss some valid circles.
       int rmin = 20;     
       int rmax = 40;
       int threshold = 60;
       Mat deteced_circles = hough_circle(img,rmin,rmax,threshold);
       imshow("deteced_circles", deteced_circles);

       
 

       waitKey();

       return 0;
   

}
