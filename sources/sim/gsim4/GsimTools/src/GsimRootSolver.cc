/**
 *  @file
 *  @brief  GsimRootSolver
 *  $Id: $
 *  $Log:$
 */

#include "GsimTools/GsimRootSolver.h"
#include "TF1.h"

//GSL extern "C" {
//GSL #include <gsl/gsl_math.h>
//GSL #include <gsl/gsl_roots.h>
//GSL #include <gsl/gsl_errno.h>
//GSL }
#include <cmath>
#include <algorithm>
#include <iostream>
#include <iomanip>


GsimRootSolver* GsimRootSolver::s_rootSolver=0;
TF1* GsimRootSolver::s_function=0;


GsimRootSolver::GsimRootSolver()
{
  double dbleps=2.2204460492503131e-16;
  m_espilonRelative=10 * dbleps;
  m_epsilonAbsolute=10 * dbleps;
  m_maxIterations=10000;
  m_iterations=0;
  m_errorStatus=0;
  m_xError=0.;
  m_xLowBound=0.;
  m_xHighBound=0.;
  m_xRoot=0.;
}


GsimRootSolver::~GsimRootSolver()
{
  delete s_function;
}

GsimRootSolver* GsimRootSolver::getGsimRootSolver()
{
  if (!s_rootSolver) {
    static GsimRootSolver theRootSolver;
    s_rootSolver = &theRootSolver;
  }
  return s_rootSolver;
}

double GsimRootSolver::rootSolverFunction(double x,void* )
{
  double val=0.;
  if(s_function) {
    val=s_function->Eval(x);
  } else {
    std::cerr << "TF1 is not used but called rootSolverFunction" << std::endl;
    val=0.;
  }
  return val;
}

void GsimRootSolver::setFunction(double (*pFunc)(double x, void* p),
				 int , double* par)
{
  if(s_function) {
    delete s_function;
    s_function=0;
  }

  //GSL m_gslfunc.function = pFunc;
  //GSL m_gslfunc.params = par;
  m_function = pFunc;
  m_params = par;
}

void GsimRootSolver::setFunction(char* cFormula,double xlow,double xhigh,
				 int n, double *par)
{
  if(s_function) delete s_function;
  s_function = new TF1("GsimRootSolverFunction",
		       cFormula,xlow,xhigh);
  
  for(int i=0;i<n;i++) {
    s_function->SetParameter(i,par[i]);
  }

  //GSL m_gslfunc.function = &GsimRootSolver::rootSolverFunction;
  //GSL m_gslfunc.params = 0;
  m_function = &GsimRootSolver::rootSolverFunction;
  m_params = 0;
}

double GsimRootSolver::eval(double x)
{
  return
    m_function(x,m_params);
}

void GsimRootSolver::solve(double xLow,double xHigh,int mode)
{
  if(mode==0) {
    //GSL solveGSL(xLow,xHigh);
    solveBrent(xLow,xHigh);
  } else {
    solveD0(xLow,xHigh);
  }
}






