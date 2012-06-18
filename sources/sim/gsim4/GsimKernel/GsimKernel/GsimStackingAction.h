/**
 *  @file
 *  @brief  GsimStackingAction
 *  $Id: GsimStackingAction.h,v 1.1 2007/02/04 12:14:38 nanjo Exp $
 *  $Log: GsimStackingAction.h,v $
 *  Revision 1.1  2007/02/04 12:14:38  nanjo
 *  GsimStackingAction is added.
 *
 */
#ifndef GsimStackingAction_h
#define GsimStackingAction_h

#include "G4UserStackingAction.hh"
#include "globals.hh"

#include <list>

class GsimStackingActionMessenger;

class GsimStackingAction : public G4UserStackingAction
{
public:
  GsimStackingAction();
  virtual ~GsimStackingAction();

  virtual void PrepareNewEvent();
  virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
  virtual void NewStage();
  
  virtual void triggerPrimaryEndZ(double z1=-999,double z2=-999);


  virtual void setBriefDtectorOrder(std::list<std::string> briefNameList);
  
private:
  GsimStackingActionMessenger* m_messenger;
  bool   m_withPrimaryEndTrigger;
  double m_triggerPrimaryEndZ1;
  double m_triggerPrimaryEndZ2;
  int    m_stage;
  std::list<std::string>   m_briefNamePriorityList;
  std::list<int>           m_briefIDPriorityList;
  std::list<int>::iterator m_briefIDPriorityIterator;
  int                      m_priorBriefID;
  bool                     m_priorityRest;
};

inline void GsimStackingAction::setBriefDtectorOrder(std::list<std::string> briefNameList)
{
  m_briefNamePriorityList=briefNameList;
  m_priorityRest=true;
}

#endif





