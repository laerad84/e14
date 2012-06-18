/**
 *  @file
 *  @brief  GsimE14HalonSpectrum
 *  $Id: $
 *  $Log: $
 */
#ifndef GsimE14HalonSpectrum_h
#define GsimE14HalonSpectrum_h

#include "GsimKernel/GsimSpectrum.h"
#include <string>
#include <vector>
#include <map>

#include "CLHEP/Vector/ThreeVector.h"

#include "TFile.h"
#include "TTree.h"

#ifndef M_PIl
# define M_PIl          3.1415926535897932384626433832795029L  /* pi */
#endif

class G4Event;

class GsimE14HalonSpectrum : public GsimSpectrum
{
 public:
  GsimE14HalonSpectrum(std::string name);
  virtual ~GsimE14HalonSpectrum();

 protected:
  GsimE14HalonSpectrum();
  virtual void   generateSpecial(const G4Event* anEvent);

  TFile* tf;
  TTree* tr;
  int m_cnt;
  int m_all;
};

#endif // GsimE14HalonSpectrum_h
