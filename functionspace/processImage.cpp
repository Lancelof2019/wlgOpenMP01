#include "../headerspace/WatershedAlg.h"
using namespace cv;
void WatershedAlg::processImage(Mat &image,Mat &duplImage)  {


       image = makeImageGrayScale(image);

     
       vector< vector<int> > erosionTargetThree{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}, };
       image = erosion(image, erosionTargetThree);

        int** __restrict threshmat;
        threshmat= thresholdMeasure(image);

       int** __restrict antimat;
       antimat=antiInverseImage(threshmat,image.rows,image.cols);
        int **markers=new int*[image.rows];
          for(int i=0;i<image.rows;i++){
              markers[i]=new int[image.cols];

	  }
        #pragma omp parallel for
	for(int i=0;i<image.rows;i++){
	 #pragma omp parallel for
	   for(int j=0;j<image.cols;j++){
               markers[i][j]=0;
               
		}
	}



	int** __restrict matimage;
        matimage=distanceTransform(antimat,markers,image.rows,image.cols);


       image = watershed(matimage, markers,duplImage,image.rows,image.cols);


    }
