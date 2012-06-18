/**
 *  @file
 *  @brief  GsimDetectorFactory
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimDetectorFactory.h,v 1.1 2006/01/26 04:53:30 nanjo Exp $
 *  $Log: GsimDetectorFactory.h,v $
 *  Revision 1.1  2006/01/26 04:53:30  nanjo
 *  Detector and persistency classes are added.
 *
 */

#ifndef GsimDetectorFactory_h
#define GsimDetectorFactory_h

// includes
#include <string>
#include "G4ThreeVector.hh"

// forward declaration
class GsimDetectorManager;
class GsimDetector;
template <class T> class GsimDetectorFactoryMessenger;
class G4VPhysicalVolume;

/**
 *  @class GsimDetectorFactory
 *  @brief abstract factory for GsimDetector 
 *
 *  This class provides ...
 */


template<class T> class GsimDetectorFactory
{
public:
  /// Constructor.
  GsimDetectorFactory(GsimDetectorManager* dm,std::string factoryName);

  /// Destructor.
  virtual ~GsimDetectorFactory();

  inline std::string getFactoryName();
  
  /// Interface to build Detector and register it to G4RunManager.
  void buildAndRegister(std::string name,
			std::string motherFullName,
			G4ThreeVector transV,G4ThreeVector rotV,
			int userFlag=0);
  
protected:
  /// Hidden constructor.
  GsimDetectorFactory();

  /// Build Detector which user should implement.
  /**
   *  User should implement this method where GsimDetector
   *  should be created and returned.
   */
  virtual GsimDetector* build(std::string name,
			      GsimDetector* motherDetector,
			      G4ThreeVector transV,G4ThreeVector rotV,
			      int userFlag=0);

  std::string m_factoryName;
  GsimDetectorFactoryMessenger<T>* m_detectorFactoryMessenger;
  GsimDetectorManager* m_DM;
  
};

template<class T> inline std::string GsimDetectorFactory<T>::getFactoryName() {
  return m_factoryName;
}



//#include "GsimKernel/GsimDetectorFactory.h"
#include "GsimKernel/GsimDetectorFactoryMessenger.h"
#include "GsimKernel/GsimDetectorManager.h"
#include "GsimKernel/GsimDetector.h"
#include "GsimPersistency/GsimMessage.h"


template<class T> GsimDetectorFactory<T>::GsimDetectorFactory(GsimDetectorManager* dm,
					 std::string factoryName)
{
#ifdef GSIMDEBUG
  {
    std::ostringstream ostr;
    ostr << "enter GsimDetectorFactory::GsimDetectorFactory(GsimDetectorManager* dm,std::string factoryName=";
    ostr << factoryName << ")"; 
    GsimMessage::getInstance()
      ->report("debug",ostr.str());
  }
#endif  
  m_DM=dm;
  m_factoryName=factoryName;
  
  m_detectorFactoryMessenger
    = new GsimDetectorFactoryMessenger<T>(this);
#ifdef GSIMDEBUG
  {
    std::ostringstream ostr;
    ostr << "exit  GsimDetectorFactory::GsimDetectorFactory(GsimDetectorManager* dm,std::string factoryName=";
    ostr << factoryName << ")"; 
    GsimMessage::getInstance()
      ->report("debug",ostr.str());
  }
#endif  
}


template<class T> GsimDetectorFactory<T>::~GsimDetectorFactory()
{
#ifdef GSIMDEBUG
  {
    GsimMessage::getInstance()
      ->report("debug","enter GsimDetectorFactory::~GsimDetectorFactory()");
  }
#endif  
  delete m_detectorFactoryMessenger;
#ifdef GSIMDEBUG
  {
    GsimMessage::getInstance()
      ->report("debug","exit  GsimDetectorFactory::~GsimDetectorFactory()");
  }
#endif  
}


template<class T> void GsimDetectorFactory<T>::buildAndRegister(std::string name,
								std::string motherFullName,
								G4ThreeVector transV,G4ThreeVector rotV,
								int userFlag)
{
#ifdef GSIMDEBUG
  {
    std::ostringstream ostr;
    ostr << "enter GsimDetectorFactory::buildAndRegister(";
    ostr << "name=" << name << ",";
    ostr << "motherFullName=" << motherFullName << ",";
    ostr << "G4ThreeVector transV=" << transV << ",";
    ostr << "G4ThreeVector rotV=" << rotV << ",";
    ostr << "userFlag=" << userFlag << ")";
    GsimMessage::getInstance()
      ->report("debug",ostr.str());
  }
#endif
  

  // remvoe last "/"
  int len = motherFullName.size();
  if(std::string(motherFullName,len-1,1) == "/") {
    motherFullName=std::string(motherFullName,0,len-1);
  }
  GsimDetector* motherDet=m_DM->findDetector(motherFullName);
  
  std::string fullname = motherFullName;
  fullname+="/";
  fullname+= name;
  if(m_DM->findDetector(fullname)) {
    std::ostringstream ostr;
    ostr << "Detector name : ";
    ostr << fullname;
    ostr << "is not built, which was already registered.";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
    return;
  }
  
  GsimDetector* det = build(name,motherDet,transV,rotV,userFlag);
  det->update();
  if(motherDet) motherDet->addDaughter(det);
  m_DM->registerDetector(det);
  
#ifdef GSIMDEBUG
  {
    std::ostringstream ostr;
    ostr << "enter GsimDetectorFactory::buildAndRegister(";
    ostr << "name=" << name << ",";
    ostr << "motherFullName=" << motherFullName << ",";
    ostr << "G4ThreeVector transV=" << transV << ",";
    ostr << "G4ThreeVector rotV=" << rotV << ",";
    ostr << "userFlag=" << userFlag << ")";
    GsimMessage::getInstance()
      ->report("debug",ostr.str());
  }
#endif
}


template<class T> GsimDetector*  GsimDetectorFactory<T>::GsimDetectorFactory::build(std::string name,
										    GsimDetector* motherDetector,
										    G4ThreeVector transV,G4ThreeVector rotV,
										    int userFlag)
{
#ifdef GSIMDEBUG
  {
    std::ostringstream ostr;
    ostr << "enter GsimDetectorFactory::build(";
    ostr << "name=" << name << ",";
    ostr << "mother=" << motherDetector << ",";
    ostr << "G4ThreeVector transV=" << transV << ",";
    ostr << "G4ThreeVector rotV=" << rotV << ",";
    ostr << "userFlag=" << userFlag << ")";
    GsimMessage::getInstance()
      ->report("debug",ostr.str());
  }
#endif
  
  return (new T(name,motherDetector,transV,rotV,userFlag));
  
#ifdef GSIMDEBUG
  {
    std::ostringstream ostr;
    ostr << "exit  GsimDetectorFactory::build(";
    ostr << "name=" << name << ",";
    ostr << "mother=" << motherDetector << ",";
    ostr << "G4ThreeVector transV=" << transV << ",";
    ostr << "G4ThreeVector rotV=" << rotV << ",";
    ostr << "userFlag=" << userFlag << ")";
    GsimMessage::getInstance()
      ->report("debug",ostr.str());
  }
#endif
}


#endif //GsimDetectorFactory_h



