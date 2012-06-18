/**
 *  @file
 *  @brief  GsimKL2gamma
 *  $Id: GsimKL2gamma.h,v 1.3 2006/12/06 19:25:52 nanjo Exp $
 *  $Log: GsimKL2gamma.h,v $
 *  Revision 1.3  2006/12/06 19:25:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimKL2gamma_h
#define GsimKL2gamma_h

//includes
#include "globals.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"

//forward declaration


/**
 *  @class GsimKL2gamma
 *  @brief This class provides the KL0->gamma gamma decay.
 */

class GsimKL2gamma : public G4ParticleDefinition
{
 private:
   /**
    *  @brief The instance of this.
    */
   static GsimKL2gamma* theInstance;
   /**
    *  @function GsimKL2gamma
    *  @brief Constructor for GsimKL2gamma
    */
   GsimKL2gamma(){}
   /**
    *  @function ~GsimKL2gamma
    *  @brief Destructor for GsimKL2gamma
    */
   ~GsimKL2gamma(){}

 public:
   /**
    *  @function Definition
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    */
   static GsimKL2gamma* Definition();
   /**
    *  @function KL2gammaDefinition
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    *
    *  This is the same as Definition().
    */
   static GsimKL2gamma* KL2gammaDefinition();
   /**
    *  @function KL2gamma
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    *
    *  This is the same as Definition().
    */
   static GsimKL2gamma* KL2gamma();
};

#endif // GsimKL2gamma_h
