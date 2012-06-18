/**
 *  @file
 *  @brief  GsimRootSolver
 *  $Id: $
 *  $Log:$
 */
#ifndef GsimRootSolver_h
#define GsimRootSolver_h



class TF1;

//GSL extern "C" {
//GSL #include <gsl/gsl_math.h>
//GSL }

class GsimRootSolver
{
 public:
  ~GsimRootSolver();

  /// calls the object of singleton class.
  static GsimRootSolver* getGsimRootSolver();

  /// Set function with formula characters.
  void   setFunction(char* cFormula, double xlow,double xhigh,int n=0,double *par=0);

  /// Set function with function pointer;
  void   setFunction(double (*pFunc)(double x, void* p),int n=0,double *par=0);

  /// Solve root. gsl is used in mode==0, else CERNLIB dzero is used.
  void   solve(double xLow,double xHigh,int mode=0);

  /// print status.
  void   print();

  double getRootX();
  double getErrorX();
  int    getErrorStatus();
  int    getIterations();
  double eval(double x);
  
 private:
  GsimRootSolver();
  //GSL void   solveGSL(double xLow,double xHigh);
  void   solveD0(double xLow,double xHigh);
  void   solveBrent(double xLow,double xHigh);
  void   initBrent(double xLow,double xHigh);
  bool   iterateBrent(double& root,double& xLow,double& xHigh);
  bool   test_interval (double x_lower, double x_upper, double epsabs, double epsrel);

  /// singleton 
  static GsimRootSolver* s_rootSolver;

  /// static function used for gsl_function.function
  static double rootSolverFunction(double x,void* p);

  /// static function used in rootSolverFunction
  static TF1* s_function;
  
  /// gsl_function
  //GSL gsl_function m_gslfunc;

  double (* m_function) (double x, void * params);
  void* m_params;


  

  double m_espilonRelative;
  double m_epsilonAbsolute;
  unsigned int m_maxIterations;


  unsigned int m_iterations;
  int    m_errorStatus;
  double m_xError;
  double m_xLowBound;
  double m_xHighBound;
  double m_xRoot;


  //for my brent
  double m_a;
  double m_b;
  double m_c;
  double m_fa;
  double m_fb;
  double m_fc;
  double m_d;
  double m_e;
};

inline double GsimRootSolver::getRootX() { return m_xRoot; }
inline double GsimRootSolver::getErrorX() { return m_xError; }
inline int    GsimRootSolver::getErrorStatus() { return m_errorStatus; }
inline int    GsimRootSolver::getIterations() { return m_iterations; }

#endif //GsimRootSolver_h
