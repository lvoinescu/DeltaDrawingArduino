#include <Servo.h>

double sensorRange = 0.0;

Servo servo1;
Servo servo2;
Servo servo3;

double correz=0; //correction due to the robot geometry errors
double vertical=0;

double xPos = 0;  // x axis position
double yPos = 0; // y axis position
double zPos = 0; // z axis position, negative is up, positive is down. Delta bots are usually used up side down...

double t1;  //servo angle t for 'theta', 1 for servo 1
double t2;
double t3;

// temp variables
double currX = 0;
double currY = 0;
double currZ = 0;
double currT = millis();

double targetX = 0;
double targetY = 0;
double targetZ = 0;


double maxSpeed = 0.04; //0.100// mm / millisec -0.600 is good ^ 0.100 is low, 1.500 is fast
double minSpeed = 0.0001;
double currSpeed= 0;
double acceleration = 0.016; // mm / millisec / millisec - 0.002 keeps the current rig pretty calm, 0.004 starts to be wobbly

int result;
int data = 0;
boolean finitoPercorso = false;  // end of path
boolean finitoMvto = false;  // end of movement

int u=0;

void setup(){
  // attach servos
  servo1.attach(3);
  servo2.attach(6);
  servo3.attach(9);

  Serial.begin(9600);
  goTo( 0,0,-10); // for pen setup
  buildPath(); // build the path of the pen
  u=0;
}


void loop(){
    restart();
    int len = 0;

    
    while(Serial.available() <3) {
      delay(1);
    }
    
    byte startLineByte = Serial.read();
      
    byte len0 = Serial.read();
    byte len1 = Serial.read();
    len = len0 + 256 *len1;
    
  
    for(int i=0; i< len; i++){
      
        while(Serial.available() <4) {
          delay(1);
        }

      
        byte x0 = Serial.read();
        byte x1 = Serial.read();
        //int x = 256 *x1 + x0;      
  
        byte y0 = Serial.read();
        byte y1 = Serial.read();
        //int y = 256 *y1 + y0;

     
         int x = x1<<8 | x0;
         
         int y = y1<<8 | y0;
         
         if(i==0) {
           addPoint(x, y, -10);
         }
         
         addPoint(x, y, 0);
         
         if(i==len-1){
           
           addPoint(x, y, -10);
         }
    }
    

    while(Serial.available() <1) {
      delay(1);
    }
    byte endLineByte = Serial.read();

    while (!finitoPercorso){
      boolean a = loopPath(); // make the path
      while (!finitoMvto){
           boolean b=loopMotion(); // make the movement
      }
      finitoMvto=false;
    }
    
    finitoPercorso = false;

   
    //delay(1000);
  
  Serial.write("RD");
  Serial.flush();

 

 // detach servos
  //servo1.detach();
  //servo2.detach();
  //servo3.detach();


}




