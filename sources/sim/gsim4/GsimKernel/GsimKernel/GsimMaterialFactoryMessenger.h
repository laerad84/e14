/**
 *  @file
 *  @brief  GsimMaterialFactoryMessenger
 *  $Id: $
 *  $Log:$
 */

#ifndef GsimMaterialFactoryMessenger_h
#define GsimMaterialFactoryMessenger_h

// includes

#include "G4UImessenger.hh"
#include "globals.hh"

// forward declaration

class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithoutParameter;
template<class T> class GsimMaterialFactory;
/**
 *  @class GsimMaterialFactoryMessenger
 *  @brief Messenger for GsimMaterialFactory.
 *
 *  This class is owned by GsimMaterialFactory and
 *  provide a feature to produce GsimMaterial.
 */

template<class T>
class GsimMaterialFactoryMessenger : public G4UImessenger
{
public:
  /// Constructor.
  /**
   *  @param factory This parent factory class.
   */
  GsimMaterialFactoryMessenger(GsimMaterialFactory<T>* factory);

  /// Destructor.
  virtual ~GsimMaterialFactoryMessenger();

  /// Define action for UI
  void SetNewValue(G4UIcommand*, G4String);
  
protected:

  /// parent factory class.
  GsimMaterialFactory<T>* m_factory;

  /// User Interface directory. 
  G4UIdirectory*          m_factoryDir;

  /// A user Interface command under the directory.
  G4UIcmdWithoutParameter*     m_cmd;

};


//#include "GsimKernel/GsimMaterialFactoryMessenger.h"
#include "GsimKernel/GsimMaterialFactory.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"


template<class T>
GsimMaterialFactoryMessenger<T>::
GsimMaterialFactoryMessenger(GsimMaterialFactory<T>* factory)
  :m_factory(factory)
{
#ifdef GSIMDEBUG
  {
    std::string msg = "enter GsimMaterialFactoryMessenger::";
    msg+="GsimMaterialFactoryMessenger(GsimMaterialFactory* factory)";
    GsimMessage::getInstance()
      ->report("debug",msg);
  }
#endif

  std::string factoryName  = factory->getFactoryName();
  std::string dirName="/GsimMaterialFactory/";
  dirName+=factoryName;
  dirName+="/";

  std::string commandName=dirName;
  commandName+="build";
  
  m_factoryDir = new G4UIdirectory(G4String(dirName.c_str()));
  m_factoryDir->SetGuidance("Build Mateiral.");

  m_cmd = new G4UIcmdWithoutParameter(G4String(commandName.c_str()),this);
  m_cmd->SetGuidance("Build mateiral.");
  m_cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
#ifdef GSIMDEBUG
  {
    std::string msg = "exit  GsimMaterialFactoryMessenger::";
    msg+="GsimMaterialFactoryMessenger(GsimMaterialFactory* factory)";
    GsimMessage::getInstance()
      ->report("debug",msg);
  }
#endif
}

template<class T>
GsimMaterialFactoryMessenger<T>::~GsimMaterialFactoryMessenger()
{
#ifdef GSIMDEBUG
  {
    std::string msg = "enter GsimMaterialFactoryMessenger::";
    msg+="~GsimMaterialFactoryMessenger()";
    GsimMessage::getInstance()
      ->report("debug",msg);
  }
#endif
  
  delete m_cmd;
  delete m_factoryDir;

#ifdef GSIMDEBUG
  {
    std::string msg = "exit  GsimMaterialFactoryMessenger::";
    msg+="~GsimMaterialFactoryMessenger()";
    GsimMessage::getInstance()
      ->report("debug",msg);
  }
#endif
}


template<class T>
void GsimMaterialFactoryMessenger<T>::SetNewValue(G4UIcommand* command,G4String)
{
#ifdef GSIMDEBUG
  {
    std::string msg = "enter GsimMaterialFactoryMessenger::";
    msg+="SetNewValue(G4UIcommand* command,G4String newValue=";
    msg+=std::string(aValue.data()) ;
    msg+=")";
    GsimMessage::getInstance()
      ->report("debug",msg);
  }
#endif
  
  if( command == m_cmd )
    {
      m_factory->build();
    }

#ifdef GSIMDEBUG
  {
    std::string msg = "enter GsimMaterialFactoryMessenger::";
    msg+="SetNewValue(G4UIcommand* command,G4String newValue=";
    msg+=std::string(aValue.data()) ;
    msg+=")";
    GsimMessage::getInstance()
      ->report("debug",msg);
  }
#endif
}





#endif //GsimMaterialFactoryMessenger_h



