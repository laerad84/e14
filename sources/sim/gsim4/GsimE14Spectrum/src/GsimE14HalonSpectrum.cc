/**
 *  @file
 *  @brief  GsimE14HalonSpectrum
 *  $Id: $
 *  $Log: $
 */
#include "GsimE14Spectrum/GsimE14HalonSpectrum.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimPersistency/GsimPersistencyManager.h"

#include "G4Event.hh"
#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"

#include "CLHEP/Random/Randomize.h"


#include "TLeaf.h"

#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>



GsimE14HalonSpectrum::GsimE14HalonSpectrum(std::string name)
  : GsimSpectrum(name)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  GsimPersistencyManager::getPersistencyManager()
    ->createHistogram("hE14HalonMome","hE14HalonMome [GeV/c]",
		      150,0,15);
  

  char* ev = std::getenv("E14_TOP_DIR");
  std::string datadir=ev;
  datadir+="/data/e14halon.root";

  char* etd=std::getenv("E14_HALO_N_SPECTRUM_DATA");
  if(etd) {
    datadir=etd;
  }

  std::ostringstream ostr;
  ostr << datadir << " is used for the E14 halo n spectrum data." << std::endl;
  GsimMessage::getInstance()
    ->report("info",ostr.str());
  
  tf = new TFile(datadir.c_str());
  tr = (TTree*)tf->Get("h1");

  m_all=tr->GetEntries();
  m_cnt=int(CLHEP::RandFlat::shoot()*m_all);
  
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


GsimE14HalonSpectrum::~GsimE14HalonSpectrum()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  tf->Close();
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}



void GsimE14HalonSpectrum::generateSpecial(const G4Event* anEvent)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  if(m_cnt>m_all) {
    m_cnt=0;
  }
  tr->GetEntry(m_cnt);
  m_cnt+=1;
  
  TLeaf * rl = tr->GetLeaf("hvcc1");
  TLeaf * pl = tr->GetLeaf("hpcc1");

  double x = rl->GetValue(0);
  double y = rl->GetValue(1);
  double z = 0.;

  CLHEP::Hep3Vector vtx=CLHEP::Hep3Vector(x*cm,y*cm,z*cm);

  double px = pl->GetValue(0);
  double py = pl->GetValue(1);
  double pz = pl->GetValue(2);
  
  CLHEP::Hep3Vector p=CLHEP::Hep3Vector(px*GeV,py*GeV,pz*GeV);

  ///////////////////
  double phi = CLHEP::RandFlat::shoot()*2*M_PIl;
  vtx.rotateZ(phi);
  p.rotateZ(phi);
  ///////////////////

  
  double R0=vtx.perp();
  double R1= R0 + CLHEP::RandGauss::shoot(0., std::abs(R0-5.427365*cm)*0.01);
  vtx=vtx*(R1/R0);

  double P0=p.mag();
  double P1=P0 + CLHEP::RandGauss::shoot(0., P0*0.02 );

  double Theta=p.theta();
  Theta = Theta + CLHEP::RandGauss::shoot(0., Theta*0.01 );

  double Phi=p.phi();
  Phi = Phi + CLHEP::RandGauss::shoot(0., Phi*0.001 );
  
  px = P1 * sin(Theta) * cos(Phi);
  py = P1 * sin(Theta) * sin(Phi);
  pz = P1 * cos(Theta);
  p = CLHEP::Hep3Vector(px, py, pz);

  
  G4PrimaryVertex* pv = anEvent->GetPrimaryVertex(0);
  pv->SetPosition(vtx.x(), vtx.y(),vtx.z());
  G4PrimaryParticle*    particle    = pv->GetPrimary();
  particle->SetMomentum(p.x(),p.y(),p.z());

  GsimPersistencyManager::getPersistencyManager()
    ->fillHistogram("hE14HalonMome",p.mag());
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}



