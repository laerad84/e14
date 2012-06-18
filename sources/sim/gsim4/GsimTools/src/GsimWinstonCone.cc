/**
 *  @file
 *  @brief  GsimWinstonCone
 *  $Id: $
 *  $Log:$
 */

#include "GsimTools/GsimRootSolver.h"
#include "GsimTools/GsimWinstonCone.h"
#include <cmath>

#include "TCanvas.h"
#include "TGraph.h"
#include "TH2.h"
#include "TMath.h"
#include "TLine.h"
#include "TArrow.h"
#include "TMarker.h"
#include "TArc.h"
#include "TLatex.h"
#include "TPad.h"

GsimWinstonCone::GsimWinstonCone(double tin,double tout)
{
  m_TIN=tin;
  m_TOUT=tout;
  m_maxSinTheta=m_TOUT/m_TIN;
  m_maxTheta=std::asin(m_maxSinTheta);
  m_Length=
    m_TOUT*(1.+1./m_maxSinTheta)/(2.*std::tan(m_maxTheta));

  m_pathLength=0.;
  m_nReflections=0;
  m_maxReflections=20;
  m_errorStatus=0;

  xPoint = new double[m_maxReflections+3];
  yPoint = new double[m_maxReflections+3];
  zPoint = new double[m_maxReflections+3];
  
  m_frame=0;
  m_grX=0;
  m_grY=0;
  m_nPoint=0;
}

GsimWinstonCone::~GsimWinstonCone()
{
  delete [] xPoint;
  delete [] yPoint;
  delete [] zPoint;
  delete m_frame;
  delete m_grX;
  delete m_grY;
}


double GsimWinstonCone::getMaxPath(double* r, double* v)
{

  double sp=0;
  if(v[2]<0) {
    sp=-r[2]/v[2];
  } else if(v[2]>0) {
    sp=(m_Length-r[2])/v[2];
  } else if(v[2]==0) {
    if(v[1]>0) {
      sp=(m_TIN/2.-r[0])/v[0];
    } else if(v[1]<0) {
      sp=(-m_TIN/2.-r[0])/v[0];
    } else if(v[0]==0.) {
      if(v[1]>0.) {
	sp=(m_TIN/2.-r[1])/v[1];
      } else if(v[1]<0.) {
	sp=(-m_TIN/2.-r[1])/v[1];
      } else {
	//ERROR
      }
    }
  }
  return sp;
}


double GsimWinstonCone::cwicof(double s,void *par)
{
  //par[11]
  //0  :m_TIN
  //1  :m_TOUT
  //2  :maxPathLength
  //3 pmaxSinTheta
  //4 pmaxTheta
  //5-7:r[3]
  //8-10:v[3]

  double *vpar=(double*)par;
  double out=0.;
  if(s==0.) {
    out=1.;
    return out;
  }
  
  if(s==vpar[2]) {
    out=-1.;
    return out;
  }
  
  double tanTheta=(vpar[1]/2.+std::sqrt(
				       std::pow(vpar[5]+s*vpar[8],2.)+
				       std::pow(vpar[6]+s*vpar[9],2.)
				       )
		   )/(vpar[7]+s*vpar[10]);
  double theta=std::atan(tanTheta);
  if(theta<vpar[4]) {
    out=1.;
    return out;
  } else {
    double rho=(1.+vpar[3])*vpar[1]/(1.-std::cos(theta+vpar[4]));
    out=std::pow(rho,2.)
      -std::pow(vpar[1]/2.+std::sqrt(
				    std::pow(vpar[5]+s*vpar[8],2.)+
				    std::pow(vpar[6]+s*vpar[9],2.)
				    ),2.)
      -std::pow(vpar[7]+s*vpar[10],2.);
    return out;
  }
}


