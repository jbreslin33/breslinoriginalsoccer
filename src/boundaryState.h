#ifndef BOUNDARYSTATE_H
#define BOUNDARYSTATE_H

class Boundary;

class BoundaryState
{
public:

  virtual ~BoundaryState(){}

  //this will execute when the state is entered
  virtual void enter(Boundary*)=0;

  //this is the states normal update function
  virtual void execute(Boundary*)=0;

  //this will execute when the state is exited. (My word, isn't
  //life full of surprises... ;o))
  virtual void exit(Boundary*)=0;
};

#endif