#include "soccerTeam.h"
#include "fieldPlayer.h"
#include "string.h"
#include "soccerBall.h"
#include "vector3D.h"
#include "geometry.h"
#include "soccerTeamStateMachine.h"
#include "soccerTeamStates.h"
#include "fieldPlayerStates.h"
#include "utils.h"


IMPLEMENT_CO_NETOBJECT_V1(SoccerTeam);


SoccerTeam::SoccerTeam()
{
  //public
  teamColor = 0;
  myteam = 0;
  defendTop = 0;
  playerArray[11] = NULL;
  NUMBER_OF_PLAYERS_ON_TEAM = 0;
  goalPoint = Point3F(0.0f, 0.0f, 0.0f);
  closestSoFarMax = 200;
  minPassingDistance = 25;
  minAirPassingDistance = 20;
  maxPassingDistance = 150;
  passTarget = Point3F(0.0f, 0.0f, 0.0f);
  distanceToTarget = 0.0;
  goal = NULL;
  possession = 0;
  playerTick = 0;

  //private
  soccerTeamStateMachine = NULL;
  pitch = NULL; // the allknowing soccerpitch
  opponent = NULL; // other team
  controllingPlayer = NULL;  //key players..
  supportingPlayer = NULL;
  receivingPlayer = NULL;
  playerClosestToBall = NULL;
  distSqToBallOfClosestPlayer = 0.0;
  Con::errorf("Called SoccerTeam Constructor");

  //setup the state machine
  soccerTeamStateMachine = new SoccerTeamStateMachine(this);
  soccerTeamStateMachine->setCurrentState(PrepareForKickOff::Instance());
  soccerTeamStateMachine->setPreviousState(PrepareForKickOff::Instance());
  soccerTeamStateMachine->setGlobalState(NULL);
}
SoccerTeam::~SoccerTeam()
{
}
void SoccerTeam::setHomeTeam() {
	teamColor = 0;
	myteam = 0;
	defendTop = 1;
	NUMBER_OF_PLAYERS_ON_TEAM = 11;
	Con::errorf("Registered Home(blue) Team");
}
void SoccerTeam::setAwayTeam() {
	teamColor = 1;
    myteam = 1;
	defendTop = 0;
	NUMBER_OF_PLAYERS_ON_TEAM = 3;
    Con::errorf("Registered Away(red) Team");
}
void SoccerTeam::setSoccerPitch(SoccerPitch* p) {
	pitch = p;
}
void SoccerTeam::setOpponent(SoccerTeam* opp) {
	opponent = opp;
}
void SoccerTeam::setPlayer(FieldPlayer* fp, int i) {
	playerArray[i] = fp;
}
void SoccerTeam::processUpdate() // this is equivalent to buckland soccerTeam update
{ 
  soccerTeamStateMachine->update();	
  for (int i = 0; i < NUMBER_OF_PLAYERS_ON_TEAM; i++) {
    //Con::errorf("about to get runtime error");
    playerArray[i]->processUpdate();
  }
  if (pitch->getGameRunning()) {
    calculateClosestPlayerToBall();
  }
}

void SoccerTeam::testTeams() {
    Point3F v( 0.0f, 0.0f, 0.0f );
	playerArray[3]->setMoveDestination(v,false);
}

void SoccerTeam::calculateClosestPlayerToBall()
{
  double closestSoFar = 15000.00;

  for (int i = 0; i < NUMBER_OF_PLAYERS_ON_TEAM; i++) {
	  double dist = 0;
      dist = vec3DDistanceSq( playerArray[i]->getPosition(), getPitch()->getBallPosition());
	  playerArray[i]->setDistSqToBall(dist);
	  
	  if (dist < closestSoFar && !playerArray[i]->getHuman())
      {
        closestSoFar = dist;
        playerClosestToBall = playerArray[i];
      }
  }
  distSqToBallOfClosestPlayer = closestSoFar;
}
void SoccerTeam::sendAllPlayersHome() {
  for (int i = 0; i < NUMBER_OF_PLAYERS_ON_TEAM; i++) {
	playerArray[i]->setTransform(playerArray[i]->getHomePointMatrixF());
  }
}
void SoccerTeam::setToKickOff() {
  getFSM()->changeState(PrepareForKickOff::Instance());
}

