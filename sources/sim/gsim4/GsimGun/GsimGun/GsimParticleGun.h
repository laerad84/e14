/**
 *  @file
 *  @brief  GsimParticleGun
 *  $Id: 
 *  $Log: 
 */

#ifndef GsimParticleGun_h
#define GsimParticleGun_h

//includes
#include "GsimKernel/GsimPrimaryGeneratorAction.h"

//forward declaration
class G4Event;
class G4ParticleGun;

/**
 *  @class GsimParticleGun
 *  @brief This class provides GsimPrimaryGeneratorAction to generate beam particles.
 *  @see http://geant4.web.cern.ch/geant4/G4UsersDocuments/UsersGuides/ForApplicationDeveloper/html/GettingStarted/eventDef.html#2.6.2
 *  @see http://pcitapiww.cern.ch/asdcgi/geant4/SRM/G4GenDoc.exe.pl?flag=2&FileName=G4ParticleGun.hh&FileDir=event/include
 *
 *  This class provides G4ParticleGun, one of two G4VPrimaryGenerator concrete classes.
 */
class GsimParticleGun : public GsimPrimaryGeneratorAction
{
 public:

  /**
   *  @function GsimParticleGun
   *  @brief Constructor for GsimParticleGun
   */
  GsimParticleGun();

  /**
   *  @function ~GsimParticleGun
   *  @brief Destructor for GsimParticleGun
   */
  ~GsimParticleGun();
  
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
  G4ParticleGun* m_particleGun;
};

#endif //GsimParticleGun_h
