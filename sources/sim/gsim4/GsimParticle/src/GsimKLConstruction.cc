/**
 *  @file
 *  @brief  GsimKLConstruction
 *  $Id: GsimKLConstruction.cc,v 1.5 2006/12/06 19:25:52 nanjo Exp $
 *  $Log: GsimKLConstruction.cc,v $
 *  Revision 1.5  2006/12/06 19:25:52  nanjo
 *  CVS variables.
 *
 */

#include "GsimPersistency/GsimMessage.h"
#include "GsimParticle/GsimKLConstruction.h"
#include "GsimParticle/GsimKLpi0nunu.h"
#include "GsimParticle/GsimKLpienu.h"
#include "GsimParticle/GsimKLpimunu.h"
#include "GsimParticle/GsimKL3pi0.h"
#include "GsimParticle/GsimKLpipipi0.h"
#include "GsimParticle/GsimKLpipi.h"
#include "GsimParticle/GsimKLpi0pi0.h"
#include "GsimParticle/GsimKLpienugamma.h"
#include "GsimParticle/GsimKLpimunugamma.h"
#include "GsimParticle/GsimKL2gamma.h"
#include "GsimParticle/GsimKLbeta.h"


GsimKLConstruction* GsimKLConstruction::s_KLConstruction = 0;

GsimKLConstruction* GsimKLConstruction::getKLConstruction()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(!s_KLConstruction) {
    static GsimKLConstruction theKLConstruction;
    s_KLConstruction = &theKLConstruction;
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return s_KLConstruction;
}

GsimKLConstruction::GsimKLConstruction()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_KLlist.push_back(GsimKLpi0nunu::KLpi0nunuDefinition());
  m_KLlist.push_back(GsimKLpienu::KLpienuDefinition());
  m_KLlist.push_back(GsimKLpimunu::KLpimunuDefinition());
  m_KLlist.push_back(GsimKL3pi0::KL3pi0Definition());
  m_KLlist.push_back(GsimKLpipipi0::KLpipipi0Definition());
  m_KLlist.push_back(GsimKLpipi::KLpipiDefinition());
  m_KLlist.push_back(GsimKLpi0pi0::KLpi0pi0Definition());
  m_KLlist.push_back(GsimKLpienugamma::KLpienugammaDefinition());
  m_KLlist.push_back(GsimKLpimunugamma::KLpimunugammaDefinition());
  m_KLlist.push_back(GsimKL2gamma::KL2gammaDefinition());
  m_KLlist.push_back(GsimKLbeta::KLbetaDefinition());
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimKLConstruction::~GsimKLConstruction()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


bool GsimKLConstruction::isGsimKL(G4ParticleDefinition* particleDefinition)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  for(std::list<G4ParticleDefinition*>::iterator it=m_KLlist.begin();
      it!=m_KLlist.end();it++) {
    
    if(particleDefinition==(*it)) {
      return true;
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return false;
}
