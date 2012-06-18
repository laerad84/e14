/**
 *  @file
 *  @brief  GsimE14CC01
 *  $Id: GsimE14CC01.h,v 1.2 2006/12/06 19:04:45 nanjo Exp $
 *  $Log: GsimE14CC01.h,v $
 *  Revision 1.2  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE14CC01_h
#define GsimE14CC01_h

//includes
#include <string>
#include <list>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE14CC01
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE14CC01 : public GsimDetector
{
 public:
  GsimE14CC01(std::string name,
	      GsimDetector* motherDetector,
	      G4ThreeVector transV,
	      G4ThreeVector rotV,
	      int userFlag=0);
  
  virtual ~GsimE14CC01();
  virtual void   setFastSimulationLevel(int level);
  
  static double getCC01Length();
 protected:
  std::list<GsimDetector*> m_detList;
  GsimE14CC01();

};

inline double GsimE14CC01::getCC01Length() {
  double scint_thick = 0.5;
  double pbsb1_thick = 0.1;
  double pbsb2_thick = 0.2;
  double brass_thick = 0.0375;
  double al_thick = 1.5;
  double gap_scint = 0.005;
  double cc02_len =
    (scint_thick + 2.0*brass_thick + pbsb1_thick + gap_scint*2.0)*14.0 +
    (scint_thick + 2.0*brass_thick + pbsb2_thick + gap_scint*2.0)*29.0 +
    (al_thick*2.0 + scint_thick);
  return cc02_len;
}

#endif // GsimE14CC01_h
