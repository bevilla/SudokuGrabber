//
//-----------------------------------------------------------------------------
//Filename:    find2DArrayNumber.cpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 11/13/17.
//-----------------------------------------------------------------------------
//

#include <IClassify.hpp>
#include <SudokuGrabber.hpp>
#include <cv.hpp>
#include <iostream>

namespace sg {
    int *find2DArrayNumber(cv::Mat &undistortedThreshed, IClassify &dr, double maxLength) {
        int dist = static_cast<int>(ceil(maxLength / 9));
        int *output = new int[81];
        cv::Mat currentCell = cv::Mat(dist, dist, CV_8UC1);


        for (int j = 0; j < 9; j++) {
            for (int i = 0; i < 9; i++) {
                // We copy the current cell into a separate image
                //undistortedThreshed.adjustROI(i*dist, i*dist+dist, j*dist, j*dist+dist);
                for (int y = 0; y < dist && j * dist + y < undistortedThreshed.cols; y++) {
                    uchar *ptr = currentCell.ptr(y);
                    // uchar* ptr2 = &(undistortedThreshed.ptr<uchar>(i*dist)[j*dist]);
                    for (int x = 0; x < dist && i * dist + x < undistortedThreshed.rows; x++) {
                        ptr[x] = undistortedThreshed.at<uchar>(j * dist + y, i * dist + x);
                    }
                }

                // Fill edges with black color
                /*
                for(int l=0;l<dist/10;l++)
                {
                    floodFill(undistortedThreshed, cv::Point(l,l), cvScalar(0));
                    floodFill(undistortedThreshed, cv::Point(l,dist-l-1), cvScalar(0));
                    floodFill(undistortedThreshed, cv::Point(dist-l-1,l), cvScalar(0));
                    floodFill(undistortedThreshed, cv::Point(dist-l-1,dist-l-1), cvScalar(0));
                }

                /*CvRect bb = findBB(currentCell);
                Mat currentToProcess = Mat(bb.height-bb.x, bb.width-bb.x, CV_8UC1);
                for(int y=bb.y;y<bb.height;y++)
                {
                    uchar* ptr = currentToProcess.ptr(y);
                    // uchar* ptr2 = &(undistortedThreshed.ptr<uchar>(i*dist)[j*dist]);
                    for(int x=bb.x;x<bb.width;x++)
                    {
                        ptr[x] = currentCell.at<uchar>(y, x);
                    }
                }*/


                cv::Moments m = cv::moments(currentCell, true);
                int area = static_cast<int>(m.m00);

                imshow("tested", currentCell);

                if (area > currentCell.rows * currentCell.cols / 5) {
                    int number = dr.classify(currentCell);
                    std::cout << "Classified as: " << number << std::endl;
                    output[j * 9 + i] = number;
                    // cv::waitKey(0);
                } else {
                    output[j * 9 + i] = 0;
                    std::cout << "Empty block" << std::endl;
                }

                // cv::waitKey(0);

                // cv::imshow(windowName, undistortedThreshed);
            }
            printf("\n");
        }
        return output;
    }
}