#include "Matrix.h"
#include <iostream>
#include <vector>
#include "FileWriter.hpp"
#include <string>

Matrix::Matrix(const int verticalSize,const int horizontalSize, std::vector<int>& vect)
{   //Matrix constructor 
    //const int verticalSize/horizontalSize:    These variables are the sizes of our 2d matrix
    //vector<int> vect: is the vector that carries values to insert our values inside of the matrix

    privMatrix = new int*[verticalSize];
    horSize=horizontalSize;
    verSize=verticalSize;
    for(int i = 0; i < verticalSize; i++){
        privMatrix[i] = new int[horizontalSize];    //We create horizontalSize sized arrays inside each pointer that our privMatrix points.
        for(int j = 0; j < horizontalSize; j++){    
            privMatrix[i][j] = vect[i*horizontalSize+j];    //We insert each value from our vect one by one to our Matrix.
            
            }
    }
}

Matrix::~Matrix(){
    for(int i = 0; i < verSize; i++){
        delete[] privMatrix[i];
    }
    
}

void Matrix::multiplyMatrixes(Matrix& keyMatrix,int verticalIndex,int horizontalIndex,string outputFileName){
    //  This function multiplies one matrix with another and since my program is going to use it continuously I have designed it in a recursive way.
    //Matrix keyMatrix:    Matrix object which holds the key matrix
    //int verticalIndex/horizontalIndex:    These indices points our program to where to look at. !!! I have preferred to use top-left index in my design
    //string outputFileName:   File to print our output to

    int keySize= keyMatrix.verSize;     //So that I dont need to call function everytime I need key matrixes size.
    int sum = 0;                        //I add every individual multiply operation to this variable.
    int orientation;                    //Orientation is the direction we expect our key to search next.
    std::string outputString;
    int** kmatrix = keyMatrix.getMatrix();
    for (int i = 0; i < keySize; i++)
    {
        for (int j = 0; j < keySize; j++)
        {
            sum += kmatrix[i][j] * privMatrix[verticalIndex+i][horizontalIndex+j];
        }
    }

     while(sum<0){  //If sum is negative we add 5 until it reaches a positive value
        sum+=5;
    }

    outputString = std::to_string(verticalIndex+(keySize-1)/2) +","+std::to_string(horizontalIndex+(keySize-1)/2) +":"+std::to_string(sum);
    //verticalIndex+(keySize-1)/2 or horizontalIndex+(keySize-1)/2 represents the middle index of that matrix.
    writeToFile(outputFileName,outputString);
   
    orientation = sum%5;

    switch (orientation)
    {
    case 0: //Means our function has found the treasure
        break;
    case 1: //Means to go up
        if (privMatrix[verticalIndex][horizontalIndex+1]==0) 
        //We use top-left index in our program so this index is the one on the right of it. If this value is zero it means we cannot go upwards(Remember our boundaries consists of 0s)
        {
            orientation=2;  //If we cannot go up then go downwards.
            break;
        }
        break;
        
    case 2: //Means to go down
        if (privMatrix[verticalIndex+keySize-1][horizontalIndex+1]==0)
        //Check the index one right of the bottom-left index.
        {
            orientation=1;  //If we cannot go down then go upwards.
            break;
        }
        break;
        
    case 3: //Means to go right
        if (privMatrix[verticalIndex+1][horizontalIndex+keySize-1]==0)
        //Check the index one down of the top-right index.
        {   
            
            orientation=4;  //If we cannot go right then go leftwards
            break;
        }        
        break;
        
    case 4: //Means to go left
        if (privMatrix[verticalIndex+1][horizontalIndex]==0)
        //Check the index one down of the top-left index.
        {
            orientation=3;  //If we cannot go left then go rightwards.
            break;
        }
       break;
        
    }
    if (orientation == 0){
        return;
    }

    shiftOperator(orientation,keySize,verticalIndex,horizontalIndex);   //This function operates the shifting of key matrix operation.

    multiplyMatrixes(keyMatrix,verticalIndex,horizontalIndex,outputFileName);   //We called this function again. This will go on continously until we find the treasure.
    
        
       
    

}

int** Matrix::getMatrix(){
    return privMatrix;
}


void Matrix::shiftOperator(int orientation,int size,int &verticalIndex,int &horizontalIndex){
    //int orientation:  Direction of our shift operation.
    //int size: Size of the key. This variable is important because we are shifting our key matrix by the size of the key.
    //int &verticalIndex and int &horizontalIndex:  These are the location of our matrix.Don't forget these are the top-left indexes.
//We passed them by reference so that we can change their value and it will apply these changes in actual variables.
    //This function operates the shifting of the key matrix operation.
    switch (orientation)
    {
    case 1: //MEANS SHIFT TO UP
        verticalIndex = verticalIndex - size;
        break;
    case 2: //MEANS SHIFT TO DOWN
        verticalIndex = verticalIndex + size;
        break;
    case 3: //MEANS SHIFT TO RIGHT
        horizontalIndex = horizontalIndex +size;
        break;
    case 4: //MEANS SHIFT TO LEFT
        horizontalIndex= horizontalIndex -size;
        break;
}
}
