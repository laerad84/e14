/**
 *  @file
 *  @brief  GsimE391CC02
 *  $Id: GsimE391CC02.h,v 1.2 2006/12/06 18:58:52 nanjo Exp $
 *  $Log: GsimE391CC02.h,v $
 *  Revision 1.2  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE391CC02_h
#define GsimE391CC02_h

//includes
#include <string>
#include <list>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE391CC02
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE391CC02 : public GsimDetector
{
 public:
  GsimE391CC02(std::string name,
	       GsimDetector* motherDetector,
	       G4ThreeVector transV,
	       G4ThreeVector rotV,
	       int useFlag=0);

  virtual void   setFastSimulationLevel(int level);
  
  virtual ~GsimE391CC02();

 protected:
  std::list<GsimDetector*> m_detList;
  GsimE391CC02();

};


#endif // GsimE391CC02_h
