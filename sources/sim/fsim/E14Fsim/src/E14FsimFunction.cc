#include "E14Fsim/E14FsimFunction.h"
#include "TMath.h"
#include <iostream>
#include <cmath>


E14FsimFunction* E14FsimFunction::s_function=0;

E14FsimFunction::E14FsimFunction()
{
  if(s_function) {
    std::cerr << "E14FsimFunction is constructed twice." << std::endl;
    return;
  }
  m_CVineffPar[0][0]=9.52657e-06;
  m_CVineffPar[1][0]=3.17552e-06;
  m_CVineffPar[0][1]=0.00190467;
  m_CVineffPar[1][1]=0.000634889;
  m_CVineffPar[0][2]=-0.0356322;
  m_CVineffPar[1][2]=-0.0356322;
  m_CVineffPar[0][3]=0.000343819;
  m_CVineffPar[1][3]=0.000114606;
  m_CVineffPar[0][4]=299.184;
  m_CVineffPar[1][4]=299.184;
  m_CVineffPar[0][5]=-51.0998;
  m_CVineffPar[1][5]=-51.0998;



  double tmpv[9][4]={
    {0.491215, -85.3823,  4.3708e-7,-1.83026},
    {0.645205, -130.363,  4.3708e-7,-1.83026},
    {0.729022, -162.020,  4.3708e-7,-1.83026},
    {0.783803, -180.183,  4.3708e-7,-1.83026},
    {0.821742, -191.685,  4.3708e-7,-1.83026},
    {0.844931, -199.065,  4.3708e-7,-1.83026},
    {0.860766, -203.985,  4.3708e-7,-1.83026},
    {0.868633, -206.584,  4.3708e-7,-1.83026},
    {0.872535, -207.804,  4.3708e-7,-1.83026},
  };
  for(int i=0;i<9;i++) {
    for(int j=0;j<4;j++) {
      m_fpar[i][j]=tmpv[i][j];
    }
  }
  s_function=this;

  m_fusionMode=0;
}


E14FsimFunction::~E14FsimFunction()
{
  ;
}


E14FsimFunction* E14FsimFunction::getFunction()
{
  if(!s_function) {
    s_function  = new E14FsimFunction();
  }
  return s_function;
}



double E14FsimFunction::getCSIWeight(double Mome , int PID)
{
  double Weight = 1;

  if (PID == 22) {
    Weight *= csiineff(Mome/1000);
  } else if (PID == 11 || PID==-11 || PID == 13 || PID == -13 ) {
    Weight *= TMath::Min(6*CVineff(Mome,PID) , 1.0); // KOPIO model x 6
  } else if (PID == 211  || PID == -211 ){
    Weight *= newCVineffPi(Mome,PID);
  }
  return (Weight);
}

double E14FsimFunction::getBARWeight(double Mome , int PID , double theta)
{
  double Weight = 1;

  if (PID == 22){
    Weight *= mbineff(Mome/1000.,theta);
  } else if (PID == 11 || PID==-11 || PID == 13 || PID == -13 ){
    Weight *= TMath::Min(6*CVineff(Mome,PID) , 1.0); // KOPIO model x 6
  } else if (PID == 211  || PID == -211 ){
    Weight *= newCVineffPi(Mome,PID);
  }
  return (Weight);
}