bool GsimWinstonCone::trace(double* r, double* v)
{
  m_nPoint=0;
  m_pathLength=0.;
  m_nReflections=0;
  m_errorStatus=0;
  
  double THLIM=-1000.;
  
  double vmag=std::sqrt(std::pow(v[0],2.)+std::pow(v[1],2.)+std::pow(v[2],2.));
  if(vmag==0.) {
    //error
    return false;
  }

  if(vmag!=1.) {
    for(int i=0;i<3;i++) {
      v[i]=v[i]/vmag;
    }
  }

  if(r[2]==m_Length &&
     std::sqrt(
	       std::pow(r[0],2.)+
	       std::pow(r[1],2.) ) > m_TIN/2.) {
    // WRITE(6,*)'IERR=1 - ray incident out of the entrance face'
    m_errorStatus=1;
    return false;
  }

  

  while(1) {
    xPoint[m_nPoint]=r[0];
    yPoint[m_nPoint]=r[1];
    zPoint[m_nPoint]=r[2];
    m_nPoint++;

    double sp=getMaxPath(r,v);
    
    double r1[3]={0.,0.,0.};
    r1[0]=r[0]+v[0]*sp;
    r1[1]=r[1]+v[1]*sp;
    r1[2]=r[2]+v[2]*sp;
    double r1mag=std::sqrt(
			   std::pow(r1[0],2.)+
			   std::pow(r1[1],2.) );
    if(m_nReflections>0) {
      if( v[2] < 0. && r1mag < m_TOUT/2. ) {
	//reach to bottom
	m_pathLength+=sp;
	for(int k=0;k<3;k++) {
	  r[k]=r1[k];
	}
	r[2]=0.;
	m_errorStatus=0;
	xPoint[m_nPoint]=r[0];
	yPoint[m_nPoint]=r[1];
	zPoint[m_nPoint]=r[2];
	m_nPoint++;
	return true;
      } else if(v[2]>0 && r1mag < m_TIN/2.) {
	//reach to top
	for(int k=0;k<3;k++) {
	  r[k]=r1[k];
	}
	r[2]=m_Length;
	m_errorStatus=3;
	xPoint[m_nPoint]=r[0];
	yPoint[m_nPoint]=r[1];
	zPoint[m_nPoint]=r[2];
	m_nPoint++;
	m_pathLength+=sp;
	// WRITE(6,*)'IERR=3 - the ray comes back to the entrance face'
	return false; 
      }
    }
    
    //hit to surface
    
    if(m_nReflections>m_maxReflections) {
      //exceed max reflections
      m_errorStatus=2;
      // WRITE(6,*)'IERR=2 - number of bounces greater than NMAX'
      return false;
    }
    m_nReflections++;

    //calculate intersection
    
    double par[11]
      ={m_TIN,m_TOUT,sp,
	m_maxSinTheta,m_maxTheta,
	r[0],r[1],r[2],v[0],v[1],v[2]};
    
    GsimRootSolver* rootSolver=GsimRootSolver::getGsimRootSolver();
    rootSolver->setFunction(cwicof,11,par);

    if(sp<0 && sp>-1.e-10) sp=0.;
    //rootSolver->solve(0,sp,1);
    rootSolver->solve(0,sp,0);
    double sst=rootSolver->getRootX();

    for(int k=0;k<3;k++) {
      r1[k]=r[k]+sst*v[k];
    }
    
    //determination of the tangent plane at the impact point
    double tanTheta=(m_TOUT/2.+std::sqrt(std::pow(r1[0],2.)+std::pow(r1[1],2.)))/r1[2];
    double theta=std::atan(tanTheta);
    double XPRIME=std::sqrt(
			    std::pow(std::sqrt( std::pow(r1[0],2.)+std::pow(r1[1],2.))+m_TOUT/2.,2.)
			    +std::pow(r1[2],2.)
			    )*std::sin(theta+m_maxTheta);

    double A=1./m_TOUT/(1.+m_maxSinTheta)/2.;
    double ETA=std::atan(2.*A*XPRIME)+m_maxTheta;
    double ZETA=std::atan2(r1[1],r1[0]);
    if(ZETA<0.) ZETA=ZETA+2.*M_PI;

    double normalV[3]
      =
      {
	-std::sin(ETA)*std::cos(ZETA),
	-std::sin(ETA)*std::sin(ZETA),
	std::cos(ETA)
      };

    double cosInAngle=0;
    for(int k=0;k<3;k++) {
      cosInAngle+=normalV[k]*v[k];
    }
    double iAng=std::acos(cosInAngle);
    if(iAng<=THLIM) {
      //        WRITE(6,*)'IERR=4 - ray incident out of limit angle'
      m_errorStatus=4;
      xPoint[m_nPoint]=r1[0];
      yPoint[m_nPoint]=r1[1];
      zPoint[m_nPoint]=r1[2];
      m_nPoint++;
      return false;
    }


    
    for(int k=0;k<3;k++) {
      v[k]=v[k]+2.*std::abs(cosInAngle)*normalV[k];
    }

    m_pathLength+=std::sqrt(
			    std::pow(r[0]-r1[0],2.)+
			    std::pow(r[1]-r1[1],2.)+
			    std::pow(r[2]-r1[2],2.));

    r[0]=r1[0];
    r[1]=r1[1];
    r[2]=r1[2];
    
    //if (r[2] > 33.6) {  // tsugime of funnel
    //  call diffuse2(XP,YP,CX0,CY0,CZ0,SIGMA,OFFSETANG);
    //}
  }
}


