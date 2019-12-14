#ifndef SOCCERTEAMSTATES_H
#define SOCCERTEAMSTATES_H
#include "soccerTeamState.h"

class SoccerTeam;

//------------------------------------------------------------------------
class FreezeTeam : public SoccerTeamState
{ 
private:
  FreezeTeam(){}
public:
  //this is a singleton
  static FreezeTeam* Instance();
  void enter(SoccerTeam* team);
  void execute(SoccerTeam* team);
  void exit(SoccerTeam* team);
  //bool OnMessage(SoccerTeam*, const Telegram&){return false;}
};

//------------------------------------------------------------------------
class Attacking : public SoccerTeamState
{ 
private:
  Attacking(){}
public:
  //this is a singleton
  static Attacking* Instance();
  void enter(SoccerTeam* team);
  void execute(SoccerTeam* team);
  void exit(SoccerTeam* team);
  //bool OnMessage(SoccerTeam*, const Telegram&){return false;}
};
//------------------------------------------------------------------------

class Defending : public SoccerTeamState
{ 
private:
  Defending(){}
public:
  //this is a singleton
  static Defending* Instance();
  void enter(SoccerTeam* team);
  void execute(SoccerTeam* team);
  void exit(SoccerTeam* team);
  //bool OnMessage(SoccerTeam*, const Telegram&){return false;}
};
//------------------------------------------------------------------------


class PrepareForKickOff : public SoccerTeamState
{ 
private:
  PrepareForKickOff(){}
public:
  //this is a singleton
  static PrepareForKickOff* Instance();
  void enter(SoccerTeam* team);
  void execute(SoccerTeam* team);
  void exit(SoccerTeam* team);
  //bool OnMessage(SoccerTeam*, const Telegram&){return false;}
};

//------------------------------------------------------------------------

class SixTopLeftOffenseTeam : public SoccerTeamState
{ 
private:
  SixTopLeftOffenseTeam(){}
public:
  //this is a singleton
  static SixTopLeftOffenseTeam* Instance();
  void enter(SoccerTeam* team);
  void execute(SoccerTeam* team);
  void exit(SoccerTeam* team);
  //bool OnMessage(SoccerTeam*, const Telegram&){return false;}
};

//------------------------------------------------------------------------

class SixTopLeftDefenseTeam : public SoccerTeamState
{ 
private:
  SixTopLeftDefenseTeam(){}
public:
  //this is a singleton
  static SixTopLeftDefenseTeam* Instance();
  void enter(SoccerTeam* team);
  void execute(SoccerTeam* team);
  void exit(SoccerTeam* team);
  //bool OnMessage(SoccerTeam*, const Telegram&){return false;}
};

//------------------------------------------------------------------------

class SixTopRightOffenseTeam : public SoccerTeamState
{ 
private:
  SixTopRightOffenseTeam(){}
public:
  //this is a singleton
  static SixTopRightOffenseTeam* Instance();
  void enter(SoccerTeam* team);
  void execute(SoccerTeam* team);
  void exit(SoccerTeam* team);
  //bool OnMessage(SoccerTeam*, const Telegram&){return false;}
};



//------------------------------------------------------------------------

class SixTopRightDefenseTeam : public SoccerTeamState
{ 
private:
  SixTopRightDefenseTeam(){}
public:
  //this is a singleton
  static SixTopRightDefenseTeam* Instance();
  void enter(SoccerTeam* team);
  void execute(SoccerTeam* team);
  void exit(SoccerTeam* team);
  //bool OnMessage(SoccerTeam*, const Telegram&){return false;}
};

//------------------------------------------------------------------------

class CornerTopLeftOffenseTeam : public SoccerTeamState
{ 
private:
  CornerTopLeftOffenseTeam(){}
public:
  //this is a singleton
  static CornerTopLeftOffenseTeam* Instance();
  void enter(SoccerTeam* team);
  void execute(SoccerTeam* team);
  void exit(SoccerTeam* team);
  //bool OnMessage(SoccerTeam*, const Telegram&){return false;}
};

//------------------------------------------------------------------------

class CornerTopLeftDefenseTeam : public SoccerTeamState
{ 
private:
  CornerTopLeftDefenseTeam(){}
public:
  //this is a singleton
  static CornerTopLeftDefenseTeam* Instance();
  void enter(SoccerTeam* team);
  void execute(SoccerTeam* team);
  void exit(SoccerTeam* team);
  //bool OnMessage(SoccerTeam*, const Telegram&){return false;}
};

//------------------------------------------------------------------------

class CornerTopRightOffenseTeam : public SoccerTeamState
{ 
private:
  CornerTopRightOffenseTeam(){}
public:
  //this is a singleton
  static CornerTopRightOffenseTeam* Instance();
  void enter(SoccerTeam* team);
  void execute(SoccerTeam* team);
  void exit(SoccerTeam* team);
  //bool OnMessage(SoccerTeam*, const Telegram&){return false;}
};



//------------------------------------------------------------------------

class CornerTopRightDefenseTeam : public SoccerTeamState
{ 
private:
  CornerTopRightDefenseTeam(){}
public:
  //this is a singleton
  static CornerTopRightDefenseTeam* Instance();
  void enter(SoccerTeam* team);
  void execute(SoccerTeam* team);
  void exit(SoccerTeam* team);
  //bool OnMessage(SoccerTeam*, const Telegram&){return false;}
};



//------------------------------------------------------------------------




class ThrowInTeam : public SoccerTeamState
{ 
private:
  ThrowInTeam(){}
public:
  //this is a singleton
  static ThrowInTeam* Instance();
  void enter(SoccerTeam* team);
  void execute(SoccerTeam* team);
  void exit(SoccerTeam* team);
  //bool OnMessage(SoccerTeam*, const Telegram&){return false;}
};


class CornerKickTeam : public SoccerTeamState
{ 
private:
  CornerKickTeam(){}
public:
  //this is a singleton
  static CornerKickTeam* Instance();
  void enter(SoccerTeam* team);
  void execute(SoccerTeam* team);
  void exit(SoccerTeam* team);
  //bool OnMessage(SoccerTeam*, const Telegram&){return false;}
};

class GoalKickTeam : public SoccerTeamState
{ 
private:
  GoalKickTeam(){}
public:
  //this is a singleton
  static GoalKickTeam* Instance();
  void enter(SoccerTeam* team);
  void execute(SoccerTeam* team);
  void exit(SoccerTeam* team);
  //bool OnMessage(SoccerTeam*, const Telegram&){return false;}
};

#endif