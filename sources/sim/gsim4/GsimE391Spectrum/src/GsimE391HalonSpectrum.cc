/**
 *  @file
 *  @brief  GsimE391HalonSpectrum
 *  $Id: $
 *  $Log: $
 */
#include "GsimE391Spectrum/GsimE391HalonSpectrum.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4Event.hh"
#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"

#include "CLHEP/Random/Randomize.h"




#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <sstream>


GsimE391HalonSpectrum::GsimE391HalonSpectrum(std::string name)
  : GsimSpectrum(name)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  char* ev = std::getenv("E14_TOP_DIR");
  std::string datadir=ev;
  datadir+="/data/e391halon.root";

  char* etd=std::getenv("E391_HALO_N_SPECTRUM_DATA");
  if(etd) {
    datadir=etd;
  }

  std::ostringstream ostr;
  ostr << datadir << " is used for the E391 halo n spectrum data." << std::endl;
  GsimMessage::getInstance()
    ->report("info",ostr.str());
  
  tf = new TFile(datadir.c_str());
  tr = (TTree*)tf->Get("tr");

  nhalo=tr->GetEntries();
  ihalo=0;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


GsimE391HalonSpectrum::~GsimE391HalonSpectrum()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  tf->Close();
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}



void GsimE391HalonSpectrum::generateSpecial(const G4Event* anEvent)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  CLHEP::Hep3Vector p;
  CLHEP::Hep3Vector vtx;

  HaloNeutronEvent(p,vtx);
  vtx=vtx*cm;
  
  G4PrimaryVertex* pv = anEvent->GetPrimaryVertex(0);
  pv->SetPosition(vtx.x(), vtx.y(),vtx.z());
  G4PrimaryParticle*    particle    = pv->GetPrimary();
  particle->SetMomentum(p.x()*GeV,p.y()*GeV,p.z()*GeV);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}



void 
GsimE391HalonSpectrum::HaloNeutronEvent(CLHEP::Hep3Vector& pout, CLHEP::Hep3Vector& vout)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  CLHEP::Hep3Vector p,v;
  HaloNeutronGen2(p, v);
  pout = p;
  vout = v;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void
GsimE391HalonSpectrum::HaloNeutronGen2(CLHEP::Hep3Vector& p, CLHEP::Hep3Vector& vtx)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  TLeaf * rr = tr->GetLeaf("rr");
  TLeaf * pp = tr->GetLeaf("pp");
  TLeaf * theta = tr->GetLeaf("theta");
  TLeaf * phim = tr->GetLeaf("phim");

  if ( ihalo >= nhalo ) {
    ihalo = 0;
  }
  tr->GetEntry(ihalo);

  double Rr = rr->GetValue(0);
  double Pp = pp->GetValue(0);
  double Theta = theta->GetValue(0);
  double Phim = phim->GetValue(0);

  // add fluctuation for R

  
  
  Rr = Rr + CLHEP::RandGauss::shoot(0., std::abs(Rr-2.45128)*0.01);
  double rphi = CLHEP::RandFlat::shoot()*2*M_PIl;

  double xx = Rr*cos(rphi);
  double yy = Rr*sin(rphi);
  double z_c6exit = -199.5;
  vtx = CLHEP::Hep3Vector(xx, yy, z_c6exit);
  
  // add fluctuation for p
  Pp = Pp + CLHEP::RandGauss::shoot(0., Pp*0.02 );
  Theta = Theta + CLHEP::RandGauss::shoot(0., Theta*0.01 );
  Phim = Phim + CLHEP::RandGauss::shoot(0., Phim*0.001 );

  double pphi = rphi + Phim;
  double px = Pp * sin(Theta) * cos(pphi);
  double py = Pp * sin(Theta) * sin(pphi);
  double pz = Pp * cos(Theta);
  p = CLHEP::Hep3Vector(px, py, pz);

  ihalo++;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

