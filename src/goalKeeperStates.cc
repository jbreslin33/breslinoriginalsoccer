#include "goalKeeper.h"
#include "goalKeeperStates.h"
#include "fieldPlayer.h"
#include "soccerTeam.h"
#include "fieldPlayerStates.h"
//#include "soccer/ball/soccerBall/soccerBall.h"
//#include "soccer/team/soccerTeam/soccerTeam.h"
//#include "math/mMathFn.h"

TendGoal* TendGoal::Instance()
{
  static TendGoal instance;
  return &instance;
}
void TendGoal::enter(FieldPlayer* fieldPlayer)
{
	fieldPlayer->setShapeName("TendGoal");
}
void TendGoal::execute(FieldPlayer* fieldPlayer)
{
	//position goalie between a point on goaline and ball
    Point3F dest = fieldPlayer->Interpose(fieldPlayer->getRearTarget(), fieldPlayer->getDistFromTarget());
    
	//set goalie destination
	fieldPlayer->setMoveDestination(dest, false);

    //keep goalie aimed at ball
	if(fieldPlayer->getMyTeam()->getControllingPlayer())
	  fieldPlayer->setAimObject(fieldPlayer->getMyTeam()->getControllingPlayer());

	//if ball is within a predefined distance, the keeper moves out from
  //position to try and intercept it.
  if (fieldPlayer->ballWithinGoalieRange() && !fieldPlayer->getMyTeam()->isInControl())
  {
    fieldPlayer->getFSM()->changeState(GoaliePursueBall::Instance());
  }
  
}
void TendGoal::exit(FieldPlayer* fieldPlayer)
{
}

/*------------------------------------------*/

GoaliePursueBall* GoaliePursueBall::Instance()
{
  static GoaliePursueBall instance;
  return &instance;
}
void GoaliePursueBall::enter(FieldPlayer* fieldPlayer)
{
	fieldPlayer->setShapeName("GoaliePursueBall");
}
void GoaliePursueBall::execute(FieldPlayer* fieldPlayer)
{
	if(!fieldPlayer->ballWithinGoalieRange())
       fieldPlayer->getFSM()->changeState(TendGoal::Instance());

    if(fieldPlayer->isControllingPlayer())
       fieldPlayer->getFSM()->changeState(PutBallBackInPlay::Instance());


	fieldPlayer->setMoveDestination(fieldPlayer->Pursuit(), false);
  
}
void GoaliePursueBall::exit(FieldPlayer* fieldPlayer)
{
}


PutBallBackInPlay* PutBallBackInPlay::Instance()
{
  static PutBallBackInPlay instance;
  return &instance;
}
void PutBallBackInPlay::enter(FieldPlayer* fieldPlayer)
{
	fieldPlayer->setShapeName("PutBallBackInPlay");
}
void PutBallBackInPlay::execute(FieldPlayer* fieldPlayer)
{
    FieldPlayer* receiver = NULL;

	if( fieldPlayer->getMyTeam()->findPunt(fieldPlayer,receiver,fieldPlayer->getMaxPassingForce(),fieldPlayer->getMyTeam()->getMinPassingDistance())) {
      if (fieldPlayer->getMyTeam()->getReceiver()) {
	    if (!fieldPlayer->getMyTeam()->getReceiver()->getHuman()) {
	      //fieldPlayer->getMyTeam()->getReceiver()->getFSM()->changeState(Receiver::Instance()); //tell the recievr to not move
	      fieldPlayer->getFSM()->changeState(GoalieAiming::Instance()); // start the kick proccess
		}
	  }
	}
  
}
void PutBallBackInPlay::exit(FieldPlayer* fieldPlayer)
{
}


GoalieAiming* GoalieAiming::Instance()
{
  static GoalieAiming instance;
  return &instance;
}
void GoalieAiming::enter(FieldPlayer* fieldPlayer)
{
	fieldPlayer->setShapeName("GoalieAiming");
	fieldPlayer->setMoveDestination(fieldPlayer->getPosition(), false);
	fieldPlayer->setAimLocation(fieldPlayer->getMyTeam()->getTarget());
}
void GoalieAiming::execute(FieldPlayer* fieldPlayer)
{
  if (fieldPlayer->aimAtObject(fieldPlayer->getMyTeam()->getTarget()))
    fieldPlayer->getFSM()->changeState(Punt::Instance());
}
void GoalieAiming::exit(FieldPlayer* fieldPlayer)
{
	
}

Punt* Punt::Instance()
{
  static Punt instance;
  return &instance;
}
void Punt::enter(FieldPlayer* fieldPlayer)
{
    fieldPlayer->setShapeName("Punt");
	fieldPlayer->Kick();
}

void Punt::execute(FieldPlayer* fieldPlayer)
{
 Con::errorf("exectute Punt");
 fieldPlayer->getFSM()->changeState(TendGoal::Instance());
  
}
void Punt::exit(FieldPlayer* fieldPlayer)
{

}