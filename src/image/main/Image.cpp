#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <string>
#include <stdlib.h>

#include "Image.hpp"

//using namespace cv;
//Image 
//{ 
  //private:
    //std::string imagePath;
  //public:
Image::Image(std::string imagePath) { 
  setImg(imagePath); 
} 

int Image::readImage() { 
  cv::Mat img = cv::imread(imagePath, cv::IMREAD_COLOR); 
  if (img.empty()) { 
    std::cout << "Could not read image : " << imagePath << std::endl; 
    return 1; 
  } 

  cv::imshow("Display window", img);
  int k = cv::waitKey(0); 
  if(k == 's') 
  {
    cv::imwrite(imagePath, img);
  }
  return 0;
  }
