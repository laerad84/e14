/**
 *  @file
 *  @brief  GsimKL3pi0
 *  $Id: GsimKL3pi0.h,v 1.3 2006/12/06 19:25:52 nanjo Exp $
 *  $Log: GsimKL3pi0.h,v $
 *  Revision 1.3  2006/12/06 19:25:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimKL3pi0_h
#define GsimKL3pi0_h

//includes
#include "globals.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"

//forward declaration


/**
 *  @class GsimKL3pi0
 *  @brief This class provides the KL0->pi0pi0pi0 decay.
 */

class GsimKL3pi0 : public G4ParticleDefinition
{
 private:
   /**
    *  @brief The instance of this.
    */
   static GsimKL3pi0* theInstance;
   /**
    *  @function GsimKL3pi0
    *  @brief Constructor for GsimKL3pi0
    */
   GsimKL3pi0(){}
   /**
    *  @function ~GsimKL3pi0
    *  @brief Destructor for GsimKL3pi0
    */
   ~GsimKL3pi0(){}

 public:
   /**
    *  @function Definition
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    */
   static GsimKL3pi0* Definition();
   /**
    *  @function KL3pi0Definition
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    *
    *  This is the same as Definition().
    */
   static GsimKL3pi0* KL3pi0Definition();
   /**
    *  @function KL3pi0
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    *
    *  This is the same as Definition().
    */
   static GsimKL3pi0* KL3pi0();
};

#endif // GsimKL3pi0_h
