#include "MatrixMath.h"


/**
 * @brief A function to transpose the matrix. This is not in place.
 * @return A new matrix instance that is the transposed version of this matrix
 */
Matrix3f Matrix3f::transpose(){
    float newData[3][3] = {{0}};
    uint8_t i = 0, j = 0;
    for(i; i < 3; i++){
        for(j; j < 3; j++){
            newData[i][j] = (*this)(j, i);
        }
    }
    return Matrix3f(newData);
}


/**
 * @brief If the matrix is non-singular (det != 0), returns the inverse
 * @return The inverse of the matrix
 */
Matrix3f Matrix3f::inverse(){
    float det = determinant();
    if(fabs(det) < 0.0001) { return nullptr; }
    Matrix3f adj = adjugate_();
    return adj * (1.0f / det);
}


/**
 * @brief Multiplication overload for multiplying a 3x3 matrix by a 3x1 vector
 * @return The multiplication of the matrix and vector.
 */
Vector3f Matrix3f::operator*(const Vector3f& vec){
    Matrix3f product = (*this) * (Matrix3f)vec;
    return Vector3f(product); 
}


/**
 * @brief A function to calculate the adjugate of the matrix (transpose of the cofactor)
 * @return The adjugate of the matrix.
 */
Matrix3f Matrix3f::adjugate_(){
    float newData[3][3] = {0};
    float detData[2][2] = {0};

    detData[0][0] = (*this)(1, 1);
    detData[0][1] = (*this)(1, 2);
    detData[1][0] = (*this)(2, 1);
    detData[1][1] = (*this)(2, 2);
    newData[0][0] = determinant2x2_(detData);

    detData[0][0] = (*this)(0, 1);
    detData[0][1] = (*this)(0, 2);
    detData[1][0] = (*this)(2, 1);
    detData[1][1] = (*this)(2, 2);
    newData[0][1] = -determinant2x2_(detData);

    detData[0][0] = (*this)(1, 0);
    detData[0][1] = (*this)(1, 1);
    detData[1][0] = (*this)(2, 0);
    detData[1][1] = (*this)(2, 1);
    newData[0][2] = determinant2x2_(detData);

    detData[0][0] = (*this)(1, 0);
    detData[0][1] = (*this)(1, 2);
    detData[1][0] = (*this)(2, 0);
    detData[1][1] = (*this)(2, 2);
    newData[1][0] = -determinant2x2_(detData);

    detData[0][0] = (*this)(0, 0);
    detData[0][1] = (*this)(0, 2);
    detData[1][0] = (*this)(2, 0);
    detData[1][1] = (*this)(2, 2);
    newData[1][1] = determinant2x2_(detData);

    detData[0][0] = (*this)(0, 0);
    detData[0][1] = (*this)(0, 2);
    detData[1][0] = (*this)(1, 0);
    detData[1][1] = (*this)(1, 2);
    newData[1][2] = -determinant2x2_(detData);

    detData[0][0] = (*this)(1, 0);
    detData[0][1] = (*this)(1, 1);
    detData[1][0] = (*this)(2, 0);
    detData[1][1] = (*this)(2, 1);
    newData[2][0] = determinant2x2_(detData);

    detData[0][0] = (*this)(0, 0);
    detData[0][1] = (*this)(0, 1);
    detData[1][0] = (*this)(2, 0);
    detData[1][1] = (*this)(2, 1);
    newData[2][1] = -determinant2x2_(detData);

    detData[0][0] = (*this)(0, 0);
    detData[0][1] = (*this)(0, 1);
    detData[1][0] = (*this)(1, 0);
    detData[1][1] = (*this)(1, 1);
    newData[2][2] = determinant2x2_(detData);


    return Matrix3f(newData);
}


/**
 * @brief A 2x2 determinant
 * @param A 2d 2x2 array whose determinant will be returned
 * @return Returns the determinant of the 2x2 array
 */
float Matrix3f::determinant2x2_(float arr[2][2]){
   return ((arr[0][0] * arr[1][1]) - (arr[1][0] * arr[0][1])); 
}



/**
 * @brief Matrix Multiplication of two matrices
 * @return New 3x3 matrix instance
 */
Matrix3f Matrix3f::operator* (const Matrix3f& a1){
    float newData[3][3] = {0};
    uint8_t i, j, k;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            for(k = 0; k < 3; k++){
                newData[i][j] += (*this)(i, k) * a1.data_[k][j]; 
            }
        }
    }
    return Matrix3f(newData);
}


/**
 * @brief Matrix Addition of two matrices
 * @return New 3x3 matrix instance that is the sum
 */
Matrix3f Matrix3f::operator+ (const Matrix3f& a1){
    float newData[3][3] = {0};
    uint8_t i, j;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            newData[i][j] = (*this)(i, j) + a1.data_[i][j];
        }
    }
    return Matrix3f(newData);
}


/**
 * @brief Returns the determinant of the matrix.
 * @return The determinant of the matrix
 */
float Matrix3f::determinant(){
    float i = this->data_[0][0] * ((this->data_[1][1] * this->data_[2][2]) - (this->data_[1][2] * this->data_[2][1]));
    float j = this->data_[0][1] * ((this->data_[1][0] * this->data_[2][2]) - (this->data_[2][0] * this->data_[1][2]));
    float k = this->data_[0][2] * ((this->data_[1][0] * this->data_[2][1]) - (this->data_[1][1] * this->data_[2][0]));
    return i - j + k;
}


/**
 * @brief Gives access to matrix data values
 * @param i The row index
 * @param j The column index
 * @return The float value at index (i, j) 
 */
float& Matrix3f::operator() (const uint8_t i, const uint8_t j){
    return data_[i][j];
}


/**
 * @brief Matrix subtraction of two matrices
 * @return New 3x3 matrix instance that is the result of the subtraction
 */
Matrix3f Matrix3f::operator- (const Matrix3f& a1){
    float newData[3][3] = {0};
    uint8_t i, j;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            newData[i][j] = (*this)(i, j) - a1.data_[i][j];
        }
    }
    return Matrix3f(newData);
    
}


/**
 * @brief Matrix multiplication by scalar
 * @return new 3x3 matrix instance that is the product.
 */
Matrix3f Matrix3f::operator* (const float& a){
    float newData[3][3] = {{0}};
    uint8_t i, j;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            newData[i][j] = (*this)(i, j) * a;
        }
    }
    return Matrix3f(newData);
}