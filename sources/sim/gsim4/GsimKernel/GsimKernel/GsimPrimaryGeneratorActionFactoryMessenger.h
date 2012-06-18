/**
 *  @file
 *  @brief  GsimPrimaryGeneratorActionFactoryMessenger
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimPrimaryGeneratorActionFactoryMessenger.h,v 1.2 2006/01/26 04:34:22 nanjo Exp $
 *  $Log: GsimPrimaryGeneratorActionFactoryMessenger.h,v $
 *  Revision 1.2  2006/01/26 04:34:22  nanjo
 *  Factory pattern and template method on factory and messenger class is intorduced .
 *
 */

#ifndef GsimPrimaryGeneratorActionFactoryMessenger_h
#define GsimPrimaryGeneratorActionFactoryMessenger_h

// includes
#include "G4UImessenger.hh"
#include "globals.hh"

// forward declaration
template<class T> class GsimPrimaryGeneratorActionFactory;
class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithoutParameter;
/**
 *  @class GsimPrimaryGeneratorActionFactoryMessenger
 *  @brief Messenger for GsimPrimaryGeneratorActionFactory.
 *
 *  This class is owned by GsimPrimaryGeneratorActionFactory and
 *  provide a feature to produce GsimPrimaryGeneratorAction.
 */

template<class T>
class GsimPrimaryGeneratorActionFactoryMessenger : public G4UImessenger
{
public:
  /// Constructor.
  /**
   *  @param factory This parent factory class.
   */
  GsimPrimaryGeneratorActionFactoryMessenger(GsimPrimaryGeneratorActionFactory<T>* factory);

  /// Destructor.
  virtual ~GsimPrimaryGeneratorActionFactoryMessenger();

  /// Define action for UI
  void SetNewValue(G4UIcommand*, G4String);
  
protected:

  /// parent factory class.
  GsimPrimaryGeneratorActionFactory<T>* m_factory;

  /// User Interface directory. 
  G4UIdirectory*                     m_factoryDir;

  /// A user Interface command under the directory.
  G4UIcmdWithoutParameter*           m_cmd;

};



//#include "GsimKernel/GsimPrimaryGeneratorActionFactoryMessenger.h"
#include "GsimKernel/GsimPrimaryGeneratorActionFactory.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"

template<class T>
GsimPrimaryGeneratorActionFactoryMessenger<T>::
GsimPrimaryGeneratorActionFactoryMessenger(GsimPrimaryGeneratorActionFactory<T>* factory)
  :m_factory(factory)
{
#ifdef GSIMDEBUG
  {
    std::string msg = "enter GsimPrimaryGeneratorActionFactoryMessenger::";
    msg+="GsimPrimaryGeneratorActionFactoryMessenger(GsimPrimaryGeneratorActionFactory* factory)";
    GsimMessage::getInstance()
      ->report("debug",msg);
  }
#endif

  std::string factoryName=m_factory->getName();

  std::string dirName="/GsimPrimaryGeneratorActionFactory/";
  dirName+=factoryName;
  dirName+="/";
  
  std::string commandName=dirName;
  commandName+="buildAndRegister";
  
  m_factoryDir = new G4UIdirectory(G4String(dirName.c_str()));
  m_factoryDir->SetGuidance("Build GsimPrimaryGeneratorAction.");

  m_cmd = new G4UIcmdWithoutParameter(G4String(commandName.c_str()),this);
  m_cmd->SetGuidance("Build and register this PrimaryGeneratorAction.");
  m_cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
#ifdef GSIMDEBUG
  {
    std::string msg = "exit  GsimPrimaryGeneratorActionFactoryMessenger::";
    msg+="GsimPrimaryGeneratorActionFactoryMessenger(GsimPrimaryGeneratorActionFactory* factory)";
    GsimMessage::getInstance()
      ->report("debug",msg);
  }
#endif
}

template<class T>
GsimPrimaryGeneratorActionFactoryMessenger<T>::~GsimPrimaryGeneratorActionFactoryMessenger()
{
#ifdef GSIMDEBUG
  {
    std::string msg = "enter GsimPrimaryGeneratorActionFactoryMessenger::";
    msg+="~GsimPrimaryGeneratorActionFactoryMessenger()";
    GsimMessage::getInstance()
      ->report("debug",msg);
  }
#endif
  
  delete m_cmd;
  delete m_factoryDir;

#ifdef GSIMDEBUG
  {
    std::string msg = "exit  GsimPrimaryGeneratorActionFactoryMessenger::";
    msg+="~GsimPrimaryGeneratorActionFactoryMessenger()";
    GsimMessage::getInstance()
      ->report("debug",msg);
  }
#endif
}


template<class T>
void GsimPrimaryGeneratorActionFactoryMessenger<T>::SetNewValue(G4UIcommand* command,G4String)
{
#ifdef GSIMDEBUG
  {
    std::string msg = "enter GsimPrimaryGeneratorActionFactoryMessenger::";
    msg+="SetNewValue(G4UIcommand* command,G4String newValue)";
    GsimMessage::getInstance()
      ->report("debug",msg);
  }
#endif
  
  if( command == m_cmd )
    { m_factory->buildAndRegister(); }

#ifdef GSIMDEBUG
  {
    std::string msg = "exit  GsimPrimaryGeneratorActionFactoryMessenger::";
    msg+="SetNewValue(G4UIcommand* command,G4String newValue)";
    GsimMessage::getInstance()
      ->report("debug",msg);
  }
#endif
}


#endif //GsimPrimaryGeneratorActionFactoryMessenger_h



