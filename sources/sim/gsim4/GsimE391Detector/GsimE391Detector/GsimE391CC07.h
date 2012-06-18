/**
 *  @file
 *  @brief  GsimE391CC07
 *  $Id: GsimE391CC07.h,v 1.3 2006/12/06 18:58:52 nanjo Exp $
 *  $Log: GsimE391CC07.h,v $
 *  Revision 1.3  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE391CC07_h
#define GsimE391CC07_h

//includes
#include <string>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE391CC07
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE391CC07 : public GsimDetector
{
 public:
  GsimE391CC07(std::string name,
	       GsimDetector* motherDetector,
	       G4ThreeVector transV,
	       G4ThreeVector rotV,
	       int useFlag=0);
  
  virtual ~GsimE391CC07();

 protected:
  GsimE391CC07();
  
};


#endif // GsimE391CC07_h
