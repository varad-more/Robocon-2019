//Include all libraries
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include "MegunoLink.h"
#include "SimpleKalmanFilter.h"
//volatile int a = 0;
/**********************************************/
//MPU6050 accelgyro; // <--use for AD0 floating
MPU6050 accelgyro(0x69); // <-- use for AD0 high
int e_mea = 1;
float angle;
int e_est = 1;
int q = 1 ;
int l = 0;
int m = 1;
SimpleKalmanFilter kfx11 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfy11 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfx12 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfy12 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfx21 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfy21 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfx22 = SimpleKalmanFilter(e_mea, e_est, q);
SimpleKalmanFilter kfy22 = SimpleKalmanFilter(e_mea, e_est, q);

//e_mea: Measurement Uncertainty - How much do we expect to our measurement vary
//e_est: Estimation Uncertainty - Can be initilized with the same value as e_mea since the kalman filter will adjust its value.
//q: Process Variance - usually a small number between 0.001 and 1 - how fast your measurement moves. Recommended 0.01. Should be tunned to your needs.
//                                                               ^
/**********************************************/
//Declare constants for mpu
int16_t ax, ay, az;
int16_t gx, gy, gz;

//Declaring all the variables

float pi = 3.14159;
float a1 = 0;
float a2 = 39;
float a3 = 0;
float a4 = 39;
float fb1;

