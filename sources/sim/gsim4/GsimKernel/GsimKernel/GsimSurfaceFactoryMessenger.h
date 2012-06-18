/**
 *  @file
 *  @brief  GsimSurfaceFactoryMessenger
 *  $Id: $
 *  $Log:$
 */

#ifndef GsimSurfaceFactoryMessenger_h
#define GsimSurfaceFactoryMessenger_h

// includes

#include "G4UImessenger.hh"
#include "globals.hh"

// forward declaration

class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithAString;
class GsimSurfaceFactory;
/**
 *  @class GsimSurfaceFactoryMessenger
 *  @brief Messenger for GsimSurfaceFactory.
 *
 *  This class is owned by GsimSurfaceFactory and
 *  provide a feature to produce GsimSurface.
 */

class GsimSurfaceFactoryMessenger : public G4UImessenger
{
public:
  /// Constructor.
  /**
   *  @param factory This parent factory class.
   */
  GsimSurfaceFactoryMessenger(GsimSurfaceFactory* factory);

  /// Destructor.
  virtual ~GsimSurfaceFactoryMessenger();

  /// Define action for UI
  void SetNewValue(G4UIcommand*, G4String aValue);
  
protected:

  /// parent factory class.
  GsimSurfaceFactory* m_factory;

  /// User Interface directory. 
  G4UIdirectory*          m_factoryDir;

  /// A user Interface command under the directory.
  G4UIcmdWithAString*     m_cmd;

};


//#include "GsimKernel/GsimSurfaceFactoryMessenger.h"
#include "GsimKernel/GsimSurfaceFactory.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"


GsimSurfaceFactoryMessenger::
GsimSurfaceFactoryMessenger(GsimSurfaceFactory* factory)
  :m_factory(factory)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  std::string dirName="/GsimSurfaceFactory/";

  std::string commandName=dirName;
  commandName+="build";
  
  m_factoryDir = new G4UIdirectory(G4String(dirName.c_str()));
  m_factoryDir->SetGuidance("Build GsimSurface.");

  m_cmd = new G4UIcmdWithAString(G4String(commandName.c_str()),this);
  m_cmd->SetGuidance("Build  GsimSurface.");
  m_cmd->SetGuidance("/GsimSurfaceFactory/build name det1FullName det2FullName");
  m_cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimSurfaceFactoryMessenger::~GsimSurfaceFactoryMessenger()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  
  delete m_cmd;
  delete m_factoryDir;

#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimSurfaceFactoryMessenger::SetNewValue(G4UIcommand* command,G4String aValue)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  
  if( command == m_cmd )
    {
      GsimUtil* util = GsimUtil::getUtil();
      G4String line = aValue;
      G4String tmpline = aValue;
      G4String tmpout,out1,out2,out3;
      int nArg=0;
      bool ok=true;
      while(ok) {
	ok=util->shift(tmpline,tmpout);
	if(ok) nArg++;
      }
      if(nArg==3) {
	util->shift(line,out1);
	util->shift(line,out2);
	util->shift(line,out3);
      } else {
	{
	  std::string msg = "Wrong command format at GsimSurfaceFactoryMessenger::";
	  msg+="SetNewValue(G4UIcommand* command,G4String newValue=";
	  msg+=std::string(aValue.data()) ;
	  msg+=")";
	  GsimMessage::getInstance()
	    ->report("warning",msg);
	}
	return;
      }

      std::string name = std::string(out1.data());
      std::string vol1name = std::string(out2.data());
      std::string vol2name = std::string(out3.data());
      m_factory->build(name,vol1name,vol2name);
    }

#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}





#endif //GsimSurfaceFactoryMessenger_h



