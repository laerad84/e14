/**
 *  @file
 *  @brief  GsimE14
 *  $Id: GsimE14.h,v 1.3 2006/12/06 19:04:45 nanjo Exp $
 *  $Log: GsimE14.h,v $
 *  Revision 1.3  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE14_h
#define GsimE14_h

//includes
#include <string>
#include <list>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE14
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE14 : public GsimDetector
{
 public:
  
  /**
   *  @function GsimE14
   *  @brief Constructor for GsimDetector
   *  @param name The name of the volume.
   *  @param motherDetector A pointer to the mother volume.
   *  @param transV A Geant (CLHEP) translation vector.
   *  @param rotV A Geant (CLHEP) rotation vector.
   *  @param userFlag
   *    10*x+y
   *     y: optical 0:nooptical BHPV, 1:optical BHPV
   *     x: beam hole size
   */
  GsimE14(std::string name,
	  GsimDetector* motherDetector,
	  G4ThreeVector transV,
	  G4ThreeVector rotV,
	  int userFlag=0);
  
  virtual ~GsimE14();

 protected:
  virtual void beginOfRunAction();
  virtual void endOfRunAction();
  virtual bool beginOfEventAction(const G4Event* evt);
  virtual bool endOfEventAction(const G4Event* evt);
  virtual bool steppingAction(const G4Step* theStep);
  virtual void setFastSimulationLevel(int level);

  GsimE14();

  
 int  m_photoNuclearN;
 int* m_photoNuclearDetID;

 std::list<GsimDetector*> m_detMoveList;

};


#endif // GsimE14_h
