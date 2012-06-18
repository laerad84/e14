/**
 *  @file
 *  @brief  GsimKLpipi
 *  $Id: GsimKLpipi.h,v 1.3 2006/12/06 19:25:52 nanjo Exp $
 *  $Log: GsimKLpipi.h,v $
 *  Revision 1.3  2006/12/06 19:25:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimKLpipi_h
#define GsimKLpipi_h

//includes
#include "globals.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"

//forward declaration


/**
 *  @class GsimKLpipi
 *  @brief This class provides the KL0->pi+pi- decay.
 */

class GsimKLpipi : public G4ParticleDefinition
{
 private:
   /**
    *  @brief The instance of this.
    */
   static GsimKLpipi* theInstance;
   /**
    *  @function GsimKLpipi
    *  @brief Constructor for GsimKLpipi
    */
   GsimKLpipi(){}
   /**
    *  @function ~GsimKLpipi
    *  @brief Destructor for GsimKLpipi
    */
   ~GsimKLpipi(){}

 public:
   /**
    *  @function Definition
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    */
   static GsimKLpipi* Definition();
   /**
    *  @function KLpipiDefinition
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    *
    *  This is the same as Definition().
    */
   static GsimKLpipi* KLpipiDefinition();
   /**
    *  @function KLpipi
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    *
    *  This is the same as Definition().
    */
   static GsimKLpipi* KLpipi();
};

#endif // GsimKLpipi_h
