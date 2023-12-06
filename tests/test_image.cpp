#include<iostream>
#include "../src/Image.hh"

using namespace std;

int main(){
    // declare 4 pixels 
    Pixel p1({0,0,0});
    Pixel p2({1,1,1});
    Pixel p3({2,2,2});
    Pixel p4({3,3,3});
    
    // make a 2D array of pixels
    vector<vector<Pixel>> data{{p1,p2},{p3,p4}};
    
    // Build an image with this 2D array :
    Image img(data);
    
    // Access pixel 0,0
    cout << "On loc 0,0, channels values are " << img.get_pixel(0,0) << endl;
    
    // Change the channel values of that pixel
    img.set_pixel(p2,0,0);

    // Access this pixel and print it
    cout << "On loc 0,0, new channels values are " << img.get_pixel(0,0) << endl;

    // cout the image :
    cout << "Our image is thus : " << endl << img << endl;
    

    // Get rows or columns
    try{
        cout << "first row is " << endl;
        vector<Pixel> first_row = img.get_row(0);
        for(size_t i(0);i<first_row.size();++i){
            cout << first_row[i] << ' ';
        }
        cout << endl;

        cout << "last col is " << endl;
        vector<Pixel> last_col = img.get_column(1);
        for(size_t i(0);i<last_col.size();++i){
            cout << last_col[i] << ' ';
        }
        cout << endl;

        // Set column
        img.set_column(last_col,0);
        cout << "*changed first col to last col* ---> first col is now : " << endl;
        vector<Pixel> first_col = img.get_column(0);
        for(size_t i(0);i<first_col.size();++i){
            cout << first_col[i] << ' ';
        }
        cout << endl;

        // Set row
        img.set_row(first_row,1);
        cout << "*changed last row to first row* ---> last row is now : " << endl;
        vector<Pixel> last_row = img.get_row(1);
        for(size_t i(0);i<last_row.size();++i){
            cout << last_row[i] << ' ';
        }
        cout << endl;

        // test the exception handling in Image methods (should throw an exception)
        vector<Pixel> error_column = img.get_column(30);
    }
    catch(invalid_argument const& except){
        cout << "Catched the exception : " << endl << except.what() << endl;
        // abort tests
        return 1;
    }

    return 0;
}
