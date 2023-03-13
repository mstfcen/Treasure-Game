#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <string>

class Matrix
{
private:
void shiftOperator(int orientation,int size,int &verticalIndex,int &horizontalIndex);
protected:
    int** privMatrix;
    int horSize,verSize;

public:
    
    Matrix(int verticalSize,int horizontalSize, std::vector<int>& vect);
    ~Matrix();
    int** getMatrix();
    void multiplyMatrixes(Matrix& keyMatrix,int verticalIndex,int horizontalIndex,std::string outputFileName);
    
};
#endif