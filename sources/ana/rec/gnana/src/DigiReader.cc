#include <sstream>
#include "gnana/DigiReader.h"
#include "gnana/E14GNAnaDataContainer.h"

DigiReader::DigiReader(TTree *tr){
  m_tr = tr;
  for(int i=0; i<s_maxDet; i++){
    m_detName[i]="";
  }
  m_detName[CC01] = "CC01.";
  m_detName[CC02] = "CC02.";
  m_detName[CC03] = "CC03.";
  m_detName[CC04] = "CC04.";
  m_detName[CC05] = "CC05.";
  m_detName[CC06] = "CC06.";
  m_detName[CBAR] = "CBAR.";
  m_detName[FBAR] = "FBAR.";
  m_detName[CSI] = "CSI.";
  m_detName[BHPV] = "BHPV.";
  m_detName[CV] = "CV.";
  m_detName[BCV] = "BCV.";
  m_detName[BHCV] = "BHCV.";

  for(int i=0;i<s_maxDet;i++){
    m_det[i] =  new GsimDetectorEventData();
    if(m_detName[i].empty()) continue;
    m_tr->SetBranchAddress(m_detName[i].c_str(),&m_det[i]);
  }
  m_genPar = new GsimGenParticleData();
  m_genParName = "GenParticle.";
  m_tr->SetBranchAddress(m_genParName.c_str(),&m_genPar);
  
  std::stringstream ss;
  ss<<"DigiReader:: Assign detector-ID as follows... "<<std::endl;
  for(int i=0;i<s_maxDet;i++){
    if(m_detName[i].empty()) continue;
    ss<<"ID "<<i<<":"<<m_detName[i]<<" ";
  }
  GsimMessage::getInstance()->report("info",ss.str().c_str());

  //  setAllBranchStatus(false);
  //  setCSIBranchStatus(true,"digi");
  //  setVetoBranchStatus(true,"digi");
}

DigiReader::~DigiReader(){
  for(int idet=0;idet<s_maxDet;idet++){
    delete m_det[idet];
  }
}

int DigiReader::addDetector(std::string detName){
  for(int i=0;i<s_maxDet;i++){
    if(m_detName[i].empty()){
      m_detName[i] = detName;
      m_det[i] =  new GsimDetectorEventData();
      m_tr->SetBranchAddress(m_detName[i].c_str(),&m_det[i]);
      GsimMessage::getInstance()->report("info",Form("DigiReader::addDetector:  ID %d:%s",i,m_detName[i].c_str()));
      return  i;
    }
  }
  
  GsimMessage::getInstance()->report("warning","too many detectors. Ignored AddDetector()");
  return -1;
}

/*
void DigiReader::setBranchStatus(int detID,bool stat, std::string bname ) {
  if(bname.empty()) bname = "*";
  m_tr->SetBranchStatus((m_detName[detID]+bname).c_str(),stat);
}

void DigiReader::setGenParticleBranchStatus(bool stat, std::string bname) {
  if(bname.empty()) bname = "*";
  m_tr->SetBranchStatus((m_genParName+bname).c_str(),stat);
}

void DigiReader::setVetoBranchStatus(bool stat, std::string bname) {
  for(int i=0;i<s_maxDet;i++){
    if(m_detName[i].empty())continue;
    if(m_detName[i]=="CSI.")continue;
    setBranchStatus(i,stat,bname);
  }
}

void DigiReader::setCC01BranchStatus(bool stat, std::string bname) {
  setBranchStatus(CC01,stat,bname);
}
void DigiReader::setCC02BranchStatus(bool stat, std::string bname) {
  setBranchStatus(CC02,stat,bname);
}
void DigiReader::setCC03BranchStatus(bool stat, std::string bname) {
  setBranchStatus(CC03,stat,bname);
}
void DigiReader::setCC04BranchStatus(bool stat, std::string bname) {
  setBranchStatus(CC04,stat,bname);
}
void DigiReader::setCC05BranchStatus(bool stat, std::string bname) {
  setBranchStatus(CC05,stat,bname);
}
void DigiReader::setCC06BranchStatus(bool stat, std::string bname) {
  setBranchStatus(CC06,stat,bname);
}
void DigiReader::setFBARBranchStatus(bool stat, std::string bname) {
  setBranchStatus(FBAR,stat,bname);
}
void DigiReader::setCBARBranchStatus(bool stat, std::string bname) {
  setBranchStatus(CBAR,stat,bname);
}
void DigiReader::setCVBranchStatus(bool stat, std::string bname) {
  setBranchStatus(CV,stat,bname);
}
void DigiReader::setBCVBranchStatus(bool stat, std::string bname) {
  setBranchStatus(BCV,stat,bname);
}
void DigiReader::setBHCVBranchStatus(bool stat, std::string bname) {
  setBranchStatus(BHCV,stat,bname);
}
void DigiReader::setBHPVBranchStatus(bool stat, std::string bname) {
  setBranchStatus(BHPV,stat,bname);
}
void DigiReader::setCSIBranchStatus(bool stat, std::string bname) {
  setBranchStatus(CSI,stat,bname);
}
*/

