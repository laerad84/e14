#include "gnana/E14GNAnaDataContainer.h"



E14GNAnaDataContainer::E14GNAnaDataContainer()
{
  initAll();
}


E14GNAnaDataContainer::~E14GNAnaDataContainer(){
  ;
}


void E14GNAnaDataContainer::branchOfGlobal(TTree *tree){
  if(tree->GetBranch("eventID")!=0){
    return;
  }
  // global
  tree->Branch("eventID",&eventID,"eventID/I");
  tree->Branch("OrigEventID",&OrigEventID,"OrigEventID/I");
  tree->Branch("CutCondition",&CutCondition,"CutCondition/I");
  tree->Branch("VetoCondition",&VetoCondition,"VetoCondition/I");
}

void E14GNAnaDataContainer::branchOfDigi(TTree *tree){
  if(tree->GetBranch("CsiNumber")!=0){
    GsimMessage::getInstance()
      ->report("warning","branchOfDigi() was called twice. Ignored.");
    return;
  }
  branchOfGlobal(tree);
  //GsimDigiData
  tree->Branch("VetoNumber",&VetoNumber,"VetoNumber/I");
  tree->Branch("VetoDetID",VetoDetID,"VetoDetID[VetoNumber]/I");
  tree->Branch("VetoModID",VetoModID,"VetoModID[VetoNumber]/I");
  tree->Branch("VetoEne",VetoEne,"VetoEne[VetoNumber]/D");
  tree->Branch("VetoTime",VetoTime,"VetoTime[VetoNumber]/D");
  
  tree->Branch("CsiNumber",&CsiNumber,"CsiNumber/I");
  tree->Branch("CsiModID",CsiModID,"CsiModID[CsiNumber]/I");
  tree->Branch("CsiEne",CsiEne,"CsiEne[CsiNumber]/D");
  tree->Branch("CsiTime",CsiTime,"CsiTime[CsiNumber]/D");
}


void E14GNAnaDataContainer::branchOfClusterList(TTree *tree){
  if(tree->GetBranch("ClusterNumber")!=0){
    GsimMessage::getInstance()
      ->report("warning","branchOfClusterList() was called twice. Ignored.");
    return;
  }
  branchOfGlobal(tree);
  // Cluster
  tree->Branch("ClusterNumber",&ClusterNumber,"ClusterNumber/I");
  tree->Branch("ClusterId",ClusterId,"ClusterId[ClusterNumber]/I");
  tree->Branch("ClusterStatus",ClusterStatus,"ClusterStatus[ClusterNumber]/I");
  tree->Branch("ClusterThreshold",ClusterThreshold,"ClusterThreshold[ClusterNumber]/D");
  tree->Branch("ClusterDepE",ClusterDepE,"ClusterDepE[ClusterNumber]/D");
  tree->Branch("ClusterCoePos",ClusterCoePos,"ClusterCoePos[ClusterNumber][3]/D");
  tree->Branch("ClusterTime",ClusterTime,"ClusterTime[ClusterNumber]/D");
  tree->Branch("ClusterRMS",ClusterRMS,"ClusterRMS[ClusterNumber]/D");
  tree->Branch("ClusterSize",ClusterSize,"ClusterSize[ClusterNumber]/I");
  tree->Branch("ClusterCsiId",ClusterCsiId,Form("ClusterCsiId[ClusterNumber][%d]/I",s_arrSize));
  tree->Branch("ClusterCsiE",ClusterCsiE,Form("ClusterCsiE[ClusterNumber][%d]/D",s_arrSize));
  tree->Branch("ClusterCsiTime",ClusterCsiTime,Form("ClusterCsiTime[ClusterNumber][%d]/D",s_arrSize));
}

void E14GNAnaDataContainer::branchOfGammaList(TTree *tree){
  branchOfClass(tree,1);
}
void E14GNAnaDataContainer::branchOfPi0List(TTree *tree){
  branchOfClass(tree,2);
}
void E14GNAnaDataContainer::branchOfKlong(TTree *tree,int nFillKlong){
  GsimMessage::getInstance()
    ->report("warning","***** E14GsimGNAnaDataContainer ******");
  GsimMessage::getInstance()
    ->report("warning","setData(std::vector<Klong>) : Only 2 leading Klongs are recorded by default. If you want to change # of KL recorded, call setNKlong(int #ofKL ) (if setting #ofKL<=0, all in the vector<Klong> are recorded). ");
  GsimMessage::getInstance()
    ->report("warning","***************************************");
  
  m_nFillKlong = nFillKlong;
  branchOfClass(tree,4);
}