void SoccerTeam::changePlayersToDefensiveHomePoint() {
  for (int i = 0; i < NUMBER_OF_PLAYERS_ON_TEAM; i++) {
	  if(!playerArray[i]->getHuman())
         playerArray[i]->setCurrentHomePoint(playerArray[i]->getDefensiveHomePoint());
  }
}
void SoccerTeam::changePlayersToOffensiveHomePoint() {
  for (int i = 0; i < NUMBER_OF_PLAYERS_ON_TEAM; i++) {
     if(!playerArray[i]->getHuman())
        playerArray[i]->setCurrentHomePoint(playerArray[i]->getOffensiveHomePoint());
  }
}
void SoccerTeam::changePlayersToHomePoint() {
  for (int i = 0; i < NUMBER_OF_PLAYERS_ON_TEAM; i++) {
     if(!playerArray[i]->getHuman())
        playerArray[i]->setCurrentHomePoint(playerArray[i]->getHomePoint());
  }
}



// we skipped a method
bool SoccerTeam::findPass(FieldPlayer* passer,FieldPlayer*& receiver,double power,double minPassingDistance) {
  
  double closestDistance = 10000;
  Point3F target = Point3F(0.0f, 0.0f, 0.0f);
  FieldPlayer* closestReceiver = NULL; //declare a temp var to hold the closest reciver thus far

  for (int i = 0; i < NUMBER_OF_PLAYERS_ON_TEAM; i++) {
    if (playerArray[i] != passer  && playerArray[i]->getHuman() == 0) { 
      double distance = vec3DDistanceSq(passer->getPosition(),playerArray[i]->getPosition()); 
	  if (distance  > minPassingDistance * minPassingDistance) {
		 // if (passer->isPassForward(playerArray[i]->getPosition())) {
		    if (getBestPassToReceiver(passer,playerArray[i],target,power)) {
  	          if (distance < closestDistance) {
                closestDistance = distance;
		        setReceiver(playerArray[i]);
		        setTarget(target); //set the soccerTeam member variable target--this is the current global team target now
			    setDistanceToTarget(distance);
		      }
	        }
		  //}
		} 
	}
  }
  if (getReceiver() == NULL) {
//Con::errorf("test");
    return false;
  }
  else {
    return true;
  }
}



bool SoccerTeam::findAirPass(FieldPlayer* passer,FieldPlayer*& receiver,double power,double minAirPassingDistance) {
  
  double closestDistance = 10000;
  Point3F target = Point3F(0.0f, 0.0f, 0.0f);
  FieldPlayer* closestReceiver = NULL; //declare a temp var to hold the closest reciver thus far

  for (int i = 0; i < NUMBER_OF_PLAYERS_ON_TEAM; i++) {
    if (playerArray[i] != passer  && playerArray[i]->getHuman() == 0) { 
      double distance = vec3DDistanceSq(passer->getPosition(),playerArray[i]->getPosition()); 
	  if (distance  > minAirPassingDistance * minAirPassingDistance) {
		  //if (passer->isPassForward(playerArray[i]->getPosition())) {
		    if (getBestAirPassToReceiver(passer,playerArray[i],target,power)) {
  	          if (distance < closestDistance) {
                closestDistance = distance;
		        setReceiver(playerArray[i]);
		        setTarget(target); //set the soccerTeam member variable target--this is the current global team target now
			    setDistanceToTarget(distance);
		      }
	        }
		 // }
		} 
	}
  }
  if (getReceiver() == NULL) {
//Con::errorf("test");
    return false;
  }
  else {
    return true;
  }
}


