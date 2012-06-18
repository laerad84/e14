/**
 *  @file
 *  @brief  GsimKLbeta
 *  $Id: 
 *  $Log: 
 */
#ifndef GsimKLbeta_h
#define GsimKLbeta_h

//includes
#include "globals.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"

//forward declaration


/**
 *  @class GsimKLbeta
 */

class GsimKLbeta : public G4ParticleDefinition
{
 private:
   static GsimKLbeta* theInstance;
   GsimKLbeta(){}
   ~GsimKLbeta(){}

 public:
   static GsimKLbeta* Definition();
   static GsimKLbeta* KLbetaDefinition();
   static GsimKLbeta* KLbeta();
};

#endif // GsimKLbeta_h
