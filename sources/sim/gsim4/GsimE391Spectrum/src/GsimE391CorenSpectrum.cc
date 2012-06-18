/**
 *  @file
 *  @brief  GsimE391CorenSpectrum
 *  $Id: $
 *  $Log: $
 */
#include "GsimE391Spectrum/GsimE391CorenSpectrum.h"
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


GsimE391CorenSpectrum::GsimE391CorenSpectrum(std::string name)
  : GsimSpectrum(name)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  char* ev = std::getenv("E14_TOP_DIR");
  std::string datadir=ev;
  datadir+="/data/e391coren.root";

  
  char* etd=std::getenv("E391_CORE_N_SPECTRUM_DATA");
  if(etd) {
    datadir=etd;
  }

  std::ostringstream ostr;
  ostr << datadir << " is used for the E391 core n spectrum data." << std::endl;
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


GsimE391CorenSpectrum::~GsimE391CorenSpectrum()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  tf->Close();
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}



void GsimE391CorenSpectrum::generateSpecial(const G4Event* anEvent)
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
GsimE391CorenSpectrum::HaloNeutronEvent(CLHEP::Hep3Vector& pout, CLHEP::Hep3Vector& vout)
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
GsimE391CorenSpectrum::HaloNeutronGen2(CLHEP::Hep3Vector& p, CLHEP::Hep3Vector& vtx)
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

  
  

  double rphi = CLHEP::RandFlat::shoot()*2*M_PIl;

  double xx = Rr*cos(rphi);
  double yy = Rr*sin(rphi);
  double z_c6exit = -199.5;
  vtx = CLHEP::Hep3Vector(xx, yy, z_c6exit);
  
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

