#ifndef GOALKEEPER_H
#define GOALKEEPER_H


#include "fieldPlayer.h"
//#include "soccer/pitch/soccerPitch/soccerPitch.h"
//#include "soccer/ai/fieldPlayer/soccerFieldPlayer/fieldPlayerStateMachine.h"

//class SoccerTeam;

class GoalKeeper : public FieldPlayer
{
	typedef FieldPlayer Parent;

public:
 

private:
  //GoalKeeperStateMachine*   goalKeeperStateMachine;
  FieldPlayerStateMachine*   fieldPlayerStateMachine;
  Point3F homePoint;
  Point3F currentHomePoint;
  Point3F offensiveHomePoint;
  Point3F defensiveHomePoint;
  MatrixF homePointMatrixF;
  double playerComfortZoneSq;
  bool    human;
  SoccerTeam*             team;
  double maxPassingForce;
  Point3F Square[9];
  


public:
  DECLARE_CONOBJECT(GoalKeeper);
  GoalKeeper();
  ~GoalKeeper();


 
protected:

};

#endif