#include "csimap/CsiMap.h"
#include "TChain.h"
#include "TEventList.h"
#include "GsimData/GsimDetectorData.h"

CsiMap* CsiMap::s_CsiMap = 0;

CsiMap::CsiMap(){
  readCsiConfig();

  if(s_CsiMap) {
    GsimMessage::getInstance()
      ->report("error","CsiMap constructor is called twice.");
    exit(1);
  }
  s_CsiMap  = this;
}

void CsiMap::readCsiConfig(std::string mapFile){
  m_nCsI = 0;
  if(mapFile.empty()){
    mapFile
      =std::getenv("E14_TOP_DIR")+std::string("/share/csimap/csi_dettree.root");
  }
  
  TChain dettr("detectorTree00");
  dettr.Add(mapFile.c_str());
  GsimMessage::getInstance()
    ->report("info",Form("read %s as CsiMap-data file.",mapFile.c_str()));

  GsimDetectorData* detector = new GsimDetectorData();
  dettr.SetBranchAddress("detector",&detector);
  
  std::string condition = "m_sensitiveDetectorName.fData==\"CSI\"";
  TEventList* elist = new TEventList("elistInCsiMap","elistInCsiMap");
  dettr.Draw(">>elistInCsiMap",condition.c_str());
  
  int nlist = elist->GetN();
  if(nlist==0){
    GsimMessage::getInstance()
      ->report("error",Form("Can't find CsiMap-data in %s.",mapFile.c_str()));
    exit(1);
  }
  for(int i=0;i<nlist;i++){
    dettr.GetEntry(elist->GetEntry(i));
    int num = detector->m_nClone+detector->m_copyNo+1;
    m_nCsI=(m_nCsI<num)?num:m_nCsI;
  }
  GsimMessage::getInstance()
    ->report("info",Form("CsiMap:: # of crystals == %d",m_nCsI));
  if(m_nCsI>s_arrSize){
    GsimMessage::getInstance()
      ->report("error","CsiMap:: too many crystals!");
    exit(1);
  }

  for(int i=0;i<s_arrSize;i++){
    m_Xarray[i] = 0;
    m_Yarray[i] = 0;
    m_Zarray[i] = 0;
    m_Warray[i] = -1;
  }
  
  for(int i=0;i<nlist;i++){
    dettr.GetEntry(elist->GetEntry(i));
    TVector3 origPos = detector->m_position;
    double origLength = detector->m_parameterArray[2];
    double origWidth = detector->m_parameterArray[0];
    int ID = detector->m_copyNo;
    
    m_Xarray[ID]=origPos.x();
    m_Yarray[ID]=origPos.y();
    m_Zarray[ID]=origPos.z()-origLength/2.;
    m_Warray[ID]=origWidth;
    
    int nClone = detector->m_nClone;
    int *copyNo = detector->m_clonedCopyNoArray;
    double *xposi = (detector->m_clonedPositionXArray) ;//mm
    double *yposi = (detector->m_clonedPositionYArray) ;
    double *zposi = (detector->m_clonedPositionZArray) ;
    for(int j=0;j<nClone;j++){
      int k = copyNo[j];
      if(k+1>m_nCsI){
	GsimMessage::getInstance()
	  ->report("error","CsiMap::readCsIConfig() something wrong");
	exit(1);
      }
      m_Xarray[k]=xposi[j];
      m_Yarray[k]=yposi[j];
      m_Zarray[k]=zposi[j]-origLength/2.;
      m_Warray[k]=origWidth;
    }
  }
    
  delete detector;
  delete elist;  
  dettr.ResetBranchAddresses();
}


CsiMap* CsiMap::getCsiMap() {
  if(!s_CsiMap) {
    s_CsiMap  = new CsiMap();
  }
  return s_CsiMap;
}

double CsiMap::getX(int const &ID) const{
  if(ID<0||ID>=m_nCsI){
    GsimMessage::getInstance()->report("warning",Form("CsiMap::getX(): a Crystal with ID==%d dosen't exsist.",ID));
    return 0;
  }
  return m_Xarray[ID];
}

double CsiMap::getY(int const &ID) const{
  if(ID<0||ID>=m_nCsI){
    GsimMessage::getInstance()->report("warning",Form("CsiMap::getY(): a Crystal with ID==%d dosen't exsist.",ID));
    return 0;
  }
  return m_Yarray[ID];
}

double CsiMap::getZSurface(int const &ID) const{
  if(ID<0||ID>=m_nCsI){
    GsimMessage::getInstance()->report("warning",Form("CsiMap::getZSurface(): a Crystal with ID==%d dosen't exsist.",ID));
    return 0;
  }
  return m_Zarray[ID];
}

double CsiMap::getW(int const &ID) const{
  if(ID<0||ID>=m_nCsI){
    GsimMessage::getInstance()->report("warning",Form("CsiMap::getW(): a Crystal with ID==%d dosen't exsist.",ID));
    return 0;
  }
  return m_Warray[ID];
}

void CsiMap::getXYW(int const &ID,double &x,double &y,double &w) const{
  if(ID<0||ID>=m_nCsI){
    GsimMessage::getInstance()->report("warning",Form("CsiMap::getXYW(): a Crystal with ID==%d dosen't exsist.",ID));
    x = y = w = 0;
    return;
  }
  x = m_Xarray[ID];
  y = m_Yarray[ID];
  w = m_Warray[ID];
}

void CsiMap::getXYWarray(int const &nDigi,int const *ID,double x[],double y[],double w[]) const{
  for(int i=0;i<nDigi;i++){
    getXYW(ID[i],x[i],y[i],w[i]);
  }
}


