#include "soccerPitch.h"
#include "console/simBase.h"
#include "console/console.h"
#include "console/consoleTypes.h"
#include "soccerTeam.h"
#include "soccerBall.h"
#include "fieldPlayer.h"
#include "soccerTeamStates.h"
#include "goal.h"
#include "ball.h"
#include "soccerPitchStateMachine.h"
#include "soccerPitchStates.h"
#include "boundary.h"

IMPLEMENT_CO_NETOBJECT_V1(SoccerPitch);

SoccerPitch::SoccerPitch()
{
  Con::errorf("SoccerPitch Constructor");
  soccerBall = NULL;
  homeTeam = NULL;
  awayTeam = NULL;
  soccerPitchStateMachine = NULL;

  gameRunning = false;
  kickOff     = false;

  //tap off
  ballStartPosition.x = 0;
  ballStartPosition.y = 0;
  ballStartPosition.z = 2;

  //top left corner kick
  topLeftCornerKickPosition.x = -37;
  topLeftCornerKickPosition.y = 54.5;
  topLeftCornerKickPosition.z = 2;

  //top right corner kick
  topRightCornerKickPosition.x = 37;
  topRightCornerKickPosition.y = 54.5;
  topRightCornerKickPosition.z = 2;
  
  //bottom right corner kick
  bottomRightCornerKickPosition.x = 37;
  bottomRightCornerKickPosition.y = -54.5;
  bottomRightCornerKickPosition.z = 2;

  //bottom left corner kick
  bottomLeftCornerKickPosition.x = -37;
  bottomLeftCornerKickPosition.y = -54.5;
  bottomLeftCornerKickPosition.z = 2;

  //north west six kick
  topLeftSixKickPosition.x = -9;
  topLeftSixKickPosition.y = 49;
  topLeftSixKickPosition.z = 2;

  //north east six kick
  topRightSixKickPosition.x = 9;
  topRightSixKickPosition.y = 49;
  topRightSixKickPosition.z = 2;

  //south east six kick
  bottomRightSixKickPosition.x = 9;
  bottomRightSixKickPosition.y = -49;
  bottomRightSixKickPosition.z = 2;

  //south west six kick
  bottomLeftSixKickPosition.x = -9;
  bottomLeftSixKickPosition.y = -49;
  bottomLeftSixKickPosition.z = 2;

  //create the goals
  topGoal  = new Goal(Point3F(-4.0,55,0),Point3F(4.0,55,0),Point3F(0,1,0));                     
  bottomGoal  = new Goal(Point3F(-4.0,-55,0),Point3F(4.0,-55,0),Point3F(0,-1,0));

  boundary  = new Boundary(this);      

  ball = new Ball();
  quadrant = 4;
  restartPos = ballStartPosition;
  restartAim = ballStartPosition;
  restart = 1;

  topBounds = 55;
  bottomBounds = -55;
  leftBounds = -37.5;
  rightBounds = 37.5;



  //setup the state machine
 // soccerPitchStateMachine = new SoccerPitchStateMachine(this);
  //soccerPitchStateMachine->setCurrentState(NormalPlay::Instance());
 // soccerPitchStateMachine->setPreviousState(NormalPlay::Instance());
 // soccerPitchStateMachine->setGlobalState(NULL);
}

SoccerPitch::~SoccerPitch()
{
}

void SoccerPitch::processUpdate()
{
    //soccerPitchStateMachine->update();	
    homeTeam->processUpdate();
    awayTeam->processUpdate();
	cameraTroll->processUpdate();
    boundary->processUpdate();

  if (getKickOff()) {
	  Con::errorf("getGameRunning is true and so is getKickOff");
	  homeTeam->getFSM()->changeState(PrepareForKickOff::Instance());
      awayTeam->getFSM()->changeState(PrepareForKickOff::Instance());
	  setKickOff(false);
  }	
}

void SoccerPitch::setSoccerBall(SoccerBall* tball)
{  
  soccerBall = tball;
}

void SoccerPitch::setCameraTroll(FieldPlayer* cTroll)
{
  cameraTroll = cTroll;
}

