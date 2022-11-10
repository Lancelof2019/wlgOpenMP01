 #include "../headerspace/WatershedAlg.h"
 #include<iostream>
 using namespace std;
 using namespace cv;
 #include <time.h>
 int main(){

     clock_t start1,end1;
     double start,end;
     start1=clock();
     start=omp_get_wtime();
  
     cv::Mat srcImg=cv::imread("../image/pexels-sagui-andrea-618833.jpg");
     cv::Mat duplImage(srcImg.rows,srcImg.cols,CV_8UC3,Scalar::all(0));
     srcImg.copyTo(duplImage);

     if(!srcImg.data){

        cout<<"The file is not loaded or does not exist"<<endl;
        return -1;


     }
   
     WatershedAlg *walg=new WatershedAlg();
     walg->processImage(srcImg,duplImage);
     end=omp_get_wtime();
     end1=clock();
     cout<<"The total time the parallel  algorithm used is :"<<(double)(end - start)<<"s"<<endl;
     cout<<"The total time the algorithm used is :"<<(double)(end1 - start1)/CLOCKS_PER_SEC<<endl;
     delete walg;
     return 0;
   } 