void E14GNAnaDataContainer::branchOfClass(TTree *tree,int mode){
  if(m_mode!=0){
    std::string name[3] 
      = {"branchOfGammaList","branchOfPi0List","branchOfKlong"};
    int ID;
    if(mode==1) ID = 0;
    else if(mode==2) ID = 1;
    else ID = 2;
    std::string message;
    message = Form("E14GsimGNAnaDataContainer::%s was called after once calling %s,%s or %s. These functions interfere each other, and you could NOT get the correct result.",name[ID].c_str(),name[0].c_str(),name[1].c_str(),name[2].c_str());
    if(tree->GetBranch("GamClusNumber")==0){
      GsimMessage::getInstance()
	->report("warning","***** E14GsimGNAnaDataContainer ******");
      GsimMessage::getInstance()->report("warning",message.c_str());
      GsimMessage::getInstance()
	->report("warning","*************************************");
    }else{
      GsimMessage::getInstance()
	->report("error","***** E14GsimGNAnaDataContainer ******");
      GsimMessage::getInstance()->report("error",message.c_str());
      GsimMessage::getInstance()
	->report("error","*************************************");
      exit(1);
    }
  }
  
  m_mode = ( m_mode | mode );

  branchOfGlobal(tree);
    // Gamma,Pi0,Klong
    
  tree->Branch("GamClusNumber",&GamClusNumber,"GamClusNumber/I");
  tree->Branch("GamClusId",GamClusId,"GamClusId[GamClusNumber]/I");
  tree->Branch("GamClusStatus",GamClusStatus,"GamClusStatus[GamClusNumber]/I");
  tree->Branch("GamClusThreshold",GamClusThreshold,"GamClusThreshold[GamClusNumber]/D");
  tree->Branch("GamClusDepE",GamClusDepE,"GamClusDepE[GamClusNumber]/D");
  tree->Branch("GamClusCoePos",GamClusCoePos,"GamClusCoePos[GamClusNumber][3]/D");
  tree->Branch("GamClusTime",GamClusTime,"GamClusTime[GamClusNumber]/D");
  tree->Branch("GamClusRMS",GamClusRMS,"GamClusRMS[GamClusNumber]/D");
  tree->Branch("GamClusSize",GamClusSize,"GamClusSize[GamClusNumber]/I");
  tree->Branch("GamClusCsiId",GamClusCsiId,Form("GamClusCsiId[GamClusNumber][%d]/I",s_arrSize));
  tree->Branch("GamClusCsiE",GamClusCsiE,Form("GamClusCsiE[GamClusNumber][%d]/D",s_arrSize));
  tree->Branch("GamClusCsiTime",GamClusCsiTime,Form("GamClusCsiTime[GamClusNumber][%d]/D",s_arrSize));

  tree->Branch("GammaNumber",&GammaNumber,"GammaNumber/I");  
  tree->Branch("GammaId",GammaId,"GammaId[GammaNumber]/I");  
  tree->Branch("GammaStatus",GammaStatus,"GammaStatus[GammaNumber]/I");  
  tree->Branch("GammaE",GammaE,"GammaE[GammaNumber]/D");  
  tree->Branch("GammaPos",GammaPos,"GammaPos[GammaNumber][3]/D");  
  tree->Branch("GammaTime",GammaTime,"GammaTime[GammaNumber]/D");  
  tree->Branch("GammaMom",GammaMom,"GammaMom[GammaNumber][3]/D");  
  tree->Branch("GammaSigmaE",GammaSigmaE,"GammaSigmaE[GammaNumber]/D");  
  tree->Branch("GammaSigmaPos",GammaSigmaPos,"GammaSigmaPos[GammaNumber][3]/D");  
  tree->Branch("GammaChi2",GammaChi2,"GammaChi2[GammaNumber]/D");  
  tree->Branch("GammaAnn",GammaAnn,"GammaAnn[GammaNumber]/D");  
  tree->Branch("Gamma_clusIndex",Gamma_clusIndex,"Gamma_clusIndex[GammaNumber]/I");  
  if(m_mode>=2){
    tree->Branch("Pi0Number",&Pi0Number,"Pi0Number/I");
    tree->Branch("Pi0Id",Pi0Id,"Pi0Id[Pi0Number]/I");
    tree->Branch("Pi0Status",Pi0Status,"Pi0Status[Pi0Number]/I");
    tree->Branch("Pi0E",Pi0E,"Pi0E[Pi0Number]/D");
    tree->Branch("Pi0Pos",Pi0Pos,"Pi0Pos[Pi0Number][3]/D"); 
    tree->Branch("Pi0Mom",Pi0Mom,"Pi0Mom[Pi0Number][3]/D");  
    tree->Branch("Pi0Pt",Pi0Pt,"Pi0Pt[Pi0Number]/D");
    tree->Branch("Pi0Mass",Pi0Mass,"Pi0Mass[Pi0Number]/D");
    tree->Branch("Pi0RecZ",Pi0RecZ,"Pi0RecZ[Pi0Number]/D");
    tree->Branch("Pi0RecZsig2",Pi0RecZsig2,"Pi0RecZsig2[Pi0Number]/D");
    tree->Branch("Pi0_gamIndex",Pi0_gamIndex,"Pi0_gamIndex[Pi0Number][2]/I");  
  }
  if(m_mode>=4){
    tree->Branch("KlongNumber",&KlongNumber,"KlongNumber/I");
    tree->Branch("KlongId",KlongId,"KlongId[KlongNumber]/I");
    tree->Branch("KlongStatus",KlongStatus,"KlongStatus[KlongNumber]/I");
    tree->Branch("KlongE",KlongE,"KlongE[KlongNumber]/D");
    tree->Branch("KlongPos",KlongPos,"KlongPos[KlongNumber][3]/D");
    tree->Branch("KlongMom",KlongMom,"KlongMom[KlongNumber][3]/D"); 
    tree->Branch("KlongPt",KlongPt,"KlongPt[KlongNumber]/D");
    tree->Branch("KlongMass",KlongMass,"KlongMass[KlongNumber]/D");
    tree->Branch("KlongDeltaZ",KlongDeltaZ,"KlongDeltaZ[KlongNumber]/D");
    tree->Branch("KlongChisqZ",KlongChisqZ,"KlongChisqZ[KlongNumber]/D");
    tree->Branch("KlongVertFlag",KlongVertFlag,"KlongVertFlag[KlongNumber]/I");
    tree->Branch("KlongSortFlag",KlongSortFlag,"KlongSortFlag[KlongNumber]/I");
    tree->Branch("Klong_piIndex",Klong_piIndex,"Klong_piIndex[KlongNumber][3]/I");  
  }
}


