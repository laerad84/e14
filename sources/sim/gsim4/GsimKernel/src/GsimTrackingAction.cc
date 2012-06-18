/**
 *  @file
 *  @brief  GsimBriefTrajectory
 *  $Id: GsimTrackingAction.cc,v 1.14 2007/02/04 12:27:44 nanjo Exp $
 *  $Log: GsimTrackingAction.cc,v $
 *  Revision 1.14  2007/02/04 12:27:44  nanjo
 *  Track history control. 2ndaries info. is add. annihil is added for shower decision.
 *
 *  Revision 1.13  2007/01/11 06:48:47  nanjo
 *  Pre/Post actions are not performed for suspended tracks.
 *
 *  Revision 1.12  2006/12/09 21:34:09  nanjo
 *  briefHistory is corrected and dictionary write.
 *
 *  Revision 1.11  2006/12/09 00:45:06  nanjo
 *  dump.
 *
 *  Revision 1.10  2006/11/30 20:07:11  nanjo
 *  Data are re-structured.
 *
 *  Revision 1.9  2006/08/01 05:27:55  nanjo
 *  GsimSpectrum is added. Debug print is updated. With/without Digi is implemented.
 *
 *  Revision 1.8  2006/06/26 05:27:28  nanjo
 *  Update around storedTrackID and storedMotherTrackID.
 *
 *  Revision 1.7  2006/06/22 11:38:57  nanjo
 *  Modifications around briefDetectorID and briefDetectorName.
 *
 *  Revision 1.6  2006/06/21 11:47:56  nanjo
 *  BriefTrajectory classes are deleted.
 *
 *  Revision 1.5  2006/03/17 08:02:13  nanjo
 *  Add a flag to disable GsimBreifTrajectory. Make faster for the detector loop.
 *
 *  Revision 1.4  2006/03/17 02:42:28  nanjo
 *  GsimVacuum is changed to GsimLowVacuum for some E391 detectors.
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
#include "GsimKernel/GsimTrackingAction.h"
#include "GsimKernel/GsimTrackInformation.h"
#include "GsimKernel/GsimDetectorManager.h"
#include "GsimKernel/GsimEventAction.h"
#include "GsimKernel/GsimTrackingActionMessenger.h"
#include "GsimPersistency/GsimMessage.h"


#include "G4Track.hh"
#include "G4TrackingManager.hh"
#include "G4EventManager.hh"
#include "G4ThreeVector.hh"

#include <iostream>
#include <iomanip>

GsimTrackingAction::GsimTrackingAction(GsimDetectorManager* dm)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_messenger = new GsimTrackingActionMessenger(this);
  m_DM=dm;
  m_isBriefTrackStore=true;
  m_isForceStorePrimary=true;
  m_withTrackHistory=true;
  m_isTrackDump=false;
  m_isTriggered=true;
  m_storeAllTracks=false;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimTrackingAction::~GsimTrackingAction()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  delete m_messenger;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimTrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif


  if(aTrack->GetTrackStatus()==fSuspend) return;
  
  if(!aTrack->GetUserInformation())
    const_cast<G4Track*>(aTrack)
      ->SetUserInformation(new GsimTrackInformation());
  GsimTrackInformation* thisTrackInfo
    = dynamic_cast<GsimTrackInformation*>(aTrack->GetUserInformation());
  thisTrackInfo->clearDetectorHitList();
  thisTrackInfo->setVertexTime(aTrack->GetGlobalTime());
  thisTrackInfo->setVertexMomentum(aTrack->GetMomentum());
  if(m_withTrackHistory)
    thisTrackInfo->processTrackHistory( aTrack );
  thisTrackInfo->processShowerFlag( aTrack );

  if(thisTrackInfo->getShowerFlag()==1) {
    const_cast<G4Track*>(aTrack)->SetTrackStatus(fSuspend);
  }

  int pdg=aTrack->GetDefinition()->GetPDGEncoding();
  for(std::list<int>::iterator itp=m_pidToKill.begin();
      itp!=m_pidToKill.end();itp++) {
    if((*itp)==pdg) {
      const_cast<G4Track*>(aTrack)->SetTrackStatus(fStopAndKill);
    }
  }
  
  m_DM->preTrackingAction(aTrack);

  if(m_isTrackDump) dumpPreTrack(aTrack);
    
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimTrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  if(aTrack->GetTrackStatus()==fSuspend) return;
  
  GsimTrackInformation* thisTrackInfo
    = dynamic_cast<GsimTrackInformation*>(aTrack->GetUserInformation());


  if(m_storeAllTracks) {
    thisTrackInfo->setStoreFlag();
    thisTrackInfo->setStoredTrackID( aTrack->GetTrackID() );
  }


  const G4VProcess* thisProc=aTrack->GetCreatorProcess();
  if(!thisProc) {
    //primary
    thisTrackInfo->setStoreFlag();
    thisTrackInfo->setStoredTrackID( aTrack->GetTrackID() );
  } else {
    G4String procName = thisProc->GetProcessName();
    if(procName=="Decay")  {
      //decayed track
      thisTrackInfo->setStoreFlag();
      thisTrackInfo->setStoredTrackID( aTrack->GetTrackID() );
    }
  }

  int pdg=aTrack->GetDefinition()->GetPDGEncoding();
  for(std::list<int>::iterator itp=m_pidToMonitor.begin();
      itp!=m_pidToMonitor.end();itp++) {
    if((*itp)==pdg) {
      thisTrackInfo->setStoreFlag();
      thisTrackInfo->setStoredTrackID( aTrack->GetTrackID() );
    }
  }

  for(std::list<int>::iterator itp=m_pidToTrigger.begin();
      itp!=m_pidToTrigger.end();itp++) {
    if((*itp)==pdg) {
      m_isTriggered=true;
    }
  }
  

  G4TrackVector * secondaries = fpTrackingManager->GimmeSecondaries();
  for(G4TrackVector::iterator it=secondaries->begin();
      it!=secondaries->end();it++) {
    
    GsimTrackInformation* daughterTrackInfo = new GsimTrackInformation();
    (*it)->SetUserInformation( daughterTrackInfo );
    daughterTrackInfo->setInitialPositionID(
					    thisTrackInfo->getCurrentDetectorID(),
					    thisTrackInfo->getCurrentBriefDetectorID());

    const G4VProcess* proc=(*it)->GetCreatorProcess();
    if(proc) {
      G4String procName=proc->GetProcessName();
      if(procName=="Decay") {
	//haveDecayProducts
	thisTrackInfo->setStoreFlag();
	thisTrackInfo->setStoredTrackID( aTrack->GetTrackID() );
	thisTrackInfo->setStatus(1);
      }

      if(procName=="conv" ||
	 procName=="eBrem" ||
	 procName=="annihil") {
	if(daughterTrackInfo->getShowerFlag()==0) {
	  daughterTrackInfo->setShowerFlag(1);
	}
      }
    }

    int pdg=(*it)->GetDefinition()->GetPDGEncoding();
    for(std::list<int>::iterator itp=m_pidToMonitor.begin();
	itp!=m_pidToMonitor.end();itp++) {
      if((*itp)==pdg) {
	thisTrackInfo->setStoreFlag();
	thisTrackInfo->setStoredTrackID( aTrack->GetTrackID() );
      }
    }
	
    
    
    int storedTrackID=thisTrackInfo->getStoredTrackID();
    daughterTrackInfo->setStoredTrackID( storedTrackID );
    
    int storedMotherTrackID=-1;
    if( thisTrackInfo->getStoreFlag() ) {
      storedMotherTrackID=aTrack->GetTrackID();
    } else {
      storedMotherTrackID=thisTrackInfo->getStoredMotherTrackID();
      unsigned long long his=thisTrackInfo->getBriefDetectorIDHistory();
      daughterTrackInfo->setBriefDetectorIDHistory( his );
    }
    daughterTrackInfo->setStoredMotherTrackID( storedMotherTrackID );
  }

  thisTrackInfo->processTrackIDinHitData();
  

  m_DM->postTrackingAction(aTrack);

  if( (!thisProc) && m_isForceStorePrimary) {
    //primary and ForceStorePrimary
  } else {
    if( ! m_isBriefTrackStore) return;
  }
  

  if( thisTrackInfo->getStoreFlag() ) {
    dynamic_cast<GsimEventAction*>
      (G4EventManager::GetEventManager()->GetUserEventAction())
      ->storeBriefTrack(aTrack);
  }
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimTrackingAction::dumpPreTrack(const G4Track* aTrack)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  G4cout << " track dump ";
  if(aTrack->GetDefinition()) {
    G4cout << std::setw(10) << aTrack->GetDefinition()->GetParticleName() << "\t";
  }
  G4cout << std::setw(5) << aTrack->GetTrackID() << "\t";
  G4cout << std::setw(5) << aTrack->GetParentID() << "\t";
  if(aTrack->GetCreatorProcess()) {
    G4cout << std::setw(30) << setiosflags(std::ios::left)
	   << aTrack->GetCreatorProcess()->GetProcessName() << "\t";
  } else {
    G4cout << std::setw(30) << setiosflags(std::ios::left)
	   << "Primary" << "\t";
  }
  G4ThreeVector v=aTrack->GetPosition();
  G4cout << std::setw(8) << std::setprecision(2) << v.x() << "\t";
  G4cout << std::setw(8) << std::setprecision(2) << v.y() << "\t";
  G4cout << std::setw(8) << std::setprecision(2) << v.z() << "\t";
  G4cout << std::setw(8) << std::setprecision(2) << aTrack->GetGlobalTime() << G4endl;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

