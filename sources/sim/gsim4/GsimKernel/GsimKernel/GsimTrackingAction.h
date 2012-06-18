 /**
 *  @file
 *  @brief  GsimTrackingAction
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimTrackingAction.h,v 1.5 2007/02/04 12:27:44 nanjo Exp $
 *  $Log: GsimTrackingAction.h,v $
 *  Revision 1.5  2007/02/04 12:27:44  nanjo
 *  Track history control. 2ndaries info. is add. annihil is added for shower decision.
 *
 *  Revision 1.4  2006/12/09 21:34:09  nanjo
 *  briefHistory is corrected and dictionary write.
 *
 *  Revision 1.3  2006/12/09 00:45:06  nanjo
 *  dump.
 *
 *  Revision 1.2  2006/06/21 11:47:56  nanjo
 *  BriefTrajectory classes are deleted.
 *
 *  Revision 1.1  2006/01/26 04:53:30  nanjo
 *  Detector and persistency classes are added.
 *
 */
#ifndef GsimTrackingAction_h
#define GsimTrackingAction_h


//includes
#include "G4UserTrackingAction.hh"
#include "globals.hh"
#include <list>

//forward declaration
class GsimDetectorManager;
class GsimTrackingActionMessenger;
class G4Track;

/**
 *  @class GsimTrackingAction
 *  @brief TrackingAction
 *
 *  This class provides ...
 */

class GsimTrackingAction : public G4UserTrackingAction
{
 public:  
  GsimTrackingAction(GsimDetectorManager* dm);
  ~GsimTrackingAction();
  
  void PreUserTrackingAction(const G4Track*);
  void PostUserTrackingAction(const G4Track*);
  void dumpPreTrack(const G4Track* aTrack);
  void setBriefTrackStore(bool isStore);
  void setForceStorePrimary(bool isStore);
  void setTrackHistory(bool withTrackHistory);
  bool withTrackHistory();
  void setTrackDump(bool isDump);
  void addPIDToMonitor(int pid);
  void clearPIDToMonitor();
  void initializeTrigger();
  
  bool isTriggerActive();
  bool isTriggered();
  void addPIDToTrigger(int pid);
  void clearPIDToTrigger();
  void addPIDToKill(int pid);
  void clearPIDToKill();

  void setStoreAllTracks(bool isStored);
  
 private:
  GsimDetectorManager* m_DM;
  bool m_isBriefTrackStore;
  bool m_isForceStorePrimary;
  bool m_withTrackHistory;
  bool m_isTrackDump;
  std::list<int> m_pidToMonitor;

  std::list<int> m_pidToTrigger;
  std::list<int> m_pidToKill;
  bool m_isTriggered;

  bool m_storeAllTracks;
  
  /// Messenger.
  GsimTrackingActionMessenger* m_messenger;
};

inline void GsimTrackingAction::setBriefTrackStore(bool isStore)
{
  m_isBriefTrackStore=isStore;
}

inline void GsimTrackingAction::setForceStorePrimary(bool isStore)
{
  m_isForceStorePrimary=isStore;
}

inline void GsimTrackingAction::setTrackHistory(bool withTrackHistory)
{
  m_withTrackHistory=withTrackHistory;
}

inline bool GsimTrackingAction::withTrackHistory()
{
  return m_withTrackHistory;
}

inline void GsimTrackingAction::setTrackDump(bool isDump)
{
  m_isTrackDump=isDump;
}

inline void GsimTrackingAction::addPIDToMonitor(int pid)
{
  m_pidToMonitor.push_back(pid);
  m_pidToMonitor.sort();
  m_pidToMonitor.unique();
}

inline void GsimTrackingAction::clearPIDToMonitor()
{
  m_pidToMonitor.clear();
}

inline void GsimTrackingAction::addPIDToTrigger(int pid)
{
  m_pidToTrigger.push_back(pid);
  m_pidToTrigger.sort();
  m_pidToTrigger.unique();
}

inline void GsimTrackingAction::clearPIDToTrigger()
{
  m_pidToTrigger.clear();
}

inline void GsimTrackingAction::initializeTrigger()
{
  m_isTriggered=false;
}

inline bool GsimTrackingAction::isTriggerActive()
{
  if(m_pidToTrigger.size()>0) return true;
  else return false;
}

inline bool GsimTrackingAction::isTriggered()
{
  return m_isTriggered;
}

inline void GsimTrackingAction::addPIDToKill(int pid)
{
  m_pidToKill.push_back(pid);
  m_pidToKill.sort();
  m_pidToKill.unique();
}

inline void GsimTrackingAction::clearPIDToKill()
{
  m_pidToKill.clear();
}

inline void GsimTrackingAction::setStoreAllTracks(bool isStored)
{
  m_storeAllTracks=isStored;
}

#endif // GsimTrackingAction_h
