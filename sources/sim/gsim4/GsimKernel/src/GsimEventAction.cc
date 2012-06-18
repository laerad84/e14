/**
 *  $Id: GsimEventAction.cc,v 1.22 2007/02/04 12:55:41 nanjo Exp $
 *  $Log: GsimEventAction.cc,v $
 *  Revision 1.22  2007/02/04 12:55:41  nanjo
 *  Fast simulation 3 is added for shower check.
 *
 *  Revision 1.21  2007/01/12 15:24:23  nanjo
 *  Add flag to store empty data or not.
 *
 *  Revision 1.20  2006/12/09 21:34:09  nanjo
 *  briefHistory is corrected and dictionary write.
 *
 *  Revision 1.19  2006/12/09 00:45:06  nanjo
 *  dump.
 *
 *  Revision 1.18  2006/12/07 04:45:00  nanjo
 *  runTree is added and GsimRunData is filled.
 *
 *  Revision 1.17  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 *  Revision 1.16  2006/11/30 20:07:11  nanjo
 *  Data are re-structured.
 *
 *  Revision 1.15  2006/11/20 16:16:45  nanjo
 *  SensitiveDetectorList is kept in DetectorManager.
 *
 *  Revision 1.14  2006/10/19 03:28:44  nanjo
 *  GsimPersistencyManagerMessenger is replaced by GsimRunActionMessneger.
 *  Information of photonuclear interaction is not filled here.
 *  Cluster ID is filled.
 *  Now GsimPersistencyManager, GsimDigitizer, and, GsimMessage is
 *  independent of Geant4. They will be moved to different directory
 *  in order to use from ROOT analysis.
 *
 *  Revision 1.13  2006/09/29 08:21:56  nanjo
 *  Total number of event is automatically stored.
 *
 *  Revision 1.12  2006/08/24 17:39:00  nanjo
 *  Event processing status is printed in batch mode.
 *
 *  Revision 1.11  2006/08/01 15:29:46  nanjo
 *  DetectorIDHistory is modified.
 *
 *  Revision 1.10  2006/06/26 05:27:28  nanjo
 *  Update around storedTrackID and storedMotherTrackID.
 *
 *  Revision 1.9  2006/06/21 11:47:56  nanjo
 *  BriefTrajectory classes are deleted.
 *
 *  Revision 1.8  2006/06/05 02:19:56  nanjo
 *  The pause timing by accumulationCount is changed.
 *
 *  Revision 1.7  2006/05/24 08:55:59  nanjo
 *  Decay of custom KL particls is treated in HEPEvt-like method.
 *  Decay products of custom KL is assigned at BeginOfEventAction,
 *  which would be used at the KL decay. At the same time,
 *  the custom KL G4ParticleDefinition is swaped to G4KaonZeroLong.
 *  So the assignment of interactions to the custom KL is not needed.
 *  The custom KL particle is converted to a G4KaonZeroLong with
 *  the spedific preAssigned decay channel.
 *
 *  Revision 1.6  2006/03/22 05:29:58  nanjo
 *  GSIMDEBUG message is added to GsimEventAction.
 *
 *  Revision 1.5  2006/03/17 08:02:13  nanjo
 *  Add a flag to disable GsimBreifTrajectory. Make faster for the detector loop.
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
#include "GsimKernel/GsimEventAction.h"
#include "GsimKernel/GsimRunAction.h"
#include "GsimKernel/GsimEventActionMessenger.h"
#include "GsimKernel/GsimDetectorManager.h"
#include "GsimKernel/GsimTrackingAction.h"
#include "GsimPersistency/GsimPersistencyManager.h"
#include "GsimKernel/GsimSteppingAction.h"
#include "GsimKernel/GsimTrackInformation.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimData/GsimRunData.h"
#include "GsimData/GsimEventData.h"
#include "GsimData/GsimGenParticleData.h"
#include "GsimData/GsimTrackData.h"
#include "GsimParticle/GsimKLConstruction.h"
#include "G4UImanager.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4EventManager.hh"
#include "G4KaonZeroLong.hh"
#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"
#include "G4ParticleDefinition.hh"
#include "G4DecayTable.hh"
#include "G4VDecayChannel.hh"
#include "G4DecayProducts.hh"
#include "G4DynamicParticle.hh"
#include "G4Track.hh"
#include <vector>
#include <sstream>
#include <ctime>

#include "TClonesArray.h"


bool GsimEventAction::s_isEventAborted=false;

GsimEventAction::GsimEventAction(GsimDetectorManager* dm)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_DM=dm;
  m_runData   = new GsimRunData();
  m_eventData = new GsimEventData();
  m_genParticleData = new GsimGenParticleData();


  m_messenger = new GsimEventActionMessenger(this);
  m_visualizationMode=0;
  m_dumpMode=0;
  m_accumulationNumber=0;
  m_accumulationCount=0;
  m_totalNumberOfEvents=0;
  m_briefTrackCount=0;
  m_skipEmptyData=false;

  GsimPersistencyManager* persistencyManager =
    GsimPersistencyManager::getPersistencyManager();
  persistencyManager
    ->setBranchOf("runTree",
		  "run","GsimRunData",&m_runData);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


GsimEventAction::~GsimEventAction()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  delete m_runData;
  delete m_eventData;
  delete m_genParticleData;
  delete m_messenger;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimEventAction::BeginOfEventAction(const G4Event* evt)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  s_isEventAborted=false;
  int eventID=evt->GetEventID();
  GsimPersistencyManager* pm = GsimPersistencyManager::getPersistencyManager();
  if(eventID==0) {
    m_totalNumberOfEvents=
      G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEventToBeProcessed();
    const GsimRunAction* runAction=dynamic_cast<const GsimRunAction*>
      (G4RunManager::GetRunManager()->GetUserRunAction());
    int runNumber=runAction->getRunNumber();
    int runID=runAction->getRunID();
    
    std::string className = m_eventData->getClassName();
    pm->setEventBranch("Event.",className,&m_eventData);

    className = m_genParticleData->getClassName();
    pm->setEventBranch("GenParticle.",className,&m_genParticleData);

    m_runData->initializeDataValues();
    m_runData->runID=runID;
    m_runData->runNumber=runNumber;
    m_runData->nEventsRequested=m_totalNumberOfEvents;
    
    m_eventData->expMC=2;
    m_eventData->run_number=runNumber;

    GsimSteppingAction* steppingAction =
      dynamic_cast<GsimSteppingAction*>(fpEventManager->GetUserSteppingAction());
    if(steppingAction)
      steppingAction->setVisualizationMode(m_visualizationMode);
  }
  m_genParticleData->Clear("C");

  makeDecayInPrimaryVertex(evt);
  
  pm->beginOfEventAction();
  
  m_eventData->initializeDataValues();
  m_eventData->event_number = static_cast<unsigned int>(eventID);
  m_eventData->spill_number =0;
  m_eventData->trigger      =TRIG_ONSPILL;
  m_eventData->time_stamp   =std::time(0);
  m_eventData->status       = 0;
  
  if(m_DM) {
    m_DM->beginOfEventAction(evt);
  }

  if(m_accumulationNumber!=0 &&
     m_accumulationCount >= std::abs(m_accumulationNumber)) {
    G4UImanager* UI = G4UImanager::GetUIpointer();
    if(UI) {
      //UI->ApplyCommand("/vis/viewer/refresh");
      UI->ApplyCommand("/vis/viewer/rebuild");
    }
    m_accumulationCount=0;
    
  }
  m_briefTrackCount=0;

  G4UserTrackingAction* uta
    =G4EventManager::GetEventManager()->GetUserTrackingAction();
  GsimTrackingAction* gta=dynamic_cast<GsimTrackingAction*>(uta);
  if(gta) {
    gta->initializeTrigger();
  }
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimEventAction::EndOfEventAction(const G4Event* evt)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  bool withDataToStore=false;
  if(!m_skipEmptyData) {
    withDataToStore=true;
  } else {
    if(m_DM) {
      m_DM->endOfEventAction(evt);
      if(m_DM->withDataToStore()) withDataToStore=true;
    }
  }


  bool isGTATriggerActive=false;
  bool isGTATriggered=true;
  G4UserTrackingAction* uta
    =G4EventManager::GetEventManager()->GetUserTrackingAction();
  GsimTrackingAction* gta=dynamic_cast<GsimTrackingAction*>(uta);
  if(gta) {
    isGTATriggerActive=gta->isTriggerActive();
    isGTATriggered=gta->isTriggered();
  }

  if(isGTATriggerActive) {
    if(isGTATriggered) {
      withDataToStore=true;
    } else {
      withDataToStore=false;
    }
  }

  int eventID=evt->GetEventID();
  if(m_dumpMode==0) {
    //
  } else if(m_dumpMode==1) {
    if(eventID<=10) {
      m_genParticleData->dump();
      m_DM->dumpSD();
    }
  } else if(m_dumpMode>=2) {
    m_genParticleData->dump();
    if(m_dumpMode>=3) {
      m_DM->dumpSDData();
    }
    m_DM->dumpSD();
  }
  
  if(withDataToStore)
    m_runData->nEventsStored+=1;
  m_runData->nEventsProcessed+=1;

  
  GsimPersistencyManager::getPersistencyManager()
    ->endOfEventAction(eventID,withDataToStore);
  
  if(m_totalNumberOfEvents>0) {
    int unit=m_totalNumberOfEvents/10;
    if(unit==0) unit=1;

    if((eventID+1)%unit==0) {

      double frac=1.*(eventID+1)/m_totalNumberOfEvents*100.;
      std::ostringstream ostr;
      ostr << "### " << int(frac) << " % of events processed." ;
      GsimMessage::getInstance()->outputSystemInfo(ostr.str());
    }
  }
  
  
  if(m_accumulationNumber!=0) {
    m_accumulationCount++;
    if(m_accumulationCount >= std::abs(m_accumulationNumber)) {
      if(m_accumulationNumber<0) {
	G4cout << "pause return" << G4endl;
	std::getchar();
      }
    }
  }
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimEventAction::makeDecayInPrimaryVertex(const G4Event* anEvent)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  int nPV= anEvent->GetNumberOfPrimaryVertex();
  for(int i=0;i<nPV;i++) {
    G4PrimaryVertex* pv = anEvent->GetPrimaryVertex(i);
    int nParticle=pv->GetNumberOfParticle();
    for(int j=0;j<nParticle;j++) {
      G4PrimaryParticle*    particle    = pv->GetPrimary(j);
      G4ParticleDefinition* particleDef = particle->GetG4code();

      GsimKLConstruction* KL = GsimKLConstruction::getKLConstruction();
      if(!KL->isGsimKL(particleDef)) continue;
      
      //change GsimKL to G4K0Long
      particle->SetG4code(G4KaonZeroLong::Definition());
	
      if(particle->GetDaughter()) {
	//If it belongs to GsimKL and it already has a daughter,
	//then don't touch.
      } else {
	G4DecayTable*    decaytable = particleDef->GetDecayTable();
	G4VDecayChannel* decaychannel = decaytable->SelectADecayChannel();
	G4DecayProducts* products = decaychannel->DecayIt(particle->GetMass());

	G4ThreeVector ParentMome      = particle->GetMomentum();
	double        ParentMass      = particle->GetMass();
	double        ParentEnergy    = std::sqrt(ParentMome.mag2()+ParentMass*ParentMass);
	G4ThreeVector ParentDirection = ParentMome.unit(); 
	products->Boost( ParentEnergy, ParentDirection);
	
	int nProducts=products->entries();
	if(nProducts>0) {
	  std::vector<G4PrimaryParticle*> daughterList;
	  G4DynamicParticle* dynamicDaughter=0;
	  G4PrimaryParticle* primaryDaughter=0;
	  for(int k=0;k<nProducts;k++) {
	    dynamicDaughter = products->PopProducts();
	    int pdgcode        = dynamicDaughter->GetPDGcode();
	    G4ThreeVector mome = dynamicDaughter->GetMomentum();
	    double mass        = dynamicDaughter->GetMass();
	    primaryDaughter = new G4PrimaryParticle( pdgcode,mome.x(),mome.y(),mome.z() );
	    primaryDaughter->SetMass( mass );
	    daughterList.push_back(primaryDaughter);
	  }
	  
	  particle->SetDaughter( daughterList[0]);
	  for(int k=1;k<nProducts;k++) {
	    daughterList[k-1]->SetNext(daughterList[k]);
	  }
	}
	delete products;
      }
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimEventAction::storeBriefTrack(const G4Track* aTrack) {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  TClonesArray &ar = *(m_genParticleData->briefTracks);
  GsimTrackData* trackData = new (ar[m_briefTrackCount]) GsimTrackData();

  GsimTrackInformation* trackInfo
    = dynamic_cast<GsimTrackInformation*>(aTrack->GetUserInformation());

  trackData->track   = aTrack->GetTrackID();
  trackData->mother  = trackInfo->getStoredMotherTrackID();
  trackData->pid     = aTrack->GetDefinition()->GetPDGEncoding();

  G4ThreeVector tvec = trackInfo->getVertexMomentum();
  trackData->p.SetXYZ(tvec.x(),tvec.y(),tvec.z());
  trackData->ek      = aTrack->GetVertexKineticEnergy();
  trackData->mass    = aTrack->GetDefinition()->GetPDGMass();
  trackData->time    = trackInfo->getVertexTime();
  
  tvec = aTrack->GetVertexPosition();
  trackData->v.SetXYZ(tvec.x(),tvec.y(),tvec.z());


  tvec = aTrack->GetMomentum();
  trackData->end_p.SetXYZ(tvec.x(),tvec.y(),tvec.z());
  trackData->end_ek      = aTrack->GetKineticEnergy();
  trackData->end_time    = aTrack->GetGlobalTime();
  tvec = aTrack->GetPosition();
  trackData->end_v.SetXYZ(tvec.x(),tvec.y(),tvec.z());
  trackData->history=trackInfo->getBriefDetectorIDHistory();
  trackData->status  = trackInfo->getStatus();
  
  const G4VProcess* proc = aTrack->GetCreatorProcess();
  G4String procName="Primary";
  if(proc) 
    procName = proc->GetProcessName();

  GsimPersistencyManager* persistencyManager
    = GsimPersistencyManager::getPersistencyManager();
  trackData->mech = persistencyManager->getProcessIDByName(procName);
  trackData->thisID=m_briefTrackCount;
  
  m_briefTrackCount++;
  
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimEventAction::abortCurrentEvent()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4EventManager::GetEventManager()->AbortCurrentEvent();
  s_isEventAborted=true;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

bool GsimEventAction::isEventAborted()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return s_isEventAborted;
}
