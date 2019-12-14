#include "ball.h"
#include "vector3D.h"
#include "T3D/gameConnection.h"
#include "math/mMathFn.h"

Ball::Ball() {
   
   mass     = 0.41;
   //friction = .3;
   friction = -0.015;
   throwForce = 0.0;
   
}
   
Ball::~Ball() { }


double Ball::timeToCoverDistance(double distance, double force)
{
  double speed = force / mass;

  //Con::errorf("speed %f", speed);
 //Con::errorf("force %f", force);
  //Con::errorf("mass %f", mass);
  //Con::errorf("Distance %f", DistanceToCover);

  double deceleration = -6;   //forget about friction and just estimate deceleration at 10 m/s
  double term = speed*speed + 2.0*distance*deceleration;
 
  if (term <= 0.0) return -1.0;
  //Con::errorf("term %f", term);

  double v = sqrt(term);

  //Con::errorf("Distance %f", DistanceToCover);
 // Con::errorf("Time %f", (v-speed)/deceleration);

  return (v-speed)/deceleration;
}


double Ball::calculateThrowForce(double distance)
{
//Con::errorf("distance %f", distance);  
	F32 maxForce = 12.3;
    F32 maxDistance = 70;
   
    //double distance = 45;
   
    F32 ratio = distance/maxDistance;
   //Con::errorf("ratio %f", ratio);  
	F32 base = .33;

    F32 exp = mLog(ratio)/mLog(base);

	F32 base2 = .5;
    // Con::errorf("before");
	// Con::errorf("exp %f", exp);  
    double force = maxForce * mPow(base2, exp);

    force = force * 1.2;

	return force;
}