void GsimRootSolver::solveD0(double xLow,double xHigh)
{

  double a=xLow;
  double b=xHigh;
  double x0=xLow;
  double eps=m_epsilonAbsolute;
  unsigned int mxf=m_maxIterations;
  double r=0.;

  
  double one=1.;
  double half=one/2.;


  double xa=std::min(a,b);
  double xb=std::max(a,b);
  double fa=eval(xa);
  double fb=eval(xb);
  if(fa*fb>0) {
    r=-2.*(xb-xa);
    x0=0;
    return;
  }

  double ee=0.;
  double ff=0.;
  unsigned int mc=0;


  bool isRepeat=true;

  m_errorStatus=0;
  m_iterations=0;
  while(isRepeat) {
    m_iterations++;
    //////////////////////////////
    x0=half*(xa+xb);
    r=x0-xa;
    ee=eps*(std::abs(x0)+1.);
    if(r < ee) {
      isRepeat=false;
      break;
    }
    //////////////////////////////
    
    
    
    
    
    double f1=fa;
    double x1=xa;
    double f2=fb;
    double x2=xb;

    
    double fx=0.;
    
    bool isJump=false;
    while(isRepeat) {
      m_iterations++;
      if(!isJump) {
	fx=eval(x0);
	mc++;
	if(mc>mxf) {
	  r=-half*std::abs(xb-xa);
	  x0=0.;
	  return;
	}
	
	if(fx*fa>0.) {
	  xa=x0;
	  fa=fx;
	} else {
	  xb=x0;
	  fb=fx;
	}
      }
      isJump=false;
      
      double u1=f1-f2;
      double u2=x1-x2;
      double u3=f2-fx;
      double u4=x2-x0;
      
      if(u2==0. || u4==0.) {
	break;
      }
      
      double f3=fx;
      double x3=x0;
      u1=u1/u2;
      u2=u3/u4;
      double ca=u1-u2;
      double cb=(x1+x2)*u2-(x2+x0)*u1;
      double cc=(x1-x0)*f1-x1*(ca*x1+cb);
      
      if(ca==0.) {
	if(cb==0.) break;
	x0=-cc/cb;
      } else {
	u3=cb/(2.*ca);
	u4=u3*u3-cc/ca;
	if(u4 < 0) break;
	if(x0+u3>=0) {
	  x0=-u3+std::sqrt(u4);
	} else {
	  x0=-u3-std::sqrt(u4);
	}
      }
      if(x0<xa || x0>xb) break;
      
      r=std::min(std::abs(x0-x3),std::abs(x0-x2));
      ee=eps*(std::abs(x0)+1.);
      if(r > ee) {
	f1=f2;
	x1=x2;
	f2=f3;
	x2=x3;
	continue;
      }
      fx=eval(x0);
      if(fx == 0.) {
	isRepeat=false;
	break;
      }

      double xx=0.;
      if(fx*fa < 0.) {
	xx=x0-ee;
	if(xx < xa) {
	  isRepeat=false;
	  break;
	}
	ff=eval(xx);
	fb=ff;
	xb=xx;
      } else {
	xx=x0+ee;
	if(xx>=xb) {
	  isRepeat=false;
	  break;
	}
	ff=eval(xx);
	fa=ff;
	xa=xx;
      }
      
      if(fx*ff>0.) {
	mc=mc+2;
	if(mc>mxf) {
	  r=-half*std::abs(xb-xa);
	  x0=0;
	  return;
	}
	f1=f3;
	x1=x3;
	f2=fx;
	x2=x0;
	x0=xx;
	fx=ff;
	isJump=true;
      }
      if(isJump) break;
      isRepeat=false;
    }
  }
  r=ee;
  ff=eval(x0);

  m_xError=r;
  m_xLowBound=xa;
  m_xHighBound=xb;
  if(xb<xa) {
    m_xLowBound=xb;
    m_xHighBound=xa;
  }
  m_xRoot=x0;
  
  return;
}



void GsimRootSolver::print()
{
  std::cout << "Root   : " << std::setprecision(17) << m_xRoot
	    << "\t" << std::setprecision(17) << m_xError << std::endl;
  std::cout << "Bound  : " << std::setprecision(17) << m_xLowBound
	    << "\t" << std::setprecision(17) << m_xHighBound << std::endl;
  std::cout << "Status : " << m_errorStatus
	    << "\t" << m_iterations << std::endl;
}



bool GsimRootSolver::iterateBrent (double& root, double& x_lower, double& x_upper)
{
  double tol, m;
  int ac_equal = 0;


  double a = m_a;
  double b = m_b;
  double c = m_c;
  double fa = m_fa;
  double fb = m_fb;
  double fc = m_fc;
  double d = m_d;
  double e = m_e;
  
  if ((fb < 0 && fc < 0) || (fb > 0 && fc > 0)) {
    ac_equal = 1;
    c = a;
    fc = fa;
    d = b - a;
    e = b - a;
  }


  if (std::abs (fc) < std::abs (fb)) {
    ac_equal = 1;
    a = b;
    b = c;
    c = a;
    fa = fb;
    fb = fc;
    fc = fa;
  }
  double dbleps=2.2204460492503131e-16;
  tol = 0.5 * dbleps * std::abs (b);
  m = 0.5 * (c - b);

  if (fb == 0) {
    root = b;
    x_lower = b;
    x_upper = b;
    
    return true;
  }

  if (std::abs (m) <= tol) {
    root = b;
    if (b < c) {
      x_lower = b;
      x_upper = c;
    } else {
      x_lower = c;
      x_upper = b;
    }

    return true;
  }

  if (std::abs (e) < tol || std::abs (fa) <= std::abs (fb)) {
    d = m;            /* use bisection */
    e = m;
  } else {
    double p, q, r;   /* use inverse cubic interpolation */
    double s = fb / fa;
    if (ac_equal) {
      p = 2 * m * s;
      q = 1 - s;
    } else {
      q = fa / fc;
      r = fb / fc;
      p = s * (2 * m * q * (q - r) - (b - a) * (r - 1));
      q = (q - 1) * (r - 1) * (s - 1);
    }
      
    if (p > 0) {
      q = -q;
    } else {
      p = -p;
    }
      
    if (2 * p < std::min(3 * m * q - std::abs (tol * q), std::abs (e * q))) {
      e = d;
      d = p / q;
    } else {
      /* interpolation failed, fall back to bisection */
      d = m;
      e = m;
    }
  }

  a = b;
  fa = fb;
  
  if (std::abs (d) > tol) {
    b += d;
  } else {
    b += (m > 0 ? +tol : -tol);
  }

  fb = eval(b);
  if (!std::isfinite(fb)) { 
    std::cerr << "function value is not finite" << std::endl;
  }

  
  m_a = a ;
  m_b = b ;
  m_c = c ;
  m_d = d ;
  m_e = e ;
  m_fa = fa ;
  m_fb = fb ;
  m_fc = fc ;

  root = b;
  
  if ((fb < 0 && fc < 0) || (fb > 0 && fc > 0)) {
    c = a;
  }

  if (b < c) {
    x_lower = b;
    x_upper = c;
  } else {
    x_lower = c;
    x_upper = b;
  }

  return true;
}


