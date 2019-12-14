#ifndef GEOMETRY_H
#define GEOMETRY_H

//------------------------------------------------------------------------
//  Given a point P and a circle of radius R centered at C this function
//  determines the two points on the circle that intersect with the 
//  tangents from P to the circle. Returns false if P is within the circle.
//
//  thanks to Dave Eberly for this one.
//------------------------------------------------------------------------
inline bool GetTangentPoints (Point3F C, double R, Point3F P, Point3F& T1, Point3F& T2)
{
  Point3F PmC = P - C;
   
  

  //double SqrLen = PmC.LengthSq();
  
  double SqrLen = PmC.x * PmC.x + PmC.y * PmC.y;
  
  double RSqr = R*R;
  if ( SqrLen <= RSqr )
  {
      // P is inside or on the circle
      return false;
  }

  double InvSqrLen = 1/SqrLen;
  double Root = sqrt(fabs(SqrLen - RSqr));

  T1.x = C.x + R*(R*PmC.x - PmC.y*Root)*InvSqrLen;
  T1.y = C.y + R*(R*PmC.y + PmC.x*Root)*InvSqrLen;
  T2.x = C.x + R*(R*PmC.x + PmC.y*Root)*InvSqrLen;
  T2.y = C.y + R*(R*PmC.y - PmC.x*Root)*InvSqrLen;

  return true;
}
#endif