#ifndef WATERSHEDALG_H
#define WATERSHEDALG_H

#include "../structPixel/structPixel.cpp"
#include<iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include<queue>
#include <vector>
#include<random>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <queue>
#include<string>
#include <cstdlib>
#include<omp.h>

#define ZERO 0
#define ONE 254
#define STEP 1
using namespace cv;
using namespace std;
class WatershedAlg{

public:
Mat makeImageGrayScale(Mat &image);
Mat inverseImage(Mat &image);
Mat erosion(Mat &image, vector< vector <int> > &kernel);
int** thresholdMeasure(Mat &image);
int** antiInverseImage(int** threshmat,int &rows,int &cols);
int** distanceTransform(int** antimat, int** markers,int &rows,int &cols);
Mat watershed(int** image, int **markers,Mat &duplImage,int &rows,int &cols);
void removeholesopt(int** src, int &pnumlThrshold, int &handlingType, int &neighbourType,int pixelThreshhold,int &rows,int &cols);
void processImage(Mat &image,Mat &duplImage) ;
};
#endif
