#include	<vector>
#include    <iostream>

#include	<opencv2/imgproc.hpp>

#include	"SudokuGrabber.hpp"

namespace sg
{
  void		findExtremeLines(const std::vector<cv::Vec2f> &lines, SudokuEdges &edges)
  {
      edges.top = cv::Vec2f(1000,1000);
      double topYIntercept=100000, topXIntercept=0;
      edges.bottom = cv::Vec2f(-1000,-1000);
      double bottomYIntercept=0, bottomXIntercept=0;
      edges.left = cv::Vec2f(1000,1000);
      double leftXIntercept=100000, leftYIntercept=0;
      edges.right = cv::Vec2f(-1000,-1000);
      double rightXIntercept=0, rightYIntercept=0;

      for (int i = 0 ; i < lines.size() ; i++)
      {
          cv::Vec2f current = lines[i];
          float p = current[0];
          float theta = current[1];

          if (p == 0 && theta == -100) continue;

          double xIntercept, yIntercept;
          xIntercept = p / cos(theta);
          yIntercept = p / (cos(theta) * sin(theta));

          if (theta > CV_PI*80/180 && theta < CV_PI*100/180)
          {
              if (p < edges.top[0])
              {
                  edges.top = current;
              }
              if (p > edges.bottom[0])
              {
                  edges.bottom = current;
              }
          }
          else if (theta < CV_PI*10/180 || theta > CV_PI*170/180)
          {
              if (xIntercept > rightXIntercept)
              {
                  edges.right = current;
                  rightXIntercept = xIntercept;
              }
              else if (xIntercept <= leftXIntercept)
              {
                  edges.left = current;
                  leftXIntercept = xIntercept;
              }
          }
      }
    }
};
