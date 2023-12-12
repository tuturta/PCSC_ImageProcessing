#include "../src/reader.hh"
#include "../src/writer.hh"
#include <iostream>
#include <string>

using namespace std;


int main(){

    // Path of files
    cout << "Start" << endl;
    const string path_in("in/test.txt");
    const string path_out("out/out.txt");

    // Declaration of reader and writer classes
    TXTReader in_file(path_in);
    TXTWriter out_file(path_out);
    cout << "Classes initialized" << endl;

    try{
        // Create the image based on the input txt file
        Image image(in_file.read());
        
        cout << "File read" << endl;
        cout << "image txt: " << image;

        // Save the image to the output file
        out_file.write(image);
        cout << "Image written" << endl;
        
    }
    catch(std::exception& e){
        cerr << "ERREUR: " << e.what() << endl;
    }

    return 0;
}