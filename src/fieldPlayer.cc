#include "fieldPlayer.h"
#include "fieldPlayerStateMachine.h"
#include "fieldPlayerStates.h"
#include "soccerTeam.h"
#include "soccerBall.h"
#include "vector3D.h"
#include "soccerTeamStates.h"

IMPLEMENT_CO_NETOBJECT_V1(FieldPlayer);

FieldPlayer::FieldPlayer() {
  mNetFlags.set(Ghostable);

  Con::errorf("FieldPlayer");

  if (camTroll) {
    fieldPlayerStateMachine = new FieldPlayerStateMachine(this);    //setup the state machine
    fieldPlayerStateMachine->setCurrentState(DoNothing::Instance());
    fieldPlayerStateMachine->setPreviousState(DoNothing::Instance());
    fieldPlayerStateMachine->setGlobalState(NULL);
    fieldPlayerStateMachine->changeState(DoNothing::Instance());
  }
  else {
    fieldPlayerStateMachine = new FieldPlayerStateMachine(this);    //setup the state machine
    fieldPlayerStateMachine->setCurrentState(FreezePlayer::Instance());
    fieldPlayerStateMachine->setPreviousState(FreezePlayer::Instance());
    fieldPlayerStateMachine->setGlobalState(NULL);
    fieldPlayerStateMachine->changeState(FreezePlayer::Instance());
  }
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
  camTroll = 0;
  maxPassingForce = 35;
  //protected
  distSqToBall = 0.0;
}

FieldPlayer::~FieldPlayer() {
}
void FieldPlayer::setSoccerPitch(SoccerPitch* p) {
	pitch = p;
	camTroll = 1;

}

void FieldPlayer::processUpdate() {
  fieldPlayerStateMachine->update();
  //Con::errorf("in process update");
}

bool FieldPlayer::isControllingPlayer() {
  return team->getControllingPlayer() == this;
}

SoccerBall* const FieldPlayer::getSoccerBall()const {
  return team->getPitch()->getSoccerBall();
}

bool FieldPlayer::isClosestTeamMemberToBall()const {
  return team->getPlayerClosestToBall() == this;
}

Point3F FieldPlayer::Pursuit()
{
   Point3F ballPos = getSoccerBall()->getPosition();
   Point3F toEvader = ballPos - getPosition();
   double LookAheadTime = toEvader.len()/(8 + 8);
   Point3F FuturePos = getSoccerBall()->getPosition() + getSoccerBall()->getVelocity() * LookAheadTime;
//Con::errorf("postion %f %f", ballPos.x, getSoccerBall()->getPosition().y);  

   return FuturePos;
}

/*
Point3F FieldPlayer::RunToTarget()
{
  
}
*/

Point3F FieldPlayer::Interpose(Point3F target, double DistFromTarget)
{
   Point3F pos;
   Point3F vectorToTarget;
   vectorToTarget = getSoccerBall()->getPosition() - target;
   vectorToTarget.normalize();
   
   pos = target + vectorToTarget * DistFromTarget;
   
   return pos;
}

Point3F FieldPlayer::getRearTarget() {
  double xPosTarget = 31.0 + getSoccerBall()->getPosition().x * 8.0/70.0;
  double yPosTarget = getMyTeam()->getGoalPoint().y;

  return Point3F(xPosTarget, yPosTarget, 0.0);
}

double FieldPlayer::getDistFromTarget() {
  return 2.0;
}

bool FieldPlayer::ballWithinGoalieRange() {

   return (vec3DDistanceSq(getMyTeam()->getGoalPoint(), getSoccerBall()->getPosition()) <= 100.0);
}

Point3F FieldPlayer::getOffenseDestination() {
  
	Point3F dest = getHomePoint();
	/*
    Point3F ball = getMyTeam()->getPitch()->getBallPosition();

	ball.x = (ball.x - 35);
	dest.x = dest.x + ball.x/3.0;
	
	if(getMyTeam()->getTeam() == 0) {
	  if(ball.y < 20)
        dest.y = getHomePoint().y;
	  else if(ball.y > 60)
	    dest.y = getHomePoint().y + 40.0;
	  else
        dest.y = dest.y + ball.y - 20;
	}
	else {
	  if(ball.y > 100)
        dest.y = getHomePoint().y;
	  else if(ball.y < 60)
	    dest.y = getHomePoint().y - 40.0;
	  else
        dest.y = dest.y + ball.y - 100;

	}
*/
    return dest;

}

