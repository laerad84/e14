/**
 *  @file
 *  @brief  GsimE391Beamline
 *  $Id: $
 *  $Log: $
 */
#ifndef GsimE391Beamline_h
#define GsimE391Beamline_h

//includes
#include <string>
#include <list>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE391Beamline
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE391Beamline : public GsimDetector
{
 public:
  GsimE391Beamline(std::string name,
		   GsimDetector* motherDetector,
		   G4ThreeVector transV,
		   G4ThreeVector rotV,
		   int useFlag=0);
  virtual void   setFastSimulationLevel(int level);
  virtual ~GsimE391Beamline();

 protected:
  GsimE391Beamline();

};


#endif // GsimE391Beamline_h
