#include "eventDisplay/CsiDisplay.h"
#include "TStyle.h"

CsiDisplay::CsiDisplay(std::string inputFile,std::string psFile)
  :m_nBox(CsiMap::getCsiMap()->getN()),isOpenPSfile(false)
{
  m_inputTree = new TChain("eventTree00");
  m_inputTree->Add(inputFile.c_str());
  m_psFile = psFile;
  
  m_box = new TBox[m_nBox];
  for(int i=0;i<m_nBox;i++){
    m_box[i].SetFillStyle(0);
  }
  m_canvas = new TCanvas("canvas","",700,700);
  m_histSmall = new TH2D("hs","",80,-1000,1000,80,-1000,1000);
  m_histLarge = new TH2D("hl","",40,-1000,1000,40,-1000,1000);
  m_histSmall->SetStats(0);
  m_histLarge->SetStats(0);

  gStyle->SetPalette(1);
}

CsiDisplay::~CsiDisplay(){
  delete [] m_box;
  delete m_canvas;
  delete m_inputTree;
  delete m_histSmall;
  delete m_histLarge;
}


void CsiDisplay::displayEvent(){
  m_currentEntry=0;

  static DigiReader reader(m_inputTree);

  int const nentry = m_inputTree->GetEntries();
  std::cout<<"there is "<<nentry<<" events in the input file"<<std::endl;

  while(1){
    int mode = checkInput();
    if(mode==-1) break;
    else if(mode==0) continue;
    
    int ndigi,id[3000];
    double E[3000],time[3000];    
    while(m_currentEntry<nentry){
      m_inputTree->GetEntry(m_currentEntry);
      reader.getCsiDigi(ndigi,id,E,time);
      if(mode!=2||ndigi!=0){
	break;
      }
      m_currentEntry++;
    }
    
    if(m_currentEntry>=nentry){
      std::cout<<"\n\n##########################################\n"<<std::endl;
      std::cout<<"  reach to the end of the file. \n\n"<<std::endl;
      break;
    }    
    
    draw(ndigi,id,E);
    m_currentEntry++;
  }
  if( isOpenPSfile ) m_canvas->Print((m_psFile+"]").c_str());
}



int CsiDisplay::checkInput(){
  static int ncalled = 0;

  std::string key;    
  if(ncalled%20==0){
    std::cout<<"\nq : quit, c : continue, p : print, log : change Z-axis to log scale"<<std::endl;
    std::cout<<"s : skip to the event with any hits, [integer] : display [integer]th event "<<std::endl;
  }
  ncalled++;

  std::cout<<"type key >> "<<std::flush;
  std::cin>>key;
  
  if(key=="q") return -1;

  if(key=="p"){
    if( !isOpenPSfile ){
      m_canvas->Print((m_psFile+"[").c_str());
      isOpenPSfile = true;
    }
    m_canvas->Print(m_psFile.c_str());
    return 0;
  }

  if(key=="log"){
    static int called_log=0;
    called_log++;
    m_canvas->SetLogz(called_log%2);
    m_canvas->Update();
    return 0;
  }
  
  if(key=="c")  return 1;

  if(key=="s")  return 2;

  if(key=="0"||(key!="0"&&atoi(key.c_str())!=0)){
    m_currentEntry = atoi(key.c_str());
    return 1;
  }

  if(key=="z"){
    double min,max;
    std::cout<<"change range of Zaxis. Input minimum value."<<std::endl;
    std::cout<<"(min) >>"<<std::flush;
    std::cin>>min;
    while(std::cin.fail()){
      std::cout<<"Bad Input! Input value"<<std::endl;
      std::cin.clear();
      std::cin.ignore();
      std::cout<<"(min) >>"<<std::flush;
      std::cin>>min;
    }
    std::cout<<"Input maximum value."<<std::endl;
    std::cout<<"(max) >>"<<std::flush;
    std::cin>>max;
    while(std::cin.fail()){
      std::cout<<"Bad Input! Input value"<<std::endl;
      std::cin.clear();
      std::cin.ignore();
      std::cout<<"(max) >>"<<std::flush;
      std::cin>>max;
    }

    if(min<max){
      m_histSmall->GetZaxis()->SetRangeUser(min,max);
      m_histLarge->GetZaxis()->SetRangeUser(min,max);
      m_canvas->SetLogx(0);
      m_canvas->Update();
      return 0;
    }
  }
  std::cout<<"invalid input."<<std::endl;
  return 0;
}

void CsiDisplay::draw(int ndigi,int *id,double *E){
  m_histSmall->Reset();
  m_histLarge->Reset();

  double maxE=1;
  for(int i=0;i<ndigi;i++){
    double x,y,w;
    CsiMap::getCsiMap()->getXYW(id[i],x,y,w);
    if(w<30)     m_histSmall->Fill(x,y,E[i]);
    else    m_histLarge->Fill(x,y,E[i]);

    if(maxE<E[i]) maxE=E[i];
  }
  
  m_histSmall->GetZaxis()->SetRangeUser(0,maxE*1.2);
  m_histLarge->GetZaxis()->SetRangeUser(0,maxE*1.2);
  m_histSmall->SetTitle(Form("%dth event",m_currentEntry));
  
  m_histSmall->Draw("colz");
  m_histLarge->Draw("colz same");

  for(int i=0;i<m_nBox;i++){
    double x,y,w;
    CsiMap::getCsiMap()->getXYW(i,x,y,w);
    x = (x>0) ? (int(x/w)+0.5)*w : (int(x/w)-0.5)*w;
    y = (y>0) ? (int(y/w)+0.5)*w : (int(y/w)-0.5)*w;
    m_box[i].DrawBox(x-w/2,y-w/2,x+w/2,y+w/2);
  }
  m_canvas->Update();
}
