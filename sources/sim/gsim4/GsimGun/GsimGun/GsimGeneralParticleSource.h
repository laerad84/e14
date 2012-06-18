/**
 *  @file
 *  @brief  GsimGeneralParticleSource
 *  $Id: 
 *  $Log: 
 */

#ifndef GsimGeneralParticleSource_h
#define GsimGeneralParticleSource_h

//includes
#include "GsimKernel/GsimPrimaryGeneratorAction.h"

//forward declaration
class G4Event;
class G4GeneralParticleSource;

/**
 *  @class GsimGeneralParticleSource
 *  @brief This class provides GsimPrimaryGeneratorAction to generate beam particles.
 *  @see http://geant4.web.cern.ch/geant4/geant4_public/source/geant4/examples/extended/eventgenerator/exgps/README
 *
 *  This class provides G4GeneralParticleSource, an advanced particle generator.
 */
class GsimGeneralParticleSource : public GsimPrimaryGeneratorAction
{
 public:
  
  /**
   *  @function GsimGeneralParticleSource
   *  @brief Constructor for GsimGeneralParticleSource
   */
  GsimGeneralParticleSource();

  /**
   *  @function ~GsimGeneralParticleSource
   *  @brief Destructor for GsimGeneralParticleSource
   */
  ~GsimGeneralParticleSource();
  
 protected:
  /**
   *  @function shoot
   *  @brief Shoots a particle by generating an initial particle vertex.
   *  @param anEvent The event that receives the particle.
   */
  virtual void shoot(G4Event* anEvent);
  /**
   *  @brief The particle gun.
   */
  G4GeneralParticleSource* m_particleGun;
};

#endif //GsimGeneralParticleSource_h
