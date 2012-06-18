/**
 *  $Id: GsimPersistencyManager.cc,v 1.36 2007/02/04 12:54:11 nanjo Exp $
 *  $Log: GsimPersistencyManager.cc,v $
 *  Revision 1.36  2007/02/04 12:54:11  nanjo
 *  Macro is stored in ROOT file.
 *
 *  Revision 1.35  2006/12/09 21:34:09  nanjo
 *  briefHistory is corrected and dictionary write.
 *
 *  Revision 1.34  2006/12/07 08:50:16  nanjo
 *  Midas interfaces for GsimGenParticleData and GsimDetectorEventData are added.
 *
 *  Revision 1.33  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 *  Revision 1.32  2006/12/04 20:20:40  nanjo
 *  runNumber is given at PersistencyManager::preBeginOfRun.
 *
 *  Revision 1.31  2006/12/04 17:27:49  nanjo
 *  Data are kept in each class, which are registered to persistencyManger.
 *  GsimPersistencyManger::setBranchOf is added then UserEventData is removed.
 *
 *  Revision 1.30  2006/12/02 07:06:38  nanjo
 *  runTree is added.
 *
 *  Revision 1.29  2006/11/30 20:07:11  nanjo
 *  Data are re-structured.
 *
 *  Revision 1.28  2006/11/20 16:16:45  nanjo
 *  SensitiveDetectorList is kept in DetectorManager.
 *
 *  Revision 1.27  2006/11/17 12:09:41  nanjo
 *  RunIDBase is added.
 *
 *  Revision 1.26  2006/10/26 14:46:12  nanjo
 *  releaseUserEventBranch is added.
 *
 *  Revision 1.25  2006/10/24 15:23:08  nanjo
 *  SensitiveDetector is re-structred.
 *
 *  Revision 1.24  2006/10/19 03:28:44  nanjo
 *  GsimPersistencyManagerMessenger is replaced by GsimRunActionMessneger.
 *  Information of photonuclear interaction is not filled here.
 *  Cluster ID is filled.
 *  Now GsimPersistencyManager, GsimDigitizer, and, GsimMessage is
 *  independent of Geant4. They will be moved to different directory
 *  in order to use from ROOT analysis.
 *
 *  Revision 1.23  2006/10/16 01:54:22  nanjo
 *  CLHEP functions are removed from GsimPersistencyManager.
 *
 *  Revision 1.22  2006/09/06 22:33:18  nanjo
 *  GsimDetectorData is added.
 *
 *  Revision 1.21  2006/08/09 13:24:58  nanjo
 *  ROOT streamer is corrected and warning message in material check is suppressed.
 *
 *  Revision 1.20  2006/08/01 05:27:55  nanjo
 *  GsimSpectrum is added. Debug print is updated. With/without Digi is implemented.
 *
 *  Revision 1.19  2006/06/22 11:38:57  nanjo
 *  Modifications around briefDetectorID and briefDetectorName.
 *
 *  Revision 1.18  2006/05/26 12:14:36  nanjo
 *  Call TFile::cd() before TTree::Write().
 *
 *  Revision 1.17  2006/05/25 12:26:24  nanjo
 *  Remove getchar().
 *
 *  Revision 1.16  2006/05/25 12:23:45  nanjo
 *  Correct debug message.
 *
 *  Revision 1.15  2006/04/13 16:12:23  nanjo
 *  Fix a bug on branch of runSeedTree.
 *
 *  Revision 1.14  2006/04/13 12:23:21  nanjo
 *  When the seed is set, random engine is set to MT .
 *
 *  Revision 1.13  2006/04/12 08:18:20  nanjo
 *  namespace of CLHEP is resolved.
 *
 *  Revision 1.12  2006/04/11 12:39:24  nanjo
 *  Fix a bug for userEventData and GsimDetector::clearThisClone is added.
 *
 *  Revision 1.11  2006/04/09 22:27:41  nanjo
 *  Correction of a miss-spell.
 *
 *  Revision 1.10  2006/04/09 22:19:20  nanjo
 *  UserEventData is added.
 *
 *  Revision 1.9  2006/04/09 20:38:57  nanjo
 *  Set compression level of ROOT file, which was suggested by Jeremy.
 *
 *  Revision 1.8  2006/03/01 12:45:32  nanjo
 *  A member function of GsimDetector, cloneDetector, is added and used in E391Detector.
 *
 *  Revision 1.7  2006/02/01 15:42:26  nanjo
 *  BriefTrajectory is stored in ROOT file.
 *
 *  Revision 1.6  2006/01/31 22:47:08  nanjo
 *  BriefTrajectory is built from G4VUserTrakInformation.
 *
 *  Revision 1.5  2006/01/31 03:00:38  nanjo
 *  Detector ID and process ID are introduced and stored in TFile.
 *
 *  Revision 1.4  2006/01/30 02:42:07  nanjo
 *  Detector information is stored in persistencyManager.
 *
 *  Revision 1.3  2006/01/27 05:08:24  nanjo
 *  PersistencyManagerMessenger is added.
 *
 *  Revision 1.2  2006/01/27 00:06:26  nanjo
 *  Seeds are saved in GsimPersistencyManager
 *
 *  Revision 1.1  2006/01/26 04:53:30  nanjo
 *  Detector and persistency classes are added.
 *
 */