Point3F FieldPlayer::getDefenseDestination() {

	Point3F dest = getHomePoint();
/*
	Point3F ball = getMyTeam()->getPitch()->getBallPosition();

	ball.x = (ball.x - 35);
	dest.x = dest.x + ball.x/3.0;
	
	if(getMyTeam()->getTeam() == 0) {
	  if(ball.y <= 60)
        dest.y = getHomePoint().y;
	  else //if(ball.y > 60)
        dest.y = dest.y + ball.y - 20;
	}
	else {
	  if(ball.y >= 60)
        dest.y = dest.y + ball.y - 100;
	  else //if(ball.y < 60)
	    dest.y = getHomePoint().y - 40.0;
	}
*/
	return dest;
}

bool FieldPlayer::isThreatened() {
  for (int i = 0; i < team->getNumberOfPlayersOnTeam(); i++) {
    Point3F opponenentPosition = team->getOpponent()->playerArray[i]->getPosition();
	//if (isPositionInFrontOfPlayer(opponenentPosition)) {
	  if (vec3DDistanceSq(getPosition(), opponenentPosition) < getPlayerComfortZoneSq()) {
        return true; // thus if at anypoint the condition is satisfied return true and get out
	  }
	//}
  }
  return false; // this is the fall thru, we checked all opponenents and your are not threatened
}

bool FieldPlayer::isPositionInFrontOfPlayer(Point3F position) {
  Point3F ToSubject = position - getPosition();
  const MatrixF& mat = getTransform();
  Point3F dir = Point3F(0.0f, 0.0f, 0.0f);
  mat.getColumn(1,&dir);
  if (mDot(ToSubject,dir) > 0) 
    return true;
  else
   return false;
}

bool FieldPlayer::isPassForward(Point3F position) {

	if (getMyTeam()->getTeam() == 0) {
       if (getPosition().y < position.y)
		   return true;
	   else
		   return false;
	}
	else {
       if (getPosition().y > position.y)
		   return true;
	   else
		   return false; 
	}
}

void FieldPlayer::setHuman(bool h) {
  human = h;
  
}

bool FieldPlayer::aimAtObject(Point3F target) {
  // get eye vector of kicker
  MatrixF mat( EulerF( 0.0f, 0.0f, 0.0f ) );
  getEyeTransform(&mat);
  VectorF v2(0.0f,0.0f,0.0f);
  mat.getColumn(1,&v2); 

  // get vector to reciever
  VectorF v1 = target - getPosition();
  v1.normalize();
  v2.normalize();
  // calculate dot product to see if vectors line up
  if (mDot(v1,v2) > .80) 
    return true;
  else
    return false;
}

bool FieldPlayer::insideShootingZone() {

  double distanceSq =  vec3DDistanceSq(getPosition(), getMyTeam()->getOpponent()->getGoalPoint());

  if(distanceSq < 900)
	  return true;
  else
	  return false;
}

void FieldPlayer::airKick() {

    MatrixF mat( EulerF( 0.0f, 0.0f, 0.0f ) );
	getEyeTransform(&mat);
    VectorF v2(0.0f, 0.0f, 0.0f);
    mat.getColumn(1,&v2); 

    getSoccerBall()->unmount();
    

	double distance;
	if (!getHuman())
	  distance = getMyTeam()->getDistanceToTarget();
	else
	  distance = 1600;


	distance = mSqrt(distance);
    double throwForce = getMyTeam()->getPitch()->getBall()->calculateThrowForce(distance);
/*
	if(getMyTeam()->getReceiver() == NULL)
      throwForce = 15;
*/     	 
	//throwForce = 15;
    v2 *= throwForce; 

	//%vec = vectorAdd(%vec,"0 0 " @ %verticalForce);
    VectorF v3(0.0f, 0.0f, throwForce/2.0);
    v2 = v2 + v3;

    getSoccerBall()->applyImpulse(getPosition(), v2);

	clearAim();

	Con::executef("scheduleResetBallCollision");
	//Con::errorf("setControllingPlayer == null");
    getMyTeam()->setControllingPlayer(NULL);
    			
}


