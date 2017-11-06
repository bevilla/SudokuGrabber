#include	<opencv2/imgproc.hpp>

#include	"SudokuGrabber.hpp"

namespace sg
{
  void		undistort(const cv::Mat &orig,
			  cv::Mat &undistorted,
			  const cv::Point2f src[],
			  const cv::Point2f dest[],
              const int maxLength)
  {
      undistorted = cv::Mat(cv::Size(maxLength, maxLength), CV_8UC1);
      cv::warpPerspective(orig, undistorted,
                          cv::getPerspectiveTransform(src, dest),
                          cv::Size(maxLength, maxLength));

  }
};
