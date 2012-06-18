/**
 *  @file
 *  @brief  GsimDetectorHitConverter
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimDetectorHitConverter.h,v 1.10 2006/12/02 07:06:11 nanjo Exp $
 *  $Log: GsimDetectorHitConverter.h,v $
 *  Revision 1.10  2006/12/02 07:06:11  nanjo
 *  sensitiveDetectorID, StopFlag, detID are updated.
 *
 *  Revision 1.9  2006/11/16 13:13:00  nanjo
 *  Module id with detector depth..
 *
 *  Revision 1.8  2006/10/24 15:23:07  nanjo
 *  SensitiveDetector is re-structred.
 *
 *  Revision 1.7  2006/10/11 01:01:35  nanjo
 *  SensitiveDetector and HitConverter are restructured.
 *
 *  Revision 1.6  2006/10/10 11:21:24  nanjo
 *  Add comments.
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
#ifndef GsimDetectorHitConverter_h
#define GsimDetectorHitConverter_h

//includes
#include <string>
#include <list>
#include <map>
//forward declaration
class G4Step;
class G4TouchableHistory;
class GsimDetectorEventData;
class G4VPhysicalVolume;
class G4StepPoint;
/**
 *  @class GsimDetectorHitConverter
 *  @brief GsimDetectorHitConverter converts G4Step to GsimDetectorHit.
 *
 *  This class provides a converter from G4Step to
 *  GsimDetectorHitData.
 */


class GsimDetectorHitConverter
{
 public:

  /**
   *  @function GsimDetectorHitConverter
   *  @brief Constructor for GsimDetectorHitConverter.
   *  @param name The name of HitConverter
   */
  GsimDetectorHitConverter(std::string name);

  /**
   *  @function ~GsimDetectorHitConverter
   *  @brief Destructor for GsimDetectorHitConverter.
   */
  virtual ~GsimDetectorHitConverter();

  void setSensitiveDetectorID(int id);
  
  /**
   *  @function convertHit
   *  @brief convert G4Step to GsimDetectorHit.
   *  @param aStep A pointer of G4Step.
   *  @param ROhist A readout history.
   *  @param storeHit A flag for the hit store.
   */
  virtual void convertHit(GsimDetectorEventData* eventData,
			  const G4Step* aStep,G4TouchableHistory* ROhist,
			  bool storeHit);
  void setThisCopyNoFactor(int thisCopyNoFactor);
  void setDeepCopyNoFactor(int deepCopyNoFactor);
  void setOverflowTime(double time);
  int  getChannelID(G4StepPoint* sp);
  std::list<int> getChannelID(G4VPhysicalVolume* pv,
			      std::map<G4VPhysicalVolume*,G4VPhysicalVolume*>& pvr);
  
 protected:
  std::string m_name;
  std::string m_converterName;
  int m_sensitiveDetectorID;
  int m_thisCopyNoFactor;
  int m_deepCopyNoFactor;
  double m_overflowTime;//[ns]
};

inline void GsimDetectorHitConverter::setSensitiveDetectorID(int id)
{
  m_sensitiveDetectorID=id;
}

inline void GsimDetectorHitConverter::setThisCopyNoFactor(int thisCopyNoFactor){
  m_thisCopyNoFactor=thisCopyNoFactor;
}

inline void GsimDetectorHitConverter::setDeepCopyNoFactor(int deepCopyNoFactor){
  m_deepCopyNoFactor=deepCopyNoFactor;
}

inline void GsimDetectorHitConverter::setOverflowTime(double time){
  m_overflowTime=time;
}

#endif // GsimDetectorHitConverter_h

