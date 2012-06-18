/**
 *  @file
 *  @brief  GsimE14CSI
 *  $Id: GsimE14CSI.h,v 1.6 2006/12/06 19:04:45 nanjo Exp $
 *  $Log: GsimE14CSI.h,v $
 *  Revision 1.6  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE14CSI_h
#define GsimE14CSI_h

//includes
#include <string>
#include <list>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE14CSI
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE14CSI : public GsimDetector
{
 public:
  GsimE14CSI(std::string name,
	     GsimDetector* motherDetector,
	     G4ThreeVector transV,
	     G4ThreeVector rotV,
	     int userFlag=0);
  
  virtual ~GsimE14CSI();
  virtual void   setFastSimulationLevel(int level);
  virtual bool endOfEventAction(const G4Event* );
 protected:

  double m_totEThreshold;
  std::list<GsimDetector*> m_detList;
  std::list<GsimDetector*> m_detMoveList;
  int m_model;
  GsimE14CSI();
  
};


#endif // GsimE14CSI_h
