/**
 *  @file
 *  @brief  GsimE14CSI
 *  $Id:  GsimE14CSI.cc,v  2012/05/14 14:36:58 sato Exp
 *  $Log: GsimE14CSI.cc,v $
 *
 *  Revision 2.0  2012/05/14 14:34  sato
 *  make CsI ID assignment left-right revarsal  
 *
 *  Revision 1.9  2007/02/04 12:56:55  nanjo
 *  GsimBoxWithAHole is used.
 *
 *  Revision 1.8  2006/12/06 18:59:15  nanjo
 *  Etot trigger is added.
 *
 *
 */
#include "GsimE14Detector/GsimE14CSI.h"
#include "GsimE14Detector/GsimE14UserGeom.h"
#include "GsimPersistency/GsimPersistencyManager.h"
#include "GsimKernel/GsimTrackInformation.h"
#include "GsimKernel/GsimSensitiveDetector.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimDetector/GsimTrap.h"
#include "GsimDetector/GsimTube.h"
#include "GsimDetector/GsimBox.h"
#include "GsimData/GsimEventData.h"

#include "G4Track.hh"
#include "G4VProcess.hh"

using namespace E14; 


GsimE14CSI::GsimE14CSI(std::string name,
		       GsimDetector* motherDetector,
		       G4ThreeVector transV,G4ThreeVector rotV,
		       int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{

  m_className = "GsimE14CSI";
  m_model=1;
  //0:20cm beam hole
  //1:15cm beam hole
  m_totEThreshold=0;
  
  // CsI crystal
  GsimTube* tube=0;
  
  // CsI region
  double  csir_rmin = 0;
  //double  csir_rmax = 97.3;
  //double  csir_rmax = 98;
  double  csir_rmax = 96.5; // corrected by Matsumura

  char nam[100];

  // CsI Cylinder
  //double  cscl_thick = 2.0; // 20 mm thick SUS
  double  cscl_thick = 1.2; // 12 mm thick SUS corrected by Matsumura
  double  cscl_len  = Csir_Len - 5;
  double  cscl_rmax = csir_rmax;
  double  cscl_rmin = cscl_rmax - cscl_thick;
  
  std::vector<double> paramVec;
  paramVec.push_back(cscl_rmin*cm);
  paramVec.push_back(cscl_rmax*cm);
  paramVec.push_back(cscl_len*cm);
  paramVec.push_back(0.*deg);
  paramVec.push_back(360.*deg);

  sprintf(nam,"CSCL");
  tube = new GsimTube(std::string(nam),this,
		      G4ThreeVector(0*cm,0*cm,2.5*cm),
		      G4ThreeVector(0,0,0));
  tube->setOuterMaterial("G4_Fe");
  tube->setParameters(paramVec);
  tube->setOuterColor("gray70");
  addDaughter(tube);
  m_detMoveList.push_back(tube);

  // CsI Cylinder Endcap 
  double  csec_thick = 2.0; // 20 mm thick SUS
  double  csec_rmax = csir_rmax - cscl_thick;
  double  csec_rmin = 20;
  paramVec.clear();
  paramVec.push_back(csec_rmin*cm);
  paramVec.push_back(csec_rmax*cm);
  paramVec.push_back(csec_thick*cm);
  paramVec.push_back(0.*deg);
  paramVec.push_back(360.*deg);
  
  sprintf(nam,"CSEC");
  GsimTube* ecap = new GsimTube(std::string(nam),this,
				G4ThreeVector(0*cm,0*cm,(Csir_Len/2-cscl_thick/2)*cm),
				G4ThreeVector(0,0,0));
  ecap->setOuterMaterial("G4_Fe");
  ecap->setParameters(paramVec);
  ecap->setOuterColor("gray70");
  addDaughter(ecap);
  m_detMoveList.push_back(ecap);


  // CsI Dummy Inner Compartment 1,2
  
  double csh1_len = KtevCsicFine_Len;
  double c_csh1_z = -Csir_Len/2 + 5 + csh1_len/2;

  sprintf(nam,"CSH1");
  GsimDetector* csh1
    = new GsimDetector(std::string(nam),this,
		       G4ThreeVector(0,0,c_csh1_z*cm),
		       G4ThreeVector(0,0,0));
  addDaughter(csh1);

  std::vector<double> paramKTEVFine;
  paramKTEVFine.push_back(KtevCsicFine_XY*cm);
  paramKTEVFine.push_back(KtevCsicFine_XY*cm);
  paramKTEVFine.push_back(KtevCsicFine_Len*cm);

  GsimBox* boxKTEVFine=0;
  int nBlockFine=48;
  int nBeamHole=8+2;
  if(m_model!=0) {
    nBeamHole=8;
  }
  int id=0;
  for(int i=0;i<nBlockFine;i++) {
    double YBlock=
      (KtevCsicFine_XY+KtevCsicFine_Gap)*(i-nBlockFine/2.)
      +(KtevCsicFine_XY+KtevCsicFine_Gap)/2.;
    
    for(int j=0;j<nBlockFine;j++) {
      {
	double XBlock=
	  (KtevCsicFine_XY+KtevCsicFine_Gap)*(j-nBlockFine/2.)
	  +(KtevCsicFine_XY+KtevCsicFine_Gap)/2.;
	
	//beam hole
	if( i>=(nBlockFine-nBeamHole)/2. &&
	    i<(nBlockFine-nBeamHole)/2.+nBeamHole &&
	    j>=(nBlockFine-nBeamHole)/2. &&
	    j<(nBlockFine-nBeamHole)/2.+nBeamHole )
	  continue;
	
	// added by Sato 20120514
	XBlock*=-1;
	if(boxKTEVFine==0) {
	  std::sprintf(nam,"KTEVCSIFine");
	  boxKTEVFine = new GsimBox(std::string(nam),csh1,
				    G4ThreeVector(XBlock*cm,
						  YBlock*cm,
						  (-csh1_len/2.+KtevCsicFine_Len/2.)*cm),
				    G4ThreeVector(0,0,0)
				    );
	  boxKTEVFine->setOuterMaterial("G4_CESIUM_IODIDE");
	  boxKTEVFine->setParameters(paramKTEVFine);
	  boxKTEVFine->setOuterColor("lightskyblue");
	  boxKTEVFine->setSensitiveDetector("CSI",id);
	  csh1->addDaughter(boxKTEVFine);
	} else {
	  boxKTEVFine->cloneDetector(G4ThreeVector(XBlock*cm,
						   YBlock*cm,
						   (-csh1_len/2.+KtevCsicFine_Len/2.)*cm),
				     G4ThreeVector(0,0,0),id);
	}
	id++;
      }
    }
  }

  double csh2_len = KtevCsic_Len;
  double c_csh2_z = -Csir_Len/2 + 5 + csh2_len/2;
  
  sprintf(nam,"CSH2");
  GsimDetector* csh2
    = new GsimDetector(std::string(nam),this,
		       G4ThreeVector(0,0,c_csh2_z*cm),
		       G4ThreeVector(0,0,0));
  addDaughter(csh2);
  

  std::vector<double> paramKTEV;
  paramKTEV.push_back(KtevCsic_XY*cm);
  paramKTEV.push_back(KtevCsic_XY*cm);
  paramKTEV.push_back(KtevCsic_Len*cm);

  GsimBox* boxKTEV=0;

  int csiStack[38]
    = { 0,12,16,20,22,24,
        26,28,30,32,32,34,
        34,36,36,36,36,36,36,
        36,36,36,36,36,36,34,
        34,32,32,30,28,26,
        24,22,20,16,12,0 };
  
  int nLayer=38;
  for(int i=0;i<nLayer;i++) {
    double YBlock=
      (KtevCsic_XY+KtevCsic_Gap)*(i-nLayer/2.)
      +(KtevCsic_XY+KtevCsic_Gap)/2.;
    
    int nBlock = csiStack[i];
    
    for(int j=0;j<nBlock;j++) {
      //KtevFine
      if( i>=(nLayer-nBlockFine/2.)/2. &&
	  i<(nLayer-nBlockFine/2.)/2.+nBlockFine/2. &&
	  j>=(nBlock-nBlockFine/2.)/2. &&
	  j<(nBlock-nBlockFine/2.)/2.+nBlockFine/2. )
	continue;
      
      double XBlock=
	(KtevCsic_XY+KtevCsic_Gap)*(j-nBlock/2.)
	+(KtevCsic_XY+KtevCsic_Gap)/2.;
      // added by Sato 20120514
      XBlock*=-1;
      if(boxKTEV==0) {
	std::sprintf(nam,"KTEVCSI");
	boxKTEV = new GsimBox(std::string(nam),csh2,
			      G4ThreeVector(XBlock*cm,
					    YBlock*cm,
					    (-csh2_len/2.+KtevCsic_Len/2.)*cm),
			      G4ThreeVector(0,0,0)
			      );
	boxKTEV->setOuterMaterial("G4_CESIUM_IODIDE");
	boxKTEV->setParameters(paramKTEV);
	boxKTEV->setOuterColor("lightskyblue");
	boxKTEV->setSensitiveDetector("CSI",id);
	csh2->addDaughter(boxKTEV);
      } else {
	boxKTEV->cloneDetector(G4ThreeVector(XBlock*cm,
					     YBlock*cm,
					     (-csh2_len/2.+KtevCsic_Len/2.)*cm),
			       G4ThreeVector(0,0,0),id);
      }
      id++;
    }
  }
  setThisAndDaughterBriefName("CSI");
  ecap->setThisAndDaughterBriefName("ECAP");
}


GsimE14CSI::~GsimE14CSI()
{
  ;
}




bool GsimE14CSI::endOfEventAction(const G4Event* )
{
  std::list<GsimSensitiveDetector*> sdList
    =getThisAndDaughterSensitiveDetectorList();
  for(std::map<G4LogicalVolume*,GsimSensitiveDetector*>::iterator
	it=m_sensitiveDetectorMap.begin();
      it!=m_sensitiveDetectorMap.end();it++) {
    GsimSensitiveDetector* sd=(*it).second;
    sdList.push_back(sd);
  }
  sdList.sort();
  sdList.unique();

  double totE=0;
  for(std::list<GsimSensitiveDetector*>::iterator
	it=sdList.begin();it!=sdList.end();it++) {
    totE+=(*it)->getTotalEnergy();
  }
  GsimPersistencyManager* pm=GsimPersistencyManager::getPersistencyManager();

  if(totE>m_totEThreshold) {
    pm->addTriggerBit(TRIG_NCLUS);
  }
  
  return true;
}


void GsimE14CSI::setFastSimulationLevel(int level)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  //reset
  if(m_fastSimulationLevel==6) {
    for(std::list<GsimDetector*>::iterator it=m_detList.begin();
	it!=m_detList.end();it++) {
      (*it)->unsetSensitiveDetector();
    }
    
    for(std::list<GsimDetector*>::iterator it=m_detMoveList.begin();
	it!=m_detMoveList.end();it++) {
      G4ThreeVector pos=(*it)->getTranslationVector();
      double z=pos.getZ();
      pos.setZ(z+29*m);
      (*it)->setTranslationVector(pos);
      (*it)->setOuterVisibility(true);
    }
  }

  //set
  if(level==6) {
    for(std::list<GsimDetector*>::iterator it=m_detList.begin();
	it!=m_detList.end();it++) {
      (*it)->setSensitiveDetector("CSI",0);
    }
    for(std::list<GsimDetector*>::iterator it=m_detMoveList.begin();
	it!=m_detMoveList.end();it++) {
      G4ThreeVector pos=(*it)->getTranslationVector();
      double z=pos.getZ();
      pos.setZ(z-29*m);
      (*it)->setTranslationVector(pos);
      (*it)->setOuterVisibility(false);
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
