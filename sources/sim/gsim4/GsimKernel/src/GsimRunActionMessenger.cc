/**
 *  $Id: GsimRunActionMessenger.cc,v 1.4 2006/12/06 18:44:00 nanjo Exp $
 *  $Log: GsimRunActionMessenger.cc,v $
 *  Revision 1.4  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 */
#include "GsimKernel/GsimRunActionMessenger.h"
#include "GsimKernel/GsimRunAction.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimPersistencyManager.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimData/GsimRandData.h"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UImanager.hh"


GsimRunActionMessenger::GsimRunActionMessenger(GsimRunAction* runAction)
  :m_runAction(runAction)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  std::string dirName="/GsimRunAction/";
  m_runActionDir = new G4UIdirectory(G4String(dirName.c_str()));
  m_runActionDir->SetGuidance("Control GsimRunAction.");
  
  {
    std::string commandName=dirName;
    commandName+="setRunIDBase";
    m_cmdSetRunIDBase = new G4UIcmdWithAnInteger(G4String(commandName.c_str()),this);
    m_cmdSetRunIDBase->SetGuidance("setRunIDBase runIDBase(integer)");
    m_cmdSetRunIDBase->SetGuidance("runID=runIDBase + (internal run number)");
    m_cmdSetRunIDBase->AvailableForStates(G4State_PreInit,G4State_Idle);
  }
  
  {
    std::string commandName=dirName;
    commandName+="setCycleOfEventSeedStore";
    m_cmdSetCycleOfEventSeedStore = new G4UIcmdWithAnInteger(G4String(commandName.c_str()),this);
    m_cmdSetCycleOfEventSeedStore->SetGuidance("setCycleOfEventSeedStore cycle(integer)");
    m_cmdSetCycleOfEventSeedStore->SetGuidance("The eventSeed is stored per cycle.");
    m_cmdSetCycleOfEventSeedStore->SetGuidance(" default: 1000");
    m_cmdSetCycleOfEventSeedStore->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setSeed";
    m_cmdSetSeed = new G4UIcmdWithAnInteger(G4String(commandName.c_str()),this);
    m_cmdSetSeed->SetGuidance("setSeed seed(integer)");
    m_cmdSetSeed->SetGuidance("Set seed.");
    m_cmdSetSeed->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="dumpSeed";
    m_cmdDumpSeed = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdDumpSeed->SetGuidance("dumpSeed fileName runNumber eventNumber");
    m_cmdDumpSeed->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="loadSeed";
    m_cmdLoadSeed = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdLoadSeed->SetGuidance("loadSeed fileName runNumber eventNumber");
    m_cmdLoadSeed->SetGuidance("loadSeed asciiFileName");
    m_cmdLoadSeed->SetGuidance("         sciiFileFormta : ");
    m_cmdLoadSeed->SetGuidance("             randomEngineID ");
    m_cmdLoadSeed->SetGuidance("             seed[0]  ");
    m_cmdLoadSeed->SetGuidance("             seed[1]  ");
    m_cmdLoadSeed->SetGuidance("               ...    ");
    m_cmdLoadSeed->SetGuidance("             seed[624]");
    m_cmdLoadSeed->SetGuidance("             seedCount");
    m_cmdLoadSeed->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  


#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif

}


GsimRunActionMessenger::~GsimRunActionMessenger()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  delete m_cmdSetRunIDBase;
  delete m_cmdSetCycleOfEventSeedStore;
  delete m_cmdSetSeed;
  delete m_cmdDumpSeed;
  delete m_cmdLoadSeed;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif

}



void GsimRunActionMessenger::SetNewValue(G4UIcommand* command,G4String aValue)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif


  aValue=G4UImanager::GetUIpointer()->SolveAlias(aValue.data());

  if(command==m_cmdSetRunIDBase) {
    m_runAction->setRunNumberBase(m_cmdSetSeed->GetNewIntValue(aValue));
  } else if(command == m_cmdSetCycleOfEventSeedStore) {
    GsimPersistencyManager* persistencyManager =
      GsimPersistencyManager::getPersistencyManager();
    persistencyManager->setCycleOfEventSeedStore(m_cmdSetCycleOfEventSeedStore->GetNewIntValue(aValue));
  } else if(command == m_cmdSetSeed) {
    m_runAction->setSeed(m_cmdSetSeed->GetNewIntValue(aValue));
  } else if(command == m_cmdDumpSeed) {
    GsimUtil* util = GsimUtil::getUtil();
    G4String tmpline = aValue;
    G4String tmpout[3];
    
    bool ok=true;
    for(int i=0;i<3;i++) {
      ok=util->shift(tmpline,tmpout[i]);
      if(!ok) {
	std::string msg = "Wrong number of paramaeters at GsimRunActionMessenger::";
	msg+="SetNewValue(G4UIcommand* command,G4String newValue=";
	msg+=std::string(aValue.data()) ;
	msg+=")";
	GsimMessage::getInstance()
	  ->report("warning",msg);
	return;
      }
    }
    std::string fileName=std::string(tmpout[0].data());
    int runNumber=std::atoi( tmpout[1].data() );
    int eventNumber=std::atoi( tmpout[2].data() );
    std::vector<unsigned long> seedVector;
    bool isOK=GsimRandData::getSeed(fileName,runNumber,eventNumber,seedVector);
    if(isOK) {
      for(std::vector<unsigned long>::iterator it=seedVector.begin();
	  it!=seedVector.end();it++) {
	std::cout << (*it) << std::endl;
      }
    }
  } else if(command == m_cmdLoadSeed) {
    GsimUtil* util = GsimUtil::getUtil();
    G4String tmpline = aValue;
    G4String tmpout[3];
    
    bool ok=true;
    int cnt=0;
    while(ok) {
      ok=util->shift(tmpline,tmpout[0]);
      if(ok) cnt++;
    }
    if(cnt==3) {
      tmpline = aValue;
      for(int i=0;i<3;i++) {
	ok=util->shift(tmpline,tmpout[i]);
      }
      std::string fileName=std::string(tmpout[0].data());
      int runNumber=std::atoi( tmpout[1].data() );
      int eventNumber=std::atoi( tmpout[2].data() );
      m_runAction->setSeed(fileName,runNumber,eventNumber);
      return;
    } else if(cnt==1) {
      std::vector<unsigned long> seedVector;
      tmpline = aValue;
      ok=util->shift(tmpline,tmpout[0]);
      std::string fileName=std::string(tmpout[0].data());
      unsigned long val;
      std::ifstream fi(fileName.c_str());
      while(fi>>val) {
	seedVector.push_back(val);
      }
      m_runAction->setSeed(seedVector);
      return;
    } else {
      //Error
      std::string msg = "Wrong number of paramaeters at GsimRunActionMessenger::";
	msg+="SetNewValue(G4UIcommand* command,G4String newValue=";
	msg+=std::string(aValue.data()) ;
	msg+=")";
	GsimMessage::getInstance()
	  ->report("warning",msg);
      return;
    }
  } else {
    std::string msg = "Wrong command  at GsimRunActionMessenger::";
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
