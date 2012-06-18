/**
 *  @file
 *  @brief  GsimE14CC06
 *  $Id: GsimE14CC06.h,v 1.2 2006/12/06 19:04:45 nanjo Exp $
 *  $Log: GsimE14CC06.h,v $
 *  Revision 1.2  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE14CC06_h
#define GsimE14CC06_h

//includes
#include <string>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE14CC06
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE14CC06 : public GsimDetector
{
 public:
  GsimE14CC06(std::string name,
	      GsimDetector* motherDetector,
	      G4ThreeVector transV,
	      G4ThreeVector rotV,
	      int userFlag=0);
  
  virtual ~GsimE14CC06();

  static double getCC06Length();

 protected:
  GsimE14CC06();
  
};

#endif // GsimE14CC06_h
