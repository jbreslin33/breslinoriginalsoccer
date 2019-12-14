#ifndef GOALKEEPERSTATE_H
#define GOALKEEPERSTATE_H

#include "goalKeeper.h"

//class FieldPlayer;

class GoalKeeperState
{
public:

  virtual ~GoalKeeperState(){}

  //this will execute when the state is entered
  virtual void enter(GoalKeeper*)=0;

  //this is the states normal update function
  virtual void execute(GoalKeeper*)=0;

  //this will execute when the state is exited. (My word, isn't
  //life full of surprises... ;o))
  virtual void exit(GoalKeeper*)=0;
};

#endif