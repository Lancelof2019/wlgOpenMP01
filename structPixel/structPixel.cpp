#include<iostream>

using namespace std;

struct Pixel {
    int val;
    int x;
    int y;

    Pixel(int val, int x, int y) : val(val), x(x), y(y) {}
    
};


struct Compare{

   bool operator()(Pixel &para1, Pixel &para2) {
        return para1.val < para2.val;
    }

};
