/**
 *  @file
 *  @brief  GsimE391CorenSpectrum
 *  $Id: $
 *  $Log: $
 */
#ifndef GsimE391CorenSpectrum_h
#define GsimE391CorenSpectrum_h

#include "GsimKernel/GsimSpectrum.h"
#include <string>
#include <vector>
#include <map>

#include "CLHEP/Vector/ThreeVector.h"

#include "TFile.h"
#include "TTree.h"
#include "TLeaf.h"

#ifndef M_PIl
# define M_PIl          3.1415926535897932384626433832795029L  /* pi */
#endif

class G4Event;

class GsimE391CorenSpectrum : public GsimSpectrum
{
 public:
  GsimE391CorenSpectrum(std::string name);
  virtual ~GsimE391CorenSpectrum();

 protected:
  GsimE391CorenSpectrum();
  virtual void   generateSpecial(const G4Event* anEvent);

  void HaloNeutronEvent(CLHEP::Hep3Vector& pout, CLHEP::Hep3Vector& vout);
  void HaloNeutronGen2(CLHEP::Hep3Vector& p, CLHEP::Hep3Vector& vtx);
  TFile* tf;
  TTree* tr;
  int nhalo;
  int ihalo;
};

#endif // GsimE391CorenSpectrum_h
