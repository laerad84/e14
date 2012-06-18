/**
 *  @file
 *  @brief  GsimPhysicsListFactoryMessenger
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimPhysicsListFactoryMessenger.h,v 1.3 2006/06/01 06:46:27 nanjo Exp $
 *  $Log: GsimPhysicsListFactoryMessenger.h,v $
 *  Revision 1.3  2006/06/01 06:46:27  nanjo
 *  GsimUserLimit is added.
 *
 *  Revision 1.2  2006/01/26 04:34:22  nanjo
 *  Factory pattern and template method on factory and messenger class is intorduced .
 *
 */

#ifndef GsimPhysicsListFactoryMessenger_h
#define GsimPhysicsListFactoryMessenger_h

// includes
#include "G4UImessenger.hh"
#include "globals.hh"

// forward declaration
template<class T> class GsimPhysicsListFactory;
class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithoutParameter;
class G4UIcmdWithABool;

/**
 *  @class GsimPhysicsListFactoryMessenger
 *  @brief PhysicsListFactory Messenger
 *
 *  This class provides messenger (user interface) for
 *  building PhysicsList and registering it to G4RunManager.
 *  It inherits from G4UImessenger.
 *  The name of PhysicsListFactory is added in the command name.
 *  This is enough for almost all users.
 *  If user want to add some command, 
 *  please make a class inherited from this class.
 */

template<class T>
class GsimPhysicsListFactoryMessenger : public G4UImessenger
{
public:

  /// Constructor;
  GsimPhysicsListFactoryMessenger(GsimPhysicsListFactory<T>* factory);

  /// Destructor;
  virtual ~GsimPhysicsListFactoryMessenger();

  /// Define user interface actions.
  void SetNewValue(G4UIcommand*, G4String);
  
protected:

  /// Hidden constructor;
  GsimPhysicsListFactoryMessenger();
  
  /// Store pointer of parent class.
  GsimPhysicsListFactory<T>* m_factory;

  /// User Interface directory.
  /**
   *  UI command is maintained in directory tree.
   */
  G4UIdirectory*        m_factoryDir;

  /// A user Interface command under the directory.
  G4UIcmdWithoutParameter*     m_cmd;
  G4UIcmdWithABool*            m_cmdWithUserLimits;
  G4UIcmdWithoutParameter*     m_cmdAddCerenkov;
};

//#include "GsimKernel/GsimPhysicsListFactoryMessenger.h"
#include "GsimKernel/GsimPhysicsListFactory.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithABool.hh"

#include <string>

template<class T>
GsimPhysicsListFactoryMessenger<T>::GsimPhysicsListFactoryMessenger(GsimPhysicsListFactory<T>* factory)
  :m_factory(factory)
{
#ifdef GSIMDEBUG
  {
    std::string msg = "enter GsimPhysicsListFactoryMessenger::GsimPhysicsListFactoryMessenger";
    msg += "(GsimPhysicsListFactory* factory)";
    GsimMessage::getInstance()
      ->report("debug",msg);
  }
#endif
  std::string factoryName=m_factory->getName();

  std::string dirName="/GsimPhysicsListFactory/";
  dirName+=factoryName;
  dirName+="/";
    
  m_factoryDir = new G4UIdirectory(G4String(dirName.c_str()));
  m_factoryDir->SetGuidance("Build GsimPhysicsList.");


  {
    std::string commandName=dirName;
    commandName+="buildAndRegister";
    m_cmd = new G4UIcmdWithoutParameter(G4String(commandName.c_str()),this);
    m_cmd->SetGuidance("Build and register this PhysicsList.");
    m_cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="withUserLimits";
    m_cmdWithUserLimits = new G4UIcmdWithABool(G4String(commandName.c_str()),this);
    m_cmdWithUserLimits->SetGuidance("With/without GsimUserLimits for the  PhysicsList.");
    m_cmdWithUserLimits->SetGuidance("withUserLimits 1/0");
    m_cmdWithUserLimits->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

  {
    std::string commandName=dirName;
    commandName+="addCerenkov";
    m_cmdAddCerenkov = new G4UIcmdWithoutParameter(G4String(commandName.c_str()),this);
    m_cmdAddCerenkov->SetGuidance("Add Cerenkov process.");
    m_cmdAddCerenkov->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

#ifdef GSIMDEBUG
 {
   std::string msg = "exit  GsimPhysicsListFactoryMessenger::GsimPhysicsListFactoryMessenger";
   msg += "(GsimPhysicsListFactory* factory)";
   GsimMessage::getInstance()
     ->report("debug",msg);
 }
#endif
}

template<class T>
GsimPhysicsListFactoryMessenger<T>::~GsimPhysicsListFactoryMessenger()
{
#ifdef GSIMDEBUG
  {
    std::string msg = "enter GsimPhysicsListFactoryMessenger::~GsimPhysicsListFactoryMessenger()";
    GsimMessage::getInstance()
      ->report("debug",msg);
  }
#endif
  
  delete m_cmd;
  delete m_cmdWithUserLimits;
  delete m_cmdAddCerenkov;
  delete m_factoryDir;

#ifdef GSIMDEBUG
 {
   std::string msg = "exit  GsimPhysicsListFactoryMessenger::~GsimPhysicsListFactoryMessenger()";
   GsimMessage::getInstance()
     ->report("debug",msg);
 }
#endif
}


template<class T>
void GsimPhysicsListFactoryMessenger<T>::SetNewValue(G4UIcommand* command,
						     G4String aValue)
{
#ifdef GSIMDEBUG
  {
    std::string msg = "enter GsimPhysicsListFactoryMessenger::SetNewValue";
    msg += "(G4UIcommand* command,G4String newValue)";
    GsimMessage::getInstance()
      ->report("debug",msg);
  }
#endif
  
  if( command == m_cmd )
    { m_factory->buildAndRegister(); }
  else if(command == m_cmdWithUserLimits)
    {
      GsimUtil* util = GsimUtil::getUtil();
      util->withUserLimits(m_cmdWithUserLimits->GetNewBoolValue(aValue));
    }
  else if(command == m_cmdAddCerenkov)
    {
      GsimUtil* util = GsimUtil::getUtil();
      util->addCerenkov();
    }
  else
    {
      GsimMessage::getInstance()->report("warning","Wrong command.");
    } 

#ifdef GSIMDEBUG
 {
   std::string msg = "exit  GsimPhysicsListFactoryMessenger::SetNewValue";
   msg += "(G4UIcommand* command,G4String newValue)";
   GsimMessage::getInstance()
     ->report("debug",msg);
 }
#endif
}

#endif //GsimPhysicsListFactoryMessenger_h



