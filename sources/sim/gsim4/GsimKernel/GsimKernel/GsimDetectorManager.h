/**
 *  @file
 *  @brief  GsimDetectorManager
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimDetectorManager.h,v 1.17 2007/02/04 12:55:41 nanjo Exp $
 *  $Log: GsimDetectorManager.h,v $
 *  Revision 1.17  2007/02/04 12:55:41  nanjo
 *  Fast simulation 3 is added for shower check.
 *
 *  Revision 1.16  2006/12/09 00:45:06  nanjo
 *  dump.
 *
 *  Revision 1.15  2006/12/04 17:27:49  nanjo
 *  Data are kept in each class, which are registered to persistencyManger.
 *  GsimPersistencyManger::setBranchOf is added then UserEventData is removed.
 *
 *  Revision 1.14  2006/11/20 16:16:45  nanjo
 *  SensitiveDetectorList is kept in DetectorManager.
 *
 *  Revision 1.13  2006/10/24 15:23:07  nanjo
 *  SensitiveDetector is re-structred.
 *
 *  Revision 1.12  2006/10/19 03:28:44  nanjo
 *  GsimPersistencyManagerMessenger is replaced by GsimRunActionMessneger.
 *  Information of photonuclear interaction is not filled here.
 *  Cluster ID is filled.
 *  Now GsimPersistencyManager, GsimDigitizer, and, GsimMessage is
 *  independent of Geant4. They will be moved to different directory
 *  in order to use from ROOT analysis.
 *
 *  Revision 1.11  2006/09/10 22:11:50  nanjo
 *  PhotoNuclear counter is re-added.
 *
 *  Revision 1.10  2006/09/06 22:33:18  nanjo
 *  GsimDetectorData is added.
 *
 *  Revision 1.9  2006/06/22 11:38:57  nanjo
 *  Modifications around briefDetectorID and briefDetectorName.
 *
 *  Revision 1.8  2006/03/17 08:02:13  nanjo
 *  Add a flag to disable GsimBreifTrajectory. Make faster for the detector loop.
 *
 *  Revision 1.7  2006/03/17 02:42:28  nanjo
 *  GsimVacuum is changed to GsimLowVacuum for some E391 detectors.
 *
 *  Revision 1.6  2006/03/14 18:02:54  nanjo
 *  Fix outerMaterial of CC04 and CC05.
 *
 *  Revision 1.5  2006/01/31 22:47:08  nanjo
 *  BriefTrajectory is built from G4VUserTrakInformation.
 *
 *  Revision 1.4  2006/01/31 03:00:38  nanjo
 *  Detector ID and process ID are introduced and stored in TFile.
 *
 *  Revision 1.3  2006/01/30 08:40:41  nanjo
 *  Process name created is stored in persistencyManager.
 *
 *  Revision 1.2  2006/01/30 02:42:07  nanjo
 *  Detector information is stored in persistencyManager.
 *
 *  Revision 1.1  2006/01/26 04:53:30  nanjo
 *  Detector and persistency classes are added.
 *
 */
#ifndef GsimDetectorManager_h
#define GsimDetectorManager_h

//includes
#include "GsimKernel/GsimDetectorContainer.h"
#include "GsimKernel/GsimSensitiveDetector.h"
#include <string>
#include <list>
#include <map>

//forward declaration
class GsimDetector;
class GsimDetectorManagerMessenger;
class GsimDetectorData;
class GsimPhysicalVolumeData;
class G4Event;
class G4Step;
class G4Track;
class G4SteppingManager;
class G4VPhysicalVolume;



/**
 *  @class GsimDetectorManager
 *  @brief DetectorManager.
 *
 *  This class provides ...
 */

class GsimDetectorManager
{
 public:
  GsimDetectorManager();
  ~GsimDetectorManager();

  bool registerDetector(GsimDetector* detector);

  
  void update();
  void redraw();
  void renewMessenger();
  void print();
  void beginOfRunAction();
  void endOfRunAction();
  
  void beginOfEventAction(const G4Event* evt);
  void endOfEventAction(const G4Event* evt);
  
  void steppingAction(const G4Step* theStep);
		      

  void preTrackingAction(const G4Track* aTrack);
  void postTrackingAction(const G4Track* aTrack);

  GsimDetector* findDetector(std::string fullName);

  std::map<int,std::string> getDetectorIDFullName();
  std::map<int,int> getDetectorIDBriefID();
  std::map<int,std::string> getDetectorBriefIDBriefName();
  
  inline bool isUpdated();
  bool isModified();

  bool withDataToStore();

  void dumpSD();
  void dumpSDData();
  
 private:
  void fillDetectorData();
  void fillPhysicalVolumeData();


  void assignDetector(std::map<G4VPhysicalVolume*,GsimDetector*>& pvd);
  void scanParentsForDetectorAssign(G4VPhysicalVolume* pv,
				    std::map<std::string, GsimDetector*>& pvNameDetectorMap,
				    std::map<G4VPhysicalVolume*,G4VPhysicalVolume*>& pvr,
				    std::list<G4VPhysicalVolume*>& pvBuffer,
				    std::map<G4VPhysicalVolume*,GsimDetector*>& pvd);
  
  GsimDetectorManagerMessenger* m_messenger;
  GsimDetectorContainer m_DC;

  GsimDetectorData* m_detectorData;
  GsimPhysicalVolumeData* m_physicalVolumeData;
  
  std::list<GsimSensitiveDetector*> m_sensitiveDetectorList;
  
  bool m_isUpdated;

  bool m_isFirstBeginOfEvent;
  std::list<GsimDetector*> m_doDefaultBeginOfEvent;
  std::list<GsimDetector*> m_doBeginOfEvent;

  bool m_isFirstEndOfEvent;
  std::list<GsimDetector*> m_doDefaultEndOfEvent;
  std::list<GsimDetector*> m_doEndOfEvent;

  bool m_isFirstStep;
  bool m_withTrackHistory;
  std::map<int,GsimDetector*> m_doDefaultSteppingList;
  std::map<int,GsimDetector*> m_doSteppingList;

  bool m_isFirstPreTrack;
  std::map<int,GsimDetector*> m_doDefaultPreTrackingList;
  std::list<GsimDetector*> m_doPreTrackingList;
  
  bool m_isFirstPostTrack;
  std::list<GsimDetector*> m_doDefaultPostTrackingList;
  std::list<GsimDetector*> m_doPostTrackingList;
};

inline bool GsimDetectorManager::isUpdated() {
  return m_isUpdated;
}

#endif // GsimDetectorManager_h
