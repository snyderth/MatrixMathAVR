#ifndef _MATRIXMATH_H_
#define _MATRIXMATH_H_

#include <Arduino.h>
#include <ArduinoLPS.h>
#include <stdint.h>

class Vector3f;

class Matrix3f{
    /* A 3x3 matrix implementation for the AVR toolchain */
    public:

        /* Constructor */
        Matrix3f(){}
        Matrix3f(float data[][3]){
            // if(data == NULL){ return; }

            uint8_t i, j;
            // Copy all values
            for(i = 0; i < 3; i++){
                for(j = 0; j < 3; j++){
                    data_[i][j] = data[i][j];
                }
            }
        }
        
        /* Matrix Operations */
        Matrix3f inverse();
        Matrix3f transpose();
        float determinant();
        

        /* Overloaded Operators */
        Matrix3f operator* (const Matrix3f&);
        Matrix3f operator* (const float&);
        Vector3f operator* (const Vector3f&);
        Matrix3f operator+ (const Matrix3f&);
        Matrix3f operator- (const Matrix3f&);
        float& operator() (const uint8_t, const uint8_t);

        // virtual void print() const{
        //     uint8_t i, j;
        //     for(i = 0; i < 3; i++){
        //         for(j = 0; j < 3; j++){
        //             Serial.print(data_[i][j]);
        //             Serial.print("\t");
        //         }
        //         Serial.println();
        //     }
        // }

        /**
         * @brief Returns the 3x3 identity
         * @return Matrix3f object that is the identity
         */
        static Matrix3f Identity(){
            Matrix3f i;

            i << 1, 0, 0,
                 0, 1, 0,
                 0, 0, 1;

            return i;
        }
        /***********************
         * Initializtion:
         * Matrix3f m << 1, 2, 3,
         *               4, 5, 6,
         *               7, 8, 9;
         * 
         * Hints:
         * https://stackoverflow.com/questions/29523119/how-could-comma-separated-initialization-such-as-in-eigen-be-possibly-implemente
         */
        /* Comma Initializer */
        struct Loader{
            Matrix3f& m;
            uint8_t i;
            /* Constructor */
            Loader(Matrix3f& mat, uint8_t index) : m(mat), i(index) {}
            /**
             * @brief Overloaded , operator that recursively loads values
             * to the end of a comma separated list.
             * @return Loader object. This data within the matrix is manipulated
             * because it is passed by reference, allowing the loader to change 
             * the data and be cleaned up.
             */
            Loader operator, (float x) {
                m.data_[i/3][i%3] = x;
                return Loader(m, i+1);
            }
        };
        /* Overloading the << operator */ 
        Loader operator<< (float x){
            data_[0][0] = x;
            return Loader(*this, 1);
        }

    /* Destructor */
    ~Matrix3f(){}
    protected:
        float data_[3][3] = {{0}}; // Initialized to all zeros
        Matrix3f adjugate_(); 
        float determinant2x2_(float[2][2]);

};


/* For typecasting vector3 (in Arduino_LPS) to Vector3f */
// #ifndef vector3
// typedef struct vector3{
//     float x;
//     float y;
//     float z;

//     inline vector3 operator-(vector3 a){
//       return {x - a.x, y - a.y, z - a.z};
//     }

//     inline vector3 operator+(vector3 a){
//       return {x + a.x, y + a.y, z + a.z};
//     }

//     float norm(){
//       return pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2);
//     }

// } vec3;

// typedef vec3 point3;
// #endif

/**
 * A vector is simply a special case of a matrix
 *  _  _        _      _ 
 * | x |       | x 0 0 |
 * | y |   =   | y 0 0 |
 * | z |       | z 0 0 |
 * -   -       --     --
 */
class Vector3f : public Matrix3f{
    public:

        /**
         * Constructors
         */
        /* Default constructor */
        Vector3f():Matrix3f(){}


        /* Constructor with vector value */
        Vector3f(vector3 v):Matrix3f(){
            (*this)(0,0) = v.x;
            (*this)(1,0) = v.y;
            (*this)(2,0) = v.z; 
        }

        /* Constructor with Matrix initializer */
        Vector3f(Matrix3f m):Matrix3f(){
            (*this)(0,0) = m(0,0);
            (*this)(1,0) = m(1,0);
            (*this)(2,0) = m(2,0); 
        }

        /* Constructor with individual init values */
        Vector3f(float x, float y, float z):Matrix3f(){
            (*this)(0,0) = x;
            (*this)(1,0) = y;
            (*this)(2,0) = z; 
        }

        // void print() const{
        //     for(uint8_t i = 0; i < 3; i++){
        //         Serial.print("\t");
        //         Serial.println((*this)[i]);
        //     }
        // }

        /**
         * For comma initialization
         */
        /**
         * @brief A loader struct that loads a single
         * comma separated value via overloading the , operator
         */
        struct Loader{
            Matrix3f& v;
            uint8_t i;
            
            /* Constructor */
            Loader(Matrix3f& vec, uint8_t index) : v(vec), i(index) {}

            /**
             * @brief Overloaded , operator. Recursively reads from the comma
             * list the values that initizalize the vector.
             */ 
            Loader operator, (float x){
                v(i/3, i%3) = x;
                return Loader(v, i+3);
            }
        };
        Loader operator<< (float x){
            this->data_[0][0] = x;
            return Loader(*this, 3);
        }

        /**
         * Access the variables in the vector
         * TODO: Error checking?
         */
        float operator[] (uint8_t i) const{
            // if(i > 2 || i < 0) { return 0.0 };
            return this->data_[i%3][i/3];
        }

        
        /**
         * @brief Compute the magnitude of the vector
         * @return The floating point magnitude of the vector
         */
        float norm(){
            return sqrt(pow((*this)[0], 2) + pow((*this)[1], 2) + pow((*this)[2], 2));
        }

        /**
         * @brief Dot product of two vectors
         */
        float operator* (const Vector3f& v){
            return ( ((*this)[0] * v[0]) 
                    + ((*this)[1] * v[1]) 
                    + ((*this)[2] * v[2]));
        }

        /**
         * @brief Cross product of two vectors
         * | i  j  k |      | a1*b2 - a2*b1 |
         * | a0 a1 a2| =>   | a2*b0 - b2*a0 |
         * | b0 b1 b2|      | a0*b1 - b0*a1 |
         */
        Vector3f operator/ (const Vector3f& vec){
            Vector3f v( (*this)[1] * vec[2] - (*this)[2] * vec[1],
                        (*this)[2] * vec[0] - (*this)[0] * vec[2],
                        (*this)[0] * vec[1] - (*this)[1] * vec[0]);
            return v;
        }


        ~Vector3f(){}

};

#endif