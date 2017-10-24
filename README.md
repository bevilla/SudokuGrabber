# SudokuGrabber

SudokuGrabber [tutorial](http://aishack.in/tutorials/sudoku-grabber-opencv-plot/ "SuDoKu Grabber using OpenCV") implementation by {EPITECH.} students using C++ and OpenCV.

## Compile and run

```bash
mkdir build
cd build
cmake ..
make
cd ..
./SudokuGrabber
```

If you got this error:
> Could not find a package configuration file provided by "OpenCV" with any of the following names...

compile the OpenCV library and use cmake like this:

```bash
  OpenCV_DIR=<path_to_opencv_lib> cmake ..
```
