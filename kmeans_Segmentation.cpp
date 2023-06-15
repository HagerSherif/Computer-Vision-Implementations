

double euclidean(const std::vector<int> p1, const std::vector<int> p2) {
    double sum = 0.0;
    for (int i = 0; i < p1.size(); ++i) {
        sum += pow(p1[i] - p2[i], 2.0);
    }
    return sqrt(sum);
}


void KMeans(Mat& img, vector<vector<int>>& centroids, vector<int>& labels, int n_clusters = 2, int max_iter = 8) {

    vector<vector<int>> X_train((img.rows * img.cols));
    int k = 0;
    
    for (int i = 0; i < img.rows; ++i) {
        for (int j = 0; j < img.cols; ++j) {

            if (img.channels() == 3) {
                X_train[k] = { (int)(img.at<Vec3b>(i, j)[0]),(int)(img.at<Vec3b>(i, j)[1]),(int)(img.at<Vec3b>(i, j)[2]) };
            }
            else {
                X_train[k] = { (int)(img.at<uchar>(i, j)) };
            }
            k += 1;
        }
    }
    
    // Initialize centroids randomly
    srand(time(nullptr));
    centroids = { {X_train[std::rand() % X_train.size()]} };
   
    while (centroids.size() < n_clusters) {
        // Calculate distances from points to the centroids
        vector<double> dists(X_train.size());
        for (int i = 0; i < X_train.size(); ++i) {
            double min_dist = std::numeric_limits<double>::max(); // initialize min_distance with maximum number available
            for (int j = 0; j < centroids.size(); ++j) {
                double dist = euclidean(X_train[i], centroids[j]);
                if (dist < min_dist) {
                    min_dist = dist;
                }
            }
            dists[i] = min_dist;
        }
        // Normalize distances to create a probability distribution
        double sum_dists = std::accumulate(dists.begin(), dists.end(), 0.0);
        transform(dists.begin(), dists.end(), dists.begin(), [=](double d) { return d / sum_dists; });
        // Select new centroid based on probability distribution
        double rand_num = std::rand() / static_cast<double>(RAND_MAX);
        double cum_prob = 0.0;
        int new_centroid_idx = -1;

        for (int i = 0; i < X_train.size(); ++i) {
            cum_prob += dists[i];
            if (cum_prob > rand_num) {
                new_centroid_idx = i;
                break;
            }
        }
        centroids.push_back(X_train[new_centroid_idx]);
    }

    // start converging the initial random centroids
    int iteration = 0;
    vector<vector<int>> prev_centroids;
    vector<double> dists(n_clusters);

    while ((prev_centroids != centroids) && (iteration < max_iter)) {

        vector<vector<vector<int>>> sorted_points(n_clusters);

        for (const auto& x : X_train) {
            for (int i = 0; i < n_clusters; ++i) {
                dists[i] = euclidean(x, centroids[i]); // finds squared distance between datapoint and each centroid
            }
            int centroid_idx = distance(dists.begin(), std::min_element(dists.begin(), dists.end()));  // find centroid index that had smallest distance with datapoint
            sorted_points[centroid_idx].push_back(x);  // cluster data in the centroid_idx found
        }
        prev_centroids = centroids;

        
        // update centroids after clustering data,for each cluster find mean of blue , green , red.
        for (int i = 0; i < n_clusters; ++i) {
            if (!sorted_points[i].empty()) {
                for (int k = 0; k < sorted_points[i][0].size(); k++)
                {
                    double total = 0;
                    for (int j = 0; j < sorted_points[i].size(); j++)
                    {
                        total += sorted_points[i][j][k];
                    }
                    centroids[i][k] = ((total) / (sorted_points[i].size()));
                }
            }
        }
        ++iteration;
 
    } 


    //final step assigning labels for each pixel according to their final cluster
    for (int j = 0; j < X_train.size(); ++j) {
        for (int i = 0; i < n_clusters; ++i) {
            dists[i] = euclidean(X_train[j], centroids[i]);
        }
        int centroid_idx = distance(dists.begin(), std::min_element(dists.begin(), dists.end()));
        labels[j] = centroid_idx;

    }


}


Mat segment(Mat& img, vector<vector<int>>& centroids, vector<int>& labels) {

    Mat segmented_img = img;
    int k = 0;
    for (int i = 0; i < segmented_img.rows; ++i) {
        for (int j = 0; j < segmented_img.cols; ++j) {
            if (img.channels() == 3)/*if image is in gbr*/ {
                (segmented_img.at<Vec3b>(i, j)[0]) = (unsigned char)(centroids[labels[k]][0]);
                (segmented_img.at<Vec3b>(i, j)[1]) = (unsigned char)(centroids[labels[k]][1]);
                (segmented_img.at<Vec3b>(i, j)[2]) = (unsigned char)(centroids[labels[k]][2]);
            }
            else {
                (segmented_img.at<uchar>(i, j)) = (unsigned char)(centroids[labels[k]][0]);
            }


            k += 1;
        }
    }
    return segmented_img = img;

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

    vector<int> labels(img.rows * img.cols);
    int n_clusters=14;
    vector<vector<int>> centroids (n_clusters);

    KMeans(img, centroids, labels, n_clusters = n_clusters);
    Mat segmented_img = segment(img, centroids, labels);
    imshow("kmeans", segmented_img);

    waitKey();
    return 0;
   
}











