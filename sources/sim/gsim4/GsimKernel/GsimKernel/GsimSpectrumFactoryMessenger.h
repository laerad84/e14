/**
 *  @file
 *  @brief  GsimSpectrumFactoryMessenger
 *  $Id: GsimSpectrumFactoryMessenger.h,v 1.2 2006/12/06 18:44:00 nanjo Exp $
 *  $Log: GsimSpectrumFactoryMessenger.h,v $
 *  Revision 1.2  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 */

#ifndef GsimSpectrumFactoryMessenger_h
#define GsimSpectrumFactoryMessenger_h

// includes

#include "G4UImessenger.hh"
#include "globals.hh"

// forward declaration

class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithoutParameter;
template<class T> class GsimSpectrumFactory;
/**
 *  @class GsimSpectrumFactoryMessenger
 *  @brief Messenger for GsimSpectrumFactory.
 *
 *  This class is owned by GsimSpectrumFactory and
 *  provide a feature to produce GsimSpectrum.
 */

template<class T>
class GsimSpectrumFactoryMessenger : public G4UImessenger
{
public:
  /// Constructor.
  /**
   *  @param factory This parent factory class.
   */
  GsimSpectrumFactoryMessenger(GsimSpectrumFactory<T>* factory);

  /// Destructor.
  virtual ~GsimSpectrumFactoryMessenger();

  /// Define action for UI
  void SetNewValue(G4UIcommand*, G4String aValue);
  
protected:

  /// parent factory class.
  GsimSpectrumFactory<T>* m_factory;

  /// User Interface directory. 
  G4UIdirectory*          m_factoryDir;

  /// A user Interface command under the directory.
  G4UIcmdWithoutParameter*     m_cmd;

};


//#include "GsimKernel/GsimSpectrumFactoryMessenger.h"
#include "GsimKernel/GsimSpectrumFactory.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"


template<class T>
GsimSpectrumFactoryMessenger<T>::
GsimSpectrumFactoryMessenger(GsimSpectrumFactory<T>* factory)
  :m_factory(factory)
{


  std::string name  = factory->getName();
  std::string dirName="/GsimSpectrumFactory/";
  dirName+=name;
  dirName+="/";

  std::string commandName=dirName;
  commandName+="buildAndRegister";
  
  m_factoryDir = new G4UIdirectory(G4String(dirName.c_str()));
  m_factoryDir->SetGuidance("Build GsimSpectrum.");

  m_cmd = new G4UIcmdWithoutParameter(G4String(commandName.c_str()),this);
  m_cmd->SetGuidance("Build and register this Spectrum.");
  m_cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

template<class T>
GsimSpectrumFactoryMessenger<T>::~GsimSpectrumFactoryMessenger()
{
  delete m_cmd;
  delete m_factoryDir;
}


template<class T>
void GsimSpectrumFactoryMessenger<T>::SetNewValue(G4UIcommand* command,G4String)
{
  
  if( command == m_cmd )
    {
      m_factory->buildAndRegister();
    }
  
}

#endif //GsimSpectrumFactoryMessenger_h



