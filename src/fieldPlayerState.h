#ifndef FIELDPLAYERSTATE_H
#define FIELDPLAYERSTATE_H

class FieldPlayer;

class FieldPlayerState
{
public:

  virtual ~FieldPlayerState(){}

  //this will execute when the state is entered
  virtual void enter(FieldPlayer*)=0;

  //this is the states normal update function
  virtual void execute(FieldPlayer*)=0;

  //this will execute when the state is exited. (My word, isn't
  //life full of surprises... ;o))
  virtual void exit(FieldPlayer*)=0;
};

#endif