void E14GNAnaDataContainer::setBranchAddress(TTree *tree){
  tree->SetBranchAddress("eventID",&OrigEventID);
  tree->SetBranchAddress("CutCondition",&CutCondition);
  tree->SetBranchAddress("VetoCondition",&VetoCondition);
  if(tree->GetBranch("ClusterNumber")!=0){
    tree->SetBranchAddress("ClusterNumber",&ClusterNumber);
    tree->SetBranchAddress("ClusterId",ClusterId);
    tree->SetBranchAddress("ClusterStatus",ClusterStatus);
    tree->SetBranchAddress("ClusterThreshold",ClusterThreshold);
    tree->SetBranchAddress("ClusterDepE",ClusterDepE);
    tree->SetBranchAddress("ClusterCoePos",ClusterCoePos);
    tree->SetBranchAddress("ClusterTime",ClusterTime);
    tree->SetBranchAddress("ClusterRMS",ClusterRMS);
    tree->SetBranchAddress("ClusterSize",ClusterSize);
    tree->SetBranchAddress("ClusterCsiId",ClusterCsiId);
    tree->SetBranchAddress("ClusterCsiE",ClusterCsiE);
    tree->SetBranchAddress("ClusterCsiTime",ClusterCsiTime);
  }
  if(tree->GetBranch("GamClusNumber")!=0){
    tree->SetBranchAddress("GamClusNumber",&GamClusNumber);
    tree->SetBranchAddress("GamClusId",GamClusId);
    tree->SetBranchAddress("GamClusStatus",GamClusStatus);
    tree->SetBranchAddress("GamClusThreshold",GamClusThreshold);
    tree->SetBranchAddress("GamClusDepE",GamClusDepE);
    tree->SetBranchAddress("GamClusCoePos",GamClusCoePos);
    tree->SetBranchAddress("GamClusTime",GamClusTime);
    tree->SetBranchAddress("GamClusRMS",GamClusRMS);
    tree->SetBranchAddress("GamClusSize",GamClusSize);
    tree->SetBranchAddress("GamClusCsiId",GamClusCsiId);
    tree->SetBranchAddress("GamClusCsiE",GamClusCsiE);
    tree->SetBranchAddress("GamClusCsiTime",GamClusCsiTime);
  }
  if(tree->GetBranch("GammaNumber")!=0){
    tree->SetBranchAddress("GammaNumber",&GammaNumber);
    tree->SetBranchAddress("GammaId",GammaId);
    tree->SetBranchAddress("GammaStatus",GammaStatus);
    tree->SetBranchAddress("GammaE",GammaE);
    tree->SetBranchAddress("GammaPos",GammaPos);
    tree->SetBranchAddress("GammaTime",GammaTime);
    tree->SetBranchAddress("GammaMom",GammaMom);
    tree->SetBranchAddress("GammaSigmaE",GammaSigmaE);
    tree->SetBranchAddress("GammaSigmaPos",GammaSigmaPos);
    tree->SetBranchAddress("GammaChi2",GammaChi2);
    tree->SetBranchAddress("GammaAnn",GammaAnn);
    tree->SetBranchAddress("Gamma_clusIndex",Gamma_clusIndex);
  }
  if(tree->GetBranch("Pi0Number")!=0){
    tree->SetBranchAddress("Pi0Number",&Pi0Number);
    tree->SetBranchAddress("Pi0Id",Pi0Id);
    tree->SetBranchAddress("Pi0Status",Pi0Status);
    tree->SetBranchAddress("Pi0E",Pi0E);
    tree->SetBranchAddress("Pi0Pos",Pi0Pos);
    tree->SetBranchAddress("Pi0Mom",Pi0Mom);
    tree->SetBranchAddress("Pi0Pt",Pi0Pt);
    tree->SetBranchAddress("Pi0Mass",Pi0Mass);
    tree->SetBranchAddress("Pi0RecZ",Pi0RecZ);
    tree->SetBranchAddress("Pi0RecZsig2",Pi0RecZsig2);
    tree->SetBranchAddress("Pi0_gamIndex",Pi0_gamIndex);
  }
  if(tree->GetBranch("KlongNumber")!=0){
    tree->SetBranchAddress("KlongNumber",&KlongNumber);
    tree->SetBranchAddress("KlongId",KlongId);
    tree->SetBranchAddress("KlongStatus",KlongStatus);
    tree->SetBranchAddress("KlongE",KlongE);
    tree->SetBranchAddress("KlongPos",KlongPos);
    tree->SetBranchAddress("KlongMom",KlongMom);
    tree->SetBranchAddress("KlongPt",KlongPt);
    tree->SetBranchAddress("KlongMass",KlongMass);
    tree->SetBranchAddress("KlongDeltaZ",KlongDeltaZ);
    tree->SetBranchAddress("KlongChisqZ",KlongChisqZ);
    tree->SetBranchAddress("KlongSortFlag",KlongSortFlag);
    tree->SetBranchAddress("KlongVertFlag",KlongVertFlag);
    tree->SetBranchAddress("Klong_piIndex",Klong_piIndex);
  }
  if(tree->GetBranch("CsiNumber")!=0){
    tree->SetBranchAddress("CsiNumber",&CsiNumber);
    tree->SetBranchAddress("CsiModID",CsiModID);
    tree->SetBranchAddress("CsiEne",CsiEne);
    tree->SetBranchAddress("CsiTime",CsiTime);
  }
  if(tree->GetBranch("VetoNumber")!=0){
    tree->SetBranchAddress("VetoNumber",&VetoNumber);
    tree->SetBranchAddress("VetoDetID",VetoDetID);
    tree->SetBranchAddress("VetoModID",VetoModID);
    tree->SetBranchAddress("VetoEne",VetoEne);
    tree->SetBranchAddress("VetoTime",VetoTime);
  }
}


