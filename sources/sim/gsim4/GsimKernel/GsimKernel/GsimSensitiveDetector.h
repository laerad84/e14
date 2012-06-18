/**
 *  @file
 *  @brief  GsimSensitiveDetector
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimSensitiveDetector.h,v 1.16 2007/02/04 12:55:41 nanjo Exp $
 *  $Log: GsimSensitiveDetector.h,v $
 *  Revision 1.16  2007/02/04 12:55:41  nanjo
 *  Fast simulation 3 is added for shower check.
 *
 *  Revision 1.15  2006/12/09 00:45:06  nanjo
 *  dump.
 *
 *  Revision 1.14  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 *  Revision 1.13  2006/12/04 17:27:49  nanjo
 *  Data are kept in each class, which are registered to persistencyManger.
 *  GsimPersistencyManger::setBranchOf is added then UserEventData is removed.
 *
 *  Revision 1.12  2006/12/02 07:06:11  nanjo
 *  sensitiveDetectorID, StopFlag, detID are updated.
 *
 *  Revision 1.11  2006/11/20 16:16:45  nanjo
 *  SensitiveDetectorList is kept in DetectorManager.
 *
 *  Revision 1.10  2006/11/16 13:13:00  nanjo
 *  Module id with detector depth..
 *
 *  Revision 1.9  2006/10/24 15:23:08  nanjo
 *  SensitiveDetector is re-structred.
 *
 *  Revision 1.8  2006/10/19 03:28:44  nanjo
 *  GsimPersistencyManagerMessenger is replaced by GsimRunActionMessneger.
 *  Information of photonuclear interaction is not filled here.
 *  Cluster ID is filled.
 *  Now GsimPersistencyManager, GsimDigitizer, and, GsimMessage is
 *  independent of Geant4. They will be moved to different directory
 *  in order to use from ROOT analysis.
 *
 *  Revision 1.7  2006/10/11 01:01:35  nanjo
 *  SensitiveDetector and HitConverter are restructured.
 *
 *  Revision 1.6  2006/08/11 06:23:30  nanjo
 *  Assign one GsimDetectorHitConverter per one GsimSensitiveDetector.
 *
 *  Revision 1.5  2006/06/14 05:54:22  nanjo
 *  GsimDigitizer is added.
 *
 *  Revision 1.4  2006/04/12 12:07:17  nanjo
 *  Fix typo.
 *
 *  Revision 1.3  2006/03/01 12:45:32  nanjo
 *  A member function of GsimDetector, cloneDetector, is added and used in E391Detector.
 *
 *  Revision 1.2  2006/02/21 09:09:59  nanjo
 *  Sensitive detector name and channel id can be assigned. If the same sensitive detector name is used for some detectors, these detectors are recognized as channels in one detector.
 *
 *  Revision 1.1  2006/01/26 04:53:30  nanjo
 *  Detector and persistency classes are added.
 *
 */
#ifndef GsimSensitiveDetector_h
#define GsimSensitiveDetector_h

//includes
#include "G4VSensitiveDetector.hh"
#include "globals.hh"
#include <string>
#include <vector>
#include <list>
#include <map>

//forward declaration
class GsimSensitiveDetectorMessenger;
class G4HCofThisEvent;
class G4Step;
class G4TouchableHistory;
class G4LogicalVolume;
class GsimDetectorHitConverter;
class GsimDigitizer;
class GsimDetectorEventData;
class G4VPhysicalVolume;
class GsimDetector;

/**
 *  @class GsimSensitieiveDetector
 *  @brief SensitiveDetector.
 *
 *  This class provides ...
 */

enum SensitiveDetectorMode {
  chargedParticleSensitiveMode,
  energyDepositSensitiveMode,
  opticalPhotonSensitiveMode,
  opticalPhotonSensitiveFastMode,
  anyParticleSensitiveMode
};

class GsimSensitiveDetector : public G4VSensitiveDetector
{
 public:
  GsimSensitiveDetector(G4String name);
  virtual ~GsimSensitiveDetector();

  virtual void Initialize(G4HCofThisEvent* HCE);
  virtual void EndOfEvent(G4HCofThisEvent* HCE);
  virtual void clear();

  
  
  
  inline void  setSensitiveMode(SensitiveDetectorMode mode);
  inline void  setOpticalPhotonEfficiency(std::vector<double> waveLen,
					 std::vector<double> effi);
  virtual void process(const G4Step* aStep,G4TouchableHistory* ROhist);
  void storeHit(bool withHit);
  void storeDigi(bool withDigi);
  bool isStoreHit();
  bool isStoreDigi();

