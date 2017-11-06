#include	<vector>

#include	<opencv2/imgproc.hpp>

#include "SudokuGrabber.hpp"

namespace sg
{
    static void mergeRelatedLines(std::vector<cv::Vec2f> *lines, cv::Mat &img)
    {
        std::vector<cv::Vec2f>::iterator current;
        for(current=lines->begin();current!=lines->end();current++)
        {
            if((*current)[0]==0 && (*current)[1]==-100) continue;

            float p1 = (*current)[0];
            float theta1 = (*current)[1];

            cv::Point pt1current, pt2current;
            if(theta1>CV_PI*45/180 && theta1<CV_PI*135/180)
            {
                pt1current.x=0;
                pt1current.y = p1/sin(theta1);
                pt2current.x=img.size().width;
                pt2current.y=-pt2current.x/tan(theta1) + p1/sin(theta1);
            }
            else
            {
                pt1current.y=0;
                pt1current.x=p1/cos(theta1);
                pt2current.y=img.size().height;
                pt2current.x=-pt2current.y/tan(theta1) + p1/cos(theta1);
            }

            std::vector<cv::Vec2f>::iterator    pos;
            for(pos=lines->begin();pos!=lines->end();pos++)
             {
                 if(*current==*pos) continue;
                 if(fabs((*pos)[0]-(*current)[0])<20 && fabs((*pos)[1]-(*current)[1])<CV_PI*10/180)
                 {
                     float p = (*pos)[0];
                     float theta = (*pos)[1];

                      cv::Point pt1, pt2;
                      if((*pos)[1]>CV_PI*45/180 && (*pos)[1]<CV_PI*135/180)
                      {
                          pt1.x=0;
                          pt1.y = p/sin(theta);
                          pt2.x=img.size().width;
                          pt2.y=-pt2.x/tan(theta) + p/sin(theta);
                      }
                      else
                      {
                          pt1.y=0;
                          pt1.x=p/cos(theta);
                          pt2.y=img.size().height;
                          pt2.x=-pt2.y/tan(theta) + p/cos(theta);
                      }

                    if(((double)(pt1.x-pt1current.x)*(pt1.x-pt1current.x) + (pt1.y-pt1current.y)*(pt1.y-pt1current.y)<64*64) &&
                    ((double)(pt2.x-pt2current.x)*(pt2.x-pt2current.x) + (pt2.y-pt2current.y)*(pt2.y-pt2current.y)<64*64))
                    {
                    // Merge the two
                        (*current)[0] = ((*current)[0]+(*pos)[0])/2;
                        (*current)[1] = ((*current)[1]+(*pos)[1])/2;

                        (*pos)[0]=0;
                        (*pos)[1]=-100;
                    }
                }
            }
        }
    }

    void		detectLines(cv::Mat &dest, std::vector<cv::Vec2f> &lines)
    {
        HoughLines(dest, lines, 1, CV_PI/180, 200);

        mergeRelatedLines(&lines, dest);

        for (int i=0 ; i<lines.size() ; i++)
        {
            drawLine(lines[i], dest, CV_RGB(0,0,128));
        }
    }
};