#include "GsimPersistency/GsimPersistencyManager.h"
#include "GsimPersistency/GsimFileIO.h"
#include "GsimPersistency/GsimRootIO.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimData/GsimDetectorData.h"
#include "GsimData/GsimPhysicalVolumeData.h"

#include "TFile.h"
#include "TTree.h"
#include "TEventList.h"
#include "TLeafI.h"
#include "TH1.h"

#include <sstream>

GsimPersistencyManager* GsimPersistencyManager::s_persistencyManager=0;


GsimPersistencyManager::GsimPersistencyManager(const char* tfname)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif


  int ofType=0;
  if(tfname!=0) {
    std::string ts=std::string(tfname);
    size_t n = ts.size();
    std::string tail="";
    if(n>6) {
      tail=std::string(ts,n-6,6);
      if(tail==".midas") {
	ofType=1;
      }
    }
    if(n>5) {
      tail=std::string(ts,n-5,5);
      if(tail==".root") {
	ofType=0;
      }
    }
    if(n>4) {
      tail=std::string(ts,n-4,4);
      if(tail==".mid") {
	ofType=1;
      }
    }
  }
  
  if(ofType==1) {
    //m_fileIO = new GsimMidasFileIO(tfname);
    GsimMessage::getInstance()
      ->report("error","Midas file is not supported no longer.");
  } else {
    m_fileIO = new GsimRootIO(tfname);
  }
  
  if(s_persistencyManager) {
    GsimMessage::getInstance()
      ->report("warning","GsimPersistencyManager constructor is called twice.");
    return;
  }
  s_persistencyManager  = this;
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimPersistencyManager::~GsimPersistencyManager() {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  delete m_fileIO;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimPersistencyManager* GsimPersistencyManager::getPersistencyManager() {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(!s_persistencyManager) {
    s_persistencyManager  = new GsimPersistencyManager("tmp.root");
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return s_persistencyManager;
}

void GsimPersistencyManager::preBeginOfRunAction(int treeID, int runNumber)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_fileIO->preBeginOfRunAction(treeID, runNumber);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimPersistencyManager::postBeginOfRunAction()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_fileIO->postBeginOfRunAction();
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimPersistencyManager::endOfRunAction()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_fileIO->endOfRunAction();
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimPersistencyManager::beginOfEventAction()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_fileIO->beginOfEventAction();
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimPersistencyManager::endOfEventAction(int eventID,bool withDataToStore)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_fileIO->endOfEventAction(eventID,withDataToStore);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimPersistencyManager::close()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_fileIO->close();
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimPersistencyManager::setBranchOf(std::string treeName,
					 std::string title,
					 std::string className,
					 void* address)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_fileIO->setBranchOf(treeName,title,className,address);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimPersistencyManager::setBranchOf(std::string treeName,
					 std::string title,
					 void* address,
					 std::string format)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_fileIO->setBranchOf(treeName,title,address,format);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimPersistencyManager::fillTreeOf(std::string treeName)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_fileIO->fillTreeOf(treeName);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimPersistencyManager::setEventBranch(std::string title,
					    std::string className,
					    void* address)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_fileIO->setEventBranch( title,className,address);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimPersistencyManager::setEventSeedBranch(std::string title,
						std::string className,
						void* address)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_fileIO->setEventSeedBranch( title,className,address);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimPersistencyManager::addTriggerBit(unsigned int status)
{
  m_fileIO->addTriggerBit(status);
}

void GsimPersistencyManager::setCycleOfEventSeedStore(int nEvent)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_fileIO->setCycleOfEventSeedStore(nEvent);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

std::string GsimPersistencyManager::getDetectorFullNameByID(int detectorID)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  std::string out=m_fileIO->getDetectorFullNameByID(detectorID);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return out;
}

int GsimPersistencyManager::getDetectorIDByFullName(std::string detectorFullName)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  int out=m_fileIO->getDetectorIDByFullName(detectorFullName);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return out;
}

