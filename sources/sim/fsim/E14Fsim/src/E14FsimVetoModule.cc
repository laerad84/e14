#include "E14Fsim/E14FsimVetoModule.h"
#include "E14Fsim/E14FsimPersistencyManager.h"

E14FsimVetoModule::E14FsimVetoModule()
  : E14FsimAnalysisModule()
{
  
}

E14FsimVetoModule::~E14FsimVetoModule()
{
  
}


void E14FsimVetoModule::beginOfRun()
{
  E14FsimPersistencyManager* pm =
    E14FsimPersistencyManager::getPersistencyManager();

  pm->branch("gsimEventNumber",&gsimEventNumber,"gsimEventNumber/I");
  pm->branch("mcEventID",&mcEventID,"mcEventID/I");
  pm->branch("nHitVeto",&nHitVeto,"nHitVeto/I");
  pm->branch("VetoPID",VetoPID,"VetoPID[nHitVeto]/I");
  pm->branch("VetoDetID",VetoDetID,"VetoDetID[nHitVeto]/I");
  pm->branch("VetoPos",VetoPos,"VetoPos[nHitVeto][3]/D");
  pm->branch("VetoMome",VetoMome,"VetoMome[nHitVeto][3]/D");
  pm->branch("VetoIneffi",VetoIneffi,"VetoIneffi[nHitVeto]/D");
  
  pm->branch("DetVetoWeight",DetVetoWeight,"DetVetoWeight[10]/D");
  pm->branch("VetoWeight",&VetoWeight,"VetoWeight/D");


  gsimEventNumber=-1;
  mcEventID=-1;
}

void E14FsimVetoModule::preClustering()
{
  VetoWeight=1.;
  for(int k=0;k<10;k++) {
    DetVetoWeight[k]=1.;
  }
  
  nHitVeto=s_vetoList.size();
  m_hitVeto=s_vetoList.size();
  int cnt=0;

  for(std::list<E14FsimVeto*>::iterator it=s_vetoList.begin();
      it!=s_vetoList.end();it++,cnt++) {
    VetoPID[cnt]=(*it)->pid();
    int detid=(*it)->detid();
    VetoDetID[cnt]=detid;
    VetoPos[cnt][0]=((*it)->pos()).x();
    VetoPos[cnt][1]=((*it)->pos()).y();
    VetoPos[cnt][2]=((*it)->pos()).z();
    VetoMome[cnt][0]=((*it)->mome()).x();
    VetoMome[cnt][1]=((*it)->mome()).y();
    VetoMome[cnt][2]=((*it)->mome()).z();
    double ineff=(*it)->ineffi();
    VetoIneffi[cnt]=ineff;
    DetVetoWeight[ detid-1 ] *=ineff;
    VetoWeight*=ineff;
  }
  VetoWeightWithoutIneffiGamma=VetoWeight;
  mcEventID++;

  E14FsimPersistencyManager* pm =
    E14FsimPersistencyManager::getPersistencyManager();
  gsimEventNumber=pm->getGsimEventData()->event_number;
}

void E14FsimVetoModule::processOneClusterPattern(std::list<int>& ){

  if(m_hitVeto!=s_vetoList.size()){
    nHitVeto   = m_hitVeto;
    VetoWeight = VetoWeightWithoutIneffiGamma;
    
    std::list<E14FsimVeto*>::iterator it = s_vetoList.begin();
    for(size_t i=0; i<m_hitVeto; i++) {
      it++;
    }
    
    while(it != s_vetoList.end()){
      VetoPID[nHitVeto]=(*it)->pid();
      int detid=(*it)->detid();
      VetoDetID[nHitVeto]=detid;
      VetoPos[nHitVeto][0]=((*it)->pos()).x();
      VetoPos[nHitVeto][1]=((*it)->pos()).y();
      VetoPos[nHitVeto][2]=((*it)->pos()).z();
      VetoMome[nHitVeto][0]=((*it)->mome()).x();
      VetoMome[nHitVeto][1]=((*it)->mome()).y();
	VetoMome[nHitVeto][2]=((*it)->mome()).z();
	double ineff=(*it)->ineffi();
	VetoIneffi[nHitVeto]=ineff;
	DetVetoWeight[ detid-1 ] *=ineff;
	VetoWeight*=ineff;

	delete (*it);
	it = s_vetoList.erase(it);
	nHitVeto++;
    }
  }
} 

void E14FsimVetoModule::endOfEvent() {
  for(std::list<E14FsimVeto*>::iterator it=s_vetoList.begin();
      it!=s_vetoList.end();it++) {
    delete (*it);
  }
  s_vetoList.clear();

}

