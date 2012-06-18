/**
 *  @file
 *  @brief  GsimE14CC00
 *  $Id: GsimE14CC00.h,v 1.2 2006/12/06 19:04:45 nanjo Exp $
 *  $Log: GsimE14CC00.h,v $
 *  Revision 1.2  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE14CC00_h
#define GsimE14CC00_h

//includes
#include <string>
#include <list>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE14CC00
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE14CC00 : public GsimDetector
{
 public:
  GsimE14CC00(std::string name,
	      GsimDetector* motherDetector,
	      G4ThreeVector transV,
	      G4ThreeVector rotV,
	      int userFlag=0);
  virtual void   setFastSimulationLevel(int level);
  virtual ~GsimE14CC00();
  static double getCC00Length();

 protected:
  std::list<GsimDetector*> m_detList;
  GsimE14CC00();

};

inline double GsimE14CC00::getCC00Length() {
  double  s_thick = 0.5;
  double  w_thick = 2.0;
  double  gap = 0.1;
  double  ll          = s_thick + w_thick + gap; // 1 layer length
  double  cc00_len    = ll*10 + s_thick;
  return cc00_len;
}
     


#endif // GsimE14CC00_h
