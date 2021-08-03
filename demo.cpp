//This program will give a brief demo of the matrix library
#include "matrix.h"

int main(){

    //Declaring new 3x3 matrix object populated initially with all zero(note: matrix dimensions cannot be less than 1)
    matrix* mat = new matrix(3, 3);
    std::cout << "Initialized Matrix: " << std::endl;
    mat -> dispMat();

    //Fill the first row of matrix with 1 and fill the first column of matrix with 1
    mat -> fillrow(1, 1);
    mat -> fillcol(1, 1);

    //Obtaining the value at a sepcified row and column
    std::cout << "Value at row 1 column 2 is: " << mat -> getVal(1, 2) << std::endl;

    std::cout << "Matrix with first row and first column populated with 1s " << std::endl;
    mat -> dispMat();
    
    //Swapping 1st row with second row
    mat -> rowswap(1, 2);
    std::cout << "Matrix with first row and second row swapped" << std::endl;
    mat -> dispMat();

    //Fill matrix with all 1s
    mat -> fillmat(1);
    std::cout << "Matrix filled with all 1s" << std::endl;
    mat -> dispMat();

    //Reseting matrix to all 0s
    mat -> clearmat();
    std::cout << "Matrix cleared and all values reset to 0" << std::endl;
    mat -> dispMat();

    //populating matrix mat with values (note: Matrix index follow conventional mathematical indexing which starts with 1 rather than 0)
    mat -> matedit(1, 1, 1); //The value at row 1 column 1 (the first value starting from the top left) is 1
    mat -> matedit(4, 1, 3); //The value at row 1 column 3 (the first value starting from the top left) is 4
    mat -> matedit(2, 1, 2); //The value at row 1 column 2 (the first value starting from the top left) is 2
    mat -> matedit(5, 2, 1); //The value at row 2 column 1 (the first value starting from the top left) is 5
    mat -> matedit(-3, 2, 2); //The value at row 2 column 2 (the first value starting from the top left) is -3
    mat -> matedit(1, 3, 3); //The value at row 3 column 3 (the first value starting from the top left) is 1
    mat -> matedit(8, 3, 2); //The value at row 3 column 2 (the first value starting from the top left) is 8
    mat -> matedit(6, 3, 1); //The value at row 3 column 1 (the first value starting from the top left) is 6
    mat -> matedit(1, 2, 3); //The value at row 2 column 3 (the first value starting from the top left) is 1
    mat -> matedit(1, 3, 3); //The value at row 1 column 2 (the first value starting from the top left) is 2

    //Display populated matrix to terminal
    std::cout << "Populated Matrix: " << std::endl;
    mat -> dispMat();  

    std::cout << "# of Rows in Matrix: " << mat -> getM() << std::endl;
    std::cout << "# of Columns in Matrix: " << mat -> getN() << std::endl;

    //Convert matrix to Row Echelon Form
    matrix* mat2 = ref(mat);
    std::cout << "Row Echelon Form converted to: " << std::endl;
    mat2 -> dispMat();

    //Convert matrix to Reduced Row Echelon Form
    matrix* mat3 = rref(mat);
    std::cout << "Reduced Row Echelon Form converted to: " << std::endl;
    mat3 -> dispMat();

    //Display Rank and Nullity of Matrix
    std::cout << "Rank of matrix is: " << mat -> rank() << ", and the nullity is: " << mat -> nullity() << std::endl;
    
    //Finding Determinant of matrix
    std::cout << "Det is: " << mat -> findDet() << std::endl;

    //Multiplying 2 matrices

    matrix* a = new matrix(3, 3);
    matrix* b = new matrix(3, 3);
    matrix* x = new matrix(3, 4);

    a -> matedit(1, 1, 1); 
    a -> matedit(4, 1, 3); 
    a -> matedit(2, 1, 2); 
    a -> matedit(5, 2, 1);

    b -> matedit(6, 1, 1); 
    b -> matedit(2, 2, 3); 
    b -> matedit(1, 1, 2); 
    b -> matedit(8, 2, 1);
    b -> matedit(8, 3, 3);
    b -> matedit(8, 3, 1);

    x -> matedit(1, 1, 1); 
    x -> matedit(2, 2, 3); 
    x -> matedit(4, 1, 2); 
    x -> matedit(8, 2, 1);
    x -> matedit(7, 3, 3);
    x -> matedit(19, 3, 1);
    x -> matedit(2, 3, 4);
    x -> matedit(5, 1, 4);
    x -> matedit(8, 2, 4);

    std::cout << "Demonstrating adding two matrices" << std::endl;

    std::cout << "Matrix a: " << std::endl;
    a -> dispMat();

    std::cout << "Matrix b: " << std::endl;
    b -> dispMat();

    std::cout << "Matrix x: " << std::endl;
    x -> dispMat();

    std::cout << "a+b: " << std::endl;
    matrix* c = matadd(a, b);

    c -> dispMat();
    delete c;

    std::cout << "a*b: " << std::endl;
    c = matmult(a, b);

    c -> dispMat();
    delete c;

    std::cout << "a*x: " << std::endl;
    c = matmult(a, x);

    c -> dispMat();
    delete c;

    matrix* d = new matrix(1, 4);
    matrix* e = new matrix(4, 1);

    d -> matedit(3, 1, 1);
    d -> matedit(4, 1, 2);
    d -> matedit(5, 1, 3);
    d -> matedit(6, 1, 4);

    e -> matedit(1, 1, 1);
    e -> matedit(2, 2, 1);
    e -> matedit(3, 3, 1);
    e -> matedit(4, 4, 1);

    std::cout << "Matrix d: " << std::endl;
    d -> dispMat();

    std::cout << "Matrix e: " << std::endl;
    e -> dispMat();


    std::cout << "d * e: " << std::endl;
    c = matmult(d, e);
    c -> dispMat();
    delete c;



    //clearing matrix from memory
    delete mat;
    delete mat2;
    delete mat3;

    return EXIT_SUCCESS;
}