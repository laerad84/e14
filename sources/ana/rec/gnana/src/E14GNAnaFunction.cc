#include "gnana/E14GNAnaFunction.h"
#include "csimap/CsiMap.h"
#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include <fstream>
#include "TMath.h"


E14GNAnaFunction* E14GNAnaFunction::s_function=0;


E14GNAnaFunction::E14GNAnaFunction()
{
  if( s_function ){
    std::cerr << "E14GNAnaFunction is constructed twice." << std::endl;
    return;
  }
  s_function = this;
}


E14GNAnaFunction::~E14GNAnaFunction(){
  ;
}


E14GNAnaFunction* E14GNAnaFunction::getFunction() {
  if(!s_function) {
    s_function  = new E14GNAnaFunction();
  }
  return s_function;
}

void E14GNAnaFunction::correctEnergy(Gamma &gamma){
  double thre = gamma.cluster().threshold();
  double edep = gamma.edep();
  double ws=0,wl=0;
  std::vector<int> const &idvec = gamma.clusterIdVec();
  std::vector<double> const &evec = gamma.clusterEVec();
  
  int size = idvec.size();
  for(int i=0;i<size;i++){
    double width = CsiMap::getCsiMap()->getW(idvec[i]);
    if(width<30)  ws+=evec[i];
    else wl+=evec[i];
  }
  ws/=edep;
  wl/=edep;
  double leakFactor = showerLeakage(thre,edep,ws,wl);
  
  gamma.setEnergy(edep*(1+leakFactor));
}


void E14GNAnaFunction::correctPosition(Gamma &gam){
  static double const Pcor[2]={6.49003,0.99254};
  static double const CsIX0=18.5;//mm
  if( gam.p3().x()==0 && gam.p3().y()==0 && gam.p3().z()==0 ){
    return;
  }
  double ene = gam.e();  
  double L = CsIX0*(Pcor[0]+Pcor[1]*log(ene/1000.));//mm
  double sinTheta = sin(gam.p3().theta());
  double newx = gam.coex()-L*sinTheta*cos(gam.p3().phi());
  double newy = gam.coey()-L*sinTheta*sin(gam.p3().phi());
  
  gam.setPos( newx, newy, gam.z());
}

void E14GNAnaFunction::shapeChi2( Gamma& gamma )
{
  static ShapeChi2 calculator;
  calculator.shapeChi2(gamma);
}
/*
void E14GNAnaFunction::shapeANN( Gamma& gamma ,int CsiNumber,int *CsiId,double *CsiEne )
{
  static ShapeANN calculator;
  calculator.shapeANN(gamma,CsiNumber,CsiId,CsiEne);
}
*/
void E14GNAnaFunction::correctEnergy(Pi0 &pi){
  correctEnergy(pi.g1());
  correctEnergy(pi.g2());
}

void E14GNAnaFunction::correctEnergy(Klong &kl ){
  for(std::vector<Pi0>::iterator it = kl.pi0().begin();
      it!= kl.pi0().end(); it++){
    for(int igam=0;igam<2;igam++){
      Gamma& gam = (igam==0) ? it->g1() : it->g2();
      correctEnergy(gam);
    }
  }
}


void E14GNAnaFunction::correctPosition(Pi0 &pi){
  for(int igam=0;igam<2;igam++){
    Gamma& gam = (igam==0) ? pi.g1() : pi.g2();
    correctPosition(gam);
  }
}

void E14GNAnaFunction::correctPosition(Klong &kl ){
  int npi = kl.pi0().size();
  for(int ipi=0; ipi<npi; ipi++){
    Pi0& pi0 = kl.pi0().at(ipi);
    for(int igam=0;igam<2;igam++){
      Gamma& gam = (igam==0) ? pi0.g1() : pi0.g2();
      correctPosition(gam);
    }
  }
}

void E14GNAnaFunction::shapeChi2(Pi0 &pi){
  for(int igam=0;igam<2;igam++){
    Gamma& gam = (igam==0) ? pi.g1() : pi.g2();
    shapeChi2(gam);
  }
}

void E14GNAnaFunction::shapeChi2(Klong &kl ){
  int npi = kl.pi0().size();
  for(int ipi=0; ipi<npi; ipi++){
    Pi0& pi0 = kl.pi0().at(ipi);
    for(int igam=0;igam<2;igam++){
      Gamma& gam = (igam==0) ? pi0.g1() : pi0.g2();
      shapeChi2(gam);
    }
  }
}

////////////////////////
//  private functions //
////////////////////////

/////////////////////
//for correctEnergy//
/////////////////////

double E14GNAnaFunction::showerLeakage(double thre,double E,double ws,double wl){
  static int isWarning = true;
  static double const par[5][6]
    ={{-0.0124228, 0.0535973, -0.00570087, -0.0272626, 0.0492056, -0.0143836},
      {0.0135769, 0.0516771, 0.00738265,-0.0200259, 0.0532812, -0.00951445},
      {0.0451242, 0.0446529, 0.0220706,-0.00882033, 0.0543621, -0.00272351},
      {0.0632153, 0.050921, 0.0275368,0.0051316, 0.0534536, 0.00466786},
      {0.0705192, 0.063754, 0.0273419,0.0162835, 0.0534304, 0.010156} };
  static double const parthre[5] = {1.5,3.0,5.0,7.5,10};
  
  int ID = 0;
  double weight = 1;
  
  if(thre<parthre[0]||thre>=parthre[4]){
    if(isWarning){
      std::cout<<"warning : CsI energy threshold=="<<thre<<". The function for gamma energy correction is not prepared in this range"<<std::endl;
      isWarning = false;
    }
    if(thre>=parthre[4]){
      ID = 3;
      weight = 0;
    }
  }else{
    bool isFound = false;
    for(int i=1;i<5;i++){
      if(thre<parthre[i]){
	ID = i-1;
	weight = (parthre[i]-thre)/(parthre[i]-parthre[i-1]);
	isFound = true;
	//	std::cout<<"i:"<<i<<" ID:"<<ID<<std::endl;
	break;
      }
    }
    if( !isFound ){
      std::cout<<"Gamma::showerLeakage() : Error"<<std::endl;
      std::cout<<thre<<" "<<E<<std::endl;
      exit(1);
    }
  }

  double f0 = ws*(par[ID][0]+par[ID][1]/sqrt(E/1000.)-par[ID][2]*log(E/1000.))
    +wl*(par[ID][3]+par[ID][4]/sqrt(E/1000.)-par[ID][5]*log(E/1000.));
  ID++;
  double f1 = ws*(par[ID][0]+par[ID][1]/sqrt(E/1000.)-par[ID][2]*log(E/1000.))
    +wl*(par[ID][3]+par[ID][4]/sqrt(E/1000.)-par[ID][5]*log(E/1000.));


  double f = weight*f0+(1-weight)*f1;
  
  return f;
}
