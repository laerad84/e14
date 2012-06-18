/**
 *  $Id: GsimSpectrumMessenger.cc,v 1.2 2006/12/06 18:44:00 nanjo Exp $
 *  $Log: GsimSpectrumMessenger.cc,v $
 *  Revision 1.2  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 */
#include "GsimKernel/GsimSpectrumMessenger.h"
#include "GsimKernel/GsimSpectrum.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UImanager.hh"

#include <cstdlib>
#include <vector>
#include <string>

GsimSpectrumMessenger::GsimSpectrumMessenger(GsimSpectrum* spectrum)
  :m_spectrum(spectrum)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif


  std::string dirName="/GsimSpectrum/";
  dirName+=spectrum->getName();
  dirName+="/";
  m_spectrumDir = new G4UIdirectory(G4String(dirName.c_str()));
  m_spectrumDir->SetGuidance("Control GsimSpectrum.");
  
  {
    std::string commandName=dirName;
    commandName+="addSpectrum";
    m_cmdAddSpectrum = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdAddSpectrum->SetGuidance("addSpectrum formula xmin xmax");
    m_cmdAddSpectrum->SetGuidance("addSpectrum TMath::Gaus(PAbs,3,1) 0 10");
    m_cmdAddSpectrum->SetGuidance("Following variables can be used.");
    m_cmdAddSpectrum->SetGuidance("VX : vertex x.");
    m_cmdAddSpectrum->SetGuidance("VY : vettex y.");
    m_cmdAddSpectrum->SetGuidance("VZ : vertex z.");
    m_cmdAddSpectrum->SetGuidance("VR : vertex r.");
    m_cmdAddSpectrum->SetGuidance("VTheta : vertex theta.");
    m_cmdAddSpectrum->SetGuidance("VCosTheta : vertex cosTheta.");
    m_cmdAddSpectrum->SetGuidance("VPhi : vertex phi.");
    m_cmdAddSpectrum->SetGuidance("PAbs : absolute momentum.");
    m_cmdAddSpectrum->SetGuidance("Energy : kinetic energy.");
    m_cmdAddSpectrum->SetGuidance("PTheta : momentum theta.");
    m_cmdAddSpectrum->SetGuidance("PCosTheta : momentum cosTheta.");
    m_cmdAddSpectrum->SetGuidance("PPhi : momentum phi");
    m_cmdAddSpectrum->SetGuidance("unit is mm or MeV.");
    m_cmdAddSpectrum->SetGuidance("addSpectrum Special");
    m_cmdAddSpectrum->SetGuidance("Special spectrum prepared..");
    m_cmdAddSpectrum->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setParameter";
    m_cmdSetParameter = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdSetParameter->SetGuidance("setParameter val");
    m_cmdSetParameter->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="clear";
    m_cmdClear = new G4UIcmdWithoutParameter(G4String(commandName.c_str()),this);
    m_cmdClear->SetGuidance("clear");
    m_cmdClear->AvailableForStates(G4State_PreInit,G4State_Idle);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


GsimSpectrumMessenger::~GsimSpectrumMessenger()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  delete m_cmdAddSpectrum;
  delete m_cmdClear;
  delete m_cmdSetParameter;
  delete m_spectrumDir;

#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimSpectrumMessenger::SetNewValue(G4UIcommand* command,G4String aValue)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  aValue=G4UImanager::GetUIpointer()->SolveAlias(aValue.data());
  
  if(command == m_cmdAddSpectrum) {
    GsimUtil* util = GsimUtil::getUtil();
    G4String tmpline = aValue;
    G4String tmpout;
    std::string tmpformula;
    double      tmpxmin=-1;
    double      tmpxmax=-1;
    bool ok=true;
    int okCount=0;
    while(ok) {
      ok=util->shift(tmpline,tmpout);
      if(ok) {
	if(okCount==0) {
	  tmpformula=std::string(tmpout.data());
	} else if(okCount==1) {
	  tmpxmin=std::atof(tmpout.data());
	} else {
	  tmpxmax=std::atof(tmpout.data());
	}
	okCount++;
      }
    }

    if(okCount==3) {
      m_spectrum->addSpectrum(tmpformula,tmpxmin,tmpxmax);
    } else if(okCount==1 && tmpformula=="Special") {
      m_spectrum->addSpectrum(tmpformula,0,0);
    } else {
      //Error
      return;
    }
  } else if(command == m_cmdSetParameter) {
    GsimUtil* util = GsimUtil::getUtil();
    m_spectrum->setParameter(util->interpret(aValue));
  } else if(command == m_cmdClear) {
    m_spectrum->clear();
  } else {
    std::string msg = "Wrong command  at GsimSpectrumMessenger::";
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
