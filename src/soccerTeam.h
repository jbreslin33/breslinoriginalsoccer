#ifndef SOCCERTEAM_H
#define SOCCERTEAM_H
#include "T3D/gameConnection.h"
#include "soccerPitch.h"
#include "soccerTeamStateMachine.h"
#include "console/simBase.h"
#include "goal.h"

#pragma warning (disable:4786)

class FieldPlayer;
class FieldPlayer;
class SoccerPitch;

class SoccerTeam : public SimObject
{
   typedef SimObject Parent;

public:
  S32 teamColor;
  S32 myteam;
  S32 defendTop;
  FieldPlayer* playerArray[11];
  int NUMBER_OF_PLAYERS_ON_TEAM;
  Point3F              goalPoint;
  double closestSoFarMax;
  double minPassingDistance;
  double minAirPassingDistance;
  double maxPassingDistance;
  Point3F     passTarget;
  F32 distanceToTarget;
  Goal*                      goal;
  bool possession;
  int playerTick;

private:

  SoccerTeamStateMachine*   soccerTeamStateMachine;
  SoccerPitch*              pitch; // the allknowing soccerpitch
  SoccerTeam*               opponent; // other team

  FieldPlayer*               controllingPlayer;  //key players..
  FieldPlayer*               supportingPlayer;
  FieldPlayer*               receivingPlayer;
  FieldPlayer*               playerClosestToBall;
  double                     distSqToBallOfClosestPlayer; //the squared distance the closest player is from the ball
  

public:
  DECLARE_CONOBJECT(SoccerTeam);

  SoccerTeam();
  ~SoccerTeam();

  void setHomeTeam();
  void setAwayTeam();
  void setSoccerPitch(SoccerPitch* p);
  void setOpponent(SoccerTeam* opp);
  SoccerTeam*const     getOpponent()const{return opponent;}
  void setPlayer(FieldPlayer* fp, int i);
  void testTeams();
  int  getTeam() { return myteam; }
  int  getDefendTop() { return defendTop; }
  int  getNumberOfPlayersOnTeam() { return NUMBER_OF_PLAYERS_ON_TEAM; }
  SoccerTeamStateMachine* getFSM()const{return soccerTeamStateMachine;}
  void calculateClosestPlayerToBall();
  void setGoalPoint(Point3F gp) { goalPoint = gp; }
  Point3F getGoalPoint() { return goalPoint; }
  double getClosestSoFarMax() { return closestSoFarMax; }
  double getMinPassingDistance() { return minPassingDistance; }
  double getMinAirPassingDistance() { return minAirPassingDistance; }
  double getMaxPassingDistance() { return maxPassingDistance; }
  void setPossession(bool p) {possession = p;}
  bool getPossession() {return possession;}
  
  
  
  
  void processUpdate();

  void setControllingPlayer(FieldPlayer* player) {
    controllingPlayer = player;
    getOpponent()->setLostControl();
  }
  void setSupportingPlayer(FieldPlayer* player) { supportingPlayer = player; }
  void setReceiver(FieldPlayer* player) { receivingPlayer = player; }
  void setTarget(Point3F target) { passTarget = target; }
  void setDistanceToTarget(F32 distance) { distanceToTarget = distance; }
  void setPlayerClosestToBall(FieldPlayer* player) { playerClosestToBall = player; }


  FieldPlayer* getControllingPlayer()const { return controllingPlayer; }
  FieldPlayer* getSupportingPlayer()const { return supportingPlayer; }
  FieldPlayer* getReceiver()const { return receivingPlayer; }
  Point3F getTarget()const { return passTarget; }
  F32 getDistanceToTarget()const { return distanceToTarget; }
  FieldPlayer* getPlayerClosestToBall()const { return playerClosestToBall; }
  void changePlayersToDefensiveHomePoint();
  void changePlayersToOffensiveHomePoint();
  void changePlayersToHomePoint();
  bool findPass(FieldPlayer* passer,
                         FieldPlayer*&            receiver,
                         double                  power,
						 double                  minPassingDistance);
  bool findAirPass(FieldPlayer* passer,
                         FieldPlayer*&            receiver,
                         double                  power,
						 double                  minPassingDistance);
  bool findAirLeadPass(FieldPlayer* passer,
                         FieldPlayer*&            receiver,
                         double                  power,
						 double                  minPassingDistance);
   bool findLeadPass(FieldPlayer* passer,
                         FieldPlayer*&            receiver,
                         double                  power,
						 double                  minPassingDistance);
  bool findPunt(FieldPlayer* passer,
                         FieldPlayer*&            receiver,
                         double                  power,
						 double                  minPassingDistance);


  bool findClosestToGoalPass(FieldPlayer* passer);
  bool canShoot(FieldPlayer* shooter, double     power);

  bool isInControl()const{
	if (controllingPlayer)
		return true;
	else return false;
  }

  void setLostControl() { controllingPlayer = NULL; }

  void sendAllPlayersHome();
  void setToKickOff();
  SoccerPitch* getPitch(){ return pitch; }

  void turnOffAI();
  void turnOnAI();
  bool isPassSafeFromAllOpponents(Point3F from, Point3F target, FieldPlayer* receiver,double force);
  bool isPassSafeFromOpponent(FieldPlayer* opp, Point3F from, Point3F target, FieldPlayer* receiver,double force);
  bool getBestPassToReceiver(FieldPlayer* passer, FieldPlayer* receiver, Point3F& Target,double power);
  bool getBestAirPassToReceiver(FieldPlayer* passer, FieldPlayer* receiver, Point3F& Target,double power);
  bool getBestAirLeadPassToReceiver(FieldPlayer* passer, FieldPlayer* receiver, Point3F& Target,double power);
  bool getBestLeadPassToReceiver(FieldPlayer* passer, FieldPlayer* receiver, Point3F& Target,double power);
  bool getPassToReceiver(FieldPlayer* passer, FieldPlayer* receiver, Point3F& Target);
  void resetVariablesOnPossesion();


};
#endif