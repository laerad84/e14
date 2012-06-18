/**
 *  @file
 *  @brief  GsimE391HalonSpectrum
 *  $Id: $
 *  $Log: $
 */
#ifndef GsimE391HalonSpectrum_h
#define GsimE391HalonSpectrum_h

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

class GsimE391HalonSpectrum : public GsimSpectrum
{
 public:
  GsimE391HalonSpectrum(std::string name);
  virtual ~GsimE391HalonSpectrum();

 protected:
  GsimE391HalonSpectrum();
  virtual void   generateSpecial(const G4Event* anEvent);

  void HaloNeutronEvent(CLHEP::Hep3Vector& pout, CLHEP::Hep3Vector& vout);
  void HaloNeutronGen2(CLHEP::Hep3Vector& p, CLHEP::Hep3Vector& vtx);
  TFile* tf;
  TTree* tr;
  int nhalo;
  int ihalo;
};

#endif // GsimE391HalonSpectrum_h
