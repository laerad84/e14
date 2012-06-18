/**
 *  $Id: GsimSensitiveDetectorMessenger.cc,v 1.4 2007/02/04 12:30:22 nanjo Exp $
 *  $Log: GsimSensitiveDetectorMessenger.cc,v $
 *  Revision 1.4  2007/02/04 12:30:22  nanjo
 *  Online veto threshold is added.
 *
 *  Revision 1.3  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 */
#include "GsimKernel/GsimSensitiveDetectorMessenger.h"
#include "GsimKernel/GsimSensitiveDetector.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UImanager.hh"


GsimSensitiveDetectorMessenger::GsimSensitiveDetectorMessenger(GsimSensitiveDetector* sensitiveDetector)
  :m_sensitiveDetector(sensitiveDetector)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  std::string dirName="/GsimSensitiveDetector/";
  dirName+=m_sensitiveDetector->getName();
  dirName+="/";
  m_sensitiveDetectorDir = new G4UIdirectory(G4String(dirName.c_str()));
  m_sensitiveDetectorDir->SetGuidance("Control GsimSensitiveDetector.");
  

  {
    std::string commandName=dirName;
    commandName+="setSensitiveMode";
    m_cmdSetSensitiveMode = new G4UIcmdWithAnInteger(G4String(commandName.c_str()),this);
    m_cmdSetSensitiveMode->SetGuidance("setSensitiveMode 0/1/2");
    m_cmdSetSensitiveMode->SetGuidance("   0 : charged particle sensitive.");
    m_cmdSetSensitiveMode->SetGuidance("   1 : Edep sensitive. (default) ");
    m_cmdSetSensitiveMode->SetGuidance("   2 : Optical photon sensitive.");
    m_cmdSetSensitiveMode->SetGuidance("   3 : Any particle sensitive.");
    m_cmdSetSensitiveMode->SetGuidance("Set sensitive mode.");
    m_cmdSetSensitiveMode->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="storeHit";
    m_cmdStoreHit = new G4UIcmdWithABool(G4String(commandName.c_str()),this);
    m_cmdStoreHit->SetGuidance("storeHit true/false");
    m_cmdStoreHit->SetGuidance("Store hit or not.");
    m_cmdStoreHit->SetGuidance(" The hit means each step in the sensitive detector.");
    m_cmdStoreHit->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="storeDigi";
    m_cmdStoreDigi = new G4UIcmdWithABool(G4String(commandName.c_str()),this);
    m_cmdStoreDigi->SetGuidance("storeDigi true/false");
    m_cmdStoreDigi->SetGuidance("Store digi.");
    m_cmdStoreDigi->SetGuidance(" The digi is sum of edep, timing,... /channel.");
    m_cmdStoreDigi->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setThisCopyNoFactor";
    m_cmdSetThisCopyNoFactor = new G4UIcmdWithAnInteger(G4String(commandName.c_str()),this);
    m_cmdSetThisCopyNoFactor->SetGuidance("setThisCopyNoFactor factor(integer)");
    m_cmdSetThisCopyNoFactor->SetGuidance("  default : -1 --> no effect.");
    m_cmdSetThisCopyNoFactor->SetGuidance("  detector->setSensitiveDetector(sdName,thisCopyNo)");
    m_cmdSetThisCopyNoFactor->SetGuidance("  SD->setThisCopyNoFactor(32)");
    m_cmdSetThisCopyNoFactor->SetGuidance("  hit channel=(mother-volume copyNo)+thisCopyNo*factor");
    m_cmdSetThisCopyNoFactor->SetGuidance("  For example :  MB ");
    m_cmdSetThisCopyNoFactor->SetGuidance("      inner volume : copyNo=0");
    m_cmdSetThisCopyNoFactor->SetGuidance("      outer volume : copyNo=1");
    m_cmdSetThisCopyNoFactor->SetGuidance("      mother-volume multiplicity : 32.");
    m_cmdSetThisCopyNoFactor->SetGuidance("        => inner 0-31+0*32= 0-31 ch");
    m_cmdSetThisCopyNoFactor->SetGuidance("        => outer 0-31+1*32=32-63 ch");
    m_cmdSetThisCopyNoFactor->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setDeepCopyNoFactor";
    m_cmdSetDeepCopyNoFactor = new G4UIcmdWithAnInteger(G4String(commandName.c_str()),this);
    m_cmdSetDeepCopyNoFactor->SetGuidance("setDeepCopyNoFactor deepFactor(integer)");
    m_cmdSetThisCopyNoFactor->SetGuidance("  hit channel=deepFactor*(mother-volume copyNo)+thisCopyNo*factor");
    m_cmdSetDeepCopyNoFactor->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setClusterID";
    m_cmdSetClusterID = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdSetClusterID->SetGuidance("setClusterID ch(integer) cl(integer)");
    m_cmdSetClusterID->SetGuidance("The channel, ch, belongs to the clusterID, cl.");
    m_cmdSetClusterID->SetGuidance("This is used for cluster definition.");
    m_cmdSetClusterID->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setOnlineVetoThreshold";
    m_cmdSetOnlineVetoThreshold = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdSetOnlineVetoThreshold->SetGuidance("setOnlineVetoThreshold 10*MeV");
    m_cmdSetOnlineVetoThreshold->SetGuidance("Set OnlineVetoThreshold.");
    m_cmdSetOnlineVetoThreshold->SetGuidance("This is used for event skip.");
    m_cmdSetOnlineVetoThreshold->SetGuidance("If totalEnergy>onlineVethThr., skip.");
    m_cmdSetOnlineVetoThreshold->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setTdcThreshold";
    m_cmdSetTdcThreshold = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdSetTdcThreshold->SetGuidance("setTdcThreshold 1*MeV");
    m_cmdSetTdcThreshold->SetGuidance("Set TdcThreshold.");
    m_cmdSetTdcThreshold->SetGuidance("This is used to set the digi timing");
    m_cmdSetTdcThreshold->SetGuidance("default : 0");
    m_cmdSetTdcThreshold->AvailableForStates(G4State_PreInit,G4State_Idle);
  }


  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif

}


