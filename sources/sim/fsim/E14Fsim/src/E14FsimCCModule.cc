#include "E14Fsim/E14FsimCCModule.h"
#include "E14Fsim/E14FsimPersistencyManager.h"
#include "E14Fsim/E14FsimFunction.h"

#include "GsimData/GsimGenParticleData.h"
#include "GsimData/GsimDetectorEventData.h"

#include "TMath.h"

E14FsimCCModule::E14FsimCCModule()
  : E14FsimAnalysisModule()
{
  m_detID=0;
}

E14FsimCCModule::~E14FsimCCModule()
{
  ;
}


void E14FsimCCModule::processEvent()
{
  int VetoID = m_detID+1;

  GsimDetectorEventData* detData
    =E14FsimPersistencyManager::getPersistencyManager()->getDetectorEventData(m_detID);
  TClonesArray* detHitArray = detData->hits;
  int nHit =detHitArray->GetEntries();
  
  for (int iHit = 0 ; iHit < nHit ; iHit++){
    GsimDetectorHitData* aHit = (GsimDetectorHitData*)(detHitArray)->At(iHit);
    
    double Mome = aHit->p.Mag();
    int PID = aHit->pid;
    double theta = aHit->p.Theta();
    theta = 90. - TMath::Abs(theta) * 180. / TMath::Pi();

    double w=E14FsimFunction::getFunction()->getBARWeight(Mome,PID,theta);
    
    E14FsimVeto* veto = new E14FsimVeto();
    veto->setDetID(VetoID);
    veto->setPID(PID);
    veto->setMome(aHit->p.x(),
		  aHit->p.y(),
		  aHit->p.z());
    veto->setPos(aHit->r.x(),
		 aHit->r.y(),
		 aHit->r.z());
    veto->setIneffi(w);
    s_vetoList.push_back(veto);
  }
}

