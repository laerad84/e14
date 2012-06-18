/**
 *  $Id: GsimDetectorContainer.cc,v 1.2 2006/08/01 05:27:55 nanjo Exp $
 *  $Log: GsimDetectorContainer.cc,v $
 *  Revision 1.2  2006/08/01 05:27:55  nanjo
 *  GsimSpectrum is added. Debug print is updated. With/without Digi is implemented.
 *
 *  Revision 1.1  2006/01/26 04:53:30  nanjo
 *  Detector and persistency classes are added.
 *
 */
#include "GsimKernel/GsimDetectorContainer.h"
#include "GsimKernel/GsimDetector.h"
#include "GsimPersistency/GsimMessage.h"

#include <sstream>

GsimDetectorContainer::GsimDetectorContainer()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimDetectorContainer::~GsimDetectorContainer() {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

bool GsimDetectorContainer::insert(GsimDetector* detector) {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  
  std::pair<std::map<std::string,GsimDetector*>::iterator,bool> ok;
  ok = std::map<std::string,GsimDetector*>::
    insert(std::make_pair(detector->getFullName(),detector));
  if(!ok.second) {
    std::ostringstream ostr;
    ostr << "Multiple use of the same detector name : ";
    ostr << detector->getName();
    ostr << " is not inserted to the container.";
    GsimMessage::getInstance()->report("error",ostr.str());
      
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return ok.second;
}



