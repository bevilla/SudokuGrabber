//
//-----------------------------------------------------------------------------
//Filename:    DigitRecognizer.hpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 11/6/17.
//-----------------------------------------------------------------------------
//

#pragma once

#include	<opencv2/opencv.hpp>
#include	<opencv2/ml.hpp>
#include	<opencv2/highgui.hpp>
#include    "IClassify.hpp"

#define MAX_NUM_IMAGES	60000

namespace sg {

    typedef unsigned char BYTE;

    class DigitRecognizer : public IClassify {
    public:
        DigitRecognizer();

        ~DigitRecognizer();

        /**
         * Method to train with ubyte files datas
         * @param trainPath
         * @param labelsPath
         * @return false if error
         */
        bool train(const char *trainPath, const char *labelsPath);

        /**
         * Override the classify implementation
         * @param img
         * @return the cell number
         */
        int classify(cv::Mat img) override;

    private:

        /**
         * Process the knn
         * @param img
         * @return
         */
        cv::Mat preprocessImage(cv::Mat img);

        /**
         * Read the data with flipping
         * @param fp
         * @return
         */
        int readFlippedInteger(FILE *fp);

    private:

        /**
         * @var KNearest for opencv 3.x
         */
        cv::Ptr<cv::ml::KNearest> _knn;

        int _numRows;
        int _numCols;
        int _numImages;
    };
};