#ifndef GOAL_H
#define GOAL_H

#include "math/mPoint.h"

class Goal
{

private:

  Point3F   leftPost;
  Point3F   rightPost;

  F32       crossbar;

  //a vector representing the facing direction of the goal
  Point3F   facing;

  //the position of the center of the goal line
  Point3F   center;

  //each time Scored() detects a goal this is incremented
  int       numGoalsScored;

public:

  Goal(Point3F left, Point3F right, Point3F face);


  //-----------------------------------------------------accessor methods
  Point3F getCenter()const{return center;}
  Point3F getFacing()const{return facing;}
  Point3F getLeftPost()const{return leftPost;}
  Point3F getRightPost()const{return rightPost;}
  F32     getCrossbar()const{return crossbar;}

  int      getNumGoalsScored()const{return numGoalsScored;}
  void     resetGoalsScored(){numGoalsScored = 0;}
};

#endif
