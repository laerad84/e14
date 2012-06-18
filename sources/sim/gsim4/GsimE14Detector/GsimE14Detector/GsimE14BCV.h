/**
 *  @file
 *  @brief  GsimE14BCV
 *  $Id: GsimE14BCV.h,v 1.2 2006/12/06 19:04:45 nanjo Exp $
 *  $Log: GsimE14BCV.h,v $
 *  Revision 1.2  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE14BCV_h
#define GsimE14BCV_h

//includes
#include <string>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE14BCV
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE14BCV : public GsimDetector
{
 public:
  GsimE14BCV(std::string name,
	     GsimDetector* motherDetector,
	     G4ThreeVector transV,
	     G4ThreeVector rotV,
	     int userFlag=0);
  
  virtual ~GsimE14BCV();

 protected:
  GsimE14BCV();

};


#endif // GsimE14BCV_h