void FieldPlayer::Kick() {

    MatrixF mat( EulerF( 0.0f, 0.0f, 0.0f ) );
	getEyeTransform(&mat);
    VectorF v2(0.0f, 0.0f, 0.0f);
    mat.getColumn(1,&v2); 

    getSoccerBall()->unmount();
    

	double distance;
	if (!getHuman())
	  distance = getMyTeam()->getDistanceToTarget();
	else
	  distance = 1600;


	distance = mSqrt(distance);
    double throwForce = getMyTeam()->getPitch()->getBall()->calculateThrowForce(distance);
/*
	if(getMyTeam()->getReceiver() == NULL)
      throwForce = 15;
*/     	 
	//throwForce = 15;

    v2 *= throwForce; 

	//%vec = vectorAdd(%vec,"0 0 " @ %verticalForce);
    //VectorF v3(0.0f, 0.0f, throwForce/2.0);
   // v2 = v2 + v3;

    getSoccerBall()->applyImpulse(getPosition(), v2);

	clearAim();
	//getSoccerBall()->setCollisionTimeout(getMyTeam()->getPitch()->getCameraTroll());

	Con::executef("scheduleResetBallCollision");
	//Con::errorf("setControllingPlayer == null");
    getMyTeam()->setControllingPlayer(NULL);
    			
}


void FieldPlayer::setSquares(int s) {
	//if (getMyTeam()->getTeam() == 0) {
	  if (s == 0) {
		 Square[0] = Point3F(0.0f, 0.0f, 0.0f);
         Square[1] = Point3F(0.0f, 0.0f, 0.0f);
		 Square[2] = Point3F(0.0f, 0.0f, 0.0f);
		 Square[3] = Point3F(0.0f, 0.0f, 0.0f);
		 Square[4] = Point3F(0.0f, 0.0f, 0.0f);
		 Square[5] = Point3F(0.0f, 0.0f, 0.0f);
		 Square[6] = Point3F(0.0f, 0.0f, 0.0f);
		 Square[7] = Point3F(0.0f, 0.0f, 0.0f);
		 Square[8] = Point3F(0.0f, 0.0f, 0.0f);
	   }
   //}
}      


ConsoleMethod( FieldPlayer, setHomePoint, void, 3, 3, "(Point3F homePoint)"
              "Set the homePoint.\n\n") {
   Point3F pos = Point3F(0.0f, 0.0f, 0.0f);
   dSscanf( argv[2], "%f %f %f", &pos.x, &pos.y, &pos.z );
   object->setHomePoint(pos);
}
ConsoleMethod( FieldPlayer, setOffensiveHomePoint, void, 3, 3, "(Point3F offensiveHomePoint)"
              "Set the offensiveHomePoint.\n\n") {
   Point3F pos = Point3F(0.0f, 0.0f, 0.0f);
   dSscanf( argv[2], "%f %f %f", &pos.x, &pos.y, &pos.z );
   object->setOffensiveHomePoint(pos);
}
ConsoleMethod( FieldPlayer, setDefensiveHomePoint, void, 3, 3, "(Point3F defensiveHomePoint)"
              "Set the defensiveHomePoint.\n\n") {
   Point3F pos = Point3F(0.0f, 0.0f, 0.0f);
   dSscanf( argv[2], "%f %f %f", &pos.x, &pos.y, &pos.z );
   object->setDefensiveHomePoint(pos);
}
ConsoleMethod( FieldPlayer, setHomePointMatrixF, void, 3, 3, "(Transform T)")
{
   Point3F pos = Point3F(0.0f, 0.0f, 0.0f);
   const MatrixF& tmat = object->getTransform();
   tmat.getColumn(3,&pos);
   AngAxisF aa(tmat);

   dSscanf(argv[2],"%g %g %g %g %g %g %g",
           &pos.x,&pos.y,&pos.z,&aa.axis.x,&aa.axis.y,&aa.axis.z,&aa.angle);

   MatrixF mat;
   aa.setMatrix(&mat);
   mat.setColumn(3,pos);
   object->setHomePointMatrixF(mat);
}

ConsoleMethod( FieldPlayer, getHuman, bool, 2, 2,"" "getHuman") {
	return object->getHuman();
}

ConsoleMethod( FieldPlayer, isControllingPlayer, bool, 2, 2,"" "isControllingPlayer") {
	return object->isControllingPlayer();
}
ConsoleMethod( FieldPlayer, setHuman, void, 3, 3,"" "setHuman") {
    object->setHuman(dAtob(argv[2]));
}

ConsoleMethod(FieldPlayer, setTeam, void, 3, 3, "(SoccerTeam obj)"
              "set the Team Pointer.")
{
   SoccerTeam* steam = NULL;
   if (Sim::findObject(dAtoi(argv[2]),steam))
     object->setTeam(steam);
}