GsimSensitiveDetectorMessenger::~GsimSensitiveDetectorMessenger()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  delete m_cmdSetSensitiveMode;
  delete m_cmdStoreHit;
  delete m_cmdStoreDigi;
  delete m_cmdSetThisCopyNoFactor;
  delete m_cmdSetDeepCopyNoFactor;
  delete m_cmdSetClusterID;
  delete m_sensitiveDetectorDir;
  delete m_cmdSetOnlineVetoThreshold;
  delete m_cmdSetTdcThreshold;
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif

}



void GsimSensitiveDetectorMessenger::SetNewValue(G4UIcommand* command,G4String aValue)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif


  aValue=G4UImanager::GetUIpointer()->SolveAlias(aValue.data());

  if(command == m_cmdSetSensitiveMode) {
    int imode = m_cmdSetSensitiveMode->GetNewIntValue(aValue);
    if(imode==0) {
      m_sensitiveDetector->setSensitiveMode(chargedParticleSensitiveMode);
    } else if(imode==1) {
      m_sensitiveDetector->setSensitiveMode(energyDepositSensitiveMode);
    } else if(imode==2) {
      m_sensitiveDetector->setSensitiveMode(opticalPhotonSensitiveMode);
    } else {
      m_sensitiveDetector->setSensitiveMode(anyParticleSensitiveMode);
    }
  } else if(command == m_cmdStoreHit) {
    m_sensitiveDetector->storeHit(m_cmdStoreHit->GetNewBoolValue(aValue));
  } else if(command == m_cmdStoreDigi) {
    m_sensitiveDetector->storeDigi(m_cmdStoreDigi->GetNewBoolValue(aValue));
  } else if(command == m_cmdSetThisCopyNoFactor) {
    m_sensitiveDetector->setThisCopyNoFactor(m_cmdSetThisCopyNoFactor->GetNewIntValue(aValue));
  } else if(command == m_cmdSetDeepCopyNoFactor) {
    m_sensitiveDetector->setDeepCopyNoFactor(m_cmdSetDeepCopyNoFactor->GetNewIntValue(aValue));
  } else if(command == m_cmdSetClusterID) {
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
    if(vec.size()==2) {
      int ch=int(vec[0]);
      int cl=int(vec[1]);
      m_sensitiveDetector->setClusterID(ch,cl);
    }
  } else if(command == m_cmdSetOnlineVetoThreshold) {
    G4String tmpline = aValue;
    double eth=GsimUtil::getUtil()->interpret(tmpline);
    m_sensitiveDetector->setOnlineVetoThreshold(eth/MeV);
  } else if(command == m_cmdSetTdcThreshold) {
    G4String tmpline = aValue;
    double eth=GsimUtil::getUtil()->interpret(tmpline);
    m_sensitiveDetector->setTdcThreshold(eth/MeV);
  } else {
    std::string msg = "Wrong command  at GsimSensitiveDetectorMessenger::";
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
