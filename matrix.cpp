#include "matrix.h"

double EPSILON = std::numeric_limits<double>::epsilon() * 1.0e-100;

matrix::matrix(std::size_t m, std::size_t n){

    this -> m = m;
    this -> n = n;
    this -> mat.resize(m);
    for (int i = 0; i < m; i++){
        mat[i].resize(n);
    }
}

matrix::matrix(std::size_t n){

    this -> m = n;
    this -> n = n;
    this -> mat.resize(n);
    for (int i = 0; i < n; i++){
        mat[i].resize(n);
    }
}

std::size_t matrix::getM(){
    return m;
}

std::size_t matrix::getN(){
    return n;
}

std::vector< std::vector<double> >& matrix::getMat(){
    std::vector< std::vector<double> > &a = mat;
    return a;
}

double matrix::getVal(std::size_t row, std::size_t col){
    return mat[row - 1][col - 1];
}

void matrix::matedit(double val, std::size_t row, std::size_t col){ //1 is an error, 0 is not an error
    mat[row - 1][col - 1] = val;
}

void matrix::fillmat(double num){
    for(int i = 0; i < m; i++){
         std::fill(mat[i].begin(), mat[i].end(), num);
    }
}

void matrix::fillrow(std::size_t row, double val){
    for(std::size_t i = 0; i < n; i++){
         mat[row - 1][i] = val;
    }
}

void matrix::fillcol(std::size_t col, double val){
    for(std::size_t i = 0; i < m; i++){
         mat[i][col - 1] = val;
    }
}

void matrix::clearmat(){
    fillmat(0);
}

double matrix::findDet(){ //will find the determinant of a nxn matrix
    if (m != n){
        std::cerr << "Error: Determinant cannot be calculated. Row and Column have different dimensions for method: findDet()" << std::endl;
        exit(-1);
    }

    double det = 0;

    if (n == 1){ //if mat is a 1x1 matrix
        det = mat[0][0];
        return det;
    }

    if (n == 2){ //2x2 matrix
        det = (mat[0][0]*mat[1][1])-(mat[0][1]*mat[1][0]);
        return det;
    }
    
    if (n == 3){ //3x3 matrix, commonly used in many applications so a shortcut is made
        det = mat[0][0]*(mat[1][1]*mat[2][2]-mat[1][2]*mat[2][1])-mat[0][1]*(mat[1][0]*mat[2][2]-mat[1][2]*mat[2][0])+mat[0][2]*(mat[1][0]*mat[2][1]-mat[1][1]*mat[2][0]);
        return det;

    }

    //CODE FOR TAKING CARE OF MATRIX WHOSE DIMENSIONS EXCEEDS 3
    
    for (int i = 0; i < n; i++){ //summation formula
        
        int cx = 0;
        int cy = 0;
        matrix* auxMat = new matrix(n-1);//creates an temporary sub matrix
        
        for (int y = 1; y < n; y++){ //row could be n-1
            cx = 0; //reset x
            
            for (int x = 0; x < n; x++){ //column could be n-1 //index doesnt match, n can be bigger than what the matrix is willing to accept

                if (x == i){ //we will no calculate the column with determina
                    continue;
                }

                auxMat -> mat[cy][cx] = mat[y][x];
                cx += 1;
                if (cx == n-1) break; //if the matrix is filled up
            }

            cy += 1;
            if (cy == n-1) break; //if the y is filled up

        }
    
        //Calculate the determinant
        if (i%2==0){ //i is even
            
                det += mat[0][i]*auxMat -> findDet();

        }else{ //i is odd
                
                det -= mat[0][i]*auxMat -> findDet(); 
            
        }

        delete auxMat;

    }
    
    return det;
}

void matrix::rowswap(std::size_t row1, std::size_t row2){ //swaps two rows of a matrix

    if (row1 == row2) return void();
    double temp = 0;
    for(std::size_t i = 0; i < n; i++){
        temp = mat[row1 - 1][i];
        mat[row1-1][i] = mat[row2-1][i];
        mat[row2-1][i] = temp;

    }

}

int iszerocol(matrix* mat, std::size_t col){

    for(std::size_t i = 1; i < mat->getM(); i++){

        if(mat->getVal(i, col) != 0) return 0;

    }

    return 1;

}

void matrix::dispMat(){

    for(std::size_t i = 0; i < m; i++){

        std::cout << "[ ";

        for(std::size_t j = 0; j < n; j++){

            std::cout << mat[i][j] << ' ';

        }

        std::cout << "]" << std::endl;

    }
}


