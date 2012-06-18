#include "../e14fsimg2ana/g2_ana.h"
#include "gamma/Gamma.h"

#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"

#include <TH2.h>
#include <TMath.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <list>


g2_ana::g2_ana(char* Filename,TTree *tree)
{
  if (tree == 0) {
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(Filename);
    if (!f) {
      f = new TFile(Filename);
    }
    tree = (TTree*)gDirectory->Get("tro");

  }
  Init(tree);
}

g2_ana::~g2_ana()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t g2_ana::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t g2_ana::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (!fChain->InheritsFrom(TChain::Class()))  return centry;
  TChain *chain = (TChain*)fChain;
  if (chain->GetTreeNumber() != fCurrent) {
    fCurrent = chain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void g2_ana::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normaly not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("KDecayMome", KDecayMome, &b_KDecayMome);
  fChain->SetBranchAddress("KDecayPos", KDecayPos, &b_KDecayPos);
  fChain->SetBranchAddress("KDecayTime", &KDecayTime, &b_KDecayTime);
  fChain->SetBranchAddress("Pi0number", &Pi0number, &b_Pi0number);
  fChain->SetBranchAddress("Pi0Mome", Pi0Mome, &b_Pi0Mome);
  fChain->SetBranchAddress("Pi0Pos", Pi0Pos, &b_Pi0Pos);
  fChain->SetBranchAddress("Pi0Time", Pi0Time, &b_Pi0Time);
  fChain->SetBranchAddress("eventID", &eventID, &b_eventID);
  fChain->SetBranchAddress("nHitCluster", &nHitCluster, &b_nHitCluster);
  fChain->SetBranchAddress("ClusterHitPos", ClusterHitPos, &b_ClusterHitPos);
  fChain->SetBranchAddress("ClusterHitTotE", ClusterHitTotE, &b_ClusterHitTotE);
  fChain->SetBranchAddress("ClusterHitAng", ClusterHitAng, &b_ClusterHitAng);
  fChain->SetBranchAddress("ClusterHitTime", ClusterHitTime, &b_ClusterHitTime);
  fChain->SetBranchAddress("ClusterHitThisID", ClusterHitThisID, &b_ClusterHitThisID);
  fChain->SetBranchAddress("ClusterHitParentID", ClusterHitParentID, &b_ClusterHitParentID);
  fChain->SetBranchAddress("ClusterHitTrueP", ClusterHitTrueP, &b_ClusterHitTrueP);
  fChain->SetBranchAddress("ClusterHitSigmaE", ClusterHitSigmaE, &b_ClusterHitSigmaE);
  fChain->SetBranchAddress("ClusterHitSigmaXY", ClusterHitSigmaXY, &b_ClusterHitSigmaXY);
  fChain->SetBranchAddress("ClusterEffi", &ClusterEffi, &b_ClusterEffi);
  fChain->SetBranchAddress("ClusterFusionProb", &ClusterFusionProb, &b_ClusterFusionProb);
  fChain->SetBranchAddress("ClusterWeight", &ClusterWeight, &b_ClusterWeight);
  fChain->SetBranchAddress("EventWeight", &EventWeight, &b_EventWeight);
  fChain->SetBranchAddress("mcEventID", &mcEventID, &b_mcEventID);
  fChain->SetBranchAddress("nHitVeto", &nHitVeto, &b_nHitVeto);
  fChain->SetBranchAddress("VetoPID", VetoPID, &b_VetoPID);
  fChain->SetBranchAddress("VetoDetID", VetoDetID, &b_VetoDetID);
  fChain->SetBranchAddress("VetoPos", VetoPos, &b_VetoPos);
  fChain->SetBranchAddress("VetoMome", VetoMome, &b_VetoMome);
  fChain->SetBranchAddress("VetoIneffi", VetoIneffi, &b_VetoIneffi);
  fChain->SetBranchAddress("DetVetoWeight", DetVetoWeight, &b_DetVetoWeight);
  fChain->SetBranchAddress("VetoWeight", &VetoWeight, &b_VetoWeight);
   
   
  hpt_vs_z_wtba = new TH2D("hpt_vs_z_wtba" , "Pt vs. Z without Pt and Z cut",30, 0, 6000, 100, 0, 300);
  hpt1_vs_z_wtba = new TH2D("hpt1_vs_z_wtba" , "Pt vs. Z without Pt and Z cut(Odd) ",30, 0, 6000, 100, 0, 300);
  hpt2_vs_z_wtba = new TH2D("hpt2_vs_z_wtba" , "Pt vs. Z without Pt and Z cut(Even)",30, 0, 6000, 100, 0, 300);
  hpt3_vs_z_wtba = new TH2D("hpt3_vs_z_wtba" , "Pt vs. Z without Pt and Z cut(Fusion)",30, 0, 6000, 100, 0, 300);
  hpt_vs_z_wtba_box = new TH2D("hpt_vs_z_wtba_box" , "Pt vs. Z in the signal box",30, 0, 6000, 100, 0, 300);
  hpt1_vs_z_wtba_box = new TH2D("hpt1_vs_z_wtba_box" , "Pt vs. Z in the signal box(Odd)",30, 0, 6000, 100, 0, 300);
  hpt2_vs_z_wtba_box = new TH2D("hpt2_vs_z_wtba_box" , "Pt vs. Z in the signal box(Even)",30, 0, 6000, 100, 0, 300);
  hpt3_vs_z_wtba_box = new TH2D("hpt3_vs_z_wtba_box" , "Pt vs. Z in the signal box(Fusion)",30, 0, 6000, 100, 0, 300);

  ehpt_vs_z_wtba = new TH2D("ehpt_vs_z_wtba" , "Pt vs. Z without Pt and Z cut",30, 0, 6000, 100, 0, 300);
  ehpt1_vs_z_wtba = new TH2D("ehpt1_vs_z_wtba" , "Pt vs. Z without Pt and Z cut(Odd) ",30, 0, 6000, 100, 0, 300);
  ehpt2_vs_z_wtba = new TH2D("ehpt2_vs_z_wtba" , "Pt vs. Z without Pt and Z cut(Even)",30, 0, 6000, 100, 0, 300);
  ehpt3_vs_z_wtba = new TH2D("ehpt3_vs_z_wtba" , "Pt vs. Z without Pt and Z cut(Fusion)",30, 0, 6000, 100, 0, 300);
  ehpt_vs_z_wtba_box = new TH2D("ehpt_vs_z_wtba_box" , "Pt vs. Z in the signal box",30, 0, 6000, 100, 0, 300);
  ehpt1_vs_z_wtba_box = new TH2D("ehpt1_vs_z_wtba_box" , "Pt vs. Z in the signal box(Odd)",30, 0, 6000, 100, 0, 300);
  ehpt2_vs_z_wtba_box = new TH2D("ehpt2_vs_z_wtba_box" , "Pt vs. Z in the signal box(Even)",30, 0, 6000, 100, 0, 300);
  ehpt3_vs_z_wtba_box = new TH2D("ehpt3_vs_z_wtba_box" , "Pt vs. Z in the signal box(Fusion)",30, 0, 6000, 100, 0, 300);

  Hlist = new TObjArray(0);

  Hlist->Add(hpt_vs_z_wtba);
  Hlist->Add(hpt1_vs_z_wtba);
  Hlist->Add(hpt2_vs_z_wtba);
  Hlist->Add(hpt3_vs_z_wtba);
  Hlist->Add(hpt_vs_z_wtba_box);
  Hlist->Add(hpt1_vs_z_wtba_box);
  Hlist->Add(hpt2_vs_z_wtba_box);
  Hlist->Add(hpt3_vs_z_wtba_box);
  Hlist->Add(ehpt_vs_z_wtba);
  Hlist->Add(ehpt1_vs_z_wtba);
  Hlist->Add(ehpt2_vs_z_wtba);
  Hlist->Add(ehpt3_vs_z_wtba);
  Hlist->Add(ehpt_vs_z_wtba_box);
  Hlist->Add(ehpt1_vs_z_wtba_box);
  Hlist->Add(ehpt2_vs_z_wtba_box);
  Hlist->Add(ehpt3_vs_z_wtba_box);


  Notify();
}