volatile int  no_pointer = 380;
volatile float points_leg1[380][2] = {{ 20 , 60 },{ 20 , 59 },{ 20 , 58 },{ 20 , 57 },{ 20 , 56 },{ 20 , 55 },{ 20 , 54 },{ 20 , 53 },{ 20 , 52 },{ 20 , 51 },{ 20 , 50 },{ 20 , 49 },{ 20 , 48 },{ 20 , 47 },{ 20 , 46 },{ 20 , 45 },{ 20 , 44 },{ 20 , 43 },{ 20 , 42 },{ 20 , 41 },{ 19 , 60 },{ 19 , 59 },{ 19 , 58 },{ 19 , 57 },{ 19 , 56 },{ 19 , 55 },{ 19 , 54 },{ 19 , 53 },{ 19 , 52 },{ 19 , 51 },{ 19 , 50 },{ 19 , 49 },{ 19 , 48 },{ 19 , 47 },{ 19 , 46 },{ 19 , 45 },{ 19 , 44 },{ 19 , 43 },{ 19 , 42 },{ 19 , 41 },{ 18 , 60 },{ 18 , 59 },{ 18 , 58 },{ 18 , 57 },{ 18 , 56 },{ 18 , 55 },{ 18 , 54 },{ 18 , 53 },{ 18 , 52 },{ 18 , 51 },{ 18 , 50 },{ 18 , 49 },{ 18 , 48 },{ 18 , 47 },{ 18 , 46 },{ 18 , 45 },{ 18 , 44 },{ 18 , 43 },{ 18 , 42 },{ 18 , 41 },{ 17 , 60 },{ 17 , 59 },{ 17 , 58 },{ 17 , 57 },{ 17 , 56 },{ 17 , 55 },{ 17 , 54 },{ 17 , 53 },{ 17 , 52 },{ 17 , 51 },{ 17 , 50 },{ 17 , 49 },{ 17 , 48 },{ 17 , 47 },{ 17 , 46 },{ 17 , 45 },{ 17 , 44 },{ 17 , 43 },{ 17 , 42 },{ 17 , 41 },{ 16 , 60 },{ 16 , 59 },{ 16 , 58 },{ 16 , 57 },{ 16 , 56 },{ 16 , 55 },{ 16 , 54 },{ 16 , 53 },{ 16 , 52 },{ 16 , 51 },{ 16 , 50 },{ 16 , 49 },{ 16 , 48 },{ 16 , 47 },{ 16 , 46 },{ 16 , 45 },{ 16 , 44 },{ 16 , 43 },{ 16 , 42 },{ 16 , 41 },{ 15 , 60 },{ 15 , 59 },{ 15 , 58 },{ 15 , 57 },{ 15 , 56 },{ 15 , 55 },{ 15 , 54 },{ 15 , 53 },{ 15 , 52 },{ 15 , 51 },{ 15 , 50 },{ 15 , 49 },{ 15 , 48 },{ 15 , 47 },{ 15 , 46 },{ 15 , 45 },{ 15 , 44 },{ 15 , 43 },{ 15 , 42 },{ 15 , 41 },{ 14 , 60 },{ 14 , 59 },{ 14 , 58 },{ 14 , 57 },{ 14 , 56 },{ 14 , 55 },{ 14 , 54 },{ 14 , 53 },{ 14 , 52 },{ 14 , 51 },{ 14 , 50 },{ 14 , 49 },{ 14 , 48 },{ 14 , 47 },{ 14 , 46 },{ 14 , 45 },{ 14 , 44 },{ 14 , 43 },{ 14 , 42 },{ 14 , 41 },{ 13 , 60 },{ 13 , 59 },{ 13 , 58 },{ 13 , 57 },{ 13 , 56 },{ 13 , 55 },{ 13 , 54 },{ 13 , 53 },{ 13 , 52 },{ 13 , 51 },{ 13 , 50 },{ 13 , 49 },{ 13 , 48 },{ 13 , 47 },{ 13 , 46 },{ 13 , 45 },{ 13 , 44 },{ 13 , 43 },{ 13 , 42 },{ 13 , 41 },{ 12 , 60 },{ 12 , 59 },{ 12 , 58 },{ 12 , 57 },{ 12 , 56 },{ 12 , 55 },{ 12 , 54 },{ 12 , 53 },{ 12 , 52 },{ 12 , 51 },{ 12 , 50 },{ 12 , 49 },{ 12 , 48 },{ 12 , 47 },{ 12 , 46 },{ 12 , 45 },{ 12 , 44 },{ 12 , 43 },{ 12 , 42 },{ 12 , 41 },{ 11 , 60 },{ 11 , 59 },{ 11 , 58 },{ 11 , 57 },{ 11 , 56 },{ 11 , 55 },{ 11 , 54 },{ 11 , 53 },{ 11 , 52 },{ 11 , 51 },{ 11 , 50 },{ 11 , 49 },{ 11 , 48 },{ 11 , 47 },{ 11 , 46 },{ 11 , 45 },{ 11 , 44 },{ 11 , 43 },{ 11 , 42 },{ 11 , 41 },{ 10 , 60 },{ 10 , 59 },{ 10 , 58 },{ 10 , 57 },{ 10 , 56 },{ 10 , 55 },{ 10 , 54 },{ 10 , 53 },{ 10 , 52 },{ 10 , 51 },{ 10 , 50 },{ 10 , 49 },{ 10 , 48 },{ 10 , 47 },{ 10 , 46 },{ 10 , 45 },{ 10 , 44 },{ 10 , 43 },{ 10 , 42 },{ 10 , 41 },{ 9 , 60 },{ 9 , 59 },{ 9 , 58 },{ 9 , 57 },{ 9 , 56 },{ 9 , 55 },{ 9 , 54 },{ 9 , 53 },{ 9 , 52 },{ 9 , 51 },{ 9 , 50 },{ 9 , 49 },{ 9 , 48 },{ 9 , 47 },{ 9 , 46 },{ 9 , 45 },{ 9 , 44 },{ 9 , 43 },{ 9 , 42 },{ 9 , 41 },{ 8 , 60 },{ 8 , 59 },{ 8 , 58 },{ 8 , 57 },{ 8 , 56 },{ 8 , 55 },{ 8 , 54 },{ 8 , 53 },{ 8 , 52 },{ 8 , 51 },{ 8 , 50 },{ 8 , 49 },{ 8 , 48 },{ 8 , 47 },{ 8 , 46 },{ 8 , 45 },{ 8 , 44 },{ 8 , 43 },{ 8 , 42 },{ 8 , 41 },{ 7 , 60 },{ 7 , 59 },{ 7 , 58 },{ 7 , 57 },{ 7 , 56 },{ 7 , 55 },{ 7 , 54 },{ 7 , 53 },{ 7 , 52 },{ 7 , 51 },{ 7 , 50 },{ 7 , 49 },{ 7 , 48 },{ 7 , 47 },{ 7 , 46 },{ 7 , 45 },{ 7 , 44 },{ 7 , 43 },{ 7 , 42 },{ 7 , 41 },{ 6 , 60 },{ 6 , 59 },{ 6 , 58 },{ 6 , 57 },{ 6 , 56 },{ 6 , 55 },{ 6 , 54 },{ 6 , 53 },{ 6 , 52 },{ 6 , 51 },{ 6 , 50 },{ 6 , 49 },{ 6 , 48 },{ 6 , 47 },{ 6 , 46 },{ 6 , 45 },{ 6 , 44 },{ 6 , 43 },{ 6 , 42 },{ 6 , 41 },{ 5 , 60 },{ 5 , 59 },{ 5 , 58 },{ 5 , 57 },{ 5 , 56 },{ 5 , 55 },{ 5 , 54 },{ 5 , 53 },{ 5 , 52 },{ 5 , 51 },{ 5 , 50 },{ 5 , 49 },{ 5 , 48 },{ 5 , 47 },{ 5 , 46 },{ 5 , 45 },{ 5 , 44 },{ 5 , 43 },{ 5 , 42 },{ 5 , 41 },{ 4 , 60 },{ 4 , 59 },{ 4 , 58 },{ 4 , 57 },{ 4 , 56 },{ 4 , 55 },{ 4 , 54 },{ 4 , 53 },{ 4 , 52 },{ 4 , 51 },{ 4 , 50 },{ 4 , 49 },{ 4 , 48 },{ 4 , 47 },{ 4 , 46 },{ 4 , 45 },{ 4 , 44 },{ 4 , 43 },{ 4 , 42 },{ 4 , 41 },{ 3 , 60 },{ 3 , 59 },{ 3 , 58 },{ 3 , 57 },{ 3 , 56 },{ 3 , 55 },{ 3 , 54 },{ 3 , 53 },{ 3 , 52 },{ 3 , 51 },{ 3 , 50 },{ 3 , 49 },{ 3 , 48 },{ 3 , 47 },{ 3 , 46 },{ 3 , 45 },{ 3 , 44 },{ 3 , 43 },{ 3 , 42 },{ 3 , 41 },{ 2 , 60 },{ 2 , 59 },{ 2 , 58 },{ 2 , 57 },{ 2 , 56 },{ 2 , 55 },{ 2 , 54 },{ 2 , 53 },{ 2 , 52 },{ 2 , 51 },{ 2 , 50 },{ 2 , 49 },{ 2 , 48 },{ 2 , 47 },{ 2 , 46 },{ 2 , 45 },{ 2 , 44 },{ 2 , 43 },{ 2 , 42 },{ 2 , 41 }};//{{ 20 , 60}, {15, 55}};//, {1, 50}, { -20 , 60 }}; //, { -20, 60} };
volatile float points_leg2[380][2] = {{- 20 , 60 },{- 20 , 59 },{- 20 , 58 },{- 20 , 57 },{- 20 , 56 },{- 20 , 55 },{- 20 , 54 },{- 20 , 53 },{- 20 , 52 },{- 20 , 51 },{- 20 , 50 },{- 20 , 49 },{- 20 , 48 },{- 20 , 47 },{- 20 , 46 },{- 20 , 45 },{- 20 , 44 },{- 20 , 43 },{- 20 , 42 },{- 20 , 41 },{- 19 , 60 },{- 19 , 59 },{- 19 , 58 },{- 19 , 57 },{- 19 , 56 },{- 19 , 55 },{- 19 , 54 },{- 19 , 53 },{- 19 , 52 },{- 19 , 51 },{- 19 , 50 },{- 19 , 49 },{- 19 , 48 },{- 19 , 47 },{- 19 , 46 },{- 19 , 45 },{- 19 , 44 },{- 19 , 43 },{- 19 , 42 },{- 19 , 41 },{- 18 , 60 },{- 18 , 59 },{- 18 , 58 },{- 18 , 57 },{- 18 , 56 },{- 18 , 55 },{- 18 , 54 },{- 18 , 53 },{- 18 , 52 },{- 18 , 51 },{- 18 , 50 },{- 18 , 49 },{- 18 , 48 },{- 18 , 47 },{- 18 , 46 },{- 18 , 45 },{- 18 , 44 },{- 18 , 43 },{- 18 , 42 },{- 18 , 41 },{- 17 , 60 },{- 17 , 59 },{- 17 , 58 },{- 17 , 57 },{- 17 , 56 },{- 17 , 55 },{- 17 , 54 },{- 17 , 53 },{- 17 , 52 },{- 17 , 51 },{- 17 , 50 },{- 17 , 49 },{- 17 , 48 },{- 17 , 47 },{- 17 , 46 },{- 17 , 45 },{- 17 , 44 },{- 17 , 43 },{- 17 , 42 },{- 17 , 41 },{- 16 , 60 },{- 16 , 59 },{- 16 , 58 },{- 16 , 57 },{- 16 , 56 },{- 16 , 55 },{- 16 , 54 },{- 16 , 53 },{- 16 , 52 },{- 16 , 51 },{- 16 , 50 },{- 16 , 49 },{- 16 , 48 },{- 16 , 47 },{- 16 , 46 },{- 16 , 45 },{- 16 , 44 },{- 16 , 43 },{- 16 , 42 },{- 16 , 41 },{- 15 , 60 },{- 15 , 59 },{- 15 , 58 },{- 15 , 57 },{- 15 , 56 },{- 15 , 55 },{- 15 , 54 },{- 15 , 53 },{- 15 , 52 },{- 15 , 51 },{- 15 , 50 },{- 15 , 49 },{- 15 , 48 },{- 15 , 47 },{- 15 , 46 },{- 15 , 45 },{- 15 , 44 },{- 15 , 43 },{- 15 , 42 },{- 15 , 41 },{- 14 , 60 },{- 14 , 59 },{- 14 , 58 },{- 14 , 57 },{- 14 , 56 },{- 14 , 55 },{- 14 , 54 },{- 14 , 53 },{- 14 , 52 },{- 14 , 51 },{- 14 , 50 },{- 14 , 49 },{- 14 , 48 },{- 14 , 47 },{- 14 , 46 },{- 14 , 45 },{- 14 , 44 },{- 14 , 43 },{- 14 , 42 },{- 14 , 41 },{- 13 , 60 },{- 13 , 59 },{- 13 , 58 },{- 13 , 57 },{- 13 , 56 },{- 13 , 55 },{- 13 , 54 },{- 13 , 53 },{- 13 , 52 },{- 13 , 51 },{- 13 , 50 },{- 13 , 49 },{- 13 , 48 },{- 13 , 47 },{- 13 , 46 },{- 13 , 45 },{- 13 , 44 },{- 13 , 43 },{- 13 , 42 },{- 13 , 41 },{- 12 , 60 },{- 12 , 59 },{- 12 , 58 },{- 12 , 57 },{- 12 , 56 },{- 12 , 55 },{- 12 , 54 },{- 12 , 53 },{- 12 , 52 },{- 12 , 51 },{- 12 , 50 },{- 12 , 49 },{- 12 , 48 },{- 12 , 47 },{- 12 , 46 },{- 12 , 45 },{- 12 , 44 },{- 12 , 43 },{- 12 , 42 },{- 12 , 41 },{- 11 , 60 },{- 11 , 59 },{- 11 , 58 },{- 11 , 57 },{- 11 , 56 },{- 11 , 55 },{- 11 , 54 },{- 11 , 53 },{- 11 , 52 },{- 11 , 51 },{- 11 , 50 },{- 11 , 49 },{- 11 , 48 },{- 11 , 47 },{- 11 , 46 },{- 11 , 45 },{- 11 , 44 },{- 11 , 43 },{- 11 , 42 },{- 11 , 41 },{- 10 , 60 },{- 10 , 59 },{- 10 , 58 },{- 10 , 57 },{- 10 , 56 },{- 10 , 55 },{- 10 , 54 },{- 10 , 53 },{- 10 , 52 },{- 10 , 51 },{- 10 , 50 },{- 10 , 49 },{- 10 , 48 },{- 10 , 47 },{- 10 , 46 },{- 10 , 45 },{- 10 , 44 },{- 10 , 43 },{- 10 , 42 },{- 10 , 41 },{- 9 , 60 },{- 9 , 59 },{- 9 , 58 },{- 9 , 57 },{- 9 , 56 },{- 9 , 55 },{- 9 , 54 },{- 9 , 53 },{- 9 , 52 },{- 9 , 51 },{- 9 , 50 },{- 9 , 49 },{- 9 , 48 },{- 9 , 47 },{- 9 , 46 },{- 9 , 45 },{- 9 , 44 },{- 9 , 43 },{- 9 , 42 },{- 9 , 41 },{- 8 , 60 },{- 8 , 59 },{- 8 , 58 },{- 8 , 57 },{- 8 , 56 },{- 8 , 55 },{- 8 , 54 },{- 8 , 53 },{- 8 , 52 },{- 8 , 51 },{- 8 , 50 },{- 8 , 49 },{- 8 , 48 },{- 8 , 47 },{- 8 , 46 },{- 8 , 45 },{- 8 , 44 },{- 8 , 43 },{- 8 , 42 },{- 8 , 41 },{- 7 , 60 },{- 7 , 59 },{- 7 , 58 },{- 7 , 57 },{- 7 , 56 },{- 7 , 55 },{- 7 , 54 },{- 7 , 53 },{- 7 , 52 },{- 7 , 51 },{- 7 , 50 },{- 7 , 49 },{- 7 , 48 },{- 7 , 47 },{- 7 , 46 },{- 7 , 45 },{- 7 , 44 },{- 7 , 43 },{- 7 , 42 },{- 7 , 41 },{- 6 , 60 },{- 6 , 59 },{- 6 , 58 },{- 6 , 57 },{- 6 , 56 },{- 6 , 55 },{- 6 , 54 },{- 6 , 53 },{- 6 , 52 },{- 6 , 51 },{- 6 , 50 },{- 6 , 49 },{- 6 , 48 },{- 6 , 47 },{- 6 , 46 },{- 6 , 45 },{- 6 , 44 },{- 6 , 43 },{- 6 , 42 },{- 6 , 41 },{- 5 , 60 },{- 5 , 59 },{- 5 , 58 },{- 5 , 57 },{- 5 , 56 },{- 5 , 55 },{- 5 , 54 },{- 5 , 53 },{- 5 , 52 },{- 5 , 51 },{- 5 , 50 },{- 5 , 49 },{- 5 , 48 },{- 5 , 47 },{- 5 , 46 },{- 5 , 45 },{- 5 , 44 },{- 5 , 43 },{- 5 , 42 },{- 5 , 41 },{- 4 , 60 },{- 4 , 59 },{- 4 , 58 },{- 4 , 57 },{- 4 , 56 },{- 4 , 55 },{- 4 , 54 },{- 4 , 53 },{- 4 , 52 },{- 4 , 51 },{- 4 , 50 },{- 4 , 49 },{- 4 , 48 },{- 4 , 47 },{- 4 , 46 },{- 4 , 45 },{- 4 , 44 },{- 4 , 43 },{- 4 , 42 },{- 4 , 41 },{- 3 , 60 },{- 3 , 59 },{- 3 , 58 },{- 3 , 57 },{- 3 , 56 },{- 3 , 55 },{- 3 , 54 },{- 3 , 53 },{- 3 , 52 },{- 3 , 51 },{- 3 , 50 },{- 3 , 49 },{- 3 , 48 },{- 3 , 47 },{- 3 , 46 },{- 3 , 45 },{- 3 , 44 },{- 3 , 43 },{- 3 , 42 },{- 3 , 41 },{- 2 , 60 },{- 2 , 59 },{- 2 , 58 },{- 2 , 57 },{- 2 , 56 },{- 2 , 55 },{- 2 , 54 },{- 2 , 53 },{- 2 , 52 },{- 2 , 51 },{- 2 , 50 },{- 2 , 49 },{- 2 , 48 },{- 2 , 47 },{- 2 , 46 },{- 2 , 45 },{- 2 , 44 },{- 2 , 43 },{- 2 , 42 },{- 2 , 41 }};//{{ -20 , 60}, { -15, 55}};//, { -1, 50}, {20, 60}};

