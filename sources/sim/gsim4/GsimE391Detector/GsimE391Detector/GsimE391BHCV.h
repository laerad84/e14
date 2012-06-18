/**
 *  @file
 *  @brief  GsimE391BHCV
 *  $Id: GsimE391BHCV.h,v 1.3 2006/12/06 18:58:52 nanjo Exp $
 *  $Log: GsimE391BHCV.h,v $
 *  Revision 1.3  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE391BHCV_h
#define GsimE391BHCV_h

//includes
#include <string>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE391BHCV
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE391BHCV : public GsimDetector
{
 public:
  GsimE391BHCV(std::string name,
	       GsimDetector* motherDetector,
	       G4ThreeVector transV,
	       G4ThreeVector rotV,
	       int useFlag=0);
  
  virtual ~GsimE391BHCV();

 protected:
  GsimE391BHCV();
};


#endif // GsimE391BHCV_h
