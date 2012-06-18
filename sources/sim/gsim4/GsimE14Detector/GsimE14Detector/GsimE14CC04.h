/**
 *  @file
 *  @brief  GsimE14CC04
 *  $Id: GsimE14CC04.h,v 1.2 2006/12/06 19:04:45 nanjo Exp $
 *  $Log: GsimE14CC04.h,v $
 *  Revision 1.2  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE14CC04_h
#define GsimE14CC04_h

//includes
#include <string>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE14CC04
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE14CC04 : public GsimDetector
{
 public:
  GsimE14CC04(std::string name,
	      GsimDetector* motherDetector,
	      G4ThreeVector transV,
	      G4ThreeVector rotV,
	      int userFlag=0);
  
  virtual ~GsimE14CC04();

  static double getCC04Length();

 protected:
  GsimE14CC04();
  int m_model;
};




#endif // GsimE14CC04_h
