#ifndef SOCCERPITCH_H
#define SOCCERPITCH_H
//#include "core/iTickable.h"
#include "T3D/gameConnection.h"
#include "console/simBase.h"
//#include "game/soccerTeam.h"
//#include "game/soccerBall.h"
//#include "game/fieldPlayer.h"
#include "goal.h"
#include "ball.h"
#include "soccerPitchStateMachine.h"
#include "boundary.h"

class SoccerBall;
class ShapeBase;
class SoccerTeam;
class FieldPlayer;

class SoccerPitch : public SimObject
{
  typedef SimObject Parent;

private:
	SoccerPitchStateMachine*   soccerPitchStateMachine;

public:
  SoccerBall*          soccerBall;
  SoccerTeam*          homeTeam;
  SoccerTeam*          awayTeam;
  FieldPlayer*         cameraTroll;
  bool                 gameRunning;
  bool                 kickOff;
  Point3F              ballStartPosition;
  Boundary*            boundary;
  
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


  DECLARE_CONOBJECT(SoccerPitch);
  SoccerPitch();
  ~SoccerPitch();

  void setSoccerBall(SoccerBall* sball);

  void setCameraTroll(FieldPlayer* cTroll);
  void setHomeTeam(SoccerTeam* hTeam);
  void setAwayTeam(SoccerTeam* aTeam);
  void setGameRunning(bool b) { gameRunning = b; }
  void setKickOff(bool b) { kickOff = b; }
  bool getGameRunning() {return gameRunning;}
  void calculateBallQuadrant();
   // Con::errorf("get Game running in function");

  bool getKickOff() { return kickOff; }
  SoccerBall* getSoccerBall() { return soccerBall; }
  Ball* getBall() { return ball; }
  void processUpdate();
  void processOutOfBounds();
  bool isPointInBounds(Point3F point);
  Point3F getBallPosition();
  Point3F getDribblerVelocity();
  int getBallQuadrant() {return quadrant;}

  SoccerTeam* getHomeTeam() { return homeTeam; }
  SoccerTeam* getAwayTeam() { return awayTeam; }
  Point3F getBallStartPosition() { return ballStartPosition; }
  Point3F getRestartAim() {return restartAim;}
  void setRestart(bool p) {restart = p;}
  bool getRestart() {return restart;}

  /*
  void throwIn();
  void goalKick();
  void cornerKick();
  bool checkOutOfBoundsSides(Point3F bp);
  bool checkOutOfBoundsTop(Point3F bp);
  bool checkOutOfBoundsBottom(Point3F bp);
  
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

  void processTopGoal();
  void processBottomGoal();
  void processFreeKickTop(Point3F bp);
  void processFreeKickBottom(Point3F bp);
  void processThrowInLeft(Point3F bp);
  void processThrowInRight(Point3F bp);
*/
};
#endif