int DigiReader::getDetID(std::string detName) const{
  if(detName.empty()) return -1;
  
  for(int i=0;i<s_maxDet;i++){
    if(detName==m_detName[i]) return i;
  }

  return -1;
}

TClonesArray* DigiReader::getDigi(int const detID){
  return m_det[detID]->digi;
}

TClonesArray* DigiReader::getHits(int const detID){
  return m_det[detID]->hits;
}

TClonesArray* DigiReader::getTrack(){
  return m_genPar->briefTracks;
}


void DigiReader::getDigi(int const detID,int &nDigi,
			 int id[],double E[],double time[]) const{
  TClonesArray *arr = m_det[detID]->digi;
  nDigi = arr->GetEntries();
  for(int i=0;i<nDigi;i++){
    GsimDigiData* digi = (GsimDigiData*) arr->At(i);
    id[i] = digi->modID;
    E[i] = digi->energy;
    time[i] = digi->time;
  }
}

void DigiReader::getCsiDigi(int &nDigi,int id[],double E[],double time[]) const{
  getDigi(CSI,nDigi,id,E,time);
}




int DigiReader::getDigiSize(int const detID) const{
  return m_det[detID]->digi->GetEntries();
}

int DigiReader::getCsiDigiSize() const{
  return m_det[CSI]->digi->GetEntries();
}

int DigiReader::getDigiId(int const detID,int const i) const{
  GsimDigiData* digi = (GsimDigiData*) m_det[detID]->digi->At(i);
  if(!digi) return -1;
  return digi->modID;
}

int DigiReader::getCsiDigiId(int const i) const{
  GsimDigiData* digi = (GsimDigiData*) m_det[CSI]->digi->At(i);
  if(!digi) return -1;
  return digi->modID;
}


double DigiReader::getDigiEne(int const detID,int const i) const{
  GsimDigiData* digi = (GsimDigiData*) m_det[detID]->digi->At(i);
  if(!digi) return -1;
  return digi->energy;
}

double DigiReader::getCsiDigiEne(int const i) const{
  GsimDigiData* digi = (GsimDigiData*) m_det[CSI]->digi->At(i);
  if(!digi) return -1;
  return digi->energy;
}

double DigiReader::getDigiTime(int const detID,int const i) const{
  GsimDigiData* digi = (GsimDigiData*) m_det[detID]->digi->At(i);
  if(!digi) return -1;
  return digi->time;
}

double DigiReader::getCsiDigiTime(int const i) const{
  GsimDigiData* digi = (GsimDigiData*) m_det[CSI]->digi->At(i);
  if(!digi) return -1;
  return digi->time;
}

double DigiReader::getTotalEnergy(int const detID) const{
  return m_det[detID]->totalEnergy;
}

double DigiReader::getCsiTotalEnergy() const{
  return m_det[CSI]->totalEnergy;
}
