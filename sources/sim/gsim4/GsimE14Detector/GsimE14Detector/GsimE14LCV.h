/**
 *  @file
 *  @brief  GsimE14LCV
 *  $Id$
 *  $Log$
 */

#ifndef GsimE14LCV_h
#define GsimE14LCV_h

//includes
#include <string>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE14LCV
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE14LCV : public GsimDetector
{
 public:
  GsimE14LCV(std::string name,
	     GsimDetector* motherDetector,
	     G4ThreeVector transV,
	     G4ThreeVector rotV,
	     int userFlag=0);
  
  virtual ~GsimE14LCV();
  
 protected:
  GsimE14LCV();
  int m_model;
};


#endif // GsimE14CV_h
