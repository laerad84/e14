/**
 *  $Id: GsimUserLimits.cc,v 1.4 2006/12/06 18:44:00 nanjo Exp $
 *  $Log: GsimUserLimits.cc,v $
 *  Revision 1.4  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 */
#include "GsimKernel/GsimUserLimits.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4StepLimiter.hh"
#include "G4UserSpecialCuts.hh"

GsimUserLimits::GsimUserLimits(const G4String& name): G4VPhysicsConstructor(name)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimUserLimits::~GsimUserLimits()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimUserLimits::ConstructParticle()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimUserLimits::ConstructProcess()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();

    //UserLimits are applied to all the particles.
    bool isMatch=true;
//     bool isMatch=false;
//     if ( particle->GetPDGStable() ) {
//       isMatch=true;
//     } else if ( (!particle->IsShortLived()) && 
// 		particle->GetPDGLifeTime()>2200*ns ) {
//       isMatch=true;
//     }

    if(isMatch) {
      int num=pmanager->GetProcessListLength();
      G4ProcessVector* pv=pmanager->GetProcessList();
      bool isContained=false;
      for(int i=0;i<num;i++) {
	if( (*pv)[i]->GetProcessName()=="UserSpecialCut" )
	  isContained=true;
      }
      if(!isContained) {
	num++;
	pmanager->AddProcess(new G4UserSpecialCuts,   -1,-1,num);
      }
      
      isContained=false;
      for(int i=0;i<num;i++) {
	if( (*pv)[i]->GetProcessName()=="StepLimiter" )
	  isContained=true;
      }
      if(!isContained) {
	num++;
	pmanager->AddProcess(new G4StepLimiter,       -1,-1,num);
      }
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}
