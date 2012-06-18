/**
 *  @file   E14GNAnaDataContainer.h
 *  @brief  data container for Cluster, Pi0, Klong class
 *  @author Kazufumi Sato <sato@champ.hep.sci.osaka-u.ac.jp>
 *  @date   2011.9.23
 *  $Id: E14GNAnaDataContainer.h,v 1.0 2011/09/23 12:38 sato Exp $
 *  $Log: E14GNAnaDataContainer.h,v $
 *
 * This class converts Cluster, Gamma, Pi0 and Klong classes 
 * to simple array and vice versa
 *
 * E14Library has data container classes "Cluster", "Gamma", "Pi0" and "Klong" 
 * to record the result of clustering or reconstruction of pi0 or KL.
 * These classes were prepaired since E391a experiment
 * and they are used in various programs.
 * But they are not TObject class, so it is bothersome
 * to input or output to TTree.
 *
 * This class converts them in the form of simple arrays 
 * to make easy to handle TTree.
 *
 * This calss also have member variables to record GsimDigiData of detectors.
 */

#ifndef E14GNAnaDataContainer_h_
#define E14GNAnaDataContainer_h_

#include <cstdlib>
#include "GsimPersistency/GsimMessage.h"
#include "cluster/Cluster.h"
#include "gamma/Gamma.h"
#include "pi0/Pi0.h"
#include "klong/Klong.h"
#include "gnana/DigiReader.h"
#include "TTree.h"

class E14GNAnaDataContainer{
 public:
  E14GNAnaDataContainer();
  ~E14GNAnaDataContainer();

  // setting branches
 public:
  void branchOfDigi(TTree *tr);
  //  void branchOfCsiDigi(TTree *tr);
  //  void branchOfVetoDigi(TTree *tr);
  void branchOfClusterList(TTree *tr);
  void branchOfKlong(TTree *tr,int nKlong = 2);
  void branchOfPi0List(TTree *tr);
  void branchOfGammaList(TTree *tr);

  void setBranchAddress(TTree *tr);
  void setNKlong(int num){m_nFillKlong = num;}
 private:
  void branchOfGlobal(TTree *tr);
  void branchOfClass(TTree *tr,int mode);

 public:
  // data container handling
  void reset();
  void resetClassNumber(){
    GamClusNumber = GammaNumber = Pi0Number = KlongNumber = 0;
    m_clusMemo.clear();
  }
  void resetClusterNumber(){ ClusterNumber = 0; }
  void resetDigiNumber(){CsiNumber = VetoNumber = 0;}

  bool getData(std::list<Cluster> &clusList) const;
  bool getData(std::list<Gamma> &gamList) const;
  bool getData(std::list<Pi0> &piList) const;
  bool getData(std::vector<Klong> &klVec) const;
  bool getData(Klong &kl ,int klID = 0) const;

  void setData( std::list<Cluster> const &clusList );
  void setData( std::list<Gamma> const &gamList );
  void setData( std::list<Pi0> const &pi0List );
  void setData( std::vector<Klong> const &klVec );
  void setData( Klong const &kl,bool standalone = true);
  void setData( DigiReader const &digiReader );
  
 private:
  int  m_nFillKlong;
  int  m_mode;
  std::list<Cluster> m_clusMemo;

  bool getCluster(Cluster &clus,int clusID) const;
  bool getGamClus(Cluster &clus,int clusID) const;
  bool getGamma(Gamma &gam,int gamID) const;
  bool getPi0(Pi0 &pi,int piID) const;
  //  bool getKlong(Klong &kl,int klID = 0) const;

  void setCluster( Cluster const &cluster,int clusterID);
  void setGamClus();
  void setGamma( Gamma const &gam);
  void setPi0( Pi0 const &pi0);

  void initAll();  
  
 public:
  
  static int const s_arrSize = 120;
  static int const s_digiArrSize = 5000;

  Int_t      eventID;
  Int_t      OrigEventID;
  Int_t      CutCondition;
  Int_t      VetoCondition;

  // data container for Cluster, Pi0, Klong
  Int_t           ClusterNumber;
  Int_t           ClusterId[s_arrSize];   //[ClusterNumber]
  Int_t           ClusterStatus[s_arrSize];   //[ClusterNumber]
  Double_t        ClusterThreshold[s_arrSize];   //[ClusterNumber]
  Double_t        ClusterDepE[s_arrSize];   //[ClusterNumber]
  Double_t        ClusterCoePos[s_arrSize][3];   //[ClusterNumber]
  Double_t        ClusterTime[s_arrSize];   //[ClusterNumber]
  Double_t        ClusterRMS[s_arrSize];  //[ClusterNumber]
  Int_t           ClusterSize[s_arrSize]; //[ClusterNumber]
  Int_t           ClusterCsiId[s_arrSize][s_arrSize];
  Double_t        ClusterCsiE[s_arrSize][s_arrSize];
  Double_t        ClusterCsiTime[s_arrSize][s_arrSize];


