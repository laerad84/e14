#ifndef E14FsimCSIModule_h
#define E14FsimCSIModule_h

#include "E14Fsim/E14FsimAnalysisModule.h"
#include "E14Fsim/E14FsimMcGamma.h"
#include "E14Fsim/E14FsimCluster.h"

#include <vector>
#include <list>

class E14FsimCSIModule : public E14FsimAnalysisModule
{
 public:
  E14FsimCSIModule();
  virtual ~E14FsimCSIModule();

  virtual void beginOfRun();
  virtual void processEvent();
  virtual void processOneClusterPattern(std::list<int>& pattern);
  virtual void postClustering();
  virtual void endOfEvent();

  int getNMcGamma();
 protected:

  void fillClusterData();
  void clearMcGammaData();
  void clearClusterData();

  void initVariables();
  
  int    m_detID;

  //MC gamma info
  std::vector<E14FsimMcGamma*> m_mcGammaVec;

  //Clustering
  std::vector<E14FsimCluster*> m_clusterVec;
  std::list<E14FsimMcGamma*>   m_ineffGammaList;

  //noFusionProb =
  //         m_noFusionProbWithoutZeroProduction *
  //         [ Prod_{m_numberOfZeroProduction} 0 ]
  double m_noFusionProbWithoutZeroProduction;
  int    m_numberOfZeroProduction;
  
  double m_sumW;


  int     eventID;
  //Cluster information
  int     nHitCluster;
  double  ClusterHitPos[50][3]; //[nHitCluster]
  double  ClusterHitTotE[50]; //[nHitCluster]
  double  ClusterHitTime[50]; //[nHitCluster]
  int     ClusterHitThisID[50];//[nHitCluster]
  int     ClusterHitParentID[50];//[nHitCluster]
  double  ClusterHitAng[50][3];//[nHitCluster]
  double  ClusterHitTrueP[50][3];//[nHitCluster]
  double  ClusterHitSigmaE[50];//[nHitCluster]
  double  ClusterHitSigmaXY[50];//[nHitCluster]
  double  ClusterEffi;
  double  CalHitClusterWeight;
  double  CalIneffiGammaWeight;
  double  ClusterFusionProb;

  double  ClusterWeight;
  double  EventWeight;
};

inline int E14FsimCSIModule::getNMcGamma()
{
  return m_mcGammaVec.size();
}
#endif
