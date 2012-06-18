/**
 *  @file
 *  @brief  GsimPbScintillator
 *  $Id: GsimPbScintillator.h,v 1.4 2006/12/06 19:28:29 nanjo Exp $
 *  $Log: GsimPbScintillator.h,v $
 *  Revision 1.4  2006/12/06 19:28:29  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimPbScintillator_h
#define GsimPbScintillator_h

//includes
#include <string>
#include "GsimKernel/GsimDetector.h"

//forward declaration
class GsimBox;
class G4Event;
class G4Track;

/**
 *  @class GsimPbScintillator
 *  @brief Detector.
 *
 *  This class provides ...
 */

class GsimPbScintillator : public GsimDetector
{
 public:
  GsimPbScintillator(std::string name,
		     GsimDetector* motherDetector,
		     G4ThreeVector transV,
		     G4ThreeVector rotV,
		     int userFlag=0);
  
  virtual ~GsimPbScintillator();

  virtual void beginOfRunAction();
  virtual bool beginOfEventAction(const G4Event* evt);
  virtual bool endOfEventAction(const G4Event* evt);
  virtual bool preTrackingAction(const G4Track* aTrack);
  virtual bool postTrackingAction(const G4Track* aTrack);

 protected:
  GsimBox* m_MB;
  GsimBox* m_Pb;
  GsimBox* m_Sc;
  
  virtual void constructPhysiDetector();
  virtual void updateParametersEtc();
  GsimPbScintillator();

  int    m_photoNuclearIniNum;
  int    m_photoNuclearFinNum;
  double m_photoNuclearIniPosZ[1000];
  int    m_photoNuclearIniDetectorID[1000];
  double m_photoNuclearFinPosZ[1000];
  int    m_photoNuclearFinDetectorID[1000];

  int    m_neutronIniNum;
  int    m_neutronFinNum;
  int    m_neutronWorldNNum;
  double m_neutronIniPosZ[1000];
  int    m_neutronIniDetectorID[1000];
  int    m_neutronIniCreProcessID[1000];
  double m_neutronIniE[1000];
  double m_neutronFinPosZ[1000];
  int    m_neutronFinDetectorID[1000];
  double m_neutronFinE[1000];
  int    m_neutronWorldN[1000];



  
};


#endif // GsimPbScintillator_h
