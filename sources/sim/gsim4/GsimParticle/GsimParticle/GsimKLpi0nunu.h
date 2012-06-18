/**
 *  @file
 *  @brief  GsimKLpi0nunu
 *  $Id: GsimKLpi0nunu.h,v 1.3 2006/12/06 19:25:52 nanjo Exp $
 *  $Log: GsimKLpi0nunu.h,v $
 *  Revision 1.3  2006/12/06 19:25:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimKLpi0nunu_h
#define GsimKLpi0nunu_h

//includes
#include "globals.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"

//forward declaration


/**
 *  @class GsimKLpi0nunu
 *  @brief This class provides the KL0->pi0 nu_e anti_nu_e, KL0->pi0 nu_mu anti_nu_mu, and KL0->pi0 nu_tau anti_nu_tau decays.
 */

class GsimKLpi0nunu : public G4ParticleDefinition
{
 private:
   /**
    *  @brief The instance of this.
    */
   static GsimKLpi0nunu* theInstance;
   /**
    *  @function GsimKLpi0nunu
    *  @brief Constructor for GsimKLpi0nunu
    */
   GsimKLpi0nunu(){}
   /**
    *  @function ~GsimKLpi0nunu
    *  @brief Destructor for GsimKLpi0nunu
    */
   ~GsimKLpi0nunu(){}

 public:
   /**
    *  @function Definition
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    */
   static GsimKLpi0nunu* Definition();
   /**
    *  @function KLpi0nunuDefinition
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    *
    *  This is the same as Definition().
    */
   static GsimKLpi0nunu* KLpi0nunuDefinition();
   /**
    *  @function KLpi0nunu
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    *
    *  This is the same as Definition().
    */
   static GsimKLpi0nunu* KLpi0nunu();

   /**
    *  @function setDecayModel
    *  @brief Sets the decay model to use.
    *  @param iModel The model to use. If 0, then GsimKPiNuNuDecayChannel. If 1, then GsimKL3DecayChannel.
    */
   void   setDecayModel(int iModel);
   void   setLambdaPlus(double lambda);
   double getLambdaPlus();

 private:
   static int    s_decayModel;
   static double s_lambdaPlus;
};

#endif // GsimKLpi0nunu_h
