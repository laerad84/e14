#include "gamma/ShapeANN.h"
#include "csimap/CsiMap.h"
//#include "CLHEP/Units/systemOfUnits.h"
#include "TMath.h"

#include "gamma/code50.h"
#include "gamma/code18.h"


ShapeANN::ShapeANN(){
  m_ANNRegion = 0;
  for(int i=0;i<27;i++) m_ANNPara[i] = 0;
}

bool ShapeANN::shapeANN(Gamma &g,int CsiNumber,int* CsiId,double *CsiEne){
  if(CsiNumber<0) readParameter(g);
  else if(CsiId!=0&&CsiEne!=0) readParameter(g,CsiNumber,CsiId,CsiEne);
  else {
    std::cout<<"shapeANN: argument error"<<std::endl;
    return false;
  }

  double ANNOutput = 0;
  if(m_ANNRegion==0){
    float finput[27];
    float foutput;
    float output2;
    for(int j=0; j<27; j++){
      finput[j] = float(m_ANNPara[j]);
    }
    snn(finput,foutput,output2);
    ANNOutput = foutput;
  } else {
    float finput[11];
    float foutput;
    float output2;
    for(int j=0; j<11; j++){
      finput[j] = float(m_ANNPara[j]);
    }
    snn2(finput,foutput,output2);
    ANNOutput = foutput;
  }
  g.setAnn(ANNOutput);
  
  return true;
}


