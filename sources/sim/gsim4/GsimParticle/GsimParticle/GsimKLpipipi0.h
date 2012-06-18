/**
 *  @file
 *  @brief  GsimKLpipipi0
 *  $Id: GsimKLpipipi0.h,v 1.3 2006/12/06 19:25:52 nanjo Exp $
 *  $Log: GsimKLpipipi0.h,v $
 *  Revision 1.3  2006/12/06 19:25:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimKLpipipi0_h
#define GsimKLpipipi0_h

//includes
#include "globals.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"

//forward declaration


/**
 *  @class GsimKLpipipi0
 *  @brief This class provides the KL0->pi+pi-pi0 decay.
 */

class GsimKLpipipi0 : public G4ParticleDefinition
{
 private:
   /**
    *  @brief The instance of this.
    */
   static GsimKLpipipi0* theInstance;
   /**
    *  @function GsimKLpipipi0
    *  @brief Constructor for GsimKLpipipi0
    */
   GsimKLpipipi0(){}
   /**
    *  @function ~GsimKLpipipi0
    *  @brief Destructor for GsimKLpipipi0
    */
   ~GsimKLpipipi0(){}

 public:
   /**
    *  @function Definition
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    */
   static GsimKLpipipi0* Definition();
   /**
    *  @function KLpipipi0Definition
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    *
    *  This is the same as Definition().
    */
   static GsimKLpipipi0* KLpipipi0Definition();
   /**
    *  @function KLpipipi0
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    *
    *  This is the same as Definition().
    */
   static GsimKLpipipi0* KLpipipi0();
};

#endif // GsimKLpipipi0_h
