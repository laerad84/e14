/**
 *  $Id: GsimStackingAction.cc,v 1.1 2007/02/04 12:14:38 nanjo Exp $
 *  $Log: GsimStackingAction.cc,v $
 *  Revision 1.1  2007/02/04 12:14:38  nanjo
 *  GsimStackingAction is added.
 *
 */
#include "GsimKernel/GsimStackingAction.h"
#include "GsimKernel/GsimStackingActionMessenger.h"
#include "GsimKernel/GsimTrackInformation.h"
#include "GsimKernel/GsimEventAction.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4EventManager.hh"
#include "G4TrackingManager.hh"
#include "G4ParticleDefinition.hh"

#include <algorithm>

GsimStackingAction::GsimStackingAction()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_messenger = new GsimStackingActionMessenger(this);
  m_stage=0;

  m_withPrimaryEndTrigger=false;
  m_triggerPrimaryEndZ1=-999;
  m_triggerPrimaryEndZ2=-999;
  m_priorBriefID=-999;
  m_priorityRest=false;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimStackingAction::~GsimStackingAction()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimStackingAction::PrepareNewEvent()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_stage=0;

  if(m_priorityRest) {
    m_briefIDPriorityList.clear();
    GsimPersistencyManager* pm=GsimPersistencyManager::getPersistencyManager();
    for(std::list<std::string>::iterator it=m_briefNamePriorityList.begin();
	it!=m_briefNamePriorityList.end();it++) {
      int id=pm->getDetectorBriefIDByBriefName((*it));
      if(id!=-1) m_briefIDPriorityList.push_back(id);
    }
    m_priorityRest=false;
  }
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

G4ClassificationOfNewTrack GsimStackingAction::ClassifyNewTrack(const G4Track* aTrack)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  G4TrackStatus trackStatus = aTrack->GetTrackStatus();

  int showerFlag=0;
  GsimTrackInformation* trackInformation
    = dynamic_cast<GsimTrackInformation*>(aTrack->GetUserInformation());
  if(trackInformation) {
    showerFlag=trackInformation->getShowerFlag();
  }
  
  G4ClassificationOfNewTrack classification = fWaiting;
  
  switch(m_stage)
    {
    case 0:
      // Stage 0 : non-suspended Primary only
      if(aTrack->GetParentID()==0) {
	classification = fUrgent;
      }
      break;

    case 1:
      // Stage 1 : non-suspended tracks
      if(showerFlag==0 && trackStatus!=fSuspend) {
	classification = fUrgent;
      } 
      break;
    case 2:
      // Stage 2 : Suspended tracks
      if(showerFlag==0) {
	if(trackStatus==fSuspend) {
	  classification = fUrgent;
	} else {
	  m_stage=1;
	  stackManager->ReClassify();
	  classification = fUrgent;
	}
      }
      break;
    case 3:
      if(m_priorBriefID!=-999) {
	int id=trackInformation->getCurrentBriefDetectorID();
	if(id==m_priorBriefID) {
	  if(showerFlag==1) {
	    trackInformation->setShowerFlag(2);
	  }
	  classification = fUrgent;
	} else {
	  std::list<int>::iterator it
	    =std::find(m_briefIDPriorityList.begin(),
		       m_briefIDPriorityIterator,id);
	  if(it!=m_briefIDPriorityIterator) {
	    if(showerFlag==1) {
	      trackInformation->setShowerFlag(2);
	    }
	    classification = fUrgent;
	  }
	}
      }
      break;
    default:
      // Stage 4 : Accept all primaries
      //           Accept all secondaries in RoI
      //           Kill secondaries outside RoI
      if(showerFlag==1) {
	trackInformation->setShowerFlag(2);
      }
      classification = fUrgent;
      break;
    }
  return classification;

  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimStackingAction::NewStage()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  
  
  m_stage++;
  if(m_stage==1) {
    //stage : 0->1
    if(m_withPrimaryEndTrigger) {
      G4EventManager* fEventManager=G4EventManager::GetEventManager();
      G4TrackingManager* fTrackingManager=fEventManager->GetTrackingManager();
      if(fTrackingManager) {
	G4Track* processedTrack=fTrackingManager->GetTrack();
	if(processedTrack) {
	  //last processed primary
	  G4ThreeVector r=processedTrack->GetPosition();
	  double endZ=r.z();
	  if(endZ>=m_triggerPrimaryEndZ1 && endZ<=m_triggerPrimaryEndZ2) {
	    //trigger
	  } else {
	    //discard
	    GsimEventAction::abortCurrentEvent();
	  }
	}
      }
    }
  }
  if(m_stage==3) {
    if(m_briefIDPriorityList.size()>0) {
      m_briefIDPriorityIterator=m_briefIDPriorityList.begin();
      m_priorBriefID=*(m_briefIDPriorityIterator);
    } else {
      m_briefIDPriorityIterator=m_briefIDPriorityList.end();
      m_priorBriefID=-999;
    }
  }
  
  if(m_stage==4) {
    m_briefIDPriorityIterator++;
    if(m_briefIDPriorityIterator!=m_briefIDPriorityList.end()) {
      m_priorBriefID=*(m_briefIDPriorityIterator);
      m_stage=3;
    } else {
      m_priorBriefID=-999;
    }
  }

  stackManager->ReClassify();
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimStackingAction::triggerPrimaryEndZ(double z1,double z2)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_triggerPrimaryEndZ1=z1;
  m_triggerPrimaryEndZ2=z2;
  if(z1==z2) m_withPrimaryEndTrigger=false;
  else       m_withPrimaryEndTrigger=true;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}
