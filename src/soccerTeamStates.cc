#include "soccerTeamStates.h"
#include "soccerTeam.h"
#include "fieldPlayer.h"
#include "fieldPlayerStates.h"
#include "T3D/item.h"
#include "goalKeeperStates.h"
#include "soccerBall.h"


FreezeTeam* FreezeTeam::Instance()
{
  static FreezeTeam instance;
  return &instance;
}
void FreezeTeam::enter(SoccerTeam* team)
{
	for (int i = 0; i < team->getNumberOfPlayersOnTeam(); i++) {
       if(team->playerArray[i]->getFSM()->currentState() != Human::Instance())
	   {
	      team->playerArray[i]->getFSM()->changeState(FreezePlayer::Instance());
	      team->playerArray[i]->setMoveDestination(team->playerArray[i]->getPosition(),false);
	   }
	}
}
void FreezeTeam::execute(SoccerTeam* team)
{
	
}
void FreezeTeam::exit(SoccerTeam* team)
{
}

/*------------------------------------------*/


Attacking* Attacking::Instance()
{
  static Attacking instance;
  return &instance;
}
void Attacking::enter(SoccerTeam* team)
{
	//here you should loop thru and tell your players to change their currentHomePoint = attackingHomePoint;.....
	// this way anytime they have nothing to do(i.e. wait() we can setMoveDestination(currentHomePoint,true)
	team->changePlayersToOffensiveHomePoint();

	for (int i = 0; i < (team->getNumberOfPlayersOnTeam()); i++) {
	 // if(!team->playerArray[i]->getHuman())
        team->playerArray[i]->getFSM()->changeState(Wait::Instance());
   }

   //team->playerArray[10]->getFSM()->changeState(Dribble::Instance());
}
void Attacking::execute(SoccerTeam* team)
{
	if(!team->getPossession())
	{ 
		//Con::errorf("change to Defend");
		team->getFSM()->changeState(Defending::Instance());
	}
}
void Attacking::exit(SoccerTeam* team)
{
}

/*------------------------------------------*/
Defending* Defending::Instance()
{
  static Defending instance;
  return &instance;
}
void Defending::enter(SoccerTeam* team)
{
	//here you should loop thru and tell your players to change their currentHomePoint = defendingHomePoint;.....
	// this way anytime they have nothing to do(i.e. wait() we can setMoveDestination(currentHomePoint,true)
	team->changePlayersToDefensiveHomePoint();
}
void Defending::execute(SoccerTeam* team)
{
	if(team->getPossession())
	{
		//Con::errorf("change to Attack");
		team->getFSM()->changeState(Attacking::Instance());
	}
}
void Defending::exit(SoccerTeam* team)
{
}


/*------------------------------------------*/

PrepareForKickOff* PrepareForKickOff::Instance()
{
  static PrepareForKickOff instance;
  return &instance;
}
void PrepareForKickOff::enter(SoccerTeam* team)
{
  team->setControllingPlayer(NULL);  //reset key player pointers 
  team->setSupportingPlayer(NULL);
  team->setReceiver(NULL);
  team->setPlayerClosestToBall(NULL);
  //team->pitch->ball->setVelocity(0,0,0);

  team->sendAllPlayersHome(); // this sets everybody's transform..

  for (int i = 0; i < (team->getNumberOfPlayersOnTeam()); i++) {
	 // if(!team->playerArray[i]->getHuman())
        team->playerArray[i]->getFSM()->changeState(FreezePlayer::Instance());
   }
   if(team->getNumberOfPlayersOnTeam() > 0)
     team->playerArray[0]->getFSM()->changeState(TendGoal::Instance());

}
void PrepareForKickOff::execute(SoccerTeam* team)
{
	if(!team->getPitch()->getRestart()) 
	  team->getFSM()->changeState(Attacking::Instance()); // this instantly sets each teams state machine to attack

	//team->getPitch()->setRestart(false);
}
void PrepareForKickOff::exit(SoccerTeam* team)
{
}

//------------------------------------------------------------------------


SixTopLeftOffenseTeam* SixTopLeftOffenseTeam::Instance()
{
  static SixTopLeftOffenseTeam instance;
  return &instance;
}
void SixTopLeftOffenseTeam::enter(SoccerTeam* team){ }
void SixTopLeftOffenseTeam::execute(SoccerTeam* team)
{

}
void SixTopLeftOffenseTeam::exit(SoccerTeam* team) { }

//------------------------------------------------------------------------


SixTopLeftDefenseTeam* SixTopLeftDefenseTeam::Instance()
{
  static SixTopLeftDefenseTeam instance;
  return &instance;
}
void SixTopLeftDefenseTeam::enter(SoccerTeam* team){ }
void SixTopLeftDefenseTeam::execute(SoccerTeam* team)
{

}
void SixTopLeftDefenseTeam::exit(SoccerTeam* team) { }

//------------------------------------------------------------------------


SixTopRightOffenseTeam* SixTopRightOffenseTeam::Instance()
{
  static SixTopRightOffenseTeam instance;
  return &instance;
}
void SixTopRightOffenseTeam::enter(SoccerTeam* team){ }
void SixTopRightOffenseTeam::execute(SoccerTeam* team)
{

}
void SixTopRightOffenseTeam::exit(SoccerTeam* team) { }

