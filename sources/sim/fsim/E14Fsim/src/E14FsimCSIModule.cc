#include "E14Fsim/E14FsimCSIModule.h"
#include "E14Fsim/E14FsimPersistencyManager.h"
#include "E14Fsim/E14FsimFunction.h"

#include "GsimData/GsimGenParticleData.h"
#include "GsimData/GsimDetectorEventData.h"
#include "GsimData/GsimTrackData.h"

#include <iostream>

E14FsimCSIModule::E14FsimCSIModule()
  : E14FsimAnalysisModule()
{
  m_detID=8;
}

E14FsimCSIModule::~E14FsimCSIModule()
{
  clearMcGammaData();
  clearClusterData();
}


void E14FsimCSIModule::beginOfRun()
{
  E14FsimPersistencyManager* pm =
    E14FsimPersistencyManager::getPersistencyManager();

  pm->branch("eventID",&eventID,"eventID/I");
  pm->branch("nHitCluster",&nHitCluster,"nHitCluster/I");
  pm->branch("ClusterHitPos",ClusterHitPos,"ClusterHitPos[nHitCluster][3]/D");
  pm->branch("ClusterHitTotE",ClusterHitTotE,"ClusterHitTotE[nHitCluster]/D");
  pm->branch("ClusterHitAng",ClusterHitAng,"ClusterHitAng[nHitCluster][2]/D");
  pm->branch("ClusterHitTime",ClusterHitTime,"ClusterHitTime[nHitCluster]/D");
  pm->branch("ClusterHitThisID",ClusterHitThisID,"ClusterHitThisID[nHitCluster]/I");
  pm->branch("ClusterHitParentID",ClusterHitParentID,"ClusterHitParentID[nHitCluster]/I");
  pm->branch("ClusterHitTrueP",ClusterHitTrueP,"ClusterHitTrueP[nHitCluster][3]/D");
  pm->branch("ClusterHitSigmaE",ClusterHitSigmaE,"ClusterHitSigmaE[nHitCluster]/D");
  pm->branch("ClusterHitSigmaXY",ClusterHitSigmaXY,"ClusterHitSigmaXY[nHitCluster]/D");
  pm->branch("ClusterEffi",&ClusterEffi,"ClusterEffi/D");
  pm->branch("CalHitClusterWeight",&CalHitClusterWeight,"CalHitClusterWeight/D");
  pm->branch("CalIneffiGammaWeight",&CalIneffiGammaWeight,"CalIneffiGammaWeight/D");
  pm->branch("ClusterFusionProb",&ClusterFusionProb,"ClusterFusionProb/D");

  pm->branch("ClusterWeight",&ClusterWeight,"ClusterWeight/D");
  pm->branch("EventWeight",&EventWeight,"EventWeight/D");

  clearClusterData();

  eventID=0;
}

void E14FsimCSIModule::processEvent()
{

  initVariables();

  
  int VetoID = m_detID+1;

  GsimGenParticleData* gp=
    E14FsimPersistencyManager::getPersistencyManager()->getGsimGenParticleData();
  TClonesArray* gpArray       = gp->briefTracks;
  int nGP=gpArray->GetEntries();

  GsimDetectorEventData* detData
    =E14FsimPersistencyManager::getPersistencyManager()->getDetectorEventData(m_detID);
  TClonesArray* detHitArray = detData->hits;
  int nHit =detHitArray->GetEntries();

  int id=0;
  for (Int_t iHit = 0 ; iHit < nHit ; iHit++){
    GsimDetectorHitData* aHit = (GsimDetectorHitData*)(detHitArray)->At(iHit);
    
    double Mome = aHit->p.Mag();
    int PID = aHit->pid;
    if (PID!=22){
      double weight=E14FsimFunction::getFunction()->getCSIWeight(Mome,PID);
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
    } else {
      //PID==22
      E14FsimMcGamma* mcgamma = new E14FsimMcGamma();
      mcgamma->m_pos=aHit->r;
      mcgamma->m_mome=aHit->p;
      mcgamma->m_energy=aHit->ek;
      mcgamma->m_time=aHit->time;
      mcgamma->m_gammaID=id;

      int parentID=-999;
      for(Int_t iGP=0; iGP<nGP; iGP++){
	GsimTrackData* aTrack = (GsimTrackData*)gpArray->At(iGP);
	if(aTrack->track == aHit->track) {
	  parentID = aTrack->mother;
	  break;
	}
      }
      mcgamma->m_parentID=parentID;
      m_mcGammaVec.push_back(mcgamma);
      id++;
    }
  }

  m_noFusionProbWithoutZeroProduction=1.;
  m_numberOfZeroProduction=0;
  int nGamma=m_mcGammaVec.size();
  for(int i=0;i<nGamma;i++) {
    for(int j=i+1;j<nGamma;j++) {
      TVector3 difV=m_mcGammaVec[i]->m_pos-m_mcGammaVec[j]->m_pos;
      double dXY=difV.Perp();
      double fp=E14FsimFunction::getFunction()->fusionProb(dXY);
      if(fp==1.) {
	m_numberOfZeroProduction++;
      } else {
	m_noFusionProbWithoutZeroProduction*=1.-fp;
      }
    }
  }
}

