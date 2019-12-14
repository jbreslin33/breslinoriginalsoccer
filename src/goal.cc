#include "goal.h"
#include "math/mPoint.h"


Goal::Goal(Point3F left, Point3F right, Point3F face)
{  
   leftPost = left;
   rightPost = right;
   crossbar = 2.67;
   center = (left+right)/2.0;
   facing = face;
   numGoalsScored = 0;

}
