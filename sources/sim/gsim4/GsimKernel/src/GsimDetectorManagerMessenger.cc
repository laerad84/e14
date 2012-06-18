/**
 *  $Id: GsimDetectorManagerMessenger.cc,v 1.4 2006/08/01 05:27:55 nanjo Exp $
 *  $Log: GsimDetectorManagerMessenger.cc,v $
 *  Revision 1.4  2006/08/01 05:27:55  nanjo
 *  GsimSpectrum is added. Debug print is updated. With/without Digi is implemented.
 *
 *  Revision 1.3  2006/03/22 13:01:25  nanjo
 *  Aliases in macrofile can be used in the Messengers.
 *
 *  Revision 1.2  2006/03/14 18:02:55  nanjo
 *  Fix outerMaterial of CC04 and CC05.
 *
 *  Revision 1.1  2006/01/26 04:53:30  nanjo
 *  Detector and persistency classes are added.
 *
 */
#include "GsimKernel/GsimDetectorManagerMessenger.h"
#include "GsimKernel/GsimDetectorManager.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UImanager.hh"

GsimDetectorManagerMessenger::GsimDetectorManagerMessenger(GsimDetectorManager* detectorManager)
  :m_detectorManager(detectorManager)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  std::string dirName="/GsimDetectorManager/";
  m_detectorManagerDir = new G4UIdirectory(G4String(dirName.c_str()));
  m_detectorManagerDir->SetGuidance("Control GsimDetectorManager.");
  

  {
    std::string commandName=dirName;
    commandName+="print";
    m_cmdPrint = new G4UIcmdWithoutParameter(G4String(commandName.c_str()),this);
    m_cmdPrint->SetGuidance("print");
    m_cmdPrint->SetGuidance("Print detector properties for all.");
    m_cmdPrint->SetGuidance("Units of shape parameters are mm or rad.");
    m_cmdPrint->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="update";
    m_cmdUpdate = new G4UIcmdWithoutParameter(G4String(commandName.c_str()),this);
    m_cmdUpdate->SetGuidance("update");
    m_cmdUpdate->SetGuidance("Update properties for all detectors.");
    m_cmdUpdate->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="redraw";
    m_cmdRedraw = new G4UIcmdWithoutParameter(G4String(commandName.c_str()),this);
    m_cmdRedraw->SetGuidance("Redraw detector for visualization.");
    m_cmdRedraw->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="renewMessenger";
    m_cmdRenewMessenger = new G4UIcmdWithoutParameter(G4String(commandName.c_str()),this);
    m_cmdRenewMessenger->SetGuidance("renewMessenger");
    m_cmdRenewMessenger->SetGuidance("Renew detector messengers.");
    m_cmdRenewMessenger->SetGuidance("Do after /GsimDetector/placeDetector...");
    m_cmdRenewMessenger->AvailableForStates(G4State_PreInit,G4State_Idle);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif

}


GsimDetectorManagerMessenger::~GsimDetectorManagerMessenger()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  
  delete m_cmdPrint;
  delete m_cmdUpdate;
  delete m_cmdRedraw;
  delete m_cmdRenewMessenger;
  
  delete m_detectorManagerDir;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}



void GsimDetectorManagerMessenger::SetNewValue(G4UIcommand* command,G4String aValue)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif


  aValue=G4UImanager::GetUIpointer()->SolveAlias(aValue.data());
  
  if(command == m_cmdPrint) {
    m_detectorManager->print();
  } else if(command == m_cmdUpdate) {
    m_detectorManager->update();
  } else if(command == m_cmdRedraw) {
    m_detectorManager->redraw();
  } else if(command == m_cmdRenewMessenger) {
    m_detectorManager->renewMessenger();
  } else {
    std::string msg = "Wrong command  at GsimDetectorManagerMessenger::";
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
