#include "soccerBall.h"
#include "vector3D.h"

IMPLEMENT_CO_NETOBJECT_V1(SoccerBall);

void SoccerBall::processTick(const Move* move)
{

   Parent::processTick(move);
}
   SoccerBall::SoccerBall()
   {
     mNetFlags.set(ScopeAlways | Ghostable);
   }
   
   SoccerBall::~SoccerBall() { }





