/**
 *  @file
 *  @brief  GsimKLpienugamma
 *  $Id: GsimKLpienugamma.h,v 1.3 2006/12/06 19:25:52 nanjo Exp $
 *  $Log: GsimKLpienugamma.h,v $
 *  Revision 1.3  2006/12/06 19:25:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimKLpienugamma_h
#define GsimKLpienugamma_h

//includes
#include "globals.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"

//forward declaration


/**
 *  @class GsimKLpienugamma
 *  @brief This class provides the KL0->pi- e+ e_nu gamma and KL0->pi+ e- anti_e_nu gamma decays.
 */

class GsimKLpienugamma : public G4ParticleDefinition
{
 private:
   /**
    *  @brief The instance of this.
    */
   static GsimKLpienugamma* theInstance;
   /**
    *  @function GsimKLpienugamma
    *  @brief Constructor for GsimKLpienugamma
    */
   GsimKLpienugamma(){}
   /**
    *  @function ~GsimKLpienugamma
    *  @brief Destructor for GsimKLpienugamma
    */
   ~GsimKLpienugamma(){}

 public:
   /**
    *  @function Definition
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    */
   static GsimKLpienugamma* Definition();
   /**
    *  @function KLpienugammaDefinition
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    *
    *  This is the same as Definition().
    */
   static GsimKLpienugamma* KLpienugammaDefinition();
   /**
    *  @function KLpienugamma
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    *
    *  This is the same as Definition().
    */
   static GsimKLpienugamma* KLpienugamma();
};

#endif // GsimKLpienugamma_h
