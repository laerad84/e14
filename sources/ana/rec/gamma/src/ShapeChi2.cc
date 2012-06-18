#include "gamma/ShapeChi2.h"
#include "csimap/CsiMap.h"
#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include <fstream>
#include "TMath.h"

ShapeChi2::ShapeChi2()
{
  
  int arrSize = 3*s_numEvalue*s_numTvalue*s_numPvalue*s_numCtrBin*s_numCtrBin;
  for(int i=0;i<arrSize;i++){
    mapNum[i]=0;
    mapMean[i]=mapSquare[i]=0;
  }
  
  for(int i0=0;i0<2;i0++){
    for(int i1=0;i1<2;i1++){
      for(int i2=0;i2<s_numEvalue;i2++){
	for(int i3=0;i3<s_numTvalue;i3++){
	  for(int i4=0;i4<s_numPvalue;i4++){
	    distRowE[i0][i1][i2][i3][i4] = 0;
	  }
	}
      }
    }
  }
  loadMap();
}


ShapeChi2::~ShapeChi2(){
  for(int type=0;type<3;type++){
    for(int e=0;e<s_numEvalue;e++){
      for(int t=0;t<s_numTvalue;t++){
        for(int p=0;p<s_numPvalue;p++){
          for(int ctrx = 0;ctrx<s_numCtrBin;ctrx++){
            for(int ctry= 0;ctry<s_numCtrBin;ctry++){
	      int index = getMapAddress(type,e,t,p,ctrx,ctry);
	      if(mapNum[index]!=0)  delete [] mapNum[index];
	      if(mapMean[index]!=0)  delete [] mapMean[index];
	      if(mapSquare[index]!=0)  delete [] mapSquare[index];
	    }
	  }
	}
      }
    }
  }
  for(int i0=0;i0<2;i0++){
    for(int i1=0;i1<2;i1++){
      for(int i2=0;i2<s_numEvalue;i2++){
	for(int i3=0;i3<s_numTvalue;i3++){
	  for(int i4=0;i4<s_numPvalue;i4++){
	    if( distRowE[i0][i1][i2][i3][i4] !=0 )
	      delete distRowE[i0][i1][i2][i3][i4];
	  }
	}
      }
    }
  }
}



void ShapeChi2::shapeChi2( Gamma& gamma )
{
  // made by Sato
  double const ene = gamma.e();
  double theta = gamma.p3().theta();
  double phi = gamma.p3().phi();
  //  std::list<CSI> csiList = gamma.csiList();
  int const size = gamma.clusterIdVec().size();
  //  double csiedep[size],csiposx[size],csiposy[size],csiwidth[size];
  double *csiedep,*csiposx,*csiposy,*csiwidth;
  csiedep = new double[size];
  csiposx = new double[size];
  csiposy = new double[size];
  csiwidth = new double[size];

  for(int i=0;i<size;i++){
    csiedep[i]=gamma.clusterEVec()[i];
    int id = gamma.clusterIdVec()[i];
    csiposx[i]=CsiMap::getCsiMap()->getX(id);
    csiposy[i]=CsiMap::getCsiMap()->getY(id);
    csiwidth[i]=CsiMap::getCsiMap()->getW(id);
  }
  
  for(int i=0;i<size;i++){
    csiedep[i]/=ene;//normalize
  }
  theta = theta*180/TMath::Pi();//rad->deg
  phi = phi*180/TMath::Pi();//rad->deg
  
  double* csipos[2]={csiposx,csiposy};
  rotAndMirror(phi,size,csipos);  
  int index[5];
  double percentage[3];
  selectMap(ene,theta,phi,index,percentage);
  int mode=calcRatioOfRowE(size,csiedep,csipos,csiwidth,index,percentage);
  
  double chi2 = compare(size,csiedep,csipos,csiwidth,index,percentage,mode);
  gamma.setChisq(chi2);
  delete [] csiedep;
  delete [] csiposx;
  delete [] csiposy;
  delete [] csiwidth;
}

////////////////////////
//  private functions //
////////////////////////

