/**
 *  @file
 *  @brief  GsimParticleGun
 *  $Id: 
 *  $Log: 
 */
#include "GsimGun/GsimParticleGun.h"
#include "GsimKernel/GsimSpectrum.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4ParticleGun.hh"
#include "G4Event.hh"

GsimParticleGun::GsimParticleGun()
  : GsimPrimaryGeneratorAction()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif


  m_particleGun = new G4ParticleGun(1);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimParticleGun::~GsimParticleGun()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  
  delete m_particleGun;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif

}


void GsimParticleGun::shoot(G4Event* anEvent)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  
  m_particleGun->GeneratePrimaryVertex(anEvent);
  if(m_spectrum) {
    m_spectrum->generateSpectrum(anEvent);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif

}


