/**
 *  @file
 *  @brief  GsimE14BHCV
 *  $Id: GsimE14BHCV.h,v 1.2 2006/12/06 19:04:45 nanjo Exp $
 *  $Log: GsimE14BHCV.h,v $
 *  Revision 1.2  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE14BHCV_h
#define GsimE14BHCV_h

//includes
#include <string>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE14BHCV
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE14BHCV : public GsimDetector
{
 public:
  GsimE14BHCV(std::string name,
	      GsimDetector* motherDetector,
	      G4ThreeVector transV,
	      G4ThreeVector rotV,
	      int userFlag=0);

  virtual ~GsimE14BHCV();

  static double getBHCVLength();
  
 protected:
  GsimE14BHCV();
};

     


#endif // GsimE14BHCV_h
