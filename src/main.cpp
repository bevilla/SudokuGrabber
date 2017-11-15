#include    <iostream>
#include    <string>

#include    <opencv2/imgproc.hpp>
#include    <opencv2/highgui.hpp>
#include    <DigitRecognizer.hpp>
#include    "SudokuGrabber.hpp"
#include    "Solver.hpp"


void sudoku(const cv::Mat &img) {
    std::string windowName = "Sudoku";
    cv::Mat result;
    std::vector<cv::Vec2f> lines;
    sg::SudokuEdges edges;
    cv::Point2f src[4], dest[4];
    int maxLength;
    cv::Mat kernel;

    sg::preprocessingImage(img, result, kernel);
    sg::findBiggestBlob(result, result, kernel);
    sg::detectLines(result, lines);
    sg::findExtremeLines(lines, edges);
    sg::calculateIntersections(img.size(), edges, src, dest, &maxLength);
    sg::undistort(img, result, src, dest, maxLength);

    // TODO : create method to process that
    cv::Mat undistortedThreshed = result.clone();
    threshold(result, undistortedThreshed, 128, 255, CV_THRESH_BINARY_INV);

    cv::cvtColor(undistortedThreshed, undistortedThreshed, cv::COLOR_BGR2GRAY);
    cv::cvtColor(result, result, cv::COLOR_BGR2GRAY);
    cv::adaptiveThreshold(result, undistortedThreshed, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY_INV, 101,
                          1);

    // TODO : use IA OCR solver
    auto dr = sg::DigitRecognizer();
    bool b = dr.train("./data/train-images-idx3-ubyte", "./data/train-labels-idx1-ubyte");
    std::cout << "Trained: " << std::to_string(b) << std::endl;

    // TODO : use Sudoku Solver
    int *tab = sg::find2DArrayNumber(undistortedThreshed, dr, maxLength);

    Solver solv(tab);
    solv.print();

    // At this point we should have the original sudoku grid undistorted
    cv::imshow(windowName, undistortedThreshed);
    while (cv::waitKey(0) != 27); // press ESC to exit while loop
}

int main(int argc, char **argv) {
    //std::string	filename = "data/sudoku.jpg";
    //std::string	filename = "../test_grid.jpg";
    std::string filename;
    if (argc > 1)
        filename = argv[1];
    else
        filename = "data/sudoku.jpg";

    cv::Mat img = cv::imread(filename);

    if (!img.data) {
        std::cerr << "Error: cannot open file \"" << filename << '"' << std::endl;
        return EXIT_FAILURE;
    }
    sudoku(img);
    return EXIT_SUCCESS;
}
