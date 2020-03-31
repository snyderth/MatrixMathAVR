#include <Arduino.h>
#include <MatrixMath.h>


Matrix3f a1, a2, a3, a4;
Vector3f b1, b2;

void setup(){

    float data[3][3] = {{1, 4, 3},
                        {4, 5, 6},
                        {7, 8, 9}};
    
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
 
    while(1);
}
