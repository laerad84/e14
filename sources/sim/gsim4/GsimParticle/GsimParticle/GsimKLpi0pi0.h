/**
 *  @file
 *  @brief  GsimKLpi0pi0
 *  $Id: GsimKLpi0pi0.h,v 1.3 2006/12/06 19:25:52 nanjo Exp $
 *  $Log: GsimKLpi0pi0.h,v $
 *  Revision 1.3  2006/12/06 19:25:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimKLpi0pi0_h
#define GsimKLpi0pi0_h

//includes
#include "globals.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"

//forward declaration


/**
 *  @class GsimKLpi0pi0
 *  @brief This class provides the KL0->pi0pi0 decay.
 */

class GsimKLpi0pi0 : public G4ParticleDefinition
{
 private:
   /**
    *  @brief The instance of this.
    */
   static GsimKLpi0pi0* theInstance;
   /**
    *  @function GsimKLpi0pi0
    *  @brief Constructor for GsimKLpi0pi0
    */
   GsimKLpi0pi0(){}
   /**
    *  @function ~GsimKLpi0pi0
    *  @brief Destructor for GsimKLpi0pi0
    */
   ~GsimKLpi0pi0(){}

 public:
   /**
    *  @function Definition
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    */
   static GsimKLpi0pi0* Definition();
   /**
    *  @function KLpi0pi0Definition
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    *
    *  This is the same as Definition().
    */
   static GsimKLpi0pi0* KLpi0pi0Definition();
   /**
    *  @function KLpi0pi0
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    *
    *  This is the same as Definition().
    */
   static GsimKLpi0pi0* KLpi0pi0();
};

#endif // GsimKLpi0pi0_h
