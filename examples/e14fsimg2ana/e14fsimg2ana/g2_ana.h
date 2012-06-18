#ifndef g2_ana_h
#define g2_ana_h

#include "pi0/Pi0.h"

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2D.h>
#include <list>

class g2_ana
{
 public:
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain
  
  std::list<Gamma> SetGammaList();
  Int_t cutSet(Pi0& pi0);
  void  fillHist(Pi0& pi0, Int_t iCut);
  Pi0   detPi0(std::list<Pi0>& pi0list);
  void  MakeTree(TFile* tf);



  Bool_t cutline(Double_t x1, Double_t y1, Double_t x2, Double_t y2,
	       Double_t var1, Double_t var2);
  Bool_t pi0kine_cut();

  // Declaration of leave types
  Double_t        KDecayMome[3];
  Double_t        KDecayPos[3];
  Double_t        KDecayTime;
  Int_t           Pi0number;
  Double_t        Pi0Mome[10][3];   //[Pi0number]
  Double_t        Pi0Pos[10][3];   //[Pi0number]
  Double_t        Pi0Time[10];
  Int_t           eventID;
  Int_t           nHitCluster;
  Double_t        ClusterHitPos[50][3];   //[nHitCluster]
  Double_t        ClusterHitTotE[50];   //[nHitCluster]
  Double_t        ClusterHitAng[50][2];   //[nHitCluster]
  Double_t        ClusterHitTime[50];   //[nHitCluster]
  Int_t           ClusterHitThisID[50];   //[nHitCluster]
  Int_t           ClusterHitParentID[50];   //[nHitCluster]
  Double_t        ClusterHitTrueP[50][3];   //[nHitCluster]
  Double_t        ClusterHitSigmaE[50];   //[nHitCluster]
  Double_t        ClusterHitSigmaXY[50];   //[nHitCluster]
  Double_t        ClusterEffi;
  Double_t        ClusterFusionProb;
  Double_t        ClusterWeight;
  Double_t        EventWeight;
  Int_t           mcEventID;
  Int_t           nHitVeto;
  Int_t           VetoPID[100];   //[nHitVeto]
  Int_t           VetoDetID[100];   //[nHitVeto]
  Double_t        VetoPos[100][3];   //[nHitVeto]
  Double_t        VetoMome[100][3];   //[nHitVeto]
  Double_t        VetoIneffi[100];   //[nHitVeto]
  Double_t        DetVetoWeight[10];
  Double_t        VetoWeight;

  Int_t      EventID;
  Int_t      OrigEventID;
  Int_t      CutCondition;
  Int_t      RecEvenOdd;
  Double_t   RecVertZ;
  Double_t   RecVertZsig2;
  Double_t   RecPi0Pt;
  Double_t   RecPi0Mass;
  Double_t   RecPi0E;
  Double_t   RecPi0Px;
  Double_t   RecPi0Py;
  Double_t   RecPi0Pz;
  Double_t   RecPi0Vx;
  Double_t   RecPi0Vy;
  Double_t   RecPi0Vz;
  
  // List of branches
  TBranch        *b_KDecayMome;   //!
  TBranch        *b_KDecayPos;   //!
  TBranch        *b_KDecayTime;   //!
  TBranch        *b_Pi0number;   //!
  TBranch        *b_Pi0Mome;   //!
  TBranch        *b_Pi0Pos;   //!
  TBranch        *b_Pi0Time;   //!
  TBranch        *b_eventID;   //!
  TBranch        *b_nHitCluster;   //!
  TBranch        *b_ClusterHitPos;   //!
  TBranch        *b_ClusterHitTotE;   //!
  TBranch        *b_ClusterHitAng;   //!
  TBranch        *b_ClusterHitTime;   //!
  TBranch        *b_ClusterHitThisID;   //!
  TBranch        *b_ClusterHitParentID;   //!
  TBranch        *b_ClusterHitTrueP;   //!
  TBranch        *b_ClusterHitSigmaE;   //!
  TBranch        *b_ClusterHitSigmaXY;   //!
  TBranch        *b_ClusterEffi;   //!
  TBranch        *b_ClusterFusionProb;   //!
  TBranch        *b_ClusterWeight;   //!
  TBranch        *b_EventWeight;   //!
  TBranch        *b_mcEventID;   //!
  TBranch        *b_nHitVeto;   //!
  TBranch        *b_VetoPID;   //!
  TBranch        *b_VetoDetID;   //!
  TBranch        *b_VetoPos;   //!
  TBranch        *b_VetoMome;   //!
  TBranch        *b_VetoIneffi;   //!
  TBranch        *b_DetVetoWeight;   //!
  TBranch        *b_VetoWeight;   //!

  g2_ana(char* Filename,TTree *tree=0);
  virtual ~g2_ana();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);

      
  //-------------------------------------------------
  TObjArray* Hlist;
  TTree* tr;
  //-------------------------------------------------
   
  TH2D* hpt_vs_z_wtba;
  TH2D* hpt_vs_z_wtba_box;
  TH2D* hpt1_vs_z_wtba;
  TH2D* hpt1_vs_z_wtba_box;
  TH2D* hpt2_vs_z_wtba;
  TH2D* hpt2_vs_z_wtba_box;
  TH2D* hpt3_vs_z_wtba;
  TH2D* hpt3_vs_z_wtba_box;
   
  //-------------------------------------------------
  // Histgram for error caliculation   

  TH2D* ehpt_vs_z_wtba;
  TH2D* ehpt_vs_z_wtba_box;
  TH2D* ehpt1_vs_z_wtba;
  TH2D* ehpt1_vs_z_wtba_box;
  TH2D* ehpt2_vs_z_wtba;
  TH2D* ehpt2_vs_z_wtba_box;
  TH2D* ehpt3_vs_z_wtba;
  TH2D* ehpt3_vs_z_wtba_box;

};

#endif