Bool_t g2_ana::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normaly not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void g2_ana::Show(Long64_t entry)
{
  if (!fChain) return;
  fChain->Show(entry);
}

Int_t g2_ana::Cut(Long64_t )
{
  return 1;
}



std::list<Gamma>
g2_ana::SetGammaList(){
  std::list<Gamma> glist;
  Int_t id =0;

  for(Int_t iHitCluster=0; iHitCluster<nHitCluster; iHitCluster++){
    Gamma gamma;
    gamma.setPos(ClusterHitPos[iHitCluster][0],ClusterHitPos[iHitCluster][1],ClusterHitPos[iHitCluster][2]);
    gamma.setEnergy(ClusterHitTotE[iHitCluster]);
    
    gamma.setTime(ClusterHitTime[iHitCluster]);
    gamma.setId(id);
    gamma.setMcThisID(ClusterHitThisID[iHitCluster]);
    gamma.setMcParentID(ClusterHitParentID[iHitCluster]);
    gamma.setSigmaPos(ClusterHitSigmaXY[iHitCluster],ClusterHitSigmaXY[iHitCluster],0);
    //    gamma.setSigmaY(ClusterHitSigmaXY[iHitCluster]);
    gamma.setSigmaE(ClusterHitSigmaE[iHitCluster]);
    glist.push_back(gamma);
    id++;

  }    
  return( glist );
}