bool SoccerTeam::findAirLeadPass(FieldPlayer* passer,FieldPlayer*& receiver,double power,double minAirPassingDistance) {
  
  double closestDistance = 10000;
  Point3F target = Point3F(0.0f, 0.0f, 0.0f);
  FieldPlayer* closestReceiver = NULL; //declare a temp var to hold the closest reciver thus far

  for (int i = 0; i < NUMBER_OF_PLAYERS_ON_TEAM; i++) {
    if (playerArray[i] != passer  && playerArray[i]->getHuman() == 0) { 
      double distance = vec3DDistanceSq(passer->getPosition(),playerArray[i]->getPosition()); 
	  if (distance  > minAirPassingDistance * minAirPassingDistance) {
		  //if (passer->isPassForward(playerArray[i]->getPosition())) {
		    if (getBestAirLeadPassToReceiver(passer,playerArray[i],target,power)) {
  	          if (distance < closestDistance) {
                closestDistance = distance;
		        setReceiver(playerArray[i]);
		        setTarget(target); //set the soccerTeam member variable target--this is the current global team target now
			    setDistanceToTarget(distance);
		      }
	        }
		 // }
		} 
	}
  }
  if (getReceiver() == NULL) {
//Con::errorf("test");
    return false;
  }
  else {
    return true;
  }
}


bool SoccerTeam::findLeadPass(FieldPlayer* passer,FieldPlayer*& receiver,double power,double minAirPassingDistance) {
  
  double closestDistance = 10000;
  Point3F target = Point3F(0.0f, 0.0f, 0.0f);
  FieldPlayer* closestReceiver = NULL; //declare a temp var to hold the closest reciver thus far

  for (int i = 0; i < NUMBER_OF_PLAYERS_ON_TEAM; i++) {
    if (playerArray[i] != passer  && playerArray[i]->getHuman() == 0) { 
      double distance = vec3DDistanceSq(passer->getPosition(),playerArray[i]->getPosition()); 
	  if (distance  > minAirPassingDistance * minAirPassingDistance) {
		  //if (passer->isPassForward(playerArray[i]->getPosition())) {
		    if (getBestLeadPassToReceiver(passer,playerArray[i],target,power)) {
  	          if (distance < closestDistance) {
                closestDistance = distance;
		        setReceiver(playerArray[i]);
		        setTarget(target); //set the soccerTeam member variable target--this is the current global team target now
			    setDistanceToTarget(distance);
		      }
	        }
		 // }
		} 
	}
  }
  if (getReceiver() == NULL) {
//Con::errorf("test");
    return false;
  }
  else {
    return true;
  }
}



bool SoccerTeam::findPunt(FieldPlayer* passer,FieldPlayer*& receiver,double power,double minPassingDistance) {
  
  // just hardcode the player we're punting to for now
  setReceiver(playerArray[10]);
  setTarget(playerArray[10]->getPosition());
  double distance = vec3DDistanceSq(passer->getPosition(),playerArray[10]->getPosition()); 
  setDistanceToTarget(distance);

  return true;
  
}