int ShapeANN::readParameter(Gamma &g)
{

  double  KtevCsic_XY  = 5.0;
  double  KtevCsic_Len = 50.0;
  double  KtevCsic_Gap = 0.03;

  double  KtevCsicFine_XY  = 2.5;
  double  KtevCsicFine_Len = 50.0;
  double  KtevCsicFine_Gap = KtevCsic_Gap*2.5/5.;

  int nBlockFine=48;
  int nBeamHole=8;
  int nLayer=38;
  
  static int init=0;
  static std::map<int,int> XYtoIDmap;
  static std::map<int,int> IDtoXYmap;
  static int region[3600]; 

  if(init==0){ 
    initANN(XYtoIDmap,IDtoXYmap,region);
    init=1;
  }

  double length = (KtevCsicFine_XY+KtevCsicFine_Gap)*nBlockFine/2.+KtevCsicFine_Gap/2;
  
  
  double* annpara;
  double anntotE=0;
  double tempx,tempy;
  int regionflag,regionnumber;
  int xid,yid,startxid,startyid,endxid,endyid;    
    
  if( length*10>TMath::Max(fabs(g.x()),fabs(g.y()) ) ){
    tempx = (g.x()/10.-KtevCsicFine_Gap)/(KtevCsicFine_XY+KtevCsicFine_Gap);
    tempy = (g.y()/10.-KtevCsicFine_Gap)/(KtevCsicFine_XY+KtevCsicFine_Gap);
    if(tempx < 0 ) xid = nBlockFine/2 + int(tempx) - 1;
    else xid = nBlockFine/2 + int(tempx);
    if(tempy < 0 ) yid = nBlockFine/2 + int(tempy) - 1;
    else yid = nBlockFine/2 + int(tempy);
      
    std::map<int,int>::iterator p;
    p = XYtoIDmap.find(yid*nBlockFine+xid);        
    if(p != XYtoIDmap.end()) regionflag= region[p->second];
    else  regionflag= 0;
    
  } else {
    tempx = (g.x()/10.-KtevCsic_Gap)/(KtevCsic_XY+KtevCsic_Gap);
    tempy = (g.y()/10.-KtevCsic_Gap)/(KtevCsic_XY+KtevCsic_Gap);
    if(tempx < 0 ) xid = nLayer/2 + int(tempx) - 1;
    else xid = nLayer/2 + int(tempx);
    if(tempy < 0 ) yid = nLayer/2 + int(tempy) - 1;
    else yid = nLayer/2 + int(tempy);
    regionflag=2;
  }
    

    
    
    if(regionflag==0){       // inner region
      startxid = xid-2;
      startyid = yid-2;
      endxid = xid+2;
      endyid = yid+2;
      regionnumber=5;
      annpara = new double[27];
      for(int i=0; i<27; i++) annpara[i]=0;
    } else {             // for middle or outer region
      if(regionflag==1){ // for middle region

	xid = xid/2 + 7;
	yid = yid/2 + 7;
      }
      startxid= xid-1;  
      startyid= yid-1;
      endxid= xid+1;
      endyid= yid+1;
      regionnumber=3;
      annpara = new double[11];
      for(int i=0; i<11; i++) annpara[i]=0;
    }

    //    int nHitCSI=ana_g2.GetCsIDigiSize();
    int nHitCSI=g.clusterIdVec().size();
    for(int j=0; j<nHitCSI; j++){
      std::map<int,int>::iterator stackmap;
      int stackXID,stackYID,stackID;
      int csiId = g.clusterIdVec().at(j);
      double csiE = g.clusterEVec().at(j);
      stackmap = IDtoXYmap.find(csiId);
      if( stackmap != IDtoXYmap.end()) stackID= stackmap->second;
      else {
	std::cout<<"CsI IDtoXYmap mapping error"<<std::endl;
	std::cout<<"ID:"<<csiId<<" x:"<<CsiMap::getCsiMap()->getX(csiId)<<" y:"<<CsiMap::getCsiMap()->getY(csiId)<<std::endl;
      }
      
      if(csiId<2240){	
	if(regionflag==0){
	  stackXID = stackID%nBlockFine;
	  stackYID = int(stackID/nBlockFine);	
	} else {
	  stackXID = (stackID%nBlockFine)/2+7;
	  stackYID = (stackID/nBlockFine)/2+7;
	}
      } else{
	stackXID = stackID%nLayer;
	stackYID = stackID/nLayer;     
      }

      if( startxid <= stackXID && stackXID <= endxid){
	if( startyid <= stackYID && stackYID <= endyid){	    
	  annpara[(stackXID-startxid)+ regionnumber* (stackYID-startyid) ]
	    += csiE;
	  anntotE += csiE;
	}
      }      
    }

    if(regionflag==0){
      //      double R = sqrt(pow(g.x(),2)+pow(g.y(),2));
      //      annpara[25] = TMath::ATan( R / (6148 - pi0.recZ()) ) * 180/TMath::Pi();
      //      annpara[26] = TMath::ATan(g.y()/g.x())*180/TMath::Pi();
      annpara[25] = g.p3().theta()/CLHEP::deg;
      annpara[26] = g.p3().phi()/CLHEP::deg;
      if(g.x()<0 && g.y()<0) annpara[26] = annpara[26] - 180;
      else if(g.x()<0 && g.y()>0) annpara[26] = annpara[26] + 180;
    } else {
      //      double R = sqrt(pow(g.x(),2)+pow(g.y(),2));
      //      annpara[9] = TMath::ATan( R / (6148 - pi0.recZ()) ) * 180/TMath::Pi();
      //      annpara[10] = TMath::ATan(g.y()/g.x())*180/TMath::Pi();
      annpara[9] = g.p3().theta()/CLHEP::deg;
      annpara[10] = g.p3().phi()/CLHEP::deg;
      if(g.x()<0 && g.y()<0) annpara[10] = annpara[10] - 180;
      else if(g.x()<0 && g.y()>0) annpara[10] = annpara[10] + 180;      
    }

    m_ANNRegion=regionflag;
    for(int j=0; j<27; j++) m_ANNPara[j]=0;
    
    if(regionflag==0){
      for(int j=0; j<27; j++){
	m_ANNPara[j]=annpara[j];
      }
    } else {
      for(int j=0; j<11; j++){
	m_ANNPara[j]=annpara[j];
      }
    }
    //std::cout<<std::endl;
    //std::getchar();
    delete [] annpara;
    return 0;
}
  


