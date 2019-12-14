#include "fieldPlayerStates.h"
#include "fieldPlayer.h"
#include "soccerBall.h"
#include "soccerTeam.h"
#include "soccerTeamStates.h"
#include "math/mMathFn.h"

ChaseBall* ChaseBall::Instance()
{
  static ChaseBall instance;
  return &instance;
}
void ChaseBall::enter(FieldPlayer* fieldPlayer)
{
	fieldPlayer->setShapeName("ChaseBall");
}
void ChaseBall::execute(FieldPlayer* fieldPlayer)
{
  if (fieldPlayer->getHuman()) {
    fieldPlayer->getFSM()->changeState(Human::Instance());
	return;
  }//this is not getting set sometimes...
  if (fieldPlayer->isControllingPlayer()) { // if your the contolling player change state to dribble
    fieldPlayer->getFSM()->changeState(Dribble::Instance());
    return;
  }
  if(fieldPlayer->isClosestTeamMemberToBall()) { // have player chase down ball
    //fieldPlayer->setMoveDestination(fieldPlayer->getMyTeam()->getPitch()->getBallPosition(), false);
	fieldPlayer->setMoveDestination(fieldPlayer->Pursuit(), false);
  }
  else { // set the players state to wait
    fieldPlayer->getFSM()->changeState(Wait::Instance());
    return;
  }
}
void ChaseBall::exit(FieldPlayer* fieldPlayer)
{
}

/*------------------------------------------*/

PursueBall* PursueBall::Instance()
{
  static PursueBall instance;
  return &instance;
}
void PursueBall::enter(FieldPlayer* fieldPlayer)
{
  fieldPlayer->setShapeName("PursueBall");
}
void PursueBall::execute(FieldPlayer* fieldPlayer)
{
  if (fieldPlayer->getHuman()) {
    fieldPlayer->getFSM()->changeState(Human::Instance());
	return;
  }
  if (fieldPlayer->isControllingPlayer()) { // if your the contolling player change state to dribble
    fieldPlayer->getFSM()->changeState(Dribble::Instance());
	return;
  }
  if (fieldPlayer == fieldPlayer->getMyTeam()->getReceiver()) {
    //fieldPlayer->setMoveDestination(fieldPlayer->getMyTeam()->getPitch()->getBallPosition(),false);
      fieldPlayer->setMoveDestination(fieldPlayer->Pursuit(), false);
  }
  else {
    fieldPlayer->getFSM()->changeState(Wait::Instance());
	return;
  }
}
void PursueBall::exit(FieldPlayer* fieldPlayer)
{
}

/*------------------------------------------*/

KickBall* KickBall::Instance()
{
  static KickBall instance;
  return &instance;
}
void KickBall::enter(FieldPlayer* fieldPlayer)
{
    fieldPlayer->setShapeName("KickBall");
	fieldPlayer->Kick();
}

void KickBall::execute(FieldPlayer* fieldPlayer)
{
 //Con::errorf("exectute kick");
 fieldPlayer->getFSM()->changeState(Wait::Instance());
  
}
void KickBall::exit(FieldPlayer* fieldPlayer)
{

	
}
/*------------------------------------------*/

Wait* Wait::Instance()
{
  static Wait instance;
  return &instance;
}
void Wait::enter(FieldPlayer* fieldPlayer)
{
	fieldPlayer->setShapeName("Wait");
}
void Wait::execute(FieldPlayer* fieldPlayer)
{

  if (fieldPlayer->getMyTeam()->getReceiver() == fieldPlayer) {
    fieldPlayer->getFSM()->changeState(Receiver::Instance());
	return;
  }

  if (fieldPlayer->getHuman()) {
    fieldPlayer->getFSM()->changeState(Human::Instance());
	return;
  }
  if (fieldPlayer->isControllingPlayer()) { // if your the contolling player change state to dribble
	fieldPlayer->getFSM()->changeState(Dribble::Instance());
	return;
  }
  if(fieldPlayer->isClosestTeamMemberToBall() && !fieldPlayer->getMyTeam()->getPossession()) { // if your closest
	if (!fieldPlayer->isControllingPlayer()) { // and don't already have ball
   	  fieldPlayer->getFSM()->changeState(ChaseBall::Instance()); // then hustle up and get the ball
	  return;
	}
  }
  // if you dont' have a specific task goto your currently assigned Home point need 
  // this getHomePoint is what will get Changed in the team states so we can better seperate the logic...
  //fieldPlayer->setMoveDestination(fieldPlayer->getCurrentHomePoint(),true);
  else { 
    if(fieldPlayer->getMyTeam()->getFSM()->currentState() == Attacking::Instance())
	  fieldPlayer->setMoveDestination(fieldPlayer->getOffenseDestination(),true);
	else
      fieldPlayer->setMoveDestination(fieldPlayer->getDefenseDestination(),true);
  }
}
void Wait::exit(FieldPlayer* fieldPlayer)
{
}
/*------------------------------------------*/
DefensiveBase* DefensiveBase::Instance()
{
  static DefensiveBase instance;
  return &instance;
}
void DefensiveBase::enter(FieldPlayer* fieldPlayer)
{
	fieldPlayer->setShapeName("DefensiveBase");
}
void DefensiveBase::execute(FieldPlayer* fieldPlayer)
{
  if (fieldPlayer->getHuman()) {
    fieldPlayer->getFSM()->changeState(Human::Instance());
	return;
  }
}
void DefensiveBase::exit(FieldPlayer* fieldPlayer)
{
}
/*------------------------------------------*/
Dribble* Dribble::Instance()
{
  static Dribble instance;
  return &instance;
}
void Dribble::enter(FieldPlayer* fieldPlayer)
{
	fieldPlayer->setShapeName("Dribble");
}

