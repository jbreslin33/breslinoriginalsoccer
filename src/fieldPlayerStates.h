#ifndef FIELDPLAYERSTATES_H
#define FIELDPLAYERSTATES_H
#include "fieldPlayerState.h"

class FieldPlayer;

//------------------------------------------------------------------------
class ChaseBall : public FieldPlayerState
{
private:
  ChaseBall(){}
public:
  //this is a singleton
  static ChaseBall* Instance();
  void enter(FieldPlayer* player);
  void execute(FieldPlayer* player);
  void exit(FieldPlayer* player);
  //bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};
//------------------------------------------------------------------------
class PursueBall : public FieldPlayerState
{
private:
  PursueBall(){}
public:
  //this is a singleton
  static PursueBall* Instance();
  void enter(FieldPlayer* player);
  void execute(FieldPlayer* player);
  void exit(FieldPlayer* player);
  //bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};
//------------------------------------------------------------------------
class KickBall : public FieldPlayerState
{
private:
  KickBall(){}
public:
  //this is a singleton
  static KickBall* Instance();
  void enter(FieldPlayer* player);
  void execute(FieldPlayer* player);
  void exit(FieldPlayer* player);
  //bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};
//------------------------------------------------------------------------
class Wait : public FieldPlayerState
{
private:
  Wait(){}
public:
  //this is a singleton
  static Wait* Instance();
  void enter(FieldPlayer* player);
  void execute(FieldPlayer* player);
  void exit(FieldPlayer* player);
  //bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};
//------------------------------------------------------------------------
class DefensiveBase : public FieldPlayerState
{
private:
  DefensiveBase(){}
public:
  //this is a singleton
  static DefensiveBase* Instance();
  void enter(FieldPlayer* player);
  void execute(FieldPlayer* player);
  void exit(FieldPlayer* player);
  //bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};
//------------------------------------------------------------------------
class Dribble : public FieldPlayerState
{
private:
  Dribble(){}
public:
  //this is a singleton
  static Dribble* Instance();
  void enter(FieldPlayer* player);
  void execute(FieldPlayer* player);
  void exit(FieldPlayer* player);
  //bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};
//------------------------------------------------------------------------
class Human : public FieldPlayerState
{
private:
  Human(){}
public:
  //this is a singleton
  static Human* Instance();
  void enter(FieldPlayer* player);
  void execute(FieldPlayer* player);
  void exit(FieldPlayer* player);
  //bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};
//------------------------------------------------------------------------
class FreezePlayer : public FieldPlayerState
{
private:
  FreezePlayer(){}
public:
  //this is a singleton
  static FreezePlayer* Instance();
  void enter(FieldPlayer* player);
  void execute(FieldPlayer* player);
  void exit(FieldPlayer* player);
  //bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};
class Aiming : public FieldPlayerState
{
private:
  Aiming(){}
public:
  //this is a singleton
  static Aiming* Instance();
  void enter(FieldPlayer* player);
  void execute(FieldPlayer* player);
  void exit(FieldPlayer* player);
  //bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};

class Square : public FieldPlayerState
{
private:
  Square(){}
public:
  //this is a singleton
  static Square* Instance();
  void enter(FieldPlayer* player);
  void execute(FieldPlayer* player);
  void exit(FieldPlayer* player);
  //bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};

class Receiver : public FieldPlayerState
{
private:
  Receiver(){}
public:
  //this is a singleton
  static Receiver* Instance();
  void enter(FieldPlayer* player);
  void execute(FieldPlayer* player);
  void exit(FieldPlayer* player);
  //bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};

class ThrowInPlayer : public FieldPlayerState
{
private:
  ThrowInPlayer(){}
public:
  //this is a singleton
  static ThrowInPlayer* Instance();
  void enter(FieldPlayer* player);
  void execute(FieldPlayer* player);
  void exit(FieldPlayer* player);
  //bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};

class GoalKickPlayer : public FieldPlayerState
{
private:
  GoalKickPlayer(){}
public:
  //this is a singleton
  static GoalKickPlayer* Instance();
  void enter(FieldPlayer* player);
  void execute(FieldPlayer* player);
  void exit(FieldPlayer* player);
  //bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};

class CornerKickPlayer : public FieldPlayerState
{
private:
  CornerKickPlayer(){}
public:
  //this is a singleton
  static CornerKickPlayer* Instance();
  void enter(FieldPlayer* player);
  void execute(FieldPlayer* player);
  void exit(FieldPlayer* player);
  //bool OnMessage(FieldPlayer*, const Telegram&){return false;}
};

//------------------------------------------------------------------------
class DoNothing : public FieldPlayerState
{
private:
  DoNothing(){}
public:
  //this is a singleton
  static DoNothing* Instance();
  void enter(FieldPlayer* player);
  void execute(FieldPlayer* player);
  void exit(FieldPlayer* player);
};

//------------------------------------------------------------------------
class FollowDribbler : public FieldPlayerState
{
private:
  FollowDribbler(){}
public:
  //this is a singleton
  static FollowDribbler* Instance();
  void enter(FieldPlayer* player);
  void execute(FieldPlayer* player);
  void exit(FieldPlayer* player);
};

//------------------------------------------------------------------------
class FollowLooseBall : public FieldPlayerState
{
private:
  FollowLooseBall(){}
public:
  //this is a singleton
  static FollowLooseBall* Instance();
  void enter(FieldPlayer* player);
  void execute(FieldPlayer* player);
  void exit(FieldPlayer* player);
};


#endif