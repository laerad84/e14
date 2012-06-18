#include "gamma/Gamma.h"
#include "rec2g/Rec2g.h"
#include "pi0/Pi0.h"
#include "e14fsimg2ana/g2_ana.h"

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>

Int_t main(Int_t argc,char** argv)
{

  if(argc !=3) {
    std::cerr << "Argument error." << std::endl;
    return 1;
  }

  
  char* ifname = argv[1];
  char* ofname = argv[2];

  g2_ana  ana_g2(ifname);
  TFile* out = new TFile(ofname,"RECREATE");
  
  ana_g2.MakeTree(out);
 
  if(ana_g2.fChain == 0);
  Long64_t nevent = ana_g2.fChain->GetEntriesFast();    
  std::cout << "N events : " << nevent << std::endl;
  Int_t in=int(nevent/100);
  if(in==0) in=1;
  
  Long64_t maxsize = 100000;
  maxsize *= 100000;
  
  // event loop start
  Long64_t nbytes = 0,nb=0;
  for (Long64_t jentry=0; jentry<nevent;jentry++) {
    
    if(jentry%in==0) {
      std::cout << (jentry/in) << " % processed." << std::endl;
    }
    
    Long64_t ientry = ana_g2.fChain->LoadTree(jentry); 
    if (ientry < 0) break;
    nb = ana_g2.fChain->GetEntry(jentry); nbytes+= nb;

    std::list<Gamma> glist = ana_g2.SetGammaList();

    if(glist.size() == 2){
      Rec2g rec2g;
      std::list<Pi0> pi0list = rec2g.recPi0withConstM(glist);
      
      if(pi0list.size()>0){
	//	if(pi0list.size()>2){
	//        std::cout<<pi0list.size()<<std::endl;
	//        getchar();
	//	}
	Pi0 pi0 = ana_g2.detPi0(pi0list);
	Int_t iCut = ana_g2.cutSet(pi0);
	ana_g2.fillHist(pi0,iCut);
	
      }      
    }
  }
 
  
  ana_g2.Hlist->Write();
  ana_g2.tr->Write();
  out->Close();
  
  return 0;
}