void SoccerPitch::setHomeTeam(SoccerTeam* hteam)
{
  homeTeam = hteam;
  homeTeam->goal = bottomGoal;
  Con::errorf("SoccerPitch now has a pointer to homeTeam($HomeTeam)in script");
}
void SoccerPitch::setAwayTeam(SoccerTeam* ateam)
{
  awayTeam = ateam;
  awayTeam->goal = topGoal;
  Con::errorf("SoccerPitch now has a pointer to AwayTeam($AwayTeam)in script");
}

void SoccerPitch::processOutOfBounds() {
  
  soccerBall->unmount();

  homeTeam->getFSM()->changeState(PrepareForKickOff::Instance());
  awayTeam->getFSM()->changeState(PrepareForKickOff::Instance());

  soccerBall->setPosition(ballStartPosition);
  VectorF vel(0,0,0);
  soccerBall->setVelocity(vel);

}

/*
void SoccerPitch::throwIn() {
  
  soccerBall->unmount();
  
  soccerBall->setPosition(restartPos);
  VectorF vel(0,0,0);
  soccerBall->setVelocity(vel);

  homeTeam->getFSM()->changeState(ThrowInTeam::Instance());
  awayTeam->getFSM()->changeState(ThrowInTeam::Instance());

}

void SoccerPitch::goalKick() {
  
  soccerBall->unmount();
  
  soccerBall->setPosition(restartPos);
  VectorF vel(0,0,0);
  soccerBall->setVelocity(vel);

  homeTeam->getFSM()->changeState(GoalKickTeam::Instance());
  awayTeam->getFSM()->changeState(GoalKickTeam::Instance());

  

}

void SoccerPitch::cornerKick() {
  
  soccerBall->unmount();
  
  soccerBall->setPosition(restartPos);
  VectorF vel(0,0,0);
  soccerBall->setVelocity(vel);

  homeTeam->getFSM()->changeState(CornerKickTeam::Instance());
  awayTeam->getFSM()->changeState(CornerKickTeam::Instance());
}

void SoccerPitch::processTopGoal()
{
   if (homeTeam->getDefendTop())
	   Con::errorf("away team goal");
   else
       Con::errorf("home team goal");
	   
}

void SoccerPitch::processBottomGoal()
{
   if (homeTeam->getDefendTop())
	   Con::errorf("home team goal");
   else
       Con::errorf("away team goal");
	   
}

void SoccerPitch::processFreeKickTop(Point3F bp)
{
	if (bp.x < topGoal->getCenter().x) {
		if (homeTeam->getPossession()) {
	      if (awayTeam->getDefendTop())
	         Con::errorf("away team six topLeft");
		  else
             Con::errorf("away team corner topLeft");
		}
		else {
          if (homeTeam->getDefendTop())
	         Con::errorf("home team six topLeft");
		  else
             Con::errorf("home team corner topLeft");
		}
	}


	else {
		if (homeTeam->getPossession()) {
	      if (awayTeam->getDefendTop())
	         Con::errorf("away team six topRight");
		  else
             Con::errorf("away team corner topRight");
		}
		else {
          if (homeTeam->getDefendTop())
	         Con::errorf("home team six topRight");
		  else
             Con::errorf("home team corner topRight");
		}
	}


}


void SoccerPitch::processFreeKickBottom(Point3F bp)
{
	if (bp.x < topGoal->getCenter().x) {
		if (homeTeam->getPossession()) {
	      if (awayTeam->getDefendTop())
	         Con::errorf("away team corner bottomLeft");
		  else
             Con::errorf("away team six bottomLeft");
		}
		else {
          if (homeTeam->getDefendTop())
	         Con::errorf("home team corner bottomLeft");
		  else
             Con::errorf("home team six bottomLeft");
		}
	}


	else {
		if (homeTeam->getPossession()) {
	      if (awayTeam->getDefendTop())
	         Con::errorf("away team corner bottomRight");
		  else
             Con::errorf("away team six bottomRight");
		}
		else {
          if (homeTeam->getDefendTop())
	         Con::errorf("home team corner bottomRight");
		  else
             Con::errorf("home team six bottomRight");
		}
	}


}

void SoccerPitch::processThrowInLeft(Point3F bp)
{
   if (homeTeam->getPossession())
      Con::errorf("away team ThrowInLeft");
   else
      Con::errorf("home team ThrowInLeft");
}

void SoccerPitch::processThrowInRight(Point3F bp)
{
   if (homeTeam->getPossession())
      Con::errorf("away team ThrowInRight");
   else
      Con::errorf("home team ThrowInRight");
}

bool SoccerPitch::checkOutOfBoundsSides(Point3F bp)
{
    if (bp.x < -37.5) {
      bp.x = -38.5;
      restartPos = bp;
	  VectorF ra(37.5,bp.y,0);
      restartAim = ra;
	  restart = 1;
      throwIn(); 
	  Con::errorf("throwIn");
    }

    if (bp.x > 37.5) {
	  bp.x = 38.5;
	  restartPos = bp;
	  VectorF ra(-37.5,bp.y,0);
      restartAim = ra;
	  restart = 1;
      throwIn(); 
	  Con::errorf("throwIn");
    }

	return restart;
}


bool SoccerPitch::checkOutOfBoundsTop(Point3F bp)
{
  if (bp.y > 55.0) //check if ball is past goal line
  {
    //if (bp.x > awayGoal->getLeftPost().x && bp.x < awayGoal->getRightPost().x && bp.y < 8.0)
	//check if ball is inside goal posts as it is already past goal line
	if (bp.x > topGoal->getLeftPost().x && bp.x < topGoal->getRightPost().x)
	{
	  processOutOfBounds(); 
	  restart = 1;
      Con::errorf("GOAL");
	}
	else {
	  restart = 1;
      //checking for six kick
	  if (homeTeam->getPossession()) 
	  {
	    if(bp.x < 0) //six kick to right of goalie
		{
          VectorF rp(-8,49,0);
          restartPos = rp;
          VectorF ra(-8,-55,0);
          restartAim = ra;
		}
		else //six kick to left of goalie
		{
          VectorF rp(8,49,0);
          restartPos = rp;
		  VectorF ra(8,-55,0);
          restartAim = ra;
		}
		goalKick(); 
	  }


      else { //away team has possesion do corner kick
	     if(bp.x < 0) 
		 {
           VectorF rp(-37,54.5,0);
           restartPos = rp;
           VectorF ra(-37,54.5,0);
           restartAim = ra;
		 }
		 else //greater than 0 corner on left side of goalie
		 {
           VectorF rp(37,54.5,0);
           restartPos = rp;
		   VectorF ra(37,-54.5,0);
           restartAim = ra;
		 }
         cornerKick(); 
	   }

	  Con::errorf("GOAL/CORNER KICK");
	}
  }

  return restart;
}



bool SoccerPitch::checkOutOfBoundsBottom(Point3F bp)
{
  if (bp.y < -55.0) 
  {
    if (bp.x > bottomGoal->getLeftPost().x && bp.x < bottomGoal->getRightPost().x && bp.y < 8.0) 
    //if (bp.x > homeGoal->getLeftPost().x && bp.x < homeGoal->getRightPost().x) 
	{
	  processOutOfBounds(); 
	  restart = 1;
      Con::errorf("GOAL");
	}
	else {
	  restart = 1;

	  if (homeTeam->getPossession()) 
	  {
	    if(bp.x < 0) //corner kick to left of goalie
		{
          VectorF rp(-37,-54.5,0);
          restartPos = rp;
		  VectorF ra(-37,54.5,0);
          restartAim = ra;
		}
		else //corner kick to left of right of goale
		{
		  VectorF rp(37,-54.5,0);
          restartPos = rp;
		  VectorF ra(37,54.5,0);
          restartAim = ra;
		}
        cornerKick();
	  }

	  else { //six kick to left of goalie
	    if(bp.x < 35.0) {
          VectorF rp(-3.6,-49,0);
          restartPos = rp;
		  VectorF ra(-3.6,49,0);
          restartAim = ra;
		  }
		else { //six kick to right of goalie
          VectorF rp(3.6,-49,0);
          restartPos = rp;
		  VectorF ra(3.6,49,0);
          restartAim = ra;
		  }
        goalKick();
		Con::errorf("GOAL/CORNER KICK");
	  }  
    }
  }

  return restart;
}
*/


