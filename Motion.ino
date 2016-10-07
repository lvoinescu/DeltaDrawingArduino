/////////////////////////////////////////////////////////////////////////
/////////////             LoopMotion            /////////////////////////
//////////////////////////////////////////////////////////////////////////
boolean loopMotion() // move one increment towards targetXYZ at constant speed
{
  double dx,dy,dz, dt, scale, distance, now;
 
  dx = targetX - currX;
  dy = targetY - currY;
  dz = targetZ - currZ;
  distance = sqrt( (dx*dx) + (dy*dy) + (dz*dz));

  if( distance < 1 ) // arrived
  {
    finitoMvto=true;
    return false;
  }

  now = millis();
  dt =  now - currT;

  if( inBrakingZone(distance))
  {
    currSpeed -= acceleration * dt;
    if( currSpeed < minSpeed )
      currSpeed = minSpeed;
  }
  else if( currSpeed < maxSpeed )
  {
    currSpeed += acceleration * dt;

    if( currSpeed > maxSpeed )
      currSpeed = maxSpeed;
  }

  scale = dt * currSpeed / distance;

  dx = scale * dx;
  dy = scale * dy;
  dz = scale * dz;

  currX += dx;
  currY += dy;
  currZ += dz;

  currT = now;


  goTo( currX, currY, currZ );
  
//    Serial.print(" X:"); Serial.print(currX);Serial.print(" Y:");  
//  Serial.print(currY);Serial.print(" Z:");
//  Serial.print(currZ);
//  Serial.print(" Correz:");Serial.print(correz);Serial.print(" T1:");
//  Serial.print(t1); Serial.print(" T2:");
//  Serial.print(t2); Serial.print(" T3:");
//  Serial.println(t3);   
  finitoMvto = false;
  return true;
}


/////////////////////////////////////////////////////////////////////////
/////////////            inBrakingZone          /////////////////////////
//////////////////////////////////////////////////////////////////////////
boolean inBrakingZone( double distance )
{
  // s = 0.5 a t^2
  // s = 0.5 v t
  // => s = v^2 / 2a
  double s = currSpeed * currSpeed * 0.5 / acceleration;
  return distance < s;
}


/////////////////////////////////////////////////////////////////////////
/////////////             MoveTo                /////////////////////////
//////////////////////////////////////////////////////////////////////////
void moveTo( double x0, double y0, double z0 )
{
  targetX = x0;
  targetY = y0;
  targetZ = z0;
  currSpeed = 0;
}