void Dribble::execute(FieldPlayer* fieldPlayer)
{
  if (fieldPlayer->getHuman()) {
    fieldPlayer->getFSM()->changeState(Human::Instance());
	return;
  }
  FieldPlayer* receiver = NULL;  // local vars that buckland uses notice he is not modyfying the class member variables for reciever
  
  if (!fieldPlayer->isControllingPlayer()) { // and don't already have ball
    fieldPlayer->getFSM()->changeState(Wait::Instance()); // then hustle up and get the ball
	return;
  }
/*
  if (fieldPlayer->insideShootingZone()) {  
    if( fieldPlayer->getMyTeam()->canShoot(fieldPlayer, 15)) {
      fieldPlayer->getFSM()->changeState(Aiming::Instance()); // start the kick proccess
    }
  }
*/
  if( fieldPlayer->getMyTeam()->findPass(fieldPlayer,receiver,fieldPlayer->getMaxPassingForce(),fieldPlayer->getMyTeam()->getMinAirPassingDistance())) {
    if (fieldPlayer->getMyTeam()->getReceiver()) {
	  if (!fieldPlayer->getMyTeam()->getReceiver()->getHuman()) {
	    //fieldPlayer->getMyTeam()->getReceiver()->getFSM()->changeState(Receiver::Instance()); //tell the recievr to not move
	    fieldPlayer->getFSM()->changeState(Aiming::Instance()); // start the kick proccess
	  }
	}
	else {
	  //Con::errorf("RecievingPlayer == NULL");
	}
  }
  else {
	  fieldPlayer->setMoveDestination(fieldPlayer->getMyTeam()->getOpponent()->getGoalPoint(), false);
  }

}
void Dribble::exit(FieldPlayer* fieldPlayer)
{
}
/*------------------------------------------*/
Human* Human::Instance()
{
  static Human instance;
  return &instance;
}
void Human::enter(FieldPlayer* fieldPlayer)
{
	fieldPlayer->setShapeName("Human");
}
void Human::execute(FieldPlayer* fieldPlayer)
{
  if (!fieldPlayer->getHuman()) {
    fieldPlayer->getFSM()->changeState(Wait::Instance());
	return;
  }
}
void Human::exit(FieldPlayer* fieldPlayer)
{
}
/*------------------------------------------*/
FreezePlayer* FreezePlayer::Instance()
{
  static FreezePlayer instance;
  return &instance;
}
void FreezePlayer::enter(FieldPlayer* fieldPlayer)
{
	fieldPlayer->setShapeName("Freeze");
}
void FreezePlayer::execute(FieldPlayer* fieldPlayer)
{
    Point3F dest = fieldPlayer->getPosition();
	fieldPlayer->setMoveDestination(dest, false);	
}
void FreezePlayer::exit(FieldPlayer* fieldPlayer)
{
}
/*------------------------------------------*/
Aiming* Aiming::Instance()
{
  static Aiming instance;
  return &instance;
}
void Aiming::enter(FieldPlayer* fieldPlayer)
{
	fieldPlayer->setShapeName("Aiming");
	fieldPlayer->setMoveDestination(fieldPlayer->getPosition(), false);
	fieldPlayer->setAimLocation(fieldPlayer->getMyTeam()->getTarget());
}
void Aiming::execute(FieldPlayer* fieldPlayer)
{
  if (fieldPlayer->getHuman()) {
    fieldPlayer->getFSM()->changeState(Human::Instance());
	return;
  }
  if (fieldPlayer->aimAtObject(fieldPlayer->getMyTeam()->getTarget()))
    fieldPlayer->getFSM()->changeState(KickBall::Instance());
}
void Aiming::exit(FieldPlayer* fieldPlayer)
{
	
}