int pwm[2][2] = {{2, 3}, {4, 5}};
int driver[2][4] = {{24, 25, 27, 26} , {28, 29, 31, 30}};
int mpu [2][2] = {{40, 41}, {42, 43}};
float T[][4] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
volatile int flag[][4] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
volatile int neg_flag[4] = {0, 0, 0, 0};
volatile int pos_flag[4] = {0, 0, 0, 0};
//volatile float points[9][2] = {{-19.34,54.90},{-17.3,49.96},{-13.4,45.153},{9.8,42.66},{13.7,45.429},{17.2,49.79},{19.3,54.755},{20,60},{-20,60} };
//volatile float points[10][2] = {/*{0, 55.15}, { 0 , 54.15}, { 0, 53.15}, { 0, 52.15}, { 0, 51.15},*/ { 0, 50.15}, { -6, 51.15}, { -8, 52.15}, { -9.17, 53.15}, { -9.8, 54.15}, { -10, 55.15}, { -9.8, 56.15}, { -9.17, 57.15}, { -8, 58.15}, { -6, 59.15}};
//volatile float points[36][2] = { { 0, 55.15}, { 0, 54.15}, { 0, 53.15}, { 0, 52.15}, { 0, 51.15}, { 0, 50.15}, { -6, 51.15}, { -8, 52.15}, { -9.17, 53.15}, { -9.8, 54.15},{-10, 55.15},{ -9, 55.15},{-8,55.15},{-7,55.15},{-6,55.15},{-5,55.15},{-4,55.15},{-3,55.15},{-2,55.15},{-1,55.15},{0,55.15},{1,55.15},{2,55.15},{3,55.15},{4,55.15},{5,55.15},{6,55.15},{7,55.15},{8,55.15},{9,55.15},{10,55.15},{9.8,54.15},{9.17,53.15},{8,52.15},{6,51.15},{0.50.15} };
volatile int pointer = 0;
/*****************************************************************************************************************************/
//Class for leg