void E14GNAnaDataContainer::reset(){
  OrigEventID = CutCondition = VetoCondition = 0;
  resetClassNumber();
  resetClusterNumber();
  resetDigiNumber();
}

bool E14GNAnaDataContainer::getData(std::list<Cluster> &clist) const{
  clist.clear();
  for(int iclus = 0; iclus < ClusterNumber; iclus++ ){
    Cluster clus;
    if(!getCluster(clus,iclus))return false;
    clist.push_back(clus);
  }
  return true;
}


bool E14GNAnaDataContainer::getData(std::list<Gamma> &glist) const{
  glist.clear();
  for(int igam = 0; igam < GammaNumber; igam++ ){
    Gamma gam;    
    if(!getGamma(gam,igam)) return false;
    glist.push_back(gam);
  }
  return true;
}


bool E14GNAnaDataContainer::getData(std::list<Pi0>& pilist) const{
  pilist.clear();
  if( 2*Pi0Number!=GammaNumber ){
    GsimMessage::getInstance()
      ->report("error",Form("Pi0Number is inconsistent with GammaNumber"));
    return false;
  }
  
  for(int ipi = 0; ipi < Pi0Number; ipi++ ){
    Pi0 pi;
    if(!getPi0(pi,ipi)) return false;
    pilist.push_back(pi);
  }
  
  return true;
}

bool E14GNAnaDataContainer::getData(std::vector<Klong> &klist) const{
  if( 2*KlongNumber != Pi0Number && 3*KlongNumber != Pi0Number ){
    GsimMessage::getInstance()
      ->report("error",Form("KlongNumber is inconsistent with Pi0Number"));
    return false;
  }

  klist.clear();
  
  for(int ikl = 0; ikl < KlongNumber; ikl++ ){
    Klong kl;
    if(!getData(kl,ikl)) return false;
    klist.push_back(kl);
  }

  return true;
}




