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
#include "soccerPitch.h"
#include "boundary.h"
#include "boundaryStateMachine.h"
#include "boundaryStates.h"

IMPLEMENT_CO_NETOBJECT_V1(Boundary);

Boundary::Boundary(SoccerPitch* p)
{
  Con::errorf("Boundary Constructor");

  pitch = p;
  
  boundaryStateMachine = NULL;

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

  topBounds = 55;
  bottomBounds = -55;
  leftBounds = -37.5;
  rightBounds = 37.5;

  //setup the state machine
  boundaryStateMachine = new BoundaryStateMachine(this);
  boundaryStateMachine->setCurrentState(NormalPlay::Instance());
  boundaryStateMachine->setPreviousState(NormalPlay::Instance());
  boundaryStateMachine->setGlobalState(NULL);
}

Boundary::Boundary()
{
}

Boundary::~Boundary()
{
}


void Boundary::processUpdate()
{
    boundaryStateMachine->update();	
}

bool Boundary::goal(Point3F bp)
{
   if (bp.x > topGoal->getLeftPost().x && bp.x < topGoal->getRightPost().x &&
	   bp.y < topGoal->getCrossbar())
   {
	   return true;
   }
   else
       return false;
}

