
#define kp 
#define ki 

bool flag;
double error;

void setup ()
{ 
  

}
//double  error_calc(double,double);
void loop ()
{
  
 
error = error_calc (lsm_heading);    
if (error >0)
{ v[a] = /* this will be added */ 
  v[b] = /*  this will be subtratced */
  v[c] = /* right  direction */
}
else 
{
  v[a] = /* this will be subtracted */
  v[b] = /*  this will be added */
  v[c] = /* left   direction */
} 
}

double error_calc(double lsm_heading  )
{
//  double set_point ;
 if ((lsm_heading> -90 || lsm_heading<90 ) && (Vector.Direction>-90  || Vector>Direction <90)
{
  set_point= Vector.Direction; 
 error = set_point  - lsm_heading ;
  flag = false ; 
}      
 else if (lsm_heading <-90 || lsm_heading >90) && (Vector.Direction <-90 || Vector.Direction >90)
 {
  double lsm_heading_bX;
  set_point= Vector.Direction-180 ;
  error= set_point- lsm_heading ;
  flag= true ;
 }
 
  return error; 
}      