bool E14GNAnaDataContainer::getData(Klong &kl,int ID) const{
  if(ID<0||ID>=KlongNumber){
    GsimMessage::getInstance()
      ->report("warning",Form("%d th Klong are not exist",ID));
    return false;
  }
  kl.setId(KlongId[ID]);
  kl.setStatus(KlongStatus[ID]);
  kl.setEnergy(KlongE[ID]);
  kl.setMass(KlongMass[ID]);
  kl.setVtx(KlongPos[ID][0],KlongPos[ID][1],KlongPos[ID][2]);
  kl.setP3(KlongMom[ID][0],KlongMom[ID][1],KlongMom[ID][2]);
  kl.setDeltaZ(KlongDeltaZ[ID]);
  kl.setChisqZ(KlongChisqZ[ID]);
  kl.setSortFlag(KlongSortFlag[ID]);
  kl.setVertexFlag(KlongVertFlag[ID]);
  
  std::vector<Pi0> &piVec = kl.pi0();
  piVec.clear();
  
  for(int i=0;i<3;i++){
    int piIndex = Klong_piIndex[ID][i];
    if(piIndex<0) continue;
    
    Pi0 pi;
    if(!getPi0(pi,piIndex)) return false;
    piVec.push_back(pi);
  }
  
  return true;
}


void  E14GNAnaDataContainer::setData( std::list<Cluster> const &clusList ){
  ClusterNumber = clusList.size();
  if( ClusterNumber > s_arrSize ){
    GsimMessage::getInstance()
      ->report("warning",Form("more than %d clusters are found",s_arrSize));
    ClusterNumber = s_arrSize;
  }
  int id=0;
  for( std::list<Cluster>::const_iterator i=clusList.begin();
       i!=clusList.end(); i++ ) {
    if(id==s_arrSize) break;
    setCluster(*i,id);
    id++;
  }
}


void  E14GNAnaDataContainer::setData( std::list<Gamma> const &gamList ){
  static bool warning = true;
  if(warning && (m_mode & 0x1) == 0 ){
    GsimMessage::getInstance()
      ->report("warning","E14GNAnaDataContainer::setData(std::list<Gamma>) was called but branchOfGammaList() was not called. This data will not be filled to TTree.");
    warning = false;
  }
  
  resetClassNumber();
  for( std::list<Gamma>::const_iterator i=gamList.begin();
       i!=gamList.end(); i++ ) {
    setGamma(*i);
  }
  setGamClus();
}


void  E14GNAnaDataContainer::setData( std::list<Pi0>const &pi0List ){
  static bool warning = true;
  if(warning && (m_mode & 0x2) == 0 ){
    GsimMessage::getInstance()
      ->report("warning","E14GNAnaDataContainer::setData(std::list<Pi0>) was called but branchOfPi0List() was not called. This data will not be filled to TTree.");
    warning = false;
  }


  resetClassNumber();
  
  for( std::list<Pi0>::const_iterator i=pi0List.begin();
       i!=pi0List.end(); i++ ) {
    setPi0(*i);
  }
  setGamClus();
}



void  E14GNAnaDataContainer::setData( std::vector<Klong>const &klVec ){
  static bool warning = true;
  if(warning && (m_mode & 0x4) == 0 ){
    GsimMessage::getInstance()
      ->report("warning","E14GNAnaDataContainer::setData(std::list<Klong>) was called but branchOfKlong() was not called. This data will not be filled to TTree.");
    warning = false;
  }

  resetClassNumber();
  int nloop =  klVec.size();
  if(m_nFillKlong > 0 && nloop > m_nFillKlong ) nloop = m_nFillKlong;
  for( int i=0;i<nloop; i++){
    setData(klVec.at(i),false);
  }
  setGamClus();
}


void  E14GNAnaDataContainer::setData( Klong const &kl ,bool standalone ){
  static bool warning = true;
  if(standalone){
    if(warning && (m_mode & 0x4) == 0 ){
      GsimMessage::getInstance()
	->report("warning","E14GNAnaDataContainer::setData(std::list<Klong>) was called but branchOfKlong() was not called. This data will not be filled to TTree.");
      warning = false;
    }
    resetClassNumber();
  }
  int id = KlongNumber;
  KlongId[id] = kl.id();
  KlongStatus[id] = kl.status();
  KlongMass[id]=kl.m();
  KlongE[id]=kl.e();
  KlongDeltaZ[id]=kl.deltaZ();
  KlongChisqZ[id]=kl.chisqZ();
  KlongPt[id]=kl.p3().perp();
  KlongVertFlag[id] = kl.vertexFlag();
  KlongSortFlag[id] = kl.sortFlag();
  for(int i=0;i<3;i++){
    KlongMom[id][i]=kl.p3()(i);
    KlongPos[id][i]=kl.v()(i);
  }
  for(int i=0;i<3;i++){
    Klong_piIndex[id][i] = -1;
  }
  for(int i=0;i<kl.pi0().size();i++){
    Klong_piIndex[id][i] = Pi0Number;
    setPi0(kl.pi0()[i]);
  }
  KlongNumber++;

  if(standalone)  setGamClus();
}


