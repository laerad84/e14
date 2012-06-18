/**
 *  @file
 *  @brief  GsimX
 *  $Id: $
 *  $Log:$
 */
#ifndef GsimX_h
#define GsimX_h

//includes
#include "globals.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"

//forward declaration


/**
 *  @class GsimX
 *  @brief This class provides the psX.
 */

class GsimX : public G4ParticleDefinition
{
 private:
   /**
    *  @brief The instance of this.
    */
   static GsimX* theInstance;
   /**
    *  @function GsimX
    *  @brief Constructor for GsimX
    */
   GsimX(){}
   /**
    *  @function ~GsimX
    *  @brief Destructor for GsimX
    */
   ~GsimX(){}

 public:
   /**
    *  @function Initialization
    *  @brief Set X properties.
    */
   static void initialize(double mass,double lifetime,double width,double charge,
			  bool isStable,bool isShortlived);
			  
   
   /**
    *  @function Definition
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    */
   static GsimX* Definition();
   /**
    *  @function XDefinition
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    *
    *  This is the same as Definition().
    */
   static GsimX* XDefinition();
   /**
    *  @function X
    *  @brief Returns the definition of the decay.
    *  @return The definition of the decay.
    *
    *  This is the same as Definition().
    */
   static GsimX* X();
};

#endif // GsimX_h
