/**
 *  $Id: GsimRunAction.cc,v 1.31 2006/12/07 08:50:16 nanjo Exp $
 *  $Log: GsimRunAction.cc,v $
 *  Revision 1.31  2006/12/07 08:50:16  nanjo
 *  Midas interfaces for GsimGenParticleData and GsimDetectorEventData are added.
 *
 *  Revision 1.30  2006/12/07 04:45:00  nanjo
 *  runTree is added and GsimRunData is filled.
 *
 *  Revision 1.29  2006/12/04 20:20:40  nanjo
 *  runNumber is given at PersistencyManager::preBeginOfRun.
 *
 *  Revision 1.28  2006/12/04 17:27:49  nanjo
 *  Data are kept in each class, which are registered to persistencyManger.
 *  GsimPersistencyManger::setBranchOf is added then UserEventData is removed.
 *
 *  Revision 1.27  2006/11/30 20:07:11  nanjo
 *  Data are re-structured.
 *
 *  Revision 1.26  2006/11/20 16:16:45  nanjo
 *  SensitiveDetectorList is kept in DetectorManager.
 *
 *  Revision 1.25  2006/11/17 12:09:41  nanjo
 *  RunIDBase is added.
 *
 *  Revision 1.24  2006/10/24 15:23:08  nanjo
 *  SensitiveDetector is re-structred.
 *
 *  Revision 1.23  2006/10/16 01:54:22  nanjo
 *  CLHEP functions are removed from GsimPersistencyManager.
 *
 *  Revision 1.22  2006/09/29 08:21:56  nanjo
 *  Total number of event is automatically stored.
 *
 *  Revision 1.21  2006/09/29 05:15:52  nanjo
 *  The memory usage at the end of run is printed.
 *
 *  Revision 1.20  2006/09/10 22:11:50  nanjo
 *  PhotoNuclear counter is re-added.
 *
 *  Revision 1.19  2006/09/06 22:33:18  nanjo
 *  GsimDetectorData is added.
 *
 *  Revision 1.18  2006/08/01 05:27:55  nanjo
 *  GsimSpectrum is added. Debug print is updated. With/without Digi is implemented.
 *
 *  Revision 1.17  2006/06/22 11:38:57  nanjo
 *  Modifications around briefDetectorID and briefDetectorName.
 *
 *  Revision 1.16  2006/05/31 19:42:24  nanjo
 *  GsimDetector::getWorldDetector is added and magnetic field is implemented.
 *
 *  Revision 1.15  2006/05/30 07:50:51  nanjo
 *  New debug message with __PRETTY_FUNCTION__ is experimentally added.
 *
 *  Revision 1.14  2006/05/25 13:00:12  nanjo
 *  Protection is added against G4Event::GetEventID().
 *
 *  Revision 1.13  2006/05/25 12:53:13  nanjo
 *  GsimPersistencyManager::close() is commentouted form interruptHandler,
 *  which is correctly treated in the ~GsimPersistencyManager().
 *
 *  Revision 1.12  2006/04/13 17:06:52  nanjo
 *  Fix a bug on recreation of MTwisterEngine.
 *
 *  Revision 1.11  2006/04/12 12:07:17  nanjo
 *  Fix typo.
 *
 *  Revision 1.10  2006/04/12 08:18:20  nanjo
 *  namespace of CLHEP is resolved.
 *
 *  Revision 1.9  2006/03/22 05:29:58  nanjo
 *  GSIMDEBUG message is added to GsimEventAction.
 *
 *  Revision 1.8  2006/03/17 08:02:13  nanjo
 *  Add a flag to disable GsimBreifTrajectory. Make faster for the detector loop.
 *
 *  Revision 1.7  2006/03/14 16:11:51  nanjo
 *  Fix G4_Air to G4_AIR.
 *
 *  Revision 1.6  2006/02/17 04:22:57  nanjo
 *  GsimMaterialManager is added. Materials to be used hve to be decrlared before the 1st run.
 *
 *  Revision 1.5  2006/02/02 19:27:56  nanjo
 *  Add various KL correspondig to decay modes.
 *
 *  Revision 1.4  2006/01/31 22:47:08  nanjo
 *  BriefTrajectory is built from G4VUserTrakInformation.
 *
 *  Revision 1.3  2006/01/31 03:00:38  nanjo
 *  Detector ID and process ID are introduced and stored in TFile.
 *
 *  Revision 1.2  2006/01/27 00:06:26  nanjo
 *  Seeds are saved in GsimPersistencyManager
 *
 *  Revision 1.1  2006/01/26 04:53:30  nanjo
 *  Detector and persistency classes are added.
 *
 */