/*
bool SoccerTeam::getBestPassToReceiver(FieldPlayer* passer, FieldPlayer* receiver, Point3F& target, double power) {
  //first, calculate how much time it will take for the ball to reach
  //this receiver, if the receiver was to remain motionless
  //double time = Pitch()->Ball()->TimeToCoverDistance(Pitch()->Ball()->Pos(),
    //                                                receiver->Pos(),
      //                                              power);  
  //double force = 60; comment out use power instead

  double distance =  sqrt(vec3DDistanceSq(passer->getPosition(), target));
  double force = getPitch()->getBall()->calculateThrowForce(distance);
   
  double time = getPitch()->getBall()->timeToCoverDistance(distance, force);
  
  //return false if ball cannot reach the receiver after having been
  //kicked with the given power
  if (time < 0) return false;
  
  //the maximum distance the receiver can cover in this time
  //double InterceptRange = time * receiver->MaxSpeed();
  double InterceptRange = time * receiver->getMaxForwardVelocity();
  
  //Scale the intercept range
  const double ScalingFactor = 0.3;
  InterceptRange *= ScalingFactor;

  //now calculate the pass targets which are positioned at the intercepts
  //of the tangents from the ball to the receiver's range circle.
  Point3F ip1 = Point3F(0.0f, 0.0f, 0.0f);
  Point3F ip2 = Point3F(0.0f, 0.0f, 0.0f);

  GetTangentPoints(receiver->getPosition(),
                   InterceptRange,
				   getPitch()->getBallPosition(),
                   ip1,
                   ip2);  

  const int NumPassesToTry = 3;
  Point3F Passes[NumPassesToTry] = {ip1, receiver->getPosition(), ip2};

  // this pass is the best found so far if it is:
  //
  //  1. Further upfield than the closest valid pass for this receiver
  //     found so far
  //  2. Within the playing area
  //  3. Cannot be intercepted by any opponents

  double ClosestSoFar = closestSoFarMax;
  bool  bResult      = false;
  for (int pass=0; pass<NumPassesToTry; ++pass)
  {
    //double dist = fabs(Passes[pass].x - OpponentsGoal()->Center().x);
    double dist = fabs(Passes[pass].x - goalPoint.x);
	//from jim..looks like the Inside just checks to see if the pos is literally inside the play
    if (( dist < ClosestSoFar) &&
		getPitch()->isPointInBounds(Passes[pass]) &&
		isPassSafeFromAllOpponents(getPitch()->getBallPosition(),
                                   Passes[pass],
                                   receiver,power))
    {
      ClosestSoFar = dist;
      target   = Passes[pass];
      bResult      = true;
    }
  }

  return bResult;
}

*/




bool SoccerTeam::getBestPassToReceiver(FieldPlayer* passer, FieldPlayer* receiver, Point3F& target, double power) {
  //first, calculate how much time it will take for the ball to reach
  //this receiver, if the receiver was to remain motionless

  double distance =  sqrt(vec3DDistanceSq(passer->getPosition(), target));
  double force = getPitch()->getBall()->calculateThrowForce(distance);
   
  double time = getPitch()->getBall()->timeToCoverDistance(distance, force);

  //return false if ball cannot reach the receiver after having been
  //kicked with the given power
  if (time < 0) return false;

  if(isPassSafeFromAllOpponents(getPitch()->getBallPosition(),
                                   receiver->getPosition(),
                                   receiver,power))
  {
    target   = receiver->getPosition();
    return true;
  }

}


bool SoccerTeam::getBestAirPassToReceiver(FieldPlayer* passer, FieldPlayer* receiver, Point3F& target, double power) {
  //first, calculate how much time it will take for the ball to reach
  //this receiver, if the receiver was to remain motionless

  double distance =  sqrt(vec3DDistanceSq(passer->getPosition(), receiver->getPosition()));
  double force = getPitch()->getBall()->calculateThrowForce(distance);
   
  double time = getPitch()->getBall()->timeToCoverDistance(distance, force);

  //return false if ball cannot reach the receiver after having been
  //kicked with the given power
  if (time < 0) return false;

    Point3F vectorToTarget = receiver->getPosition() - getPitch()->getBallPosition();
    vectorToTarget.normalize();
    distance = distance - 5.0;
    vectorToTarget = vectorToTarget * distance;

    target   = getPitch()->getBallPosition() + vectorToTarget;


  //need to alter this function at some point to account for air pass
  if(isPassSafeFromAllOpponents(getPitch()->getBallPosition(),
                                   target,
                                   receiver,power))
  {
    return true;
  }
  else
    return false;

}



