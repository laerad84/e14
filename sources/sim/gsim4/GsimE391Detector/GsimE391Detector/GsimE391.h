/**
 *  @file
 *  @brief  GsimE391
 *  $Id: GsimE391.h,v 1.4 2006/12/06 18:58:52 nanjo Exp $
 *  $Log: GsimE391.h,v $
 *  Revision 1.4  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimE391_h
#define GsimE391_h

//includes
#include <string>
#include <list>
#include "GsimKernel/GsimDetector.h"

//forward declaration

/**
 *  @class GsimE391
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimE391 : public GsimDetector
{
 public:
  GsimE391(std::string name,
	   GsimDetector* motherDetector,
	   G4ThreeVector transV,
	   G4ThreeVector rotV,
	   int useFlag=0);
  
  virtual ~GsimE391();

 protected:
  virtual void beginOfRunAction();
  virtual void endOfRunAction();
  virtual bool beginOfEventAction(const G4Event* evt);
  virtual bool endOfEventAction(const G4Event* evt);
  virtual bool steppingAction(const G4Step* theStep);
  virtual void setFastSimulationLevel(int level);
  GsimE391();

  
 int  m_photoNuclearN;
 int* m_photoNuclearDetID;

 std::list<GsimDetector*> m_detMoveList;

};


#endif // GsimE391_h
