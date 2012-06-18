/**
 *  @file
 *  @brief  GsimKLpienu
 *  $Id: GsimKLpienu.h,v 1.3 2006/12/06 19:25:52 nanjo Exp $
 *  $Log: GsimKLpienu.h,v $
 *  Revision 1.3  2006/12/06 19:25:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimKLpienu_h
#define GsimKLpienu_h

//includes
#include "globals.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"

//forward declaration


/**
 *  @class GsimKLpienu
 *  @brief This class provides the KL0->pi-e+e_nu and KL0->pi+e-anti_e_nu decays.
 */
class GsimKLpienu : public G4ParticleDefinition
{
 private:
   /**
    *  @brief The instance of this.
    */
   static GsimKLpienu* theInstance;
   /**
    *  @function GsimKLpienu
    *  @brief Constructor for GsimKLpienu
    */
   GsimKLpienu(){}
   /**
    *  @function ~GsimKLpienu
    *  @brief Destructor for GsimKLpienu
    */
   ~GsimKLpienu(){}

 public:
   /**
    *  @function Definition
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    */
   static GsimKLpienu* Definition();
   /**
    *  @function KLpienuDefinition
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    *
    *  This is the same as Definition().
    */
   static GsimKLpienu* KLpienuDefinition();
   /**
    *  @function KLpienu
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    *
    *  This is the same as Definition().
    */
   static GsimKLpienu* KLpienu();
};

#endif // GsimKLpienu_h
