/**
 *  @file
 *  @brief  GsimPrimaryGeneratorActionFactory
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimPrimaryGeneratorActionFactory.h,v 1.2 2006/01/26 04:34:22 nanjo Exp $
 *  $Log: GsimPrimaryGeneratorActionFactory.h,v $
 *  Revision 1.2  2006/01/26 04:34:22  nanjo
 *  Factory pattern and template method on factory and messenger class is intorduced .
 *
 */

#ifndef GsimPrimaryGeneratorActionFactory_h
#define GsimPrimaryGeneratorActionFactory_h

// includes
#include "globals.hh"
#include <string>

// forward declaration
class GsimPrimaryGeneratorAction;
template<class T> class GsimPrimaryGeneratorActionFactoryMessenger;


/**
 *  @class GsimPrimaryGeneratorActionFactory
 *  @brief abstract factory for GsimPrimaryGeneratorAction 
 *
 *  This class provides a feature to produce its corresponding
 *  PrimaryGeneratorAction. User is required to prepare a pair of
 *  PrimaryGeneratorAction and corresponding PrimaryGeneratorActionFactory.
 *  Default PrimaryGeneratorActionFactoryMessenger is enough
 *  for almost all cases.
 */

template<class T>
class GsimPrimaryGeneratorActionFactory
{
public:
  /// Constructor.
  GsimPrimaryGeneratorActionFactory(std::string name);

  /// Destructor.
  virtual ~GsimPrimaryGeneratorActionFactory();

  /// Interface to build PrimaryGeneratorAction and register it to G4RunManager.
  void  buildAndRegister();

  inline std::string getName();
  
protected:

  /// Build PrimaryGeneratorAction which user will edit.
  virtual GsimPrimaryGeneratorAction* build();

  /// Its messenger.
  GsimPrimaryGeneratorActionFactoryMessenger<T>*
    m_primaryGeneratorActionFactoryMessenger;

  /// Factory name
  std::string m_name;

  /// Static pointer to store current PrimaryGeneratorAction
  /**
   *  Static member is common for all classes
   *  derived from this class.
   */
  static GsimPrimaryGeneratorAction* s_currentPrimaryGeneratorAction;

};

template <class T>
inline std::string GsimPrimaryGeneratorActionFactory<T>::getName() {
  return m_name;
}


//#include "GsimKernel/GsimPrimaryGeneratorActionFactory.h"
#include "GsimKernel/GsimPrimaryGeneratorActionFactoryMessenger.h"
#include "GsimKernel/GsimPrimaryGeneratorAction.h"
#include "GsimPersistency/GsimMessage.h"
#include "G4RunManager.hh"

template <class T> GsimPrimaryGeneratorAction*
GsimPrimaryGeneratorActionFactory<T>::s_currentPrimaryGeneratorAction=0;


template <class T>
GsimPrimaryGeneratorActionFactory<T>::
GsimPrimaryGeneratorActionFactory(std::string name)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()
    ->report("debug","enter GsimPrimaryGeneratorActionFactory::GsimPrimaryGeneratorActionFactory()");
#endif

  m_name = name;
  m_primaryGeneratorActionFactoryMessenger
    = new GsimPrimaryGeneratorActionFactoryMessenger<T>(this);
  
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()
    ->report("debug","exit  GsimPrimaryGeneratorActionFactory::GsimPrimaryGeneratorActionFactory()");
#endif  
}

template <class T>
GsimPrimaryGeneratorActionFactory<T>::~GsimPrimaryGeneratorActionFactory()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()
    ->report("debug","enter GsimPrimaryGeneratorActionFactory::~GsimPrimaryGeneratorActionFactory()");
#endif
  
  delete m_primaryGeneratorActionFactoryMessenger;

#ifdef GSIMDEBUG
  GsimMessage::getInstance()
    ->report("debug","exit  GsimPrimaryGeneratorActionFactory::~GsimPrimaryGeneratorActionFactory()");
#endif    
}


template <class T>
void GsimPrimaryGeneratorActionFactory<T>::buildAndRegister()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()
    ->report("debug","enter GsimPrimaryGeneratorActionFactory::buildAndRegister()");
#endif
  
  G4RunManager* fRunManager = G4RunManager::GetRunManager();

  if(!fRunManager) {
    std::string msg = "GsimPrimaryGeneratorActionFactory::buildAndRegister() is called ";
    msg += "but G4RunManager is not exit.";
    msg += "New PrimaryGeneratorAction is not created.";
    GsimMessage::getInstance()
      ->report("warning",msg);
    return;
  }

  if(s_currentPrimaryGeneratorAction) {
    delete s_currentPrimaryGeneratorAction;
    s_currentPrimaryGeneratorAction=0;
    GsimMessage::getInstance()
      ->report("warning","new PrimaryGeneratorAction is created and old one is deleted.");
  }
  
  
  GsimPrimaryGeneratorAction* primaryGeneratorAction = build();
  s_currentPrimaryGeneratorAction=primaryGeneratorAction;
  // [todo]
  // ... store some information to specify the primarygeneartoraction
  //       to persistency manager
  //     ===> in the primarygeneartoraction new process?
  //        or just prepare the information
  //          ====> then fill it at BeginOfRun
  
  fRunManager->SetUserAction(primaryGeneratorAction);

  //
  // fRunManager->Initialize(); is called inside G4RunManager
  //        just before the BeamOn at the first time.
  // This is independent of PrimaryGeneratorAction.
  //
  //  if(fRunManager->GetUserPhysicsList()) {
  //    // PhysicsList should be registred before G4RunManager::Initialize().
  //    fRunManager->Initialize();
  //  } else {
  //    // warning message.
  //    std::string msg = "G4RunManager::Initialize() is not called";
  //    msg+=" because PhysicsList should be registred before.";
  //    GsimMessage::getInstance()
  //      ->report("warning",msg);
  //  }
    
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()
    ->report("debug","exit  GsimPrimaryGeneratorActionFactory::buildAndRegister()");
#endif
}




template <class T>
GsimPrimaryGeneratorAction* GsimPrimaryGeneratorActionFactory<T>::build() {
  return (new T());
}

#endif //GsimPrimaryGeneratorActionFactory_h



