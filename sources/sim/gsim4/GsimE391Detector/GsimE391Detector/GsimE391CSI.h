/**
 *  @file
 *  @brief  GsimE391CSI
 *  $Id: GsimE391CSI.h,v 1.5 2006/12/06 18:58:52 nanjo Exp $
 *  $Log: GsimE391CSI.h,v $
 *  Revision 1.5  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE391CSI_h
#define GsimE391CSI_h

//includes
#include <string>
#include <list>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE391CSI
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE391CSI : public GsimDetector
{
 public:
  GsimE391CSI(std::string name,
	      GsimDetector* motherDetector,
	      G4ThreeVector transV,
	      G4ThreeVector rotV,
	      int useFlag=0);

  virtual void   setFastSimulationLevel(int level);
  
  virtual ~GsimE391CSI();

 protected:
  virtual bool beginOfEventAction(const G4Event* );
  virtual bool endOfEventAction(const G4Event* );
  virtual bool postTrackingAction(const G4Track* aTrack);

  double m_totEThreshold;
  std::list<GsimDetector*> m_detList;
  std::list<GsimDetector*> m_detMoveList;
  GsimE391CSI();
};


#endif // GsimE391CSI_h
