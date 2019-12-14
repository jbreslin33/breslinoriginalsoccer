#include "boundaryStates.h"
//#include "soccer/pitch/soccerPitch/soccerPitch.h"
#include "soccerBall.h"
#include "soccerTeam.h"
#include "boundary.h"
#include "soccerTeamStates.h"


NormalPlay* NormalPlay::Instance()
{
  static NormalPlay instance;
  return &instance;
}
void NormalPlay::enter(Boundary* boundary){ }
void NormalPlay::execute(Boundary* boundary)
{
    boundary->setBallPosition(boundary->pitch->getBallPosition());
	Point3F bp = boundary->getBallPosition();

	if (bp.y > boundary->getTopBounds()) {
		if (boundary->goal(bp))
			boundary->getFSM()->changeState(TopGoal::Instance());
		else
			boundary->getFSM()->changeState(FreeKickTop::Instance());
	}
	else if (bp.y < boundary->bottomBounds) {
		if (boundary->goal(bp))
			boundary->getFSM()->changeState(BottomGoal::Instance());
		else
			boundary->getFSM()->changeState(FreeKickBottom::Instance());
	}
	else if (bp.x < boundary->getLeftBounds()) 
		boundary->getFSM()->changeState(ThrowInLeft::Instance());
	else if (bp.x > boundary->getRightBounds())
		boundary->getFSM()->changeState(ThrowInRight::Instance());

}
void NormalPlay::exit(Boundary* boundary) { }

//------------------------------------------------------------------------

TopGoal* TopGoal::Instance()
{
  static TopGoal instance;
  return &instance;
}
void TopGoal::enter(Boundary* boundary){ }
void TopGoal::execute(Boundary* boundary)
{
   if (boundary->pitch->getHomeTeam()->getDefendTop())
	   Con::errorf("away team goal");
   else
       Con::errorf("home team goal");
}
void TopGoal::exit(Boundary* boundary) { }

//------------------------------------------------------------------------

FreeKickTop* FreeKickTop::Instance()
{
  static FreeKickTop instance;
  return &instance;
}
void FreeKickTop::enter(Boundary* boundary){ }
void FreeKickTop::execute(Boundary* boundary)
{
	Point3F bp = boundary->getBallPosition();

	if (bp.x < boundary->topGoal->getCenter().x) {
		if (boundary->pitch->getHomeTeam()->getPossession()) {
			if (boundary->pitch->getAwayTeam()->getDefendTop()) {
	           //Con::errorf("away team six topLeft");
               boundary->pitch->getAwayTeam()->getFSM()->changeState(SixTopLeftOffenseTeam::Instance());
               boundary->pitch->getHomeTeam()->getFSM()->changeState(SixTopLeftDefenseTeam::Instance());

			}
			else {
               //Con::errorf("away team corner topLeft");
			   boundary->pitch->getAwayTeam()->getFSM()->changeState(CornerTopLeftOffenseTeam::Instance());
			   boundary->pitch->getHomeTeam()->getFSM()->changeState(CornerTopLeftDefenseTeam::Instance());
			}
		}
		else {
			if (boundary->pitch->getHomeTeam()->getDefendTop()) {
	           //Con::errorf("home team six topLeft");
               boundary->pitch->getHomeTeam()->getFSM()->changeState(SixTopLeftOffenseTeam::Instance());
               boundary->pitch->getAwayTeam()->getFSM()->changeState(SixTopLeftDefenseTeam::Instance());
			}
			else {
               //Con::errorf("home team corner topLeft");
               boundary->pitch->getHomeTeam()->getFSM()->changeState(CornerTopLeftOffenseTeam::Instance());
			   boundary->pitch->getAwayTeam()->getFSM()->changeState(CornerTopLeftDefenseTeam::Instance());
			}
		}
	}


	else {
		if (boundary->pitch->getHomeTeam()->getPossession()) {
			if (boundary->pitch->getAwayTeam()->getDefendTop()) {
	           //Con::errorf("away team six topRight");
			   boundary->pitch->getAwayTeam()->getFSM()->changeState(SixTopRightOffenseTeam::Instance());
               boundary->pitch->getHomeTeam()->getFSM()->changeState(SixTopRightDefenseTeam::Instance());
			}
			else {
             //Con::errorf("away team corner topRight");
			 boundary->pitch->getAwayTeam()->getFSM()->changeState(CornerTopRightOffenseTeam::Instance());
			 boundary->pitch->getHomeTeam()->getFSM()->changeState(CornerTopRightDefenseTeam::Instance());
			}
		}
		else {
			if (boundary->pitch->getHomeTeam()->getDefendTop()) {
	           //Con::errorf("home team six topRight");
		       boundary->pitch->getHomeTeam()->getFSM()->changeState(SixTopRightOffenseTeam::Instance());
               boundary->pitch->getAwayTeam()->getFSM()->changeState(SixTopRightDefenseTeam::Instance());
			}
			else {
             //Con::errorf("home team corner topRight");
			 boundary->pitch->getHomeTeam()->getFSM()->changeState(CornerTopRightOffenseTeam::Instance());
			 boundary->pitch->getAwayTeam()->getFSM()->changeState(CornerTopRightDefenseTeam::Instance());
			}
		}
	}


}
void FreeKickTop::exit(Boundary* boundary) { }

