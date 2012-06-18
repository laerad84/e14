/**
 *  @file
 *  @brief  GsimDigitizer
 *  $Id: GsimDigitizer.h,v 1.8 2006/12/06 18:44:00 nanjo Exp $ 
 *  $Log: GsimDigitizer.h,v $
 *  Revision 1.8  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 */
#ifndef GsimDigitizer_h
#define GsimDigitizer_h

//includes
#include <string>
#include <list>
#include <map>
//forward declaration
class GsimDetectorEventData;
class GsimDetectorHitData;
class GsimTimeData;
class GsimDigiData;

/**
 *  @class GsimSensitieiveDetector
 *  @brief SensitiveDetector.
 *
 *  This class provides ...
 */


class GsimDigitizer
{
 public:
  GsimDigitizer(std::string sensitiveDetectorName);
  virtual ~GsimDigitizer();
  
  virtual void digitize(GsimDetectorEventData* eventData);
  
  void setT0(double t0);
  void setTdcThresholdEnergy(double thEnergy);
  void setAdcGateWidth(double time);
  void setPileupTimeWidth(double pileupTimeWidth);
  

  virtual void buildMtimeFromHits(GsimDetectorEventData* eventData);
  virtual void constructDigiFromMtime(GsimDetectorEventData* eventData);
  virtual void fillHitsInformationToDigi(GsimDetectorEventData* eventData);
  virtual void fillEnergyToDigiFromMtim(GsimDetectorEventData* eventData);
  virtual void fillTimeToDigiFromMtim(GsimDetectorEventData* eventData);
  virtual void fillTiming(GsimDigiData* digiData,
			  std::list<GsimTimeData*>& channelTimeList);
  virtual void buildTrigFromMtimeDigi(GsimDetectorEventData* eventData);

  void setSensitiveDetectorID(int id);
  void setClusterID(int channelID,int clusterID);
  int  getClusterID(int channelID);

  void importDigitizerInformation();
  
 protected:  
  std::string m_name;
  std::string m_sensitiveDetectorName;
  int         m_sensitiveDetectorID;
  double m_t0;//ns
  double m_tdcThresholdEnergy;//MeV
  double m_pileupTimeWidth;//ns
  double m_adcGateWidth;//ns
  
  std::map<int,int> m_channelIDClusterID;
};

inline void GsimDigitizer::setSensitiveDetectorID(int id)
{
  m_sensitiveDetectorID=id;
}

inline void GsimDigitizer::setT0(double t0) {
  m_t0=t0;
}

inline void GsimDigitizer::setPileupTimeWidth(double pileupTimeWidth) {
  m_pileupTimeWidth=pileupTimeWidth;
}

     
inline void GsimDigitizer::setTdcThresholdEnergy(double thEnergy) {
  m_tdcThresholdEnergy=thEnergy;
}

inline void GsimDigitizer::setAdcGateWidth(double time) {
  m_adcGateWidth=time;
}

#endif // GsimDigitizer_h