ConsoleMethod( FieldPlayer, getTeam, S32, 2, 2,"" "getTeam") {
	return object->getMyTeam()->getTeam();
}

ConsoleMethod( FieldPlayer, setSquares, void, 3, 3,"" "setSquares") {
    object->setSquares(dAtoi(argv[2]));
}
ConsoleMethod( FieldPlayer, kick, void, 2, 2,"" "kick") {
    object->Kick();
}
ConsoleMethod(FieldPlayer, setSoccerPitch, void, 3, 3, "(SoccerPitch obj)"
              "set the SoccerPitch Pointer.")
{
   SoccerPitch* spitch = NULL;
   if (Sim::findObject(dAtoi(argv[2]),spitch))
     object->setSoccerPitch(spitch);
}

bool FieldPlayer::getAIMove(Move *movePtr)
{
if (camTroll) {
   *movePtr = NullMove;

   // Use the eye as the current position.
   MatrixF eye;
   getEyeTransform(&eye);
   Point3F location = eye.getPosition();
   Point3F rotation = getRotation();
/*
   // Orient towards the aim point, aim object, or towards
   // our destination.
   if (mAimObject || mAimLocationSet || mMoveState == ModeMove) {

      // Update the aim position if we're aiming for an object
      if (mAimObject)
         mAimLocation = mAimObject->getPosition() + mAimOffset;
      else
         if (!mAimLocationSet)
            mAimLocation = mMoveDestination;

      F32 xDiff = mAimLocation.x - location.x;
      F32 yDiff = mAimLocation.y - location.y;
      if (!isZero(xDiff) || !isZero(yDiff)) {

         // First do Yaw
         // use the cur yaw between -Pi and Pi
         F32 curYaw = rotation.z;
         while (curYaw > M_2PI_F)
            curYaw -= M_2PI_F;
         while (curYaw < -M_2PI_F)
            curYaw += M_2PI_F;

         // find the yaw offset
         F32 newYaw = mAtan( xDiff, yDiff );
         F32 yawDiff = newYaw - curYaw;

         // make it between 0 and 2PI
         if( yawDiff < 0.0f )
            yawDiff += M_2PI_F;
         else if( yawDiff >= M_2PI_F )
            yawDiff -= M_2PI_F;

         // now make sure we take the short way around the circle
         if( yawDiff > M_PI_F )
            yawDiff -= M_2PI_F;
         else if( yawDiff < -M_PI_F )
            yawDiff += M_2PI_F;

         movePtr->yaw = yawDiff;

         // Next do pitch.
         if (!mAimObject && !mAimLocationSet) {
            // Level out if were just looking at our next way point.
            Point3F headRotation = getHeadRotation();
            movePtr->pitch = -headRotation.x;
         }
         else {
            // This should be adjusted to run from the
            // eye point to the object's center position. Though this
            // works well enough for now.
            F32 vertDist = mAimLocation.z - location.z;
            F32 horzDist = mSqrt(xDiff * xDiff + yDiff * yDiff);
            F32 newPitch = mAtan( horzDist, vertDist ) - ( M_PI_F / 2.0f );
            if (mFabs(newPitch) > 0.01f) {
               Point3F headRotation = getHeadRotation();
               movePtr->pitch = newPitch - headRotation.x;
            }
         }
      }
   }
*/
//    else {
//      // Level out if we're not doing anything else
      Point3F headRotation = getHeadRotation();
      movePtr->pitch = -headRotation.x;
//   }

   // Move towards the destination
   if (mMoveState == ModeMove) {
      F32 xDiff = mMoveDestination.x - location.x;
      F32 yDiff = mMoveDestination.y - location.y;

      // Check if we should mMove, or if we are 'close enough'
      if (mFabs(xDiff) < mMoveTolerance && mFabs(yDiff) < mMoveTolerance) {
         mMoveState = ModeStop;
         throwCallback("onReachDestination");
      }
      else {
         // Build move direction in world space
         if (isZero(xDiff))
            movePtr->y = (location.y > mMoveDestination.y) ? -1.0f : 1.0f;
         else
            if (isZero(yDiff))
               movePtr->x = (location.x > mMoveDestination.x) ? -1.0f : 1.0f;
            else
               if (mFabs(xDiff) > mFabs(yDiff)) {
                  F32 value = mFabs(yDiff / xDiff);
                  movePtr->y = (location.y > mMoveDestination.y) ? -value : value;
                  movePtr->x = (location.x > mMoveDestination.x) ? -1.0f : 1.0f;
               }
               else {
                  F32 value = mFabs(xDiff / yDiff);
                  movePtr->x = (location.x > mMoveDestination.x) ? -value : value;
                  movePtr->y = (location.y > mMoveDestination.y) ? -1.0f : 1.0f;
               }

         // Rotate the move into object space (this really only needs
         // a 2D matrix)
         Point3F newMove;
         MatrixF moveMatrix;
         moveMatrix.set(EulerF(0.0f, 0.0f, -(rotation.z + movePtr->yaw)));
         moveMatrix.mulV( Point3F( movePtr->x, movePtr->y, 0.0f ), &newMove );
         movePtr->x = newMove.x;
         movePtr->y = newMove.y;

         // Set movement speed.  We'll slow down once we get close
         // to try and stop on the spot...
         if (mMoveSlowdown) {
            F32 speed = mMoveSpeed;
            F32 dist = mSqrt(xDiff*xDiff + yDiff*yDiff);
            F32 maxDist = 5.0f;
            if (dist < maxDist)
               speed *= dist / maxDist;
            movePtr->x *= speed;
            movePtr->y *= speed;
         }
		 else {
            movePtr->x *= mMoveSpeed;
            movePtr->y *= mMoveSpeed;
		 }

         // We should check to see if we are stuck...
         if (location == mLastLocation) {
            throwCallback("onMoveStuck");
            mMoveState = ModeStop;
         }
      }
   }

   // Test for target location in sight if it's an object. The LOS is
   // run from the eye position to the center of the object's bounding,
   // which is not very accurate.
   if (mAimObject) {
      MatrixF eyeMat;
      getEyeTransform(&eyeMat);
      eyeMat.getColumn(3,&location);
      Point3F targetLoc = mAimObject->getBoxCenter();

      // This ray ignores non-static shapes. Cast Ray returns true
      // if it hit something.
      RayInfo dummy;
      if (getContainer()->castRay( location, targetLoc,
            InteriorObjectType | StaticShapeObjectType | StaticObjectType |
            AtlasObjectType | TerrainObjectType, &dummy)) {
         if (mTargetInLOS) {
            throwCallback( "onTargetExitLOS" );
            mTargetInLOS = false;
         }
      }
      else
         if (!mTargetInLOS) {
            throwCallback( "onTargetEnterLOS" );
            mTargetInLOS = true;
         }
   }

   // Replicate the trigger state into the move so that
   // triggers can be controlled from scripts.
   for( int i = 0; i < MaxTriggerKeys; i++ )
      movePtr->trigger[i] = getImageTriggerState(i);
   movePtr->clamp();
   return true;
}
else  {
   *movePtr = NullMove;

   // Use the eye as the current position.
   MatrixF eye;
   getEyeTransform(&eye);
   Point3F location = eye.getPosition();
   Point3F rotation = getRotation();

   // Orient towards the aim point, aim object, or towards
   // our destination.
   if (mAimObject || mAimLocationSet || mMoveState == ModeMove) {

      // Update the aim position if we're aiming for an object
      if (mAimObject)
         mAimLocation = mAimObject->getPosition() + mAimOffset;
      else
         if (!mAimLocationSet)
            mAimLocation = mMoveDestination;

      F32 xDiff = mAimLocation.x - location.x;
      F32 yDiff = mAimLocation.y - location.y;
      if (!isZero(xDiff) || !isZero(yDiff)) {

         // First do Yaw
         // use the cur yaw between -Pi and Pi
         F32 curYaw = rotation.z;
         while (curYaw > M_2PI_F)
            curYaw -= M_2PI_F;
         while (curYaw < -M_2PI_F)
            curYaw += M_2PI_F;

         // find the yaw offset
         F32 newYaw = mAtan( xDiff, yDiff );
         F32 yawDiff = newYaw - curYaw;

         // make it between 0 and 2PI
         if( yawDiff < 0.0f )
            yawDiff += M_2PI_F;
         else if( yawDiff >= M_2PI_F )
            yawDiff -= M_2PI_F;

         // now make sure we take the short way around the circle
         if( yawDiff > M_PI_F )
            yawDiff -= M_2PI_F;
         else if( yawDiff < -M_PI_F )
            yawDiff += M_2PI_F;

         movePtr->yaw = yawDiff;

         // Next do pitch.
         if (!mAimObject && !mAimLocationSet) {
            // Level out if were just looking at our next way point.
            Point3F headRotation = getHeadRotation();
            movePtr->pitch = -headRotation.x;
         }
         else {
            // This should be adjusted to run from the
            // eye point to the object's center position. Though this
            // works well enough for now.
            F32 vertDist = mAimLocation.z - location.z;
            F32 horzDist = mSqrt(xDiff * xDiff + yDiff * yDiff);
            F32 newPitch = mAtan( horzDist, vertDist ) - ( M_PI_F / 2.0f );
            if (mFabs(newPitch) > 0.01f) {
               Point3F headRotation = getHeadRotation();
               movePtr->pitch = newPitch - headRotation.x;
            }
         }
      }
   }
   else {
      // Level out if we're not doing anything else
      Point3F headRotation = getHeadRotation();
      movePtr->pitch = -headRotation.x;
   }

   // Move towards the destination
   if (mMoveState == ModeMove) {
      F32 xDiff = mMoveDestination.x - location.x;
      F32 yDiff = mMoveDestination.y - location.y;

      // Check if we should mMove, or if we are 'close enough'
      if (mFabs(xDiff) < mMoveTolerance && mFabs(yDiff) < mMoveTolerance) {
         mMoveState = ModeStop;
         throwCallback("onReachDestination");
      }
      else {
         // Build move direction in world space
         if (isZero(xDiff))
            movePtr->y = (location.y > mMoveDestination.y) ? -1.0f : 1.0f;
         else
            if (isZero(yDiff))
               movePtr->x = (location.x > mMoveDestination.x) ? -1.0f : 1.0f;
            else
               if (mFabs(xDiff) > mFabs(yDiff)) {
                  F32 value = mFabs(yDiff / xDiff);
                  movePtr->y = (location.y > mMoveDestination.y) ? -value : value;
                  movePtr->x = (location.x > mMoveDestination.x) ? -1.0f : 1.0f;
               }
               else {
                  F32 value = mFabs(xDiff / yDiff);
                  movePtr->x = (location.x > mMoveDestination.x) ? -value : value;
                  movePtr->y = (location.y > mMoveDestination.y) ? -1.0f : 1.0f;
               }

         // Rotate the move into object space (this really only needs
         // a 2D matrix)
         Point3F newMove;
         MatrixF moveMatrix;
         moveMatrix.set(EulerF(0.0f, 0.0f, -(rotation.z + movePtr->yaw)));
         moveMatrix.mulV( Point3F( movePtr->x, movePtr->y, 0.0f ), &newMove );
         movePtr->x = newMove.x;
         movePtr->y = newMove.y;

         // Set movement speed.  We'll slow down once we get close
         // to try and stop on the spot...
         if (mMoveSlowdown) {
            F32 speed = mMoveSpeed;
            F32 dist = mSqrt(xDiff*xDiff + yDiff*yDiff);
            F32 maxDist = 5.0f;
            if (dist < maxDist)
               speed *= dist / maxDist;
            movePtr->x *= speed;
            movePtr->y *= speed;
         }
		 else {
            movePtr->x *= mMoveSpeed;
            movePtr->y *= mMoveSpeed;
		 }

         // We should check to see if we are stuck...
         if (location == mLastLocation) {
            throwCallback("onMoveStuck");
            mMoveState = ModeStop;
         }
      }
   }

   // Test for target location in sight if it's an object. The LOS is
   // run from the eye position to the center of the object's bounding,
   // which is not very accurate.
   if (mAimObject) {
      MatrixF eyeMat;
      getEyeTransform(&eyeMat);
      eyeMat.getColumn(3,&location);
      Point3F targetLoc = mAimObject->getBoxCenter();

      // This ray ignores non-static shapes. Cast Ray returns true
      // if it hit something.
      RayInfo dummy;
      if (getContainer()->castRay( location, targetLoc,
            InteriorObjectType | StaticShapeObjectType | StaticObjectType |
            AtlasObjectType | TerrainObjectType, &dummy)) {
         if (mTargetInLOS) {
            throwCallback( "onTargetExitLOS" );
            mTargetInLOS = false;
         }
      }
      else
         if (!mTargetInLOS) {
            throwCallback( "onTargetEnterLOS" );
            mTargetInLOS = true;
         }
   }

   // Replicate the trigger state into the move so that
   // triggers can be controlled from scripts.
   for( int i = 0; i < MaxTriggerKeys; i++ )
      movePtr->trigger[i] = getImageTriggerState(i);
   movePtr->clamp();
   return true;
}
}



