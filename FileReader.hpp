#include <fstream>
#include <string>
#include <iostream>
#include "Matrix.h"
#include <sstream>
#include <vector>


using namespace std;

class FileReader
{

public:
    static Matrix readMatrixFromTxtFile(string fileName,const int verticalSize,const int horizontalSize);
};

Matrix FileReader::readMatrixFromTxtFile(string fileName,const int verticalSize,const int horizontalSize){
    //string fileName:  Name of the file to read our matrix from.
    //const int verticalSize/horizontalSize:    Size of our matrix so that we can create a matrix in desired size.
    //Since we are going to use this function only to read our matrixes I create my Matrix in this function and then return it.

    string line;
    ifstream infile(fileName);  //Open file named fileName
    int x,counter=0;
    vector<int> vect;   //This vector is going to hold our values to transfer into our Matrix.

while (getline(infile, line))   //Iterate through each line of txt file
{
    istringstream iss(line);
    while(iss >> x){    //Iterate through each integer in a line
    vect.push_back(x);  //Push each integer into the integer
    }
}

    infile.close(); //Close our file.

    Matrix matrix = Matrix(verticalSize,horizontalSize,vect);//Create Matrix with specified sizes.
    
    return matrix;  //Return our created matrix.
}

