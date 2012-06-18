/**
 *  $Id: GsimEventActionMessenger.cc,v 1.13 2007/02/04 12:55:41 nanjo Exp $
 *  $Log: GsimEventActionMessenger.cc,v $
 *  Revision 1.13  2007/02/04 12:55:41  nanjo
 *  Fast simulation 3 is added for shower check.
 *
 *  Revision 1.12  2007/01/12 15:24:23  nanjo
 *  Add flag to store empty data or not.
 *
 *  Revision 1.11  2006/12/09 21:34:09  nanjo
 *  briefHistory is corrected and dictionary write.
 *
 *  Revision 1.10  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 */
#include "GsimKernel/GsimEventActionMessenger.h"
#include "GsimKernel/GsimEventAction.h"
#include "GsimKernel/GsimStackingAction.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimPersistency/GsimPersistencyManager.h"

#include "G4EventManager.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UImanager.hh"

#include <string>

GsimEventActionMessenger::GsimEventActionMessenger(GsimEventAction* eventAction)
  :m_eventAction(eventAction)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  std::string dirName="/GsimEventAction/";
  m_eventActionDir = new G4UIdirectory(G4String(dirName.c_str()));
  m_eventActionDir->SetGuidance("Control GsimEventAction.");
  

  {
    std::string commandName=dirName;
    commandName+="setVisualizationMode";
    m_cmdSetVisualizationMode = new G4UIcmdWithAnInteger(G4String(commandName.c_str()),this);
    m_cmdSetVisualizationMode->SetGuidance("setVisualzationMode 0 : no visualization");
    m_cmdSetVisualizationMode->SetGuidance("                    1 : draw trajectory");
    m_cmdSetVisualizationMode->SetGuidance("                    2 : draw trajectory+hit");
    m_cmdSetVisualizationMode->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setDumpMode";
    m_cmdSetDumpMode = new G4UIcmdWithAnInteger(G4String(commandName.c_str()),this);
    m_cmdSetDumpMode->SetGuidance("setDumpode 0 : no dump.");
    m_cmdSetDumpMode->SetGuidance("           1 : dump first 10 events.");
    m_cmdSetDumpMode->SetGuidance("           2 : dump all events.");
    m_cmdSetDumpMode->SetGuidance("           3 : dump all events with timing.");
    m_cmdSetDumpMode->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setAccumulationNumber";
    m_cmdSetAccumulationNumber = new G4UIcmdWithAnInteger(G4String(commandName.c_str()),this);
    m_cmdSetAccumulationNumber->SetGuidance("setDumpode  0 : accumulate infinitely.");
    m_cmdSetAccumulationNumber->SetGuidance("            N : accumulate N event.");
    m_cmdSetAccumulationNumber->SetGuidance("           -N : accumulate N event and pause.");
    m_cmdSetAccumulationNumber->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setVerboseLevel";
    m_cmdSetVerboseLevel = new G4UIcmdWithAnInteger(G4String(commandName.c_str()),this);
    m_cmdSetVerboseLevel->SetGuidance("setVerboseLevel  0 : off.");
    m_cmdSetVerboseLevel->SetGuidance("setVerboseLevel  1 : error.");
    m_cmdSetVerboseLevel->SetGuidance("setVerboseLevel  2 : warning.");
    m_cmdSetVerboseLevel->SetGuidance("setVerboseLevel  3 : info.");
    m_cmdSetVerboseLevel->SetGuidance("setVerboseLevel  4 : debug.");
    m_cmdSetVerboseLevel->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="writeDicitionary";
    m_cmdWriteDictionary = new G4UIcmdWithABool(G4String(commandName.c_str()),this);
    m_cmdWriteDictionary->SetGuidance("writeDicitionary true/false");
    m_cmdWriteDictionary->SetGuidance(" default is false");
    m_cmdWriteDictionary->SetGuidance("write text-file dictionary.");
    m_cmdWriteDictionary->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setSkipEmptyData";
    m_cmdSetSkipEmptyData= new G4UIcmdWithABool(G4String(commandName.c_str()),this);
    m_cmdSetSkipEmptyData->SetGuidance("setSkipEmptyData true/false");
    m_cmdSetSkipEmptyData->SetGuidance(" default : true");
    m_cmdSetSkipEmptyData->SetGuidance("Skip event with no hit/digi data.");
    m_cmdSetSkipEmptyData->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  
}


GsimEventActionMessenger::~GsimEventActionMessenger()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  
  delete m_cmdSetVisualizationMode;
  delete m_cmdSetDumpMode;
  delete m_cmdSetAccumulationNumber;
  delete m_cmdSetVerboseLevel;
  delete m_cmdWriteDictionary;
  delete m_cmdSetSkipEmptyData;
  delete m_eventActionDir;
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  
}

void GsimEventActionMessenger::SetNewValue(G4UIcommand* command,G4String aValue)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif


  aValue=G4UImanager::GetUIpointer()->SolveAlias(aValue.data());
  
  if(command == m_cmdSetVisualizationMode) {
    m_eventAction
      ->setVisualizationMode(m_cmdSetVisualizationMode->GetNewIntValue(aValue));
  } else if (command == m_cmdSetDumpMode){
    m_eventAction
      ->setDumpMode(m_cmdSetDumpMode->GetNewIntValue(aValue));
  } else if(command == m_cmdSetAccumulationNumber){
    m_eventAction
      ->setAccumulationNumber(m_cmdSetAccumulationNumber->GetNewIntValue(aValue));
  } else if (command == m_cmdSetVerboseLevel) {
    int thLevel=int(m_cmdSetVerboseLevel->GetNewIntValue(aValue));
    GsimMessage::getInstance()->setVervoseLevel(thLevel);
  } else if ( command == m_cmdWriteDictionary) {
    GsimPersistencyManager::getPersistencyManager()
      ->writeDictionary(m_cmdWriteDictionary->GetNewBoolValue(aValue));
  } else if ( command == m_cmdSetSkipEmptyData) {
    m_eventAction
      ->setSkipEmptyData(m_cmdSetSkipEmptyData->GetNewBoolValue(aValue));
  } else {
    std::string msg = "Wrong command  at GsimEventActionMessenger::";
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