Square* Square::Instance()
{
  static Square instance;
  return &instance;
}
void Square::enter(FieldPlayer* fieldPlayer)
{
	fieldPlayer->setShapeName("Square");
}
void Square::execute(FieldPlayer* fieldPlayer)
{
  if (fieldPlayer->getHuman()) {
    fieldPlayer->getFSM()->changeState(Human::Instance());
	return;
  }
  if (fieldPlayer->isControllingPlayer()) { // if your the contolling player change state to dribble
    fieldPlayer->getFSM()->changeState(Dribble::Instance());
	return;
  }
  if(fieldPlayer->isClosestTeamMemberToBall()) { // if your closest
	if (!fieldPlayer->isControllingPlayer()) { // and don't already have ball
   	  fieldPlayer->getFSM()->changeState(ChaseBall::Instance()); // then hustle up and get the ball
	  return;
	}
  }
  else { // if you dont' have a specific task goto your currently assigned Home point need 
		// this getHomePoint is what will get Changed in the team states so we can better seperate the logic...
		//fieldPlayer->setMoveDestination(fieldPlayer->getCurrentHomePoint(),true);
          //fieldPlayer->setMoveDestination(fieldPlayer->getPosition(),false);
  }
}
void Square::exit(FieldPlayer* fieldPlayer)
{
	
}


Receiver* Receiver::Instance()
{
  static Receiver instance;
  return &instance;
}
void Receiver::enter(FieldPlayer* fieldPlayer)
{
   fieldPlayer->setShapeName("Receiver");
   fieldPlayer->setMoveDestination(fieldPlayer->getMyTeam()->getTarget(),false);
}
void Receiver::execute(FieldPlayer* fieldPlayer)
{
   if (fieldPlayer->getHuman()) {
      fieldPlayer->getFSM()->changeState(Human::Instance());
	  return;
   }

   if (fieldPlayer->isControllingPlayer()) { // if your the contolling player change state to dribble
	  fieldPlayer->getFSM()->changeState(Dribble::Instance());
	  return;
   }
  
   if (fieldPlayer->getVelocity().x < 0.2 && fieldPlayer->getVelocity().y < 0.2) {
      fieldPlayer->getFSM()->changeState(ChaseBall::Instance());
	  return;
   }

}
void Receiver::exit(FieldPlayer* fieldPlayer)
{
}


ThrowInPlayer* ThrowInPlayer::Instance()
{
  static ThrowInPlayer instance;
  return &instance;
}
void ThrowInPlayer::enter(FieldPlayer* fieldPlayer)
{
   fieldPlayer->setShapeName("ThrowIn");

   if(fieldPlayer->isClosestTeamMemberToBall() && fieldPlayer->getMyTeam()->getPossession())
   {
       //fieldPlayer->setMoveDestination(fieldPlayer->getSoccerBall()->getPosition(), false);
       //fieldPlayer->setPosition(dest, fieldPlayer->getRotation());	

	   Point3F dest = fieldPlayer->getPosition();
	   fieldPlayer->setMoveDestination(dest, false);

       MatrixF mat = fieldPlayer->getTransform();
       mat.setColumn(3, fieldPlayer->getSoccerBall()->getPosition());
       fieldPlayer->setTransform(mat);

	   fieldPlayer->setAimLocation(fieldPlayer->getMyTeam()->getPitch()->getRestartAim());

   }
}
void ThrowInPlayer::execute(FieldPlayer* fieldPlayer)
{
	
	if (!fieldPlayer->isClosestTeamMemberToBall() && !fieldPlayer->getHuman()) {
      Point3F dest = fieldPlayer->getPosition();
	  fieldPlayer->setMoveDestination(dest, false);
	  
	}

}
void ThrowInPlayer::exit(FieldPlayer* fieldPlayer)
{
}

GoalKickPlayer* GoalKickPlayer::Instance()
{
  static GoalKickPlayer instance;
  return &instance;
}
void GoalKickPlayer::enter(FieldPlayer* fieldPlayer)
{
   fieldPlayer->setShapeName("GoalKickPlayer");

   if(fieldPlayer->isClosestTeamMemberToBall() && fieldPlayer->getMyTeam()->getPossession())
   {
       //fieldPlayer->setMoveDestination(fieldPlayer->getSoccerBall()->getPosition(), false);
       //fieldPlayer->setPosition(dest, fieldPlayer->getRotation());	

	   Point3F dest = fieldPlayer->getPosition();
	   fieldPlayer->setMoveDestination(dest, false);

       MatrixF mat = fieldPlayer->getTransform();
       mat.setColumn(3, fieldPlayer->getSoccerBall()->getPosition());
       fieldPlayer->setTransform(mat);

	   fieldPlayer->setAimLocation(fieldPlayer->getMyTeam()->getPitch()->getRestartAim());
   }
}
void GoalKickPlayer::execute(FieldPlayer* fieldPlayer)
{
	
	if (!fieldPlayer->isClosestTeamMemberToBall()) {
      Point3F dest = fieldPlayer->getPosition();
	  fieldPlayer->setMoveDestination(dest, false);	
	}

}
void GoalKickPlayer::exit(FieldPlayer* fieldPlayer)
{
}