//------------------------------------------------------------------------


SixTopRightDefenseTeam* SixTopRightDefenseTeam::Instance()
{
  static SixTopRightDefenseTeam instance;
  return &instance;
}
void SixTopRightDefenseTeam::enter(SoccerTeam* team){ }
void SixTopRightDefenseTeam::execute(SoccerTeam* team)
{

}
void SixTopRightDefenseTeam::exit(SoccerTeam* team) { }

//------------------------------------------------------------------------


CornerTopLeftOffenseTeam* CornerTopLeftOffenseTeam::Instance()
{
  static CornerTopLeftOffenseTeam instance;
  return &instance;
}
void CornerTopLeftOffenseTeam::enter(SoccerTeam* team){ }
void CornerTopLeftOffenseTeam::execute(SoccerTeam* team)
{

}
void CornerTopLeftOffenseTeam::exit(SoccerTeam* team) { }

//------------------------------------------------------------------------


CornerTopLeftDefenseTeam* CornerTopLeftDefenseTeam::Instance()
{
  static CornerTopLeftDefenseTeam instance;
  return &instance;
}
void CornerTopLeftDefenseTeam::enter(SoccerTeam* team){ }
void CornerTopLeftDefenseTeam::execute(SoccerTeam* team)
{

}
void CornerTopLeftDefenseTeam::exit(SoccerTeam* team) { }

//------------------------------------------------------------------------


CornerTopRightOffenseTeam* CornerTopRightOffenseTeam::Instance()
{
  static CornerTopRightOffenseTeam instance;
  return &instance;
}
void CornerTopRightOffenseTeam::enter(SoccerTeam* team){ }
void CornerTopRightOffenseTeam::execute(SoccerTeam* team)
{

}
void CornerTopRightOffenseTeam::exit(SoccerTeam* team) { }

//------------------------------------------------------------------------


CornerTopRightDefenseTeam* CornerTopRightDefenseTeam::Instance()
{
  static CornerTopRightDefenseTeam instance;
  return &instance;
}
void CornerTopRightDefenseTeam::enter(SoccerTeam* team){ }
void CornerTopRightDefenseTeam::execute(SoccerTeam* team)
{

}
void CornerTopRightDefenseTeam::exit(SoccerTeam* team) { }






/*
ThrowInTeam* ThrowInTeam::Instance()
{
  static ThrowInTeam instance;
  return &instance;
}
void ThrowInTeam::enter(SoccerTeam* team)
{
  team->setControllingPlayer(NULL);  //reset key player pointers 
  team->setSupportingPlayer(NULL);
  team->setReceiver(NULL);

  team->setPossession(!team->getPossession());

  for (int i = 0; i < (team->getNumberOfPlayersOnTeam()); i++) {
	  if(!team->playerArray[i]->getHuman())
        team->playerArray[i]->getFSM()->changeState(ThrowInPlayer::Instance());
   }
}
void ThrowInTeam::execute(SoccerTeam* team)
{
	if(!team->getPitch()->getRestart()) 
	  team->getFSM()->changeState(Attacking::Instance()); // this instantly sets each teams state machine to attack
  
	//team->getPitch()->setRestart(false);
}
void ThrowInTeam::exit(SoccerTeam* team)
{
}



GoalKickTeam* GoalKickTeam::Instance()
{
  static GoalKickTeam instance;
  return &instance;
}
void GoalKickTeam::enter(SoccerTeam* team)
{
  team->setControllingPlayer(NULL);  //reset key player pointers 
  team->setSupportingPlayer(NULL);
  team->setReceiver(NULL);

  team->setPossession(!team->getPossession());

  for (int i = 0; i < (team->getNumberOfPlayersOnTeam()); i++) {
	  if(!team->playerArray[i]->getHuman())
        team->playerArray[i]->getFSM()->changeState(GoalKickPlayer::Instance());
   }
}
void GoalKickTeam::execute(SoccerTeam* team)
{
	if(!team->getPitch()->getRestart()) 
	  team->getFSM()->changeState(Attacking::Instance()); // this instantly sets each teams state machine to attack
  
	//team->getPitch()->setRestart(false);
}
void GoalKickTeam::exit(SoccerTeam* team)
{
}



CornerKickTeam* CornerKickTeam::Instance()
{
  static CornerKickTeam instance;
  return &instance;
}
void CornerKickTeam::enter(SoccerTeam* team)
{
  team->setControllingPlayer(NULL);  //reset key player pointers 
  team->setSupportingPlayer(NULL);
  team->setReceiver(NULL);

  team->setPossession(!team->getPossession());

  for (int i = 0; i < (team->getNumberOfPlayersOnTeam()); i++) {
	  if(!team->playerArray[i]->getHuman())
        team->playerArray[i]->getFSM()->changeState(CornerKickPlayer::Instance());
   }
}
void CornerKickTeam::execute(SoccerTeam* team)
{
	if(!team->getPitch()->getRestart()) 
	  team->getFSM()->changeState(Attacking::Instance()); // this instantly sets each teams state machine to attack
  
	//team->getPitch()->setRestart(false);
}
void CornerKickTeam::exit(SoccerTeam* team)
{
}
*/