void ShapeChi2::loadMap()
{
  std::string dirName = std::getenv("E14_TOP_DIR");
  std::string mapFineName = dirName + "/share/gamma/mapFineCsi_f.dat"; 
  std::string mapLargeName = dirName + "/share/gamma/mapFineCsi_l.dat"; 
  std::string mapLargeCsiName = dirName + "/share/gamma/mapLargeCsi.dat"; 
  std::string mapName[3]={mapFineName.c_str(),mapLargeName.c_str()
			  ,mapLargeCsiName.c_str()};
  for(int type=0;type<3;type++){
    std::cout<<"read "<<mapName[type].c_str()<<std::endl;
    std::ifstream ifs(mapName[type].c_str());
    if(!ifs){
      std::cout<<"can't find "<<mapName[type]<<std::endl;
      exit(1);
    }
    int size = s_mapSize;
    if(type==2)size/=2;
    for(int e=0;e<s_numEvalue;e++){
      for(int t=0;t<s_numTvalue;t++){
	for(int p=0;p<s_numPvalue;p++){
	  for(int ctrx = 0;ctrx<s_numCtrBin;ctrx++){
	    for(int ctry= 0;ctry<s_numCtrBin;ctry++){
	      double trash;
	      ifs>>trash;
	      int index = getMapAddress(type,e,t,p,ctrx,ctry);
	      mapNum[index] = new int[size*size];
              mapMean[index] = new float[size*size];
              mapSquare[index] = new float[size*size];
	      for(int x=0;x<size;x++){
		for(int y=0;y<size;y++){
                  ifs>>mapNum[index][x*size+y];
                  ifs>>mapMean[index][x*size+y];
                  ifs>>mapSquare[index][x*size+y];
                }}
	    }}}}}
    ifs.close();
  }

  
  {
    std::string fname =std::getenv("E14_TOP_DIR");
    fname+="/share/gamma/distRowEnergy.dat";
    std::ifstream ifs(fname.c_str());
    if(!ifs){
      std::cout<<"can't find "<<fname<<std::endl;
      exit(1);
    }
    for(int i0=0;i0<2;i0++){
      for(int i1=0;i1<2;i1++){
	for(int i2=0;i2<s_numEvalue;i2++){
	  for(int i3=0;i3<s_numTvalue;i3++){
	    for(int i4=0;i4<s_numPvalue;i4++){
	      distRowE[i0][i1][i2][i3][i4] = new float[100];
	      for(int i=0;i<100;i++)
		ifs>>distRowE[i0][i1][i2][i3][i4][i];
	    }}}}}
    ifs.close();
  }
  
}



int ShapeChi2::getMapAddress(int const &forl,int const &e,int const &t,
				  int const &p,int const &x,int const &y) const{
  static int const coX=s_numCtrBin;   
  static int const coP=s_numCtrBin*s_numCtrBin;   
  static int const coT=s_numPvalue*s_numCtrBin*s_numCtrBin;   
  static int const coE=s_numTvalue*s_numPvalue*s_numCtrBin*s_numCtrBin;   
  static int const coFORL=s_numEvalue*s_numTvalue*s_numPvalue
    *s_numCtrBin*s_numCtrBin;   
  
  return coFORL*forl+coE*e+coT*t+coP*p+coX*x+y;
}



void ShapeChi2::rotAndMirror(double& phi,int const &csize,
				  double * const *csipos)
{
  int rot = (int)(phi/90.+2.5);
  int mirror =((int)(phi/45.+5)%2*2-1);
  
  phi = (phi-(rot-2)*90)*mirror;
  for(int i = 0;i<csize;i++){
    double x = csipos[0][i];
    double y = csipos[1][i];      
    if(rot==1){
      csipos[0][i]=-y;      
      csipos[1][i]=x*mirror;
    }else if(rot==2){
      csipos[0][i]=x;
      csipos[1][i]=y*mirror;
    }else if(rot==3){
      csipos[0][i]=y;
      csipos[1][i]=-x*mirror;
    }else if(rot==4||rot==0){
      csipos[0][i]=-x;
      csipos[1][i]=-y*mirror;
    }else{
      std::cout<<"Err: rotAndMirrot"<<std::endl;
      exit(0);
    }
  }
}

void ShapeChi2::selectMap(double const &ene,double const &theta,
			       double const &phi,int *index,double *percentage)
{
  static int const numVal[3]={s_numEvalue,s_numTvalue,s_numPvalue};
  static double const minVal[3]={log(100),0,0};
  static double const maxVal[3]={log(2000),42.,45.};
  static double const deltaVal[3] ={(maxVal[0]-minVal[0])/(numVal[0]-1),
				    (maxVal[1]-minVal[1])/(numVal[1]-1),
				    (maxVal[2]-minVal[2])/(numVal[2]-1)};

  double mapParam[3]={log(ene),theta,phi};
  if(mapParam[2]<0-1e-7||mapParam[2]>45+1e-7){
    std::cout<<"error : shape Chi2 Calculation"<<std::endl;
    exit(0);
  }
  //  std::cout<<"theta"<<theta<<std::endl;
  for(int i=0;i<3;i++){
    if(mapParam[i]<minVal[i]){
      index[i]=0;
      percentage[i]=1;
    }else{
      double val=(mapParam[i]-minVal[i])/deltaVal[i];
      index[i]=(int)(val);
      if(index[i]>=numVal[i]-1){
	index[i]=numVal[i]-2;
	percentage[i]=0;
      }else{
	percentage[i]=1-fmod(val,1);
      }
    }
  }
  //  std::cout<<"index:"<<index[1]<<" per:"<<percentage[1]<<std::endl;
}


