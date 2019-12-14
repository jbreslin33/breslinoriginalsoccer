#pragma warning (disable:4786)
#ifndef FIELDPLAYER_H
#define FIELDPLAYER_H
#include "T3D/aiPlayer.h"
#include "soccerPitch.h"
#include "fieldPlayerStateMachine.h"

class SoccerTeam;

class FieldPlayer : public AIPlayer
{
	typedef AIPlayer Parent;

public:

private:
  FieldPlayerStateMachine*   fieldPlayerStateMachine;
  Point3F homePoint;
  Point3F currentHomePoint;
  Point3F offensiveHomePoint;
  Point3F defensiveHomePoint;
  MatrixF homePointMatrixF;
  double playerComfortZoneSq;
  bool    human;
  bool    camTroll;
  SoccerTeam*             team;
  double maxPassingForce;
  Point3F Square[9];
  SoccerPitch*              pitch; // the allknowing soccerpitch

public:
	 DECLARE_CONOBJECT(FieldPlayer);
  FieldPlayer();
  ~FieldPlayer();
  bool getAIMove( Move *move );
  void processUpdate();
  void         setDistSqToBall(double val){ distSqToBall = val; }
  void         setHomePoint(Point3F hp) { homePoint = hp; }
  void         setOffensiveHomePoint(Point3F offp) {offensiveHomePoint = offp; }
  void         setDefensiveHomePoint(Point3F defp) {defensiveHomePoint = defp; }
  void         setCurrentHomePoint(Point3F curp) { currentHomePoint = curp; }
  Point3F      getHomePoint() { return homePoint; }
  Point3F      getOffensiveHomePoint() { return offensiveHomePoint; }
  Point3F      getDefensiveHomePoint() { return defensiveHomePoint; }
  Point3F      getCurrentHomePoint() {return currentHomePoint; }
  void         setHomePointMatrixF(MatrixF hpc) { homePointMatrixF = hpc; }
  MatrixF      getHomePointMatrixF() { return homePointMatrixF; }
  void         setHuman(bool h); 
  bool         getHuman() { return human; }
  void         setTeam(SoccerTeam* t)  { team = t; } 
  SoccerTeam*  getMyTeam() { return team; }
  bool         isControllingPlayer();
  FieldPlayerStateMachine* getFSM()const{return fieldPlayerStateMachine;}
  SoccerBall* const        getSoccerBall()const;
  bool isClosestTeamMemberToBall() const;
  bool isPositionInFrontOfPlayer(Point3F position);
  bool isPassForward(Point3F position);
  bool isThreatened();
  void setPlayerComfortZoneSq(double p) { playerComfortZoneSq = p; }
  double getPlayerComfortZoneSq() { return playerComfortZoneSq; }
  bool aimAtObject(Point3F target);
  double getMaxPassingForce() { return maxPassingForce; }
  void Kick();
  void airKick();
  void setSquares(int s);
  Point3F Pursuit();
  bool insideShootingZone();
  Point3F Interpose(Point3F target, double DistFromTarget);
  //Point3F RunToTarget();
  Point3F getRearTarget();
  double getDistFromTarget();
  bool ballWithinGoalieRange();
  Point3F getOffenseDestination();
  Point3F getDefenseDestination();
  SoccerPitch* getPitch(){ return pitch; }
  void setSoccerPitch(SoccerPitch* p);
protected:
  double distSqToBall;

  //void setMoveDestination( const Point3F &location, bool slowdown );
};


#endif