Point3F SoccerPitch::getBallPosition() {
  if(homeTeam->isInControl()) {
    Point3F pos = Point3F(0.0f, 0.0f, 0.0f);
	homeTeam->getControllingPlayer()->getMuzzlePoint(0,&pos);
	return pos;
  }
  if(awayTeam->isInControl()) {
    Point3F pos = Point3F(0.0f, 0.0f, 0.0f);
	awayTeam->getControllingPlayer()->getMuzzlePoint(0,&pos);
	return pos;
  }
  return soccerBall->getPosition();
  }

void SoccerPitch::calculateBallQuadrant() {

   Point3F pos = getBallPosition();

   if (pos.y < 40) {
      if (pos.x < 23)
		   quadrant = 0;
	  else if (pos.x < 46)
		   quadrant = 1;
	  else 
           quadrant = 2;
   }
   else if (pos.y < 80) {
      if (pos.x < 23)
		   quadrant = 3;
	  else if (pos.x < 46)
		   quadrant = 4;
	  else 
           quadrant = 5;
   }
   else {
      if (pos.x < 23)
		   quadrant = 6;
	  else if (pos.x < 46)
		   quadrant = 7;
	  else 
           quadrant = 8;
   }
//Con::errorf("quad %d", quadrant);
}

bool SoccerPitch::isPointInBounds(Point3F bp) {
  if (bp.y < 1.45) {
    return false;
  }
  if (bp.y > 118.5) {
    return false;
  }
  if (bp.x < 1.45) {
    return false; 
  }
  if (bp.x > 67.5) {
    return false; 
  }
  return true;
}

