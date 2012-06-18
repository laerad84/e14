/**
 *  @file
 *  @brief  GsimKLpimunugamma
 *  $Id: GsimKLpimunugamma.h,v 1.3 2006/12/06 19:25:52 nanjo Exp $
 *  $Log: GsimKLpimunugamma.h,v $
 *  Revision 1.3  2006/12/06 19:25:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimKLpimunugamma_h
#define GsimKLpimunugamma_h

//includes
#include "globals.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"

//forward declaration


/**
 *  @class GsimKLpimunugamma
 *  @brief This class provides the KL0->pi- mu+ mu_nu gamma and KL0->pi+ mu- anti_mu_nu gamma decays.
 */

class GsimKLpimunugamma : public G4ParticleDefinition
{
 private:
   /**
    *  @brief The instance of this.
    */
   static GsimKLpimunugamma* theInstance;
   /**
    *  @function GsimKLpimunugamma
    *  @brief Constructor for GsimKLpimunugamma
    */
   GsimKLpimunugamma(){}
   /**
    *  @function ~GsimKLpimunugamma
    *  @brief Destructor for GsimKLpimunugamma
    */
   ~GsimKLpimunugamma(){}

 public:
   /**
    *  @function Definition
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    */
   static GsimKLpimunugamma* Definition();
   /**
    *  @function KLpimunugammaDefinition
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    *
    *  This is the same as Definition().
    */
   static GsimKLpimunugamma* KLpimunugammaDefinition();
   /**
    *  @function KLpimunugamma
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    *
    *  This is the same as Definition().
    */
   static GsimKLpimunugamma* KLpimunugamma();

   /**
    *  @function setDecayModel
    *  @brief Sets the decay model to use.
    *  @see GsimKLpi0nunu->setDecayModel()
    *  @param iModel The model to use.
    *
    *  This is not currently implemented.
    */
   static void setDecayModel(int iModel);
};

#endif // GsimKLpimunugamma_h