Pi0 g2_ana::detPi0(std::list<Pi0>& pi0list){

  if(pi0list.size()>2) std::cout<<"DEBUG Pi0 list size : "<<pi0list.size()<<std::endl;
  Pi0 pi0;
  if(pi0list.size()==1){
    pi0 = *(pi0list.begin());
  }
  else if(pi0list.size()>1){
     
    Double_t Pi0Mass = 134.9764;
    Double_t Pi0Mass2 = Pi0Mass*Pi0Mass;
    Double_t costheta_r[2];
    Double_t RecMass2[2];
    
    Int_t i=0;
    for(std::list<Pi0>::iterator it =pi0list.begin();it!=pi0list.end();it++){
     
      Gamma g1 = it->g1();
      Gamma g2 = it->g2();
      
      CLHEP::Hep3Vector P1(g1.x(),g1.y(),g1.z()-it->recZ());
      CLHEP::Hep3Vector P2(g2.x(),g2.y(),g2.z()-it->recZ());
      costheta_r[i] =P1.dot(P2) / P1.mag() / P2.mag();
      RecMass2[i] = 2 * g1.e() * g2.e() * (1 - costheta_r[i]);
      i++;
    }
    std::list<Pi0>::iterator it =pi0list.begin();
    if (TMath::Abs(RecMass2[0] - Pi0Mass2)
	< TMath::Abs(RecMass2[1] - Pi0Mass2)){
      pi0 = *it;
    }
    else{
      it++;
      pi0 = *it; 

    }
  }

  return pi0;
}