bool SoccerTeam::getBestAirLeadPassToReceiver(FieldPlayer* passer, FieldPlayer* receiver, Point3F& target, double power) {
  //first, calculate how much time it will take for the ball to reach
  //this receiver, if the receiver was to remain motionless

  target   = receiver->getPosition();

  if(getTeam())
    target.y = target.y - 5.0;
  else
    target.y = target.y + 5.0;

  double distance =  sqrt(vec3DDistanceSq(passer->getPosition(), target));

    Point3F vectorToTarget = target - getPitch()->getBallPosition();
    vectorToTarget.normalize();
    distance = distance - 5.0;
    vectorToTarget = vectorToTarget * distance;

    target   = getPitch()->getBallPosition() + vectorToTarget;


  
  double force = getPitch()->getBall()->calculateThrowForce(distance);
   
  double time = getPitch()->getBall()->timeToCoverDistance(distance, force);

  //return false if ball cannot reach the receiver after having been
  //kicked with the given power
  if (time < 0) return false;


  //need to alter this function at some point to account for air pass
  if(isPassSafeFromAllOpponents(getPitch()->getBallPosition(),
                                   target,
                                   receiver,power))
  {
    return true;
  }
  else
    return false;
}


bool SoccerTeam::getBestLeadPassToReceiver(FieldPlayer* passer, FieldPlayer* receiver, Point3F& target, double power) {
  //first, calculate how much time it will take for the ball to reach
  //this receiver, if the receiver was to remain motionless

  double distance =  sqrt(vec3DDistanceSq(passer->getPosition(), receiver->getPosition()));
  double force = getPitch()->getBall()->calculateThrowForce(distance);
   
  double time = getPitch()->getBall()->timeToCoverDistance(distance, force);

  //return false if ball cannot reach the receiver after having been
  //kicked with the given power
  if (time < 0) return false;


  target   = receiver->getPosition();

  if(getTeam())
    target.y = target.y - 5.0;
  else
    target.y = target.y + 5.0;

  if(isPassSafeFromAllOpponents(getPitch()->getBallPosition(),
                                   target,
                                   receiver,power))
  {
    return true;
  }
  else
    return false;
}




bool SoccerTeam::getPassToReceiver(FieldPlayer* passer, FieldPlayer* receiver, Point3F& Target) {
	bool bResult = true;
	Target = receiver->getPosition();

  return bResult;
}

void SoccerTeam::turnOffAI()
{
   soccerTeamStateMachine->changeState(FreezeTeam::Instance());
   Con::errorf("turnOffAI");
}

void SoccerTeam::turnOnAI()
{
   for (int i = 0; i < NUMBER_OF_PLAYERS_ON_TEAM; i++) {
      if(playerArray[i]->getFSM()->currentState() != Human::Instance())
	  {
         playerArray[i]->getFSM()->changeState(Wait::Instance());
	  }
   }
   soccerTeamStateMachine->revertToPreviousState();

   Con::errorf("turnOnAI");
}



bool SoccerTeam::canShoot(FieldPlayer* shooter, double     power)
{
  //the number of randomly created shot targets this method will test 
  int NumAttempts = 5;

  while (NumAttempts--)
  {
    //choose a random position along the opponent's goal mouth. (making
    //sure the ball's radius is taken into account)
    passTarget = opponent->goal->getCenter();

	//the y value of the shot position should lay somewhere between two
    //goalposts (taking into consideration the ball diameter)
    int minXVal = opponent->goal->getLeftPost().x;
    int maxXVal = opponent->goal->getRightPost().x;

	 passTarget.x = (double)RandInt(minXVal, maxXVal);

	 //Con::errorf("X %f", passTarget.x );
	 //Con::errorf("Y %f", passTarget.y );
     //Con::errorf("Z %f", passTarget.z );

   // double distance =  sqrt(vec3DDistanceSq(shooter->getPosition(), passTarget));
   // double force = getPitch()->getBall()->calculateThrowForce(distance);

	 double distance =  vec3DDistanceSq(shooter->getPosition(), passTarget);
	 setDistanceToTarget(distance);

	 //make sure striking the ball with the given power is enough to drive
    //the ball over the goal line.
    //double time = getPitch()->getBall()->timeToCoverDistance(distance,
    //                                                  power);
	//Con::errorf("Time %f", time);
    
	//assume for now that it will always get there
    double time = 1;

    //if it is, this shot is then tested to see if any of the opponents
    //can intercept it.
    if (time >= 0)
    {
      if (1) //(isPassSafeFromAllOpponents(shooter->getPosition(), passTarget, NULL,power))
      {
        return true;
      }
    }
  }

  return false;
}

