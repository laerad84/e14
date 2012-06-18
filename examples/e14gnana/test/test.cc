#include "gnana/E14GNAnaDataContainer.h"
#include "TFile.h"
#include "TChain.h"
#include <string>

int main(int argc, char** argv){
  std::string ifname = argv[1];
  std::string ofname = argv[2];
  E14GNAnaDataContainer data;
  TChain ch("Tree");
  ch.Add(ifname.c_str());
  data.setBranchAddress(&ch);
  TFile f(ofname.c_str(),"RECREATE");
  TTree tr("tr","");
  data.branchOfKlong(&tr);
  
  int nloop = ch.GetEntries();
  for(int ievt=0;ievt<nloop;ievt++){
    ch.GetEntry(ievt);
    Klong kl;
    data.getData(kl);
    data.initAll();
    
    data.setData(kl);
    tr.Fill();
    data.eventID++;
  }
  tr.Write();
  f.Close();
}
