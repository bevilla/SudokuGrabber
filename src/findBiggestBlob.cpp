#include	<opencv2/imgproc.hpp>
#include <cv.h>
#include <iostream>

namespace sg
{
  void		findBiggestBlob(const cv::Mat &orig, cv::Mat &dest, cv::Mat &kernel)
  {
    int count = 0;
    int max = 1;

    cv::Point maxPt;
    
    for (int y = 0; y < dest.size().height; y++) {
      uchar *row = dest.ptr(y);
      for (int x = 0; x < dest.size().width; x++) {
	if (row[x] >= 128) {
	  int area = floodFill(dest, cv::Point(x, y), CV_RGB(0,0,64));
	  if (area > max) {
	    maxPt = cv::Point(x, y);
	    max = area;
	  }
	}
      }
    }

    floodFill(dest, maxPt, CV_RGB(255,255,255));
    
    std::cout << dest.size().width << std::endl;
    std::cout << dest.size().height << std::endl;
    for (int y = 0; y < dest.size().height; y++) {
      uchar *row = dest.ptr(y);
      for (int x = 0; x < dest.size().width; x++) {
    	if (row[x] == 64 && x != maxPt.x && y != maxPt.y) {
    	  int area = floodFill(dest, cv::Point(x, y), CV_RGB(0,0,0));
    	}
    	std::cout << "x : " << x << std::endl;
      }
      std::cout << "y : " << y << std::endl ;
    }
    erode(dest, dest, kernel);
    
  }
};