//class next_leg
//{
//  Leg current_leg;
//  public:
//
//};
class Leg
{
  public:
    volatile int leg;  //private variable for leg number
    volatile float X;
    volatile float Y;
    volatile float points[3][2];
    friend void chooseleg();
    SimpleKalmanFilter kfx = SimpleKalmanFilter(e_mea, e_est, q);
    SimpleKalmanFilter kfy = SimpleKalmanFilter(e_mea, e_est, q);
    SimpleKalmanFilter kfx1 = SimpleKalmanFilter(e_mea, e_est, q);
    SimpleKalmanFilter kfy1 = SimpleKalmanFilter(e_mea, e_est, q);
    int readIndex[2] = {0, 0};
    int total[2] = {0, 0};

    int numReadings = 10;
    int readings[2][10] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    float  avg1, avg2;
    float fb2 = 0, fb1 = 0;
    float error1 = 0;
    float error2 = 0;
    Leg(int _leg, SimpleKalmanFilter _kfx, SimpleKalmanFilter _kfy, SimpleKalmanFilter _kfx1, SimpleKalmanFilter _kfy1, volatile float _points[][2])
    {
      leg = _leg; //declare public variable
      SimpleKalmanFilter kfx = _kfx;
      SimpleKalmanFilter kfy = _kfy;
      SimpleKalmanFilter kfx1 = _kfx1;
      SimpleKalmanFilter kfy1 = _kfy1;
      for (int i = 0; i < 3; i++)
      {
        for (int j = 0; j < 2; j++)
        {
          points[i][j] = _points[i][j];
        }
      }


    }
    //*************************//
    //gotopos takes X and Y and Goes to that position

