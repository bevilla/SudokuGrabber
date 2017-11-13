//
//-----------------------------------------------------------------------------
//Filename:    IClassify.hpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 11/13/17.
//-----------------------------------------------------------------------------
//

#ifndef SUDOKUGRABBER_ICLASSIFY_HPP
#define SUDOKUGRABBER_ICLASSIFY_HPP

#include <opencv2/core/mat.hpp>

namespace sg {
    /**
     * @brief Interface to convert img cell to integer
     */
    class IClassify {
    public:
        /**
         * Method to convert img cell to integer
         * @param img
         * @return the number in the img cell
         */
        virtual int classify(cv::Mat img) = 0;
    };
}

#endif //SUDOKUGRABBER_ICLASSIFY_HPP
