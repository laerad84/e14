/**
 *  @file
 *  @brief  GsimE14CC03
 *  $Id: GsimE14CC03.h,v 1.3 2006/12/06 19:04:45 nanjo Exp $
 *  $Log: GsimE14CC03.h,v $
 *  Revision 1.3  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE14CC03_h
#define GsimE14CC03_h

//includes
#include <string>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE14CC03
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE14CC03 : public GsimDetector
{
 public:
  GsimE14CC03(std::string name,
	      GsimDetector* motherDetector,
	      G4ThreeVector transV,
	      G4ThreeVector rotV,
	      int userFlag=0);
  virtual ~GsimE14CC03();
 protected:
  GsimE14CC03();
  int m_model;

};


#endif // GsimE14CC03_h
