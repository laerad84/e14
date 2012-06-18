/**
 *  @file
 *  @brief  GsimGeneralParticleSource
 *  $Id: 
 *  $Log: 
 */
#include "GsimGun/GsimGeneralParticleSource.h"
#include "GsimKernel/GsimSpectrum.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4GeneralParticleSource.hh"
#include "G4Event.hh"

GsimGeneralParticleSource::GsimGeneralParticleSource()
  : GsimPrimaryGeneratorAction()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_particleGun = new G4GeneralParticleSource();
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif

}

GsimGeneralParticleSource::~GsimGeneralParticleSource()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  
  delete m_particleGun;
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimGeneralParticleSource::shoot(G4Event* anEvent)
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


