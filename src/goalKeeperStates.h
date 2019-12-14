#ifndef GOALKEEPERSTATES_H
#define GOALKEEPERSTATES_H
#include "fieldPlayerState.h"
#include "goalKeeper.h"
//#include "soccer/ai/goalKeeper/goalKeeperState.h"

//class FieldPlayer;

//------------------------------------------------------------------------
class TendGoal : public FieldPlayerState
{
private:
  TendGoal(){}
public:
  //this is a singleton
  static TendGoal* Instance();
  void enter(FieldPlayer* player);
  void execute(FieldPlayer* player);
  void exit(FieldPlayer* player);
  //bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};

class GoaliePursueBall : public FieldPlayerState
{
private:
  GoaliePursueBall(){}
public:
  //this is a singleton
  static GoaliePursueBall* Instance();
  void enter(FieldPlayer* player);
  void execute(FieldPlayer* player);
  void exit(FieldPlayer* player);
  //bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};


class PutBallBackInPlay : public FieldPlayerState
{
private:
  PutBallBackInPlay(){}
public:
  //this is a singleton
  static PutBallBackInPlay* Instance();
  void enter(FieldPlayer* player);
  void execute(FieldPlayer* player);
  void exit(FieldPlayer* player);
  //bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};

class GoalieAiming : public FieldPlayerState
{
private:
  GoalieAiming(){}
public:
  //this is a singleton
  static GoalieAiming* Instance();
  void enter(FieldPlayer* player);
  void execute(FieldPlayer* player);
  void exit(FieldPlayer* player);
  //bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};

class Punt : public FieldPlayerState
{
private:
  Punt(){}
public:
  //this is a singleton
  static Punt* Instance();
  void enter(FieldPlayer* player);
  void execute(FieldPlayer* player);
  void exit(FieldPlayer* player);
  //bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};


#endif