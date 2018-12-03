#include <Matrix.h>
float a1 = 0;
float a2 = 39;
float a3 = 0;
float a4 = 39;
float pi = 3.14159;
float T1deg = 25;//155;
float T2deg = 120;//240;
float T1 = (T1deg / 180) * pi;
float T2 = (T2deg / 180) * pi;

float hom0_1[4][4] = {{cos(T1), -sin(T1), 0, a2 * cos(T1)}, {sin(T1), cos(T1), 0, a2 * sin(T1)}, {0, 0, 1, a1}, {0, 0, 0, 1}};
Matrix<float> H0_1(4, 4, (float*)hom0_1);

float hom1_2[4][4] = {{cos(T2), -sin(T2), 0, a4 * cos(T2)}, {sin(T2), cos(T2), 0, a4 * sin(T2)}, {0, 0, 1, a3}, {0, 0, 0, 1}};
Matrix<float> H1_2(4, 4, (float*)hom1_2);

Matrix<float> H0_2 = H0_1 * H1_2;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  Serial.println("H0_1:  ");
  H0_1.show();

  Serial.println("H1_2:  ");
  H1_2.show();

  Serial.println("H0_2:  ");
  H0_2.show();
}

void loop() {
  // put your main code here, to run repeatedly:

}
