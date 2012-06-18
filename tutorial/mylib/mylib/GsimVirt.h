/**
 *  @file
 *  @brief  GsimVirt
 *  $Id: $
 *  $Log: $
 */
#ifndef GsimVirt_h
#define GsimVirt_h

//includes
#include <string>
#include "GsimKernel/GsimDetector.h"

//forward declaration
class G4Event;
class G4Track;
class G4Step;
class G4TouchableHistory;

/**
 *  @class GsimVirt
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimVirt : public GsimDetector
{
 public:
  GsimVirt(std::string name,
	   GsimDetector* motherDetector,
	   G4ThreeVector transV,
	   G4ThreeVector rotV,
	   int userFlag=0);
  
  virtual ~GsimVirt();

  virtual void beginOfRunAction();
  virtual void endOfRunAction();
  virtual bool beginOfEventAction(const G4Event* evt);
  virtual bool endOfEventAction(const G4Event* evt);
  virtual bool preTrackingAction(const G4Track* aTrack);
  virtual bool postTrackingAction(const G4Track* aTrack);
  virtual bool steppingAction(const G4Step* theStep);
  virtual void processHits(const G4Step* aStep,G4TouchableHistory* ROhist);

 protected:
  virtual void constructPhysiDetector();
  virtual void updateParametersEtc();
  GsimVirt();
};


#endif // GsimVirt_h
