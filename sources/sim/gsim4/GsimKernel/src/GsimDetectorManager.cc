/**
 *  $Id: GsimDetectorManager.cc,v 1.28 2007/02/04 12:55:41 nanjo Exp $
 *  $Log: GsimDetectorManager.cc,v $
 *  Revision 1.28  2007/02/04 12:55:41  nanjo
 *  Fast simulation 3 is added for shower check.
 *
 *  Revision 1.27  2006/12/09 00:45:06  nanjo
 *  dump.
 *
 *  Revision 1.26  2006/12/07 08:50:15  nanjo
 *  Midas interfaces for GsimGenParticleData and GsimDetectorEventData are added.
 *
 *  Revision 1.25  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 *  Revision 1.24  2006/12/04 17:27:49  nanjo
 *  Data are kept in each class, which are registered to persistencyManger.
 *  GsimPersistencyManger::setBranchOf is added then UserEventData is removed.
 *
 *  Revision 1.23  2006/11/20 16:16:45  nanjo
 *  SensitiveDetectorList is kept in DetectorManager.
 *
 *  Revision 1.22  2006/10/19 03:28:44  nanjo
 *  GsimPersistencyManagerMessenger is replaced by GsimRunActionMessneger.
 *  Information of photonuclear interaction is not filled here.
 *  Cluster ID is filled.
 *  Now GsimPersistencyManager, GsimDigitizer, and, GsimMessage is
 *  independent of Geant4. They will be moved to different directory
 *  in order to use from ROOT analysis.
 *
 *  Revision 1.21  2006/09/10 22:11:50  nanjo
 *  PhotoNuclear counter is re-added.
 *
 *  Revision 1.20  2006/09/06 22:33:18  nanjo
 *  GsimDetectorData is added.
 *
 *  Revision 1.19  2006/08/01 05:27:55  nanjo
 *  GsimSpectrum is added. Debug print is updated. With/without Digi is implemented.
 *
 *  Revision 1.18  2006/06/22 11:38:57  nanjo
 *  Modifications around briefDetectorID and briefDetectorName.
 *
 *  Revision 1.17  2006/06/01 06:46:27  nanjo
 *  GsimUserLimit is added.
 *
 *  Revision 1.16  2006/05/31 19:42:24  nanjo
 *  GsimDetector::getWorldDetector is added and magnetic field is implemented.
 *
 *  Revision 1.15  2006/05/25 12:33:15  nanjo
 *  Process name, "Primary", is added, which is used for a primary generated particle.
 *
 *  Revision 1.14  2006/05/24 09:08:20  nanjo
 *  The process assignment to the custom KLs is deleted.
 *
 *  Revision 1.13  2006/04/09 20:38:57  nanjo
 *  Set compression level of ROOT file, which was suggested by Jeremy.
 *
 *  Revision 1.12  2006/03/17 08:02:13  nanjo
 *  Add a flag to disable GsimBreifTrajectory. Make faster for the detector loop.
 *
 *  Revision 1.11  2006/03/17 02:42:28  nanjo
 *  GsimVacuum is changed to GsimLowVacuum for some E391 detectors.
 *
 *  Revision 1.10  2006/03/14 18:02:55  nanjo
 *  Fix outerMaterial of CC04 and CC05.
 *
 *  Revision 1.9  2006/03/14 16:11:51  nanjo
 *  Fix G4_Air to G4_AIR.
 *
 *  Revision 1.8  2006/03/04 10:48:33  nanjo
 *  If a negative number, -n, is set for the detector channel, the copy number of n-th up detector is used.
 *
 *  Revision 1.7  2006/02/02 21:54:02  nanjo
 *  E391 detector is sarted.
 *
 *  Revision 1.6  2006/02/02 19:27:56  nanjo
 *  Add various KL correspondig to decay modes.
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
#include "GsimKernel/GsimDetectorManager.h"
#include "GsimKernel/GsimDetectorContainer.h"
#include "GsimKernel/GsimDetector.h"
#include "GsimKernel/GsimDetectorManagerMessenger.h"
#include "GsimPersistency/GsimPersistencyManager.h"
#include "GsimKernel/GsimTrackInformation.h"
#include "GsimKernel/GsimTrackingAction.h"
#include "GsimKernel/GsimEventAction.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimData/GsimDetectorData.h"
#include "GsimData/GsimPhysicalVolumeData.h"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4StateManager.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ApplicationState.hh"
#include "G4VisManager.hh"
#include "G4ProcessTable.hh"
#include "G4UImanager.hh"

#include <sstream>


GsimDetectorManager::GsimDetectorManager() {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_isUpdated=false;
  m_isFirstBeginOfEvent=true;
  m_isFirstEndOfEvent=true;
  m_isFirstStep=true;
  m_withTrackHistory=true;
  m_isFirstPreTrack=true;
  m_isFirstPostTrack=true;
  m_detectorData = new GsimDetectorData();
  m_physicalVolumeData = new GsimPhysicalVolumeData();
  m_messenger = new GsimDetectorManagerMessenger(this);

#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  
}

GsimDetectorManager::~GsimDetectorManager() {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  for(GsimDetectorContainer::iterator it=m_DC.begin();
      it!=m_DC.end();it++) {
    GsimDetector* det =  (*it).second;
    delete  det;
  }
  m_DC.clear();
  delete m_detectorData;
  delete m_physicalVolumeData;
  delete m_messenger;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  

}

bool GsimDetectorManager::registerDetector(GsimDetector* detector)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  bool isInserted=m_DC.insert(detector);
  if(!isInserted) {
    std::ostringstream ostr;
    ostr << "Detector, "
	 << detector->getName()
	 << ", is not Registered."; 
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
    return isInserted;
  }
  m_isUpdated=false;

  int id=m_DC.size()-1;
  detector->setDetectorID(id);

  std::list<GsimDetector*> detList;
  detector->listDaughterDetector(detList);
  for(std::list<GsimDetector*>::iterator it=detList.begin();
      it!=detList.end();it++) {
    registerDetector((*it));
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif    
  return isInserted;

}

bool GsimDetectorManager::isModified()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  for(GsimDetectorContainer::iterator it=m_DC.begin();
      it!=m_DC.end();it++) {
    if ( (*it).second->isModified() == true)
      return true;
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif    
  return false;

}

bool GsimDetectorManager::withDataToStore()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  
  if(GsimEventAction::isEventAborted()) return false;
  
  for(std::list<GsimSensitiveDetector*>::iterator it=m_sensitiveDetectorList.begin();
      it!=m_sensitiveDetectorList.end();it++) {
    if( (*it)->withDataToStore() ) return true;
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif    
  return false;
}


void GsimDetectorManager::update()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif


  bool reDefineWorld=isModified();
  for(GsimDetectorContainer::iterator it=m_DC.begin();
      it!=m_DC.end();it++) {
    (*it).second->update();
  }

  if(reDefineWorld) {
    G4RunManager* fRunManager = G4RunManager::GetRunManager();
    fRunManager->DefineWorldVolume( GsimUtil::getUtil()->getPhysiWorld() ,true);
    fRunManager->SetGeometryToBeOptimized(true);
  }
  
  for(GsimDetectorContainer::iterator it=m_DC.begin();
      it!=m_DC.end();it++) {
    (*it).second->modificationDone();
  }


  if(GsimDetector::getWorldDetector()) {
    GsimDetector::getWorldDetector()->updateField();
    GsimDetector::getWorldDetector()->updateUserLimits();
  }
    
  
  m_isUpdated=true;
    
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif    

}

void GsimDetectorManager::redraw()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  if (G4VVisManager::GetConcreteInstance()) {
    G4UImanager* UI = G4UImanager::GetUIpointer();
    UI->ApplyCommand("/vis/scene/notifyHandlers");
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif    
}


void GsimDetectorManager::renewMessenger()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  
  for(GsimDetectorContainer::iterator it=m_DC.begin();
      it!=m_DC.end();it++) {
    (*it).second->deleteMessenger();
  }
  for(GsimDetectorContainer::iterator it=m_DC.begin();
      it!=m_DC.end();it++) {
    (*it).second->newMessenger();
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimDetectorManager::print()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  for(GsimDetectorContainer::iterator it=m_DC.begin();
      it!=m_DC.end();it++) {
    (*it).second->print();
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif

}

void GsimDetectorManager::beginOfRunAction()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  
  for(GsimDetectorContainer::iterator it=m_DC.begin();
      it!=m_DC.end();it++) {
    (*it).second->defaultBeginOfRunAction();
  }
  for(GsimDetectorContainer::iterator it=m_DC.begin();
      it!=m_DC.end();it++) {
    (*it).second->beginOfRunAction();
  }


  m_sensitiveDetectorList.clear();
  for(GsimDetectorContainer::iterator it=m_DC.begin();
      it!=m_DC.end();it++) {
    std::list<GsimSensitiveDetector*> lis=(*it).second->getSensitiveDetectorList();
    m_sensitiveDetectorList.merge(lis);
  }
  m_sensitiveDetectorList.sort();
  m_sensitiveDetectorList.unique();
  int cnt=0;
  for(std::list<GsimSensitiveDetector*>::iterator
	it=m_sensitiveDetectorList.begin();
      it!=m_sensitiveDetectorList.end();it++,cnt++) {
    (*it)->setSensitiveDetectorID(cnt);
  }

  fillDetectorData();
  fillPhysicalVolumeData();

  
  
  m_isFirstBeginOfEvent=true;
  m_isFirstEndOfEvent=true;
  m_isFirstStep=true;
  m_isFirstPreTrack=true;
  m_isFirstPostTrack=true;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif

}

void GsimDetectorManager::endOfRunAction()   {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  for(GsimDetectorContainer::iterator it=m_DC.begin();
      it!=m_DC.end();it++) {
    (*it).second->endOfRunAction();
  }
  for(GsimDetectorContainer::iterator it=m_DC.begin();
      it!=m_DC.end();it++) {
    (*it).second->defaultEndOfRunAction();
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif

}

void GsimDetectorManager::beginOfEventAction(const G4Event* evt)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  if(m_isFirstBeginOfEvent) {
    m_doDefaultBeginOfEvent.clear();
    m_doBeginOfEvent.clear();
    for(GsimDetectorContainer::iterator it=m_DC.begin();
	it!=m_DC.end();it++) {
      if( (*it).second->defaultBeginOfEventAction(evt) ) {
	m_doDefaultBeginOfEvent.push_back( (*it).second );
      }
    }
    for(GsimDetectorContainer::iterator it=m_DC.begin();
	it!=m_DC.end();it++) {
      if ((*it).second->beginOfEventAction(evt) ) {
	m_doBeginOfEvent.push_back( (*it).second );
      }
    }
    m_isFirstBeginOfEvent=false;
  } else {
    for(std::list<GsimDetector*>::iterator it=m_doDefaultBeginOfEvent.begin();
	it!=m_doDefaultBeginOfEvent.end();it++) {
      (*it)->defaultBeginOfEventAction(evt);
    }
    for(std::list<GsimDetector*>::iterator it=m_doBeginOfEvent.begin();
	it!=m_doBeginOfEvent.end();it++) {
      (*it)->beginOfEventAction(evt);
    }
  }
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif

}

void GsimDetectorManager::endOfEventAction(const G4Event* evt)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  if(m_isFirstEndOfEvent) {
    m_doDefaultEndOfEvent.clear();
    m_doEndOfEvent.clear();
    for(GsimDetectorContainer::iterator it=m_DC.begin();
	it!=m_DC.end();it++) {
      if( (*it).second->defaultEndOfEventAction(evt) ) {
	m_doDefaultEndOfEvent.push_back( (*it).second );
      }
    }
    for(GsimDetectorContainer::iterator it=m_DC.begin();
	it!=m_DC.end();it++) {
      if ((*it).second->endOfEventAction(evt) ) {
	m_doEndOfEvent.push_back( (*it).second );
      }
    }
    m_isFirstEndOfEvent=false;
  } else {
    for(std::list<GsimDetector*>::iterator it=m_doDefaultEndOfEvent.begin();
	it!=m_doDefaultEndOfEvent.end();it++) {
      (*it)->defaultEndOfEventAction(evt);
    }
    for(std::list<GsimDetector*>::iterator it=m_doEndOfEvent.begin();
	it!=m_doEndOfEvent.end();it++) {
      (*it)->endOfEventAction(evt);
    }
  }
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetectorManager::steppingAction(const G4Step* theStep)
					 
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  
  if(m_isFirstStep) {
    m_doDefaultSteppingList.clear();
    m_doSteppingList.clear();
    for(GsimDetectorContainer::iterator it=m_DC.begin();
	it!=m_DC.end();it++) {
      if ( (*it).second->defaultSteppingAction(theStep) ) {
	GsimDetector* det=(*it).second;
	int id=det->getDetectorID();
	m_doDefaultSteppingList.insert( std::make_pair(id,det) );
      }
    }
    for(GsimDetectorContainer::iterator it=m_DC.begin();
	it!=m_DC.end();it++) {
      if( (*it).second->steppingAction(theStep) ) {
	GsimDetector* det=(*it).second;
	int id=det->getDetectorID();
	m_doSteppingList.insert( std::make_pair(id,det) );
      }
    }
    m_isFirstStep=false;
  } else {
    G4Track* track = theStep->GetTrack();
    GsimTrackInformation* trackInformation
      = dynamic_cast<GsimTrackInformation*>(track->GetUserInformation());
    if(m_withTrackHistory && trackInformation) {
      int detID=trackInformation->getCurrentDetectorID();
      GsimDetector* det=0;
      det=m_doDefaultSteppingList[detID];
      // default stepping action for the detector at the postStep.
      if(det) det->defaultSteppingAction(theStep);
    } else {
      for(std::map<int,GsimDetector*>::iterator it=m_doDefaultSteppingList.begin();
	  it!=m_doDefaultSteppingList.end();it++) {
	(*it).second->defaultSteppingAction(theStep);
      }
    }
    
    for(std::map<int,GsimDetector*>::iterator it=m_doSteppingList.begin();
	it!=m_doSteppingList.end();it++) {
      (*it).second->steppingAction(theStep);
    }
  }

#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif

}

void GsimDetectorManager::preTrackingAction(const G4Track* aTrack)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(m_isFirstPreTrack) {
    m_doDefaultPreTrackingList.clear();
    m_doPreTrackingList.clear();
    for(GsimDetectorContainer::iterator it=m_DC.begin();
	it!=m_DC.end();it++) {
      if ( (*it).second->defaultPreTrackingAction(aTrack) ) {
	GsimDetector* det=(*it).second;
	int id=det->getDetectorID();
	m_doDefaultPreTrackingList.insert( std::make_pair(id,det) );
      }
    }
    for(GsimDetectorContainer::iterator it=m_DC.begin();
        it!=m_DC.end();it++) {
      if((*it).second->preTrackingAction(aTrack)) {
        m_doPreTrackingList.push_back((*it).second);
      }
    }
    G4UserTrackingAction* uta=G4EventManager::GetEventManager()->GetUserTrackingAction();
    GsimTrackingAction* ta=dynamic_cast<GsimTrackingAction*>(uta);
    m_withTrackHistory=ta->withTrackHistory();
    m_isFirstPreTrack=false;
  } else {
    GsimTrackInformation* trackInformation
      = dynamic_cast<GsimTrackInformation*>(aTrack->GetUserInformation());
    if(m_withTrackHistory && trackInformation) {
      int detID=trackInformation->getCurrentDetectorID();
      GsimDetector* det=0;
      det=m_doDefaultPreTrackingList[detID];
      if(det) det->defaultPreTrackingAction(aTrack);
    } else {
      for(std::map<int,GsimDetector*>::iterator it=m_doDefaultSteppingList.begin();
	  it!=m_doDefaultSteppingList.end();it++) {
	(*it).second->defaultPreTrackingAction(aTrack);
      }
    }
    for(std::list<GsimDetector*>::iterator it=m_doPreTrackingList.begin();
        it!=m_doPreTrackingList.end();it++) {
      (*it)->preTrackingAction(aTrack);
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif

}

void GsimDetectorManager::postTrackingAction(const G4Track* aTrack)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  if(m_isFirstPostTrack) {
    m_doDefaultPostTrackingList.clear();
    m_doPostTrackingList.clear();
    for(GsimDetectorContainer::iterator it=m_DC.begin();
        it!=m_DC.end();it++) {
      if((*it).second->defaultPostTrackingAction(aTrack)) {
        m_doDefaultPostTrackingList.push_back((*it).second);
      }
    }
    for(GsimDetectorContainer::iterator it=m_DC.begin();
        it!=m_DC.end();it++) {
      if((*it).second->postTrackingAction(aTrack)) {
        m_doPostTrackingList.push_back((*it).second);
      }
    }
    m_isFirstPostTrack=false;
  } else {
    for(std::list<GsimDetector*>::iterator it=m_doDefaultPostTrackingList.begin();
        it!=m_doDefaultPostTrackingList.end();it++) {
      (*it)->defaultPostTrackingAction(aTrack);
    }
    for(std::list<GsimDetector*>::iterator it=m_doPostTrackingList.begin();
        it!=m_doPostTrackingList.end();it++) {
      (*it)->postTrackingAction(aTrack);
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif

}


GsimDetector* GsimDetectorManager::findDetector(std::string fullName)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  

#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif

  if(fullName=="/") return 0;
  GsimDetectorContainer::iterator it=m_DC.find(fullName);
  if(it==m_DC.end()) {
    return 0;
  } else {
    return (*it).second;
  }
}



std::map<int,std::string> GsimDetectorManager::getDetectorIDFullName()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  std::map<int,std::string> detectorIDFullName;
  for(GsimDetectorContainer::iterator it=m_DC.begin();
      it!=m_DC.end();it++) {
    int id=(*it).second->getDetectorID();
    std::string fullName = (*it).first;
    detectorIDFullName.insert(std::make_pair(id,fullName));
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return detectorIDFullName;
}

std::map<int,int> GsimDetectorManager::getDetectorIDBriefID()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  std::map<int,int> detectorIDBriefID;
  for(GsimDetectorContainer::iterator it=m_DC.begin();
      it!=m_DC.end();it++) {
    int id       = (*it).second->getDetectorID();
    int  briefID = (*it).second->getBriefDetectorID();
    detectorIDBriefID.insert(std::make_pair(id,briefID));
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return detectorIDBriefID;
}


std::map<int,std::string> GsimDetectorManager::getDetectorBriefIDBriefName()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  std::map<int,std::string> detectorBriefIDBriefName;
  for(GsimDetectorContainer::iterator it=m_DC.begin();
      it!=m_DC.end();it++) {
    int         briefID   = (*it).second->getBriefDetectorID();
    std::string briefName = (*it).second->getBriefName();
    detectorBriefIDBriefName.insert(std::make_pair(briefID,briefName));
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return detectorBriefIDBriefName;
}


void GsimDetectorManager::fillPhysicalVolumeData()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  GsimPersistencyManager* persistencyManager =
    GsimPersistencyManager::getPersistencyManager();
  persistencyManager->setBranchOf("physicalVolumeTree",
				  "physicalVolume","GsimPhysicalVolumeData",&m_physicalVolumeData);
  
  std::map<G4VPhysicalVolume*,G4VPhysicalVolume*> pvr;
  GsimUtil::getUtil()->fillPhysicalVolumeRelationFromWorld(pvr);

  std::map<G4VPhysicalVolume*,GsimDetector*> pvd;
  assignDetector(pvd);
  for(std::map<G4VPhysicalVolume*,GsimDetector*>::iterator it=pvd.begin();
      it!=pvd.end();it++) {
    G4VPhysicalVolume* pv=(*it).first;
    GsimDetector* det = (*it).second;

    m_physicalVolumeData->pvName=(pv->GetName()).data();
    m_physicalVolumeData->pvCopyNo=pv->GetCopyNo();
    m_physicalVolumeData->detID=det->getDetectorID();
    m_physicalVolumeData->detFullName=det->getFullName();
    m_physicalVolumeData->detBriefName=det->getBriefName();
    

    m_physicalVolumeData->sdFlag=0;
    m_physicalVolumeData->sdName="";
    m_physicalVolumeData->sdID=-1;
    m_physicalVolumeData->sdNch=0;
    
    G4LogicalVolume* lv = pv->GetLogicalVolume();
    G4VSensitiveDetector* g4sd=lv->GetSensitiveDetector();
    if(g4sd) {
      GsimSensitiveDetector* sd=dynamic_cast<GsimSensitiveDetector*>(g4sd);
      std::list<int> chList=sd->getChannelID(pv,pvr);
      chList.sort();
      chList.unique();

      m_physicalVolumeData->sdFlag=1;
      m_physicalVolumeData->sdName=sd->getName();
      m_physicalVolumeData->sdID=sd->getSensitiveDetectorID();
      m_physicalVolumeData->sdNch=chList.size();

      int cnt=0;
      for(std::list<int>::iterator itch=chList.begin();
	  itch!=chList.end();itch++,cnt++) {
	int ch=(*itch);
	int cl=sd->getClusterID(ch);
	m_physicalVolumeData->sdChID[cnt]=ch;
	m_physicalVolumeData->sdClID[cnt]=cl;
      }
    }
    persistencyManager->fillTreeOf("physicalVolumeTree");
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}



void GsimDetectorManager::fillDetectorData()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  GsimPersistencyManager* persistencyManager =
    GsimPersistencyManager::getPersistencyManager();
  persistencyManager->setBranchOf("detectorTree",
				  "detector","GsimDetectorData",&m_detectorData);
  for(GsimDetectorContainer::iterator it=m_DC.begin();
      it!=m_DC.end();it++) {
    ((*it).second)->fillDetectorData(*m_detectorData);
    persistencyManager->fillTreeOf("detectorTree");
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimDetectorManager::
assignDetector(std::map<G4VPhysicalVolume*,GsimDetector*>& pvd)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  GsimUtil* util = GsimUtil::getUtil();
  /////////////////////////////////////////////////////////////////////
  std::map<std::string, GsimDetector*> pvNameDetectorMap;
  for(GsimDetectorContainer::iterator it=m_DC.begin();
      it!=m_DC.end();it++) {
    std::string   detName = (*it).first;
    GsimDetector* det     = (*it).second;
    G4VPhysicalVolume* pv = det->getPhysiDetector();
    if(pv) {
      std::string pvName=std::string( (pv->GetName()).data() );
      pvNameDetectorMap.insert( std::make_pair(pvName,det) );
    }
  }
  /////////////////////////////////////////////////////////////////////
  std::map<G4VPhysicalVolume*,G4VPhysicalVolume*> pvr;
  std::list<G4VPhysicalVolume*> pvend;
  {
    G4VPhysicalVolume* dummy=0;
    G4VPhysicalVolume* worldPV=util->getPhysiWorld();
    pvr.insert( std::make_pair(worldPV,dummy) );
    util->fillPhysicalVolumeRelation(worldPV,pvr,pvend);
  }
  /////////////////////////////////////////////////////////////////////
  std::list<G4VPhysicalVolume*> pvBuffer;
  for(std::list<G4VPhysicalVolume*>::iterator it=pvend.begin();
      it!=pvend.end();it++) {
    G4VPhysicalVolume* pv=(*it);
    scanParentsForDetectorAssign(pv,pvNameDetectorMap,pvr,
				 pvBuffer,pvd);
  }
  /////////////////////////////////////////////////////////////////////
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}



void GsimDetectorManager::
scanParentsForDetectorAssign(G4VPhysicalVolume* pv,
			     std::map<std::string, GsimDetector*>& pvNameDetectorMap,
			     std::map<G4VPhysicalVolume*,G4VPhysicalVolume*>& pvr,
			     std::list<G4VPhysicalVolume*>& pvBuffer,
			     std::map<G4VPhysicalVolume*,GsimDetector*>& pvd)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(pv==0) return;
  G4VPhysicalVolume* parentpv=0;
  pvBuffer.push_back(pv);
  std::string pvname=(pv->GetName()).data();
  std::map<std::string, GsimDetector*>::iterator itnd
    =pvNameDetectorMap.find( pvname );
  if(itnd!=pvNameDetectorMap.end()) {
    GsimDetector* det=(*itnd).second;  
    for(std::list<G4VPhysicalVolume*>::iterator itb=pvBuffer.begin();
	itb!=pvBuffer.end();itb++) {
      pvd.insert( std::make_pair(pv,det) );
    }
    pvBuffer.clear();
  }
  std::map<G4VPhysicalVolume*,G4VPhysicalVolume*>::iterator itm=pvr.find( pv );
  parentpv=(*itm).second;
  if(parentpv!=0) {
    std::map<G4VPhysicalVolume*,GsimDetector*>::iterator
      itcheck=pvd.find(parentpv);
    if(itcheck==pvd.end()) {
      scanParentsForDetectorAssign(parentpv,pvNameDetectorMap,
				   pvr,pvBuffer,pvd);
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetectorManager::dumpSD()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  for(std::list<GsimSensitiveDetector*>::iterator
	it=m_sensitiveDetectorList.begin();
      it!=m_sensitiveDetectorList.end();it++) {
    (*it)->dump(0);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimDetectorManager::dumpSDData()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  for(std::list<GsimSensitiveDetector*>::iterator
	it=m_sensitiveDetectorList.begin();
      it!=m_sensitiveDetectorList.end();it++) {
    (*it)->dump(1);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