void GsimWinstonCone::setMaxReflections(int n)
{
  m_maxReflections=n;
  if(xPoint) delete [] xPoint;
  if(yPoint) delete [] yPoint;
  if(zPoint) delete [] zPoint;

  xPoint = new double[m_maxReflections+3];
  yPoint = new double[m_maxReflections+3];
  zPoint = new double[m_maxReflections+3]; 
}

double GsimWinstonCone::wcp(double z,double a,double th) {
  double ct=TMath::Cos(th);
  double st=TMath::Sin(th);

  double a2=std::pow(ct,2.);
  double a1=
    +4.*a*std::pow(st,2.)
    +2.*z*ct*st
    +4.*a*st
    +2.*a*std::pow(ct,2.);
  double a0=
    +std::pow(z*st,2.)
    -2.*a*z*ct*st
    -4.*std::pow(a,2.)*st
    -4.*a*z*ct
    +std::pow(a*ct,2.)
    -4.*std::pow(a,2.);
  
  
  double r=
    (-a1+std::sqrt(std::pow(a1,2)-4.*a0*a2))/(2.*a2);

  return r;
}

double GsimWinstonCone::wcm(double z,double a,double th) {
  
  double ct=TMath::Cos(th);
  double st=TMath::Sin(th);

  double a2=std::pow(ct,2.);
  double a1=
    +4.*a*std::pow(st,2.)
    +2.*z*ct*st
    +4.*a*st
    +2.*a*std::pow(ct,2.);
  double a0=
    +std::pow(z*st,2.)
    -2.*a*z*ct*st
    -4.*std::pow(a,2.)*st
    -4.*a*z*ct
    +std::pow(a*ct,2.)
    -4.*std::pow(a,2.);
  
  double r=
    (-a1+std::sqrt(std::pow(a1,2)-4.*a0*a2))/(2.*a2);
  
  return -1*r;
}

void GsimWinstonCone::drawWinstonCone()
{
  if(!gPad) {
    TCanvas* c1 = new TCanvas("c1","",600,600);
    c1->SetFillStyle(0);
    c1->SetFrameFillStyle(0);
    c1->Draw();
  }
  double th=m_maxTheta;
  double a=m_TOUT/2.;
  double zmax=(1./TMath::Sin(th)+1.)*a/TMath::Tan(th);
  double xmax=wcp(zmax,a,th);
//   double zo=
//     -std::cos(m_maxTheta)*
//     a*(1+std::sin(m_maxTheta));
//   double xo=-a
//     +std::sin(m_maxTheta)*
//     a*(1+std::sin(m_maxTheta));
  
  TGraph* grw = new TGraph();
  grw->SetLineWidth(2);
  grw->SetLineColor(3);
  int N=1000;
  double dz=(zmax-0)/(N*1.);
  for(int k=0;k<N+1;k++) {
    double z=0+dz*(N-k);
    double y=wcp(z,a,th);
    grw->SetPoint(k,y,z);
  }
  for(int k=0;k<N+1;k++) {
    double z=0+dz*k;
    double y=wcm(z,a,th);
    grw->SetPoint(N+k,y,z);
  }

  if(m_frame) delete m_frame;
  m_frame = new TH2D("WinstonFrame","",
		     100,-xmax*1.1,xmax*1.1,
		     100,0,zmax*1.1);
  
  m_frame->SetStats(0);
  m_frame->Draw();
  grw->Draw("L");
  gPad->Modified();
  gPad->Update();
}