void  E14GNAnaDataContainer::setData( DigiReader const &digiReader ){
  resetDigiNumber();
  int nhit = 0,id[s_digiArrSize];
  double ene[s_digiArrSize],time[s_digiArrSize];
  for(int idet = 0; idet<DigiReader::s_maxDet; idet++){
    if(idet==digiReader.CSI){
      if(digiReader.getCsiDigiSize() > s_digiArrSize){
	GsimMessage::getInstance()
	  ->report("warning","E14GNAnaDataContainer::setData(Digireader const &) : too many hits on Csi");
	return;
      }
      digiReader.getCsiDigi(CsiNumber,CsiModID,CsiEne,CsiTime);
      continue;
    }

    if(digiReader.getDigiSize(idet)+VetoNumber > s_digiArrSize){
      GsimMessage::getInstance()
	->report("warning","E14GNAnaDataContainer::setData(Digireader const &) : too many hits on Veto");
      return;
    }
    digiReader.getDigi(idet,nhit,id,ene,time);
    for(int i=0;i<nhit;i++){
      VetoDetID[VetoNumber] = idet;
      VetoModID[VetoNumber] = id[i];
      VetoEne[VetoNumber] = ene[i];
      VetoTime[VetoNumber] = time[i];
      VetoNumber++;
    }
  }

}



bool  E14GNAnaDataContainer::getCluster(Cluster &clus,int iclus) const{ 
  if(iclus<0||iclus>=ClusterNumber){
    GsimMessage::getInstance()
      ->report("warning",Form("%d th Cluster are not exist",iclus));
    return false;
  }
  
  clus.setId(ClusterId[iclus]);
  clus.setStatus(ClusterStatus[iclus]);
  clus.setThreshold(ClusterThreshold[iclus]);
  clus.setEnergy(ClusterDepE[iclus]);
  clus.setTime(ClusterTime[iclus]);
  clus.setPos(ClusterCoePos[iclus][0],ClusterCoePos[iclus][1],
	      ClusterCoePos[iclus][2]);
  clus.setRms(ClusterRMS[iclus]);
  
  //std::list<int> idList;
  std::vector<int> idVec;
  std::vector<double> eVec;
  std::vector<double> timeVec;
  for(int icsi=0; icsi < ClusterSize[iclus]; icsi++ ){
    //    idList.push_back(ClusterCsiId[iclus][icsi]);
    eVec.push_back(ClusterCsiE[iclus][icsi]);
    idVec.push_back(ClusterCsiId[iclus][icsi]);
    timeVec.push_back(ClusterCsiTime[iclus][icsi]);
  }
  //  clus.setClusterIdList(idList);
  clus.setClusterEVec(eVec);
  clus.setClusterTimeVec(timeVec);
  clus.setClusterIdVec(idVec);
  return true;
}


bool  E14GNAnaDataContainer::getGamClus(Cluster &clus,int iclus) const{ 
  if(iclus<0||iclus>=GamClusNumber){
    GsimMessage::getInstance()
      ->report("warning",Form("%d th GamClus are not exist",iclus));
    return false;
  }
  
  clus.setId(GamClusId[iclus]);
  clus.setStatus(GamClusStatus[iclus]);
  clus.setThreshold(GamClusThreshold[iclus]);
  clus.setEnergy(GamClusDepE[iclus]);
  clus.setTime(GamClusTime[iclus]);
  clus.setPos(GamClusCoePos[iclus][0],GamClusCoePos[iclus][1],
	      GamClusCoePos[iclus][2]);
  clus.setRms(GamClusRMS[iclus]);
  
  //std::list<int> idList;
  std::vector<int> idVec;
  std::vector<double> eVec;
  std::vector<double> timeVec;
  for(int icsi=0; icsi < GamClusSize[iclus]; icsi++ ){
    //    idList.push_back(GamClusCsiId[iclus][icsi]);
    eVec.push_back(GamClusCsiE[iclus][icsi]);
    idVec.push_back(GamClusCsiId[iclus][icsi]);
    timeVec.push_back(GamClusCsiTime[iclus][icsi]);
  }
  //  clus.setGamClusIdList(idList);
  clus.setClusterEVec(eVec);
  clus.setClusterTimeVec(timeVec);
  clus.setClusterIdVec(idVec);
  return true;
}



bool  E14GNAnaDataContainer::getGamma(Gamma &gam,int igam) const{ 
  if(igam<0||igam>=GammaNumber){
    GsimMessage::getInstance()
      ->report("warning",Form("%d th Gamma are not exist",igam));
    return false;
  }
  gam.setId(GammaId[igam]);
  gam.setStatus(GammaStatus[igam]);
  gam.setEnergy(GammaE[igam]);
  gam.setTime(GammaTime[igam]);
  gam.setPos(GammaPos[igam][0],GammaPos[igam][1],
	     GammaPos[igam][2]);
  gam.setP3(GammaMom[igam][0],GammaMom[igam][1],
	     GammaMom[igam][2]);
  gam.setSigmaE(GammaSigmaE[igam]);
  gam.setSigmaPos(GammaSigmaPos[igam][0],GammaSigmaPos[igam][1],
		  GammaSigmaPos[igam][2]);
  gam.setChisq(GammaChi2[igam]);
  gam.setAnn(GammaAnn[igam]);

  int cindex = Gamma_clusIndex[igam];
  if(cindex<0) return true;
  Cluster clus;
  if(!getGamClus(clus,cindex)) return false;
  gam.setCluster(clus);
  return true;
}