#include "GsimKernel/GsimRunAction.h"
#include "GsimKernel/GsimDetectorManager.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimPersistency/GsimPersistencyManager.h"
#include "GsimData/GsimRandData.h"
#include "GsimKernel/GsimRootRandom.h"

#include "G4Timer.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4TransportationManager.hh"
#include "G4StateManager.hh"
#include "G4ApplicationState.hh"
#include "G4SDManager.hh"
#include "G4ProcessTable.hh"
#include "G4Element.hh"



#include "CLHEP/Random/Randomize.h"
#include "CLHEP/Random/engineIDulong.h"



#include <sstream>
#include <csignal>
#include <map>
#include <list>
#include <vector>

GsimRunAction::GsimRunAction(GsimDetectorManager* dm, int runNumberBase)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_isFirstRun=true;
  m_nElements = 0;
  m_timer = new G4Timer;
  m_runNumberBase=runNumberBase;
  m_DM=dm;
  m_processData = new GsimProcessData();

  if(CLHEP::HepRandom::getTheEngine()->name()!="MTwistEngine") {
    CLHEP::HepRandom::setTheEngine(new CLHEP::MTwistEngine());
  }
  gRandom = new GsimRootRandom();
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimRunAction::~GsimRunAction()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  delete m_processData;
  delete m_timer;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimRunAction::BeginOfRunAction(const G4Run* aRun)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  int runID    =aRun->GetRunID();
  int runNumber=m_runNumberBase+runID;
  
  //PersistencyManager
  GsimPersistencyManager* persistencyManager =
    GsimPersistencyManager::getPersistencyManager();
  persistencyManager->preBeginOfRunAction(runID,runNumber);

  //RunAction
  {
    std::ostringstream ostr;
    ostr << "### Run " << runID << " start." << std::endl;
    GsimMessage::getInstance()
      ->report("info",ostr.str());
  }
  m_timer->Start();
  
  if(m_isFirstRun) {
    std::signal(SIGINT,GsimRunAction::interruptHandler);
    if(CLHEP::HepRandom::getTheEngine()->name()!="MTwistEngine") {
      CLHEP::HepRandom::setTheEngine(new CLHEP::MTwistEngine());
    }
    m_nElements = G4Element::GetNumberOfElements();
    m_isFirstRun=false;
  } else {
    //Number of Material Check
    int nEle = G4Element::GetNumberOfElements();
    if(nEle!=m_nElements) {
      //
      {
	std::ostringstream ostr;
	ostr << "Number of elements changed from "
	     << m_nElements << " to " << nEle << ".";
	GsimMessage::getInstance()
	  ->report("warning",ostr.str());
      }
      GsimMessage::getInstance()
	->report("warning","Please declare new materials before the 1st run like");
      GsimMessage::getInstance()
	->report("warning","/GsimMaterialManager/useNistMaterial G4_Al G4_Fe ...");
      GsimMessage::getInstance()
	->report("warning","   /GsimMaterialFactory/GsimOpticalMaterial/build");
      GsimMessage::getInstance()
	->report("error","The increase may not be reflected to some physics, for example, G4AugerData.");
      GsimMessage::getInstance()
	->report("error","Please don't use this run.");
    }
  }

  if(m_DM->isModified() || !m_DM->isUpdated()) {
    GsimMessage::getInstance()
      ->report("warning","Detector is not Updated. Force updating.");
    G4StateManager* stateManager = G4StateManager::GetStateManager();
    G4ApplicationState currentState = stateManager->GetCurrentState();
    stateManager->SetNewState(G4State_Idle); 
    m_DM->update();
    stateManager->SetNewState(currentState);
  }
  fillProcessData();
  //DetectorManager
  m_DM->beginOfRunAction();
  //PersistencyManager
  persistencyManager->postBeginOfRunAction();
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimRunAction::EndOfRunAction(const G4Run* aRun)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  if(m_DM) {
    m_DM->endOfRunAction();
  }
  m_timer->Stop();
  
  {
    std::ostringstream ostr;
    ostr << "number of event = " << aRun->GetNumberOfEvent()
	 << " " << *m_timer << std::endl;
    GsimMessage::getInstance()
      ->outputSystemInfo(ostr.str());
  }

  GsimPersistencyManager* persistencyManager =
    GsimPersistencyManager::getPersistencyManager();
  if(persistencyManager) persistencyManager->endOfRunAction();
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}
 
 
void GsimRunAction::interruptHandler(int ) {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4RunManager* fRunManager = G4RunManager::GetRunManager();
  
  std::ostringstream ostr;
  ostr << "Interrupted at";
  if(fRunManager->GetCurrentEvent()) {
    int eveid = fRunManager->GetCurrentEvent()->GetEventID();
    ostr << " EventID = " << eveid;
  }
  int runID = fRunManager->GetCurrentRun()->GetRunID();
  ostr << " RunID = " << runID << std::endl;
  GsimMessage::getInstance()
    ->report("info",ostr.str());


  //GsimPersistencyManager* persistencyManager =
  //  GsimPersistencyManager::getPersistencyManager();
  //if(persistencyManager) persistencyManager->close();

  fRunManager->AbortEvent();
  fRunManager->AbortRun();
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  
}

