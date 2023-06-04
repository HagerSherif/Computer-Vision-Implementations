
## Table of Contents

- [Introduction](#introduction)

- [Overview](#overview)
  - [Histogram plotting](#histogram-plotting)
  - [RGB to gray-scale](#RGB-to-gray-scale)
  - [Image Equalization](#Image-Equalization)
  - [Hough circles](#Hough-circles)
  - [Template matching](#Template-matching)
  - [Segmentation using KMeans clustering](#Segmentation-using-KMeans-clustering)

## Introduction
These are some of the algorithms from scratch for my computer vision course work. OpenCv is only used for reading and showing images.


## Overview

<details>
<summary>Histogram plotting</summary>
  

 ``` RGB Histogram:                         RGB CDF:                          ```    
<img width="35%" img height="35%" alt="rgb_histogram" src="https://github.com/HagerSherif/Computer-Vision-Implementations/assets/93436199/bf228b00-bd88-4547-9d17-f75e06724fed"><img width="35%" img height="35%" alt="rgb_cumulative" src="https://github.com/HagerSherif/Computer-Vision-Implementations/assets/93436199/782059e2-6ee3-4c79-a858-2f171c06dc83">
  
 ``` Grey-scale Histogram:                   Grey-scale CDF:                  ```      
<img width="35%" img height="35%" alt="gray_cumulative" src="https://github.com/HagerSherif/Computer-Vision-Implementations/assets/93436199/2f234d44-d2a8-47b6-bb6d-5840223d3922"><img width="35%" img height="35%" alt="gray_histo (2)" src="https://github.com/HagerSherif/Computer-Vision-Implementations/assets/93436199/190b864f-50e4-4e20-8755-80aff66bb1c9">  



</details>

<details>
<summary>RGB to gray-scale</summary>
  

 ``` Before:                                                After:                                    ```   
  
<img width="50%" img height="50%" alt="whats2" src="https://github.com/HagerSherif/Computer-Vision-Implementations/assets/93436199/f2adb2ef-b9f5-4d13-9e4c-2ec0f93bb0a8"><img width="50%" img height="50%" alt="whats2" src="https://github.com/HagerSherif/Computer-Vision-Implementations/assets/93436199/bdccf89c-dc1b-4cd7-bcf8-44cf6bd1e8d2">


</details>

<details>
<summary>Image Equalization</summary>
  

 ``` Before:                                      After:                                  ```              

![whats](https://github.com/HagerSherif/Computer-Vision-Implementations/assets/93436199/72902b98-ff3e-4c08-865b-b76a96e8c3bd) 
![equalizeed](https://github.com/HagerSherif/Computer-Vision-Implementations/assets/93436199/7138a66b-a453-4c18-9bac-ddae34af8e14)
    
![gray](https://github.com/HagerSherif/Computer-Vision-Implementations/assets/93436199/1af1007d-9435-41ec-bcf6-aa80d4428105)
![equalized_gray](https://github.com/HagerSherif/Computer-Vision-Implementations/assets/93436199/cf63ee95-ee08-4bd2-baf4-f272d4937101)

  
<p> Linear CDF after equalization : </p> 
<img width="35%" img height="35%" alt="equalized_rgb_cumulative" src="https://github.com/HagerSherif/Computer-Vision-Implementations/assets/93436199/f746bdfd-07d6-402b-8383-01c1e6a43b61">

</details>


<details>
<summary>Hough circles</summary>
 
<img width="50%" img height="50%" alt="coins" src="https://github.com/HagerSherif/Computer-Vision-Implementations/assets/93436199/6237fa9e-5d74-4567-a9c7-98e0696d7526"><img width="50%" img height="50%" alt="coinsdetected" src="https://github.com/HagerSherif/Computer-Vision-Implementations/assets/93436199/38086cc6-4a96-492b-8f48-2fb0c1cc8eb3">
</details>



<details>
<summary>Template matching</summary>


</details>


<details>
<summary>Segmentation using KMeans clustering</summary>

   ``` Before:                                  After:                                 ```              
  <img width="35%" img height="35%" alt="tower" src="https://github.com/HagerSherif/Computer-Vision-Implementations/assets/93436199/fea6add7-b1bf-49ae-8c77-2f5062e34ae2"><img width="35%" img height="35%" alt="tower2" src="https://github.com/HagerSherif/Computer-Vision-Implementations/assets/93436199/08deb3cd-4d8d-47c7-9b97-71ddd7fb0b79">
  
<img width="35%" img height="35%" alt="veggies" src="https://github.com/HagerSherif/Computer-Vision-Implementations/assets/93436199/55a5e080-deee-4468-9294-6e87890d9554"><img width="35%" img height="35%" alt="another_6_clusters" src="https://github.com/HagerSherif/Computer-Vision-Implementations/assets/93436199/41870bc6-b2d9-4085-bd9b-97d27c6fce65">


  
  
</details>
