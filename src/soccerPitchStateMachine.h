#ifndef SOCCERPITCHSTATEMACHINE_H
#define SOCCERPITCHSTATEMACHINE_H
#include "soccerPitchState.h"

class SoccerPitchStateMachine
{
private:

  SoccerPitch*   m_pOwner;  //a pointer to the agent that owns this instance
  SoccerPitchState*    m_pCurrentState; // a pointer to the current State
  SoccerPitchState*   m_pPreviousState;  //a record of the last state the agent was in
  SoccerPitchState*   m_pGlobalState;   // a pointer to the global state

public:

  SoccerPitchStateMachine(SoccerPitch* owner):m_pOwner(owner),
	                               m_pCurrentState(NULL),
                                   m_pPreviousState(NULL),
                                   m_pGlobalState(NULL)
  {}

  virtual ~SoccerPitchStateMachine(){}

  void setCurrentState(SoccerPitchState* s){m_pCurrentState = s;}   //use these methods to initialize the FSM
  void setGlobalState(SoccerPitchState* s) {m_pGlobalState = s;}
  void setPreviousState(SoccerPitchState* s){m_pPreviousState = s;}

  void  update()const //call this to update the FSM
  {
    if(m_pGlobalState)   m_pGlobalState->execute(m_pOwner);  //execute global state if it exists
    if (m_pCurrentState) m_pCurrentState->execute(m_pOwner); //execute current state if it exists
  }
 
  void  changeState(SoccerPitchState* pNewState) //change to a new state
  {
    m_pPreviousState = m_pCurrentState; //keep a record of the previous state

    if(m_pCurrentState)
       m_pCurrentState->exit(m_pOwner);  //call the exit method of the existing state

    m_pCurrentState = pNewState;   //change state to the new state

    if(m_pCurrentState)
       m_pCurrentState->enter(m_pOwner); //call the entry method of the new state
  }

 
  void  revertToPreviousState()  //change state back to the previous state
  {
    changeState(m_pPreviousState);
  }
/*
  returns true if the current state's type is equal to the type of the
  class passed as a parameter.
  bool  isInState(const State& st)const
  {
    return typeid(*m_pCurrentState) == typeid(st);
  }
*/

  SoccerPitchState*  currentState()  const{return m_pCurrentState;}
  SoccerPitchState*  globalState()   const{return m_pGlobalState;}
  SoccerPitchState*  previousState() const{return m_pPreviousState;}
};
#endif


