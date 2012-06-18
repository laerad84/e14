//
{
  TFile *tf = new TFile("../data/tutorial07.root");
  
  eventTree00->Draw("tube.totalEnergy");
  gPad->Modified();
  gPad->Update();
  std::getchar();

  eventTree00->Draw("det.totalEnergy:tube.totalEnergy");
  gPad->Modified();
  gPad->Update();
  std::getchar();

  eventTree00->Draw("tube.hits.pid");
  gPad->Modified();
  gPad->Update();
  std::getchar();

  eventTree00->Draw("tube.hits.pid","abs(tube.hits.pid)<100");
  gPad->Modified();
  gPad->Update();
  std::getchar();

  eventTree00->Draw("tube.hits.pid","abs(tube.hits.pid)>100");
  gPad->Modified();
  gPad->Update();
  std::getchar();

  eventTree00->Draw("tube.hits.ek","tube.hits.pid==22");
  gPad->SetLogy();
  gPad->Modified();
  gPad->Update();
  std::getchar();
  gPad->SetLogy(0);

  

  eventTree00->Draw("tube.hits.ek","abs(tube.hits.pid)>100");
  gPad->Modified();
  gPad->Update();
  std::getchar();
}