double E14FsimFunction::CVineff(double p , int PID)
{
  double DeadThick = 6.7;  // mg/cm^2
  double EthresCV = 0.05;  // MeV
  bool UsePVboost=true;

  //veto inefficiency for e,mu
  // Same as KOPIO Fast MC

  //c -- local
  
  double Ekin,pvboost,ineff;

  //c -- 25jan05 for pv_ineff
  //  double angle;
  //  int ierr;

  //c -- assumed minimum cv ineffy due to veto blindness
  double cvmin = 1.e-5;

  //c parameters for pi+ ineffy
  //c 12jul04 reduce by X4
  //      logical FIRST/.TRUE./
  double a,b;
  //c      double e1/185./,e2/360./,ineff1/1.e-4/,ineff2/2.e-5/
  double e1 = 185.;
  double e2 = 360.;
  double ineff1 = 0.25e-4;
  double ineff2 = 0.5e-5 ;

  double emass = 0.51099892;
  double mumass = 105.6538369;
  
  //c ------------------------------------------
  b = (log(ineff2)-log(ineff1))/(e2-e1);
  a = -b*e2+log(ineff2);

  //c -- species-dependent CV inefficiencies
  if (13 == PID ) {//! mu-
    ineff = cvmin;
  }
  else if (11 == PID ){ // then    ! e-
    ineff = cvmin;
  }
  else if (-11 == PID ){// then     ! e+
    ineff = 0.05/sqrt(p*p+emass * emass)/6;
  }
  else if (-13 == PID) {//then   ! mu+
    ineff = cvmin;
  }
  ineff = TMath::Max(cvmin,ineff);

  //c -- assumed improvement in CV ineffy due to detection
  //c -- of particles in PV.
  //c -- 12jul04 Allow PVboost for pi+. But not pi-

  pvboost = 1.;
  if (UsePVboost){// .and. ID.ne.-2) then

    //c -- assume relevant energy scale in PV for charged particles
    //c -- is the kinetic energy

    if (11 == PID || -11 == PID ){ // then ! e
      Ekin = sqrt(p*p+emass*emass)-emass;
    }
    else if (13 == PID || -13 == PID) {//then !mu
      Ekin = sqrt(p*p+mumass*mumass)-mumass;
    }
    
    //c -- cannot have improvement of more than a factor 1/100
    //c -- due to PV. The factor is larger for low kinetic energies.
    if (Ekin > 10.) { //then
      
      //      if (UseTaskForcePV.eq.6){// then
      //c -- 27jan05 pv_ineff is the PV ineffy as a function of angle and energy of the
      //c          incident photon. Since pv_boost is the result of some sort of conversion
      //c          or interaction in the CV, the direction of the photon(s) that strike the
      //c          PV is unknown. So I assume that normal incidence is a good approximation.
      //               angle = 0.
      //               pvboost = pv_ineff(Ekin,angle,ierr)
      //               if (ierr.ne.0) write(LUNout,'(1x,a,i3)')'CVN: WARNING PV_INEFF returns ierr=',ierr
      //            else
      //               pvboost = pvn(Ekin)
      //            endif
      
      pvboost = PVineff(Ekin);
      pvboost = TMath::Max(1.e-2,pvboost);
    }
  }      
  double cvn = ineff * pvboost ;
  
  return (cvn);
}

double E14FsimFunction::PVineff(double Egamma)
{
  // ineff = 1 for Eg<2MeV
  // ineff = 1E-6 for Eg>1GeV
  double ineff;
  if (Egamma <= 2) ineff = 1;
  else if (Egamma >= 1000) ineff = 1e-6;
  else {
    //  Double_T_t a = 10 ** (6 * log10(2) /( 3-log10(2)));
    //  Double_T_t b = 6 / (log10(2) -3);
    double a = 4.66886;
    double b = -2.22307;
    ineff = a * pow(Egamma,b);

  }
  return (ineff) ;
}



double E14FsimFunction::newCVineffPi(double P , int PID)
{

  int iPID;
  if (-211 == PID ) iPID =0;
  else  iPID =1;
  
  double mome = P;
  double ineff_exp =  m_CVineffPar[iPID][0]
    + m_CVineffPar[iPID][1]*exp(m_CVineffPar[iPID][2] * mome);
  
  double A = mome-m_CVineffPar[iPID][4];
  double sigma = m_CVineffPar[iPID][5];
  double ineff_gaus =  m_CVineffPar[iPID][3]*exp(- A*A/(2*sigma*sigma));
  double ineff = ineff_exp + ineff_gaus;
  //  double ineff = ineff_exp;
  
  ineff = TMath::Min(1.0 , ineff);
  return ineff;
}


double E14FsimFunction::csiAngRes(double Egamma)
{
  //[GeV],[rad]
  double sigma = 0.03 / sqrt(Egamma);
  return sigma;
}

double E14FsimFunction::csiEnergyRes(double Egamma)
{
  //GeV
  //1%/E+2%/sqrt(E)
  double sigmE=
    sqrt(0.01*0.01 * Egamma*Egamma + 0.02*0.02 * Egamma );
  
  return sigmE;
}

double E14FsimFunction::csiPosRes(double Egamma)
{
  return 5. / sqrt(Egamma); // mm
}

double E14FsimFunction::fusionProb(double dgg)
{
  if(m_fusionMode==0) {
    return fusionProbKAMI(dgg);
  } else if(m_fusionMode==1) {
    return fusionProbChi2(dgg);
  } else if(m_fusionMode==-1) {
    return 0;
  } else {
    return fusionProbRMS(dgg);
  }
}

