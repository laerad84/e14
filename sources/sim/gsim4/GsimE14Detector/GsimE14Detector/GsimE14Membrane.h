/**
 *  @file
 *  @brief  GsimE14Membrane
 *  $Id: GsimE14Membrane.h,v 1.2 2006/12/06 19:04:45 nanjo Exp $
 *  $Log: GsimE14Membrane.h,v $
 *  Revision 1.2  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE14Membrane_h
#define GsimE14Membrane_h

//includes
#include <string>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE14Membrane
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE14Membrane : public GsimDetector
{
 public:
  GsimE14Membrane(std::string name,
		  GsimDetector* motherDetector,
		  G4ThreeVector transV,
		  G4ThreeVector rotV,
		  int userFlag=0);
  
  virtual ~GsimE14Membrane();
  
 protected:
  GsimE14Membrane();
};

#endif // GsimE14Membrane_h
