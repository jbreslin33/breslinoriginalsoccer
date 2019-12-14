#ifndef BALL_H
#define BALL_H

#include "math/mPoint.h"


class Ball
{

private:

  double friction;
  double mass;
  double throwForce;
  

public:

	Ball();
    ~Ball();

	double timeToCoverDistance(double distance, double force);
	double getBallFriction() { return friction; }
	double getBallMass() { return mass; }
	double calculateThrowForce(double distance);
	void setThrowForce(double force) { throwForce = force; }
	double getThrowForce() { return throwForce; }
  
};

#endif
