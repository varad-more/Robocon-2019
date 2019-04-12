/*#################################################################BOOM########################################################################*/
/*Dont use this \/\/\/\/\/\/\*/
const unsigned long CurrentTimer = millis();
/*\/\/\/\/\/\/\*/
const unsigned long seq_1_timerRate_l0l0 = 1000UL;
const unsigned long seq_1_timerRate_l0l1 = 1000UL;
const unsigned long seq_1_timerRate_l1l0 = 1000UL;
const unsigned long seq_1_timerRate_l1l1 = 1000UL;
const unsigned long seq_1_timerRate_l2l0 = 1000UL;
const unsigned long seq_1_timerRate_l2l1 = 1000UL;
const unsigned long seq_1_timerRate_l3l0 = 1000UL;
const unsigned long seq_1_timerRate_l3l1 = 1000UL;
/*#################################################################BOOM########################################################################*/
const unsigned long seq_2_timerRate_l0l0 = 1000UL;
const unsigned long seq_2_timerRate_l0l1 = 1000UL;
const unsigned long seq_2_timerRate_l1l0 = 1000UL;
const unsigned long seq_2_timerRate_l1l1 = 1000UL;
const unsigned long seq_2_timerRate_l2l0 = 1000UL;
const unsigned long seq_2_timerRate_l2l1 = 1000UL;
const unsigned long seq_2_timerRate_l3l0 = 1000UL;
const unsigned long seq_2_timerRate_l3l1 = 1000UL;
/*#################################################################BOOM########################################################################*/
const unsigned long seq_3_timerRate_l0l0 = 1000UL;
const unsigned long seq_3_timerRate_l0l1 = 1000UL;
const unsigned long seq_3_timerRate_l1l0 = 1000UL;
const unsigned long seq_3_timerRate_l1l1 = 1000UL;
const unsigned long seq_3_timerRate_l2l0 = 1000UL;
const unsigned long seq_3_timerRate_l2l1 = 1000UL;
const unsigned long seq_3_timerRate_l3l0 = 1000UL;
const unsigned long seq_3_timerRate_l3l1 = 1000UL;
/*#################################################################BOOM########################################################################*/
const unsigned long seq_4_timerRate_l0l0 = 1000UL;
const unsigned long seq_4_timerRate_l0l1 = 1000UL;
const unsigned long seq_4_timerRate_l1l0 = 1000UL;
const unsigned long seq_4_timerRate_l1l1 = 1000UL;
const unsigned long seq_4_timerRate_l2l0 = 1000UL;
const unsigned long seq_4_timerRate_l2l1 = 1000UL;
const unsigned long seq_4_timerRate_l3l0 = 1000UL;
const unsigned long seq_4_timerRate_l3l1 = 1000UL;
/*#################################################################BOOM########################################################################*/

unsigned long timerLast_l0l0 = millis();
unsigned long timerLast_l0l1 = millis();
unsigned long timerLast_l1l0 = millis();
unsigned long timerLast_l1l1 = millis();
unsigned long timerLast_l2l0 = millis();
unsigned long timerLast_l2l1 = millis();
unsigned long timerLast_l3l0 = millis();
unsigned long timerLast_l3l1 = millis();

int flag[4][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};

int pwm[4][2] = {{13, 12}, {11, 10}, {9, 8}, {7, 6}};
int driver[4][2] = {{25, 29}, {33, 37}, {41, 45}, {49, 53}};
int brake[4][2] = {{23, 27}, {31, 35}, {39, 43}, {47, 51}};

//int pwm[4][2] = {{5, 6}, {11, 10}, {9, 8}, {7, 6}};
//int driver[4][2] = {{10, 8}, {33, 37}, {41, 45}, {49, 53}};
//int brake[4][2] = {{11, 9}, {31, 35}, {39, 43}, {47, 51}};

/*#################################################################BOOM########################################################################*/
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
  Serial.println("Aa gaya setup me");
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(29, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(27, OUTPUT);
  //  pinMode(5, OUTPUT);
  //  pinMode(6, OUTPUT);
  //  pinMode(11, OUTPUT);
  //  pinMode(9, OUTPUT);
  //  pinMode(10, OUTPUT);
  //  pinMode(8, OUTPUT);
  Serial.println("Sale ruk 3 sec tak");
  delay(3000);
}
/*#################################################################BOOM########################################################################*/
void loop()
{
  Serial.println("Chal aa gaya loop me");
  seq_init_1();
  seq_1();
  seq_init_2();
  seq_2();
  seq_init_3();
  seq_3();
  seq_init_4();
  seq_4();
}

