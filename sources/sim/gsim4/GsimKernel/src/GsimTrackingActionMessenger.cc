/**
 *  @file
 *  $Id: GsimTrackingActionMessenger.cc,v 1.5 2007/02/04 12:25:46 nanjo Exp $
 *  $Log: GsimTrackingActionMessenger.cc,v $
 *  Revision 1.5  2007/02/04 12:25:46  nanjo
 *  SetTrackHistory is added.
 *
 *  Revision 1.4  2006/12/09 21:34:09  nanjo
 *  briefHistory is corrected and dictionary write.
 *
 *  Revision 1.3  2006/12/09 00:45:06  nanjo
 *  dump.
 *
 *  Revision 1.2  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 */
#include "GsimKernel/GsimTrackingActionMessenger.h"
#include "GsimKernel/GsimTrackingAction.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UImanager.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithoutParameter.hh"

#include <string>

GsimTrackingActionMessenger::GsimTrackingActionMessenger(GsimTrackingAction* trackingAction)
  :m_trackingAction(trackingAction)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  std::string dirName="/GsimTrackingAction/";
  m_trackingActionDir = new G4UIdirectory(G4String(dirName.c_str()));
  m_trackingActionDir->SetGuidance("Control GsimTrackingAction.");
  

  {
    std::string commandName=dirName;
    commandName+="setBriefTrackStore";
    m_cmdSetBriefTrackStore = new G4UIcmdWithABool(G4String(commandName.c_str()),this);
    m_cmdSetBriefTrackStore->SetGuidance("setBriefTrackStroe true/false");
    m_cmdSetBriefTrackStore->SetGuidance("  (Default: true)  ");
    m_cmdSetBriefTrackStore->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setForceStorePrimary";
    m_cmdSetForceStorePrimary = new G4UIcmdWithABool(G4String(commandName.c_str()),this);
    m_cmdSetForceStorePrimary->SetGuidance("setForceStroePrimary true/false");
    m_cmdSetForceStorePrimary->SetGuidance("Store primary even if setBriefTrackStroe=false.");
    m_cmdSetForceStorePrimary->SetGuidance("  (Default: true)  ");
    m_cmdSetForceStorePrimary->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setTrackHistory";
    m_cmdSetTrackHistory = new G4UIcmdWithABool(G4String(commandName.c_str()),this);
    m_cmdSetTrackHistory->SetGuidance("setTrackHistory true/false");
    m_cmdSetTrackHistory->SetGuidance("Store vlume history associated with a track.");
    m_cmdSetTrackHistory->SetGuidance("  (Default: true)  ");
    m_cmdSetTrackHistory->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setTrackDump";
    m_cmdSetTrackDump = new G4UIcmdWithABool(G4String(commandName.c_str()),this);
    m_cmdSetTrackDump->SetGuidance("setTrackDump true/false");
    m_cmdSetTrackDump->SetGuidance("Dump tracks at production.");
    m_cmdSetTrackDump->SetGuidance("  (Default: false)  ");
    m_cmdSetTrackDump->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="addPIDToMonitor";
    m_cmdAddPIDToMonitor = new G4UIcmdWithAnInteger(G4String(commandName.c_str()),this);
    m_cmdAddPIDToMonitor->SetGuidance("addPIDToMonitor pid");
    m_cmdAddPIDToMonitor->SetGuidance("A track with the pid will be stored");
    m_cmdAddPIDToMonitor->SetGuidance("  in addition ot tracks before/after decay.");
    m_cmdAddPIDToMonitor->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="clearPIDToMonitor";
    m_cmdClearPIDToMonitor = new G4UIcmdWithoutParameter(G4String(commandName.c_str()),this);
    m_cmdClearPIDToMonitor->SetGuidance("clearPIDToMonitor");
    m_cmdClearPIDToMonitor->SetGuidance("clear all pids to monitor.");
    m_cmdClearPIDToMonitor->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  
  {
    std::string commandName=dirName;
    commandName+="addPIDToTrigger";
    m_cmdAddPIDToTrigger = new G4UIcmdWithAnInteger(G4String(commandName.c_str()),this);
    m_cmdAddPIDToTrigger->SetGuidance("addPIDToTrigger pid");
    m_cmdAddPIDToTrigger->SetGuidance("A track with the pid will be triggered.");
    m_cmdAddPIDToTrigger->SetGuidance("If not, the event is discarded.");
    m_cmdAddPIDToTrigger->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="clearPIDToTrigger";
    m_cmdClearPIDToTrigger = new G4UIcmdWithoutParameter(G4String(commandName.c_str()),this);
    m_cmdClearPIDToTrigger->SetGuidance("clearPIDToTrigger");
    m_cmdClearPIDToTrigger->SetGuidance("clear all pids to trigger.");
    m_cmdClearPIDToTrigger->AvailableForStates(G4State_PreInit,G4State_Idle);
  }


  {
    std::string commandName=dirName;
    commandName+="addPIDToKill";
    m_cmdAddPIDToKill = new G4UIcmdWithAnInteger(G4String(commandName.c_str()),this);
    m_cmdAddPIDToKill->SetGuidance("addPIDToKill pid");
    m_cmdAddPIDToKill->SetGuidance("A track with the pid will be killed.");
    m_cmdAddPIDToKill->SetGuidance("If not, the event is discarded.");
    m_cmdAddPIDToKill->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="clearPIDToKill";
    m_cmdClearPIDToKill = new G4UIcmdWithoutParameter(G4String(commandName.c_str()),this);
    m_cmdClearPIDToKill->SetGuidance("clearPIDToKill");
    m_cmdClearPIDToKill->SetGuidance("clear all pids to kill.");
    m_cmdClearPIDToKill->AvailableForStates(G4State_PreInit,G4State_Idle);
  }


  {
    std::string commandName=dirName;
    commandName+="setStoreAllTracks";
    m_cmdSetStoreAllTracks = new G4UIcmdWithABool(G4String(commandName.c_str()),this);
    m_cmdSetStoreAllTracks->SetGuidance("setStoreAllTracks true/false");
    m_cmdSetStoreAllTracks->SetGuidance("  (Default: false)  ");
    m_cmdSetStoreAllTracks->AvailableForStates(G4State_PreInit,G4State_Idle);
  }
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


GsimTrackingActionMessenger::~GsimTrackingActionMessenger()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  
  delete m_cmdSetBriefTrackStore;
  delete m_cmdSetForceStorePrimary;
  delete m_cmdSetTrackHistory;
  delete m_cmdSetTrackDump;
  delete m_cmdAddPIDToMonitor;
  delete m_cmdClearPIDToMonitor;
  delete m_cmdAddPIDToTrigger;
  delete m_cmdClearPIDToTrigger;
  delete m_cmdAddPIDToKill;
  delete m_cmdClearPIDToKill;
  delete m_cmdSetStoreAllTracks;
  delete m_trackingActionDir;
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif

}