void E14FsimCSIModule::processOneClusterPattern(std::list<int>& pattern)
{
  int maxid=-1;
  for(std::list<int>::iterator it=pattern.begin();
      it!=pattern.end();it++) {
    if((*it)==-1) {
      //ineefi;
    } else {
      //cluster No. (*it);
      if( (*it)>maxid ) maxid= (*it);
    }
  }

  int nCluster=maxid+1;
  for(int k=0;k<nCluster;k++) {
    E14FsimCluster* clu = new E14FsimCluster();
    clu->m_clusterID=k;
    m_clusterVec.push_back(clu);
  }

  int cnt=0;
  for(std::list<int>::iterator it=pattern.begin();
      it!=pattern.end();it++,cnt++) {
    E14FsimMcGamma* mcGamma = m_mcGammaVec[ cnt ];
    if((*it)==-1) {
      m_ineffGammaList.push_back( mcGamma );

      ///  add shiomi      
      E14FsimVeto* veto = new E14FsimVeto();
      veto->setDetID(m_detID+1);
      veto->setPID(22);                          // photon
      veto->setMome(mcGamma->m_mome.x(),
		    mcGamma->m_mome.y(),
		    mcGamma->m_mome.z());
      veto->setPos(mcGamma->m_pos.x(),
		   mcGamma->m_pos.y(),
		   mcGamma->m_pos.z());
      veto->setIneffi(E14FsimFunction::getFunction()->csiineff( mcGamma->m_energy/1000.  ));
      s_vetoList.push_back(veto);
      ///

    } else {
      E14FsimCluster* clu = m_clusterVec[ (*it) ];
      clu->addMcGamma( mcGamma );
    }
  }

  for(std::vector<E14FsimCluster*>::iterator it=m_clusterVec.begin();
      it!=m_clusterVec.end();it++) {
    (*it)->smear();
  }

  fillClusterData();
  
  eventID++;
  clearClusterData();
}



