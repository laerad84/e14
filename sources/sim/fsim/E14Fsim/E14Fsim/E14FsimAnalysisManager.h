#ifndef E14FsimAnalysisManager_h
#define E14FsimAnalysisManager_h

#include "E14Fsim/E14FsimAnalysisModule.h"
#include "E14Fsim/E14FsimMcGamma.h"
#include "E14Fsim/E14FsimVeto.h"
#include "E14Fsim/E14FsimClusterPatternGenerator.h"

#include <iostream>
#include <iomanip>
#include <list>
#include <string>
#include <vector>

class GsimGenParticleData;
class GsimDetectorEventData;
class TFile;
class TTree;

class E14FsimCCModule;
class E14FsimBARModule;
class E14FsimCSIModule;
class E14FsimBHPVModule;
class E14FsimGenParticleModule;
class E14FsimVetoModule;

class E14FsimAnalysisManager
{
 public:
  E14FsimAnalysisManager(char* ifileName,char* ofileName, int nSel=-1,
			 int iCluster=-1, int iFusion=0, int iSmear=1);
  virtual ~E14FsimAnalysisManager();

  void importModule(E14FsimAnalysisModule* mod);

  void run();
  void beginOfRun();
  void processEvent();
  void endOfRun();
  
 private:
  void deleteAndClearModules();

  int m_nEventRequest;
  int m_event;

  int m_nClusterRequest;
  
  std::list<E14FsimAnalysisModule*> m_moduleList;
  E14FsimClusterPatternGenerator m_cpg;

  E14FsimGenParticleModule* m_GenParticleModule;

  //  E14FsimCCModule*   m_CC01Module;
  E14FsimCCModule*   m_CC02Module;
  E14FsimCCModule*   m_CC03Module;
  E14FsimCCModule*   m_CC04Module;
  E14FsimCCModule*   m_CC05Module;
  E14FsimCCModule*   m_CC06Module;
  E14FsimBARModule*  m_CBARModule;
  E14FsimBARModule*  m_FBARModule;
  E14FsimCSIModule*  m_CSIModule;
  E14FsimBHPVModule* m_BHPVModule;
  
  E14FsimVetoModule* m_VetoModule;
  
};
#endif //E14FsimAnalysisManager_h
