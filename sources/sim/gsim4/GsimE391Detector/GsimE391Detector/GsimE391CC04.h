/**
 *  @file
 *  @brief  GsimE391CC04
 *  $Id: GsimE391CC04.h,v 1.2 2006/12/06 18:58:52 nanjo Exp $
 *  $Log: GsimE391CC04.h,v $
 *  Revision 1.2  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE391CC04_h
#define GsimE391CC04_h

//includes
#include <string>
#include <list>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE391CC04
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE391CC04 : public GsimDetector
{
 public:
  GsimE391CC04(std::string name,
	       GsimDetector* motherDetector,
	       G4ThreeVector transV,
	       G4ThreeVector rotV,
	       int useFlag=0);
  
  virtual void   setFastSimulationLevel(int level);
  
  virtual ~GsimE391CC04();

 protected:
  std::list<GsimDetector*> m_detList;
  GsimE391CC04();

};


#endif // GsimE391CC04_h