/*#################################################################BOOM########################################################################*/
void seq_init_1()
{
  Serial.println("seq_init_1");
  flag[0][0] = 0;
  flag[0][1] = 0;
  flag[1][0] = 0;
  flag[1][1] = 0;
  flag[2][0] = 0;
  flag[2][1] = 0;
  flag[3][0] = 0;
  flag[3][1] = 0;

  forward(driver[0][0], brake[0][0]);
  backward(driver[0][1], brake[0][1]);
  //forward(driver[1][0], brake[1][0]);
  //forward(driver[1][1], brake[1][1]);
  //backward(driver[2][0], brake[2][0]);
  //forward(driver[2][1], brake[2][1]);
  //backward(driver[3][0], brake[3][0]);
  //forward(driver[3][1], brake[3][1]);
  Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>_seq_init_1");
}

/*#################################################################BOOM########################################################################*/
void seq_init_2()
{
  Serial.println("seq_init_2");
  flag[0][0] = 0;
  flag[0][1] = 0;
  flag[1][0] = 0;
  flag[1][1] = 0;
  flag[2][0] = 0;
  flag[2][1] = 0;
  flag[3][0] = 0;
  flag[3][1] = 0;

  forward(driver[0][0], brake[0][0]);
  forward(driver[0][1], brake[0][1]);
  //forward(driver[1][0], brake[1][0]);
  //forward(driver[1][1], brake[1][1]);
  //backward(driver[2][0], brake[2][0]);
  //forward(driver[2][1], brake[2][1]);
  //backward(driver[3][0], brake[3][0]);
  //forward(driver[3][1], brake[3][1]);
  Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>_seq_init_2");
}

/*#################################################################BOOM########################################################################*/
void seq_init_3()
{
  Serial.println("seq_init_3");
  flag[0][0] = 0;
  flag[0][1] = 0;
  flag[1][0] = 0;
  flag[1][1] = 0;
  flag[2][0] = 0;
  flag[2][1] = 0;
  flag[3][0] = 0;
  flag[3][1] = 0;

  backward(driver[0][0], brake[0][0]);
  //backward(driver[0][1], brake[0][1]);
  //backward(driver[1][0], brake[1][0]);
  //backward(driver[1][1], brake[1][1]);
  //backward(driver[2][0], brake[2][0]);
  //backward(driver[2][1], brake[2][1]);
  //forward(driver[3][0], brake[3][0]);
  //backward(driver[3][1], brake[3][1]);
  Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>_seq__init_3");
}

/*#################################################################BOOM########################################################################*/
void seq_init_4()
{
  Serial.println("seq_init_4");
  flag[0][0] = 0;
  flag[0][1] = 0;
  flag[1][0] = 0;
  flag[1][1] = 0;
  flag[2][0] = 0;
  flag[2][1] = 0;
  flag[3][0] = 0;
  flag[3][1] = 0;

  //backward(driver[0][0], brake[0][0]);
  backward(driver[0][1], brake[0][1]);
  //backward(driver[1][0], brake[1][0]);
  //forward(driver[1][1], brake[1][1]);
  //forward(driver[2][0], brake[2][0]);
  //forward(driver[2][1], brake[2][1]);
  //forward(driver[3][0], brake[3][0]);
  //forward(driver[3][1], brake[3][1]);
  Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>_seq__init_4");
}

/*#################################################################BOOM########################################################################*/
void seq_1()
{
  timerLast_l0l0 = millis();
  timerLast_l0l1 = millis();
  timerLast_l1l0 = millis();
  timerLast_l1l1 = millis();
  timerLast_l2l0 = millis();
  timerLast_l2l1 = millis();
  timerLast_l3l0 = millis();
  timerLast_l3l1 = millis();

  do {
    Serial.println("seq_1");
    /*Leg 0*/
    if ((millis() - timerLast_l0l0) >= timerRate_l0l0)
    {
      hardstop(brake[0][0]);
      flag[0][0] = 1;
    }
    if ((millis() - timerLast_l0l1) >= timerRate_l0l1)
    {
      hardstop(brake[0][1]);
      flag[0][1] = 1;
    }
    /*Leg 1*/
    if ((millis() - timerLast_l1l0) >= timerRate_l1l0)
    {
      hardstop(brake[1][0]);
      flag[1][0] = 1;
    }
    if ((millis() - timerLast_l1l1) >= timerRate_l1l1)
    {
      hardstop(brake[1][1]);
      flag[1][1] = 1;
    }
    /*Leg 2*/
    if ((millis() - timerLast_l2l0) >= timerRate_l2l0)
    {
      hardstop(brake[2][0]);
      flag[2][0] = 1;
    }
    if ((millis() - timerLast_l2l1) >= timerRate_l2l1)
    {
      hardstop(brake[2][1]);
      flag[2][1] = 1;
    }
    /*Leg 3*/
    if ((millis() - timerLast_l3l0) >= timerRate_l3l0)
    {
      hardstop(brake[3][0]);
      flag[3][0] = 1;
    }
    if ((millis() - timerLast_l3l1) >= timerRate_l3l1)
    {
      hardstop(brake[3][1]);
      flag[3][1] = 1;
    }
    Serial.print(flag[0][0]);
    Serial.print("\t");
    Serial.print(flag[0][1]);
    Serial.print("\t");
    /*Serial.print(flag[1][0]);
      Serial.print("\t");
      Serial.print(flag[1][1]);
      Serial.print("\t");
      Serial.print(flag[2][0]);
      Serial.print("\t");
      Serial.print(flag[2][1]);
      Serial.print("\t");
      Serial.print(flag[3][0]);
      Serial.print("\t");
      Serial.println(flag[3][1]);*/

  } while (!flag[0][0] || !flag[0][1]);// || !flag[1][0] || !flag[1][1] || !flag[2][0] || !flag[2][1] || !flag[3][0] || !flag[3][1]);
  Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>_seq_1");
}

