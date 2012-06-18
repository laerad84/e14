/**
 *  @file
 *  @brief  GsimE391CC06
 *  $Id: GsimE391CC06.h,v 1.3 2006/12/06 18:58:52 nanjo Exp $
 *  $Log: GsimE391CC06.h,v $
 *  Revision 1.3  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE391CC06_h
#define GsimE391CC06_h

//includes
#include <string>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE391CC06
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE391CC06 : public GsimDetector
{
 public:
  GsimE391CC06(std::string name,
	       GsimDetector* motherDetector,
	       G4ThreeVector transV,
	       G4ThreeVector rotV,
	       int useFlag=0);

  virtual ~GsimE391CC06();

 protected:
  GsimE391CC06();
};


#endif // GsimE391CC06_h
