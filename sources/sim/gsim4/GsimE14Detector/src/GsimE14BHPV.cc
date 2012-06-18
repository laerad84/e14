/**
 *  @file
 *  @brief  GsimE14BHPV
 *  $Id: GsimE14BHPV.cc,v 1.3 2006/12/06 19:04:45 nanjo Exp $ 
 *  $Log: GsimE14BHPV.cc,v $
 *  Revision 1.3  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimE14Detector/GsimE14BHPV.h"
#include "GsimE14Detector/GsimE14UserGeom.h"
#include "GsimDetector/GsimBox.h"
#include "GsimKernel/GsimSensitiveDetector.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimTools/GsimWinstonCone.h"
#include "GsimPersistency/GsimMessage.h"

#include "CLHEP/Random/Randomize.h"

#include "G4Step.hh"
#include "G4OpticalPhoton.hh"
#include "G4ThreeVector.hh"
#include "G4VTouchable.hh"
#include "G4NavigationHistory.hh"

#include <list>

using namespace E14;

GsimE14BHPV::GsimE14BHPV(std::string name,
			 GsimDetector* motherDetector,
			 G4ThreeVector transV,G4ThreeVector rotV,
			 int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{

  m_className = "GsimE14BHPV";
  // BHPV

  // Photon Veto
  if(userFlag-int(userFlag/10)*10>0) {
    m_opticalMode=true;
  } else {
    m_opticalMode=false;
  }

  if(m_opticalMode) {
    GsimUtil::getUtil()->addCerenkov();
  }
  
  m_lenXY    =  30.0;//[cm]
  m_lenTile  =  5.0;//[cm]
  m_pbThick  =  0.2; // 2 mmt  Pb
  m_agThick  =  5.0; // 5 cmt  Aerogel

  m_gap1Thick=0.2;//[cm]
  m_gap2Thick=0.1;//[cm]
  m_mirrorSpace=30;//[cm]
  m_plateThick=0.1;//[cm]
  m_mirrorAngle=135;//[cm]
  m_gapOBoxWCone=0.5;//[cm]
  m_dInWCone=30.;//[cm]
  m_dOutWCone=12.;//[cm]
  m_gapWConePMT=1.;//[cm]
  m_rPMT=5.5;//[cm]

  m_transmittanceWrap=0.9;
  m_reflectanceMirror=0.9;
  m_reflectanceWall=0.8;
  m_reflectanceWCone=0.85;
  
  for(int k=0;k<3;k++) { 
    m_reflectanceAGWall[k]=0.8;
  }
  for(int k=0;k<3;k++) { 
    m_nMaxReflectionAGWall[k]=0;
  }
  for(int k=0;k<3;k++) {
    m_nReflectionAGWall[k]=0;
  }
  m_nReflectionOBoxWall=0;
  m_nReflectionMirror=0;
  m_nReflectionWConeWall=0;

  m_pathLengthAG=0.;
  m_pathLengthOBox=0.;
  m_pathLengthWCone=0.;
  m_pathLengthAir=0.;

  m_refractiveIndexAG =1.05;
  //m_refractiveIndexAG =1.046;

  m_QEmisc=0.76;//overall efficiency
  //m_QEmisc=0.8923;
  
  m_nLayer=25;


  m_winstonCone = new GsimWinstonCone(m_dInWCone,m_dOutWCone);
  
  double  len_mod=
    m_plateThick+
    m_pbThick+
    m_plateThick+
    m_gap1Thick+
    m_gap2Thick+
    m_agThick+
    m_mirrorSpace+
    m_gap1Thick+
    m_plateThick;//36cm


  char nam[100];
  GsimBox* boxMod =0;
  for(int i=0;i<m_nLayer;i++) {
    double z=-(len_mod*m_nLayer)/2.+len_mod*i;
    if(boxMod==0) {
      std::sprintf(nam,"BHPVMOD");
      std::vector<double> paramVec;
      paramVec.push_back(m_lenXY*cm);
      paramVec.push_back(m_lenXY*cm);
      paramVec.push_back(len_mod*cm);
      boxMod = new GsimBox(std::string(nam),this,
			   G4ThreeVector(0,0,z*cm),
			   G4ThreeVector(0,0,0));
      boxMod->setParameters(paramVec);
      boxMod->setOuterMaterial("G4_AIR");
      boxMod->setOuterCopyNo(i);
      boxMod->setOuterVisibility(false);
      addDaughter(boxMod);
      m_detList.push_back(boxMod);
    } else {
      boxMod->cloneDetector(G4ThreeVector(0,0,z*cm),
			    G4ThreeVector(0,0,0),
			    i);
    }
  }
  

  {
    std::vector<double> paramVec;
    paramVec.push_back(m_lenXY*cm);
    paramVec.push_back(m_lenXY*cm);
    paramVec.push_back(m_plateThick*cm);
    sprintf(nam,"BHPVPL");
    double z= -len_mod/2.+m_plateThick/2.;
    GsimBox* box = new GsimBox(std::string(nam),boxMod,
			       G4ThreeVector(0,0,z*cm),
			       G4ThreeVector(0,0,0));
    box->setParameters(paramVec);
    box->setOuterMaterial("G4_Fe");
    box->setOuterColor("gray70");
    box->setOuterCopyNo(-1);
    boxMod->addDaughter(box);
    m_detList.push_back(box);

    z = -len_mod/2.+
      m_plateThick+
      m_pbThick+
      m_plateThick/2.;
    box->cloneDetector(G4ThreeVector(0,0,z*cm),
		       G4ThreeVector(0,0,0),0);

    z = +len_mod/2.-m_plateThick/2.;
    box->cloneDetector(G4ThreeVector(0,0,z*cm),
		       G4ThreeVector(0,0,0),0);
  }


  {
    std::vector<double> paramVec;
    paramVec.push_back(m_lenXY*cm);
    paramVec.push_back(m_lenXY*cm);
    paramVec.push_back(m_pbThick*cm);
    sprintf(nam,"BHPVPB");
    double z= -len_mod/2.+m_plateThick+m_pbThick/2.;
    GsimBox* box = new GsimBox(std::string(nam),boxMod,
			       G4ThreeVector(0,0,z*cm),
			       G4ThreeVector(0,0,0));
    box->setParameters(paramVec);
    box->setOuterMaterial("G4_Pb");
    box->setOuterColor("gray50");
    box->setOuterCopyNo(-1);
    boxMod->addDaughter(box);
    m_detList.push_back(box);
  }

  {
    std::vector<double> paramVec;
    paramVec.push_back(m_lenXY*cm);
    paramVec.push_back(m_lenXY*cm);
    paramVec.push_back(m_agThick*cm);
    sprintf(nam,"BHPVAG");
    double z= -len_mod/2.+
      m_plateThick+
      m_pbThick+
      m_plateThick+
      m_gap1Thick+
      m_gap2Thick+
      m_agThick/2.;
    GsimBox* box = new GsimBox(std::string(nam),boxMod,
                               G4ThreeVector(0,0,z*cm),
                               G4ThreeVector(0,0,0));
    box->setParameters(paramVec);
    if(m_opticalMode) {
      box->setOuterMaterial("GsimOpticalAerogel");
    } else {
      box->setOuterMaterial("GsimAerogel");
    }
    box->setOuterColor("yellow");
    box->setSensitiveDetector("BHPV",-1,false,true,this);
    boxMod->addDaughter(box);
  }
  setThisAndDaughterBriefName("BHPV");

  
  if(m_opticalMode) {
    std::list<GsimSensitiveDetector*> sdList=getThisAndDaughterSensitiveDetectorList();  
    for(std::list<GsimSensitiveDetector*>::iterator it=sdList.begin();
	it!=sdList.end();it++) {
      std::string sdName=(*it)->getName();
      if(sdName == "BHPV") {
	(*it)->setTdcThreshold(0.5);
	(*it)->setSensitiveMode(opticalPhotonSensitiveFastMode);
      }
    }
  }
  
}

GsimE14BHPV::~GsimE14BHPV()
{
  delete m_winstonCone;
}

void GsimE14BHPV::setFastSimulationLevel(int level)
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
  }

  //set
  if(level==6) {
    for(std::list<GsimDetector*>::iterator it=m_detList.begin();
	it!=m_detList.end();it++) {
      (*it)->setSensitiveDetector("BHPV",-1,true);
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

double GsimE14BHPV::getBHPVLength() {

  double pbThick  =  0.2; // 2 mmt  Pb
  double agThick  =  5.0; // 5 cmt  Aerogel
  double gap1Thick=0.2;//[cm]
  double gap2Thick=0.1;//[cm]
  double mirrorSpace=30;//[cm]
  double plateThick=0.1;//[cm]
  
  double  len_mod=
    plateThick+
    pbThick+
    plateThick+
    gap1Thick+
    gap2Thick+
    agThick+
    mirrorSpace+
    gap1Thick+
    plateThick;//36cm
  int nLayer=25;
  
  return len_mod*nLayer;
}



void GsimE14BHPV::processHits(const G4Step* aStep,G4TouchableHistory* ROhist)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  G4Track*              track    = aStep->GetTrack();
  G4ParticleDefinition* particle = track->GetDefinition();

  //Treat only optical photon
  if(particle!=G4OpticalPhoton::OpticalPhotonDefinition()) return;

  traceFromInsideAerogel(aStep,ROhist);
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimE14BHPV::traceFromInsideAerogel(const G4Step* aStep,G4TouchableHistory* ROhist)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  //Set undetected as default
  const_cast<G4Step*>(aStep)->SetTotalEnergyDeposit(0);
  m_pathLengthAir=0.;
  
  double hbarc=197.327053;//ev nm
  double energy=aStep->GetPreStepPoint()->GetKineticEnergy()/eV;//eV
  double waveL=2.*M_PI*hbarc/energy;//nm

  //Local pos and mom in Aerogel
  double pPos[3]={0,0,0};
  double pVec[3]={0,0,0};
  translateFromGlobalToAG(aStep,pPos,pVec);

  //hisotry of raytraced points --> store in vector<double>
  //       ----> coordinate transform
  //  with debug flag
  //debug with TGraph

  //normalization
  double mag=std::sqrt(
		       std::pow(pVec[0],2.)+
		       std::pow(pVec[1],2.)+
		       std::pow(pVec[2],2.));
  if(mag==0) return;//error
  for(int k=0;k<3;k++) {
    pVec[k]/=mag;
  }
  
  
  //RayTrace within Aerogel with AG coordinate
  bool isTraced = traceAerogel(waveL,pPos, pVec);
  if(!isTraced) return;
  
  //RayTrace in Optical Box
  pPos[2]=-1.*m_mirrorSpace/2.;// explicitly assign front z position of OBox 
  
  
  // RayTrace within OBox(mirror space) with OBox coordinate
  isTraced=traceOpticalBox(waveL,pPos, pVec);
  if(!isTraced) return;

  //RayTrace in WinstonCone
  // trans to WCone coordinate from OBOX coordinate
  translateFromOBoxToWCone(pPos,pVec);
  // RayTrace within WinstonCone with WinstonCone coordinate
  isTraced=traceWCone(waveL,pPos, pVec);
  if(!isTraced) return;

  //Hit decision at PMT
  // trans to OBox coordinate from WCone coordinate
  translateFromWConeToOBox(pPos, pVec);
  //PMT phtocathod is 1cm far from PMT face
  double dGapPath=-1.*m_gapWConePMT/pVec[1];
  for(int k=0;k<3;k++) {
    pPos[k]=pPos[k]+pVec[k]*dGapPath;
  }
    
  m_pathLengthAir=
    m_pathLengthOBox+
    m_pathLengthWCone+dGapPath;
	
  double angleinPMT=std::atan(std::sqrt(std::pow(pVec[0],2.)+std::pow(pVec[2],2.))/pVec[1]);
  //     === on Detection Plane at Y=yPMT
  //     --- circular gate for PMT
  if (std::sqrt(std::pow(pPos[0],2.)+std::pow(pPos[2],2.))>m_rPMT) {
    isTraced=false;
  }
  if(!isTraced) return;

  {
    //hit inside PMT cathode
    //Q.E. check
    double rnd=CLHEP::RandFlat::shoot();
    if ( rnd > m_QEmisc*getPMTQE(waveL) ) {
      isTraced=false;
    }
  }
  if(!isTraced) return;
	
  {
    //Detected(PhotoElectron is generated)
    const_cast<G4Step*>(aStep)->SetTotalEnergyDeposit(1.*MeV);
    
    //timing calculation with TOF
    double cLight=29.9792458;// [cm/nsec]
    double dt=
      m_pathLengthAG/cLight/m_refractiveIndexAG+
      m_pathLengthAir/cLight;
    
    G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
    double time=preStepPoint->GetGlobalTime()/ns;
    preStepPoint->SetGlobalTime( (time+dt)*ns );
  }
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif 
}

double GsimE14BHPV::dNextAbsorption(double waveL)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  //waveL[nm]
  //  according to NIM A440 (2000) 338  //
  double A=0.96;
  double CT=0.0082;

  //  cutoff wavelength (by hand)  //
  if (waveL<300.) {
    return 0;
  }
  
  double lambda=-1./log(A);
  double rnd=CLHEP::RandFlat::shoot();
  double d=-log(rnd)*lambda;
  return d;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

double GsimE14BHPV::dNextScattering(double waveL)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  double A=0.96;
  double CT=0.0082;
  double lambda=1./(CT/std::pow(waveL*1e-3,4.));
  double rnd=CLHEP::RandFlat::shoot();
  double d=-log(rnd)*lambda;
  return d;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimE14BHPV::scatterInAerogel(double* pVec)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  double cth=0.;
  while(1) {
    double rnd0=CLHEP::RandFlat::shoot();
    double rnd1=CLHEP::RandFlat::shoot();
    double cth=1.-2.*rnd0;
    if(rnd1<=(1.+std::pow(cth,2.))/2.) break;
  }
  double sth=sqrt(1.-std::pow(cth,2.));
  double rnd=CLHEP::RandFlat::shoot();
  double cphi=cos(2.*M_PI*rnd);
  double sphi=sin(2.*M_PI*rnd);

  
  
  G4ThreeVector vec(pVec[0],pVec[1],pVec[2]);
  double COSTH=vec.cosTheta();
  double SINTH=std::sqrt(1.-std::pow(COSTH,2.));
  double fac=1./std::sqrt(std::pow(pVec[0],2.)+std::pow(pVec[1],2.));
  double COSPH=fac*pVec[0];
  double SINPH=fac*pVec[1];

  double P1=sth*cphi;
  double P2=sth*sphi;
  double P3=cth;
  
  pVec[0]=P1*COSTH*COSPH - P2*SINPH + P3*SINTH*COSPH;
  pVec[1]=P1*COSTH*SINPH + P2*COSPH + P3*SINTH*SINPH;
  pVec[2]=P1*SINTH                 + P3*COSTH;

#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  
  return;
}


bool GsimE14BHPV::traceAerogel(double waveL,double* pPos, double* pVec)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  bool isReach=false;
  bool isRefU=false;
  bool isScat=false;
  
  double dNextAbs=dNextAbsorption(waveL);
  double dNextSc =dNextScattering(waveL);
  double pPosS[3]={0,0,0};
  double dAGTile[3]={m_lenXY/2.,m_lenXY/2.,m_agThick/2.};
  
  for(int k=0;k<3;k++) {
    m_nReflectionAGWall[k]=0;
  }
  m_pathLengthAG=0.;
  
  while(!isReach) {
    ////////////////////////////////////////////////
    //Scattering at Tile boundary
    //Wrong?
    for(int k=0;k<3;k++) {
      pPosS[k]=pPos[k]+dNextSc*pVec[k];
      if ((pPos[k]-5.)*(pPosS[k]-5.) < 0.) {
	double frac = std::abs(pPos[k] - 5) / std::abs(pPosS[k]-pPos[k]);
	dNextSc = frac * dNextSc;
      }
      pPosS[k]=pPos[k]+dNextSc*pVec[k];
      if ((pPos[k]+5.)*(pPosS[k]+5.) < 0.) {
	double frac = std::abs(pPos[k] + 5) / std::abs(pPosS[k]-pPos[k]);
	dNextSc = frac * dNextSc;
      }
    }
    ////////////////////////////////////////////////

    ////////////////////////////////////////////////
    //1 Step
    double dStep=0;
    double zNext=pPos[2]+std::min(dNextAbs,dNextSc)*pVec[2];
    if (zNext > dAGTile[2]) {
      //--- reach to downstream end
      isReach=true;
      dStep=( dAGTile[2]-pPos[2])/pVec[2];
    } else if(zNext<-dAGTile[2]) {
      //--- go back to upstream end
      isRefU=true;
      m_nReflectionAGWall[2]+=1;
      if (m_nReflectionAGWall[2]>m_nMaxReflectionAGWall[2]) {
	return false;
      }
      dStep=(-dAGTile[2]-pPos[2])/pVec[2];
      dNextAbs=dNextAbs-dStep;
      dNextSc =dNextSc -dStep;
    } else {
      //--- absorbed or scatttered at somewhere in tile
      if (dNextAbs<dNextSc) {
	return false;	//discard if absorbed
      }
      isScat=true;
      dStep=dNextSc;
      dNextAbs=dNextAbs-dStep;
      dNextSc =dNextScattering(waveL);
    }

    //--- proceed to next point
    pPos[2]=dStep*pVec[2]+pPos[2];
    for(int k=0;k<2;k++) {
      pPos[k]=dStep*pVec[k]+pPos[k];
      
      if (std::abs(pPos[k])>dAGTile[k]) {
	int nRthis=int((std::abs(pPos[k])+dAGTile[k])/(dAGTile[k]*2.));
	m_nReflectionAGWall[k]+=nRthis;
	if (m_nReflectionAGWall[k]>m_nMaxReflectionAGWall[k]) return false;
	if (pPos[k]<0.) {
	  pPos[k]=pPos[k]+dAGTile[k]*2.*nRthis;
	} else {
	  pPos[k]=pPos[k]-dAGTile[k]*2.*nRthis;
	}
	pPos[k]=pPos[k]*std::pow((-1.),nRthis);
	pVec[k]=pVec[k]*std::pow((-1.),nRthis);
      }
    }

    if (isRefU) pVec[2]=-pVec[2];
    if (isScat) scatterInAerogel(pVec);
    m_pathLengthAG+=dStep;
  }

  //Dead in reflection in AG wall
  for(int k=0;k<3;k++) {
    double rnd=CLHEP::RandFlat::shoot();
    if (rnd>std::pow(m_reflectanceAGWall[k],m_nReflectionAGWall[k])) 
      return false;
  }


  //Dead in wrap transmittance
  {
    double rnd=CLHEP::RandFlat::shoot();
    if ( rnd>m_transmittanceWrap ) {
      return false;
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return true;
}

bool GsimE14BHPV::traceOpticalBox(double waveL,double* pPos, double* pVec)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  m_pathLengthOBox=0.;
  m_nReflectionOBoxWall=0;
  m_nReflectionMirror=0;
  
  double OBOXd[3]=
    {
      m_lenXY/2.,
      m_lenXY/2.,
      m_mirrorSpace/2.
    };
  //           20      5/2?
  //OBOXd(3)=zAC2PMT-ATILd(3)*2.

  

  //////////////////////////////////////////////////////////////
  // === in Optical Cell
  double dSafe=0.0001;//1um
  double rad=M_PI*m_mirrorAngle/180.;
  double nVecmir[3]=
    {0.,
     std::cos(rad),
     -1. * std::sin(rad)
    };
  
  
  int ctr=0;
  bool isReach=false;
  while(!isReach) {
    ctr=ctr+1;
    if (pPos[2] < -1.*OBOXd[2]) {
      return false;//upstream of OBOX
    }
    if (ctr>10) {
      return false;//too many bounce
    }
    
    double lenmir=-(pPos[1]-pPos[2]*std::tan(rad))/(pVec[1]-pVec[2]*std::tan(rad));
    double lenside=0.;
    if (pVec[0]>0.) {
      lenside=(OBOXd[0]-pPos[0])/pVec[0];
    } else {
      lenside=(-OBOXd[0]-pPos[0])/pVec[0];
    }

    double lenholiz=0.;
    if (pVec[1]>0.) {
      lenholiz=(OBOXd[1]-pPos[1])/pVec[1];
    } else {
      lenholiz=(-OBOXd[1]-m_gapOBoxWCone-pPos[1])/pVec[1];
    }

    if (
	(lenmir<lenside) &&
	(lenmir<lenholiz) &&
	(lenmir>dSafe)        //0.0001 Why?
	) {
      double ndotv=0.;
      for(int k=0;k<3;k++) {
	ndotv=ndotv+pVec[k]*nVecmir[k];
      }
      ndotv=std::abs(ndotv);
      for(int k=0;k<3;k++) {
	pPos[k]=pPos[k]+lenmir*pVec[k];
	pVec[k]=pVec[k]+ndotv*nVecmir[k]*2.0;
      }
      m_nReflectionMirror++;
      m_pathLengthOBox+=lenmir;
    } else if (
	       (lenside<lenholiz) &&
	       (lenside>dSafe)
	       ) {
      for(int k=0;k<3;k++) {
	pPos[k]=pPos[k]+lenside*pVec[k];
      }
      pVec[0]=-pVec[0];
      m_nReflectionOBoxWall++;
      m_pathLengthOBox+=lenside;
    } else if (
	       (lenholiz>dSafe) &&
	       (pVec[1]<0.)
	       ) {
      for(int k=0;k<3;k++) {
	pPos[k]=pPos[k]+lenholiz*pVec[k];
      }
      isReach=true;
    } else if (lenholiz>dSafe) {
      for(int k=0;k<3;k++) {
	pPos[k]=pPos[k]+lenholiz*pVec[k];
      }
      pVec[1]=-pVec[1];
      m_nReflectionOBoxWall++;
      m_pathLengthOBox+=lenholiz;
    } else {
      //lenholiz<dSafe
      return false;//by HN
    }
  }

  
  //Dead in reflection at Wall
  {
    double rnd=CLHEP::RandFlat::shoot();
    if ( rnd > std::pow(m_reflectanceWall,m_nReflectionOBoxWall) ) {
      return false;
    }
  }

  //Dead in main mirror
  {
    double rnd=CLHEP::RandFlat::shoot();
    if ( rnd > std::pow(m_reflectanceMirror,m_nReflectionMirror) ) {
      return false;
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  
  return true;
}


bool GsimE14BHPV::traceWCone(double waveL,double* pPos, double* pVec)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_pathLengthWCone=0;
  m_nReflectionWConeWall=0;
  bool isTraced=m_winstonCone->trace(pPos,pVec);
  m_nReflectionWConeWall=
    m_winstonCone->getNReflections();
  m_pathLengthWCone=
    m_winstonCone->getPathLength();

  //Dead in reflection at WinstonCone surface.
  if(isTraced) {
    double rnd=CLHEP::RandFlat::shoot();
    if ( rnd>std::pow(m_reflectanceWCone,m_nReflectionWConeWall) ) {
      isTraced=false;
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return isTraced;
}


double GsimE14BHPV::getPMTQE(double waveL)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  //  Blue sensitivity ratio of real PMTs to typical value (9.0)  //
  //       Average of 6 PMTs delivered in 2001/2002 = 9.7  -> R=1.08
  double R2TYP=1.08;

  //  Typical spectral response from Hamamatsu's spec sheet
  int np=11;
  double wlx[11]=
    {
      280.0,
      300.0,
      320.0,
      340.0,
      360.0,
      380.0,
      400.0,
      450.0,
      500.0,
      550.0,
      600.0
    };
  
  double QEwlx[11]=
    {
      0.00,
      0.050,
      0.13,
      0.18,
      0.21,
      0.22,
      0.22,
      0.17,
      0.11,
      0.060,
      0.022
    };

  double QEwl=0.0;
  if (waveL<wlx[0] || waveL>wlx[np-1]) return QEwl;
  
  for(int k=0;k<np-1;k++) {
    if (waveL<wlx[k+1]) {
      QEwl = QEwlx[k]+
	(QEwlx[k+1]-QEwlx[k])/(wlx[k+1]-wlx[k])* (waveL-wlx[k]);
      QEwl /= R2TYP;
      return QEwl;
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return QEwl;
}

void GsimE14BHPV::translateFromGlobalToAG(const G4Step* aStep,double* pPos, double* pVec)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4ThreeVector globalPos=aStep->GetPreStepPoint()->GetPosition();
  G4ThreeVector globalMom=aStep->GetPreStepPoint()->GetMomentum();
  const G4VTouchable*   touch= aStep->GetPreStepPoint()->GetTouchable();
  
  G4ThreeVector agLocalPos
    =touch->GetHistory()->GetTopTransform().TransformPoint(globalPos);
  G4ThreeVector agLocalMom
    =touch->GetHistory()->GetTopTransform().TransformAxis(globalMom);
  
  pPos[0]=agLocalPos.x()/cm;
  pPos[1]=agLocalPos.y()/cm;
  pPos[2]=agLocalPos.z()/cm;
  pVec[0]=agLocalMom.x();
  pVec[1]=agLocalMom.y();
  pVec[2]=agLocalMom.z();
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimE14BHPV::translateFromAGToOBox(double* pPos, double* pVec)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  //Wrong?
  //pPos[2]=-OBOXd[2];// trans to OBOX coordinate from AG coordinate
  pPos[2]-=(m_agThick/2.+m_mirrorSpace/2.);// trans to OBOX coordinate from AG coordinate
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimE14BHPV::translateFromOBoxToWCone(double* pPos, double* pVec)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  // trans to WCone coordinate from OBOX coordinate
  double h=m_winstonCone->getHight();
  double x=-pPos[0];
  double y=pPos[2];
  double z=pPos[1]+h+m_gapOBoxWCone+m_lenXY/2.;
  double vx=-pVec[0];
  double vy=pVec[2];
  double vz=pVec[1];
  
  pPos[0]=x;
  pPos[1]=y;
  pPos[2]=z;
  pVec[0]=vx;
  pVec[1]=vy;
  pVec[2]=vz;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimE14BHPV::translateFromWConeToOBox(double* pPos, double* pVec)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  // trans to OBox coordinate from WCone coordinate
  double h=m_winstonCone->getHight();
  double x=-pPos[0];
  double y=pPos[2]-h-m_gapOBoxWCone-m_lenXY/2.;
  double z=pPos[1];
  double vx=-pVec[0];
  double vy=pVec[2];
  double vz=pVec[1];
  pPos[0]=x;
  pPos[1]=y;
  pPos[2]=z;
  pVec[0]=vx;
  pVec[1]=vy;
  pVec[2]=vz;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}
