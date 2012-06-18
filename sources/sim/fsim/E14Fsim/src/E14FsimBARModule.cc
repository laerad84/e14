#include "E14Fsim/E14FsimBARModule.h"
#include "E14Fsim/E14FsimFunction.h"
#include "E14Fsim/E14FsimPersistencyManager.h"
#include "TMath.h"

#include "GsimData/GsimGenParticleData.h"
#include "GsimData/GsimDetectorEventData.h"
#include <iostream>

E14FsimBARModule::E14FsimBARModule()
  : E14FsimAnalysisModule()
{
  m_detID=6;
}

E14FsimBARModule::~E14FsimBARModule()
{
  ;
}


void E14FsimBARModule::processEvent()
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

    TVector3  rV = aHit->r;
    rV.SetZ(0.);
    double R = rV.Perp();
    double Pr = aHit->p.Dot(rV)/R;
    double theta = TMath::ASin(Pr/Mome);
    theta = TMath::Abs(theta) * 180. / TMath::Pi();
    
    double weight =E14FsimFunction::getFunction()->getBARWeight(Mome,PID,theta);

    E14FsimVeto* veto = new E14FsimVeto();
    veto->setDetID(VetoID);
    veto->setPID(PID);
    veto->setMome(aHit->p.x(),
		  aHit->p.y(),
		  aHit->p.z());
    veto->setPos(aHit->r.x(),
		 aHit->r.y(),
		 aHit->r.z());
    veto->setIneffi(weight);
    s_vetoList.push_back(veto);
  }
}

