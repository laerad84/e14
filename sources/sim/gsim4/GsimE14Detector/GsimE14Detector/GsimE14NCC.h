/**
 *  @file
 *  @brief  GsimE14NCC
 *  $Id: $
 *  $Log: $
 */
#ifndef GsimE14NCC_h
#define GsimE14NCC_h

//includes
#include <string>
#include <list>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE14NCC
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE14NCC : public GsimDetector
{
 public:
  GsimE14NCC(std::string name,
	     GsimDetector* motherDetector,
	     G4ThreeVector transV,
	     G4ThreeVector rotV,
	     int userFlag=0);
  
  virtual ~GsimE14NCC();
 protected:
  GsimE14NCC();
};

#endif // GsimE14NCC_h
