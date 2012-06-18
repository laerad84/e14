/**
 *  @file
 *  @brief  GsimDetectorFactoryMessenger
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimDetectorFactoryMessenger.h,v 1.1 2006/01/26 04:53:30 nanjo Exp $
 *  $Log: GsimDetectorFactoryMessenger.h,v $
 *  Revision 1.1  2006/01/26 04:53:30  nanjo
 *  Detector and persistency classes are added.
 *
 */

#ifndef GsimDetectorFactoryMessenger_h
#define GsimDetectorFactoryMessenger_h

// includes

#include "G4UImessenger.hh"
#include "globals.hh"

// forward declaration

class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithAString;
template<class T> class GsimDetectorFactory;
/**
 *  @class GsimDetectorFactoryMessenger
 *  @brief Messenger for GsimDetectorFactory.
 *
 *  This class is owned by GsimDetectorFactory and
 *  provide a feature to produce GsimDetector.
 */

template<class T>
class GsimDetectorFactoryMessenger : public G4UImessenger
{
public:
  /// Constructor.
  /**
   *  @param factory This parent factory class.
   */
  GsimDetectorFactoryMessenger(GsimDetectorFactory<T>* factory);

  /// Destructor.
  virtual ~GsimDetectorFactoryMessenger();

  /// Define action for UI
  void SetNewValue(G4UIcommand*, G4String aValue);
  
protected:

  /// parent factory class.
  GsimDetectorFactory<T>* m_factory;

  /// User Interface directory. 
  G4UIdirectory*          m_factoryDir;

  /// A user Interface command under the directory.
  G4UIcmdWithAString*     m_cmd;

};


//#include "GsimKernel/GsimDetectorFactoryMessenger.h"
#include "GsimKernel/GsimDetectorFactory.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"


template<class T>
GsimDetectorFactoryMessenger<T>::
GsimDetectorFactoryMessenger(GsimDetectorFactory<T>* factory)
  :m_factory(factory)
{
#ifdef GSIMDEBUG
  {
    std::string msg = "enter GsimDetectorFactoryMessenger::";
    msg+="GsimDetectorFactoryMessenger(GsimDetectorFactory* factory)";
    GsimMessage::getInstance()
      ->report("debug",msg);
  }
#endif

  std::string factoryName  = factory->getFactoryName();
  std::string dirName="/GsimDetectorFactory/";
  dirName+=factoryName;
  dirName+="/";

  std::string commandName=dirName;
  commandName+="buildAndRegister";
  
  m_factoryDir = new G4UIdirectory(G4String(dirName.c_str()));
  m_factoryDir->SetGuidance("Build GsimDetector.");

  m_cmd = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
  m_cmd->SetGuidance("Build and register this Detector.");
  m_cmd->SetGuidance("Usage");
  m_cmd->SetGuidance("/GsimDetectorFactory/xxx/buildAndRegister");
  m_cmd->SetGuidance("name mother posX posY posZ rotX, rotY rotZ [userFlag]");
  m_cmd->SetGuidance("name mother posX posY posZ [userFlag]");
  m_cmd->SetGuidance("name mother [userFlag]");
  m_cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
#ifdef GSIMDEBUG
  {
    std::string msg = "exit  GsimDetectorFactoryMessenger::";
    msg+="GsimDetectorFactoryMessenger(GsimDetectorFactory* factory)";
    GsimMessage::getInstance()
      ->report("debug",msg);
  }
#endif
}

template<class T>
GsimDetectorFactoryMessenger<T>::~GsimDetectorFactoryMessenger()
{
#ifdef GSIMDEBUG
  {
    std::string msg = "enter GsimDetectorFactoryMessenger::";
    msg+="~GsimDetectorFactoryMessenger()";
    GsimMessage::getInstance()
      ->report("debug",msg);
  }
#endif
  
  delete m_cmd;
  delete m_factoryDir;

#ifdef GSIMDEBUG
  {
    std::string msg = "exit  GsimDetectorFactoryMessenger::";
    msg+="~GsimDetectorFactoryMessenger()";
    GsimMessage::getInstance()
      ->report("debug",msg);
  }
#endif
}


