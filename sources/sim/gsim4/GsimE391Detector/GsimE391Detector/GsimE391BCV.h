/**
 *  @file
 *  @brief  GsimE391BCV
 *  $Id: GsimE391BCV.h,v 1.3 2006/12/06 18:58:52 nanjo Exp $
 *  $Log: GsimE391BCV.h,v $
 *  Revision 1.3  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE391BCV_h
#define GsimE391BCV_h

//includes
#include <string>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE391BCV
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE391BCV : public GsimDetector
{
 public:
  GsimE391BCV(std::string name,
	      GsimDetector* motherDetector,
	      G4ThreeVector transV,
	      G4ThreeVector rotV,
	      int useFlag=0);
  
  virtual ~GsimE391BCV();

 protected:
  GsimE391BCV();

};


#endif // GsimE391BCV_h
