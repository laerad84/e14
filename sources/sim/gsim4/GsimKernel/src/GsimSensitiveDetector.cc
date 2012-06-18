/**
 *  $Id: GsimSensitiveDetector.cc,v 1.20 2007/02/04 12:30:37 nanjo Exp $
 *  $Log: GsimSensitiveDetector.cc,v $
 *  Revision 1.20  2007/02/04 12:30:37  nanjo
 *  Online veto threshold is added.
 *
 *  Revision 1.19  2006/12/09 21:34:09  nanjo
 *  briefHistory is corrected and dictionary write.
 *
 *  Revision 1.18  2006/12/09 00:45:06  nanjo
 *  dump.
 *
 *  Revision 1.17  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 *  Revision 1.16  2006/12/04 17:27:49  nanjo
 *  Data are kept in each class, which are registered to persistencyManger.
 *  GsimPersistencyManger::setBranchOf is added then UserEventData is removed.
 *
 *  Revision 1.15  2006/12/02 07:06:11  nanjo
 *  sensitiveDetectorID, StopFlag, detID are updated.
 *
 *  Revision 1.14  2006/11/20 16:16:46  nanjo
 *  SensitiveDetectorList is kept in DetectorManager.
 *
 *  Revision 1.13  2006/11/16 13:13:00  nanjo
 *  Module id with detector depth..
 *
 *  Revision 1.12  2006/10/24 15:23:08  nanjo
 *  SensitiveDetector is re-structred.
 *
 *  Revision 1.11  2006/10/19 03:28:44  nanjo
 *  GsimPersistencyManagerMessenger is replaced by GsimRunActionMessneger.
 *  Information of photonuclear interaction is not filled here.
 *  Cluster ID is filled.
 *  Now GsimPersistencyManager, GsimDigitizer, and, GsimMessage is
 *  independent of Geant4. They will be moved to different directory
 *  in order to use from ROOT analysis.
 *
 *  Revision 1.10  2006/10/11 01:01:35  nanjo
 *  SensitiveDetector and HitConverter are restructured.
 *
 *  Revision 1.9  2006/08/11 06:23:30  nanjo
 *  Assign one GsimDetectorHitConverter per one GsimSensitiveDetector.
 *
 *  Revision 1.8  2006/08/11 06:13:58  nanjo
 *  SensitiveDetector is registered in SDManager.
 *
 *  Revision 1.7  2006/08/01 05:27:55  nanjo
 *  GsimSpectrum is added. Debug print is updated. With/without Digi is implemented.
 *
 *  Revision 1.6  2006/06/14 05:54:22  nanjo
 *  GsimDigitizer is added.
 *
 *  Revision 1.5  2006/04/12 12:07:17  nanjo
 *  Fix typo.
 *
 *  Revision 1.4  2006/04/12 08:18:20  nanjo
 *  namespace of CLHEP is resolved.
 *
 *  Revision 1.3  2006/03/01 12:45:32  nanjo
 *  A member function of GsimDetector, cloneDetector, is added and used in E391Detector.
 *
 *  Revision 1.2  2006/02/21 09:09:59  nanjo
 *  Sensitive detector name and channel id can be assigned. If the same sensitive detector name is used for some detectors, these detectors are recognized as channels in one detector.
 *
 *  Revision 1.1  2006/01/26 04:53:30  nanjo
 *  Detector and persistency classes are added.
 *
 */
#include "GsimKernel/GsimSensitiveDetector.h"
#include "GsimKernel/GsimSensitiveDetectorMessenger.h"
#include "GsimKernel/GsimDetectorHitConverter.h"
#include "GsimKernel/GsimDigitizer.h"
#include "GsimKernel/GsimDetector.h"
#include "GsimPersistency/GsimPersistencyManager.h"
#include "GsimKernel/GsimTrackInformation.h"
#include "GsimKernel/GsimEventAction.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimData/GsimDetectorEventData.h"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4OpticalPhoton.hh"
#include "G4Geantino.hh"
#include "G4VPhysicalVolume.hh"

#include "CLHEP/Random/Randomize.h"
#include <iostream>

