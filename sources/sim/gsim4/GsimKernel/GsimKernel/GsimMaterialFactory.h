/**
 *  @file
 *  @brief  GsimMaterialFactory
 *  $Id: $
 *  $Log:$
 */

#ifndef GsimMaterialFactory_h
#define GsimMaterialFactory_h

// includes
#include <string>
#include "G4ThreeVector.hh"

// forward declaration
template <class T> class GsimMaterialFactoryMessenger;

/**
 *  @class GsimMaterialFactory
 *  @brief abstract factory for GsimMaterial 
 *
 *  This class provides ...
 */


template<class T> class GsimMaterialFactory
{
public:
  /// Constructor.
  GsimMaterialFactory(std::string factoryName);

  /// Destructor.
  virtual ~GsimMaterialFactory();

  inline std::string getFactoryName();
  
  virtual void build();
  
protected:
  /// Hidden constructor.
  GsimMaterialFactory();

  std::string m_factoryName;
  GsimMaterialFactoryMessenger<T>* m_materialFactoryMessenger;
};

template<class T> inline std::string GsimMaterialFactory<T>::getFactoryName() {
  return m_factoryName;
}




#include "GsimKernel/GsimMaterialFactoryMessenger.h"
#include "GsimPersistency/GsimMessage.h"


template<class T> GsimMaterialFactory<T>::GsimMaterialFactory(std::string factoryName)
							      
{
#ifdef GSIMDEBUG
  {
    std::ostringstream ostr;
    ostr << "enter GsimMaterialFactory::GsimMaterialFactory(std::string factoryName=";
    ostr << factoryName << ")"; 
    GsimMessage::getInstance()
      ->report("debug",ostr.str());
  }
#endif  
  m_factoryName=factoryName;
  
  m_materialFactoryMessenger
    = new GsimMaterialFactoryMessenger<T>(this);
#ifdef GSIMDEBUG
  {
    std::ostringstream ostr;
    ostr << "exit  GsimMaterialFactory::GsimMaterialFactory(std::string factoryName=";
    ostr << factoryName << ")"; 
    GsimMessage::getInstance()
      ->report("debug",ostr.str());
  }
#endif  
}


template<class T> GsimMaterialFactory<T>::~GsimMaterialFactory()
{
#ifdef GSIMDEBUG
  {
    GsimMessage::getInstance()
      ->report("debug","enter GsimMaterialFactory::~GsimMaterialFactory()");
  }
#endif  
  delete m_materialFactoryMessenger;
#ifdef GSIMDEBUG
  {
    GsimMessage::getInstance()
      ->report("debug","exit  GsimMaterialFactory::~GsimMaterialFactory()");
  }
#endif  
}


template<class T> void  GsimMaterialFactory<T>::GsimMaterialFactory::build()
{
#ifdef GSIMDEBUG
  {
    std::ostringstream ostr;
    ostr << "enter GsimMaterialFactory::build()";
    GsimMessage::getInstance()
      ->report("debug",ostr.str());
  }
#endif

  new T();
  
#ifdef GSIMDEBUG
 {
   std::ostringstream ostr;
   ostr << "exit  GsimMaterialFactory::build()";
   GsimMessage::getInstance()
     ->report("debug",ostr.str());
 }
#endif
}


#endif //GsimMaterialFactory_h