    void gotopos(volatile float _X, volatile  float _Y)
    {
      Serial.println("In gotopos");
      X = _X;
      Y = _Y;
      flag[0][leg] = 1;
      flag[1][leg] = 1;
      Serial.print(X);
      Serial.print("  ");
      Serial.print(Y);
    }
    void chosen_fun()
    {
      if  (neg_flag[leg] == 1)
      {
        calculate_neg_angle(X, Y);
        neg_flag[leg] = 0;
      }

      if  (pos_flag[leg] == 1)
      {
        calculate_pos_angle(X, Y);
        pos_flag[leg] = 0;
      }
    }


    //*************************//
    //choose function

    void choose_fn()
    {
      if (X < 0)
      {
        if (flag[0][leg] == 1 || flag[1][leg] == 1)
        {
          neg_flag[leg] = 1;
        }
      }
      else if (X >= 0)
      {
        if (flag[0][leg] == 1 || flag[1][leg] == 1)
        {
          pos_flag[leg] = 1;
        }
      }
      else
      {
        Serial.println("  gotopos not set");
      }
    }

    //*************************//
    //calculates angle for positive X

    void calculate_pos_angle(float X, float Y)
    {
      float r1 = 0;
      float phi1 = 0;
      float phi2 = 0;
      float phi3 = 0;
      r1 = sqrt(X * X + Y * Y);
      phi1 = acos(((a4 * a4) - (a2 * a2) - (r1 * r1)) / (-2.0 * a2 * r1));
      phi2 = atan(Y / X);
      T[0][leg] = phi2 - phi1;
      phi3 = acos(((r1 * r1) - (a2 * a2) - (a4 * a4)) / (-2.0 * a2 * a4));
      T[1][leg] = pi - phi3;
      T[0][leg] = T[0][leg] * 180 / pi;
      T[1][leg] = T[1][leg] * 180 / pi;
      //
      //      r1 = sqrt(X * X + Y * Y);
      //      phi1 = (acos((r1 * r1 + a2 * a2 - a4 * a4) / (2 * a2 * r1))) * 180. / PI;
      //      phi2 = (atan(Y / X)) * 180 / PI;
      //      phi3 = (acos((a2 * a2 + a4 * a4 - r1 * r1) / (2 * a2 * a4))) * 180. / PI;
      //      T[0][leg] = phi1 + phi2;
      //      T[1][leg] = phi3 + T[0][leg] - 180;
      //      T[0][leg] = 180 - T[0][leg] ;/
      //      T[1][leg] = 180 - T[1][leg] ;/
      //steve changes
      //      T[0][leg] = 180 - T[0][leg];
      //      T[1][leg] = 180 - T[1][leg];

      //      T[0][leg] = T[0][leg] - 90;
      /*********************/
      //       r1 = sqrt(X * X + Y * Y);
      //      phi1 = acos(((r1 * r1) + (a2 * a2) - (a4 * a4)) / (2.0 * a2 * r1));
      //      phi2 = atan(Y / X);
      //      phi3 = (acos(((a4 * a4) + (a2 * a2) - (r1 * r1)) / (2.0 * a2 * a4)))*180/PI;
      //      T[0][leg] = (phi2 + phi1)*180/PI;
      //      T[1][leg] = -(phi3 + T[0][leg] - 180);
      onoffcontrol();
    }
    //*************************//
    //calculates angle for niggative X

