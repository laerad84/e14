/**
 *  @file
 *  @brief  GsimE14FBAR
 *  $Id: GsimE14FBAR.h,v 1.2 2006/12/06 19:04:45 nanjo Exp $
 *  $Log: GsimE14FBAR.h,v $
 *  Revision 1.2  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE14FBAR_h
#define GsimE14FBAR_h

//includes
#include <string>
#include <list>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE14FBAR
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE14FBAR : public GsimDetector
{
 public:
  GsimE14FBAR(std::string name,
	      GsimDetector* motherDetector,
	      G4ThreeVector transV,
	      G4ThreeVector rotV,
	      int userFlag=0);
  
  virtual void   setFastSimulationLevel(int level);
  
  virtual ~GsimE14FBAR();

 protected:
  std::list<GsimDetector*> m_detList;
  GsimE14FBAR();

};


#endif // GsimE14FBAR_h
