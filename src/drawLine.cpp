#include	<vector>

#include	<opencv2/imgproc.hpp>

namespace sg
{
    void drawLine(cv::Vec2f line, cv::Mat &img, cv::Scalar rgb = CV_RGB(0,0,255))
    {
        if(line[1]!=0)
        {
            float m = -1/tan(line[1]);
            float c = line[0]/sin(line[1]);

            cv::line(img, cv::Point(0, c), cv::Point(img.size().width, m*img.size().width+c), rgb);
        }
        else
        {
            cv::line(img, cv::Point(line[0], 0), cv::Point(line[0], img.size().height), rgb);
        }
    }
}