int ShapeChi2::calcRatioOfRowE(int const &csize,double const *csiedep,
				    double *const *csipos,
				    double const *csiwidth,int *index,
				    double const *percentage)
{
  
  static double const hmin = -1.;
  static double const hwidth = 0.02;

  //  static double loop=0;
  int mode=0;
  double origPos[2]={csipos[0][0]-csiwidth[0]/2,
		     csipos[1][0]-csiwidth[0]/2};
  for(int i=0;i<csize;i++){
    if(csiwidth[i]<30) continue;
    mode=1;
    origPos[0] = csipos[0][i]-csiwidth[i]/2;
    origPos[1] = csipos[1][i]-csiwidth[i]/2;
    break;
  }
  double const FineCsiWid=25.;
  for(int xy=0;xy<2;xy++){
    std::map<int,double> rowE;
    for(int i=0;i<csize;i++){
      csipos[xy][i]=(csipos[xy][i]-origPos[xy])/FineCsiWid+200;
      int key=(int)(csipos[xy][i]/(mode+1));
      rowE[key]+=csiedep[i];
    }
    double max=0;
    int maxid=0;
    for(std::map<int,double>::iterator i=rowE.begin();
	i!=rowE.end();i++){
      if(i->second<max) continue;
      maxid=i->first;
      max=i->second;	    
    }
    for(int i=0;i<csize;i++){
      csipos[xy][i]=csipos[xy][i]-maxid*(mode+1)+s_mapCtr;
    }
    double ratio;
    if(rowE[maxid-1]>rowE[maxid+1])
      ratio = -rowE[maxid-1]/rowE[maxid];
    else
      ratio = rowE[maxid+1]/rowE[maxid];
    int bin = (int)((ratio-hmin)/hwidth);	  
    float ctrPosAverage=0;
    for(int ei=0;ei<2;ei++){
      double coeffE =TMath::Abs(ei-percentage[0]);
      for(int ti=0;ti<2;ti++){
	double coeffT =TMath::Abs(ti-percentage[1]);
	for(int pi=0;pi<2;pi++){
	  double coeffP =TMath::Abs(pi-percentage[2]);
	  float ctrPos=distRowE[mode][xy][index[0]+ei][index[1]+ti][index[2]+pi][bin];
	  ctrPosAverage+=coeffE*coeffT*coeffP*ctrPos;
	}
      }
    }
    index[3+xy] =(int)(ctrPosAverage*s_numCtrBin);
    if(index[3+xy]==s_numCtrBin) index[3+xy]--;
    if(index[3+xy]>s_numCtrBin){std::cout<<"e"<<std::endl;exit(0);}
  }
  return mode;
}



double ShapeChi2::compare(int const &csize,double const *csiedep,
			       double const *const *csipos,
			       double const *csiwidth,int const *index,
			       double const *percentage,
			       int const &mode)
{
  double chi2=0;
  int ndf=0;
  for(int i=0;i<csize;i++){
    if(csipos[0][i]<0||csipos[0][i]>s_mapSize) continue;
    if(csipos[1][i]<0||csipos[1][i]>s_mapSize) continue;
    int xi=(int)(csipos[0][i]);
    int yi=(int)(csipos[1][i]);
    int ForL,mapCoordinate;
    if(csiwidth[i]>30){
      ForL=2;
      mapCoordinate = xi/2*(s_mapSize/2)+yi/2;      
      if(mapCoordinate>=25){
	std::cout<<"err: mapCoo>=25"<<std::endl;
	exit(0);
      }
    }else{
      ForL = mode;
      mapCoordinate = xi*s_mapSize+yi;      
      if(mapCoordinate>=100){
	std::cout<<"err: mapCoo>=100"<<std::endl;
	exit(0);
      }
    }
    ndf++;  
    double num,mean,disp;
    num=mean=disp=0;
    for(int ei=0;ei<2;ei++){
      double coeffE =TMath::Abs(ei-percentage[0]);
      for(int ti=0;ti<2;ti++){
	double coeffT =TMath::Abs(ti-percentage[1]);
	for(int pi=0;pi<2;pi++){
	  double coeffP =TMath::Abs(pi-percentage[2]);
	  double coeff=coeffE*coeffT*coeffP;
	  int address=getMapAddress(ForL,index[0]+ei,index[1]+ti,
				  index[2]+pi,index[3],index[4]);
	  num+=coeff*mapNum[address][mapCoordinate];
	  mean+=mapMean[address][mapCoordinate]*coeff;
	  disp+=(mapSquare[address][mapCoordinate]-pow(mapMean[address][mapCoordinate],2))*coeff;
	}
      }
    }
    if(disp==0){
      chi2=1000*ndf;
      break;
    }else{
      chi2+=pow(csiedep[i]-mean,2)/disp;
    }
  }
  if(ndf==0)
    chi2=1000;
  else
    chi2/=ndf;
  return chi2;
}

