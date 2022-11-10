#include "../headerspace/WatershedAlg.h"
using namespace cv;
#define ZERO 0
 void WatershedAlg::removeholesopt(int** src,int &pnumThrshold, int &handlingType, int &neighbourType,int pixelThreshold,int &rows,int &cols)  {
  
    int RemoveCount=0;       

	#pragma omp parallel for 
        for(int i = 0; i < rows; ++i)  {    
 
             #pragma omp parallel for 
            for(int j = 0; j < cols; ++j) {    
                 if(src[i][j]>pixelThreshold){
                 Pointlabel.at<uchar>(i,j)=0;
                 
               
                 }
      
            }    
        }  


    vector<vector<Point>> contours; 
    vector<cv::Vec4i> hierarchy; 
    findContours(Pointlabel,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point()); 
 
    Point p=Point(0,0);


   if (!contours.empty() && !hierarchy.empty())	{

           #pragma omp parallel for      
	   for(int z=0;z<contours.size();z++){

	
		        cv::Rect countourposition = cv::boundingRect(Mat(contours.at(z)));      	
	
		        double area = contourArea(contours.at(z));
			
			if (area < pnumThrshold) 
			{
			
				
				#pragma omp parallel for
				
				for (int i = countourposition.y; i < countourposition.y + countourposition.height; i++) 
			
			
				{
					
					#pragma omp parallel for
         
					for (int j = countourposition.x; j < countourposition.x + countourposition.width; j++) 
				
					{
						
						if ((int)Pointlabel.at<uchar>(i,j) == 255) 
						{
						    Pointlabel.at<uchar>(i,j) = 2;
                                                    src[i][j]=pixelThreshold;

						}
					}
				}
			}
			
		}
	}

 }
