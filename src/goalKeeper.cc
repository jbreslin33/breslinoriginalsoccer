#include "goalKeeper.h"
#include "fieldPlayerStateMachine.h"
#include "goalKeeperStates.h"
#include "T3D/aiPlayer.h"
#include "soccerBall.h"
#include "fieldPlayer.h"


IMPLEMENT_CO_NETOBJECT_V1(GoalKeeper);

GoalKeeper::GoalKeeper() {
  mNetFlags.set(ScopeAlways | Ghostable);

  Con::errorf("GoalKeeper");

  fieldPlayerStateMachine = new FieldPlayerStateMachine(this);    //setup the state machine
  fieldPlayerStateMachine->setCurrentState(TendGoal::Instance());
  fieldPlayerStateMachine->setPreviousState(TendGoal::Instance());
  fieldPlayerStateMachine->setGlobalState(NULL);
  fieldPlayerStateMachine->changeState(TendGoal::Instance());
  //public
  //delayCollisionTimeout = false;
  //private
  homePoint = Point3F(0.0f, 0.0f, 0.0f);
  currentHomePoint = Point3F(0.0f, 0.0f, 0.0f);
  offensiveHomePoint = Point3F(0.0f, 0.0f, 0.0f);
  defensiveHomePoint = Point3F(0.0f, 0.0f, 0.0f);
  MatrixF homePointMatrixF( EulerF( 0.0f, 0.0f, 0.0f ) );
  team = NULL;
  playerComfortZoneSq = 75;
  human = 0;
  maxPassingForce = 35;
  //protected
  distSqToBall = 0.0;


}

GoalKeeper::~GoalKeeper() {
}
