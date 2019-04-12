/*Dont use this \/\/\/\/\/\/\*/
const unsigned long CurrentTimer = millis();
/*\/\/\/\/\/\/\*/
const unsigned long timerRate_l0l0 = 1000UL;
const unsigned long timerRate_l0l1 = 1000UL;
const unsigned long timerRate_l1l0 = 1000UL;
const unsigned long timerRate_l1l1 = 1000UL;
const unsigned long timerRate_l2l0 = 1000UL;
const unsigned long timerRate_l2l1 = 1000UL;
const unsigned long timerRate_l3l0 = 1000UL;
const unsigned long timerRate_l3l1 = 1000UL;

unsigned long timerLast_l0l0 = millis();
unsigned long timerLast_l0l1 = millis();
unsigned long timerLast_l1l0 = millis();
unsigned long timerLast_l1l1 = millis();
unsigned long timerLast_l2l0 = millis();
unsigned long timerLast_l2l1 = millis();
unsigned long timerLast_l3l0 = millis();
unsigned long timerLast_l3l1 = millis();

int flag[4][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};

//int pwm[4][2] = {{13, 12}, {11, 10}, {9, 8}, {7, 6}};
//int driver[4][2] = {{25, 29}, {33, 37}, {41, 45}, {49, 53}};
//int brake[4][2] = {{23, 27}, {31, 35}, {39, 43}, {47, 51}};

int pwm[4][2] = {{5, 6}, {11, 10}, {9, 8}, {7, 6}};
int driver[4][2] = {{10, 8}, {33, 37}, {41, 45}, {49, 53}};
int brake[4][2] = {{11, 9}, {31, 35}, {39, 43}, {47, 51}};

void setup()
{
  Serial.begin(115200);
  digitalWrite(pwm[0][0], HIGH);
  digitalWrite(pwm[0][1], HIGH);
  digitalWrite(pwm[1][0], HIGH);
  digitalWrite(pwm[1][1], HIGH);
  digitalWrite(pwm[2][0], HIGH);
  digitalWrite(pwm[2][1], HIGH);
  digitalWrite(pwm[3][0], HIGH);
  digitalWrite(pwm[3][1], HIGH);
  //  pinMode(13, OUTPUT);
  //  pinMode(12, OUTPUT);
  //  pinMode(25, OUTPUT);
  //  pinMode(29, OUTPUT);
  //  pinMode(23, OUTPUT);
  //  pinMode(27, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop()
{
  //forward(driver[0][1], brake[0][1]);
  //backward(driver[0][0], brake[0][0]);
  //hardstop(brake[0][0]);
  //hardstop(brake[0][1]);
  Serial.println(digitalRead(A3));
}


void backward(int l1, int l2)
{
  // actuator opening
  digitalWrite(l2, LOW);
  digitalWrite(l1, HIGH);

}

void forward(int l1, int l2)
{
  // actuator closing
  digitalWrite(l2, LOW);
  digitalWrite(l1, LOW);

}

void hardstop(int l1)
{
  digitalWrite(l1, HIGH);
}
