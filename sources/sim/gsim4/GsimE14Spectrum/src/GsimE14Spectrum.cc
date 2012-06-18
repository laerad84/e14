/**
 *  $Id: GsimE14Spectrum.cc,v 1.2 2006/12/06 19:16:29 nanjo Exp $
 *  $Log: GsimE14Spectrum.cc,v $
 *  Revision 1.2  2006/12/06 19:16:29  nanjo
 *  CVS variables.
 *
 */

#include "GsimE14Spectrum/GsimE14Spectrum.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimPersistency/GsimPersistencyManager.h"

#include "G4Event.hh"
#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"


#include "CLHEP/Random/Randomize.h"

#include "TF1.h"

#include <string>
#include <vector>
#include <cmath>




GsimE14Spectrum::GsimE14Spectrum(std::string name)
  : GsimSpectrum(name)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  GsimPersistencyManager::getPersistencyManager()
    ->createHistogram("hE14Mome","hE14Mome [GeV/c]",100,0,10);
  
  m_parameter=1.;


  
  
  m_pMin=5e-2*GeV;
  m_z=1000*m;
  m_wMax=1.;
  m_pKLDistExitZ=-1*m;
  
  
  
  m_pKLFunc = new TF1("pKLFunc",
		      pKLDist,0,10*GeV,1);
  m_pKLFunc->SetNpx(1000);
  m_pKLFunc->SetParameter(0,m_z);
  m_mode=1;
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


GsimE14Spectrum::~GsimE14Spectrum()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  
  delete m_pKLFunc;
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}



void GsimE14Spectrum::getCircularProfile(double zStart,
					 double& xStart,double& yStart,
					 double& cost,double& sint,double& phi)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  double zTarget   = -21 * m;
  double dcost = 9.0e-6 / (2 * M_PI ) * m_parameter;

  cost = 1 - dcost * CLHEP::RandFlat::shoot();
  sint = std::sqrt(1 -cost*cost);
  double tant = sint/cost;
  phi =2* M_PI * CLHEP::RandFlat::shoot();
  
  xStart = tant*cos(phi) * (zStart - zTarget); 
  yStart = tant*sin(phi) * (zStart - zTarget);
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimE14Spectrum::getSquareProfile(double zStart,
				       double& xStart,double& yStart,
				       double& cost,double& sint,double& phi)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  double xColSize = 15.2/2.* mm;
  double yColSize = 25.0/2.* mm;
  double zCol     = -21*m + 7*m;

  double xTarget=0;
  double yTarget=0;
  double zTarget = -21 * m;

  double xCol=1e3 *m;
  double yCol=1e3 *m;

  while(
	!
	(xCol>  -xColSize &&
	 xCol < +xColSize &&
	 yCol > -yColSize &&
	 yCol < +yColSize
	 )
	) {
    
    xTarget = CLHEP::RandFlat::shoot(-9.1, 9.1) * mm;
    yTarget = CLHEP::RandFlat::shoot(-1., 1.) * mm;
    
    cost = CLHEP::RandFlat::shoot(cos(3.1e-3),1.);
    sint = std::sqrt(1 -cost*cost);
    phi =2* M_PI * CLHEP::RandFlat::shoot();
    
    double tCol=(zCol-zTarget)/cost;
    //Zcol = cost*t + zTarget
    xCol = sint*cos(phi)*tCol+xTarget;
    yCol = sint*sin(phi)*tCol+yTarget;
  }

  double tStart = (zStart-zTarget)/cost;
  xStart = sint*cos(phi)*tStart+xTarget;
  yStart = sint*sin(phi)*tStart+yTarget;

#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}



void GsimE14Spectrum::generateSpecial(const G4Event* anEvent)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  G4PrimaryVertex* pv = anEvent->GetPrimaryVertex(0);
  G4ThreeVector vPos = pv->GetPosition();
  double z=vPos.z();

  double PKaon = getKaonMomentum(z);

  
  double zStart = z;
  double cost = 0.;
  double sint = 0.;
  double phi  = 0.;
  double xStart = 0.;
  double yStart = 0.;

  getCircularProfile(zStart,
		     xStart,yStart,cost,sint,phi);
  
  G4ThreeVector vtx(xStart,yStart,zStart);

  G4ThreeVector  Kdir = G4ThreeVector(sint*cos(phi),sint*sin(phi),cost);
  G4ThreeVector p = Kdir * PKaon;

  
  pv->SetPosition(vtx.x(), vtx.y(),vtx.z());
  G4PrimaryParticle*    particle    = pv->GetPrimary();
  particle->SetMomentum(p.x(),p.y(),p.z());

  GsimPersistencyManager::getPersistencyManager()
    ->fillHistogram("hE14Mome",p.mag()/GeV);
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}




