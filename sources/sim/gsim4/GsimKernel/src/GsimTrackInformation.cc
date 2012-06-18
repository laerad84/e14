/**
 *  $Id: GsimTrackInformation.cc,v 1.15 2007/02/04 12:28:56 nanjo Exp $
 *  $Log: GsimTrackInformation.cc,v $
 *  Revision 1.15  2007/02/04 12:28:56  nanjo
 *  Shower flag is added.
 *
 *  Revision 1.14  2007/01/11 06:47:31  nanjo
 *  current/previous detectorID are kept.
 *
 *  Revision 1.13  2006/12/09 21:34:09  nanjo
 *  briefHistory is corrected and dictionary write.
 *
 *  Revision 1.12  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 */
#include "GsimKernel/GsimTrackInformation.h"
#include "GsimPersistency/GsimPersistencyManager.h"
#include "GsimPersistency/GsimMessage.h"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4VProcess.hh"

GsimTrackInformation::GsimTrackInformation()
  : G4VUserTrackInformation()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_vertexTime=-999;
  m_vertexMomentum=G4ThreeVector(-999,-999,-999);
  m_status=0;
  m_storedTrackID=-1;
  m_storedMotherTrackID=-1;

  m_currentDetectorID=-1;
  m_currentBriefDetectorID=-1;
  m_previousDetectorID=-1;
  m_previousBriefDetectorID=-1;
  
  m_briefDetectorIDHistory=0xffffffffffffffffULL;
  m_detectorHitList.clear();
  m_storeFlag=false;
  m_isHistoryBufferFull=false;
  m_stopStatus=0;
  m_showerFlag=0;
  m_persistencyManager
    =GsimPersistencyManager::getPersistencyManager();
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimTrackInformation::~GsimTrackInformation()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimTrackInformation::Print() const
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimTrackInformation::processTrackIDinHitData()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  for(std::list<GsimDetectorHitData*>::iterator it=m_detectorHitList.begin();
      it!=m_detectorHitList.end();it++) {
    (*it)->track=m_storedTrackID;
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
	
}

void GsimTrackInformation::processStepHistory(const G4Step* aStep)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4Track* track = aStep->GetTrack();
  processTrackHistory(track);
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimTrackInformation::processTrackHistory(const G4Track* aTrack)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_previousDetectorID=m_currentDetectorID;
  m_previousBriefDetectorID=m_currentBriefDetectorID;

  std::string volumeName = "";
  
  const G4Step* aStep=aTrack->GetStep();
  if(!aStep) {
    volumeName = std::string( (aTrack->GetVolume()->GetName()).data() );
  } else {
    G4VPhysicalVolume* pv=aStep->GetPostStepPoint()->GetPhysicalVolume();
    if(pv) { 
      volumeName = std::string( (pv->GetName()).data() );
    } else {
      //Reach OutOfWorld
      m_currentDetectorID=-1;
      m_currentBriefDetectorID=-1;
      return;
    }
  }

  m_currentDetectorID
    =m_persistencyManager->getDetectorIDByPhysicalVolumeName(volumeName);
  m_currentBriefDetectorID
    = m_persistencyManager->getDetectorBriefIDByID(m_currentDetectorID);

  if(m_isHistoryBufferFull) return;
  
  if( ! (m_currentBriefDetectorID>=0 && m_currentBriefDetectorID<=31) ) return;//out of range
  
  if(m_previousBriefDetectorID==m_currentBriefDetectorID) return;

  //64bit=5bit x 12 +4bit
  
  unsigned long long tail=0xf;
  unsigned long long headclear=0xffffffffffffffffULL;
  headclear=headclear>>5;
  
  unsigned long long itmp=m_briefDetectorIDHistory;
  if( ((m_briefDetectorIDHistory>>4) & tail)!=tail ) {
    m_isHistoryBufferFull=true;
  }
  if(m_isHistoryBufferFull) return; //buffer is full

  unsigned long long btmp=m_currentBriefDetectorID;
  m_briefDetectorIDHistory=((itmp>>5)&headclear)|(btmp<<(64-5));

#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimTrackInformation::processShowerFlag(const G4Track* aTrack)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  
  if(m_showerFlag==0) {
    const G4VProcess* thisProc=aTrack->GetCreatorProcess();
    if(thisProc) {
      G4String procName = thisProc->GetProcessName();
      if(procName=="conv" ||
	 procName=="eBrem" ||
	 procName=="annihil")  {
	m_showerFlag=1;
      }
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


