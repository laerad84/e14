/**
 *  @file
 *  @brief  GsimEventAction
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimEventAction.h,v 1.12 2007/02/04 12:55:41 nanjo Exp $
 *  $Log: GsimEventAction.h,v $
 *  Revision 1.12  2007/02/04 12:55:41  nanjo
 *  Fast simulation 3 is added for shower check.
 *
 *  Revision 1.11  2007/01/12 15:24:23  nanjo
 *  Add flag to store empty data or not.
 *
 *  Revision 1.10  2006/12/07 04:44:59  nanjo
 *  runTree is added and GsimRunData is filled.
 *
 *  Revision 1.9  2006/11/30 20:07:11  nanjo
 *  Data are re-structured.
 *
 *  Revision 1.8  2006/09/29 08:21:56  nanjo
 *  Total number of event is automatically stored.
 *
 *  Revision 1.7  2006/08/24 17:39:00  nanjo
 *  Event processing status is printed in batch mode.
 *
 *  Revision 1.6  2006/06/21 11:47:56  nanjo
 *  BriefTrajectory classes are deleted.
 *
 *  Revision 1.5  2006/05/24 08:55:59  nanjo
 *  Decay of custom KL particls is treated in HEPEvt-like method.
 *  Decay products of custom KL is assigned at BeginOfEventAction,
 *  which would be used at the KL decay. At the same time,
 *  the custom KL G4ParticleDefinition is swaped to G4KaonZeroLong.
 *  So the assignment of interactions to the custom KL is not needed.
 *  The custom KL particle is converted to a G4KaonZeroLong with
 *  the spedific preAssigned decay channel.
 *
 *  Revision 1.4  2006/03/15 05:33:20  nanjo
 *  EventActionMessegner is added.
 *
 *  Revision 1.3  2006/02/01 15:42:26  nanjo
 *  BriefTrajectory is stored in ROOT file.
 *
 *  Revision 1.2  2006/01/31 22:47:08  nanjo
 *  BriefTrajectory is built from G4VUserTrakInformation.
 *
 *  Revision 1.1  2006/01/26 04:53:30  nanjo
 *  Detector and persistency classes are added.
 *
 */
#ifndef GsimEventAction_h
#define GsimEventAction_h

//includes
#include "G4UserEventAction.hh"
#include "globals.hh"

//forward declaration
class GsimEventActionMessenger;
class GsimDetectorManager;
class GsimRunData;
class GsimEventData;
class GsimGenParticleData;
class G4Event;
class G4Track;



/**
 *  @class GsimEventAction
 *  @brief EventAction
 *
 *  This class provides ...
 */

class GsimEventAction : public G4UserEventAction
{
public:
  /// Constructor.
  GsimEventAction(GsimDetectorManager* dm);

  /// Destructor.
  ~GsimEventAction();

  /// BeginOfEventAction
  void   BeginOfEventAction(const G4Event*);
  
  /// EndOfEventAction
  void   EndOfEventAction(const G4Event*);

  void storeBriefTrack(const G4Track* aTrack);

  inline void setVisualizationMode(int visualizationMode);
  inline void setDumpMode(int dumpMode);
  inline void setAccumulationNumber(int accumulationNumber);

  inline void setSkipEmptyData(bool isSkip=true);

  static void abortCurrentEvent();
  static bool isEventAborted(); 
  
private:
  /// Make decay kinematics of GsimKL particles in PrimaryVertex.
  void makeDecayInPrimaryVertex(const G4Event* anEvent);
  
  void dumpBriefTrack() const;
  void dumpTreeBriefTrack() const;

  /// Messenger.
  GsimEventActionMessenger* m_messenger;

  /// Pointer of detector manager.
  GsimDetectorManager* m_DM;

  GsimRunData*         m_runData;
  GsimEventData*       m_eventData;
  GsimGenParticleData* m_genParticleData;

  /// Visualization mode.
  /**
   *   - 0 no visualization
   *   - 1 draw trajectory
   *   - 2 draw trajectory+hit 
   */
  int m_visualizationMode;

  /// Dump mode.
  /**
   *  - 0 no dump
   *  - 1 first 10 event
   *  - 2 all event
   */
  int m_dumpMode;

  /// Count for accumulation of visualization
  /**
   *  -  0 accumulate infinitely
   *  -  N accumulate N event then continue
   *  - -N accumulate N event then pause
   */
  int m_accumulationNumber;
  int m_accumulationCount;
  /// Total number of events to process.
  /**
   * If this is set, status of event processing is printed.
   */
  int m_totalNumberOfEvents;
  int m_briefTrackCount;

  /// Skip empty data if it is 1.
  bool m_skipEmptyData;
  static bool s_isEventAborted;
};


inline void GsimEventAction::setVisualizationMode(int visualizationMode) {
  m_visualizationMode=visualizationMode;
}

inline void GsimEventAction::setDumpMode(int dumpMode) {
  m_dumpMode=dumpMode;
}
inline void GsimEventAction::setAccumulationNumber(int accumulationNumber) {
  m_accumulationNumber = accumulationNumber;
}

inline void GsimEventAction::setSkipEmptyData(bool isSkip) {
  m_skipEmptyData=isSkip;
}
#endif // GsimEventAction_h

    