    void calculate_neg_angle(float X, float Y)
    {
      //Serial.println("In calcneg");
      float r1 = 0;
      float phi1 = 0;
      float phi2 = 0;
      float phi3 = 0;
      X = abs(X);
      r1 = sqrt(X * X + Y * Y);
      phi1 = acos(((a4 * a4) - (a2 * a2) - (r1 * r1)) / (-2.0 * a2 * r1));
      phi2 = atan(-Y / X);
      phi2 = pi + phi2;
      T[0][leg] = phi2 - phi1;
      phi3 = acos(((r1 * r1) - (a2 * a2) - (a4 * a4)) / (-2.0 * a2 * a4));
      T[1][leg] = pi - phi3;
      T[0][leg] = T[0][leg] * 180 / pi;
      T[1][leg] = T[1][leg] * 180 / pi;
      //      T[1/][leg] = phi3 + T[0][leg] - 180;
      //      //steve

      //      r1 = sqrt(X * X + Y * Y);
      //      phi1 = (acos((r1 * r1 + a2 * a2 - a4 * a4) / (2 * a2 * r1))) * 180. / PI;
      //      phi2 = (atan(-Y / X)) * 180 / PI; // Here X is negetive so, in k2 it is multipled by negetive sign.
      //      phi3 = (acos((a2 * a2 + a4 * a4 - r1 * r1) / (2 * a2 * a4))) * 180. / PI;
      //      T[0][leg] = phi1 + phi2;
      //      T[1][leg] = phi3 + T[0][leg] - 180;
      //      T[0][leg] = 180 - T[0][leg] ;/
      //      T[1][leg] = 180 - T[1][leg] ;/

      //   T[0][leg] = 180 - T[0][leg];
      //      T[1][leg] = 180 - T[1][leg]'
      onoffcontrol();
    }
    //*************************//
    //control logic for motion

    void onoffcontrol()
    {
      float Kp1 = 1.3, Kp2 = 45;
      int standard = 150;
      //Read the feedback pot

      digitalWrite(mpu[leg][0], HIGH);
      digitalWrite(mpu[leg][1], LOW);
      accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
      Serial.print("#####################################leg   ");
      Serial.println(leg);

      ax = kfx.updateEstimate(ax);
      az = kfy.updateEstimate(az);
      Serial.print("Link 1   angle=");
      angle = 180 * atan2(ax, az) / PI;
      fb1 = abs(angle) - 5.5 ;
      Serial.print(fb1);
      avg1 = average(fb1, 0);
      Serial.print("   ");
      Serial.print(T[0][leg]);
      digitalWrite(mpu[leg][0], LOW);

      digitalWrite(mpu[leg][1], HIGH);
      accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
      ax = kfx1.updateEstimate(ax);
      az = kfy1.updateEstimate(az);
      Serial.print("Link2   angle=");
      Serial.print(" ");
      angle = 180 * atan2(ax, az) / PI;
      fb2 =  abs(angle);
      fb2 = fb2 - fb1;
      Serial.print(fb2);
      Serial.print(" ");
      Serial.println(T[1][leg]);
      Serial.print(" ");
      avg2 = average(fb2, 1);
      Serial.println(avg1);
      Serial.println(avg2);
      fb1 = avg1;
      fb2 = avg2;
      digitalWrite(mpu[leg][1], LOW);

      //      //Find error
      error1 = T[0][leg] - fb1;
      error2 = T[1][leg] - fb2;
      int pwm1 = (abs(error1) - abs(error2)) * Kp1 + standard;
      int pwm2 = 255;
      //      int pwm1 = int((error1) * Kp1 * (abs(error1) - abs(error2)) + standard);
      //      int pwm2 = int((error2) * Kp2 * (pow(1.7, (-abs(error1) + 20)) + 1) + standard);
      pwm1 = constrain(pwm1, 0, 255);
      //      pwm2 = constrain(pwm2, 0, 255);


      analogWrite(pwm[leg][0], 255); //pwm1);
      analogWrite(pwm[leg][1], 255); //);

      //      Serial.print(" ");
      //      Serial.print(p/wm[leg][0]);
      //      Serial.print(pwm[/leg][1]);
      //Control statements for feedback based motion
      if ((error1) <= 5 && (error1) >=  -5 )
      {
        //hardstop(relay[leg][0], relay[leg][1]);
        analogWrite(pwm[leg][0], 0);
        flag[0][leg] = 0;
        Serial.print(pwm[leg][0]);
        Serial.println("L1 stop");

      }
      else
      {
        flag[0][leg] = 1;
        Serial.println("L1 start");

      }
      if ((error2) <= 5 && (error2) >= -5 )
      {
        analogWrite(pwm[leg][1], 0);
        flag[1][leg] = 0;
        Serial.print(pwm[leg][1]);
        Serial.println("L2 stop");

      }
      else
      {
        flag[1][leg] = 1;
        Serial.println("L2 start");

      }

      if (fb1 < T[0][leg] && fb2 < T[1][leg])
      {
        if (flag[0][leg] == 1)
        {
          //          forward(relay[leg][0], relay[leg][1]);
          backward(driver[leg][0], driver[leg][1]);
          -  Serial.print("link one increase angle"); Serial.print(" "); Serial.print (driver[leg][0]); Serial.print(" "); Serial.print (driver[leg][1]);
        }
        if (flag[1][leg] == 1)
        {
          backward(driver[leg][2], driver[leg][3]);
          Serial.print("link two  increase angle"); Serial.print(" "); Serial.print (driver[leg][2]); Serial.print(" "); Serial.print (driver[leg][3]);
        }
      }
      else if (fb1 < T[0][leg] && fb2 > T[1][leg])
      {
        if (flag[0][leg] == 1)
        {
          //          forward(driver[leg][0], driver[leg][1]);
          backward(driver[leg][0], driver[leg][1]);
          Serial.print("link one  increase angle"); Serial.print(" "); Serial.print (driver[leg][0]); Serial.print(" "); Serial.print (driver[leg][1]);
        }
        if (flag[1][leg] == 1)
        {
          forward(driver[leg][2],  driver[leg][3]);
          Serial.print("link two decrease angle"); Serial.print(" "); Serial.print (driver[leg][2]); Serial.print(" "); Serial.print (driver[leg][3]);
        }
      }
      else if (fb1 > T[0][leg] && fb2 < T[1][leg])
      {
        if (flag[0][leg] == 1)
        {
          //          backward(driver[leg][0], driver[leg][1]);
          forward(driver[leg][0], driver[leg][1]);
          Serial.print("link one decrease angle"); Serial.print(" "); Serial.print (driver[leg][0]); Serial.print(" "); Serial.print (driver[leg][1]);
        }
        if (flag[1][leg] == 1)
        {
          backward(driver[leg][2], driver[leg][3]);

          Serial.print("link two  increase angle"); Serial.print(" "); Serial.print (driver[leg][2]); Serial.print(" "); Serial.print (driver[leg][3]);
        }
      }
      else if (fb1 > T[0][leg]  && fb2 > T[1][leg])
      {
        if (flag[0][leg] == 1)
        {
          //          backward(driver[leg][0], driver[leg][1]);
          forward(driver[leg][0], driver[leg][1]);
          Serial.print("link one decrease angle"); Serial.print(" "); Serial.print (driver[leg][0]); Serial.print(" "); Serial.print (driver[leg][1]);
        }
        if (flag[1][leg] == 1)
        {
          forward(driver[leg][2], driver[leg][3]);
          Serial.print("link two  decrease angle"); Serial.print(" "); Serial.print (driver[leg][2]); Serial.print(" "); Serial.print (driver[leg][3]);
        }
      }
      Serial.print("flag");
      Serial.print(flag[0][leg]);
      Serial.print(flag[1][leg]);
    }
    //*************************//
    //back forward and stop functions

