#include	<vector>

#include	<opencv2/imgproc.hpp>

#include	"SudokuGrabber.hpp"

namespace sg
{
  void		findExtremeLines(cv::Mat &dest, const std::vector<cv::Vec2f> &lines, SudokuEdges &edges)
  {
      cv::Vec2f topEdge = cv::Vec2f(1000,1000);
      double topYIntercept=100000, topXIntercept=0;
      cv::Vec2f bottomEdge = cv::Vec2f(-1000,-1000);
      double bottomYIntercept=0, bottomXIntercept=0;
      cv::Vec2f leftEdge = cv::Vec2f(1000,1000);
      double leftXIntercept=100000, leftYIntercept=0;
      cv::Vec2f rightEdge = cv::Vec2f(-1000,-1000);
      double rightXIntercept=0, rightYIntercept=0;

      for(int i=0 ; i<lines.size() ; i++)
      {
          cv::Vec2f current = lines[i];
          float p=current[0];
          float theta=current[1];

          if(p==0 && theta==-100) continue;

          double xIntercept, yIntercept;
          xIntercept = p/cos(theta);
          yIntercept = p/(cos(theta)*sin(theta));

          if(theta>CV_PI*80/180 && theta<CV_PI*100/180)
          {
              if(p<topEdge[0])
              {
                  topEdge = current;
              }
              if(p>bottomEdge[0])
              {
                  bottomEdge = current;
              }
          }
          else if(theta<CV_PI*10/180 || theta>CV_PI*170/180)
          {
              if(xIntercept>rightXIntercept)
              {
                  rightEdge = current;
                  rightXIntercept = xIntercept;
              }
              else if(xIntercept<=leftXIntercept)
              {
                  leftEdge = current;
                  leftXIntercept = xIntercept;
              }
          }
      }
       drawLine(topEdge, dest, CV_RGB(57,255,28));
       drawLine(bottomEdge, dest, CV_RGB(57,255,28));
       drawLine(leftEdge, dest, CV_RGB(57,255,28));
       drawLine(rightEdge, dest, CV_RGB(57,255,28));
    }
};