Int_t g2_ana::cutSet(Pi0& pi0){

  Gamma g1 = pi0.g1();
  Gamma g2 = pi0.g2();
  
  Int_t iCut  = 0;

  
  Double_t Egamma_Min = 0.1 * 1000; //GeV to MeV
  Double_t Egamma_Max = 2.0 * 1000; //GeV to MeV
  //  Double_t Egamma_Max = 10.0;
  
  Double_t R_Min =175;
  Double_t R_Max =850;
  //  Double_t R_Max =1350;  // for step2

  Double_t Zvert_Min =3000;
  Double_t Zvert_Max =5000;

  Double_t Pt_Min =0.13 * 1000; //GeV to MeV
  Double_t Pt_Max =0.25 * 1000; //GeV to MeV

  Double_t Acop_Min =30.; // deg

  Double_t gDist_Min =300.; //mm

  Double_t TotE_Min =0.5 * 1000; // GeV to MeV

  Double_t Etheta_Min =2.5 * 1000  ; //GeV to MeV 
  
  Double_t Eratio_Min = 0.2;

  //Energy Cut
  if( g1.e()  < Egamma_Min || g2.e() < Egamma_Min ||
      g1.e() > Egamma_Max || g2.e() > Egamma_Max)
    iCut = (iCut | 0x0001);
  
  //Fiducial in CsI
  Double_t R1 = g1.pos().perp();
  Double_t R2 = g2.pos().perp();

  if ( R1 < R_Min || R1 > R_Max
      ||  R2 < R_Min || R2 > R_Max)  iCut = (iCut | 0x0002);
  
  // Vertex Cut
  RecVertZ = pi0.recZ();
  if ( RecVertZ < Zvert_Min || RecVertZ > Zvert_Max) iCut = (iCut | 0x0004);

  // PT Cut
  RecPi0Pt = pi0.p3().perp();
  if ( RecPi0Pt < Pt_Min || RecPi0Pt > Pt_Max)  iCut = (iCut | 0x0008);

  RecPi0E  = pi0.e();
  RecPi0Px = pi0.p3().x();
  RecPi0Py = pi0.p3().y();
  RecPi0Pz = pi0.p3().z();
  RecPi0Vx = pi0.v().x();
  RecPi0Vy = pi0.v().y();
  RecPi0Vz = pi0.v().z();

  

  // Acp_angle  Cut
  Double_t acop;
  Double_t  ct = (g1.x()*g2.x()+g1.y()*g2.y())/R1/R2;
  if(TMath::Abs(ct) >= 1){
    acop = 0.0;
  }
  else{
    acop = TMath::Pi() - TMath::ACos(ct);
    acop = acop * 180. / TMath::Pi();
  }
  
  Double_t Acop_angle = acop;
  if (Acop_angle < Acop_Min) iCut = (iCut | 0x0010);
  
  //Two gamma distance
  CLHEP::Hep3Vector gdist = g1.pos()-g2.pos();
  Double_t gamma_dist = gdist.mag();
                              
  if (gamma_dist < gDist_Min) iCut = (iCut | 0x0020);
    
  //Total energy of two gammas
  Double_t E_tot = g1.e() + g2.e();
  if (E_tot < TotE_Min)  iCut = (iCut | 0x0040);
  
  // In_ang cut : Odd-pair cut
  Double_t  In_Ang1 = TMath::ATan(R1/(g1.z()-pi0.recZ()));
  In_Ang1 = In_Ang1 * 180 / TMath::Pi();
  Double_t  Etheta1 = g1.e() * In_Ang1;
  Double_t  In_Ang2 = TMath::ATan(R2/(g2.z()-pi0.recZ()));
  In_Ang2 = In_Ang2 * 180 / TMath::Pi();
  Double_t  Etheta2 = g2.e() * In_Ang2;


  if (Etheta1 < Etheta_Min || Etheta2 < Etheta_Min)
     iCut = (iCut | 0x0080);
  
  // E_ratio_cut
  Double_t Eratio = TMath::Min(g1.e(),g2.e())
                  / TMath::Max(g1.e(),g2.e());
  if (Eratio < Eratio_Min)    iCut = (iCut | 0x0100);

  // Pi0 Kinematic Cut
  if(pi0kine_cut())  {
    iCut = (iCut | 0x0200);
  }
  
  return iCut;  
}

