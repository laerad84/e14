/**
 *  @file
 *  @brief  GsimRootRandom
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2009.2.10
 *  $Id: $
 *  $Log:$
 */

#ifndef GsimRootRandom_h
#define GsimRootRandom_h

#include "TRandom.h"

class GsimRootRandom : public TRandom {

private:
   UInt_t   fMt[624];
   Int_t    fCount624;

public:
   GsimRootRandom(UInt_t seed=4357);
   virtual ~GsimRootRandom();
   virtual  Double_t  Rndm(Int_t i=0);
   virtual  void      RndmArray(Int_t n, Float_t *array);
   virtual  void      RndmArray(Int_t n, Double_t *array);
   virtual  void      SetSeed(UInt_t seed=0);
};

R__EXTERN TRandom *gRandom;

#endif //GsimRootRandom_h
