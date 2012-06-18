#ifndef E14FsimPersistencyManager_h
#define E14FsimPersistencyManager_h

#include "GsimData/GsimEventData.h"
#include "GsimData/GsimGenParticleData.h"
#include "GsimData/GsimDetectorEventData.h"

#include "TFile.h"
#include "TTree.h"

class E14FsimPersistencyManager
{
 public:
  E14FsimPersistencyManager(char* ifileName,char* ofileName);
  ~E14FsimPersistencyManager();

  static E14FsimPersistencyManager* getPersistencyManager();


  void beginOfRun();
  bool loop();
  void fillTree();
  void close();
  
  
  void branch(const char* brName,void* address, const char* format);
  int  getEntries();

  GsimEventData*         getGsimEventData();
  GsimGenParticleData*   getGsimGenParticleData();
  GsimDetectorEventData* getDetectorEventData(int iDet);
  
 private:
  E14FsimPersistencyManager();
  static E14FsimPersistencyManager* s_persistencyManager;

  std::string m_ifname;
  std::string m_ofname;

  TFile* m_tf;
  TTree* m_tr;

  TFile* m_tfo;
  TTree* m_tro;

  GsimEventData*         m_eventData;
  GsimGenParticleData*   m_gp;
  std::string            m_detName[10];
  GsimDetectorEventData* m_detData[10];

  int m_nEntries;
  int m_loopCount;
  
};

inline GsimEventData* E14FsimPersistencyManager::getGsimEventData() {
  return m_eventData;
}

inline GsimGenParticleData* E14FsimPersistencyManager::getGsimGenParticleData() {
  return m_gp;
}

inline GsimDetectorEventData* E14FsimPersistencyManager::getDetectorEventData(int iDet) {
  if(iDet<0 || iDet>9) return 0;
  return m_detData[iDet];
}

#endif
