#ifndef SOCCERAI_H
#define SOCCERAI_H

#include "T3D/item.h"
#include "soccerPitch.h"


class SoccerAI : public Item
{
   typedef Item Parent;

   public:
      SoccerPitch*          pitch;
	  bool                  start;

      DECLARE_CONOBJECT(SoccerAI);
      SoccerAI();
      ~SoccerAI();
	  void processTick(const Move *move);
	  void setStart(bool b) { start = b; }
	  void setSoccerPitch(SoccerPitch* pitch);
};

#endif