GsimSensitiveDetector::GsimSensitiveDetector(G4String name)
  :G4VSensitiveDetector(name)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_name=name;
  m_sensitiveDetectorID=-1;
  m_storeHit=false;
  m_storeDigi=false;
  m_sensitiveMode=energyDepositSensitiveMode;
  
  m_detectorEventData = new GsimDetectorEventData();
  m_hitConverter = new GsimDetectorHitConverter(name);

  m_messenger = new GsimSensitiveDetectorMessenger(this);

  m_fastSimulationLevel=0;
  m_onlineVetoThreshold=1e6;//[MeV]=1TeV
  m_hitProcessDetector=0;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimSensitiveDetector::~GsimSensitiveDetector(){
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  delete m_detectorEventData;
  for(std::list<GsimDigitizer*>::iterator it=m_digitizerList.begin();
      it!=m_digitizerList.end();it++) {
    delete (*it);
  }
  m_digitizerList.clear();
  delete m_hitConverter;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimSensitiveDetector::Initialize(G4HCofThisEvent*)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  int eventID=G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  if(eventID==0) {
    makeBranch();
  }
  initializeDataValues();
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimSensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  digitize();
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimSensitiveDetector::clear()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

G4bool GsimSensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  processHitsDetector(aStep, ROhist);
  
  G4Track*              track    = aStep->GetTrack();
  G4ParticleDefinition* particle = track->GetDefinition();
  double                charge   = particle->GetPDGCharge();
  double                edep     = aStep->GetTotalEnergyDeposit();


  if(particle==G4Geantino::Definition()) {
    process(aStep,ROhist);
    return true;
  }
  
  if(m_sensitiveMode==chargedParticleSensitiveMode) {
    if(charge!=0) {
      process(aStep,ROhist);
      return true;
    } else return false;
  } else if(m_sensitiveMode==energyDepositSensitiveMode) {
    if(edep>0){
      process(aStep,ROhist);
      return true;
    } else return false;
  } else if(m_sensitiveMode==opticalPhotonSensitiveMode) {
    if(particle==G4OpticalPhoton::OpticalPhotonDefinition()) {
      if(isOpticalPhotonHit(track->GetKineticEnergy())) {
	aStep->SetTotalEnergyDeposit(1.*MeV);
	process(aStep,ROhist);
	track->SetTrackStatus(fStopAndKill);
	return true;
      } else return false;
    }
  } else if(m_sensitiveMode==opticalPhotonSensitiveFastMode) {
    if(particle==G4OpticalPhoton::OpticalPhotonDefinition()) {
      process(aStep,ROhist);
      track->SetTrackStatus(fStopAndKill);
      return true;
    }
  } else if(m_sensitiveMode==anyParticleSensitiveMode) {
    return true;
  } else {
    
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return false;
}

bool GsimSensitiveDetector::isOpticalPhotonHit(double opticalPhotonEnergy)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  double effi=getOpticalPhotonEfficiency(opticalPhotonEnergy);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  if(CLHEP::RandFlat::shoot()<effi) return true;
  else                       return false; 
}

double GsimSensitiveDetector::getOpticalPhotonEfficiency(double opticalPhotonEnergy)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(m_opticalPhotonWaveLength.size()<2) return 0;
  
  double hbarc=197.326968;//[eV nm]
  double waveLength = 2*M_PI*hbarc/(opticalPhotonEnergy/eV);

  std::vector<double>::iterator itFast = m_opticalPhotonWaveLength.begin();
  std::vector<double>::iterator itLast = m_opticalPhotonWaveLength.end();
  itLast--;

  double minWL=(*itFast);
  double maxWL=(*itLast);
  if((*itLast)<(*itFast)) {
    maxWL=(*itFast);
    minWL=(*itLast);
  }

  if(waveLength<minWL || waveLength>maxWL) return 0;


  std::vector<double>::iterator itW1=m_opticalPhotonWaveLength.begin();
  std::vector<double>::iterator itW2=m_opticalPhotonWaveLength.begin();
  itW2++;
  std::vector<double>::iterator itE1=m_opticalPhotonEfficiency.begin();
  std::vector<double>::iterator itE2=m_opticalPhotonEfficiency.begin();
  itE2++;

  
  for(;itW2!=m_opticalPhotonWaveLength.end();itW1++,itW2++,itE1++,itE2++) {
    if( ( waveLength-(*itW1) ) * ( waveLength-(*itW2) ) < 0) {
      
      double l1=std::abs( waveLength-(*itW1) );
      double l2=std::abs( waveLength-(*itW2) );
      double e1=(*itE1);
      double e2=(*itE2);

      return (l2*e1+l1*e2)/(l1+l2);
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return 0.;
}

void GsimSensitiveDetector::makeBranch()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  std::string className = m_detectorEventData->getClassName();
  std::string tit;
  tit+=m_name;
  tit+=".";
  GsimPersistencyManager::getPersistencyManager()
    ->setEventBranch(tit,className,&m_detectorEventData);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}
