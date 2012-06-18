/**
 *  $Id: $
 *  $Log:$
 */

#include "GsimKernel/GsimRootRandom.h"
#include "TClass.h"

#include "CLHEP/Random/Randomize.h"
#include "CLHEP/Random/engineIDulong.h"

TRandom *gRandom = new GsimRootRandom();


GsimRootRandom::GsimRootRandom(UInt_t seed)
{
  SetName("GsimRootRandom");
  SetTitle("Random number generator: Mersenne Twistor");
  SetSeed(seed);
}

GsimRootRandom::~GsimRootRandom()
{
  ;
}

//______________________________________________________________________________
Double_t GsimRootRandom::Rndm(Int_t)
{
  return CLHEP::RandFlat::shoot();
}

void GsimRootRandom::RndmArray(Int_t n, Float_t *array)
{
  for(Int_t i=0; i<n; i++) array[i]=(Float_t)Rndm();
}

void GsimRootRandom::RndmArray(Int_t n, Double_t *array)
{
  for(Int_t i=0; i<n; i++) array[i]=Rndm();
}

void GsimRootRandom::SetSeed(UInt_t seed)
{
  fSeed= seed;
  CLHEP::HepRandom::getTheEngine()->setSeed(seed,0);
}