void g2_ana::fillHist(Pi0& pi0,Int_t iCut){
  
  RecEvenOdd   = 0;
  RecVertZsig2 = pi0.recZsig2();

  CLHEP::HepLorentzVector p_pi0( pi0.p3(),pi0.e() );
  RecPi0Mass   = p_pi0.m();
  //  std::cout<<"DEBUG "<<RecVertZsig2<<"\t"<<RecPi0Mass<<std::endl;
  //getchar();
  CutCondition = iCut;
    
  Gamma g1 = pi0.g1();
  Gamma g2 = pi0.g2();
  if(g1.mcParentID() == g2.mcParentID()) RecEvenOdd = 1;
  if(int(g1.mcParentID())/10000<=-1 ||
     int(g2.mcParentID())/10000<=-1 ) RecEvenOdd = -1;
  
  
  OrigEventID = eventID;  
  tr->Fill();
  
  EventID+= 1;
  
  Bool_t AllButPtandZ = ((iCut | 0x000c) == 0x000c);
  Bool_t InTheSignalBox = (iCut == 0);
  
  Double_t RecWeightAll  = EventWeight;
  Double_t RecWeightAll2 = RecWeightAll*RecWeightAll;
  
  //std::cout<<RecVertZ<<" "<<RecPi0Pt<<" "<<iCut<<std::endl;
  // getchar();
 
  if (! AllButPtandZ) return;
  hpt_vs_z_wtba->Fill(RecVertZ,RecPi0Pt,RecWeightAll);
  
  if (RecEvenOdd == 0){
    hpt1_vs_z_wtba->Fill(RecVertZ,RecPi0Pt,RecWeightAll);
  }
  else if (RecEvenOdd == 1){
    hpt2_vs_z_wtba->Fill(RecVertZ,RecPi0Pt,RecWeightAll);
  }
  else if (RecEvenOdd == -1){    
    hpt3_vs_z_wtba->Fill(RecVertZ,RecPi0Pt,RecWeightAll);
  }

  if(InTheSignalBox){
    hpt_vs_z_wtba_box ->Fill(RecVertZ,RecPi0Pt,RecWeightAll);
    
    if (RecEvenOdd == 0){
      hpt1_vs_z_wtba_box ->Fill(RecVertZ,RecPi0Pt,RecWeightAll);
    }
    else if (RecEvenOdd == 1){
      hpt2_vs_z_wtba_box ->Fill(RecVertZ,RecPi0Pt,RecWeightAll);
    }
    else if (RecEvenOdd == -1){
      hpt3_vs_z_wtba_box ->Fill(RecVertZ,RecPi0Pt,RecWeightAll);
     }
  }

  // error sum
  ehpt_vs_z_wtba->Fill(RecVertZ,RecPi0Pt,RecWeightAll2);

  if (RecEvenOdd == 0){
    ehpt1_vs_z_wtba->Fill(RecVertZ,RecPi0Pt,RecWeightAll2);
  }
  else if (RecEvenOdd == 1){
    ehpt2_vs_z_wtba->Fill(RecVertZ,RecPi0Pt,RecWeightAll2);
  }
  else if (RecEvenOdd == -1){
    ehpt3_vs_z_wtba->Fill(RecVertZ,RecPi0Pt,RecWeightAll2);
  }
  
  if(InTheSignalBox){
    ehpt_vs_z_wtba_box ->Fill(RecVertZ,RecPi0Pt,RecWeightAll2);
    if (RecEvenOdd == 0){
      ehpt1_vs_z_wtba_box ->Fill(RecVertZ,RecPi0Pt,RecWeightAll2);
    }
    else if (RecEvenOdd == 1){
      ehpt2_vs_z_wtba_box ->Fill(RecVertZ,RecPi0Pt,RecWeightAll2);
    }
    else if (RecEvenOdd == -1){
      ehpt3_vs_z_wtba_box ->Fill(RecVertZ,RecPi0Pt,RecWeightAll2);
    }
  
  }
}