template<class T>
void GsimDetectorFactoryMessenger<T>::SetNewValue(G4UIcommand* command,G4String aValue)
{
#ifdef GSIMDEBUG
  {
    std::string msg = "enter GsimDetectorFactoryMessenger::";
    msg+="SetNewValue(G4UIcommand* command,G4String newValue=";
    msg+=std::string(aValue.data()) ;
    msg+=")";
    GsimMessage::getInstance()
      ->report("debug",msg);
  }
#endif
  
  if( command == m_cmd )
    {
      GsimUtil* util = GsimUtil::getUtil();
      G4String line = aValue;
      G4String tmpline = aValue;
      G4String tmpout,out1,out2;
      G4String outt[3];
      G4String outr[3];
      G4String out9;
      int nArg=0;
      bool ok=true;
      while(ok) {
	ok=util->shift(tmpline,tmpout);
	if(ok) nArg++;
      }
      if(nArg==9) {
	util->shift(line,out1);
	util->shift(line,out2);
	for(int k=0;k<3;k++) {
	  util->shift(line,outt[k]);
	}
	for(int k=0;k<3;k++) {
	  util->shift(line,outr[k]);
	}
	util->shift(line,out9);
      } else if(nArg==8) {
	util->shift(line,out1);
	util->shift(line,out2);
	for(int k=0;k<3;k++) {
	  util->shift(line,outt[k]);
	}
	for(int k=0;k<3;k++) {
	  util->shift(line,outr[k]);
	}
	out9="0";
      } else if(nArg==6) {
	util->shift(line,out1);
	util->shift(line,out2);
	for(int k=0;k<3;k++) {
	  util->shift(line,outt[k]);
	}
	for(int k=0;k<3;k++) {
	  outr[k]="0";
	}
	util->shift(line,out9);
      } else if(nArg==5) {
	util->shift(line,out1);
	util->shift(line,out2);
	for(int k=0;k<3;k++) {
	  util->shift(line,outt[k]);
	}
	for(int k=0;k<3;k++) {
	  outr[k]="0";
	}
	out9="0";
      } else if(nArg==3) {
	util->shift(line,out1);
	util->shift(line,out2);
	for(int k=0;k<3;k++) {
	  outt[k]="0";
	}
	for(int k=0;k<3;k++) {
	  outr[k]="0";
	}
	util->shift(line,out9);
      } else if(nArg==2) {
	util->shift(line,out1);
	util->shift(line,out2);
	for(int k=0;k<3;k++) {
	  outt[k]="0";
	}
	for(int k=0;k<3;k++) {
	  outr[k]="0";
	}
	out9="0";
      } else {
	{
	  std::string msg = "Wrong command format at GsimDetectorFactoryMessenger::";
	  msg+="SetNewValue(G4UIcommand* command,G4String newValue=";
	  msg+=std::string(aValue.data()) ;
	  msg+=")";
	  GsimMessage::getInstance()
	    ->report("warning",msg);
	}
	return;
      }

      std::string name = std::string(out1.data());
      std::string mothername = std::string(out2.data());
      double tra[3];
      double rot[3];
      for(int k=0;k<3;k++) {
	tra[k] = util->interpret(outt[k]);
	rot[k] = util->interpret(outr[k]);
      }
      G4ThreeVector traV(tra[0],tra[1],tra[2]);
      G4ThreeVector rotV(rot[0],rot[1],rot[2]);
      int userFlag=std::atoi(out9.data());
      m_factory->buildAndRegister(name,mothername,traV,rotV,userFlag);
    }

#ifdef GSIMDEBUG
  {
    std::string msg = "enter GsimDetectorFactoryMessenger::";
    msg+="SetNewValue(G4UIcommand* command,G4String newValue=";
    msg+=std::string(aValue.data()) ;
    msg+=")";
    GsimMessage::getInstance()
      ->report("debug",msg);
  }
#endif
}





#endif //GsimDetectorFactoryMessenger_h