void GsimSensitiveDetector::initializeDataValues()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_detectorEventData->initializeDataValues();
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimSensitiveDetector::addDigitizer(GsimDigitizer* digi)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_digitizerList.push_back(digi);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimSensitiveDetector::process(const G4Step* aStep,G4TouchableHistory* ROhist)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  bool doProcess=true;

  G4Track* track=aStep->GetTrack();
  int status=track->GetTrackStatus();
  GsimTrackInformation* trackInfo
    = dynamic_cast<GsimTrackInformation*>(track->GetUserInformation());
  trackInfo->setStopStatus(status+10*m_fastSimulationLevel);
  
  if( (!m_storeDigi) && (!m_storeHit) ) {
    doProcess=false;
  }
  m_hitConverter->convertHit(m_detectorEventData,aStep,ROhist,doProcess);

  if(m_detectorEventData->totalEnergy>m_onlineVetoThreshold) {
    GsimEventAction::abortCurrentEvent();
  }
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimSensitiveDetector::digitize()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if( (!m_storeDigi) && (!m_storeHit) ) return;

  sortHitData();
  
  if(m_storeDigi) {
    for(std::list<GsimDigitizer*>::iterator it=m_digitizerList.begin();
	it!=m_digitizerList.end();it++) {
      (*it)->digitize(m_detectorEventData);
    }
  }
  
  if(!m_storeHit) {
    clearHitData();
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimSensitiveDetector::sortHitData()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  TClonesArray &arHits = *(m_detectorEventData->hits);
  arHits.Sort();
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimSensitiveDetector::clearHitData()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_detectorEventData->clearHitData();
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimSensitiveDetector::setThisCopyNoFactor(int thisCopyNoFactor)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_hitConverter->setThisCopyNoFactor(thisCopyNoFactor);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimSensitiveDetector::setDeepCopyNoFactor(int deepCopyNoFactor)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_hitConverter->setDeepCopyNoFactor(deepCopyNoFactor);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}



void GsimSensitiveDetector::setClusterID(int channelID,int clusterID)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  for(std::list<GsimDigitizer*>::iterator it=m_digitizerList.begin();
      it!=m_digitizerList.end();it++) {
    (*it)->setClusterID(channelID,clusterID);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

int GsimSensitiveDetector::getClusterID(int channelID)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  int clid=-1;
  if(m_digitizerList.size()!=0) {
    std::list<GsimDigitizer*>::iterator it=m_digitizerList.begin();
    clid=(*it)->getClusterID(channelID);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return clid;
}



std::list<int> GsimSensitiveDetector::GsimSensitiveDetector::getChannelID(G4VPhysicalVolume* pv,
							       std::map<G4VPhysicalVolume*,G4VPhysicalVolume*>& pvr) {
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return m_hitConverter->getChannelID(pv,pvr);
}

bool GsimSensitiveDetector::withDataToStore()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  
  if(m_detectorEventData) {
    if(m_storeDigi &&
       m_detectorEventData->nDigi>0) return true;
    if(m_storeHit &&
       m_detectorEventData->nHit>0)  return true;
  }
  return false;
}


void GsimSensitiveDetector::setSensitiveDetectorID(int id)
{
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_sensitiveDetectorID=id;
  m_hitConverter->setSensitiveDetectorID(id);
  for(std::list<GsimDigitizer*>::iterator it=m_digitizerList.begin();
      it!=m_digitizerList.end();it++) {
    (*it)->setSensitiveDetectorID(id);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

double GsimSensitiveDetector::getTotalEnergy()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  double totE=0;
  if(m_detectorEventData) {
    totE=m_detectorEventData->totalEnergy;
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return totE;
}

void GsimSensitiveDetector::dump(int imode=0)
{
  std::cout << m_name  << "\t"
	    << m_sensitiveDetectorID << "\t"
	    << getTotalEnergy()
	    << std::endl;
  if(imode!=0) {
    m_detectorEventData->dumpDigi();
  }
}


void GsimSensitiveDetector::
processHitsDetector(G4Step* aStep, G4TouchableHistory* ROhist) {
  if(m_hitProcessDetector)
    m_hitProcessDetector->processHits(aStep, ROhist);
}


void GsimSensitiveDetector::setTdcThreshold(double eth) {
  if(m_digitizerList.size()>0) {
    std::list<GsimDigitizer*>::iterator it
      =m_digitizerList.begin();
    (*it)->setTdcThresholdEnergy(eth);
  }
}
