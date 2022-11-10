#include "../headerspace/WatershedAlg.h"
#include<vector>
using namespace cv;
#define NUMSIZE 8
#define NSIZE 4

Mat WatershedAlg::watershed(int** image, int **markers,Mat &duplImage,int &rows,int &cols) {

       priority_queue<Pixel,vector<Pixel>,Compare> prioq;

       int msize=0;
       bool** __restrict inprioq=new bool*[rows];
       int** __restrict markerMap=new int*[rows];

      for(int i=0;i<rows;i++){
          inprioq[i]=new bool[cols];
 
       }

           for(int i=0;i<rows;i++){
           markerMap[i]=new int[cols];

       }



        #pragma omp parallel for
        for(int i=0;i<rows;i++){
         #pragma omp parallel for
         for(int j=0;j<cols;j++){
           inprioq[i][j]=false;
	  markerMap[i][j]=0;

	   }
          }

       int dx[NUMSIZE]={-1, 1, 0, 0, -1, -1, 1, 1};
       int dy[NUMSIZE]={0, 0, -1, 1, -1,  1, 1, -1};

        // Put markers in priority queue
        int id = 1;
        Mat testDuplicate;
        duplImage.copyTo(testDuplicate);
        Mat dstImage(duplImage.rows,duplImage.cols,CV_8UC3,Scalar::all(0));

   for(int y=0;y<rows;y++){

      for(int z=0;z<cols;z++){
 
           if(markers[y][z]==2){    
            markerMap[y][z] = id;
            msize++;
             for(int i = 0; i < 4; i++) {

                int newX =y + dx[i];
                int newY =z + dy[i];
                if(newX < 0 || newY < 0 || newX >= rows || newY >= cols) {
                    continue;
                }
              

                prioq.push( Pixel( image[newX][newY], newX, newY) );
                
             }

             id++;
           }
        }
   }

         Vec3b colors[msize+1];
         #pragma omp parallel for
         for(int i = 0; i <= msize; i++) {
           Vec3b vecColor;
           vecColor[0] = rand()%255+0;
           vecColor[1] = rand()%255+1;
           vecColor[2] = rand()%255+2;          
           colors[i]=vecColor;
        }


        while(!prioq.empty()) {
            Pixel curpoint = prioq.top(); prioq.pop();//store the neighbours near ctrx and ctry
            bool canLabel = true;
            int neighboursLabel = 0;
            for(int i = 0; i < 8; i++) {
                int nextX = curpoint.x + dx[i];
                int nextY = curpoint.y + dy[i];
                if(nextX < 0 || nextY < 0 || nextX >= rows || nextY >= cols) {
                    continue;
                }
                Pixel next = Pixel( image[nextX][nextY], nextX, nextY);

                // Must check if all surrounding marked have the same color
                if(markerMap[next.x][next.y] != 0 && next.val != 0) {// id neighbour is not background,
                    if(neighboursLabel == 0) {
                        neighboursLabel = markerMap[next.x][next.y];//using id value,all strats from their closest neighbour
                    } else {//this part tells us that if there is two points at the boundary to see if they are in the same classification,
                    //two classification there is no merge
                        if(markerMap[next.x][next.y] != neighboursLabel ) {
                            canLabel = false;
                        }
                    }
                } else {
                    if(inprioq[nextX][nextY] == false) {
                        inprioq[next.x][next.y] = true;//aviod duplicate point is chosen,point does not exist in marker or background
                        prioq.push(next);
                        //the most important expending step,//only the point whose pixel value is 0 in Markermap
                    }
                }
            }

            if(canLabel&&image[curpoint.x][curpoint.y]!=0) {
                
                markerMap[curpoint.x][curpoint.y] = neighboursLabel;//in this way it tells us that the points in same region share the same id or label
               duplImage.at<Vec3b>(curpoint.x,curpoint.y)=colors[ markerMap[curpoint.x][curpoint.y] ];
         
                
            }
         
        }

       cv::addWeighted(duplImage,0.4,testDuplicate,0.6,0,dstImage);
        duplImage.release();
        testDuplicate.release();
        return dstImage;
    }