//------------------------------------------------------------------------

BottomGoal* BottomGoal::Instance()
{
  static BottomGoal instance;
  return &instance;
}
void BottomGoal::enter(Boundary* boundary){ }
void BottomGoal::execute(Boundary* boundary)
{
   if (boundary->pitch->getHomeTeam()->getDefendTop())
	   Con::errorf("home team goal");
   else
       Con::errorf("away team goal");

}
void BottomGoal::exit(Boundary* boundary) { }

//------------------------------------------------------------------------

FreeKickBottom* FreeKickBottom::Instance()
{
  static FreeKickBottom instance;
  return &instance;
}
void FreeKickBottom::enter(Boundary* boundary){ }
void FreeKickBottom::execute(Boundary* boundary)
{
	Point3F bp = boundary->getBallPosition();

	if (bp.x < boundary->topGoal->getCenter().x) {
		if (boundary->pitch->getHomeTeam()->getPossession()) {
	      if (boundary->pitch->getAwayTeam()->getDefendTop())
	         Con::errorf("away team corner bottomLeft");
		  else
             Con::errorf("away team six bottomLeft");
		}
		else {
          if (boundary->pitch->getHomeTeam()->getDefendTop())
	         Con::errorf("home team corner bottomLeft");
		  else
             Con::errorf("home team six bottomLeft");
		}
	}


	else {
		if (boundary->pitch->getHomeTeam()->getPossession()) {
	      if (boundary->pitch->getAwayTeam()->getDefendTop())
	         Con::errorf("away team corner bottomRight");
		  else
             Con::errorf("away team six bottomRight");
		}
		else {
          if (boundary->pitch->getHomeTeam()->getDefendTop())
	         Con::errorf("home team corner bottomRight");
		  else
             Con::errorf("home team six bottomRight");
		}
	}


}

void FreeKickBottom::exit(Boundary* boundary) { }

//------------------------------------------------------------------------

ThrowInLeft* ThrowInLeft::Instance()
{
  static ThrowInLeft instance;
  return &instance;
}
void ThrowInLeft::enter(Boundary* boundary){ }
void ThrowInLeft::execute(Boundary* boundary)
{
   if (boundary->pitch->getHomeTeam()->getPossession())
      Con::errorf("away team ThrowInLeft");
   else
      Con::errorf("home team ThrowInLeft");

}
void ThrowInLeft::exit(Boundary* boundary) { }

//------------------------------------------------------------------------

ThrowInRight* ThrowInRight::Instance()
{
  static ThrowInRight instance;
  return &instance;
}
void ThrowInRight::enter(Boundary* boundary){ }
void ThrowInRight::execute(Boundary* boundary)
{
   if (boundary->pitch->getHomeTeam()->getPossession())
      Con::errorf("away team ThrowInRight");
   else
      Con::errorf("home team ThrowInRight");

}
void ThrowInRight::exit(Boundary* boundary) { }
