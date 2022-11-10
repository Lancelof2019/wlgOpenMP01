#include "../headerspace/WatershedAlg.h"
#include <queue>
#include <cstdlib> 
#include <vector>
#include <string.h>
#define NUMSIZE 8
#define NSIZE 4

using namespace cv;

int** WatershedAlg::distanceTransform(int** matArr, int** markers,int &rows,int &cols) {

        int dx[NUMSIZE]={-1, 1, 0, 0, -1, -1, 1, 1};
        int dy[NUMSIZE]={0, 0, -1, 1, -1,  1, 1, -1};
        //int numthresh=25;
        int pixelThreshold=55;


	bool** visArr=new bool*[rows];

	for(int i=0;i<rows;i++){
	     visArr[i]=new bool[cols];
	}	

       
        int* plotx=new int[rows*cols];
	int* ploty=new int[rows*cols];

        

        memset(plotx,-1,sizeof(int)*rows*cols);
        memset(ploty,-1,sizeof(int)*rows*cols);

       int **plots=new int*[rows];

       for(int i=0;i<rows;i++){
       plots[i]=new int[cols];
   }

        

//******It makes the nearest piexel along 0 point sohow up and become the edge pixel
 
        #pragma omp parallel for
        for(int i = 0; i < rows; i++) {
         #pragma omp parallel for
	   for(int j = 0; j < cols; j++) {
                if(matArr[i][j]!= ZERO) {
                    continue;
                }
                //this is the part that sepreated from the edge
                #pragma omp simd 
                for(int h = 0; h < NSIZE; h++) {
                    int nextX = i + dx[h];
                    int nextY = j + dy[h];

                    if( nextX < 0 || nextY < 0 || nextX >= rows || nextY >= cols ) {
                        continue;
                    }

                    if( !visArr[nextX][nextY] && matArr[nextX][nextY]== ONE){ 
                        visArr[nextX][nextY] = true;

			matArr[nextX][nextY]=pixelThreshold;
			plots[nextX][nextY]=1;

                    }
                }
                
        }
        
     }
    //******It makes the nearest piexel along 0 point sohow up and become the edge pixel
    
//edge is equal to 50
        int maxVal=0;
        int pcounter=0;
       // #pragma omp parallel for reduction(+:pcounter)
        for(int i=0;i<rows;i++){
          // #pragma omp parallel for
           for(int j=0;j<cols;j++){
             if(plots[i][j]==1){
                  plotx[pcounter]=i;
		  ploty[pcounter]=j;
                 // qx.push(i);
		 // qy.push(j);
		  pcounter++;
	     }
              

	   }


	}

int qcounter=0;
    
int i=0;
while(plotx[i]!=-1){

            int crtX=plotx[i];
            int crtY=ploty[i];
             i++;
             qcounter++;
            bool isBigger = true;

            for(int h = 0; h < NUMSIZE; h++) {
                int nextX = crtX + dx[h];
                int nextY = crtY + dy[h];

                if( nextX < 0 || nextY < 0 || nextX >= rows || nextY >= cols || matArr[nextX][nextY] == ZERO ) {
                    continue;
                }

                if( matArr[crtX][crtY] <= matArr[nextX][nextY]) {
                    isBigger = false;

                }
                //pick the max local value of some regions

                if( matArr[crtX][crtY] +1< matArr[nextX][nextY] ) {
                    visArr[nextX][nextY] = true;
                    matArr[nextX][nextY] =  min((matArr[crtX][crtY]+1), 254);

                    //to get max value for difference between max value image and image
                    if(maxVal<=matArr[nextX][nextY]){
                       maxVal=matArr[nextX][nextY];

                    }
                     //to get max value for difference between max value image and image
                    plotx[pcounter]=nextX;
                    ploty[pcounter]=nextY;
                    pcounter++;

                }
               
            }
           //find the max value in local area
            if(isBigger) {
                markers[crtX][crtY]=2;
        
             }
          }


   pixelThreshold=pixelThreshold-1;
   int pnumThrshold=30;
   int handlingType=0;
   int neighbourType=0;
   removeholesopt(matArr,pnumThrshold,  handlingType, neighbourType, pixelThreshold,rows,cols);

      return matArr;
    }
