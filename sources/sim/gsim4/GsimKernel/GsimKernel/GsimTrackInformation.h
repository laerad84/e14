/**
 *  @file
 *  @brief  GsimTrackInformation
 *  $Id: GsimTrackInformation.h,v 1.12 2007/02/04 12:28:56 nanjo Exp $
 *  $Log: GsimTrackInformation.h,v $
 *  Revision 1.12  2007/02/04 12:28:56  nanjo
 *  Shower flag is added.
 *
 *  Revision 1.11  2007/01/11 06:47:31  nanjo
 *  current/previous detectorID are kept.
 *
 *  Revision 1.10  2006/12/09 21:34:09  nanjo
 *  briefHistory is corrected and dictionary write.
 *
 *  Revision 1.9  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 */
#ifndef GsimTrackInformation_h
#define GsimTrackInformation_h

//includes
#include "GsimData/GsimDetectorHitData.h"
#include "GsimPersistency/GsimPersistencyManager.h"
#include "G4VUserTrackInformation.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include <list>
#include <string>

//forward declaration
class G4Track;
class G4Step;

/**
 *  @class GsimTrackInformation
 *  @brief Track information.
 *
 *  This class provides ...
 */

class GsimTrackInformation : public G4VUserTrackInformation
{
public:
  GsimTrackInformation();
  virtual ~GsimTrackInformation();
  virtual void Print() const;
  void processStepHistory(const G4Step* aStep);
  void processTrackHistory(const G4Track* aTrack);
  void processShowerFlag(const G4Track* aTrack);

  void setStoredTrackID(int id);
  int  getStoredTrackID();
  void setStoredMotherTrackID(int id);
  int  getStoredMotherTrackID();
  void setStoreFlag();
  bool getStoreFlag();
  unsigned long long
    getBriefDetectorIDHistory();
  void setBriefDetectorIDHistory(unsigned long long histo);

  void setVertexTime(double time);
  double getVertexTime();

  void setVertexMomentum(G4ThreeVector pv);
  G4ThreeVector getVertexMomentum();

  void setStatus(int status);
  int  getStatus();

  void clearDetectorHitList();
  void addDetectorHit(GsimDetectorHitData* hit);
  void processTrackIDinHitData();

  void setStopStatus(int status);
  int  getStopStatus();

  int getCurrentDetectorID();
  int getCurrentBriefDetectorID();
  int getPreviousDetectorID();
  int getPreviousBriefDetectorID();
  void setInitialPositionID(int id, int briefID);

  void setShowerFlag(int flag);
  int  getShowerFlag();
  
 private:
  double        m_vertexTime;
  G4ThreeVector m_vertexMomentum;
  int           m_status; //0:stable 1:unstable
  int           m_storedTrackID;
  int           m_storedMotherTrackID;

  int           m_currentDetectorID;
  int           m_currentBriefDetectorID;
  int           m_previousDetectorID;
  int           m_previousBriefDetectorID;
  
  unsigned long long m_briefDetectorIDHistory;
  std::list<GsimDetectorHitData*> m_detectorHitList;
  bool m_storeFlag;
  bool m_isHistoryBufferFull;

  //trackStatus+10*fastSimulationLeve
  //0:fAlive                   Continue the tracking
  //1:fStopButAlive            Invoke active rest physics processes and
  //                              and kill the current track afterward
  //2:fStopAndKill             Kill the current track
  //3:fKillTrackAndSecondaries Kill the current track and also associated
  //                                secondaries.
  //4:fSuspend                 Suspend the current track
  //5:fPostponeToNextEvent     Postpones the tracking of thecurrent track  
  //                             to the next event.
  int           m_stopStatus;

  int           m_showerFlag;

  GsimPersistencyManager* m_persistencyManager;
};


inline void  GsimTrackInformation::setStoredTrackID(int id)
{
  m_storedTrackID=id;
}

inline int  GsimTrackInformation::getStoredTrackID()
{
  return m_storedTrackID;
}


inline void  GsimTrackInformation::setStoredMotherTrackID(int id)
{
  m_storedMotherTrackID=id;
}

inline int  GsimTrackInformation::getStoredMotherTrackID()
{
  return m_storedMotherTrackID;
}



inline void GsimTrackInformation::setStoreFlag()
{
  m_storeFlag=true;
}

inline bool GsimTrackInformation::getStoreFlag()
{
  return m_storeFlag;
}


inline unsigned long long
GsimTrackInformation::getBriefDetectorIDHistory()
{
  return m_briefDetectorIDHistory;
}

inline void GsimTrackInformation::setBriefDetectorIDHistory(unsigned long long histo)
{
  m_briefDetectorIDHistory=histo;
}

inline void GsimTrackInformation::clearDetectorHitList()
{
  m_detectorHitList.clear();
}
inline void GsimTrackInformation::addDetectorHit(GsimDetectorHitData* hit)
{
  m_detectorHitList.push_back(hit);
}

inline void GsimTrackInformation::setVertexTime(double time)
{
  m_vertexTime=time;
}

inline double GsimTrackInformation::getVertexTime() {
  return m_vertexTime;
}

inline void GsimTrackInformation::setVertexMomentum(G4ThreeVector pv)
{
  m_vertexMomentum=pv;
}

inline G4ThreeVector GsimTrackInformation::getVertexMomentum()
{
  return m_vertexMomentum;
}
     
inline void GsimTrackInformation::setStatus(int status)
{
  m_status=status;
}
inline int  GsimTrackInformation::getStatus()
{
  return m_status;
}

inline void GsimTrackInformation::setStopStatus(int status)
{
  m_stopStatus=status;
}

inline int  GsimTrackInformation::getStopStatus()
{
  return m_stopStatus;
}


inline int GsimTrackInformation::getCurrentDetectorID() {
  return m_currentDetectorID;
}

inline int GsimTrackInformation::getCurrentBriefDetectorID() {
  return m_currentBriefDetectorID;
}

inline int GsimTrackInformation::getPreviousDetectorID() {
  return m_previousDetectorID;
}
     
inline int GsimTrackInformation::getPreviousBriefDetectorID() {
  return m_previousBriefDetectorID;
}

inline void GsimTrackInformation::setShowerFlag(int flag) {
  m_showerFlag=flag;
}
inline int  GsimTrackInformation::getShowerFlag() {
  return m_showerFlag;
}

inline void GsimTrackInformation::setInitialPositionID(int id, int briefID)
{
  m_currentDetectorID=id;
  m_currentBriefDetectorID=briefID;
}
#endif // GsimTrackInformation_h


