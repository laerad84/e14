//
{
  TFile *tf = new TFile("../data/tutorial05.root");
  
  eventTree00->Draw("GenParticle.briefTracks.mass");
  gPad->SetLogy();
  gPad->Modified();
  gPad->Update();
  std::getchar();
  gPad->SetLogy(0);
  
  eventTree00->Draw("GenParticle.briefTracks.mass:Event.event_number","","box");
  gPad->Modified();
  gPad->Update();
  std::getchar();

  eventTree00->Draw("det.totalEnergy");
  gPad->Modified();
  gPad->Update();
  std::getchar();
  
  eventTree00->Draw("det.digi.energy:det.digi.modID","","box");
  gPad->Modified();
  gPad->Update();
  std::getchar();
  
  eventTree00->Draw("det.digi.energy","det.digi.modID==1");
  gPad->Modified();
  gPad->Update();
  std::getchar();

  GsimGenParticleData* data = new GsimGenParticleData();
  eventTree00->SetBranchAddress("GenParticle.",&data);
  eventTree00->GetEntry(798);
  data->dump();
}