void g2_ana::MakeTree(TFile* tf){
  tf->cd();
  EventID =0;
  tr    = new TTree("Tree","Tree");
  tr->Branch("EventID",&EventID,"EventID/I");
  tr->Branch("OrigEventID",&OrigEventID,"OrigEventID/I");
  tr->Branch("mcEventID",&mcEventID,"mcEventID/I");
  tr->Branch("Pi0number",&Pi0number,"Pi0number/I");
  tr->Branch("Pi0Mome",Pi0Mome,"Pi0Mome[Pi0number][3]/D");
  tr->Branch("Pi0Pos",Pi0Pos,"Pi0Pos[Pi0number][3]/D");
  tr->Branch("nHitCluster",&nHitCluster,"nHitCluster/I");
  tr->Branch("ClusterHitTotE",ClusterHitTotE,"ClusterHitTotE[nHitCluster]/D");
  tr->Branch("ClusterHitPos",ClusterHitPos,"ClusterHitPos[nHitCluster][3]/D");
  tr->Branch("ClusterHitThisID",ClusterHitThisID,"ClusterHitThisID[nHitCluster]/I");
  tr->Branch("ClusterHitParentID",ClusterHitParentID,"ClusterHitParentID[nHitCluster]/I");
  tr->Branch("ClusterEffi",&ClusterEffi,"ClusterEffi/D");
  tr->Branch("ClusterFusionProb",&ClusterFusionProb,"ClusterFusionProb/D");
  tr->Branch("ClusterWeight",&ClusterWeight,"ClusterWeight/D");
  tr->Branch("EventWeight",&EventWeight,"EventWeight/D");
  tr->Branch("nHitVeto",&nHitVeto,"nHitVeto/I");
  tr->Branch("VetoPID",VetoPID,"VetoPID[nHitVeto]/I");
  tr->Branch("VetoDetID",VetoDetID,"VetoDetID[nHitVeto]/I");
  tr->Branch("VetoPos",VetoPos,"VetoPos[nHitVeto][3]/D");
  tr->Branch("VetoMome",VetoMome,"VetoMome[nHitVeto][3]/D");
  tr->Branch("VetoIneffi",VetoIneffi,"VetoIneffi[nHitVeto]/D");  
  tr->Branch("VetoWeight",&VetoWeight,"VetoWeight/D");

  tr->Branch("CutCondition",&CutCondition,"CutCondition/I");
  tr->Branch("RecEvenOdd",&RecEvenOdd ,"RecEvenOdd/I");
  tr->Branch("RecVertZ",&RecVertZ,"RecVertZ/D");
  tr->Branch("RecPi0Pt",&RecPi0Pt,"RecPi0Pt/D");
  tr->Branch("RecVertZsig2",&RecVertZsig2,"RecVertZsig2/D");
  tr->Branch("RecPi0Mass",&RecPi0Mass,"RecPi0Mass/D");
  tr->Branch("RecPi0E",&RecPi0E,"RecPi0E/D");
  tr->Branch("RecPi0Px",&RecPi0Px,"RecPi0Px/D");
  tr->Branch("RecPi0Py",&RecPi0Py,"RecPi0Py/D");
  tr->Branch("RecPi0Pz",&RecPi0Pz,"RecPi0Pz/D");
  tr->Branch("RecPi0Vx",&RecPi0Vx,"RecPi0Vx/D");
  tr->Branch("RecPi0Vy",&RecPi0Vy,"RecPi0Vy/D");
  tr->Branch("RecPi0Vz",&RecPi0Vz,"RecPi0Vz/D");
}

Bool_t g2_ana::cutline(Double_t x1, Double_t y1, Double_t x2, Double_t y2,
		     Double_t var1, Double_t var2)
{
  Double_t slope = ( y1 - y2 ) / ( x1 - x2 );
  Double_t intercept = y1 - slope * x1 ;
  Double_t y = slope * var1 + intercept;
  if ( var2 > y ) return kTRUE; // above the line
  return kFALSE;
}


Bool_t g2_ana::pi0kine_cut()
{
  Double_t cpi0pt=RecPi0Pt*1e-3;
  Double_t cpi0pz=RecPi0Pz*1e-3;
  Double_t cpi0recz=RecVertZ*1e-1;
  Double_t cpi0e=RecPi0E*1e-3;

  Bool_t flag = kFALSE;
  Double_t pratio = cpi0pt/cpi0pz;
  if (( cpi0recz < 400 )&&( pratio < 0.1 )) return kTRUE;
  if (( cpi0recz > 400 )&&
      !( cutline(400., 0.1, 500., 0.15, cpi0recz, pratio) )) return kTRUE;
  if ( !(cutline(300., 0.8, 500., 0.4, cpi0recz, cpi0e)) ) return kTRUE;
  if ( (cutline(300., 0.2, 500., 0.34, cpi0recz, pratio)) ) return kTRUE;
  return kFALSE;

}
