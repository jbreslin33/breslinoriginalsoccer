#ifndef SOCCERTEAMSTATEMACHINE_H
#define SOCCERTEAMSTATEMACHINE_H
#include "soccerTeamState.h"

class SoccerTeamStateMachine
{
private:

  SoccerTeam*   m_pOwner;  //a pointer to the agent that owns this instance
  SoccerTeamState*    m_pCurrentState; // a pointer to the current State
  SoccerTeamState*   m_pPreviousState;  //a record of the last state the agent was in
  SoccerTeamState*   m_pGlobalState;   // a pointer to the global state

public:

  SoccerTeamStateMachine(SoccerTeam* owner):m_pOwner(owner),
	                               m_pCurrentState(NULL),
                                   m_pPreviousState(NULL),
                                   m_pGlobalState(NULL)
  {}

  virtual ~SoccerTeamStateMachine(){}

  void setCurrentState(SoccerTeamState* s){m_pCurrentState = s;}   //use these methods to initialize the FSM
  void setGlobalState(SoccerTeamState* s) {m_pGlobalState = s;}
  void setPreviousState(SoccerTeamState* s){m_pPreviousState = s;}

  void  update()const //call this to update the FSM
  {
    if(m_pGlobalState)   m_pGlobalState->execute(m_pOwner);  //execute global state if it exists
    if (m_pCurrentState) m_pCurrentState->execute(m_pOwner); //execute current state if it exists
  }
 
  void  changeState(SoccerTeamState* pNewState) //change to a new state
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

  SoccerTeamState*  currentState()  const{return m_pCurrentState;}
  SoccerTeamState*  globalState()   const{return m_pGlobalState;}
  SoccerTeamState*  previousState() const{return m_pPreviousState;}
};
#endif