/*#################################################################BOOM########################################################################*/
void seq_2()
{
  timerLast_l0l0 = millis();
  timerLast_l0l1 = millis();
  timerLast_l1l0 = millis();
  timerLast_l1l1 = millis();
  timerLast_l2l0 = millis();
  timerLast_l2l1 = millis();
  timerLast_l3l0 = millis();
  timerLast_l3l1 = millis();

  do {
    Serial.println("seq_2");
    /*Leg 0*/
    if (digitalRead(A3)) //((millis() - timerLast_l0l0) >= timerRate_l0l0)
    {
      hardstop(brake[0][0]);
      flag[0][0] = 1;
    }
    if (digitalRead(A3)) //((millis() - timerLast_l0l1) >= timerRate_l0l1)
    {
      hardstop(brake[0][1]);
      flag[0][1] = 1;
    }
    /*Leg 1*/
    if ((millis() - timerLast_l1l0) >= timerRate_l1l0)
    {
      hardstop(brake[1][0]);
      flag[1][0] = 1;
    }
    if ((millis() - timerLast_l1l1) >= timerRate_l1l1)
    {
      hardstop(brake[1][1]);
      flag[1][1] = 1;
    }
    /*Leg 2*/
    if ((millis() - timerLast_l2l0) >= timerRate_l2l0)
    {
      hardstop(brake[2][0]);
      flag[2][0] = 1;
    }
    if ((millis() - timerLast_l2l1) >= timerRate_l2l1)
    {
      hardstop(brake[2][1]);
      flag[2][1] = 1;
    }
    /*Leg 3*/
    if (digitalRead(A6))//((millis() - timerLast_l3l0) >= timerRate_l3l0)
    {
      hardstop(brake[3][0]);
      flag[3][0] = 1;
    }
    if (digitalRead(A6))//((millis() - timerLast_l3l1) >= timerRate_l3l1)
    {
      hardstop(brake[3][1]);
      flag[3][1] = 1;
    }
    Serial.print(flag[0][0]);
    Serial.print("\t");
    Serial.print(flag[0][1]);
    Serial.print("\t");
    /*Serial.print(flag[1][0]);
      Serial.print("\t");
      Serial.print(flag[1][1]);
      Serial.print("\t");
      Serial.print(flag[2][0]);
      Serial.print("\t");
      Serial.print(flag[2][1]);
      Serial.print("\t");
      Serial.print(flag[3][0]);
      Serial.print("\t");
      Serial.println(flag[3][1]);*/

  } while (!flag[0][0] || !flag[0][1]);// || !flag[1][0] || !flag[1][1] || !flag[2][0] || !flag[2][1] );//|| !flag[3][0] || !flag[3][1]);
  Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>_seq_2");
}

