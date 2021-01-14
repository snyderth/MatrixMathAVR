#include "MatrixMath.h"


/**
 * @brief A function to transpose the matrix. This is not in place.
 * @return A new matrix instance that is the transposed version of this matrix
 */
Matrix4f Matrix4f::transpose(){
    float newData[4][4] = {{0}};
    uint8_t i = 0, j = 0;
    for(i; i < 4; i++){
        for(j; j < 4; j++){
            newData[i][j] = (*this)(j, i);
        }
    }
    return Matrix4f(newData);
}


/**
 * @brief If the matrix is non-singular (det != 0), returns the inverse
 * @return The inverse of the matrix
 */
Matrix4f Matrix4f::inverse(){
    float det = determinant();
    // NOTE: This segfaults the uC if determinant is zero. How do we stop this?
    if(fabs(det) < 0.000000001) { return nullptr; }
    Matrix4f adj = this->adjugate_();
    return adj * (1.0f / det);
}


/**
 * @brief A function to determine if the matrix is invertible.
 * @return True if the matrix has an inverse
 * @return False if the matrix does not have an inverse
 */
bool Matrix4f::inverseExists(){
    if(fabs(determinant()) < 0.000000001) { return false; }
    return true;
}

/**
 * @brief Multiplication overload for multiplying a 4x4 matrix by a 4x1 vector
 * @return The multiplication of the matrix and vector.
 */
Vector4f Matrix4f::operator*(const Vector4f& vec){
    Matrix4f product = (*this) * (Matrix4f)vec;
    return Vector4f(product); 
}

/**
 * @brief Takes the row,col minor (excludes row and col)
 * @return The minor in matrix3f form
 */
Matrix3f Matrix4f::minor_(int row, int col){
    float newData[3][3] = {0};
    for(uint8_t i = 0; i < 4; i++){ // rows
        for(uint8_t j = 0; j < 4; j++){ // cols
            if(i < row && j < col){
                newData[i][j] = (*this)(i, j);
            }else if(i > row && j > col){
                newData[i-1][j-1] = (*this)(i, j);
            }else if(i > row && j < col){
                newData[i-1][j] = (*this)(i, j);
            }else if(i < row && j > col){
                newData[i][j-1] = (*this)(i, j);
            }

        }
    }
    return Matrix3f(newData);
}
/**
 * @brief A function to calculate the adjugate of the matrix (transpose of the cofactor)
 * @return The adjugate of the matrix.
 */
Matrix4f Matrix4f::adjugate_(){
    float adjData[4][4] = {0};
    float detData[2][2] = {0};
    Matrix4f adj;
    Matrix3f temp;
    for(uint8_t i = 0; i < 4; i++){
        for(uint8_t j = 0; j < 4; j++){
            //Populate minor
            adjData[i][j] = pow(-1, i+j) * minor_(j, i).determinant();
        }
    }
    return Matrix4f(adjData);
}


/**
 * @brief A 2x2 determinant
 * @param A 2d 2x2 array whose determinant will be returned
 * @return Returns the determinant of the 2x2 array
 */
float Matrix4f::determinant2x2_(float arr[2][2]){
   return ((arr[0][0] * arr[1][1]) - (arr[1][0] * arr[0][1])); 
}



/**
 * @brief Matrix Multiplication of two matrices
 * @return New 4x4 matrix instance
 */
Matrix4f Matrix4f::operator* (const Matrix4f& a1){
    float newData[4][4] = {0};
    uint8_t i, j, k;
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            for(k = 0; k < 4; k++){
                newData[i][j] += (*this)(i, k) * a1.data_[k][j]; 
            }
        }
    }
    return Matrix4f(newData);
}


/**
 * @brief Matrix Addition of two matrices
 * @return New 3x3 matrix instance that is the sum
 */
Matrix4f Matrix4f::operator+ (const Matrix4f& a1){
    float newData[4][4] = {0};
    uint8_t i, j;
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            newData[i][j] = (*this)(i, j) + a1.data_[i][j];
        }
    }
    return Matrix4f(newData);
}


/**
 * @brief Returns the determinant of the matrix.
 * @return The determinant of the matrix
 */
float Matrix4f::determinant(){
    Matrix3f tempMinor;
    tempMinor << this->data_[1][1], this->data_[1][2], this->data_[1][3],
                 this->data_[2][1], this->data_[2][2], this->data_[2][3],
                 this->data_[3][1], this->data_[3][2], this->data_[3][3];
    float i = this->data_[0][0] * tempMinor.determinant();
    tempMinor << this->data_[1][0], this->data_[1][2], this->data_[1][3],
                 this->data_[2][0], this->data_[2][2], this->data_[2][3],
                 this->data_[3][0], this->data_[3][2], this->data_[3][3];
    float j = this->data_[0][1] * tempMinor.determinant();
    tempMinor << this->data_[1][0], this->data_[1][1], this->data_[1][3],
                 this->data_[2][0], this->data_[2][1], this->data_[2][3],
                 this->data_[3][0], this->data_[3][1], this->data_[3][3];
    float k = this->data_[0][2] * tempMinor.determinant();
    tempMinor << this->data_[1][0], this->data_[1][1], this->data_[1][2],
                 this->data_[2][0], this->data_[2][1], this->data_[2][2],
                 this->data_[3][0], this->data_[3][1], this->data_[3][2];
    float l = this->data_[0][3] * tempMinor.determinant();
 
    return i - j + k - l;
}


/**
 * @brief Gives access to matrix data values
 * @param i The row index
 * @param j The column index
 * @return The float value at index (i, j) 
 */
float& Matrix4f::operator() (const uint8_t i, const uint8_t j){
    return data_[i][j];
}


/**
 * @brief Matrix subtraction of two matrices
 * @return New 3x3 matrix instance that is the result of the subtraction
 */
Matrix4f Matrix4f::operator- (const Matrix4f& a1){
    float newData[4][4] = {0};
    uint8_t i, j;
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            newData[i][j] = (*this)(i, j) - a1.data_[i][j];
        }
    }
    return Matrix4f(newData);
    
}


/**
 * @brief Matrix multiplication by scalar
 * @return new 4x4 matrix instance that is the product.
 */
Matrix4f Matrix4f::operator* (const float& a){
    float newData[4][4] = {{0}};
    uint8_t i, j;
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            newData[i][j] = (*this)(i, j) * a;
        }
    }
    return Matrix4f(newData);
}