    void backward(int l1, int l2)
    {
      digitalWrite(l1, HIGH);
      digitalWrite(l2, LOW);
    }

    void forward(int l1, int l2)
    {
      digitalWrite(l1, LOW);
      digitalWrite(l2, HIGH);
    }

    void hardstop(int l1, int l2)
    {
      digitalWrite(l1, HIGH);
      digitalWrite(l2, HIGH);
    }
    void check_point()
    {
      //      Serial.println("IN CHECKPOINT");
      if (flag[0][leg] == 0 && flag[1][leg] == 0)
      {
        //        Serial.println("NEXT POINT");
        pointer++;
        Serial.println("####################################################################");
        delay(1000);
        Serial.print("    pointer   " );
        Serial.println(pointer);
        //        int temp_pt=0 ;
        if (pointer >  no_pointer - 1 )
        {
          pointer = 0;

          if (l == 0 && m == 1 )
          {
            l = 1; m = 0;
          }
          else
          {
            l = 0; m = 1;
          }

        }
        gotopos(points[pointer][0], points[pointer][1]);
        // changed by Prathamesh on 17/03/2019
        //          if (temp_pt<pointer)
        //          {
        //           temp_pt++;
        //      .      if (l==0){l=1;}
        //            else {l=0;}
        //          }
        //            if (pointer >  no_pointer - 1 )
        //            {pointer =0; }
        //      gotopos(points[pointer][0], points[pointer][1]);
      }
    }
    float average(int val, int leg)
    {

      //      Serial.println();
      //      for (int o = 0 ; o < 2; o++)
      //      {
      //        for (int p = 0; p < 10; p++)
      //        {
      //          Serial.print(" "); Serial.print(readings[o][p]);
      //        }
      //        Serial.println();
      //      }
      total[leg] = total[leg] - readings[leg][readIndex[leg]];
      // read from the sensor:
      readings[leg][readIndex[leg]] = val;
      // add the reading to the total:
      total[leg] = total[leg] + readings[leg][readIndex[leg]];
      // advance to the next position in the array:
      readIndex[leg] = readIndex[leg] + 1;

      // if we're at the end of the array...
      if (readIndex[leg] >= numReadings) {
        // ...wrap around to the beginning:
        readIndex[leg] = 0;
      }

      // calculate the average:
      return (total[leg] / numReadings);
    }
    //*************************//
};




//*****************************************************************************************************************************//

//Leg leg1 = Leg(0, kfx11, kfy11, kfx12, kfy12, points_leg1);
//Leg leg2 = Leg(1, kfx21, kfy21, kfx22, kfy22, points_leg2);
Leg leg[2] = {Leg(0, kfx11, kfy11, kfx12, kfy12, points_leg1),
              Leg(1, kfx21, kfy21, kfx22, kfy22, points_leg2)
             };
//Leg leg3 = Leg(2);
//Leg leg4 = Leg(3);


//Setup function to setup baud rate pinModes

