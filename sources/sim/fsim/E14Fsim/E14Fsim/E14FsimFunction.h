#ifndef E14FsimFunction_h
#define E14FsimFunction_h

class E14FsimFunction
{
 public:
  E14FsimFunction();
  ~E14FsimFunction();

  static E14FsimFunction* getFunction();

  //ineffi. weight
  double getCSIWeight(double Mome , int PID);
  double getBARWeight(double Mome , int PID , double theta);
  
  //photon ineffi.
  double mbineff( double x, double theta );
  double csiineff( double x );

  //fusion
  double fusionProb(double dgg);
  double fusionProbKAMI(double dgg);
  double fusionProbChi2(double dgg);
  double fusionProbRMS(double dgg);
  

  //smearing
  double csiAngRes(double Egamma);
  double csiEnergyRes(double Egamma);
  double csiPosRes(double Egamma);

  inline void setFusionMode(int imode) { m_fusionMode=imode; }
    
 protected:
  static E14FsimFunction* s_function;


  double CVineff(double p , int PID);
  double PVineff(double Egamma);
  double newCVineffPi(double P , int PID);


  double func1(double* par, double x );
  double func0(double* par, double x );
  
  double m_CVineffPar[2][6];
  double m_fpar[9][4];

  int m_fusionMode;
};

#endif
