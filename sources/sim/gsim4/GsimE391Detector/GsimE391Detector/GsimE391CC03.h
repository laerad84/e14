/**
 *  @file
 *  @brief  GsimE391CC03
 *  $Id: GsimE391CC03.h,v 1.3 2006/12/06 18:58:52 nanjo Exp $
 *  $Log: GsimE391CC03.h,v $
 *  Revision 1.3  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE391CC03_h
#define GsimE391CC03_h

//includes
#include <string>
#include <list>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE391CC03
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE391CC03 : public GsimDetector
{
 public:
  GsimE391CC03(std::string name,
	       GsimDetector* motherDetector,
	       G4ThreeVector transV,
	       G4ThreeVector rotV,
	       int useFlag=0);
  
  virtual void   setFastSimulationLevel(int level);
  
  virtual ~GsimE391CC03();

 protected:
  std::list<GsimDetector*> m_detList;
  GsimE391CC03();
};


#endif // GsimE391CC03_h
