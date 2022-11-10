
#include "../headerspace/WatershedAlg.h"
using namespace cv;

int** WatershedAlg::antiInverseImage(int **antimat,int &rows,int &cols) {
        #pragma omp parallel for 
	for(int i = 0; i < rows; i++) {
	   #pragma omp parallel for  
            for(int j = 0; j < cols; j++) {
                if( antimat[i][j] == ZERO ) {
                    antimat[i][j] = ZERO;
                } else {
                    antimat[i][j] = ONE;
                }
            }
        }

        return antimat;
    }