/*#################################################################BOOM########################################################################*/
void seq_3()
{
  timerLast_l0l0 = millis();
  timerLast_l0l1 = millis();
  timerLast_l1l0 = millis();
  timerLast_l1l1 = millis();
  timerLast_l2l0 = millis();
  timerLast_l2l1 = millis();
  timerLast_l3l0 = millis();
  timerLast_l3l1 = millis();

  do {
    Serial.println("seq_3");
    /*Leg 0*/
    if ((millis() - timerLast_l0l0) >= timerRate_l0l0)
    {
      hardstop(brake[0][0]);
      flag[0][0] = 1;
    }
    if ((millis() - timerLast_l0l1) >= timerRate_l0l1)
    {
      hardstop(brake[0][1]);
      flag[0][1] = 1;
    }
    /*Leg 1*/
    if ((millis() - timerLast_l1l0) >= timerRate_l1l0)
    {
      hardstop(brake[1][0]);
      flag[1][0] = 1;
    }
    if ((millis() - timerLast_l1l1) >= timerRate_l1l1)
    {
      hardstop(brake[1][1]);
      flag[1][1] = 1;
    }
    /*Leg 2*/
    if ((millis() - timerLast_l2l0) >= timerRate_l2l0)
    {
      hardstop(brake[2][0]);
      flag[2][0] = 1;
    }
    if ((millis() - timerLast_l2l1) >= timerRate_l2l1)
    {
      hardstop(brake[2][1]);
      flag[2][1] = 1;
    }
    /*Leg 3*/
    if ((millis() - timerLast_l3l0) >= timerRate_l3l0)
    {
      hardstop(brake[3][0]);
      flag[3][0] = 1;
    }
    if ((millis() - timerLast_l3l1) >= timerRate_l3l1)
    {
      hardstop(brake[3][1]);
      flag[3][1] = 1;
    }
    Serial.print(flag[0][0]);
    Serial.print("\t");
    Serial.print(flag[0][1]);
    Serial.print("\t");
    /*Serial.print(flag[1][0]);
      Serial.print("\t");
      Serial.print(flag[1][1]);
      Serial.print("\t");
      Serial.print(flag[2][0]);
      Serial.print("\t");
      Serial.print(flag[2][1]);
      Serial.print("\t");
      Serial.print(flag[3][0]);
      Serial.print("\t");
      Serial.println(flag[3][1]);*/

  } while (!flag[0][0] || !flag[0][1]);// || !flag[1][0] || !flag[1][1] || !flag[2][0] || !flag[2][1] || !flag[3][0] || !flag[3][1]);
  Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>_seq_3");
}

/*#################################################################BOOM########################################################################*/
void seq_4()
{
  timerLast_l0l0 = millis();
  timerLast_l0l1 = millis();
  timerLast_l1l0 = millis();
  timerLast_l1l1 = millis();
  timerLast_l2l0 = millis();
  timerLast_l2l1 = millis();
  timerLast_l3l0 = millis();
  timerLast_l3l1 = millis();

  do {
  Serial.println("seq_4");
    /*Leg 0*/
    if ((millis() - timerLast_l0l0) >= timerRate_l0l0)
    {
      hardstop(brake[0][0]);
      flag[0][0] = 1;
    }
    if ((millis() - timerLast_l0l1) >= timerRate_l0l1)
    {
      hardstop(brake[0][1]);
      flag[0][1] = 1;
    }
    /*Leg 1*/
    if (digitalRead(A4))//((millis() - timerLast_l1l0) >= timerRate_l1l0)
    {
      hardstop(brake[1][0]);
      flag[1][0] = 1;
    }
    if (digitalRead(A4))//((millis() - timerLast_l1l1) >= timerRate_l1l1)
    {
      hardstop(brake[1][1]);
      flag[1][1] = 1;
    }
    /*Leg 2*/
    if (digitalRead(A5))//((millis() - timerLast_l2l0) >= timerRate_l2l0)
    {
      hardstop(brake[2][0]);
      flag[2][0] = 1;
    }
    if (digitalRead(A5))//((millis() - timerLast_l2l1) >= timerRate_l2l1)
    {
      hardstop(brake[2][1]);
      flag[2][1] = 1;
    }
    /*Leg 3*/
    if ((millis() - timerLast_l3l0) >= timerRate_l3l0)
    {
      hardstop(brake[3][0]);
      flag[3][0] = 1;
    }
    if ((millis() - timerLast_l3l1) >= timerRate_l3l1)
    {
      hardstop(brake[3][1]);
      flag[3][1] = 1;
    }
    Serial.print(flag[0][0]);
    Serial.print("\t");
    Serial.print(flag[0][1]);
    Serial.print("\t");
    /*Serial.print(flag[1][0]);
      Serial.print("\t");
      Serial.print(flag[1][1]);
      Serial.print("\t");
      Serial.print(flag[2][0]);
      Serial.print("\t");
      Serial.print(flag[2][1]);
      Serial.print("\t");
      Serial.print(flag[3][0]);
      Serial.print("\t");
      Serial.println(flag[3][1]);*/

  } while (!flag[0][0] || !flag[0][1]);// || !flag[1][0] || !flag[1][1] || !flag[2][0] || !flag[2][1] || !flag[3][0] || !flag[3][1]);
  Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>_seq_4");
}

/*#################################################################BOOM########################################################################*/
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
/*#################################################################BOOM########################################################################*/
