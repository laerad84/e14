/**
 *  @file
 *  @brief  GsimE391Membrane
 *  $Id: GsimE391Membrane.h,v 1.1 2007/02/04 12:57:39 nanjo Exp $
 *  $Log: GsimE391Membrane.h,v $
 *  Revision 1.1  2007/02/04 12:57:39  nanjo
 *  GsimE391Membrane is added.
 *
 *  Revision 1.2  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE391Membrane_h
#define GsimE391Membrane_h

//includes
#include <string>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE391Membrane
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE391Membrane : public GsimDetector
{
 public:
  GsimE391Membrane(std::string name,
		   GsimDetector* motherDetector,
		   G4ThreeVector transV,
		   G4ThreeVector rotV,
		   int useFlag=0);
  
  virtual ~GsimE391Membrane();
  
 protected:
  GsimE391Membrane();
};

#endif // GsimE391Membrane_h
