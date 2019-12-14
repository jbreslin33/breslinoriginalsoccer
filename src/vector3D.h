#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "math/mPoint.h"

double vec3DDistanceSq(const Point3F &v1, const Point3F &v2);


Point3F PointToLocalSpace(Point3F point,Point3F AgentHeading, Point3F AgentSide,Point3F AgentPosition);
double LengthSq();

#endif