/**
 *  $Id: 
 *  $Log:
 */

#include "GsimE14Spectrum/GsimE14SurveySpectrum.h"
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




GsimE14SurveySpectrum::GsimE14SurveySpectrum(std::string name)
  : GsimE14Spectrum(name)
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
		      pKLSurveyDist,0,10*GeV,1);
  m_pKLFunc->SetNpx(1000);
  m_pKLFunc->SetParameter(0,m_z);
  m_mode = 1;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


GsimE14SurveySpectrum::~GsimE14SurveySpectrum()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  
  delete m_pKLFunc;
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}



void GsimE14SurveySpectrum::generateSpecial(const G4Event* anEvent)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  G4PrimaryVertex* pv = anEvent->GetPrimaryVertex(0);
  G4ThreeVector vPos = pv->GetPosition();
  double z=vPos.z();

  double PKaon = getKaonMomentum(z);

  double zStart = z;
  double xStart = 0;
  double yStart = 0;
  
  double cost=0;
  double sint=0;
  double phi=0;

  getSquareProfile(zStart,xStart,yStart,
		   cost,sint,phi);

  
  G4ThreeVector vtx(xStart,yStart,zStart);
  
  G4ThreeVector  Kdir(sint*cos(phi),sint*sin(phi),cost);
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


double GsimE14SurveySpectrum::pKLSurveyDistExit( double Pk )
{
  Pk=Pk/GeV;
  //Pk[GeV/c]
  //30-GeV proton on Pt target
  //After 7-cm Pb absorber 
  //Fitted by Shiomi by using measured data

  //Yield
  //Ni Target: (1.94 +-0.05 +0.16-0.15)*1e7
  //Pt Target: (4.19 +00.09 +0.32-0.26)*1e7
  
  double pKLDistExitPar[5] =
    { 1.74e8 ,
      1.37e+00 ,
      7.48e-01 ,
      -2.95e-01 ,
      1.68e-04 } ;  // MC(geant3) pt target result 2011/06/28
  

  double sigma = pKLDistExitPar[2]*( 1 - (pKLDistExitPar[3] + Pk*pKLDistExitPar[4])*(Pk-pKLDistExitPar[1]) );
  double yval = pKLDistExitPar[0]*
    std::exp(-0.5*(Pk-pKLDistExitPar[1])*(Pk-pKLDistExitPar[1])/(sigma*sigma));
  
  double val =  yval;
  val=val/pKLDistExitPar[0];
  return val;
}

double GsimE14SurveySpectrum::pKLSurveyDist(double* x,double* par)
{
  //x[0]: Pk with unit
  //par[0]: dZ with unit
  return pKLSurveyDistExit(x[0])*pKLWeight(x[0],par[0]);
}

