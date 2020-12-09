#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <stdio.h>
#include <stdlib.h>

using namespace cv;
class Image {
  private: 
    std::string imagePath; 
  public: 
    Image(std::string imagePath) { 
      this->imagePath = imagePath; 
    } 

    int readImage() { 
      Mat img = imread(imagePath, IMREAD_COLOR);
      if (img.empty()) { 
        std::cout << "Could not read image : " << this->imagePath << std::endl; 
        return 1; 
      } 
      imshow("Display window", img);
      int k = waitKey(0); 
      if(k == 's') {
          imwrite(this->imagePath, img);
      }

      return 0;
  }
} image;

