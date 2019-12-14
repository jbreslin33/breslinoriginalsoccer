#ifndef BOUNDARYSTATES_H
#define BOUNDARYSTATES_H
#include "boundaryState.h"

//class SoccerPitch;

//------------------------------------------------------------------------
class NormalPlay : public BoundaryState
{ 
private:
  NormalPlay(){}
public:
  //this is a singleton
  static NormalPlay* Instance();
  void enter(Boundary* pitch);
  void execute(Boundary* pitch);
  void exit(Boundary* pitch);
  //bool OnMessage(SoccerTeam*, const Telegram&){return false;}
};

//------------------------------------------------------------------------

class TopGoal : public BoundaryState
{ 
private:
  TopGoal(){}
public:
  //this is a singleton
  static TopGoal* Instance();
  void enter(Boundary* pitch);
  void execute(Boundary* pitch);
  void exit(Boundary* pitch);
  //bool OnMessage(SoccerTeam*, const Telegram&){return false;}
};

//------------------------------------------------------------------------

class FreeKickTop : public BoundaryState
{ 
private:
  FreeKickTop(){}
public:
  //this is a singleton
  static FreeKickTop* Instance();
  void enter(Boundary* pitch);
  void execute(Boundary* pitch);
  void exit(Boundary* pitch);
  //bool OnMessage(SoccerTeam*, const Telegram&){return false;}
};

//------------------------------------------------------------------------

class BottomGoal : public BoundaryState
{ 
private:
  BottomGoal(){}
public:
  //this is a singleton
  static BottomGoal* Instance();
  void enter(Boundary* pitch);
  void execute(Boundary* pitch);
  void exit(Boundary* pitch);
  //bool OnMessage(SoccerTeam*, const Telegram&){return false;}
};

//------------------------------------------------------------------------

class FreeKickBottom : public BoundaryState
{ 
private:
  FreeKickBottom(){}
public:
  //this is a singleton
  static FreeKickBottom* Instance();
  void enter(Boundary* pitch);
  void execute(Boundary* pitch);
  void exit(Boundary* pitch);
  //bool OnMessage(SoccerTeam*, const Telegram&){return false;}
};

//------------------------------------------------------------------------

class ThrowInLeft : public BoundaryState
{ 
private:
  ThrowInLeft(){}
public:
  //this is a singleton
  static ThrowInLeft* Instance();
  void enter(Boundary* pitch);
  void execute(Boundary* pitch);
  void exit(Boundary* pitch);
  //bool OnMessage(SoccerTeam*, const Telegram&){return false;}
};

//------------------------------------------------------------------------

class ThrowInRight : public BoundaryState
{ 
private:
  ThrowInRight(){}
public:
  //this is a singleton
  static ThrowInRight* Instance();
  void enter(Boundary* pitch);
  void execute(Boundary* pitch);
  void exit(Boundary* pitch);
  //bool OnMessage(SoccerTeam*, const Telegram&){return false;}
};

//------------------------------------------------------------------------

#endif