  bool withDataToStore();

  /**
   *  @function addDigitizer
   *  @brief Add digitizer.
   *  @param digi GsimDigitizer to be added.
   */
  void addDigitizer(GsimDigitizer* digi);
  
  std::string getName();
  int  getSensitiveDetectorID();
  void setSensitiveDetectorID(int id);
  void setThisCopyNoFactor(int thisCopyNoFactor);
  void setDeepCopyNoFactor(int deepCopyNoFactor);
  void setClusterID(int channelID,int clusterID);
  int  getClusterID(int channelID);
  std::list<int>  getChannelID(G4VPhysicalVolume* pv,
  			       std::map<G4VPhysicalVolume*,G4VPhysicalVolume*>& pvr);

  void setFastSimulationLevel(int level);
  double getTotalEnergy();

  /**
   *  @function setTdcThreshold
   *  @brief set TDC threshold
   *  @param eth threshold energy in the unit of MeV
   */
  void setTdcThreshold(double eth);
  
  /**
   *  @function setOnlineVetoThreshold
   *  @brief set online veto  threshold
   *  @param eth threshold energy in the unit of MeV
   */
  void setOnlineVetoThreshold(double eth);
  void setHitProcessDetector(GsimDetector* detector);
  void dump(int imode);
  void processHitsDetector(G4Step* aStep, G4TouchableHistory* ROhist);
  
 protected:
  G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);

  
  bool   isOpticalPhotonHit(double opticalPhotonEnergy);
  double getOpticalPhotonEfficiency(double opticalPhotonEnergy);

  /**
   *  @function makeBranch
   *  @brief Make a ROOT Branch for the hit. 
   */
  virtual void makeBranch();

  /**
   *  @function initializeDataValues
   *  @brief Initialize the data.
   */
  virtual void initializeDataValues();

  /**
   *  @function digitize
   *  @brief Digitize.
   */
  void digitize();

  /**
   *  @function sortHitData
   *  @brief Sort hit data with hitChannel, time, and, energy.
   */
  void sortHitData();

  /**
   *  @function clearHitData
   *  @brief Clear hit data.
   */
  void clearHitData();

  
		    
  GsimSensitiveDetectorMessenger* m_messenger;
  
  std::string m_name;

  //automatically assigned in GsimRunAction.
  int m_sensitiveDetectorID;
  
  SensitiveDetectorMode m_sensitiveMode;
  std::vector<double> m_opticalPhotonEfficiency;
  std::vector<double> m_opticalPhotonWaveLength;// in nm;
  
  
  
  bool m_storeHit;
  bool m_storeDigi;
  std::map<int,int> m_channelIDClusterID;

  GsimDetectorEventData* m_detectorEventData;
  GsimDetectorHitConverter* m_hitConverter;
  std::list<GsimDigitizer*> m_digitizerList;
  GsimDetector* m_hitProcessDetector;


  int m_fastSimulationLevel;
  double m_onlineVetoThreshold;//[MeV]
};

inline void GsimSensitiveDetector::setSensitiveMode(SensitiveDetectorMode mode) {
  m_sensitiveMode=mode;
}

inline void GsimSensitiveDetector::
setOpticalPhotonEfficiency(std::vector<double> waveLen,
			   std::vector<double> effi) {
  if(waveLen.size()!=effi.size()) return;
  
  m_opticalPhotonWaveLength=waveLen;
  m_opticalPhotonEfficiency=effi;
}

inline void GsimSensitiveDetector::storeHit(bool withHit) {
  m_storeHit=withHit;
}

inline void GsimSensitiveDetector::storeDigi(bool withDigi) {
  m_storeDigi=withDigi;
}

inline bool GsimSensitiveDetector::isStoreHit() {
  return m_storeHit;
}
inline bool GsimSensitiveDetector::isStoreDigi() {
  return m_storeDigi;
}

inline std::string GsimSensitiveDetector::getName()
{
  return m_name;
}

inline int  GsimSensitiveDetector::getSensitiveDetectorID()
{
  return m_sensitiveDetectorID;
}
inline void GsimSensitiveDetector::setFastSimulationLevel(int level)
{
  m_fastSimulationLevel=level;
}

inline void GsimSensitiveDetector::setOnlineVetoThreshold(double eth) {
  m_onlineVetoThreshold=eth;
}

inline void GsimSensitiveDetector::setHitProcessDetector(GsimDetector* detector) {
  m_hitProcessDetector=detector;
}

#endif // GsimSensitiveDetector_h

