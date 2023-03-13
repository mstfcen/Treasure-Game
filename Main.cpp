#include "Matrix.h"
#include "Matrix.cpp"
#include "FileReader.hpp"
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    stringstream ss(argv[1]);       //Our map matrix size is stated as NxM. So I passed it in a string stream to get each dimensions size.
    int keySize = stoi(argv[2]);    //argv[2] represents the key Matrixes size. Since I need it as an integer I hold it as an integer.
    string mapFileName = argv[3];   //this is the name of the txt file which holds our Map Matrix.
    string keyFileName = argv[4];   //This is the name of the txt file which holds our Key Matrix.
    string outputFileName = argv[5];//This is the name of the txt file which our program should print our output to.

    int mapSizesArr[2]; 
    int counter=0,x;
    string str;
    while (getline(ss, str, 'x'))   //So I splitted the string from where the each 'x' is at. And since we know we are going to get 2 integers from this operation I hold them in a array which has a size of 2
    {   
        mapSizesArr[counter++]=stoi(str);
    }

    Matrix keyMatrix = FileReader::readMatrixFromTxtFile(keyFileName,keySize,keySize);  //This is where I create my key Matrix object.
    
    Matrix mapMatrix = FileReader::readMatrixFromTxtFile(mapFileName,mapSizesArr[0],mapSizesArr[1]);    //This is where I create my map Matrix object.

    mapMatrix.multiplyMatrixes(keyMatrix,0,0,outputFileName);   //This is the function to start recursive multiplyMatrixes function.

    return 0;
}