double GsimE14Spectrum::pKLDistExit( double Pk )
{
  Pk=Pk/GeV;
  //Pk[GeV/c]
  //30-GeV proton on Ni target
  //After 7-cm Pb absorber 
  //Fitted by Nakajima


  double pKLDistExitPar[8]=
    {
      1.78303e+03,
      1.24432e+00,
      5.39864e-01,
      -5.11454e-01,
      4.43691e-02,
      6.18994e+02,
      1.00234e+00,
      1.31606e-01
    };

  
  double sigma = pKLDistExitPar[2]*( 1 - (pKLDistExitPar[3] + Pk*pKLDistExitPar[4])*(Pk-pKLDistExitPar[1]) );
  double yval = pKLDistExitPar[0]*
    std::exp(-0.5*(Pk-pKLDistExitPar[1])*(Pk-pKLDistExitPar[1])/(sigma*sigma));
					     
  
  
  //gausian part
  double A = Pk-pKLDistExitPar[6];
  double fit_gaus =  pKLDistExitPar[5]*std::exp(- A*A/(2*pKLDistExitPar[7]*pKLDistExitPar[7]));
  
  double val =  yval-fit_gaus;
  val=val/pKLDistExitPar[0];
  return val;
}


double GsimE14Spectrum::pKLWeight( double Pk, double dZ )
{
  //maximum wieght = exp(20.)
  double MK=0.497614*GeV;
  double ctau=15.34*m;
  double weight=1.;
  double lnweight=-MK/Pk*dZ/ctau;
  if(lnweight<20.) {
    weight=std::exp(lnweight);
  } else {
    weight=std::exp(20.);
  }
  return weight;
}

double GsimE14Spectrum::getKaonMomentum(double z)
{
  //z should be larger than just after the Pb abosrber
  if(m_z!=z) {
    m_z=z;
    m_wMax=getMaximumWeight(z);
    double dZ=z-m_pKLDistExitZ;
    m_pKLFunc->SetParameter(0,dZ);
  }

  if(m_mode==1) {
    double Pk=m_pKLFunc->GetRandom();
    return Pk;
  } else {
    double dZ=z-m_pKLDistExitZ;
    double Pk=0;
    while (1) {
      Pk = 8.0* GeV *  CLHEP::RandFlat::shoot(); // GeV/c  maximam 8GeV/c
      
      double weight=pKLWeight(Pk, dZ);
      double val =  pKLDistExit( Pk )*weight;
      if (val > m_wMax*CLHEP::RandFlat::shoot() ) break;
    }
    return Pk;
  }
}


double GsimE14Spectrum::pKLDist(double* x,double* par)
{
  //x[0]: Pk with unit
  //par[0]: dZ with unit
  return pKLDistExit(x[0])*pKLWeight(x[0],par[0]);
}


double GsimE14Spectrum::getMaximumWeight(double z)
{
  
  double dZ=z-m_pKLDistExitZ;
  int N=100;
  double pMin=0.*GeV;
  double pMax=10.*GeV;
  double dP=(pMax-pMin)/(N*1.);

  int iMax=-1;
  double wMax=-1;
  double wPrev=-1;
  double wNext=-1;
  for(int j=0;j<3;j++) {
    for(int i=0;i<N;i++) {
      double Pk=dP*(i+1)+pMin;
      double w=pKLDistExit(Pk)*pKLWeight(Pk,dZ);
      if(w>wMax) {
	iMax=i;
	wMax=w;
      }
    }
    if(iMax==-1) break;
    
    if(iMax>=0) {
      pMin=(iMax)*dP+pMin;
    }
    if(iMax<N-1) {
      pMax=(iMax+2)*dP+pMin;
    }
    dP=(pMax-pMin)/(N*1.);
    wPrev=pKLDistExit(pMin)*pKLWeight(pMin,dZ);
    wNext=pKLDistExit(pMax)*pKLWeight(pMax,dZ);
  }
  if(iMax!=-1) {
    if(wPrev>wNext) {
      wMax=wMax+(wMax-wNext);
    } else {
      wMax=wMax+(wMax-wPrev);
    }
  }

  return wMax;
}
