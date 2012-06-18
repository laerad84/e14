/**
 *  @file
 *  @brief  GsimSpectrumFactory
 *  $Id: GsimSpectrumFactory.h,v 1.2 2006/12/06 18:44:00 nanjo Exp $ 
 *  $Log: GsimSpectrumFactory.h,v $
 *  Revision 1.2  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 */

#ifndef GsimSpectrumFactory_h
#define GsimSpectrumFactory_h

// includes
#include <string>

// forward declaration
class GsimSpectrum;
template <class T> class GsimSpectrumFactoryMessenger;


/**
 *  @class GsimSpectrumFactory
 *  @brief abstract factory for GsimSpectrum 
 *
 *  This class provides ...
 */


template<class T> class GsimSpectrumFactory
{
public:
  /// Constructor.
  GsimSpectrumFactory(std::string name);

  /// Destructor.
  virtual ~GsimSpectrumFactory();

  inline std::string getName();
  
  /// Interface to build  and register
  void buildAndRegister();

  
protected:
  /// Hidden constructor.
  GsimSpectrumFactory();

  /// Build spectrum.
  /**
   *  User should implement this method where GsimSpectrum
   *  should be created and returned.
   */
  virtual GsimSpectrum* build();
  std::string m_name;
  GsimSpectrumFactoryMessenger<T>* m_spectrumFactoryMessenger;
};

template<class T> inline std::string GsimSpectrumFactory<T>::getName() {
  return m_name;
}



//#include "GsimKernel/GsimSpectrumFactory.h"
#include "GsimKernel/GsimSpectrumFactoryMessenger.h"
#include "GsimKernel/GsimSpectrum.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimKernel/GsimPrimaryGeneratorAction.h"
#include "G4RunManager.hh"
#include "G4VUserPrimaryGeneratorAction.hh"


template<class T> GsimSpectrumFactory<T>::GsimSpectrumFactory(std::string name)
{
  m_name=name;
  m_spectrumFactoryMessenger
    = new GsimSpectrumFactoryMessenger<T>(this);
}


template<class T> GsimSpectrumFactory<T>::~GsimSpectrumFactory()
{
  delete m_spectrumFactoryMessenger;
}


template<class T> void GsimSpectrumFactory<T>::buildAndRegister()
{
  
  
  const G4VUserPrimaryGeneratorAction* cpga = G4RunManager::GetRunManager()
    ->GetUserPrimaryGeneratorAction();
  
  G4VUserPrimaryGeneratorAction* pga = const_cast<G4VUserPrimaryGeneratorAction*>(cpga);
  GsimPrimaryGeneratorAction* gpga = dynamic_cast<GsimPrimaryGeneratorAction*>(pga);
  
  if(gpga) {
    GsimSpectrum* spectrum = build();
    gpga->registerSpectrum(spectrum);
  }
}


template<class T> GsimSpectrum*  GsimSpectrumFactory<T>::GsimSpectrumFactory::build()
{
  return (new T(m_name));
}


#endif //GsimSpectrumFactory_h