  // data constainer for Klong, Pi0, Gamma and its Cluster.
  Int_t           GamClusNumber;
  Int_t           GamClusId[s_arrSize];   //[GamClusNumber]
  Int_t           GamClusStatus[s_arrSize];   //[GamClusNumber]
  Double_t        GamClusThreshold[s_arrSize];   //[GamClusNumber]
  Double_t        GamClusDepE[s_arrSize];   //[GamClusNumber]
  Double_t        GamClusCoePos[s_arrSize][3];   //[GamClusNumber]
  Double_t        GamClusTime[s_arrSize];   //[GamClusNumber]
  Double_t        GamClusRMS[s_arrSize];  //[GamClusNumber]
  Int_t           GamClusSize[s_arrSize]; //[GamClusNumber]
  Int_t           GamClusCsiId[s_arrSize][s_arrSize];
  Double_t        GamClusCsiE[s_arrSize][s_arrSize];
  Double_t        GamClusCsiTime[s_arrSize][s_arrSize];

  Int_t           GammaNumber;
  Int_t           GammaId[s_arrSize];   //[GammaNumber]
  Int_t           GammaStatus[s_arrSize];   //[GammaNumber]
  Double_t        GammaE[s_arrSize];   //[GammaNumber]
  Double_t        GammaPos[s_arrSize][3];   //[GammaNumber]
  Double_t        GammaTime[s_arrSize];   //[GammaNumber]
  Double_t        GammaMom[s_arrSize][3];   //[GammaNumber]
  Double_t        GammaSigmaE[s_arrSize];   //[GammaNumber]
  Double_t        GammaSigmaPos[s_arrSize][3];   //[GammaNumber]
  Double_t        GammaChi2[s_arrSize];  //[GammaNumber]
  Double_t        GammaAnn[s_arrSize];  //[GammaNumber]
  Int_t           Gamma_clusIndex[s_arrSize];  //[GammaNumber] 


  Int_t           Pi0Number;
  Int_t           Pi0Id[s_arrSize]; //[Pi0Number]
  Int_t           Pi0Status[s_arrSize]; //[Pi0Number]
  Double_t        Pi0E[s_arrSize]; //[Pi0Number]
  Double_t        Pi0Pos[s_arrSize][3];   //[Pi0Number][3]
  Double_t        Pi0Mom[s_arrSize][3];   //[Pi0Number][3]
  Double_t        Pi0Pt[s_arrSize]; //[Pi0Number]
  Double_t        Pi0Mass[s_arrSize]; //[Pi0Number]
  Double_t        Pi0RecZ[s_arrSize]; //[Pi0Number]
  Double_t        Pi0RecZsig2[s_arrSize]; //[Pi0Number]
  Int_t           Pi0_gamIndex[s_arrSize][2];  //[Pi0Number]

  Int_t           KlongNumber;
  Int_t           KlongId[s_arrSize]; //[KlongNumber]
  Int_t           KlongStatus[s_arrSize]; //[KlongNumber]
  Double_t        KlongE[s_arrSize]; //[KlongNumber]
  Double_t        KlongPos[s_arrSize][3];   //[KlongNumber]
  Double_t        KlongMom[s_arrSize][3];  //[KlongNumber]
  Double_t        KlongPt[s_arrSize]; //[KlongNumber]
  Double_t        KlongMass[s_arrSize]; //[KlongNumber]
  Double_t        KlongDeltaZ[s_arrSize]; //[KlongNumber]
  Double_t        KlongChisqZ[s_arrSize]; //[KlongNumber]
  Int_t           KlongSortFlag[s_arrSize]; //[KlongNumber]
  Int_t           KlongVertFlag[s_arrSize]; //[KlongNumber]
  Int_t           Klong_piIndex[s_arrSize][3];   //[KlongNumber][3]

  // data container for GsimDigiData
  Int_t           CsiNumber;
  Int_t           CsiModID[s_digiArrSize];   //[CsiNumber]
  Double_t        CsiEne[s_digiArrSize];   //[CsiNumber]
  Double_t        CsiTime[s_digiArrSize];   //[CsiNumber]
  
  Int_t           VetoNumber;
  Int_t           VetoDetID[s_digiArrSize];   //[VetoNumber]
  Int_t           VetoModID[s_digiArrSize];   //[VetoNumber]
  Double_t        VetoEne[s_digiArrSize];   //[VetoNumber]
  Double_t        VetoTime[s_digiArrSize];   //[VetoNumber]
};




#endif
