/**
 *  @file
 *  @brief  GsimKLpimunu
 *  $Id: GsimKLpimunu.h,v 1.3 2006/12/06 19:25:52 nanjo Exp $
 *  $Log: GsimKLpimunu.h,v $
 *  Revision 1.3  2006/12/06 19:25:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimKLpimunu_h
#define GsimKLpimunu_h

//includes
#include "globals.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"

//forward declaration


/**
 *  @class GsimKLpimunu
 *  @brief This class provides the KL0->pi-mu+mu_nu and KL0->pi+mu-anti_mu_nu decays.
 */
class GsimKLpimunu : public G4ParticleDefinition
{
 private:
   /**
    *  @brief The instance of this.
    */
   static GsimKLpimunu* theInstance;
   /**
    *  @function GsimKLpimunu
    *  @brief Constructor for GsimKLpimunu
    */
   GsimKLpimunu(){}
   /**
    *  @function ~GsimKLpimunu
    *  @brief Destructor for GsimKLpimunu
    */
   ~GsimKLpimunu(){}

 public:
   /**
    *  @function Definition
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    */
   static GsimKLpimunu* Definition();
   /**
    *  @function KLpimunuDefinition
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    *
    *  This is the same as Definition().
    */
   static GsimKLpimunu* KLpimunuDefinition();
   /**
    *  @function KLpimunu
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    *
    *  This is the same as Definition().
    */
   static GsimKLpimunu* KLpimunu();
};

#endif // GsimKLpimunu_h
