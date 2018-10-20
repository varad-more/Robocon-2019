#define kp
#define ki 

int  error_flag=0; 
int* motor_changes(double error);
int* calc_motor_speeds(int v, double theta);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  int* difference ;
  double prev_error=0;
  double error = errorcal( lsm_heading, Vector.Direction);
  difference = motor_changes(error, prev_error);
  motor_speed = calc_motor_speeds(Vector.Magnitude, Vector.Direction, &difference ); // done
  set_motor_values(motor_speed, dir);
  prev_error= error ;


}

int* calc_motor_speeds(int v, double theta , int *differnece  )
{
  static int arr[3];
  theta = (double(theta) / 180) * PI;
  arr[0] = abs(v * ((cos(theta) * 0.866) + (sin(theta) * 0.5))) + *diff[0];
  arr[1] = abs(v * ((cos(theta) * 0.866) - (sin(theta) * 0.5))) + *diff[1] ;
  arr[2] = abs(v * sin(theta)) + *diff[2];
  if ((theta < 180 && theta > 120) ||  (theta > -180 && theta < -120))
  {
    arr[2] = 0 ;
  }
  if (arr[0] < 30 && arr[0] >= 0)
  {
    arr[0] = 0;
  }
  if (arr[1] < 30  && arr[1] >= 0)
  {
    arr[1] = 0;
  }
  if (arr[2] < 40 && arr[2] >= 0)
  {
    arr[2] = 0;
  }
  return arr;
}

int* motor_changes(double error, double prev_error )
{
 
 static int diff[3];
  if (error > 0 )
  {
    diff[0] =  (kp(error)+ki(prev_error+error)) ;
    diff[1] =  (kp(error)+ki(prev_error+error)) ;  
    diff[2] =  (kp(error)+ki(prev_error+error));
  error_flag=0;
  }
  else if (error < 0)
  {
    diff[0] =(kp(error)+ki(prev_error+error)) ;
    diff[1] = (kp(error)+ki(prev_error+error));
    diff[2] = (kp(error)+ki(prev_error+error));
  error_flag=1;
  }
  else
  {
    diff[0] = ;
    diff[1] = ;
    diff[2] = ;
  }
  
  return diff ;
}

void write_motor_dir(int MX_dir_r, int MX_dir_l, char dir)
{
  if (dir == 'r' || dir == 'R')
  {
    digitalWrite(MX_dir_r, HIGH);
    digitalWrite(MX_dir_l, LOW);
  }
  else if (dir == 'l' || dir == 'L')
  {
    digitalWrite(MX_dir_r, LOW);
    digitalWrite(MX_dir_l, HIGH);
  }
}

void set_motor_values(int *vel, char *dir)
{
  analogWrite(MA.pwm, vel[0]);
  analogWrite(MB.pwm, vel[1]);
  analogWrite(MC.pwm, vel[2]);
  write_motor_dir(MA.dir_r, MA.dir_l, dir[0]);
  write_motor_dir(MB.dir_r, MB.dir_l, dir[1]);
  write_motor_dir(MC.dir_r, MC.dir_l, dir[2]);
} 