void GsimRunAction::setSeed(long singleSeed)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(CLHEP::HepRandom::getTheEngine()->name()!="MTwistEngine") {
    GsimMessage::getInstance()
      ->report("warning","GsimRunAction RandomEngine is changed to MTwiterEngine. ");
    CLHEP::HepRandom::setTheEngine(new CLHEP::MTwistEngine());
  }  
  CLHEP::HepRandom::getTheEngine()->setSeed(singleSeed,0);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimRunAction::setSeed(std::vector<unsigned long> seedVector)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(CLHEP::HepRandom::getTheEngine()->name()!="MTwistEngine") {
    GsimMessage::getInstance()
      ->report("warning","GsimRunAction RandomEngine is changed to MTwiterEngine.");
    CLHEP::HepRandom::setTheEngine(new CLHEP::MTwistEngine());
  }
  CLHEP::HepRandom::getTheEngine()->get(seedVector);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimRunAction::setSeed(std::string tfName,int runID,int eventID)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  std::vector<unsigned long> seedVector;
  if(!GsimRandData::getSeed(tfName,runID,eventID,seedVector)) {
    GsimMessage::getInstance()
      ->report("warning","GsimRunAction seedVector is not obtained.");
    return;
  }

  if(CLHEP::HepRandom::getTheEngine()->name()!="MTwistEngine") {
    GsimMessage::getInstance()
      ->report("warning","GsimRunAction RandomEngine is changed to MTwiterEngine.");
    CLHEP::HepRandom::setTheEngine(new CLHEP::MTwistEngine());
  }
  setSeed(seedVector);
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


int  GsimRunAction::getRunNumber() const
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4RunManager* fRunManager = G4RunManager::GetRunManager();
  int runID = fRunManager->GetCurrentRun()->GetRunID();
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return m_runNumberBase+runID;
}

int  GsimRunAction::getRunID() const
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4RunManager* fRunManager = G4RunManager::GetRunManager();
  int runID = fRunManager->GetCurrentRun()->GetRunID();
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return runID;
}


void GsimRunAction::fillProcessData()
{
  GsimPersistencyManager* persistencyManager =
    GsimPersistencyManager::getPersistencyManager();
  persistencyManager->setBranchOf("processTree",
				  "process","GsimProcessData",&m_processData);
  m_processData->processName="Primary";
  m_processData->processID=0;
  persistencyManager->fillTreeOf("processTree");
  
  G4ProcessTable* processTable = G4ProcessTable::GetProcessTable();
  G4ProcessTable::G4ProcNameVector* procNameVector
    = processTable->GetNameList();
  int idx=1;
  G4ProcessTable::G4ProcNameVector::iterator itr;
  for (itr=procNameVector->begin(); itr!=procNameVector->end(); ++itr) {
    m_processData->processName=(*itr).data();
    m_processData->processID=idx;
    idx++;
    persistencyManager->fillTreeOf("processTree");
  }
}

