#include "vector3D.h"
#include "C2DMatrix.h"

double vec3DDistanceSq(const Point3F &v1, const Point3F &v2)
{
  double ySeparation = v2.y - v1.y;
  double xSeparation = v2.x - v1.x;

  return ySeparation*ySeparation + xSeparation*xSeparation;
}


Point3F PointToLocalSpace(Point3F point,
                             Point3F AgentHeading,
                             Point3F AgentSide,
                              Point3F AgentPosition)
{
   //make a copy of the point
   Point3F TransPoint = point;

   //create a transformation matrix
	C2DMatrix matTransform = C2DMatrix();

   double Tx = -mDot(AgentPosition, AgentHeading);
   double Ty = -mDot(AgentPosition, AgentSide);

   //create the transformation matrix
  matTransform._11(AgentHeading.x); matTransform._12(AgentSide.x);
  matTransform._21(AgentHeading.y); matTransform._22(AgentSide.y);
  matTransform._31(Tx);           matTransform._32(Ty);


//now transform the vertices
  matTransform.TransformVector2Ds(TransPoint);

  return TransPoint;

}

