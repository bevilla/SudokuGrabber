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
  void		preprocessingImage(const cv::Mat &orig, cv::Mat &dest);

  /*
  ** Create a cv::Mat where sudoku grid lines are set to white
  ** and anything else is set to black
  ** The result is copied in dest
  */
  void		findBiggestBlob(const cv::Mat &orig, cv::Mat &dest);

  /*
  ** Apply HoughLines and merge lines
  ** The result is copied in lines
  */
  void		detectLines(const cv::Mat &orig, std::vector<cv::Vec2f> &lines);

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
				       SudokuEdges &src,
				       SudokuEdges &dest);

  /*
  ** Apply undistortion using src and dest coordinates
  ** The result is copied in undistorted
  */
  void		undistort(const cv::Mat &orig,
			  cv::Mat &undistorted,
			  const SudokuEdges &src,
			  const SudokuEdges &dest);
};
