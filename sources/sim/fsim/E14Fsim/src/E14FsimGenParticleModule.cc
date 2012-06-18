#include "E14Fsim/E14FsimGenParticleModule.h"
#include "E14Fsim/E14FsimPersistencyManager.h"

E14FsimGenParticleModule::E14FsimGenParticleModule()
  : E14FsimAnalysisModule()
{
  
}

E14FsimGenParticleModule::~E14FsimGenParticleModule()
{
  
}


void E14FsimGenParticleModule::initialize()
{
  ;
}
  
void E14FsimGenParticleModule::beginOfRun()
{
  E14FsimPersistencyManager* persistencyManager =
    E14FsimPersistencyManager::getPersistencyManager();
  
  persistencyManager->branch("KDecayMome",KDecayMome,"KDecayMome[3]/D");
  persistencyManager->branch("KDecayPos",KDecayPos,"KDecayPos[3]/D");
  persistencyManager->branch("KDecayTime",&KDecayTime,"KDecayTime/D");

  persistencyManager->branch("Pi0number",&Pi0number,"Pi0number/I");
  persistencyManager->branch("Pi0Mome",Pi0Mome,"Pi0Mome[Pi0number][3]/D");
  persistencyManager->branch("Pi0Pos",Pi0Pos,"Pi0Pos[Pi0number][3]/D");
  persistencyManager->branch("Pi0Time",Pi0Time,"Pi0Time[Pi0number]/D");
}

void E14FsimGenParticleModule::processEvent()
{
  GsimGenParticleData* gp=
    E14FsimPersistencyManager::getPersistencyManager()->getGsimGenParticleData();
  
  TClonesArray* gpArray       = gp->briefTracks;
  int nGP=gpArray->GetEntries();

  int pi0number = 0;
  for(int i=0; i<nGP; i++){
    GsimTrackData* aTrack = (GsimTrackData*)gpArray->At(i);
    
    if(aTrack->pid == 130){
      KDecayPos[0]=aTrack->end_v.x();
      KDecayPos[1]=aTrack->end_v.y();
      KDecayPos[2]=aTrack->end_v.z(); 
      KDecayMome[0]=aTrack->end_p.x();
      KDecayMome[1]=aTrack->end_p.y();
      KDecayMome[2]=aTrack->end_p.z();
      KDecayTime=aTrack->end_time;
    }
    if(aTrack->pid == 111){
      Pi0Pos[pi0number][0]=aTrack->v.x();
      Pi0Pos[pi0number][1]=aTrack->v.y();
      Pi0Pos[pi0number][2]=aTrack->v.z(); 
      Pi0Mome[pi0number][0]=aTrack->p.x();
      Pi0Mome[pi0number][1]=aTrack->p.y();
      Pi0Mome[pi0number][2]=aTrack->p.z();
      Pi0Time[pi0number]=aTrack->time;
      pi0number +=1;
    }
  }
  Pi0number = pi0number;
}

void E14FsimGenParticleModule::endOfRun()
{
  ;
}

void E14FsimGenParticleModule::terminate()
{
  ;
}
