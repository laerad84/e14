/**
 *  @file
 *  @brief  GsimPhysicsListFactory
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimPhysicsListFactory.h,v 1.5 2006/08/02 01:58:48 nanjo Exp $
 *  $Log: GsimPhysicsListFactory.h,v $
 *  Revision 1.5  2006/08/02 01:58:48  nanjo
 *  One warning message is changed to a info. message.
 *
 *  Revision 1.4  2006/06/04 08:43:49  nanjo
 *  GsimUserLimits is enabled in default configuration.
 *
 *  Revision 1.3  2006/06/01 06:46:27  nanjo
 *  GsimUserLimit is added.
 *
 *  Revision 1.2  2006/01/26 04:34:22  nanjo
 *  Factory pattern and template method on factory and messenger class is intorduced .
 *
 */

#ifndef GsimPhysicsListFactory_h
#define GsimPhysicsListFactory_h

// includes
#include "GsimKernel/GsimUserLimits.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimPhysicsList/GsimCerenkovPhysics.h"
#include "G4VModularPhysicsList.hh"
#include "globals.hh"
#include <string>
#include <sstream>

// forward declaration
template<class T> class GsimPhysicsListFactoryMessenger;
class G4VUserPhysicsList;

/**
 *  @class GsimPhysicsListFactory
 *  @brief Abstract factory for G4VUserPhysicsList.
 *
 *  This class provides an interface to build a PhysicsList
 *  and register it to G4RunManager. 
 *  User should implement a concrete class with a constructor, 
 *  destructor, and build() function.
 *   -. constructor has name and messenger creation.
 *   -. empty destructor.
 *   -. In a build function, new corresponding PhysicsList.
 */

template<class T>
class GsimPhysicsListFactory
{
public:
  /// Constructor.
  GsimPhysicsListFactory(std::string name);

  /// Destructor.
  virtual ~GsimPhysicsListFactory();

  /// Build and register new PhysicsList.
  /**
   *  Build new PhysicsList and register it to G4RunManager,
   *  where delete current PhysicsList and reassign the newly
   *  created PhysicsList to the current PhysicsList pointer.
   */
  void buildAndRegister();

  /// Get name.
  inline std::string getName();
  
  void withUserLimits(bool withUL);
  void addCerenkov();
protected:

  ///build PhysicsList.
  G4VUserPhysicsList* build();

  /// Messenger (user inteface) for this PhysicsList factory.
  GsimPhysicsListFactoryMessenger<T>* m_physicsListFactoryMessenger;

  /// Name of this physicslist
  std::string m_name;
};

template<class T>
inline std::string GsimPhysicsListFactory<T>::getName() {
  return m_name;
}



//#include "GsimKernel/GsimPhysicsListFactory.h"
#include "GsimKernel/GsimPhysicsListFactoryMessenger.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4VUserPhysicsList.hh"
#include "G4RunManager.hh"
#include "G4Neutron.hh"
#include "G4ProcessVector.hh"
#include "G4VProcess.hh"

template<class T>
GsimPhysicsListFactory<T>::GsimPhysicsListFactory(std::string name)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()
    ->report("debug","enter GsimPhysicsListFactory::GsimPhysicsListFactory()");
#endif

  m_name=name;
  m_physicsListFactoryMessenger
    = new GsimPhysicsListFactoryMessenger<T>(this);
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()
    ->report("debug","exit  GsimPhysicsListFactory::GsimPhysicsListFactory()");
#endif
}

template<class T>
GsimPhysicsListFactory<T>::~GsimPhysicsListFactory()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()
    ->report("debug","enter GsimPhysicsListFactory::~GsimPhysicsListFactory()");
#endif
  
  delete m_physicsListFactoryMessenger;
  m_physicsListFactoryMessenger=0;

#ifdef GSIMDEBUG
  GsimMessage::getInstance()
    ->report("debug","exit  GsimPhysicsListFactory::~GsimPhysicsListFactory");
#endif
}

template<class T>
void GsimPhysicsListFactory<T>::buildAndRegister()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()
    ->report("debug","enter GsimPhysicsListFactory::buildAndRegister()");
#endif

  G4RunManager* fRunManager = G4RunManager::GetRunManager();
  
  if(!fRunManager) {
    std::string msg = "GsimPhysicsListFactory::buildAndRegister() is called ";
    msg += "but G4RunManager is not exit.";
    msg += "New PhysicsList is not created.";
    GsimMessage::getInstance()
      ->report("warning",msg);
    return;
  }
  
  const G4VUserPhysicsList* pl = fRunManager->GetUserPhysicsList();
  const GsimPhysicsList* gpl= dynamic_cast<const GsimPhysicsList*>(pl);
  if(!pl) {
    GsimMessage::getInstance()
      ->report("warning","No PhysicsList. New Physicslist is not created.");
    return;
  }
  if(!gpl) {
    std::string msg = "GsimPhysicsListFactory::buildAndRegister() can be used ";
    msg += "only once.";
    msg += "New PhysicsList is not created.";
    GsimMessage::getInstance()
      ->report("warning",msg);
    return;
  }

  const_cast<G4VUserPhysicsList*>(pl)->RemoveProcessManager();
  //delete pl; particles are killed from 9.1
  //GsimMessage::getInstance()
  //  ->report("info","new PhysicsList is created and old one is deleted.");

  G4VUserPhysicsList* newpl = build();
  
  if(gpl->isUserLimitsOn()) {
    G4VModularPhysicsList* mpl= dynamic_cast<G4VModularPhysicsList*>(newpl);
    if(mpl) {
      mpl->RegisterPhysics( new GsimUserLimits() );
    } else {
      std::string msg="UserLimis is not registered, since PhysicsList is not a G4VModularPhysicsList.";
      GsimMessage::getInstance()->report("warning",msg);
    }
  }

  if(gpl->isCerenkovAdded()) {
    G4VModularPhysicsList* mpl= dynamic_cast<G4VModularPhysicsList*>(newpl);
    if(mpl) {
      mpl->RegisterPhysics( new GsimCerenkovPhysics() );
    } else {
      std::string msg="Cerenkov is not registered, since PhysicsList is not a G4VModularPhysicsList.";
      GsimMessage::getInstance()->report("warning",msg);
    }
  }
  
  fRunManager->SetUserInitialization(newpl);
  // ConstructParticle is already done by GsimPhysicsList.
  fRunManager->PhysicsHasBeenModified();

  // fRunManager->Initialize(); is called inside G4RunManager
  //        just before the BeamOn at the first time.
  // fRunManager->Initialize();
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()
    ->report("debug","exit  GsimPhysicsListFactory::buildAndRegister()");
#endif
}


template<class T>
G4VUserPhysicsList*  GsimPhysicsListFactory<T>::build()
{
  T* pl = new T();
  return pl;
}

#endif //GsimPhysicsListFactory_h



