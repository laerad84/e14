#include "GsimData/GsimEventData.h"
#include "GsimData/GsimGenParticleData.h"
#include "GsimData/GsimTrackData.h"
#include "GsimData/GsimDetectorEventData.h"
#include "GsimData/GsimDetectorHitData.h"

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>


int main(int argc,char** argv)
{

  if(argc!=3) {
    std::cerr << "# of arguments error." << std::endl;
    return 1;
  }
  
  char* ifname = argv[1];
  char* ofname = argv[2];

  GsimEventData*   ev = new GsimEventData();
  GsimGenParticleData*   gp = new GsimGenParticleData();
  GsimDetectorEventData* det = new GsimDetectorEventData();

  // fileopen 
  TFile* tfi = new  TFile(ifname);

  // set address
  TTree* tr = (TTree*)tfi->Get("eventTree00");
  tr->SetBranchAddress("Event.",&ev);
  tr->SetBranchAddress("GenParticle.",&gp);
  tr->SetBranchAddress("det.",&det);


  TFile* tfo = new  TFile(ofname,"RECREATE");
  int    irun;
  int    ievent;
  int    maxID;
  double maxE;
  TTree* tro = new TTree("tro","tro");
  tro->Branch("irun",&irun,"irun/I");
  tro->Branch("ievent",&ievent,"ievent/I");
  tro->Branch("maxID",&maxID,"maxID/I");
  tro->Branch("maxE",&maxE,"maxE/D");

  Int_t nevent = Int_t(tr->GetEntries()); // Number of events

  std::cout << "N events : " << nevent << std::endl;
  int in=int(nevent/100);
  // event loop start
  for (Int_t jentry=0; jentry<nevent;jentry++) {

    if(jentry%in==0) {
      std::cout << (jentry/in) << " % processed." << std::endl;
    }

    Int_t ientry = tr->LoadTree(jentry); 
    if (ientry < 0) break;
    tr->GetEntry(jentry);

    UShort_t run_number=ev->run_number;
    UShort_t event_number=ev->event_number;
    
    irun=run_number;
    ievent=event_number;
    
    // get nhit and print it
    TClonesArray* GPArray  = gp->briefTracks;
    TClonesArray* DetDigiArray = det->digi;
    
    int nGP=GPArray->GetEntries();
    int nDetDigi=DetDigiArray->GetEntries();
    
    if(nGP>1) {
      gp->dump();
    }
    
    for (Int_t iGP=0; iGP<nGP; iGP++){
      GsimTrackData* aTrack = (GsimTrackData*)GPArray->At(iGP);
    }

    maxID=-1;
    maxE=0;;
    for (Int_t iDetDigi=0; iDetDigi<nDetDigi; iDetDigi++){
      GsimDigiData* aDigi = (GsimDigiData*)DetDigiArray->At(iDetDigi);
      if(aDigi->energy>maxE) {
	maxE=aDigi->energy;
	maxID=aDigi->modID;
      }
    }
    tro->Fill();
  }
  tro->Write();
  tfo->Close();
  tfi->Close();
  
  return 0;
}
