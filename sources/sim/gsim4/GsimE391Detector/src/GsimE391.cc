/**
 *  @file
 *  @brief  GsimE391
 *  $Id: GsimE391.cc,v 1.6 2007/02/04 12:56:46 nanjo Exp $
 *  $Log: GsimE391.cc,v $
 *  Revision 1.6  2007/02/04 12:56:46  nanjo
 *  GsimBoxWithAHole is used.
 *
 *  Revision 1.5  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimE391Detector/GsimE391.h"
#include "GsimE391Detector/GsimUserGeom.h"
#include "GsimE391Detector/GsimE391Membrane.h"
#include "GsimE391Detector/GsimE391BA.h"
#include "GsimE391Detector/GsimE391BCV.h"
#include "GsimE391Detector/GsimE391BHCV.h"
#include "GsimE391Detector/GsimE391CBAR.h"
#include "GsimE391Detector/GsimE391CC00.h"
#include "GsimE391Detector/GsimE391CC02.h"
#include "GsimE391Detector/GsimE391CC03.h"
#include "GsimE391Detector/GsimE391CC04.h"
#include "GsimE391Detector/GsimE391CC05.h"
#include "GsimE391Detector/GsimE391CC06.h"
#include "GsimE391Detector/GsimE391CC07.h"
#include "GsimE391Detector/GsimE391CSI.h"
#include "GsimE391Detector/GsimE391CV.h"
#include "GsimE391Detector/GsimE391FBAR.h"
#include "GsimE391Detector/GsimE391SAND.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimPersistency/GsimPersistencyManager.h"

#include "G4Track.hh"
#include "G4VProcess.hh"

GsimE391::GsimE391(std::string name,
		   GsimDetector* motherDetector,
		   G4ThreeVector transV,G4ThreeVector rotV,
		   int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{

  m_className = "GsimE391";
  m_photoNuclearDetID = new int[1000];

  GsimE391Membrane* mbn = new GsimE391Membrane("mbn",this,
					       G4ThreeVector(0,0,0),
					       G4ThreeVector(0,0,0));
  addDaughter(mbn);
  m_detMoveList.push_back(mbn);
  
  
  GsimE391FBAR* fbar = new GsimE391FBAR("fbar",this,
					G4ThreeVector(0,0,(275./2.)*cm),
					G4ThreeVector(0,0,0));
  addDaughter(fbar);
  
  
  GsimE391CBAR* cbar = new GsimE391CBAR("cbar",this,
					G4ThreeVector(0,0,(134.8+550./2.)*cm),
					G4ThreeVector(0,0,0));
  addDaughter(cbar);
  
  GsimE391BCV* bcv = new GsimE391BCV("bcv",this,
				     G4ThreeVector(0,0,(135+550/2.)*cm),
				     G4ThreeVector(0,0,0));
  addDaughter(bcv);
  m_detMoveList.push_back(bcv);
  
  GsimE391CV* cv = new GsimE391CV("cv",this,
				  G4ThreeVector(0,0,(609.8-(45.-0.6)/2.)*cm),
				  G4ThreeVector(0,0,0));
  addDaughter(cv);
  m_detMoveList.push_back(cv);
  
  GsimE391CC02* cc02 = new GsimE391CC02("cc02",this,
					G4ThreeVector(0,0,(275.-((0.5+2.0*0.0375+0.1+0.005*2.0)*14.0+(0.5+2.0*0.0375+0.2+0.005*2.0)*29.0+(1.5*2.0+0.5))/2)*cm),
					G4ThreeVector(0,0,0));
  addDaughter(cc02);

  GsimE391CSI* csi = new GsimE391CSI("csi",this,
				     G4ThreeVector(0,0,(609.8+180./2.)*cm),
				     G4ThreeVector(0,0,0));
  addDaughter(csi);
  

  GsimE391CC03* cc03 = new GsimE391CC03("cc03",this,
					G4ThreeVector(0,0,(609.8+55./2.)*cm),
					G4ThreeVector(0,0,0));
  addDaughter(cc03);
  
  GsimE391SAND* sand = new GsimE391SAND("sand",this,
					G4ThreeVector(0,0,(609.8+5+30.0/2.)*cm),
					G4ThreeVector(0,0,0));
  addDaughter(sand);
  
  
  
  GsimE391CC04* cc04 = new GsimE391CC04("cc04",this,
					G4ThreeVector(0,0,(614.8+95.5+(((32+2)*0.5+32*0.2+(2*32+2-1)*0.025)+(0.8+3.)*2.)/2.)*cm),
					G4ThreeVector(0,0,0));
  addDaughter(cc04);
  
  GsimE391CC05* cc05 = new GsimE391CC05("cc05",this,
					G4ThreeVector(0,0,(614.8+259.3+(((30+2+2)*0.5+32*0.2+(2*2+2-1)*0.025)+(0.8+3.)*2.)/2.)*cm),
					G4ThreeVector(0,0,0));
  addDaughter(cc05);

  GsimE391CC00* cc00 = new GsimE391CC00("cc00",this,
					G4ThreeVector(0,0,(-59.0-((0.5+2.0+0.1)*10+0.5)/2.)*cm),
					G4ThreeVector(0,0,0));
  addDaughter(cc00);
  
  GsimE391CC06* cc06 = new GsimE391CC06("cc06",this,
					G4ThreeVector(0,0,(614.8+310.8+15.0/2.)*cm),
					G4ThreeVector(0,0,0));
  addDaughter(cc06);
  
  GsimE391CC07* cc07 = new GsimE391CC07("cc07",this,
					G4ThreeVector(0,0,(614.8+385.8+15.0/2.)*cm),
					G4ThreeVector(0,0,0));
  addDaughter(cc07);
  
  GsimE391BHCV* bhcv = new GsimE391BHCV("bhcv",this,
					G4ThreeVector(0,0,(614.8+414.5+7.0+5.0)*cm),
					G4ThreeVector(0,0,0));
  addDaughter(bhcv);
  m_detMoveList.push_back(bhcv);
  
  GsimE391BA* ba = new GsimE391BA("ba",this,
				  G4ThreeVector(0,0,(614.8+444.5+51./2.+10.)*cm),
				  G4ThreeVector(0,0,0));
  addDaughter(ba);

  update();
  
}


GsimE391::~GsimE391()
{
  delete [] m_photoNuclearDetID;
}



void GsimE391::beginOfRunAction()
{
  GsimPersistencyManager* pm= GsimPersistencyManager::getPersistencyManager();
  pm->setBranchOf("eventTree",
		  "photoNuclearN",&m_photoNuclearN,"photoNuclearN/I");
  pm->setBranchOf("eventTree",
		  "photoNuclearDetID",m_photoNuclearDetID,"photoNuclearDetID[photoNuclearN]/I");
}

void GsimE391::endOfRunAction()
{
  ;
}

bool GsimE391::beginOfEventAction(const G4Event*)
{
  m_photoNuclearN=0;
  return true;
}

bool GsimE391::endOfEventAction(const G4Event*)
{
  return false;
}

bool GsimE391::steppingAction(const G4Step* theStep)
{
  G4Track* track = theStep->GetTrack();
  G4String theProName =""; 
  if(theStep->GetPostStepPoint()->GetProcessDefinedStep() != 0){
    theProName = 
      theStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
  }
  if(theProName == "PhotonInelastic") {
    GsimPersistencyManager* persistencyManager
      = GsimPersistencyManager::getPersistencyManager();
    std::string volumeName = std::string( (track->GetVolume()->GetName()).data() );
    int detID=persistencyManager->getDetectorIDByPhysicalVolumeName(volumeName);
    int briefID = persistencyManager->getDetectorBriefIDByID(detID);
    if(briefID!=-1) {
      if(m_photoNuclearN<1000) {
	m_photoNuclearDetID[m_photoNuclearN]=briefID;
	m_photoNuclearN++;
      }
    }
  }
  return true;
}



void GsimE391::setFastSimulationLevel(int level)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  //reset
  if(m_fastSimulationLevel==6) {
    for(std::list<GsimDetector*>::iterator it=m_detMoveList.begin();
	it!=m_detMoveList.end();it++) {
      G4ThreeVector pos=(*it)->getTranslationVector();
      double z=pos.getZ();
      pos.setZ(z+29*m);
      (*it)->setTranslationVector(pos);
      (*it)->setThisAndDaughterOuterVisibility(true);
    }
  }

  //set
  if(level==6) {
    for(std::list<GsimDetector*>::iterator it=m_detMoveList.begin();
	it!=m_detMoveList.end();it++) {
      G4ThreeVector pos=(*it)->getTranslationVector();
      double z=pos.getZ();
      pos.setZ(z-29*m);
      (*it)->setTranslationVector(pos);
      (*it)->setThisAndDaughterOuterVisibility(false);
    }
  }

  
  {
    m_fastSimulationLevel=level;
    for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
	it!=m_daughterDetectorContainer.end();it++) {
      GsimDetector* daughter =  (*it).second;
      daughter->setFastSimulationLevel(level);
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif 
}
