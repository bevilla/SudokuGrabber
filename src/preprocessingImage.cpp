#include	<opencv2/imgproc.hpp>

namespace sg
{
  const cv::Mat	kernel = (cv::Mat_<uchar>(3, 3) << 0, 1, 0, 1, 1, 1, 0, 1, 0);

  void		preprocessingImage(const cv::Mat &orig, cv::Mat &dest)
  {
    cv::Mat result;

    cv::cvtColor(orig, result, CV_BGR2GRAY);
    cv::GaussianBlur(result, result, cv::Size(11, 11), 0);
    cv::adaptiveThreshold(result, result, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 5, 2);
    cv::bitwise_not(result, result);
    cv::dilate(result, result, kernel);
    dest = result;
  }
};