bool E14GNAnaDataContainer::getPi0(Pi0& pi0, int ipi) const{
  if(ipi<0||ipi>=Pi0Number){
    GsimMessage::getInstance()
      ->report("warning",Form("%d th Pi0 are not exist",ipi));
    return false;
  }
  pi0.setId(Pi0Id[ipi]);
  pi0.setStatus(Pi0Status[ipi]);
  pi0.setEnergy(Pi0E[ipi]);
  pi0.setMass(Pi0Mass[ipi]);
  pi0.setVtx(Pi0Pos[ipi][0],Pi0Pos[ipi][1],Pi0Pos[ipi][2]);
  pi0.setP3(Pi0Mom[ipi][0],Pi0Mom[ipi][1],Pi0Mom[ipi][2]);
  pi0.setRecZ(Pi0RecZ[ipi]);
  pi0.setRecZsig2(Pi0RecZsig2[ipi]);

  Gamma gamma1,gamma2;
  if( !getGamma(gamma1,Pi0_gamIndex[ipi][0])
      ||  !getGamma(gamma2,Pi0_gamIndex[ipi][1]))
    return false;

  pi0.setGamma(gamma1,gamma2);
  return true;
}




void  E14GNAnaDataContainer::setCluster( const Cluster& clus, int cnum ){
  if(ClusterNumber<=cnum){
    std::cout<<"error: E14GNAnaDataContainer::setCluster()"<<std::endl;
    exit(1);
  }
  ClusterId[cnum] = clus.id(); 
  ClusterStatus[cnum] = clus.status(); 
  ClusterThreshold[cnum] = clus.threshold(); 
  ClusterDepE[cnum] = clus.e(); 
  ClusterTime[cnum] = clus.t();
  for(int i=0;i<3;i++){
    ClusterCoePos[cnum][i] = clus.pos()(i);
  }
  ClusterRMS[cnum] = clus.rms();
  ClusterSize[cnum] = clus.clusterIdVec().size();
  if(ClusterSize[cnum] > s_arrSize){
    GsimMessage::getInstance()
      ->report("warning",Form("more than %d crystals in the cluster.",s_arrSize));
    ClusterSize[cnum] = s_arrSize;
  }
  
  for(int i=0;i<ClusterSize[cnum];i++){
    ClusterCsiId[cnum][i] = clus.clusterIdVec()[i];
    ClusterCsiE[cnum][i] = clus.clusterEVec()[i];
    ClusterCsiTime[cnum][i] = clus.clusterTimeVec()[i];
  }
  for(int i=ClusterSize[cnum];i<s_arrSize;i++){
    ClusterCsiId[cnum][i] = 0;
    ClusterCsiE[cnum][i] = 0;
    ClusterCsiTime[cnum][i] = 0;
  }
}


void  E14GNAnaDataContainer::setGamClus(){
  GamClusNumber = m_clusMemo.size();
  if( GamClusNumber > s_arrSize ){
    GsimMessage::getInstance()
      ->report("warning",Form("more than %d clusters are found",s_arrSize));
    GamClusNumber = s_arrSize;
  }
  int id=0;
  for( std::list<Cluster>::const_iterator it=m_clusMemo.begin();
       it!=m_clusMemo.end(); it++ ) {
    if(id==s_arrSize) break;

    GamClusId[id] = it->id(); 
    GamClusStatus[id] = it->status(); 
    GamClusThreshold[id] = it->threshold(); 
    GamClusDepE[id] = it->e(); 
    GamClusTime[id] = it->t();
    for(int i=0;i<3;i++){
      GamClusCoePos[id][i] = it->pos()(i);
    }
    GamClusRMS[id] = it->rms();
    GamClusSize[id] = it->clusterIdVec().size();
    if(GamClusSize[id]>s_arrSize){
      GsimMessage::getInstance()->report("warning",Form("more than %d crystals in the GammaCluster.",s_arrSize));
      GamClusSize[id] = s_arrSize;
    }
    for(int i=0;i<s_arrSize;i++){
      if(i<GamClusSize[id]){
	GamClusCsiId[id][i] = it->clusterIdVec()[i];
	GamClusCsiE[id][i] = it->clusterEVec()[i];
	GamClusCsiTime[id][i] = it->clusterTimeVec()[i];
      }else{
     	GamClusCsiId[id][i] = 0;
	GamClusCsiE[id][i] = 0;
	GamClusCsiTime[id][i] = 0;
      }
    }
    id++;
  }
}