matrix* ref(matrix* mat){ //makes a copy of a matrix in reduced row echelon form, will return original matrix if matrix is already in rref. Algorithm will be Gaussian elimination

    matrix* rmat = new matrix(mat -> getM(), mat -> getN());
    
    for(int i = 1; i <= rmat->getM(); i++){
        for(int j = 1; j <= rmat->getN(); j++){
            rmat -> matedit(mat -> getVal(i, j), i, j);
        }
    }
    
    //Now to reduce rmat
    std::vector< std::vector <double> > &temp = rmat -> getMat();
    std::size_t x = 0, y = 0;
    double* pivot = &temp[x][y]; //sets the pivot 
    std::size_t c = 1; //signifies what column we are at
    bool begin = 0;

    while(x < rmat->getM() && y < rmat -> getN()){
        if(iszerocol(rmat, c)){
            c++;
            y++;
            continue;
        }

        else if (begin == 0){ //we are at beginning, this step will be used to rowswap all of the rows to their proper place 

            for(std::size_t i = x; i < rmat -> getM(); i++){
                if (std::abs(temp[i][y] - 0) > EPSILON){
                    begin = 1;
                    rmat -> rowswap(i+1, 1);
                    break;
                }
            }

        }
        

        else{ //we have found a nonzero value


            while(std::abs(temp[x][y] - 0) < EPSILON){ //finding leading value
                if (x == rmat -> getM() - 1) break; //we have encountered a zero row
                x++;
            }

            pivot = &temp[x][y];

            for(std::size_t i = x + 1; i < rmat -> getM(); i++){ //for each row
  
                if(std::abs(temp[i][y] - 0) < EPSILON) continue;
                
                double k = temp[i][y] / (*pivot);

                for (std::size_t j = 0; j < rmat->getN(); j++){ //for each column on a given row

                    if (j == y){
                        temp[i][j] = 0;
                        continue;
                    } 

                    temp[i][j] = -1*temp[x][j]*k + temp[i][j];

                }

            }

            //row operations have been performed
            //now we have finished converting the first column
            //Moving on to next row and column

            y++;
            x++;
            c++;

            if (x > rmat -> getM() - 1 || y > rmat -> getN() - 1) break; //we have encountered a zero row

            for(std::size_t i = x; i < rmat -> getM(); i++){

                if (std::abs(temp[i][y] - 0) > EPSILON){
                    rmat -> rowswap(x+1, i+1); //rowswap operation has been performed
                    break;
                }

            }

        }

    }

    //We have reached the end of the matrix
    return rmat;


}

matrix* rref(matrix* mat){

    matrix* rmat = ref(mat);

    std::vector< std::vector <double> > &temp = rmat -> getMat();
    std::size_t x = rmat -> getM() - 1; std::size_t y = rmat -> getN() - 1;

    //Finding leading entry on last row
    for(std::size_t i = rmat -> getN() - 1; i >= 0 && i <= rmat -> getN(); i--){
        if(std::abs(temp[x][i] - 0) > EPSILON){
            y = i;
            break;
        }

    }

    while(x < rmat -> getM() && y < rmat -> getN()){

        for(std::size_t i = 0; i < rmat -> getN(); i++){ //recalculating pivot

            if(std::abs(temp[x][i] - 0) > EPSILON){
                y = i;
                break;
            }

        }

        if(std::abs(temp[x][y] - 0) < EPSILON){
            x--;
            continue;
        }

        double* pivot = &temp[x][y];
        for(std::size_t i = x - 1; i >= 0 && i <= x; i--){

            if(std::abs(temp[i][y] - 0) < EPSILON) continue;

            double k = temp[i][y] / (*pivot);

            for(std::size_t j = 0; j < rmat -> getN(); j++){

                if (j == y){
                    temp[i][j] = 0;
                    continue;
                }
                
                temp[i][j] = (-1)*temp[x][j]*k + temp[i][j];
            }

        }

        //Row operations have been performed

        double pval = *pivot;
        for(std::size_t i = 0; i < rmat -> getN(); i++){
            if (std::abs(temp[x][i] - 0) < EPSILON) continue;
            temp[x][i] = temp[x][i] / pval;

        }

        //Moving on to next row and column
        y--;
        x--;
    
    }
    
    return rmat;

}


std::size_t matrix::rank(){

    matrix* rmat = rref(this);
    std::vector< std::vector <double> > &temp = rmat -> getMat();

    std::size_t nzrowctr = 0;
    for(std::size_t i = 0; i < m; i++){
        int iszero = 1;
        for(std::size_t j = 0; j < n; j++){
            if(std::abs(temp[i][j] - 0) > EPSILON){
                iszero = 0;
                break;
            }
        }

        if (iszero == 0) nzrowctr++;
    }

    delete rmat;
    return nzrowctr;

}

std::size_t matrix::nullity(){
    return n - this->rank();
}

matrix* matadd(matrix* a, matrix* b){

    if (a -> getM() != b -> getM() || a -> getN() != b -> getN()){
        std::cerr << "Error: matrices have different dimensions" << std::endl;
        exit(-1);
    }

    matrix* c = new matrix(a -> getM(), a -> getN());

    for (std::size_t i = 1; i <= a -> getM(); i++){
        for (std::size_t j = 1; j <= a -> getN(); j++){
            c -> matedit(a -> getVal(i, j) + b -> getVal(i, j), i, j);
        }
    }

    return c;

}

matrix* matmult(matrix* a, matrix* b){

    if (a -> getN() != b -> getM()){
        std::cerr << "Error: The number of columns in the first matrix is not equal to the number of rows in the second matrix. Multiplication of the two matrices is impossible" << std::endl;
        exit(-1);
    }

    matrix* c = new matrix(a -> getM(), b -> getN());

    for (std::size_t i = 1; i <= a -> getM(); i++){
        for (std::size_t j = 1; j <= b -> getN(); j++){

            double total = 0;
            for(std::size_t k = 1; k <= a -> getN(); k++){
                total += (a -> getVal(i, k) * b -> getVal(k, j));
            }
            c -> matedit(total, i, j);

        }
    }

    return c;

}