CornerKickPlayer* CornerKickPlayer::Instance()
{
  static CornerKickPlayer instance;
  return &instance;
}
void CornerKickPlayer::enter(FieldPlayer* fieldPlayer)
{
   fieldPlayer->setShapeName("CornerKickPlayer");

   if(fieldPlayer->isClosestTeamMemberToBall() && fieldPlayer->getMyTeam()->getPossession())
   {
       //fieldPlayer->setMoveDestination(fieldPlayer->getSoccerBall()->getPosition(), false);
      // fieldPlayer->setPosition(dest, fieldPlayer->getRotation());	

	   Point3F dest = fieldPlayer->getPosition();
	   fieldPlayer->setMoveDestination(dest, false);

       MatrixF mat = fieldPlayer->getTransform();
       mat.setColumn(3, fieldPlayer->getSoccerBall()->getPosition());
       fieldPlayer->setTransform(mat);

	   fieldPlayer->setAimLocation(fieldPlayer->getMyTeam()->getPitch()->getRestartAim());
   }
}
void CornerKickPlayer::execute(FieldPlayer* fieldPlayer)
{
	
	if (!fieldPlayer->isClosestTeamMemberToBall()) {
      Point3F dest = fieldPlayer->getPosition();
	  fieldPlayer->setMoveDestination(dest, false);	
	}

}
void CornerKickPlayer::exit(FieldPlayer* fieldPlayer)
{
}

/*------------------------------------------*/

DoNothing* DoNothing::Instance()
{
  static DoNothing instance;
  return &instance;
}
void DoNothing::enter(FieldPlayer* FieldPlayer)
{
	FieldPlayer->setShapeName("Wait");
}
void DoNothing::execute(FieldPlayer* FieldPlayer)
{
	
 // if (FieldPlayer->getPitch()->getSoccerBall()->isMounted()) {
  //  FieldPlayer->getFSM()->changeState(FollowDribbler::Instance());
 // }
 // else {
    FieldPlayer->getFSM()->changeState(FollowLooseBall::Instance());
  //}
  
}
void DoNothing::exit(FieldPlayer* FieldPlayer)
{
}
/*------------------------------------------*/

/*------------------------------------------*/

FollowDribbler* FollowDribbler::Instance()
{
  static FollowDribbler instance;
  return &instance;
}
void FollowDribbler::enter(FieldPlayer* FieldPlayer)
{
	FieldPlayer->setShapeName("Follow Dribbler");
	//FieldPlayer->setMomentum(FieldPlayer->getPitch()->getSoccerBall()->getVelocity());
	FieldPlayer->setMoveSpeed(0.5);
	//FieldPlayer->setMomentum(FieldPlayer->getPitch()->getSoccerBall()->getVelocity());
}
void FollowDribbler::execute(FieldPlayer* FieldPlayer)
{
  if (FieldPlayer->getPitch()->getSoccerBall()->isMounted()) {
    //FieldPlayer->getFSM()->changeState(FollowDribbler::Instance());
  }
  else {
    FieldPlayer->getFSM()->changeState(FollowLooseBall::Instance());
  }
  Point3F ballpos = FieldPlayer->getPitch()->getBallPosition();

  //ballpos.x = 0;
  
  FieldPlayer->setMoveDestination(ballpos,true); 
}
void FollowDribbler::exit(FieldPlayer* FieldPlayer)
{
}
/*------------------------------------------*/

FollowLooseBall* FollowLooseBall::Instance()
{
  static FollowLooseBall instance;
  return &instance;
}
void FollowLooseBall::enter(FieldPlayer* FieldPlayer)
{
	FieldPlayer->setShapeName("Follow Loose Ball");
	//FieldPlayer->setMomentum(FieldPlayer->getPitch()->getSoccerBall()->getVelocity());
	//FieldPlayer->setMoveSpeed(1.0);
	//FieldPlayer->setMomentum(FieldPlayer->getPitch()->getSoccerBall()->getVelocity());

}
void FollowLooseBall::execute(FieldPlayer* FieldPlayer)
{
  //if (FieldPlayer->getPitch()->getSoccerBall()->isMounted()) {
    //FieldPlayer->getFSM()->changeState(FollowDribbler::Instance());
  //}
  //else {
    //FieldPlayer->getFSM()->changeState(FollowLooseBall::Instance());
  //}
  Point3F ballpos = FieldPlayer->getPitch()->getBallPosition();
 
  
  ballpos.x = 0;
  
  FieldPlayer->setMoveDestination(ballpos,true); 
}
void FollowLooseBall::exit(FieldPlayer* FieldPlayer)
{
}
