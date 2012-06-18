/**
 *  @file
 *  @brief  GsimKLConstruction
 *  $Id: GsimKLConstruction.h,v 1.5 2006/12/06 19:25:52 nanjo Exp $
 *  $Log: GsimKLConstruction.h,v $
 *  Revision 1.5  2006/12/06 19:25:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimKLConstruction_h
#define GsimKLConstruction_h

//includes
#include <list>
#include "G4ParticleDefinition.hh"
//forward declaration


/**
 *  @class GsimKLConstruction
 *  @brief This class constructs the KL0 with all of the decay modes.
 */

class GsimKLConstruction
{
 public:
  /**
   *  @function GsimKLConstruction
   *  @brief Destructor for GsimKLConstruction
   */
  virtual ~GsimKLConstruction();
  /**
   *  @function getKLConstruction
   *  @brief Returns a KL0.
   *  @return The constructed KL0 with the decay modes.
   */
  static GsimKLConstruction* getKLConstruction();
  /**
   *  @function isGsimKL
   *  @brief Determines if a particle is a Gsim KL0.
   *  @param particleDefinition The particle.
   *  @return True, if the particle is a Gsim KL0.
   */
  bool isGsimKL(G4ParticleDefinition* particleDefinition);
 private:
  /**
   *  @function GsimKLConstruction
   *  @brief Constructor for GsimKLConstruction
   *  @see getKLConstruction()
   * 
   *  The constructor is called by getKLConstruction.
   */
  GsimKLConstruction();
  /**
   *  @brief The KL0.
   */
  static GsimKLConstruction* s_KLConstruction;
  /**
   *  @brief The list of processes.
   */
  std::list<G4ParticleDefinition*> m_KLlist;
};

#endif // GsimKLConstruction_h
