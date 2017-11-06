#pragma once

#include	<vector>

#include	<opencv2/imgproc.hpp>

namespace sg
{
  struct	SudokuEdges
  {
    cv::Vec2f	top;
    cv::Vec2f   bottom;
    cv::Vec2f   left;
    cv::Vec2f   right;
  };

  const cv::Mat	kernel;

  /*
  ** Apply gaussian blur, threshold, bitwisenot, dilate algorithm
  ** The result is copied in dest
  */
  void		preprocessingImage(const cv::Mat &orig, cv::Mat &dest, cv::Mat &kernel);

  /*
  ** Create a cv::Mat where sudoku grid lines are set to white
  ** and anything else is set to black
  ** The result is copied in dest
  */
  void		findBiggestBlob(const cv::Mat &orig, cv::Mat &dest, cv::Mat &kernel);

  /*
  ** Apply HoughLines and merge lines
  ** The result is copied in lines
  */
  void		detectLines(cv::Mat &dest, std::vector<cv::Vec2f> &lines);

  /*
  ** Get edges of extreme lines
  ** The result is copied in edges
  */
  void		findExtremeLines(const std::vector<cv::Vec2f> &lines, SudokuEdges &edges);

  /*
  ** Find intersections of the four lines in order to apply undistortion
  ** The result is copied in src, dest
  */
  void		calculateIntersections(const cv::Size &matSize,
				       const SudokuEdges &edges,
				       cv::Point2f src[],
				       cv::Point2f dest[],
                       int *maxLength);

  /*
  ** Apply undistortion using src and dest coordinates
  ** The result is copied in undistorted
  */
  void		undistort(const cv::Mat &orig,
			  cv::Mat &undistorted,
			  const cv::Point2f src[],
			  const cv::Point2f dest[],
              const int maxLength);

              void       drawLine(cv::Vec2f line, cv::Mat &img, cv::Scalar rgb = CV_RGB(0,0,255));
};