ConsoleMethod(SoccerPitch, setSoccerBall, void, 3, 3, "(SoccerBall obj)"
              "set the SoccerBall Pointer.")
{
   SoccerBall* sball = NULL;
   if (Sim::findObject(dAtoi(argv[2]),sball))
     object->setSoccerBall(sball);
}

ConsoleMethod(SoccerPitch, setCameraTroll, void, 3, 3, "(CameraTroll obj)"
              "set the CameraTroll Pointer.")
{
   FieldPlayer* cTroll = NULL;
   if (Sim::findObject(dAtoi(argv[2]),cTroll))
     object->setCameraTroll(cTroll);
}

ConsoleMethod(SoccerPitch, setHomeTeam, void, 3, 3, "(SoccerTeam obj)"
              "set the Home Team Pointer.")
{
   SoccerTeam* steam = NULL;
   if (Sim::findObject(dAtoi(argv[2]),steam))
     object->setHomeTeam(steam);
}
ConsoleMethod(SoccerPitch, setAwayTeam, void, 3, 3, "(SoccerTeam obj)"
              "set the Away Team Pointer.")
{
   SoccerTeam* steam = NULL;
   if (Sim::findObject(dAtoi(argv[2]),steam))
     object->setAwayTeam(steam);
}
ConsoleMethod( SoccerPitch, setGameRunning, void, 3, 3,"" "setGameRunning") {
    object->setGameRunning(dAtob(argv[2]));
}

ConsoleMethod( SoccerPitch, setKickOff, void, 3, 3,"" "setKickOff") {
    object->setKickOff(dAtob(argv[2]));
}
ConsoleMethod( SoccerPitch, getGameRunning, bool, 2, 2,"" "getGameRunning") {
	return object->getGameRunning();
}

ConsoleMethod( SoccerPitch, setRestart, void, 3, 3, "(bool p)"
              "Set the Restart.\n\n") {
//Con::errorf("ConsoleMethod setRestart");
   object->setRestart(dAtob(argv[2]));
}
