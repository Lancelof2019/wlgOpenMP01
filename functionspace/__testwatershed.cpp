int **nextSet= new int*[rows*cols];
for(int i=0;i<rows*cols;i++){

 nextSet[i]=new int[3];

}



//cout<<"makers size:"<<markers.size()<<endl;

//int msize=markers.size();
//vector<Point>::iterator markstart=markers.begin();
//vector<Point>::iterator markend=markers.end();
//vector<Point>::iterator markit;

 //#pragma omp parallel for


cout<<"ok"<<endl;


//cout<<"queue size"<<prioq.size()<<endl;
int ptcounter=0;
        while(!prioq.empty()) {
            //Pixel curpoint = prioq.top(); prioq.pop();//store the neighbours near ctrx and ctry

             int curpoint[3]={prioq.top()[0],prioq.top()[1],prioq.top()[2]};
             prioq.pop();
             int CrtX=curpoint[1];
             int CrtY=curpoint[2];
           // cout<<"curpoint"<<curpoint<<endl;
            bool canLabel = true;
            int neighboursLabel = 0;
            for(int i = 0; i < 8; i++) {
            
            //    int nextX = curpoint.x + dx[i];
              //  int nextY = curpoint.y + dy[i];
              int nextX = curpoint[1] + dx[i];
              int nextY = curpoint[2] + dy[i];
             

            
              if(nextX < 0 || nextY < 0 || nextX >= rows || nextY >= cols) {
                    continue;
                }

                //Pixel next = Pixel( image[nextX][nextY], nextX, nextY);
                 //int next[3]={image[nextX][nextY],nextX, nextY};

                // int *next=new int[3];
                  //    next[0]=image[nextX][nextY];
                    //  next[1]=nextX;
                     // next[2]=nextY;
		     //
		     //
	//	 int *next=nextSet[ptcounter];
		 nextSet[ptcounter][0]=image[nextX][nextY];

                 nextSet[ptcounter][1]=nextX;
		 nextSet[ptcounter][2]=nextY;
		 

		 // next[0]=image[nextX][nextY];
                 // next[1]=nextX;
                 // next[2]=nextY;

                // Must check if all surrounding marked have the same color
                //if(markerMap[nextX][nextY] != 0 && next.val != 0) {// id neighbour is not background,
                if(markerMap[nextX][nextY] != 0 &&  nextSet[ptcounter][0]!= 0){
                    if(neighboursLabel == 0) {
                        neighboursLabel = markerMap[nextX][nextY];//using id value,all strats from their closest neighbour
                    } else {//this part tells us that if there is two points at the boundary to see if they are in the same classification,
                    //two classification there is no merge
                        if(markerMap[nextX][nextY] != neighboursLabel ) {
                            canLabel = false;
                        }
                    }
                } else {
                    if(inprioq[nextX][nextY] == false) {
                        inprioq[nextX][nextY] = true;//aviod duplicate point is chosen,point does not exist in marker or background
                        prioq.push(nextSet[ptcounter]);
                        //the most important expending step,//only the point whose pixel value is 0 in Markermap
                    }
                }
		ptcounter++;
            }

            if(canLabel&&image[CrtX][CrtY]!=0) {
                
                markerMap[CrtX][CrtY] = neighboursLabel;//in this way it tells us that the points in same region share the same id or label
               duplImage.at<Vec3b>(CrtX,CrtY)=colors[ markerMap[CrtX][CrtY] ];
         
                
            }
         
        }
