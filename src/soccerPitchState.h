#ifndef SOCCERPITCHSTATE_H
#define SOCCERPITCHSTATE_H

class SoccerPitch;

class SoccerPitchState
{
public:

  virtual ~SoccerPitchState(){}

  //this will execute when the state is entered
  virtual void enter(SoccerPitch*)=0;

  //this is the states normal update function
  virtual void execute(SoccerPitch*)=0;

  //this will execute when the state is exited. (My word, isn't
  //life full of surprises... ;o))
  virtual void exit(SoccerPitch*)=0;
};

#endif