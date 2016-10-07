
// Manage reation and replay of paths for delta bot

// point
struct point
{
  int x,y,z;
};
#define MAX_POINTS 100
struct point points[ MAX_POINTS ];

int nextPoint = -1;
int numPoints = 0;


void restart(){
  nextPoint = -1;
  numPoints = 0;
}

/////////////////////////////////////////////////////////////////////////
/////////////             LoopPath              /////////////////////////
//////////////////////////////////////////////////////////////////////////
boolean loopPath(){

  if( nextPoint+1 >= numPoints )
  {
    finitoPercorso = true;  // done all our work, will never run again
    return false;
  }
  //Serial.print(nextPoint);
  //Serial.print("- Xpoint:");
  //Serial.print(points[nextPoint].x);
  //Serial.print(" Ypoint:");
  //Serial.print(points[nextPoint].y);
  //Serial.print(" Zpoint:");
  //Serial.println(points[nextPoint].z);

  nextPoint ++;
  moveTo(points[nextPoint].x, points[nextPoint].y, points[nextPoint].z);
  finitoPercorso=false;
  return true;
}

/////////////////////////////////////////////////////////////////////////
/////////////             buildPath            /////////////////////////
//////////////////////////////////////////////////////////////////////////
void buildPath()
{
circles();
 //squares();
//center();
  //stopSign(6);
  //circles();


}


/////////////////////////////////////////////////////////////////////////
/////////////             addPoint            /////////////////////////
//////////////////////////////////////////////////////////////////////////
void addPoint( int x, int y, int z )
{
  if( numPoints + 1 >= MAX_POINTS )
    return;

  points[numPoints].x = x;
  points[numPoints].y = y;
  points[numPoints].z = z;

  numPoints ++;
}


void center(){
  for(int i=0; i<2; i++){
    addPoint( 0, 0, -30);
    addPoint( 0, 0, 0);
  }
}


/////////////////////////////////////////////////////////////////////////
/////////////             squares                /////////////////////////
//////////////////////////////////////////////////////////////////////////
void circles()
{
  int l=10;
  for(int i=0; i<10;i++) {
    circle(80,2);
  }
}


/////////////////////////////////////////////////////////////////////////
/////////////             squares                /////////////////////////
//////////////////////////////////////////////////////////////////////////
void squares()
{
  int l=8;
  for(int i=0; i<20;i++) {
    square(10*l);
  }
}

/////////////////////////////////////////////////////////////////////////
/////////////             rectangle             /////////////////////////
//////////////////////////////////////////////////////////////////////////
void rectangle( int x1, int y1, int x2, int y2 )
{
  addPoint( x1, y1,-10);
  addPoint( x1, y1, 0 );

  addPoint( x1, y2, 0 );
  addPoint( x2, y2, 0 );
  addPoint( x2, y1, 0 );

  addPoint( x1, y1, 0 );
  addPoint( x1, y1,-10);

} 

/////////////////////////////////////////////////////////////////////////
/////////////             square                /////////////////////////
//////////////////////////////////////////////////////////////////////////
void square( int x )
{
  //  addPoint( x,x,20);
  addPoint( x, x, 0 );

  addPoint( x, -x, 0 );
  addPoint( -x, -x, 0 );
  addPoint( -x, x, 0 );

  addPoint( x, x, 0 );
  //  addPoint( x,x,20);

} 



void square2( int x )
{
  //  addPoint( x,x,20);
  addPoint( x, 0, 0 );
  addPoint( 0, x, 0 );
  addPoint( -x, 0, 0 );
  addPoint( 0, -x, 0 );

  //addPoint( x, x, 0 );
  //  addPoint( x,x,20);

} 


void line (int x) {
  //  addPoint( x,x,20);
  addPoint( x, x, 0 );  
  addPoint( -x, x, 0 );
  addPoint( x, x, 0 );
}


void stopSign(int l) {

  addPoint( -6 *l, 2 * l, 10);

  addPoint( -6 *l, 2* l, 0);
  addPoint( -2 * l, 6 *l, 0);
  addPoint( 2 * l, 6 *l, 0);
  addPoint( 6 * l, 2 *l, 0);

  addPoint( 6 * l, -2 *l, 0);
  addPoint( 2 * l, -6 *l, 0);
  addPoint( -2 * l, -6 *l, 0);
  addPoint( -6 * l, -2 *l, 0);

  addPoint( -6 *l, 2 * l, 0);


  addPoint( -6 *l, 2 * l, 10);
}


void circleY (int r, int x, float &y) {

  y=sqrt(r * r - x * x);

}


void circle(int r, int pas) {


  for(int i=0;i < 4; i++) {

    int x=0;
    float y ;

    for(x=-r; x < r;x += pas) {
      circleY(r, x, y);
      addPoint(x, y, 0);  
    }

    for(x=r; x > -r;x -= pas) {
      circleY(r, x, y);
      addPoint(x, -y, 0);  
    }

  }

}