//returns true if pass/shot can't be intercepted by any opponent
//bool SoccerTeam::isPassSafeFromAllOpponents(Vector2D                from,
  //                                          Vector2D                target,
    //                                        const PlayerBase* const receiver,
      //                                      double     PassingForce)const
bool SoccerTeam::isPassSafeFromAllOpponents(Point3F from, Point3F target, FieldPlayer* receiver,double power)
{
  for (int i = 0; i < opponent->NUMBER_OF_PLAYERS_ON_TEAM; i++)
  {
    if (!isPassSafeFromOpponent(opponent->playerArray[i], from, target, receiver,power))
    { 
      return false;
    }
  }
  return true;
}

//returns true if pass/shot can't be intercepted this specific opponent
bool SoccerTeam::isPassSafeFromOpponent(FieldPlayer* opp, Point3F from, Point3F target, FieldPlayer* receiver, double power)
{
  //move the opponent into local space.
  VectorF ToTarget = target - from;
  
  ToTarget.normalize();

  //get perpendicular to the target vector
  VectorF ToTargetPerp(0.0f,0.0f,0.0f);
  ToTargetPerp.x = -ToTarget.y;
  ToTargetPerp.y =  ToTarget.x;

  ToTargetPerp.normalize();

  Point3F pos = Point3F(0.0f, 0.0f, 0.0f);
  pos = from;

  VectorF LocalPosOpp = PointToLocalSpace(opp->getPosition(),
                                         ToTarget,
                                         ToTargetPerp,
                                         pos);
 if ( LocalPosOpp.x < 0 )
  {
    return true;
  }

// vec3DDistanceSq
 //if the opponent is further away than the target we need to consider if
  //the opponent can reach the position before the receiver.
  //if (vec3DDistanceSq(from, target) < Vec2DDistanceSq(opp->Pos(), from))
 
  if (vec3DDistanceSq(from, target) < vec3DDistanceSq(opp->getPosition(), from)) 
  {
    if (receiver)
	{
      if ( vec3DDistanceSq(target, opp->getPosition())  >
		  vec3DDistanceSq(target, receiver->getPosition()) )
      {
        return true;
      }
      else
      {
        return false;
      }
    }
    else
    {
      return true;
    }
  }
   //calculate how long it takes the ball to cover the distance to the 
  //position orthogonal to the opponents position

  double distance =  sqrt(vec3DDistanceSq(from, target));
  double force = getPitch()->getBall()->calculateThrowForce(distance);

  double distanceToOpp =  sqrt(vec3DDistanceSq(Point3F(0,0,0), Point3F(LocalPosOpp.x,0,0)));

    //double force = 30;
    double TimeForBall = getPitch()->getBall()->timeToCoverDistance(distanceToOpp, force);
    double reach = opp->getMaxForwardVelocity() * TimeForBall;
//Con::errorf("TimeForBall %f", TimeForBall);
//Con::errorf("forwardVel %f", opp->getMaxForwardVelocity());

//if the distance to the opponent's y position is less than his running
  //range plus the radius of the ball and the opponents radius then the
  //ball can be intercepted
  if ( fabs(LocalPosOpp.y) < reach )
  {
    return false;
  }

  return true;
}
void SoccerTeam::resetVariablesOnPossesion() {
 
  setSupportingPlayer(NULL);
  setReceiver(NULL);
  setPlayerClosestToBall(NULL);
  getOpponent()->setSupportingPlayer(NULL);
  getOpponent()->setReceiver(NULL);
  getOpponent()->setPlayerClosestToBall(NULL);
}

