#include <Arduino.h>
#include <MatrixMath.h>


Matrix3f a1, a2, a3, a4;
Vector3f b1, b2;

Matrix4f c1, c2, c3, c4;
Vector4f d1, d2;

void setup(){
    float data4[4][4] = {{1, 3, 5, 9},
                         {1, 3, 1, 7},
                         {4, 3, 9, 7},
                         {5, 2, 0,9}};
    float data[3][3] = {{1, 4, 3},
                        {4, 5, 6},
                        {7, 8, 9}};

    c1 = Matrix4f(data4);
    c2 = Matrix4f(data4);
    c4 <<  1, 2, 3, 4,
           5, 6, 7, 8,
           9, 10, 11, 12,
           13, 14, 15, 16;
    d1 << 1, 2, 3, 4;
    a1 = Matrix3f(data);
    a2 = Matrix3f(data);
    a4 << 1, 4, 3, 
          4, 5, 6, 
          7, 8, 9;
          
    b1 << 1, 2, 3;
    Serial.begin(115200);
    a4.print();
    Serial.println();
    b1.print();
    Serial.println();
    c4.print();
    Serial.println();
    d1.print();
    Serial.println();
}

long start = millis();
void loop(){
    Serial.println("================================");
    Serial.println("A1 X A2: ");
    start = micros();
    Matrix3f a3 = a1 * a2;
    long dur = micros() - start;
    a3.print();
    Serial.print("Multiplication takes: ");
    Serial.print(dur);
    Serial.print(" microseconds\n");

    Serial.println("================================");
    Serial.println("A1 inverse:");
    start = micros();
    a3 = a1.inverse();
    dur = micros() - start;
    a3.print();   
    Serial.print("Inverse takes: ");
    Serial.print(dur);
    Serial.print(" microseconds\n");
    Serial.println("================================");
    
    
    Serial.println("A1: ");
    a1.print();
    Serial.println();
    
    start = micros();
    b2 = a1 * b1;
    dur = micros() - start;
    b2.print();
    Serial.print("Matrix-vector mult takes: ");
    Serial.print(dur);
    Serial.print(" microseconds\n");
    Serial.println("================================");

    Serial.println("b1 * b2 (dot product):");
    float dot;
    start = micros();
    dot = b1 * b2;
    dur = micros() - start;
    Serial.println(dot);
    Serial.print("Dot product takes: ");
    Serial.print(dur);
    Serial.print(" microseconds\n");
    Serial.println("================================");

    Serial.print("b1: \n");
    b1.print();
    Serial.print("b2: \n");
    b2.print();

    start = micros();
    b2 = b1 / b2;
    dur = micros() - start;
    Serial.println("b1 X b2:");
    b2.print();
    Serial.print("Dot product takes: ");
    Serial.print(dur);
    Serial.print(" microseconds\n");
    Serial.println("================================");

    Serial.println("================================");
    Serial.println("C1 X C2: ");
    start = micros();
    c3 = c1 * c2;
    dur = micros() - start;
    c3.print();
    Serial.print("Multiplication takes: ");
    Serial.print(dur);
    Serial.print(" microseconds\n");

    Serial.println("================================");
    Serial.println("C1 inverse:");
    start = micros();
    c3 = c1.inverse();
    dur = micros() - start;
    c3.print();   
    Serial.print("Inverse takes: ");
    Serial.print(dur);
    Serial.print(" microseconds\n");
    Serial.println("================================");
    
    Serial.println("C1: ");
    c1.print();
    Serial.println();
    
 
    start = micros();
    d2 = c1 * d1;
    dur = micros() - start;
    d2.print();
    Serial.print("Matrix-vector mult takes: ");
    Serial.print(dur);
    Serial.print(" microseconds\n");
    Serial.println("================================");

    Serial.println("d1 * d2 (dot product):");
    start = micros();
    dot = d1 * d2;
    dur = micros() - start;
    Serial.println(dot);
    Serial.print("Dot product takes: ");
    Serial.print(dur);
    Serial.print(" microseconds\n");
    Serial.println("================================");

    Serial.print("d1: \n");
    d1.print();
    Serial.print("d2: \n");
    d2.print();



    while(1);
}