void setup()
{
  for (int i = 0 ; i < 2; i++)
  {
    for (int j = 0 ; j < 2; j++)
    {
      pinMode(driver[i][j], OUTPUT);
      digitalWrite(driver[i][j], LOW);
    }
  }


  Wire.begin();
  Serial.begin(115200);
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      pinMode(mpu[i][j], OUTPUT);
      digitalWrite(mpu[i][j], LOW);
    }
  }

  digitalWrite(mpu[0][0], HIGH);
  digitalWrite(mpu[0][1], LOW);
  digitalWrite(mpu[1][0], LOW);
  digitalWrite(mpu[1][1], LOW);
  Serial.print("l1l1        ");
  accelgyro.initialize();
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  for (int a = 0; a <= 9; a++)
  {
    float  avg1, angle;
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    ax = leg[0].kfx.updateEstimate(ax);
    az = leg[0].kfy.updateEstimate(az);

    //    Serial.print("Leg1   an/gle=");
    //      Serial.print(ax);
    //      Serial.print(" ");
    angle = 180 * atan2(ax, az) / PI;

    fb1 = abs(angle) - 5.5 ; // fb1=180- abs(angle) -5 ;
    //    Serial.print(fb1/);
    avg1 = leg[0].average(fb1, 0);
  }


  digitalWrite(mpu[0][1], HIGH);
  digitalWrite(mpu[0][0], LOW);
  digitalWrite(mpu[1][0], LOW);
  digitalWrite(mpu[1][1], LOW);
  Serial.println("l1l2     ");
  accelgyro.initialize();
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  for (int a = 0; a <= 9; a++)
  {
    float fb2, avg2, angle;
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    ax = leg[0].kfx1.updateEstimate(ax);
    az = leg[0].kfy1.updateEstimate(az);
    //    Serial.print("Leg2   angle/=");
    //      Serial.print(ax);
    //    Serial.print(" "/);
    angle = 180 * atan2(ax, az) / PI;

    fb2 =  abs(angle);
    fb2 = fb2 - fb1;

    avg2 = leg[0].average(fb2, 1);
  }

  //
  digitalWrite(mpu[1][0], HIGH);
  digitalWrite(mpu[0][1], LOW);
  digitalWrite(mpu[0][0], LOW);
  digitalWrite(mpu[1][1], LOW);
  Serial.print("l2l1    ");
  accelgyro.initialize();
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  for (int a = 0; a <= 9; a++)
  {
    float  avg1, angle;
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    ax = leg[1].kfx.updateEstimate(ax);
    az = leg[1].kfy.updateEstimate(az);

    //    Serial.print("Le/g1   angle=");
    //      Serial.print(ax);
    //      Serial.print(" ");
    angle = 180 * atan2(ax, az) / PI;

    fb1 = abs(angle) - 5.5 ; // fb1=180- abs(angle) -5 ;
    //   / Serial.print(fb1);
    //    /avg1 = leg2.average(fb1, 0);
  }

  digitalWrite(mpu[1][1], HIGH);
  digitalWrite(mpu[0][1], LOW);
  digitalWrite(mpu[1][0], LOW);
  digitalWrite(mpu[0][0], LOW);
  Serial.print("l2l2    ");
  accelgyro.initialize();
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  for (int a = 0; a <= 9; a++)
  {
    float fb2, avg2, angle;
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    ax = leg[1].kfx1.updateEstimate(ax);
    az = leg[1].kfy1.updateEstimate(az);
    //    Serial.print("Leg2   angle=");/
    //      Serial.print(ax);
    //    Serial.print(" ")/;
    angle = 180 * atan2(ax, az) / PI;

    fb2 =  abs(angle);
    fb2 = fb2 - fb1;

    ///avg2 = leg2.average(fb2, 1);
  }
  digitalWrite(mpu[0][0], LOW);
  digitalWrite(mpu[0][1], LOW);
  digitalWrite(mpu[1][0], LOW);
  digitalWrite(mpu[1][1], LOW);


  //Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");


  Serial.println("start");


  // initialize timer1

  noInterrupts();           // disable all interrupts

  TCCR1A = 0 ;

  TCCR1B = 0;

  TCNT1  = 0;

  OCR1A = 5000;            // compare match register 16MHz/256/2Hz

  TCCR1B |= (1 << WGM12);   // CTC mode

  TCCR1B |= (1 << CS12);    // 256 prescaler

  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  //  Serial.print("noint");
  interrupts();             // enable all interrupts
  Serial.println("Set points");
  leg[l].gotopos(-1, 50);
  leg[m].gotopos(1, 50);
  //leg2.gotopos(20, 60);

  Serial.println("done with this ");
  //  leg2.gotopos(-20, 60);
  //  leg3.gotopos(-20, 60);
  //  leg4.gotopos(-20, 60);

}
//*************************//
//ISR

SIGNAL(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
  //  if (digitalRead(2) == HIGH)
  //  {
  cli();
  OCR1A = 3000;
  //Serial.println("In ISR");
  leg[l].choose_fn();
  leg[m].choose_fn();
  // leg2.choose_fn();
  if (flag[0][l] == 0 && flag[1][l] == 0 && flag[0][m] == 0 && flag[1][m] == 0)
  { 
    leg[l].check_point();
    leg[m].check_point();
  }
  // leg2.check_point();
  //  a++;
  sei();
  //  leg2.choose_fn();
  //  leg3.choose_fn();
  //  leg4.choose_fn();
  //  }
}
//*************************//
//loop function


void loop()
{
  //Serial.println("hello");
  //Serial.println(a);
  leg[l].chosen_fun();
  leg[m].chosen_fun();
  //leg2.chosen_fun();


  //*************************//
}