ConsoleMethod( SoccerTeam, turnOffAI, void, 2, 2, "()"
              "turn off ai state machines") {
	object->turnOffAI();
}

ConsoleMethod( SoccerTeam, turnOnAI, void, 2, 2, "()"
              "turn on ai state machines") {
	object->turnOnAI();
}

ConsoleMethod( SoccerTeam, setHomeTeam, void, 2, 2, "()"
              "set the team as home(blue) team") {
	object->setHomeTeam();
}
ConsoleMethod( SoccerTeam, setAwayTeam, void, 2, 2, "()"
              "set the team as away(red) team") {
	object->setAwayTeam();
}
ConsoleMethod(SoccerTeam, setSoccerPitch, void, 3, 3, "(SoccerPitch obj)"
              "set the SoccerPitch Pointer.")
{
   SoccerPitch* spitch = NULL;
   if (Sim::findObject(dAtoi(argv[2]),spitch))
     object->setSoccerPitch(spitch);
}
ConsoleMethod(SoccerTeam, setOpponent, void, 3, 3, "(SoccerTeam obj)"
              "set the Opponent Pointer.")
{
   SoccerTeam* opp = NULL;
   if (Sim::findObject(dAtoi(argv[
	   2]),opp))
     object->setOpponent(opp);
}
ConsoleMethod(SoccerTeam, setPlayer, void, 4, 4, "(FieldPlayer obj, int i)"
              "set the player in playerArray at index i.")
{
   FieldPlayer* fp = NULL;
   if (Sim::findObject(dAtoi(argv[2]),fp)) {
     object->setPlayer(fp,dAtoi(argv[3]));
	 
	 
   }
}
ConsoleMethod( SoccerTeam, testTeams, void, 2, 2, "()"
              "test teams") {
	object->testTeams();
}

ConsoleMethod(SoccerTeam, setControllingPlayer, void, 3, 3, "(FieldPlayer obj, int i)"
              "set the player who controls the ball.")
{
   FieldPlayer* fp = NULL;
   //object->setReceiver(NULL); //release the receiver
   object->getOpponent()->setReceiver(NULL);
  if (Sim::findObject(dAtoi(argv[2]),fp))
     object->setControllingPlayer(fp);
     
}
ConsoleMethod(SoccerTeam, setControllingPlayerToNull, void, 2, 2, "(FieldPlayer obj, int i)"
              "set the player who controls the ball.")
{
   //FieldPlayer* fp;
  ///if (Sim::findObject(dAtoi(argv[2]),fp))
     object->setControllingPlayer(NULL);
}
ConsoleMethod( SoccerTeam, setGoalPoint, void, 3, 3, "(Point3F setGoalPoint)"
              "Set the setGoalPoint.\n\n") {
   Point3F pos = Point3F(0.0f, 0.0f, 0.0f);
   dSscanf( argv[2], "%f %f %f", &pos.x, &pos.y, &pos.z );
   object->setGoalPoint(pos);
}
ConsoleMethod( SoccerTeam, setToKickOff, void, 2, 2, "()"
              "setToKickOff") {
	object->setToKickOff();
}
ConsoleMethod( SoccerTeam, resetVariablesOnPossesion, void, 2, 2, "()"
              "resetVariablesOnPossesion") {
	object->resetVariablesOnPossesion();
}
ConsoleMethod( SoccerTeam, setPossession, void, 3, 3, "(bool p)"
              "Set the setPossession.\n\n") {
//Con::errorf("ConsoleMethod setPossession");
   object->setPossession(dAtob(argv[2]));
}


