/**
 *  @file
 *  $Id: GsimSteppingActionMessenger.cc,v 1.2 2006/12/06 18:44:00 nanjo Exp $
 *  $Log: GsimSteppingActionMessenger.cc,v $
 *  Revision 1.2  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 */
#include "GsimKernel/GsimSteppingActionMessenger.h"
#include "GsimKernel/GsimSteppingAction.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UImanager.hh"

#include <string>

GsimSteppingActionMessenger::GsimSteppingActionMessenger(GsimSteppingAction* steppingAction)
  :m_steppingAction(steppingAction)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  std::string dirName="/GsimSteppingAction/";
  m_steppingActionDir = new G4UIdirectory(G4String(dirName.c_str()));
  m_steppingActionDir->SetGuidance("Control GsimSteppingAction.");
  
  {
    std::string commandName=dirName;
    commandName+="setParticleColor";
    m_cmdSetParticleColor = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdSetParticleColor->SetGuidance("setParticleColor  pdgCode colorName.");
    m_cmdSetParticleColor->SetGuidance("setParticleColor  particleName colorName.");
    m_cmdSetParticleColor->SetGuidance("ColorNames are ");
    m_cmdSetParticleColor->SetGuidance(" white gray20 gray50 gray70 gray75 black");
    m_cmdSetParticleColor->SetGuidance(" red green blue cyan magenta yellow purple4");
    m_cmdSetParticleColor->SetGuidance(" deeppink lightskyblue lightyellow orange ");
    m_cmdSetParticleColor->SetGuidance(" violet purple ");
    m_cmdSetParticleColor->SetGuidance(" If white is selected, such tracks are not drawn.");
    m_cmdSetParticleColor->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  
}


GsimSteppingActionMessenger::~GsimSteppingActionMessenger()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  delete m_cmdSetParticleColor;
  delete m_steppingActionDir;
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  
}

void GsimSteppingActionMessenger::SetNewValue(G4UIcommand* command,G4String aValue)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif


  aValue=G4UImanager::GetUIpointer()->SolveAlias(aValue.data());
  
  if (command == m_cmdSetParticleColor) {
    G4String tmpline = aValue;
    G4String tmpID;
    G4String tmpName;
    bool ok=true;
    GsimUtil* util = GsimUtil::getUtil();
    ok=util->shift(tmpline,tmpID);
    int pid=std::atoi(tmpID.data());
    if(ok) 
      ok=util->shift(tmpline,tmpName);
    if(ok) {
      if(pid!=0) {
	m_steppingAction
	  ->setTrackColor(pid,std::string(tmpName.data()));
      } else {
	m_steppingAction
	  ->setTrackColor(std::string(tmpID.data()),std::string(tmpName.data()));
      }
    } else {
      std::string msg = "Wrong number of paramaeters at GsimSteppingActionMessenger::";
      msg+="SetNewValue(G4UIcommand* command,G4String newValue=";
      msg+=std::string(aValue.data()) ;
      msg+=")";
      GsimMessage::getInstance()
	->report("warning",msg);
      return;
    }
  } else {
    std::string msg = "Wrong command  at GsimSteppingActionMessenger::";
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
