#include "E14Fsim/E14FsimAnalysisManager.h"
#include "E14Fsim/E14FsimPersistencyManager.h"

#include "E14Fsim/E14FsimPersistencyManager.h"
#include "E14Fsim/E14FsimGenParticleModule.h"
#include "E14Fsim/E14FsimCCModule.h"
#include "E14Fsim/E14FsimBARModule.h"
#include "E14Fsim/E14FsimCSIModule.h"
#include "E14Fsim/E14FsimBHPVModule.h"
#include "E14Fsim/E14FsimVetoModule.h"
#include "E14Fsim/E14FsimFunction.h"
#include "E14Fsim/E14FsimCluster.h"


#include "GsimData/GsimGenParticleData.h"
#include "GsimData/GsimDetectorEventData.h"

#include "TFile.h"
#include "TTree.h"

#include <iostream>

E14FsimAnalysisManager::E14FsimAnalysisManager(char* ifileName,char* ofileName, int nSel,
					       int iCluster, int iFusion, int iSmear) {

  m_nEventRequest=nSel;
  m_event=0;
  m_nClusterRequest=iCluster;

  new E14FsimPersistencyManager(ifileName,ofileName);

  m_GenParticleModule = new E14FsimGenParticleModule();
  
  //  m_CC01Module = new E14FsimCCModule();
  m_CC02Module = new E14FsimCCModule();
  m_CC03Module = new E14FsimCCModule();
  m_CC04Module = new E14FsimCCModule();
  m_CC05Module = new E14FsimCCModule();
  m_CC06Module = new E14FsimCCModule();
  m_CBARModule= new E14FsimBARModule();
  m_FBARModule = new E14FsimBARModule();
  m_CSIModule = new E14FsimCSIModule();
  m_BHPVModule = new E14FsimBHPVModule();
  m_VetoModule = new E14FsimVetoModule();

  m_VetoModule = new E14FsimVetoModule();

  //  m_CC01Module->setDetectorID(0);
  m_CC02Module->setDetectorID(1);
  m_CC03Module->setDetectorID(2);
  m_CC04Module->setDetectorID(3);
  m_CC05Module->setDetectorID(4);
  m_CC06Module->setDetectorID(5);
  m_CBARModule->setDetectorID(6);
  m_FBARModule->setDetectorID(7);


  m_moduleList.push_back( m_GenParticleModule );
  
  //  m_moduleList.push_back( m_CC01Module );
  m_moduleList.push_back( m_CC02Module );
  m_moduleList.push_back( m_CC03Module );
  m_moduleList.push_back( m_CC04Module );
  m_moduleList.push_back( m_CC05Module );
  m_moduleList.push_back( m_CC06Module );
  m_moduleList.push_back( m_CBARModule );
  m_moduleList.push_back( m_FBARModule );
  m_moduleList.push_back( m_CSIModule );
  m_moduleList.push_back( m_BHPVModule );

  m_moduleList.push_back( m_VetoModule );
  
  m_cpg.makePool(m_nClusterRequest);

  E14FsimAnalysisModule::clearVetoData();

  E14FsimFunction::getFunction()->setFusionMode(iFusion);
  E14FsimCluster::setSmearMode(iSmear);
}


E14FsimAnalysisManager::~E14FsimAnalysisManager() {
  deleteAndClearModules();
}

void E14FsimAnalysisManager::run()
{

  E14FsimPersistencyManager* pm
    = E14FsimPersistencyManager::getPersistencyManager();

  if(m_nEventRequest<0)
    m_nEventRequest=pm->getEntries();

  std::cerr << m_nEventRequest << " events are requested." << std::endl;

  int nSep=m_nEventRequest/100;
  if(nSep==0) nSep=1;
  
  beginOfRun();
  while ( pm->loop() )
    {
      if(m_event>=m_nEventRequest) break;
      processEvent();
      m_event++;

      if(m_event%nSep==0) {
	std::cerr << int(m_event/nSep) << " % is processed." << std::endl;
      }
    }
  endOfRun();
}

void E14FsimAnalysisManager::beginOfRun()
{
  E14FsimPersistencyManager::getPersistencyManager()->beginOfRun();
  
  for(std::list<E14FsimAnalysisModule*>::iterator
	it=m_moduleList.begin();it!=m_moduleList.end();it++) {
    (*it)->beginOfRun();
  }
  
  m_event=0;
}

void E14FsimAnalysisManager::processEvent()
{

  E14FsimPersistencyManager* pm = E14FsimPersistencyManager::getPersistencyManager();

  for(std::list<E14FsimAnalysisModule*>::iterator
	it=m_moduleList.begin();it!=m_moduleList.end();it++) {
    (*it)->processEvent();
  }

  for(std::list<E14FsimAnalysisModule*>::iterator
	it=m_moduleList.begin();it!=m_moduleList.end();it++) {
    (*it)->preClustering();
  }

  int nGamma=m_CSIModule->getNMcGamma();

  if(nGamma>0) {
    //some gammas in CSI
    std::list< std::list<int> > patternList
      =m_cpg.getClusterPatternList(nGamma,m_nClusterRequest);
    for( std::list< std::list<int> >::iterator itp=patternList.begin();
	 itp!=patternList.end();itp++) {
      for(std::list<E14FsimAnalysisModule*>::iterator
	    it=m_moduleList.begin();it!=m_moduleList.end();it++) {
	(*it)->processOneClusterPattern( (*itp) );
      }
      pm->fillTree();
    }
    
    if(m_nClusterRequest==-1) {
      //tripple or more fusion
      for(std::list<E14FsimAnalysisModule*>::iterator
	    it=m_moduleList.begin();it!=m_moduleList.end();it++) {
	(*it)->postClustering();
      }
      pm->fillTree();
    }
  } else {
    if(m_nClusterRequest==-1) {
      //no gamma in CSI
      pm->fillTree();
    }
  }
  
  for(std::list<E14FsimAnalysisModule*>::iterator
	it=m_moduleList.begin();it!=m_moduleList.end();it++) {
    (*it)->endOfEvent();
  }
}

void E14FsimAnalysisManager::endOfRun() {
  for(std::list<E14FsimAnalysisModule*>::iterator
	it=m_moduleList.begin();it!=m_moduleList.end();it++) {
    (*it)->endOfRun();
  }

  E14FsimPersistencyManager* pm = E14FsimPersistencyManager::getPersistencyManager();
  pm->close();
}


void E14FsimAnalysisManager::deleteAndClearModules() {
  for(std::list<E14FsimAnalysisModule*>::iterator
	it=m_moduleList.begin();it!=m_moduleList.end();it++) {
    delete (*it);
  }
  m_moduleList.clear();
}

void E14FsimAnalysisManager::importModule(E14FsimAnalysisModule* mod) {
  m_moduleList.push_back(mod);
}