void  E14GNAnaDataContainer::setGamma( const Gamma& gam ){
  int id = GammaNumber;
  if(id>=s_arrSize){
    GsimMessage::getInstance()
      ->report("warning","too many Gamma-cluster");
    return;
  }
  GammaId[id] = gam.id(); 
  GammaStatus[id] = gam.status(); 
  GammaE[id] = gam.e(); 
  GammaTime[id] = gam.t();
  GammaSigmaE[id] = gam.sigmaE();

  for(int i=0;i<3;i++){
    GammaPos[id][i] = gam.pos()(i);
    GammaSigmaPos[id][i] = gam.sigmaPos()(i);
    GammaMom[id][i] = gam.p3()(i);
  }
  GammaChi2[id] = gam.chisq();
  GammaAnn[id] = gam.ann();

  bool find=false;
  int index = -1;
  for(std::list<Cluster>::const_iterator it = m_clusMemo.begin();
      it != m_clusMemo.end(); it++){
    index++;
    if(it->e()!=gam.edep()) continue;
    if(it->pos()!=gam.coepos()) continue;
    if(it->t()!=gam.cluster().t()) continue;
    if(it->id()!=gam.cluster().id()) continue;
    find = true;
    break;
  }
  if(find) Gamma_clusIndex[id] = index;
  else{
    m_clusMemo.push_back(gam.cluster());
    Gamma_clusIndex[id] = index + 1;
  }

  GammaNumber++;
}


void  E14GNAnaDataContainer::setPi0( const Pi0& pi ){
  int id = Pi0Number;
  Pi0Id[id] = pi.id();
  Pi0Status[id] = pi.status();
  Pi0Mass[id]=pi.m();
  Pi0E[id]=pi.e();
  Pi0RecZ[id]=pi.recZ();
  Pi0RecZsig2[id]=pi.recZsig2();
  Pi0Pt[id]=pi.p3().perp();
  for(int i=0;i<3;i++){
    Pi0Mom[id][i]=pi.p3()(i);
    Pi0Pos[id][i]=pi.v()(i);
  }
  Pi0_gamIndex[id][0] = GammaNumber;
  setGamma(pi.g1());
  Pi0_gamIndex[id][1] = GammaNumber;
  setGamma(pi.g2());
  Pi0Number++;
}


void  E14GNAnaDataContainer::initAll(){
  m_nFillKlong = 2;
  m_mode=0;
  m_clusMemo.clear();
  
  eventID =  OrigEventID = 0;
  CutCondition =  VetoCondition = 0;
  KlongNumber = Pi0Number = GammaNumber = ClusterNumber = 0;
  VetoNumber = CsiNumber = 0;
  
    
  for(int i=0;i<s_arrSize;i++){
    KlongStatus[i] = Pi0Status[i] = GammaStatus[i] = ClusterStatus[i] = 0;
    KlongId[i] = KlongSortFlag[i] = KlongVertFlag[i] = 0;
    KlongPt[i] = KlongMass[i] = KlongE[i] = KlongDeltaZ[i] = KlongChisqZ[i] =0;
    Pi0Id[i] = 0;
    Pi0Pt[i] = Pi0Mass[i] = Pi0E[i] =  Pi0RecZ[i] = Pi0RecZsig2[i] = 0;  
    GammaId[i] = 0;
    GammaE[i] = GammaTime[i] = GammaSigmaE[i] = GammaChi2[i] = GammaAnn[i] = 0;
    ClusterId[i] = ClusterSize[i] = 0;
    ClusterDepE[i] = ClusterTime[i] = ClusterRMS[i] = 0;
    ClusterThreshold[i] = 0;

    for(int j=0;j<3;j++){
      KlongMom[i][j] = KlongPos[i][j] = 0;  
      Pi0Mom[i][j] = Pi0Pos[i][j] = 0;  
      GammaMom[i][j] = GammaPos[i][j] = GammaSigmaPos[i][j] = 0;  
      ClusterCoePos[i][j] = 0;
    }
    
    for(int j=0;j<3;j++){
      Klong_piIndex[i][j] = -1;
    }
    for(int j=0;j<2;j++){
      Pi0_gamIndex[i][j] = -1;
    }
    Gamma_clusIndex[i] = -1;
    
    for(int j=0;j<s_arrSize;j++){
      ClusterCsiId[i][j] = 0;
      ClusterCsiE[i][j] = 0;
      ClusterCsiTime[i][j] = 0;
    }
  }
  for(int i=0;i<s_digiArrSize;i++){
    CsiEne[i] = CsiTime[i] = 0;  
    CsiModID[i] = 0;
    VetoEne[i] = VetoTime[i] = 0;  
    VetoDetID[i] = VetoModID[i] = 0; 
  }
}

