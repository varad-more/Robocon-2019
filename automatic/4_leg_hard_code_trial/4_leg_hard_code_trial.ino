
// analog A3,A4,A5,A6

bool link[4][2]={{0,0},{0,0},{0,0},{0,0}};
bool flag[4]={0,0,0,0};


unsigned long timer = 0UL;
const unsigned long t_link[4][2]= {{0,0},{0,0},{0,0},{0,0}};


int l1,l2,l3,l4;

void inst (int,int,int,int);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  if (   flag[0]==0 && flag[1]==0 && flag[2]==0 && flag[3]==0 )
  {
      inst(0,1,2,3);  
  }
  if (  flag[0]==0 && flag[1]==0 && flag[2]==0 && flag[3]==0 )
  {
  inst(1,2,3,0);  
  }
  if (   flag[0]==0 && flag[1]==0 && flag[2]==0 && flag[3]==0 )
  {
  inst(2,3,0,1);  
  }
  if ( flag[0]==0 && flag[1]==0 && flag[2]==0 && flag[3]==0 )
  {
  inst(3,0,1,2);  
  }
  
}

void inst (int l1,int l2,int l3,int l4)
{
   timer=millis();
   if (link[l1][0]==0 && link[l1][0])
   {
    if (millis () - timer );
    // move the actuators 
   }
   if (link[l2][0]==0 && link[l2][0])
   {
    // move the actuators 
   }
   if (link[l3][0]==0 && link[l3][0])
   {
    // move the actuators 
   }
   if (link[l4][0]==0 && link[l4][0])
   {
    // move the actuators 
   } 
   flag[0]=1;flag[1]=1;flag[2]=1;flag[3]=1; 
}
