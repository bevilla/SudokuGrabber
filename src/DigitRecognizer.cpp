//
//-----------------------------------------------------------------------------
//Filename:    DigitRecognizer.cpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 11/6/17.
//-----------------------------------------------------------------------------
//

#include "DigitRecognizer.hpp"

sg::DigitRecognizer::DigitRecognizer() {
    // the ml module in 3.0 got some refactoring lately
    _knn = cv::ml::KNearest::create();
}

sg::DigitRecognizer::~DigitRecognizer() {

}

bool sg::DigitRecognizer::train(const char *trainPath, const char *labelsPath) {
    FILE *fp = fopen(trainPath, "rb");
    FILE *fp2 = fopen(labelsPath, "rb");

    if (!fp || !fp2) {
        std::cerr << "IOError with files fp ad fp2" << std::endl
                  << "fp: " << trainPath << std::endl << "fp2: " << labelsPath << std::endl;
        return false;
    }

    // Read bytes in flipped order
    int magicNumber = readFlippedInteger(fp);
    _numImages = readFlippedInteger(fp);
    _numRows = readFlippedInteger(fp);
    _numCols = readFlippedInteger(fp);

    // std::cout << "Magic number: " <<  magicNumber << std::endl;
    // std::cout << "Number of images " <<  _numImages << std::endl;
    // std::cout << "Number of rows " <<  _numRows << std::endl;
    // std::cout << "Number of columns " <<  _numCols << std::endl;

    fseek(fp2, 0x08, SEEK_SET);

    if (_numImages > MAX_NUM_IMAGES) _numImages = MAX_NUM_IMAGES;

    //////////////////////////////////////////////////////////////////
    // Go through each training data entry and figure out a
    // center for each digit

    int size = _numRows * _numCols;
    CvMat *trainingVectors = cvCreateMat(_numImages, size, CV_32FC1);
    CvMat *trainingClasses = cvCreateMat(_numImages, 1, CV_32FC1);

    memset(trainingClasses->data.ptr, 0, sizeof(float) * _numImages);

    BYTE *temp = new BYTE[size];
    BYTE tempClass = 0;
    for (int i = 0; i < _numImages; i++) {
        fread((void *) temp, size, 1, fp);
        fread((void *) (&tempClass), sizeof(BYTE), 1, fp2);

        trainingClasses->data.fl[i] = tempClass;

        // Normalize the vector
        /*float sumofsquares = 0;
        for(int k=0;k<size;k++)
            sumofsquares+=temp[k]*temp[k];
        sumofsquares = sqrt(sumofsquares);*/

        for (int k = 0; k < size; k++)
            trainingVectors->data.fl[i * size + k] = temp[k]; ///sumofsquares;
    }

    _knn->train(cv::cvarrToMat(trainingVectors), cv::ml::ROW_SAMPLE, cv::cvarrToMat(trainingClasses));
    fclose(fp);
    fclose(fp2);

    return true;
}

int sg::DigitRecognizer::classify(cv::Mat img) {
    cv::Mat cloneImg = preprocessImage(img);

    return static_cast<int>(_knn->findNearest(cv::Mat_<float>(cloneImg), 1, cv::noArray()));
}

cv::Mat sg::DigitRecognizer::preprocessImage(cv::Mat img) {
    int rowTop = -1, rowBottom = -1, colLeft = -1, colRight = -1;

    cv::Mat temp;
    int thresholdBottom = 50;
    int thresholdTop = 50;
    int thresholdLeft = 50;
    int thresholdRight = 50;
    int center = img.rows / 2;
    for (int i = center; i < img.rows; i++) {
        if (rowBottom == -1) {
            temp = img.row(i);
            IplImage stub = temp;
            if (cvSum(&stub).val[0] < thresholdBottom || i == img.rows - 1)
                rowBottom = i;
        }

        if (rowTop == -1) {
            temp = img.row(img.rows - i);
            IplImage stub = temp;
            if (cvSum(&stub).val[0] < thresholdTop || i == img.rows - 1)
                rowTop = img.rows - i;
        }

        if (colRight == -1) {
            temp = img.col(i);
            IplImage stub = temp;
            if (cvSum(&stub).val[0] < thresholdRight || i == img.cols - 1)
                colRight = i;
        }

        if (colLeft == -1) {
            temp = img.col(img.cols - i);
            IplImage stub = temp;
            if (cvSum(&stub).val[0] < thresholdLeft || i == img.cols - 1)
                colLeft = img.cols - i;
        }
    }

    /*
    cv::Point2i pt = cv::Point((colLeft+colRight)/2, (rowTop+rowBottom)/2);
    cv::line(img, cv::Point(0, rowTop), cv::Point(img.cols, rowTop), cvScalar(255,255,255));
    cv::line(img, cv::Point(0, rowBottom), cv::Point(img.cols, rowBottom), cvScalar(255,255,255));
    cv::line(img, cv::Point(colLeft, 0), cv::Point(colLeft, img.rows), cvScalar(255,255,255));
    cv::line(img, cv::Point(colRight, 0), cv::Point(colRight, img.rows), cvScalar(255,255,255));
    */
    // imshow("Testing the image", img);
    // cvWaitKey(0);

    // Now, position this into the center

    cv::Mat newImg;
    newImg = newImg.zeros(img.rows, img.cols, CV_8UC1);

    int startAtX = (newImg.cols / 2) - (colRight - colLeft) / 2;
    int startAtY = (newImg.rows / 2) - (rowBottom - rowTop) / 2;

    for (int y = startAtY; y < (newImg.rows / 2) + (rowBottom - rowTop) / 2; y++) {
        uchar *ptr = newImg.ptr<uchar>(y);
        for (int x = startAtX; x < (newImg.cols / 2) + (colRight - colLeft) / 2; x++) {
            ptr[x] = img.at<uchar>(rowTop + (y - startAtY), colLeft + (x - startAtX));
        }
    }

    cv::Mat cloneImg = cv::Mat(_numRows, _numCols, CV_8UC1);
    resize(newImg, cloneImg, cv::Size(_numCols, _numRows));

    // Now fill along the borders
    /*
    for(int i=0;i<cloneImg.rows;i++)
    {
        floodFill(cloneImg, cvPoint(0, i), cvScalar(0,0,0));
        floodFill(cloneImg, cvPoint(cloneImg.cols-1, i), cvScalar(0,0,0));

        floodFill(cloneImg, cvPoint(i, 0), cvScalar(0));
        floodFill(cloneImg, cvPoint(i, cloneImg.rows-1), cvScalar(0));
    }
     */

    // imshow("testing image", cloneImg);

    cloneImg = cloneImg.reshape(1, 1);

    return cloneImg;
}

int sg::DigitRecognizer::readFlippedInteger(FILE *fp) {
    int ret = 0;
    BYTE *temp;

    temp = (BYTE *) (&ret);
    fread(&temp[3], sizeof(BYTE), 1, fp);
    fread(&temp[2], sizeof(BYTE), 1, fp);
    fread(&temp[1], sizeof(BYTE), 1, fp);
    fread(&temp[0], sizeof(BYTE), 1, fp);

    return ret;
}
