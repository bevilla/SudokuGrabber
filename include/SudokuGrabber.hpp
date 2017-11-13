#pragma once

#include    <vector>
#include "IClassify.hpp"
#include    <opencv2/imgproc.hpp>

namespace sg {

    /**
     * @brief SudokuEdges struct
     */
    struct SudokuEdges {
        cv::Vec2f top;
        cv::Vec2f bottom;
        cv::Vec2f left;
        cv::Vec2f right;
    };

    const cv::Mat kernel;

    /**
     * Apply gaussian blur, threshold, bitwisenot, dilate algorithm
     * The result is copied in dest
     * @param orig
     * @param dest
     * @param kernel
     */
    void preprocessingImage(const cv::Mat &orig, cv::Mat &dest, cv::Mat &kernel);

    /**
     * Create a cv::Mat where sudoku grid lines are set to white
     * and anything else is set to black
     * The result is copied in dest
     * @param orig
     * @param dest
     * @param kernel
     */
    void findBiggestBlob(const cv::Mat &orig, cv::Mat &dest, cv::Mat &kernel);

    /**
     * Apply HoughLines and merge lines
     * The result is copied in lines
     * @param dest
     * @param lines
     */
    void detectLines(cv::Mat &dest, std::vector<cv::Vec2f> &lines);

    /**
     * Get edges of extreme lines
     * The result is copied in edges
     * @param lines
     * @param edges
     */
    void findExtremeLines(const std::vector<cv::Vec2f> &lines, SudokuEdges &edges);

    /**
     * Find intersections of the four lines in order to apply undistortion
     * The result is copied in src, dest
     * @param matSize
     * @param edges
     * @param src
     * @param dest
     * @param maxLength
     */
    void calculateIntersections(const cv::Size &matSize,
                                const SudokuEdges &edges,
                                cv::Point2f src[],
                                cv::Point2f dest[],
                                int *maxLength);

    /**
     *
     * Apply undistortion using src and dest coordinates
     * The result is copied in undistorted
     * @param orig
     * @param undistorted
     * @param src
     * @param dest
     * @param maxLength
     */
    void undistort(const cv::Mat &orig,
                   cv::Mat &undistorted,
                   const cv::Point2f src[],
                   const cv::Point2f dest[],
                   const int maxLength);

    void drawLine(cv::Vec2f line, cv::Mat &img, cv::Scalar rgb = CV_RGB(0, 0, 255));

    /**
     * Get the array via OCR of the cell
     * @param undistortedThreshed
     * @param dr
     * @param maxLength
     * @return
     */
    int *find2DArrayNumber(cv::Mat &undistortedThreshed, IClassify &dr, double maxLength);
};