double E14FsimFunction::fusionProbKAMI(double dgg)
{
  //[mm]
  
  double prob = 0;
  double ineff[17] = {1.0, 0.8,0.725,0.625,0.550,0.450,0.375,0.300,
                        0.250,0.160,0.125,0.080,0.070,0.040,0.025,
                        0.02,0.0};
  double dist[17] = {10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32,
                       34, 36, 38, 40, 50};

  int ID;
  if (dgg < 10) {
    prob = 1;
  }
  else if (dgg < 50 ){
    if (dgg < 40 ){
      ID = (int)((dgg-10.)/2.);
    }
    else {
      ID = 15;
    }
    double dist1 = dgg - dist[ID]; 
    double dist2 = dist[ID+1] - dgg; 

    prob = (dist2 * ineff[ID] + dist1 * ineff[ID+1])/ (dist1 + dist2);
  }
  else {
    prob = 0;
  }

  return prob;

}


double E14FsimFunction::fusionProbChi2(double dgg)
{
  //[mm]
  
  double prob = 0;
  double ineff[9] = {
    0.754521,
    0.72814,
    0.66229,
    0.532064,
    0.359221,
    0.215131,
    0.127594,
    0.081468,
    0.071284
  };
  double dist[9] = {5,15,25,35,45,55,65,75,85};

  int ID;
  if (dgg < 5) {
    prob = ineff[0];
  }
  else if (dgg < 85 ){
    ID = (int)((dgg-5.)/10.);
    double dist1 = dgg - dist[ID]; 
    double dist2 = dist[ID+1] - dgg; 
    prob = (dist2 * ineff[ID] + dist1 * ineff[ID+1])/ (dist1 + dist2);
  }
  else {
    prob = 0;
  }

  return prob;

}

double E14FsimFunction::fusionProbRMS(double dgg)
{
  //[mm]
  
  double prob = 0;
  double ineff[10] = {
    0.872083,
    0.867983,
    0.824325,
    0.758552,
    0.642557,
    0.462544,
    0.278677,
    0.145107,
    0.074921,
    0.046386
  };
  double dist[10] = {5,15,25,35,45,55,65,75,85,95};

  int ID;
  if (dgg < 5) {
    prob = ineff[0];
  }
  else if (dgg < 95 ){
    ID = (int)((dgg-5.)/10.);
    double dist1 = dgg - dist[ID]; 
    double dist2 = dist[ID+1] - dgg; 
    prob = (dist2 * ineff[ID] + dist1 * ineff[ID+1])/ (dist1 + dist2);
  }
  else {
    prob = 0;
  }

  return prob;

}


// MB : 5MeV<E<2GeV
// Do not call this function directly
double
E14FsimFunction::func1( double* par, double x )
{
  return  par[0] * exp(par[1] * x) + par[2] * pow(x,par[3]);
}

// MB : 0.5MeV<E<5 MeV
// Do not call this function directly
double
E14FsimFunction::func0( double* par, double x )
{
  double  f = func1(par,0.005);
  double  b = log(f)/(0.005-0.0005);
  double  a = exp(-0.0005*b);
  return  a * exp( b*x );
}

// Inefficiency Function for MB
// usage : double  f = mbineff( energy,theta )
//         energy=[GeV], theta=[degree],90deg=perpendicular to det surface.
double
E14FsimFunction::mbineff( double x, double theta )
{
  if ( x < 0.0005 )
    return 1.0;
  else if ( x > 2.0 )
    return func1(m_fpar[0],2.0);
  
  // 
  int     tindex = (int)floor((theta-5)/10.);
  double  tmod   = (theta-5)/10. - tindex;
  
  int  t1 = tindex;
  int  t2 = t1 + 1;
  if ( t1 < 0 ) t1 = 0;
  if ( t2 < 0 ) t2 = 0;
  if ( t1 > 8 ) t1 = 8;
  if ( t2 > 8 ) t2 = 8;
  
  double  f1,f2;  
  if ( x < 0.005 ){
    f1 = func0( m_fpar[t1],x );
    f2 = func0( m_fpar[t2],x );
  }
  else{
    f1 = func1( m_fpar[t1],x );
    f2 = func1( m_fpar[t2],x );
  }
  double  f = exp(log(f1)*(1.-tmod) + log(f2)*tmod);

  return f;
}

// Inefficiency Function for CsI
// usage : double  f = csiineff( energy )
//         energy=[GeV]
double
E14FsimFunction::csiineff( double x )
{
  double  par[]= {3.5409E-7, -2.27731};
  double  f;
  if ( x > 2.0 ) {
    f= par[0] * pow(2.0,par[1]);
  }
  else{
    f = par[0] * pow(x,par[1]);
    if ( f > 1.0 ) 
      f = 1.0;
  }
  
  return f;
}

