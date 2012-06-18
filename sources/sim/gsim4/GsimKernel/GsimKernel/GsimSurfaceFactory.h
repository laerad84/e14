/**
 *  @file
 *  @brief  GsimSurfaceFactory
 *  $Id:$
 *  $Log:$
 */

#ifndef GsimSurfaceFactory_h
#define GsimSurfaceFactory_h

// includes
#include <string>


// forward declaration
class GsimDetectorManager;
class GsimSurface;
class GsimSurfaceFactoryMessenger;

/**
 *  @class GsimSurfaceFactory
 *  @brief abstract factory for GsimSurface 
 *
 *  This class provides ...
 */


class GsimSurfaceFactory
{
public:
  /// Constructor.
  GsimSurfaceFactory(GsimDetectorManager* dm);

  /// Destructor.
  virtual ~GsimSurfaceFactory();

  /// Interface to build Detector and register it to G4RunManager.
  void build(std::string name,
	     std::string vol1FullName,
	     std::string vol2FullName);
  
protected:
  GsimDetectorManager* m_DM;
  GsimSurfaceFactoryMessenger* m_surfaceFactoryMessenger;
};

//#include "GsimKernel/GsimSurfaceFactory.h"
#include "GsimKernel/GsimSurfaceFactoryMessenger.h"
#include "GsimKernel/GsimSurface.h"
#include "GsimKernel/GsimDetectorManager.h"
#include "GsimKernel/GsimDetector.h"
#include "GsimPersistency/GsimMessage.h"


GsimSurfaceFactory::GsimSurfaceFactory(GsimDetectorManager* dm)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_DM=dm;
  m_surfaceFactoryMessenger
    = new GsimSurfaceFactoryMessenger(this);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  
}


GsimSurfaceFactory::~GsimSurfaceFactory()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif  
  delete m_surfaceFactoryMessenger;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  
}


void GsimSurfaceFactory::build(std::string name,
			       std::string vol1FullName,
			       std::string vol2FullName)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  
  GsimDetector* vol1Det=0;
  GsimDetector* vol2Det=0;
  
  // remvoe last "/"
  {
    int len = vol1FullName.size();
    if(std::string(vol1FullName,len-1,1) == "/") {
      vol1FullName=std::string(vol1FullName,0,len-1);
    }
    vol1Det=m_DM->findDetector(vol1FullName);
  }

  {
    int len = vol2FullName.size();
    if(std::string(vol2FullName,len-1,1) == "/") {
      vol2FullName=std::string(vol2FullName,0,len-1);
    }
    vol2Det=m_DM->findDetector(vol2FullName);
  }
  
  new GsimSurface(name,vol1Det,vol2Det);
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

#endif //GsimSurfaceFactory_h



