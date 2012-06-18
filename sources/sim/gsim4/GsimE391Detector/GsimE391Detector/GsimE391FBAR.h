/**
 *  @file
 *  @brief  GsimE391FBAR
 *  $Id: GsimE391FBAR.h,v 1.2 2006/12/06 18:58:52 nanjo Exp $
 *  $Log: GsimE391FBAR.h,v $
 *  Revision 1.2  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE391FBAR_h
#define GsimE391FBAR_h

//includes
#include <string>
#include <list>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE391FBAR
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE391FBAR : public GsimDetector
{
 public:
  GsimE391FBAR(std::string name,
	       GsimDetector* motherDetector,
	       G4ThreeVector transV,
	       G4ThreeVector rotV,
	       int useFlag=0);
  
  virtual void   setFastSimulationLevel(int level);
  
  virtual ~GsimE391FBAR();

 protected:
  std::list<GsimDetector*> m_detList;
  GsimE391FBAR();

};


#endif // GsimE391FBAR_h
