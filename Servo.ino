// from http://code.google.com/p/arduino/source/browse/#svn/trunk/libraries/Servo
#define MIN_PULSE_WIDTH       900.0     // the shortest pulse sent to a servo  
#define MAX_PULSE_WIDTH      2100.0     // the longest pulse sent to a servo 


// limits of servo motion for our rig
int minServoPos = -90;
int maxServoPos = 90;

/////////////////////////////////////////////////////////////////////////
/////////////             goTo                 /////////////////////////
//////////////////////////////////////////////////////////////////////////
void goTo( double x0, double y0, double z0 )
{
  double theta1;
  double theta2;
  double theta3;


  correz=0;    
  //correz=-(x0*x0+y0*y0)/9000*15; 


  vertical=z0+baseZ+correz;
  //vertical=0;

  if( 0 != delta_calcInverse( x0,  y0,  z0*3 + baseZ - correz, theta1, theta2, theta3))
  {
//    Serial.println("Value not correct");  
    return; // no pos
  }


  boolean success = true; 
  success &= transformToServoAngle( theta1, 1 );
  success &= transformToServoAngle( theta2, 2 );
  success &= transformToServoAngle( theta3, 3 );


//  servoWritedouble( &servo1, theta1 + 132);
//  servoWritedouble( &servo2, theta2 + 148);
//  servoWritedouble( &servo3, theta3 + 132); 

  int offset = 120;
//  servoWritedouble( &servo1, theta1 + offset + 14);
//  servoWritedouble( &servo2, theta2 + offset + 28);
//  servoWritedouble( &servo3, theta3 + offset + 6); 

  servoWritedouble( &servo1, theta1 + offset + 14);
  servoWritedouble( &servo2, theta2 + offset + 32);
  servoWritedouble( &servo3, theta3 + offset + 12); 


  t1=theta1;
  t2=theta2;
  t3=theta3;
}


/////////////////////////////////////////////////////////////////////////
/////////////             trasformToServoAngle   /////////////////////////
//////////////////////////////////////////////////////////////////////////
boolean transformToServoAngle( double &theta, int index)
{
  // Our servos go from 0 (max retract) to 120 (full extend, arm in line with servo body) to 170 (overextended)
  // Theta from the geometry maths has 0 with the arm horizontal, -90 at full extend

  theta = -theta;

  boolean success = true;

  if( theta < minServoPos )
  {
    success = false;
    //Serial.print("Theta " +  String(index) + " value not correct"); 
    //Serial.println(theta);
    theta = minServoPos;
  }

  if( theta > maxServoPos )
  {
    success = false;
    //Serial.print("V:"); 
    //Serial.println(theta);
    theta = maxServoPos; 
  }
  return success;
}







/////////////////////////////////////////////////////////////////////////
/////////////             servoWritedouble         /////////////////////////
//////////////////////////////////////////////////////////////////////////
// Use writeMicroseconds instead of write() to get more servo resolution, copy conversion formula from Arduino Servo lib source
// This gets us something like ten times the resolution, so we get much smoother motion 
void servoWritedouble( Servo *s, double angle)
{  

  int uS = MIN_PULSE_WIDTH + angle * ( MAX_PULSE_WIDTH - MIN_PULSE_WIDTH ) / 180.0;      

  s->writeMicroseconds(uS);
}

