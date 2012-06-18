/**
 *  @file
 *  @brief  GsimE14CC05
 *  $Id: GsimE14CC05.h,v 1.2 2006/12/06 19:04:45 nanjo Exp $
 *  $Log: GsimE14CC05.h,v $
 *  Revision 1.2  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE14CC05_h
#define GsimE14CC05_h

//includes
#include <string>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE14CC05
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE14CC05 : public GsimDetector
{
 public:
  GsimE14CC05(std::string name,
	      GsimDetector* motherDetector,
	      G4ThreeVector transV,
	      G4ThreeVector rotV,
	      int userFlag=0);
  
  virtual ~GsimE14CC05();
  static double getCC05Length();
 
 protected:
  GsimE14CC05();
};

#endif // GsimE14CC05_h