int ShapeANN::readParameter(Gamma &g,int CsiNumber,int *CsiId,double *CsiEne)
{

  double  KtevCsic_XY  = 5.0;
  double  KtevCsic_Len = 50.0;
  double  KtevCsic_Gap = 0.03;

  double  KtevCsicFine_XY  = 2.5;
  double  KtevCsicFine_Len = 50.0;
  double  KtevCsicFine_Gap = KtevCsic_Gap*2.5/5.;

  int nBlockFine=48;
  int nBeamHole=8;
  int nLayer=38;
  
  static int init=0;
  static std::map<int,int> XYtoIDmap;
  static std::map<int,int> IDtoXYmap;
  static int region[3600]; 

  if(init==0){ 
    initANN(XYtoIDmap,IDtoXYmap,region);
    init=1;
  }

  double length = (KtevCsicFine_XY+KtevCsicFine_Gap)*nBlockFine/2.+KtevCsicFine_Gap/2;
  
  
  double* annpara;
  double anntotE=0;
  double tempx,tempy;
  int regionflag,regionnumber;
  int xid,yid,startxid,startyid,endxid,endyid;    
    
  if( length*10>TMath::Max(fabs(g.x()),fabs(g.y()) ) ){
    tempx = (g.x()/10.-KtevCsicFine_Gap)/(KtevCsicFine_XY+KtevCsicFine_Gap);
    tempy = (g.y()/10.-KtevCsicFine_Gap)/(KtevCsicFine_XY+KtevCsicFine_Gap);
    if(tempx < 0 ) xid = nBlockFine/2 + int(tempx) - 1;
    else xid = nBlockFine/2 + int(tempx);
    if(tempy < 0 ) yid = nBlockFine/2 + int(tempy) - 1;
    else yid = nBlockFine/2 + int(tempy);
      
    std::map<int,int>::iterator p;
    p = XYtoIDmap.find(yid*nBlockFine+xid);        
    if(p != XYtoIDmap.end()) regionflag= region[p->second];
    else  regionflag= 0;
    
  } else {
    tempx = (g.x()/10.-KtevCsic_Gap)/(KtevCsic_XY+KtevCsic_Gap);
    tempy = (g.y()/10.-KtevCsic_Gap)/(KtevCsic_XY+KtevCsic_Gap);
    if(tempx < 0 ) xid = nLayer/2 + int(tempx) - 1;
    else xid = nLayer/2 + int(tempx);
    if(tempy < 0 ) yid = nLayer/2 + int(tempy) - 1;
    else yid = nLayer/2 + int(tempy);
    regionflag=2;
  }
    

    
    
    if(regionflag==0){       // inner region
      startxid = xid-2;
      startyid = yid-2;
      endxid = xid+2;
      endyid = yid+2;
      regionnumber=5;
      annpara = new double[27];
      for(int i=0; i<27; i++) annpara[i]=0;
    } else {             // for middle or outer region
      if(regionflag==1){ // for middle region

	xid = xid/2 + 7;
	yid = yid/2 + 7;
      }
      startxid= xid-1;  
      startyid= yid-1;
      endxid= xid+1;
      endyid= yid+1;
      regionnumber=3;
      annpara = new double[11];
      for(int i=0; i<11; i++) annpara[i]=0;
    }

    //    int nHitCSI=ana_g2.GetCsIDigiSize();
    int nHitCSI=CsiNumber;
    for(int j=0; j<nHitCSI; j++){
      std::map<int,int>::iterator stackmap;
      int stackXID,stackYID,stackID;
      int csiId = CsiId[j];
      int csiE = CsiEne[j];
      stackmap = IDtoXYmap.find(csiId);
      if( stackmap != IDtoXYmap.end()) stackID= stackmap->second;
      else{
	std::cout<<"CsI IDtoXYmap mapping error"<<std::endl;
	std::cout<<"ID:"<<csiId<<" x:"<<CsiMap::getCsiMap()->getX(csiId)<<" y:"<<CsiMap::getCsiMap()->getY(csiId)<<std::endl;
      }
      
      if(csiId<2240){	
	if(regionflag==0){
	  stackXID = stackID%nBlockFine;
	  stackYID = int(stackID/nBlockFine);	
	} else {
	  stackXID = (stackID%nBlockFine)/2+7;
	  stackYID = (stackID/nBlockFine)/2+7;
	}
      } else{
	stackXID = stackID%nLayer;
	stackYID = stackID/nLayer;     
      }

      if( startxid <= stackXID && stackXID <= endxid){
	if( startyid <= stackYID && stackYID <= endyid){	    
	  annpara[(stackXID-startxid)+ regionnumber* (stackYID-startyid) ]
	    += csiE;
	  anntotE += csiE;
	}
      }      
    }

    if(regionflag==0){
      //      double R = sqrt(pow(g.x(),2)+pow(g.y(),2));
      //      annpara[25] = TMath::ATan( R / (6148 - pi0.recZ()) ) * 180/TMath::Pi();
      //      annpara[26] = TMath::ATan(g.y()/g.x())*180/TMath::Pi();
      annpara[25] = g.p3().theta()/CLHEP::deg;
      annpara[26] = g.p3().phi()/CLHEP::deg;
      if(g.x()<0 && g.y()<0) annpara[26] = annpara[26] - 180;
      else if(g.x()<0 && g.y()>0) annpara[26] = annpara[26] + 180;
    } else {
      //      double R = sqrt(pow(g.x(),2)+pow(g.y(),2));
      //      annpara[9] = TMath::ATan( R / (6148 - pi0.recZ()) ) * 180/TMath::Pi();
      //      annpara[10] = TMath::ATan(g.y()/g.x())*180/TMath::Pi();
      annpara[9] = g.p3().theta()/CLHEP::deg;
      annpara[10] = g.p3().phi()/CLHEP::deg;
      if(g.x()<0 && g.y()<0) annpara[10] = annpara[10] - 180;
      else if(g.x()<0 && g.y()>0) annpara[10] = annpara[10] + 180;      
    }

    m_ANNRegion=regionflag;
    for(int j=0; j<27; j++) m_ANNPara[j]=0;
    
    if(regionflag==0){
      for(int j=0; j<27; j++){
	m_ANNPara[j]=annpara[j];
      }
    } else {
      for(int j=0; j<11; j++){
	m_ANNPara[j]=annpara[j];
      }
    }
    delete [] annpara;
    return 0;
}


