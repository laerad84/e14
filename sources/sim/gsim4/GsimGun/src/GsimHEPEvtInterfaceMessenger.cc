/**
 *  @file
 *  @brief  GsimHEPEvtInterfaceMessenger
 *  $Id: 
 *  $Log: 
 */
#include "GsimGun/GsimHEPEvtInterfaceMessenger.h"
#include "GsimGun/GsimHEPEvtInterface.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include <vector>

GsimHEPEvtInterfaceMessenger::
GsimHEPEvtInterfaceMessenger(GsimHEPEvtInterface* interface)
  :m_hepEvtInterface(interface)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  std::string dirName="/GsimPrimaryGeneratorAction/HepEVT/";
  m_dir = new G4UIdirectory(G4String(dirName.c_str()));
  m_dir->SetGuidance("GsimHEPEvtInterface Command .");

  {
    std::string commandName=dirName;
    commandName+="setInputFileName";
    m_cmdSetInputFileName = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdSetInputFileName->SetGuidance("setInputFileName (HEPevt text data file)");
    m_cmdSetInputFileName->SetGuidance("setInputFileName (HEPevt root data file)");
    m_cmdSetInputFileName->SetGuidance("Set input fileName.");
    m_cmdSetInputFileName->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setInputEventDataFileName";
    m_cmdSetInputEventDataFileName = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdSetInputEventDataFileName->SetGuidance("setInputEventDataFileName fileName detctorName.");
    m_cmdSetInputEventDataFileName->SetGuidance("setInputEventDataFileName fileName detctorName runNo.");
    m_cmdSetInputEventDataFileName->SetGuidance("setInputEventDataFileName fileName detctorName runNo KLtype.");
    m_cmdSetInputEventDataFileName->SetGuidance("Set input gsim4 EventData fileName.");
    m_cmdSetInputEventDataFileName->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setVertexPosition";
    m_cmdSetVertexPosition = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdSetVertexPosition->SetGuidance("setVertexPosition x y z");
    m_cmdSetVertexPosition->SetGuidance("Set common vertex position.");
    m_cmdSetVertexPosition->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setVertexTime";
    m_cmdSetVertexTime = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdSetVertexTime->SetGuidance("setVertexTime t");
    m_cmdSetVertexTime->SetGuidance("Set common vertex time.");
    m_cmdSetVertexTime->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="convertToRootFile";
    m_cmdConvertToRootFile = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdConvertToRootFile->SetGuidance("convertToRootFile RootFile");
    m_cmdConvertToRootFile->SetGuidance("convert input ascii HEPEvt file to ROOT file.");
    m_cmdConvertToRootFile->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="gotoEventNumber";
    m_cmdGotoEventNumber = new G4UIcmdWithAnInteger(G4String(commandName.c_str()),this);
    m_cmdGotoEventNumber->SetGuidance("gotoEventNumber number");
    m_cmdGotoEventNumber->SetGuidance("Goto the event number.");
    m_cmdGotoEventNumber->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="setZeroPIDParticle;";
    m_cmdSetZeroPIDParticle = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
    m_cmdSetZeroPIDParticle->SetGuidance("setZroPIDParticle geantino/chargedgeantino/opticalphoton");
    m_cmdSetZeroPIDParticle->SetGuidance("Set zero PID particle for HEPEvt.");
    m_cmdSetZeroPIDParticle->AvailableForStates(G4State_PreInit,G4State_Idle);
  }


  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


GsimHEPEvtInterfaceMessenger::~GsimHEPEvtInterfaceMessenger()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  delete m_cmdSetInputFileName;
  delete m_cmdSetInputEventDataFileName;
  delete m_cmdSetVertexPosition;
  delete m_cmdSetVertexTime;
  delete m_cmdConvertToRootFile;
  delete m_cmdGotoEventNumber;
  delete m_cmdSetZeroPIDParticle;
  delete m_dir;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}



void GsimHEPEvtInterfaceMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if( command == m_cmdSetInputFileName )
    { m_hepEvtInterface
	->setInputFileName(std::string(newValue.data()));
    }
  else if( command == m_cmdSetInputEventDataFileName )
    {

      GsimUtil* util = GsimUtil::getUtil();
      G4String tmpline = newValue;
      G4String tmpout;
    
      std::vector<std::string> vec;
      bool ok=true;
      while(ok) {
	ok=util->shift(tmpline,tmpout);
	if(ok) {
	  vec.push_back(std::string(tmpout.data()));
	}
      }
      if(vec.size()==2) {
	m_hepEvtInterface
	  ->setInputEventDataFileName(vec[0],vec[1]);
      } else if(vec.size()==3) {
	int runNo=std::atoi(vec[2].c_str());
	m_hepEvtInterface
	  ->setInputEventDataFileName(vec[0],vec[1],runNo);
      } else if(vec.size()==4) {
	int runNo=std::atoi(vec[2].c_str());
	m_hepEvtInterface
	  ->setInputEventDataFileName(vec[0],vec[1],runNo,vec[3]);
      } else {
	std::string msg = "Wrong number of paramaeters.";
	GsimMessage::getInstance()->report("warning",msg);
      }
    }
  else if( command == m_cmdSetVertexPosition )
    {
      GsimUtil* util = GsimUtil::getUtil();
      G4String tmpline = newValue;
      G4String tmpout;
      std::vector<double> vec;
      bool ok=true;
      while(ok) {
	ok=util->shift(tmpline,tmpout);
	if(ok) {
	  vec.push_back(util->interpret(tmpout));
	}
      }
      if(vec.size()!=3) {
	std::string msg = "Wrong number of paramaeters ";
	msg+="at GsimHEPEvtInterfaceMessenger::";
	msg+="SetNewValue(G4UIcommand* command,G4String newValue=";
	msg+=std::string(newValue.data()) ;
	msg+=")";
	GsimMessage::getInstance()
	  ->report("warning",msg);
	return;
      }
      G4ThreeVector tvec(vec[0],vec[1],vec[2]);
      m_hepEvtInterface
	->setVertexPosition(tvec);
    }
  else if( command == m_cmdSetVertexTime )
    {
      GsimUtil* util = GsimUtil::getUtil();
      G4String tmpline = newValue;
      G4String tmpout;
      std::vector<double> vec;
      bool ok=true;
      while(ok) {
	ok=util->shift(tmpline,tmpout);
	if(ok) {
	  vec.push_back(util->interpret(tmpout));
	}
      }
      if(vec.size()!=1) {
	std::string msg = "Wrong number of paramaeters ";
	msg+="at GsimHEPEvtInterfaceMessenger::";
	msg+="SetNewValue(G4UIcommand* command,G4String newValue=";
	msg+=std::string(newValue.data()) ;
	msg+=")";
	GsimMessage::getInstance()
	  ->report("warning",msg);
	return;
      }
      m_hepEvtInterface->setVertexTime(vec[0]);
    }
  else if( command == m_cmdGotoEventNumber)
    {
      m_hepEvtInterface
	->gotoEventNumber(m_cmdGotoEventNumber->GetNewIntValue(newValue));
    }
  else if( command == m_cmdConvertToRootFile)
    {
      m_hepEvtInterface->convertToRootFile(std::string(newValue.data()));
    }
  else if( command == m_cmdSetZeroPIDParticle)
    {
      m_hepEvtInterface->setZeroPIDParticle(std::string(newValue.data()));
    }
  else {
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}
