#ifndef SOCCERTEAMSTATE_H
#define SOCCERTEAMSTATE_H

class SoccerTeam;

class SoccerTeamState
{
public:

  virtual ~SoccerTeamState(){}

  //this will execute when the state is entered
  virtual void enter(SoccerTeam*)=0;

  //this is the states normal update function
  virtual void execute(SoccerTeam*)=0;

  //this will execute when the state is exited. (My word, isn't
  //life full of surprises... ;o))
  virtual void exit(SoccerTeam*)=0;
};

#endif