void GsimWinstonCone::drawWinstonConeWithParameters()
{
  if(!gPad) {
    TCanvas* c1 = new TCanvas("c1","",600,600);
    c1->SetFillStyle(0);
    c1->SetFrameFillStyle(0);
    c1->Draw();
  }
  double th=m_maxTheta;
  double a=m_TOUT/2.;
  double zmax=(1./TMath::Sin(th)+1.)*a/TMath::Tan(th);
  double xmax=wcp(zmax,a,th);
  double zo=
    -std::cos(m_maxTheta)*
    a*(1+std::sin(m_maxTheta));
  //double xo=wcp(zo,a,th);
  double xo=-a
    +std::sin(m_maxTheta)*
    a*(1+std::sin(m_maxTheta));
  
  TGraph* grw = new TGraph();
  grw->SetLineWidth(2);
  grw->SetLineColor(3);
  TGraph* gre = new TGraph();
  gre->SetLineWidth(1);
  gre->SetLineColor(1);
  int N=1000;
  double dz=(zmax-0)/(N*1.);
  for(int k=0;k<N+1;k++) {
    double z=0+dz*(N-k);
    double y=wcp(z,a,th);
    grw->SetPoint(k,y,z);
  }
  for(int k=0;k<N+1;k++) {
    double z=0+dz*k;
    double y=wcm(z,a,th);
    grw->SetPoint(N+k,y,z);
  }
  dz=(0-zo)/(N*1.);
  for(int k=0;k<N+1;k++) {
    double z=zo+dz*k;
    double y=wcp(z,a,th);
    gre->SetPoint(k,y,z);
  }
  
  
  
  double mm=std::max(zmax,xmax);
  if(m_frame) delete m_frame;
  m_frame = new TH2D("WinstonFrame","",
		     100,-mm*1.2,mm*1.2,
		     100,-mm*1.2,mm*1.2);

  m_frame->SetStats(0);
  m_frame->Draw();
  grw->Draw("L");
  gre->Draw("L");
  
  
  TLine* l1 = new TLine(-a,0,xmax,zmax);
  TLine* l2 = new TLine(-a,0,-a,zmax);
  l1->Draw();
  l2->Draw();

  {
    double ze=zmax;
    double xe=
      (xo+m_TOUT/2.)/(zo-0.)*zmax-m_TOUT/2.;
    if(xe>mm) {
      xe=mm;
      ze=(xe+m_TOUT/2.)/(xo+m_TOUT/2.)*(zo-0.);
    }
    TArrow* lyp = new TArrow(xo,zo,xe,ze);
    lyp->Draw();
    (new TLatex(xe,ze,"z'"))->Draw();
  }

  {
    double ze=zmax;
    double xe=
      -1./(xo+m_TOUT/2.)*(zo-0.)
      *zmax
      -1./(xo+m_TOUT/2.)*(zo-0.)*(-zo)+xo;
    if(xe>mm) {
      xe=mm;
      ze=(xe-(-1./(xo+m_TOUT/2.)*(zo-0.)*(-zo)+xo))*(-1.)*(xo+m_TOUT/2.)/(zo-0.);
    }
    TArrow* lxp = new TArrow(xo,zo,xe,ze);
    lxp->Draw();
    (new TLatex(xe,ze,"x'"))->Draw();
  }
  
  TArrow* lx = new TArrow(0,0,0,mm);
  TArrow* ly = new TArrow(0,0,mm,0);
  lx->Draw();
  ly->Draw();
  (new TLatex(0,mm,"z"))->Draw();
  (new TLatex(mm,0,"x"))->Draw();

  TMarker* m = new TMarker(-a,0,24);
  m->Draw();

  TArc* arc0 = new TArc(-a,0,mm/2.,90,90+m_maxTheta/TMath::Pi()*180.);
  TArc* arc1 = new TArc(-a,0,mm/2.,90-m_maxTheta/TMath::Pi()*180.,90);
  arc0->SetFillStyle(0);
  arc0->Draw();
  arc1->SetFillStyle(0);
  arc1->Draw();
  TLatex* f0 = new TLatex(-1.8*a-a,mm/2*1.2,"#theta_{max}");
  TLatex* f1 = new TLatex(-1.8*a+a,mm/2*1.2,"#theta_{max}");
  TLatex* f2 = new TLatex(-a*2,-a,"f");
  TLatex* f3 = new TLatex(0,-mm*0.3,"T_{out}");
  TLatex* f4 = new TLatex(0,mm*1.1,"T_{in}");
  
  f0->Draw();
  f1->Draw();
  f2->Draw();
  f3->Draw();
  f4->Draw();

  TArrow* aout = new TArrow(-a,-mm*0.3,a,-mm*0.3,0.05,"<>");
  aout->Draw();
  TArrow* ain = new TArrow(-m_TIN/2.,mm*1.1,m_TIN/2.,mm*1.1,0.05,"<>");
  ain->Draw();
  TArrow* af = new TArrow(xo,zo,-a,0,0.03,"<>");
  af->Draw();

  {
    double z=zmax/3.;
    double x=wcp(z,a,th);
    (new TMarker(x,z,24))->Draw();
    (new TArrow(-a,0,x,z,0.03,"<>"))->Draw();
    TArc* ap=new TArc(-a,0,mm/3.,
		      TMath::ATan(z/(x+a))/TMath::Pi()*180,90);
    ap->SetFillStyle(0);
    ap->Draw();
    (new TLatex(-0.8*a,mm/3,"#theta"))->Draw();
    (new TLatex(x*0.5,z*0.5,"#rho(#theta)"))->Draw();


    double theta=std::atan((a+x)/z);
    double xp=std::sqrt(std::pow(x+a,2.)+std::pow(z,2))*std::sin(theta+m_maxTheta);
    double f=a*(1.+std::sin(m_maxTheta));
    double eta=std::atan(1./(2.*f)*xp)+m_maxTheta;
    double grad=TMath::Tan(eta);
    double dx=0.3*mm*std::cos(eta);
    double xs=x-dx;
    double xe=x+dx;
    double zs=(grad)*(xs-x)+z;
    double ze=(grad)*(xe-x)+z;
    (new TLine(xs,zs,xe,ze))->Draw();
    dx=0.3*mm*std::sin(eta);
    xe=x-dx;
    ze=-1./grad*(-dx)+z;
    xs=x;
    zs=z;
    (new TLine(xs,zs,xe,ze))->Draw();
    (new TLine(x,z,x,z+0.3*mm))->Draw();
    TArc* aq=new TArc(x,z,mm*0.15,
		      90,90+eta/TMath::Pi()*180.);
    aq->SetFillStyle(0);
    aq->Draw();
    (new TLatex(x-0.1*mm,z+0.1*mm,"#eta"))->Draw();
  }

  (new TLatex(-mm*0.9,-mm*0.6,"Define with x'^{2}=4fy' and #theta_{max}"))->Draw();
  (new TLatex(-mm*0.9,-mm*0.8,"or define with T_{in} and T_{out}"))->Draw();
  //(new TLatex(-mm*0.9,-mm*0.7,"#theta=atan((a+x)/z),a=T_{out}/2"))->Draw();
  //(new TLatex(-mm*0.9,-mm*0.95,"x'=#sqrt{(a+x)^{2}+z^{2}}#times sin(#theta+#theta_{max})"))->Draw();
  //2x dx = 4f dy
  //x 1/(2f) =dy/dx
  
  gPad->Modified();
  gPad->Update();
}
    
    
    


  




void GsimWinstonCone::drawTrace()
{
  if(m_grX) delete m_grX;
  m_grX = new TGraph(m_nPoint,
		     xPoint,zPoint);
  
  if(m_grY) delete m_grY;
  m_grY = new TGraph(m_nPoint,
		     yPoint,zPoint);
  
  m_grX->SetLineColor(2);
  m_grY->SetLineColor(4);
  m_grX->SetMarkerStyle(20);
  m_grY->SetMarkerStyle(20);
  
  m_grX->Draw("LP same");
  m_grY->Draw("LP same");
  
  gPad->Modified();
  gPad->Update();
}
