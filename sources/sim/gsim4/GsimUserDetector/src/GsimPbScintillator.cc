/**
 *  @file
 *  @brief  GsimPbScintillator
 *  $Id: GsimPbScintillator.cc,v 1.7 2006/12/07 18:29:33 nanjo Exp $ 
 *  $Log: GsimPbScintillator.cc,v $
 *  Revision 1.7  2006/12/07 18:29:33  nanjo
 *  GsimDetector userInputs are used.
 *
 *  Revision 1.6  2006/12/06 19:28:29  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimUserDetector/GsimPbScintillator.h"
#include "GsimDetector/GsimBox.h"
#include "GsimPersistency/GsimPersistencyManager.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4Box.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"
#include "G4Neutron.hh"

GsimPbScintillator::GsimPbScintillator(std::string name,
				       GsimDetector* motherDetector,
				       G4ThreeVector transV,G4ThreeVector rotV,
				       int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{

  m_className = "GsimPbScintillator";

  m_numberOfParameters=6;
  m_parameterArray= new double[m_numberOfParameters];
  m_parameterArray[0] =1.*m;   // x length of box
  m_parameterArray[1] =1.*m;   // y length of box
  m_parameterArray[2] =1.*mm;  // z length of Pb
  m_parameterArray[3] =3.*mm;  // z length of Sci
  m_parameterArray[4] =81;     // number of Pb  layer
  m_parameterArray[5] =82;     // number of Sci layer

  m_MB = new GsimBox("MB",this,
		     G4ThreeVector(0,0,0),
		     G4ThreeVector(0,0,0));

  m_MB->setOuterMaterial("G4_Galactic");
  m_MB->setOuterVisibility(true);
  m_MB->setBriefName("MB");
  addDaughter(m_MB);

  m_Pb = new GsimBox("Pb",m_MB,
		     G4ThreeVector(0,0,0),
		     G4ThreeVector(0,0,0));
  
  m_Pb->setOuterMaterial("G4_Pb");
  m_Pb->setOuterVisibility(true);
  m_Pb->setOuterColor("gray70");
  m_Pb->setBriefName("MB");
  m_MB->addDaughter(m_Pb);

  

  m_Sc = new GsimBox("Sc",m_MB,
		     G4ThreeVector(0,0,0),
		     G4ThreeVector(0,0,0));
  m_Sc->setOuterVisibility(true);
  m_Sc->setOuterColor("yellow");
  m_Sc->setBriefName("MB");
  m_Sc->setSensitiveDetector(name);
  m_MB->addDaughter(m_Sc);

  m_Pb->setSensitiveDetector(name+"Pb");
  m_Pb->setHitsStore(false);

  
  update();
}


GsimPbScintillator::~GsimPbScintillator()
{
  ;
}

void GsimPbScintillator::constructPhysiDetector()
{
  
}

void GsimPbScintillator::updateParametersEtc()
{
  
  if(m_parameterArray[4]==m_parameterArray[5]) {
  } else if(m_parameterArray[4]+1==m_parameterArray[5]) {
  } else {
    m_parameterArray[5]=m_parameterArray[4];
  }

  double MBlen=
    m_parameterArray[2]*m_parameterArray[4]
    +m_parameterArray[3]*m_parameterArray[5];
  std::vector<double> paramMB;
  paramMB.push_back(m_parameterArray[0]);
  paramMB.push_back(m_parameterArray[1]);
  paramMB.push_back(MBlen);
  m_MB->setParameters(paramMB);
  m_MB->setTranslationVector(G4ThreeVector(0,0,MBlen/2));

  m_Pb->clearThisClone();
  m_Sc->clearThisClone();

  std::vector<double> paramPb;
  paramPb.push_back(m_parameterArray[0]);
  paramPb.push_back(m_parameterArray[1]);
  paramPb.push_back(m_parameterArray[2]);


  double pb1stZ=m_parameterArray[2]/2.-MBlen/2.;
  double sc1stZ=m_parameterArray[2]+m_parameterArray[3]/2.-MBlen/2.;
  if(m_parameterArray[4]+1==m_parameterArray[5]) {
    sc1stZ=m_parameterArray[3]/2.-MBlen/2.;
    pb1stZ=m_parameterArray[3]+m_parameterArray[2]/2.-MBlen/2.;
  }
  m_Pb->setParameters(paramPb);
  m_Pb->setTranslationVector(G4ThreeVector(0,0,pb1stZ));


  std::vector<double> paramSc;
  paramSc.push_back(m_parameterArray[0]);
  paramSc.push_back(m_parameterArray[1]);
  paramSc.push_back(m_parameterArray[3]);
  m_Sc->setParameters(paramSc);
  m_Sc->setTranslationVector(G4ThreeVector(0,0,sc1stZ));
  


  
  
  for(int k=1;k<m_parameterArray[4];k++) {
    double z=pb1stZ+(m_parameterArray[2]+m_parameterArray[3])*k;
    m_Pb->cloneDetector(G4ThreeVector(0,0,z),
			G4ThreeVector(0,0,0),k);
  }

  
  for(int k=1;k<m_parameterArray[5];k++) {
    double z=sc1stZ+(m_parameterArray[2]+m_parameterArray[3])*k;
    m_Sc->cloneDetector(G4ThreeVector(0,0,z),
			G4ThreeVector(0,0,0),k);
  }

}

void GsimPbScintillator::beginOfRunAction()
  
{
  if(m_userFlag==1) {
    GsimPersistencyManager* pm= GsimPersistencyManager::getPersistencyManager();
    
    pm->setBranchOf("eventTree",
		    "photoNuclearIniNum",&m_photoNuclearIniNum,
		    "photoNuclearIniNum/I");
    pm->setBranchOf("eventTree",
		    "photoNuclearFinNum",&m_photoNuclearFinNum,
		    "photoNuclearFinNum/I");
    pm->setBranchOf("eventTree",
		    "photoNuclearIniPosZ",m_photoNuclearIniPosZ,
		    "photoNuclearIniPosZ[photoNuclearIniNum]/D");
    pm->setBranchOf("eventTree",
		    "photoNuclearIniDetectorID",m_photoNuclearIniDetectorID,
		    "photoNuclearIniDetectorID[photoNuclearIniNum]/I");
    pm->setBranchOf("eventTree",
		    "photoNuclearFinPosZ",m_photoNuclearFinPosZ,
		    "photoNuclearFinPosZ[photoNuclearFinNum]/D");
    pm->setBranchOf("eventTree",
		    "photoNuclearFinDetectorID",m_photoNuclearFinDetectorID,
		    "photoNuclearFinDetectorID[photoNuclearFinNum]/I");
    
    pm->setBranchOf("eventTree",
		    "neutronIniNum",&m_neutronIniNum,
		    "neutronIniNum/I");
    pm->setBranchOf("eventTree",
		    "neutronFinNum",&m_neutronFinNum,
		    "neutronFinNum/I");
    pm->setBranchOf("eventTree",
		    "neutronIniPosZ",m_neutronIniPosZ,
		    "neutronIniPosZ[neutronIniNum]/D");
    pm->setBranchOf("eventTree",
		    "neutronIniDetectorID",m_neutronIniDetectorID,
		    "neutronIniDetectorID[neutronIniNum]/I");
    pm->setBranchOf("eventTree",
		    "neutronIniCreProcessID",m_neutronIniCreProcessID,
		    "neutronIniCreProcessID[neutronIniNum]/I");
    pm->setBranchOf("eventTree",
		    "neutronIniE",m_neutronIniE,
		    "neutronIniE[neutronIniNum]/D");
    pm->setBranchOf("eventTree",
		    "neutronFinPosZ",m_neutronFinPosZ,
		    "neutronFinPosZ[neutronFinNum]/D");
    pm->setBranchOf("eventTree",
		    "neutronFinDetectorID",m_neutronFinDetectorID,
		    "neutronFinDetectorID[neutronFinNum]/I");
    pm->setBranchOf("eventTree",
		    "neutronFinE",m_neutronFinE,
		    "neutronFinE[neutronFinNum]/D");
    
    pm->setBranchOf("eventTree",
		    "neutronWorldNNum",&m_neutronWorldNNum,
		    "neutronWorldNNum/I");
    pm->setBranchOf("eventTree",
		    "neutronWorldN",m_neutronWorldN,
		    "neutronWorldN[neutronWorldNNum]/I");
  }
}
  
bool GsimPbScintillator::beginOfEventAction(const G4Event* )
{
  m_photoNuclearIniNum=0;
  m_photoNuclearFinNum=0;
  m_neutronIniNum=0;
  m_neutronFinNum=0;
  m_neutronWorldNNum=1;
  m_neutronWorldN[0]=0;
  return true;
}

bool GsimPbScintillator::endOfEventAction(const G4Event* )
{
  return false;
}

bool GsimPbScintillator::preTrackingAction(const G4Track* aTrack) {
  //PN origin track
  if(m_userFlag==1) {
    GsimPersistencyManager* pm= GsimPersistencyManager::getPersistencyManager();
    if(aTrack->GetCreatorProcess()) {
      if(aTrack->GetCreatorProcess()->GetProcessName()=="PhotonInelastic") {
	m_photoNuclearIniPosZ[m_photoNuclearIniNum]=(aTrack->GetPosition()).z();
	std::string volName = std::string( (aTrack->GetVolume()->GetName()).data() );
	m_photoNuclearIniDetectorID[m_photoNuclearIniNum]= pm->getDetectorIDByPhysicalVolumeName(volName);
	m_photoNuclearIniNum++;
      }
    }
    //neutron track
    if(aTrack->GetDefinition()==G4Neutron::Neutron()) {
      m_neutronIniPosZ[m_neutronIniNum]=(aTrack->GetPosition()).z();
      std::string volName = std::string( (aTrack->GetVolume()->GetName()).data() );
      m_neutronIniDetectorID[m_neutronIniNum]= pm->getDetectorIDByPhysicalVolumeName(volName);
      std::string prcName = std::string ( (aTrack->GetCreatorProcess()->GetProcessName()).data() );
      m_neutronIniCreProcessID[m_neutronIniNum]=pm->getProcessIDByName(prcName);
      m_neutronIniE[m_neutronIniNum]=aTrack->GetKineticEnergy()/MeV;
      m_neutronIniNum++;
    }
  }
  return true;
}

bool GsimPbScintillator::postTrackingAction(const G4Track* aTrack) {
  //PN origin track
  if(m_userFlag==1) {
    GsimPersistencyManager* pm= GsimPersistencyManager::getPersistencyManager();
    if(aTrack->GetCreatorProcess()) {
      if(aTrack->GetCreatorProcess()->GetProcessName()=="PhotonInelastic") {
	m_photoNuclearFinPosZ[m_photoNuclearFinNum]=(aTrack->GetPosition()).z();
	std::string volName = std::string( (aTrack->GetVolume()->GetName()).data() );
	m_photoNuclearFinDetectorID[m_photoNuclearFinNum]= pm->getDetectorIDByPhysicalVolumeName(volName);
	m_photoNuclearFinNum++;
      }
    }
    
    //neutron track
    if(aTrack->GetDefinition()==G4Neutron::Neutron()) {
      m_neutronFinPosZ[m_neutronFinNum]=(aTrack->GetPosition()).z();
      std::string volName = std::string( (aTrack->GetVolume()->GetName()).data() );
      m_neutronFinDetectorID[m_neutronFinNum]= pm->getDetectorIDByPhysicalVolumeName(volName);
      m_neutronFinE[m_neutronFinNum]=aTrack->GetKineticEnergy()/MeV;
      if(m_neutronFinDetectorID[m_neutronFinNum]==0) {
	m_neutronWorldN[0]+=1;
      }
      m_neutronFinNum++;
    }
  }
  return true;
}
