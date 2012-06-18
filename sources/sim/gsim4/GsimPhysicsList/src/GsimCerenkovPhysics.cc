/**
 *  @file
 *  @brief  GsimCerenkovPhysics
 *  $Id: $
 *  $Log:$
 */
#include "GsimPhysicsList/GsimCerenkovPhysics.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4RunManager.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4Cerenkov.hh"
#include "G4ProcessVector.hh"
#include "G4VProcess.hh"
#include "G4VUserPhysicsList.hh"
#include "G4Version.hh"

#include <sstream>




GsimCerenkovPhysics::GsimCerenkovPhysics()
  :  G4VPhysicsConstructor("GsimCerenkov") 
{
  //
}

GsimCerenkovPhysics::~GsimCerenkovPhysics()
{
  //
}

void GsimCerenkovPhysics::ConstructParticle()
{
  //
}

void GsimCerenkovPhysics::ConstructProcess()
{
  if(isCerenkovAdded()) {
    GsimMessage::getInstance()
      ->report("warning","Cerenkov is already added.");
    return;
  }
  
  G4RunManager* runManager =  G4RunManager::GetRunManager();
  if(!runManager) {
    GsimMessage::getInstance()
      ->report("warning","No runManager.");
    return;
  }

  G4ParticleTable* pt = G4ParticleTable::GetParticleTable();
  if(!pt) {
    GsimMessage::getInstance()
      ->report("warning","No particle table.");
    return;
  }

  G4Cerenkov* theCerenkovProcess=findCerenkov();
  if(!theCerenkovProcess) {
    theCerenkovProcess = new G4Cerenkov("Cerenkov");
    theCerenkovProcess->SetMaxNumPhotonsPerStep(300); // which limit the step size
    theCerenkovProcess->SetTrackSecondariesFirst(true); // for firster memory release
  }
  
  int nP=pt->size();
  for(int j=0;j<nP;j++) {
    G4ParticleDefinition* particle = pt->GetParticle(j);
    G4ProcessManager* pmanager = particle->GetProcessManager();
    if(!pmanager) {
      G4RunManager* fRunManager = G4RunManager::GetRunManager();
      const G4VUserPhysicsList* pl = fRunManager->GetUserPhysicsList();
      const_cast<G4VUserPhysicsList*>(pl)->AddProcessManager(particle);
      pmanager = particle->GetProcessManager();

      G4String particleName = particle->GetParticleName();
      std::ostringstream ostr;
      ostr << "Process manager is constructed and added to a particle, "
	   << particleName << ".";
      GsimMessage::getInstance()
	->report("info",ostr.str());
    }
    int idx=pmanager->GetProcessIndex(theCerenkovProcess);
    if(idx!=-1) continue;
    if(theCerenkovProcess) {
      if (theCerenkovProcess->IsApplicable(*particle)) {
#if ( G4VERSION_NUMBER >= 910 )
	pmanager->AddProcess(theCerenkovProcess);
	pmanager->SetProcessOrdering(theCerenkovProcess,idxPostStep);
#else
	pmanager->AddContinuousProcess(theCerenkovProcess);
#endif
      }
    }
  }
  
  GsimMessage::getInstance()
    ->report("info","Cerenkov is added.");
}


bool GsimCerenkovPhysics::isCerenkovAdded()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  G4RunManager* runManager =  G4RunManager::GetRunManager();
  if(!runManager) {
    return false;
  }

  G4ParticleTable* pt = G4ParticleTable::GetParticleTable();
  if(!pt) {
    return false;
  }

  bool isAdded=true;
  int nP=pt->size();
  for(int j=0;j<nP;j++) {
    G4ParticleDefinition* particle = pt->GetParticle(j);
    G4double charge=particle->GetPDGCharge();
    G4String particleName = particle->GetParticleName();
    if(charge==0 || particleName=="chargedgeantino") continue;
    

    G4ProcessManager* pmanager = particle->GetProcessManager();
    if(!pmanager) {
      isAdded=false;
      continue;
    }
    
    G4ProcessVector* pv=pmanager->GetProcessList();
    int num=pv->size();

    int nCerenkov=0;
    for(int k=0;k<num;k++) {
      G4VProcess* proc= (*pv)[k];
      G4String name=proc->GetProcessName();
      if(name=="Cerenkov") {
	nCerenkov++;
      }
    }
    if(nCerenkov==0) {
      //Cerenkov is not added for this charged particle.
      isAdded=false;
    } else if(nCerenkov==1) {
      //Cerenkov is added for this charged particle.
    } else {
      //Cerenkov is added multiple times for this charged particle.
      std::ostringstream ostr;
      ostr << particleName << " : " << "Cerenkov is added "
	   << nCerenkov << " times.";
      GsimMessage::getInstance()
	->report("error",ostr.str());
    }
  }
  return isAdded;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


G4Cerenkov* GsimCerenkovPhysics::findCerenkov()
{
  G4Cerenkov* fCerenkov=0;
  G4RunManager* runManager =  G4RunManager::GetRunManager();
  if(!runManager) {
    return fCerenkov;
  }

  G4ParticleTable* pt = G4ParticleTable::GetParticleTable();
  if(!pt) {
    return fCerenkov;
  }
  int nP=pt->size();
  for(int j=0;j<nP;j++) {
    G4ParticleDefinition* particle = pt->GetParticle(j);
    G4ProcessManager* pmanager = particle->GetProcessManager();
    if(!pmanager) continue;
    G4ProcessVector* procV=pmanager->GetProcessList();
    for(int i=0;i<procV->size();i++) {
      G4String procName=(*procV)[i]->GetProcessName();
      if(procName=="Cerenkov") {
	fCerenkov=dynamic_cast<G4Cerenkov*>( (*procV)[i] );
	return fCerenkov;
      }
    }
  }
  return fCerenkov;
}