void E14FsimCSIModule::fillClusterData()
{
  nHitCluster=m_clusterVec.size();
  int cnt=0;
  ClusterEffi=1.;
  CalHitClusterWeight=1.;
  CalIneffiGammaWeight=1.;

  int nZeroProd=m_numberOfZeroProduction;
  ClusterFusionProb=m_noFusionProbWithoutZeroProduction;
  
  for(std::vector<E14FsimCluster*>::iterator it=m_clusterVec.begin();
      it!=m_clusterVec.end();it++,cnt++) {
    ClusterHitPos[cnt][0]=((*it)->m_pos).x();
    ClusterHitPos[cnt][1]=((*it)->m_pos).y();
    ClusterHitPos[cnt][2]=((*it)->m_pos).z();
    
    ClusterHitTotE[cnt]=(*it)->m_energy;
    ClusterHitTime[cnt]=(*it)->m_time;
    ClusterHitThisID[cnt]=(*it)->m_mcGammaID[0];
    ClusterHitParentID[cnt]=(*it)->m_mcParentID[0];
    if((*it)->m_nMcGamma==2) {
      //this id
      if((*it)->m_mcGammaID[0]>=100 || (*it)->m_mcGammaID[1]>=100) {
	std::cout << "Warning : Parent track ID >= 100. "  << std::endl;
	std::cout << "          No cluster parent info. is stored."  << std::endl;
	ClusterHitThisID[cnt]=-20000;
      } else {
	ClusterHitThisID[cnt]=
	  -20000
	  -100*(*it)->m_mcGammaID[1]+
	  -(*it)->m_mcGammaID[0];
	//m_mcParentID[] can be -1 if initial photon
	//ClusterHitParentID[cnt] can be -19xxx
      }
    } else if((*it)->m_nMcGamma>2) {
      if((*it)->m_mcGammaID[0]>=100 || (*it)->m_mcGammaID[1]>=100) {
	std::cout << "Warning : Parent track ID >= 100. "  << std::endl;
	std::cout << "          No cluster parent info. is stored."  << std::endl;
	ClusterHitThisID[cnt]=-30000;
      } else {
	ClusterHitThisID[cnt]=
	  -30000
	  -100*(*it)->m_mcGammaID[1]+
	  -(*it)->m_mcGammaID[0];
      }
    }

    if((*it)->m_nMcGamma==2) {
      //parent id
      if((*it)->m_mcParentID[0]>=100 || (*it)->m_mcParentID[1]>=100) {
	std::cout << "Warning : Parent track ID >= 100. "  << std::endl;
	std::cout << "          No cluster parent info. is stored."  << std::endl;
	ClusterHitParentID[cnt]=-20000;
      } else {
	ClusterHitParentID[cnt]=
	  -20000
	  -100*(*it)->m_mcParentID[1]+
	  -(*it)->m_mcParentID[0];
	//m_mcParentID[] can be -1 if initial photon
	//ClusterHitParentID[cnt] can be -19xxx
      }
    } else if((*it)->m_nMcGamma>2) {
      if((*it)->m_mcParentID[0]>=100 || (*it)->m_mcParentID[1]>=100) {
	std::cout << "Warning : Parent track ID >= 100. "  << std::endl;
	std::cout << "          No cluster parent info. is stored."  << std::endl;
	ClusterHitParentID[cnt]=-30000;
      } else {
	ClusterHitParentID[cnt]=
	  -30000
	  -100*(*it)->m_mcParentID[1]+
	  -(*it)->m_mcParentID[0];
      }
    }
    ClusterHitTrueP[cnt][0]=((*it)->m_mome).x();
    ClusterHitTrueP[cnt][1]=((*it)->m_mome).y();
    ClusterHitTrueP[cnt][2]=((*it)->m_mome).z();
    
    ClusterHitSigmaE[cnt]=(*it)->m_sigmaE;
    ClusterHitSigmaXY[cnt]=(*it)->m_sigmaX;

    for(int k=0;k<(*it)->m_nMcGamma;k++) {
      ClusterEffi*=
	1.-E14FsimFunction::getFunction()->csiineff(  ((*it)->m_mcGammaMome[k].Mag())/1000.  );
    }

    if((*it)->m_nMcGamma==2) {
      double fp=(*it)->m_mcFusionProb;

      if(fp == 1.) {
	nZeroProd--;
      } else {
	ClusterFusionProb*=fp/(1.-fp);
      }
    }
  }
  
  if(nZeroProd>0) {
    ClusterFusionProb=0.;
  }

  CalHitClusterWeight = ClusterEffi;

  for(std::list<E14FsimMcGamma*>::iterator it=m_ineffGammaList.begin();
      it!=m_ineffGammaList.end();it++) {
    ClusterEffi*=
      E14FsimFunction::getFunction()->csiineff(  (*it)->m_energy/1000.  );

    CalIneffiGammaWeight *=
      E14FsimFunction::getFunction()->csiineff(  (*it)->m_energy/1000.  );
  }

  ClusterWeight=ClusterEffi*ClusterFusionProb;
  EventWeight=ClusterWeight*VetoWeightWithoutIneffiGamma;
  
  m_sumW+=ClusterWeight;
}


void E14FsimCSIModule::postClustering()
{
  ClusterWeight=1.-m_sumW;
  nHitCluster=1;
  ClusterEffi=-1.;//no meaning
  CalHitClusterWeight=1;
  CalIneffiGammaWeight=1;
  ClusterFusionProb=1.; //tripple or more fusion
  EventWeight=ClusterWeight*VetoWeightWithoutIneffiGamma;
}

void E14FsimCSIModule::endOfEvent()
{
  clearMcGammaData();
}



void E14FsimCSIModule::clearMcGammaData()
{
  for(std::vector<E14FsimMcGamma*>::iterator it=m_mcGammaVec.begin();
      it!=m_mcGammaVec.end();it++) {
    delete (*it);
  }
  m_mcGammaVec.clear();
}

void E14FsimCSIModule::clearClusterData()
{
  for(std::vector<E14FsimCluster*>::iterator it=m_clusterVec.begin();
      it!=m_clusterVec.end();it++) {
    delete (*it);
  }
  m_clusterVec.clear();
  m_ineffGammaList.clear();
}



void E14FsimCSIModule::initVariables()
{
  nHitCluster=0;
  ClusterEffi=1.;
  ClusterFusionProb=1.;
  ClusterWeight=1.;
  CalHitClusterWeight=1;
  CalIneffiGammaWeight=1;
  EventWeight=1.;
  m_sumW=0;
}
