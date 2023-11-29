#include<iostream>
#include "Pixel.hh"

using namespace std;

int main(){
    Pixel pix({1,2,3,4});
    cout << "dimension " << pix.dim() << endl;
    return 0;
}