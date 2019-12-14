#ifndef BOUNDARY_H
#define BOUNDARY_H
//#include "core/iTickable.h"
#include "T3D/gameConnection.h"
#include "console/simBase.h"
//#include "game/soccerTeam.h"
//#include "game/soccerBall.h"
//#include "game/fieldPlayer.h"
#include "goal.h"
#include "ball.h"
#include "boundaryStateMachine.h"

class SoccerBall;
class ShapeBase;
class SoccerTeam;
class FieldPlayer;

class Boundary : public SimObject
{
  typedef SimObject Parent;

private:
	BoundaryStateMachine*   boundaryStateMachine;

public:

  SoccerPitch*          pitch;

  Point3F              topLeftCornerKickPosition;
  Point3F              topRightCornerKickPosition;
  Point3F              bottomLeftCornerKickPosition;
  Point3F              bottomRightCornerKickPosition;

  Point3F              topLeftSixKickPosition;
  Point3F              topRightSixKickPosition;
  Point3F              bottomLeftSixKickPosition;
  Point3F              bottomRightSixKickPosition;

  Goal*                bottomGoal;
  Goal*                topGoal;
  Point3F              crossbar;
  Ball*                ball;
  int                  quadrant;
  Point3F              restartPos;
  Point3F              restartAim;
  bool                 restart;

  F32              topBounds;
  F32              bottomBounds;
  F32              leftBounds;
  F32              rightBounds;

  Point3F          ballPosition;

  DECLARE_CONOBJECT(Boundary);
  Boundary();
  Boundary(SoccerPitch* p);
  ~Boundary();

  void processUpdate();

  Point3F getTopLeftCornerKickPosition() { return topLeftCornerKickPosition; }
  Point3F getTopRightCornerKickPosition() { return topRightCornerKickPosition; }
  Point3F getBottomLeftCornerKickPosition() { return bottomLeftCornerKickPosition; }
  Point3F getBottomRightCornerKickPosition() { return bottomRightCornerKickPosition; }

  Point3F getTopLeftSixKickPosition() { return topLeftSixKickPosition; }
  Point3F getTopRightSixKickPosition() { return topRightSixKickPosition; }
  Point3F getBottomLeftSixKickPosition() { return bottomLeftSixKickPosition; }
  Point3F getBottomRightSixKickPosition() { return bottomRightSixKickPosition; }

  F32 getTopBounds() { return topBounds; }
  F32 getBottomBounds() { return bottomBounds; }
  F32 getLeftBounds() { return leftBounds; }
  F32 getRightBounds() { return rightBounds; }

  Point3F getBallPosition() { return ballPosition; }
  void setBallPosition(Point3F bp) {ballPosition = bp;}

  bool goal(Point3F bp);

  BoundaryStateMachine* getFSM()const{return boundaryStateMachine;}

};
#endif