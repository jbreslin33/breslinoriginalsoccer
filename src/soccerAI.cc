#include "soccerAI.h"


IMPLEMENT_CO_NETOBJECT_V1(SoccerAI);

void SoccerAI::processTick(const Move* move)
{
PROFILE_START(SoccerAI);
   Parent::processTick(move);
   if(start) // if this is true we know that soccerAI has a pointer to SoccerPitch and we can proceed
     if (pitch->getGameRunning()) // check if the game is started so we can begin the ai chain
       pitch->processUpdate();  // later we may use ai before game starts but for now we are holding off
PROFILE_END();
}


   SoccerAI::SoccerAI() {
	 pitch = NULL;
     start = false;
   }
   SoccerAI::~SoccerAI() { }

void SoccerAI::setSoccerPitch(SoccerPitch* spitch)
{
  pitch = spitch;
  Con::errorf("SoccerAI now has a pointer to SoccerPitch");
}

   ConsoleMethod(SoccerAI, setSoccerPitch, void, 3, 3, "(SoccerPitch obj)"
              "set the SoccerPitch Pointer.")
{
   SoccerPitch* spitch = NULL;
   if (Sim::findObject(dAtoi(argv[2]),spitch))
     object->setSoccerPitch(spitch);
}

ConsoleMethod( SoccerAI, setStart, void, 3, 3,"" "setStart") {
    object->setStart(dAtob(argv[2]));
}