int GsimPersistencyManager::getDetectorBriefIDByID(int detectorID)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  int out=m_fileIO->getDetectorBriefIDByID(detectorID);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return out;
}

int GsimPersistencyManager::getDetectorBriefIDByBriefName(std::string briefName)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  int out=m_fileIO->getDetectorBriefIDByBriefName(briefName);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return out;
}

std::string GsimPersistencyManager::getDetectorBriefNameByBriefID(int briefID)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  std::string out=m_fileIO->getDetectorBriefNameByBriefID(briefID);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return out;
}

int GsimPersistencyManager::getDetectorIDByPhysicalVolumeName(std::string physicalVolumeName)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  int out = m_fileIO->getDetectorIDByPhysicalVolumeName(physicalVolumeName);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return out;
}

std::string GsimPersistencyManager::getProcessNameByID(int processID)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  std::string out=m_fileIO->getProcessNameByID(processID);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return out;
}

int GsimPersistencyManager::getProcessIDByName(std::string processName)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  int out=m_fileIO->getProcessIDByName(processName);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return out;
}


std::map<int,int> GsimPersistencyManager::getClusterInfo(std::string sensitiveDetectorName)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  std::map<int,int> out=m_fileIO->getClusterInfo(sensitiveDetectorName);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return out;
}


void GsimPersistencyManager::writeDictionary(bool write)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_fileIO->withDictionary(write);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimPersistencyManager::readScript(const char* fname)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_fileIO->readScript(fname);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimPersistencyManager::readCommand(const char* line)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_fileIO->readCommand(line);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


TH1D* GsimPersistencyManager::
createHistogram(char* name,char* title,int nbin,double xmin,double xmax)
{
  return m_fileIO->createHistogram(name,title,nbin,xmin,xmax);
}

void  GsimPersistencyManager::
fillHistogram(char* name,double value)
{
  m_fileIO->fillHistogram(name,value);
}


TH2D* GsimPersistencyManager::
createHistogram(char* name,char* title,
		int nbinx,double xmin,double xmax,
		int nbiny,double ymin,double ymax)
{
  return m_fileIO->createHistogram(name,title,
				   nbinx,xmin,xmax,
				   nbiny,ymin,ymax);
}

void  GsimPersistencyManager::
fillHistogram(char* name,double xvalue,double yvalue)
{
  m_fileIO->fillHistogram(name,xvalue,yvalue);
}
