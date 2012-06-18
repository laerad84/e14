#include "E14Fsim/E14FsimPersistencyManager.h"
#include "E14Fsim/E14FsimFunction.h"

#include <iostream>


E14FsimPersistencyManager* E14FsimPersistencyManager::s_persistencyManager=0;

E14FsimPersistencyManager::E14FsimPersistencyManager(char* ifileName,char* ofileName)
{
  if(s_persistencyManager) {
    std::cerr << "E14FsimPersistencyManager is constructed twice." << std::endl;
    return;
  }
  
  m_ifname = ifileName;
  m_ofname = ofileName;

  m_tf = new TFile(m_ifname.c_str());
  m_tr = (TTree*)m_tf->Get("eventTree00");

  m_detName[0]="CC01.";
  m_detName[1]="CC02.";
  m_detName[2]="CC03.";
  m_detName[3]="CC04.";
  m_detName[4]="CC05.";
  m_detName[5]="CC06.";
  m_detName[6]="CBAR.";
  m_detName[7]="FBAR.";
  m_detName[8]="CSI.";
  m_detName[9]="BHPV.";

  m_eventData=0;
  m_gp=0;
  for(int k=0;k<10;k++) {
    m_detData[k]=0;
  }
  
  s_persistencyManager=this;
}


E14FsimPersistencyManager::~E14FsimPersistencyManager()
{
  delete m_eventData;
  delete m_gp;
  for(int k=0;k<10;k++) {
    delete m_detData[k];
  }
}

E14FsimPersistencyManager* E14FsimPersistencyManager::getPersistencyManager()
{
  return s_persistencyManager;
}



void E14FsimPersistencyManager::beginOfRun()
{
  m_tfo = new TFile(m_ofname.c_str(),"RECREATE");
  m_tro = new TTree("tro","tro");

  m_eventData = new GsimEventData();
  m_tr->SetBranchAddress("Event.",&m_eventData);
  m_gp = new GsimGenParticleData();
  m_tr->SetBranchAddress("GenParticle.",&m_gp);

  m_nEntries=m_tr->GetEntries();
  m_loopCount=0;

  for(int k=0;k<10;k++) {
    m_detData[k] = new GsimDetectorEventData();
  }
  for(int k=0;k<10;k++) {
    m_tr->SetBranchAddress(m_detName[k].c_str(),&m_detData[k]);
  }
}


bool E14FsimPersistencyManager::loop()
{
  m_tr->GetEntry( m_loopCount );

  if(m_loopCount==m_nEntries) return false;

  Long64_t centry = m_tr->LoadTree(m_loopCount);
  if (centry < 0) return false;
  m_tr->GetEntry(m_loopCount);
  m_loopCount++;
  return true;
}

void E14FsimPersistencyManager::fillTree()
{
  m_tro->Fill();
  


}

int E14FsimPersistencyManager::getEntries()
{
  if(m_tr)
    return m_tr->GetEntries();
  else return -1;
}

void E14FsimPersistencyManager::branch(const char* brName,void* address, const char* format)
{
  m_tro->Branch(brName,address,format);
}


void E14FsimPersistencyManager::close()
{
  m_tfo->cd();
  m_tro->Write();
  m_tfo->Close();
  m_tf->Close();
}

