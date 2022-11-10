#include "../headerspace/WatershedAlg.h"
#include <cmath> 
#include <stdlib.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

int** WatershedAlg::thresholdMeasure(Mat &image) {

   cv::adaptiveThreshold(image,image,255,cv::ADAPTIVE_THRESH_GAUSSIAN_C,cv::THRESH_BINARY,  5,3);

   int **threshmat=new int*[image.rows];
   for(int i=0;i<image.rows;i++){

      threshmat[i]=new int[image.cols];

   }
 #pragma omp parallel for
 for(int i=0;i<image.rows;i++){
     #pragma omp parallel for
	 for(int j=0;j<image.cols;j++){
         threshmat[i][j]=(int)image.at<uchar>(i,j);

	}
   }
       


        return threshmat;
 }