void GsimRootSolver::initBrent(double xLow,double xHigh)
{
  m_xLowBound = xLow;
  m_xHighBound = xHigh;
  m_xRoot = 0.5 * (xLow + xHigh);  /* initial estimate */
  
  double fLow = eval(xLow);
  double fHigh = eval(xHigh);

  m_a = xLow;
  m_fa = fLow;

  m_b = xHigh;
  m_fb = fHigh;

  m_c = xHigh;
  m_fc = fHigh;

  m_d = xHigh - xLow ;
  m_e = xHigh - xLow ;

  if ((fLow < 0.0 && fHigh < 0.0) || (fLow > 0.0 && fHigh > 0.0)) {
    std::cerr << "endpoints do not straddle y=0" << std::endl;
  }
}
  
void GsimRootSolver::solveBrent(double xLow,double xHigh)
{
  initBrent(xLow,xHigh);

  m_iterations = 0;
  bool notConverged=true;
  do 
    {
      m_iterations++ ;
      iterateBrent (m_xRoot,m_xLowBound,m_xHighBound);
      //double r = m_xRoot;
      double a = m_xLowBound;
      double b = m_xHighBound;
      notConverged = test_interval (a,b,
				    m_epsilonAbsolute,
				    m_espilonRelative);
    }
  while (notConverged && m_iterations < m_maxIterations);
  
  m_errorStatus=0;
  if(m_iterations >= m_maxIterations) {
    m_errorStatus=1;
  } else {
    if(notConverged) {
      m_errorStatus=2;
    }
  }
  m_xError=(m_xHighBound-m_xLowBound)/2.;

  
  return;
}


bool GsimRootSolver::test_interval (double x_lower, double x_upper, double epsabs, double epsrel)
{
  const double abs_lower = std::abs(x_lower) ;
  const double abs_upper = std::abs(x_upper) ;

  if (epsrel < 0.0) {
    std::cerr << "relative tolerance is negative" << std::endl;
    return true;
  }
  
  if (epsabs < 0.0) {
    std::cerr << "absolute tolerance is negative" << std::endl;
    return true;
  }

  if (x_lower > x_upper) {
    std::cerr << "lower bound larger than upper bound" << std::endl;
    return true;
  }


  double min_abs=0.;
  if ((x_lower > 0.0 && x_upper > 0.0) || (x_lower < 0.0 && x_upper < 0.0)) {
    min_abs = std::min(abs_lower, abs_upper) ;
  } else {
    min_abs = 0;
  }

  double tolerance = epsabs + epsrel * min_abs  ;
  
  if (std::abs(x_upper - x_lower) < tolerance)
    return false;
  
  return true;
}


///////////////////////////////////////////////////////////////////////
//  GSL
// void GsimRootSolver::solveGSL(double xLow,double xHigh)
// {

//   const gsl_root_fsolver_type* fsolver=
//     gsl_root_fsolver_brent;
//     //gsl_root_fsolver_bisection;
//     //gsl_root_fsolver_falsepos;

//   gsl_root_fsolver* s = gsl_root_fsolver_alloc(fsolver);

//   double x_lower = xLow;
//   double x_upper = xHigh;

//   gsl_root_fsolver_set(s, &m_gslfunc, x_lower, x_upper) ;

//   int status=0;
//   m_iterations = 0;
//   do 
//     {
//       m_iterations++ ;
//       gsl_root_fsolver_iterate (s);
//       double r = gsl_root_fsolver_root(s);
//       double a = gsl_root_fsolver_x_lower(s);
//       double b = gsl_root_fsolver_x_upper(s);
//       status = gsl_root_test_interval (a,b,
// 				       m_epsilonAbsolute,
// 				       m_espilonRelative);
//     }
//   while (status == GSL_CONTINUE && m_iterations < m_maxIterations);

//   m_errorStatus=0;
//   if(m_iterations >= m_maxIterations) {
//     m_errorStatus=1;
//   } else {
//     if(status!=GSL_SUCCESS) {
//       m_errorStatus=2;
//     }
//   }

//   m_xLowBound=gsl_root_fsolver_x_lower(s);
//   m_xHighBound=gsl_root_fsolver_x_upper(s);
//   m_xError=(m_xHighBound-m_xLowBound)/2.;
//   m_xRoot=gsl_root_fsolver_root(s);

//   gsl_root_fsolver_free(s);
//   return;
// }
///////////////////////////////////////////////////////////////////////
