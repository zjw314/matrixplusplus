#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <vector>
#include <limits>

class matrix{ //This will be a 1-based matrix (the index of the 1st element of the matrix will be at row 1 column 1). 
    private:
        size_t m; //how many rows
        size_t n; //how many columns
        std::vector<std::vector<double> > mat; //actual mxn matrix, which is a 2D vector

    public:
        matrix(size_t m, size_t n); matrix(size_t n);
        size_t getM(); //returns number of rows
        size_t getN(); //returns number of columns
        std::vector< std::vector<double> >& getMat(); //returns a reference to the 2D vector
        double getVal(size_t row, size_t col); //retrives value from the specified row and column
        void matedit(double val, size_t row, size_t col); //edits at the specified row and column with the value
        void fillmat(double val); //fills the matrix with a certain number
        void fillrow(size_t row, double val); //fills a specified row with a double value
        void fillcol(size_t col, double val); //fills a specified column with a double value
        void clearmat(); //resets all elements of matrix to 0
        double findDet(); //finds the determinant of the matrix
        void rowswap(size_t row1, size_t row2); //swaps two specified rows of a matrix
        void dispMat(); //displays matrix
        size_t rank(); //returns rank of matrix
        size_t nullity(); //returns nullity of matrix

};

matrix* ref(matrix* mat); //returns a pointer to a row echelon form of the specified matrix
matrix* rref(matrix* mat); //returns a pointer to the reduced row echelon form of the specified matrix
matrix* matadd(matrix* a, matrix* b);
matrix* matmult(matrix* a, matrix* b);




