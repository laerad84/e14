/**
 *  @file
 *  $Id: GsimStackingActionMessenger.cc,v 1.1 2007/02/04 12:14:38 nanjo Exp $
 *  $Log: GsimStackingActionMessenger.cc,v $
 *  Revision 1.1  2007/02/04 12:14:38  nanjo
 *  GsimStackingAction is added.
 *
 */
#include "GsimKernel/GsimStackingActionMessenger.h"
#include "GsimKernel/GsimStackingAction.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UImanager.hh"

#include <string>

GsimStackingActionMessenger::GsimStackingActionMessenger(GsimStackingAction* stackingAction)
  :m_stackingAction(stackingAction)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  std::string dirName="/GsimStackingAction/";
  m_stackingActionDir = new G4UIdirectory(G4String(dirName.c_str()));
  m_stackingActionDir->SetGuidance("Control GsimStackingAction.");
  
  {
    std::string commandName=dirName;
    commandName+="triggerPrimaryEndZ";
    m_cmdTriggerPrimaryEndZ= new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdTriggerPrimaryEndZ->SetGuidance("triggerPrimaryEndZ z1 z2");
    m_cmdTriggerPrimaryEndZ->SetGuidance("Store only events with");
    m_cmdTriggerPrimaryEndZ->SetGuidance(" z of the end point of primary particle ");
    m_cmdTriggerPrimaryEndZ->SetGuidance(" from z1 to z2.");
    m_cmdTriggerPrimaryEndZ->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setBriefDtectorOrder";
    m_cmdSetBriefDtectorOrder = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdSetBriefDtectorOrder->SetGuidance("setBriefDtectorOrder det0 det1 ...");
    m_cmdSetBriefDtectorOrder->SetGuidance("Start detector simulation in the order,");
    m_cmdSetBriefDtectorOrder->SetGuidance("    det0 det1 ...");
    m_cmdSetBriefDtectorOrder->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  
}


GsimStackingActionMessenger::~GsimStackingActionMessenger()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  delete m_cmdTriggerPrimaryEndZ;
  delete m_cmdSetBriefDtectorOrder;
  delete m_stackingActionDir;
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  
}

void GsimStackingActionMessenger::SetNewValue(G4UIcommand* command,G4String aValue)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif


  aValue=G4UImanager::GetUIpointer()->SolveAlias(aValue.data());
  
  if (command == m_cmdTriggerPrimaryEndZ) {
    GsimUtil* util = GsimUtil::getUtil();
    G4String tmpline = aValue;
    G4String tmpout;
    std::vector<double> vec;
    bool ok=true;
    while(ok) {
      ok=util->shift(tmpline,tmpout);
      if(ok) {
	vec.push_back(util->interpret(tmpout));
      }
    }
    if(vec.size()!=2) {
      std::string msg = "Wrong number of paramaeters at GsimEventActionMessenger::";
      msg+="SetNewValue(G4UIcommand* command,G4String newValue=";
      msg+=std::string(aValue.data()) ;
      msg+=")";
      GsimMessage::getInstance()
	->report("warning",msg);
      return;
    }
    m_stackingAction->triggerPrimaryEndZ(vec[0],vec[1]);
  } else if(command==m_cmdSetBriefDtectorOrder) {
    GsimUtil* util = GsimUtil::getUtil();
    G4String tmpline = aValue;
    G4String tmpout;
    std::list<std::string> briefNameList;
    bool ok=true;
    while(ok) {
      ok=util->shift(tmpline,tmpout);
      if(ok) {
	briefNameList.push_back(std::string(tmpout.data()));
      }
    }
    m_stackingAction->setBriefDtectorOrder(briefNameList);
  } else {
    std::string msg = "Wrong command  at GsimStackingActionMessenger::";
    msg+="SetNewValue(G4UIcommand* command,G4String newValue=";
    msg+=std::string(aValue.data()) ;
    msg+=")";
    GsimMessage::getInstance()
      ->report("warning",msg);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  
}
