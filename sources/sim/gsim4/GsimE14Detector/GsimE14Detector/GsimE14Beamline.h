/**
 *  @file
 *  @brief  GsimE14Beamline
 *  $Id:$
 *  $Log:$
 */
#ifndef GsimE14Beamline_h
#define GsimE14Beamline_h

//includes
#include <string>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE14Beamline
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE14Beamline : public GsimDetector
{
 public:
  GsimE14Beamline(std::string name,
		  GsimDetector* motherDetector,
		  G4ThreeVector transV,
		  G4ThreeVector rotV,
		  int userFlag=0);
  
  virtual ~GsimE14Beamline();

 protected:
  GsimE14Beamline();

  double roundThis(double val);
    

};


#endif // GsimE14Beamline_h