void ShapeANN::initANN(std::map<int,int>&XYtoIDmap,std::map<int,int>& IDtoXYmap,int* region)
{

  double  KtevCsic_XY  = 5.0;
  double  KtevCsic_Len = 50.0;
  double  KtevCsic_Gap = 0.03;

  double  KtevCsicFine_XY  = 2.5;
  double  KtevCsicFine_Len = 50.0;
  double  KtevCsicFine_Gap = KtevCsic_Gap*2.5/5.;

  int nBlockFine=48;
  int nBeamHole=8;
  int nLayer=38;

  for(int i=0; i<3600; i++){
    region[i]=0;
  }
  /*
  double tempx,tempy;
  int xid,yid;

  int ncsi = CsiMap::getCsiMap()->getN();
  for(int id=0;id<ncsi;id++){
    double x,y,w;
    CsiMap::getCsiMap()->getXYW(id,x,y,w);
    if(w==0){ continue;}

    if(w<30){
      tempx = (x/10.-KtevCsicFine_Gap)/(KtevCsicFine_XY+KtevCsicFine_Gap);
      tempy = (y/10.-KtevCsicFine_Gap)/(KtevCsicFine_XY+KtevCsicFine_Gap);
      if(tempx < 0 ) xid = nBlockFine/2 + int(tempx) - 1;
      else xid = nBlockFine/2 + int(tempx);
      if(tempy < 0 ) yid = nBlockFine/2 + int(tempy) - 1;
      else yid = nBlockFine/2 + int(tempy);
      
      if(xid<2 || xid>nBlockFine-3 || yid<2 || yid>nBlockFine-3) region[id]=1;
	
      IDtoXYmap.insert(std::make_pair(id,xid+yid*nBlockFine));
      XYtoIDmap.insert(std::make_pair(xid+yid*nBlockFine,id));
      
    } else {
      tempx = (x/10.-KtevCsic_Gap)/(KtevCsic_XY+KtevCsic_Gap);
      tempy = (y/10.-KtevCsic_Gap)/(KtevCsic_XY+KtevCsic_Gap);
      if(tempx < 0 ) xid = nLayer/2 + int(tempx) - 1;
      else xid = nLayer/2 + int(tempx);
      if(tempy < 0 ) yid = nLayer/2 + int(tempy) - 1;
      else yid = nLayer/2 + int(tempy);

      //      IDtoXYmap.insert(std::make_pair(id,(nLayer-nBlock)/2+xid+yid*nLayer));
      IDtoXYmap.insert(std::make_pair(id,xid+yid*nLayer));
    }
  }
}
  */


  
  //  int nBlockFine=48;
  //  int nBeamHole=8;
  int id=0;
  for(int i=0;i<nBlockFine;i++) {
    
    for(int j=0;j<nBlockFine;j++) {
      {
        //beam hole
        if( i>=(nBlockFine-nBeamHole)/2. &&
            i<(nBlockFine-nBeamHole)/2.+nBeamHole &&
            j>=(nBlockFine-nBeamHole)/2. &&
            j<(nBlockFine-nBeamHole)/2.+nBeamHole )
          continue;
	
        if(i<2 || i>nBlockFine-3 || j<2 || j>nBlockFine-3) region[id] = 1;
	
        IDtoXYmap.insert(std::make_pair(id,j+i*nBlockFine));
        XYtoIDmap.insert(std::make_pair(j+i*nBlockFine,id));
        id++;
      }
    }
  }
 
  int csiStack[38]
    = { 2,12,16,20,22,24,
        26,28,30,32,32,34,
        34,36,36,36,36,36,38,
        38,36,36,36,36,36,34,
        34,32,32,30,28,26,
        24,22,20,16,12,2 };
 
 // int csiStack[38]
//    = { 0,12,16,20,22,24,
//        26,28,30,32,32,34,
//        34,36,36,36,36,36,36,
//        36,36,36,36,36,36,34,
//        34,32,32,30,28,26,
//        24,22,20,16,12,0 };
  
//  int nLayer=38;

  std::cout<<id<<std::endl;

  for(int i=0;i<nLayer;i++) {
    int nBlock = csiStack[i];

    for(int j=0;j<nBlock;j++) {

      //KtevFine
      if( i>=(nLayer-nBlockFine/2.)/2. &&
          i<(nLayer-nBlockFine/2.)/2.+nBlockFine/2. &&
          j>=(nBlock-nBlockFine/2.)/2. &&
          j<(nBlock-nBlockFine/2.)/2.+nBlockFine/2. )
        continue;


      IDtoXYmap.insert(std::make_pair(id,(nLayer-nBlock)/2+j+i*nLayer));
      //XYtoIDmap.insert(std::make_pair((nLayer-nBlock)/2+j+i*nLayer,id));


      id++;
    }
  }
}





  
void ShapeANN::cnjfeed(int &ninp,int &nhid,
		      float* thre,float* weig,float* oin,
		      float &out) {
  int itc=0;
  int ijc=0;
  float A[50];
  float B=0;
  float O[50];

  for(int i=0;i<nhid;i++) {
    A[i]=thre[itc];
    itc++;
    for(int j=0;j<ninp;j++) {
      A[i]=A[i]+weig[ijc]*oin[j];
      ijc++;
    }
    O[i]=0.5*(1.0+TMath::TanH(A[i]));
  }
  B=thre[itc];
  itc++;
  for(int j=0;j<nhid;j++) {
    B=B+weig[ijc]*O[j];
    ijc++;
  }
  out=0.5*(1.0+TMath::TanH(B));
}
