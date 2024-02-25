

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
