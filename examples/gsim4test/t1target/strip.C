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

  // strip pid input output

  if(argc!=4) {
    std::cerr << "# of arguments error." << std::endl;
    return 1;
  }
  
  int pid=std::atoi(argv[1]);
  char* ifname = argv[2];
  char* ofname = argv[3];
  
  GsimDetectorEventData* det0 = new GsimDetectorEventData();

  // fileopen 
  TFile* tfi = new  TFile(ifname);
  
  

  // set address
  TTree* tr = (TTree*)tfi->Get("eventTree00");
  tr->SetBranchAddress("det0.",&det0);

  TFile* tfo = new  TFile(ofname,"RECREATE");
  GsimDetectorEventData* deto = new GsimDetectorEventData();
  TTree* tro = new TTree("eventTree00","eventTree00");
  tro->Branch("det0.","GsimDetectorEventData",&deto);


  Int_t nevent = Int_t(tr->GetEntries()); // Number of events

  // event loop start
  for (Int_t jentry=0; jentry<nevent;jentry++) {

    Int_t ientry = tr->LoadTree(jentry); 
    if (ientry < 0) break;
    tr->GetEntry(jentry);
    
    // get nhit and print it
    int nHit = det0->nHit; // Number of hit in the det0 detector
    
    TClonesArray* HitArray = det0->hits;
    GsimDetectorHitData* aHit = 0;
    // loop for all hits of an event
    deto->Clear();
    TClonesArray &ar = *(deto->hits);
    
    int cnt=0;
    for (Int_t ihit=0; ihit<nHit; ihit++){
      GsimDetectorHitData* aHit = (GsimDetectorHitData*)HitArray->UncheckedAt(ihit);
      if( aHit->pid == pid ){
	GsimDetectorHitData* data = new (ar[cnt]) GsimDetectorHitData();
	
	data->thisID=aHit->thisID;
	data->track=aHit->track;
	data->stop=aHit->stop;
	data->hitChannel=aHit->hitChannel;

	data->time=aHit->time;
	data->edep=aHit->edep;
	data->pid=aHit->pid;
	data->r=aHit->r;
	data->ek=aHit->ek;
	data->p=aHit->p;

	cnt++;
      }
    }
    if(cnt>0)
      tro->Fill();
  }
  
  tfo->Write();
  tfo->Close();
  tfi->Close();
  
  return 0;
}