void GsimTrackingActionMessenger::SetNewValue(G4UIcommand* command,G4String aValue)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  aValue=G4UImanager::GetUIpointer()->SolveAlias(aValue.data());
  
  if(command == m_cmdSetBriefTrackStore) {
    m_trackingAction
      ->setBriefTrackStore(m_cmdSetBriefTrackStore->GetNewBoolValue(aValue));
  } else if(command == m_cmdSetForceStorePrimary) {
    m_trackingAction
      ->setForceStorePrimary(m_cmdSetBriefTrackStore->GetNewBoolValue(aValue));
  } else if(command == m_cmdSetTrackHistory) {
    m_trackingAction
      ->setTrackHistory(m_cmdSetTrackHistory->GetNewBoolValue(aValue));
  } else if(command == m_cmdSetTrackDump) {
    m_trackingAction
      ->setTrackDump(m_cmdSetBriefTrackStore->GetNewBoolValue(aValue));
  } else if(command == m_cmdAddPIDToMonitor) {
    m_trackingAction
      ->addPIDToMonitor(m_cmdAddPIDToMonitor->GetNewIntValue(aValue));
  } else if(command == m_cmdClearPIDToMonitor) {
    m_trackingAction->clearPIDToMonitor();
  } else if(command == m_cmdAddPIDToTrigger) {
    m_trackingAction
      ->addPIDToTrigger(m_cmdAddPIDToTrigger->GetNewIntValue(aValue));
  } else if(command == m_cmdClearPIDToTrigger) {
    m_trackingAction->clearPIDToTrigger();
  } else if(command == m_cmdAddPIDToKill) {
    m_trackingAction
      ->addPIDToKill(m_cmdAddPIDToKill->GetNewIntValue(aValue));
  } else if(command == m_cmdClearPIDToKill) {
    m_trackingAction->clearPIDToKill();
  } else if(command == m_cmdSetStoreAllTracks) {
    m_trackingAction
      ->setStoreAllTracks(m_cmdSetStoreAllTracks->GetNewBoolValue(aValue));
  } else {
    std::string msg = "Wrong command  at GsimTrackingActionMessenger::";
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
