#ifndef SOCCERBALL_H
#define SOCCERBALL_H

#include "T3D/item.h"

class SoccerBall : public Item
{
   typedef Item Parent;
  

public:
	  
      DECLARE_CONOBJECT(SoccerBall);
      SoccerBall();
      ~SoccerBall();

	  void processTick(const Move *move);

};

#endif
