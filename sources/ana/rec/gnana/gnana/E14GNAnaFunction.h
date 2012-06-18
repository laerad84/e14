/**
 *  @file   E14GNAnaFunction.h
 *  @brief  Functions for g2ana,g4ana,g6ana
 * This class provides functions for cuts, corrections, etc.
 *
 *  @author Kazufumi Sato <sato@champ.hep.sci.osaka-u.ac.jp>
 *  @date   2011.9.23
 *  $Id: E14GNAnaFunction.h,v 1.0 2011/09/23 12:38 sato Exp $
 *  $Log: E14GNAnaFunction.h,v $
 */



#ifndef E14GNAnaFunction_h_
#define E14GNAnaFunction_h_

#include <cstdlib>
#include "GsimPersistency/GsimMessage.h"
#include "gamma/Gamma.h"
#include "pi0/Pi0.h"
#include "klong/Klong.h"
#include "gamma/ShapeChi2.h"
//#include "gamma/ShapeANN.h"

class E14GNAnaFunction
{
  E14GNAnaFunction();
 public:
  static E14GNAnaFunction* getFunction();
  ~E14GNAnaFunction();
  
  // correction for angle dependency of gamma position
  void correctEnergy(Gamma& gamma);  
  void correctPosition(Gamma& gamma);
  void shapeChi2(Gamma& gamma);
  //  void shapeANN(Gamma& gamma,int CsiNumber = -1,int *CsiId = 0,double *CsiEne = 0);

public:
  void correctPosition(Pi0 &pi);
  void correctPosition(Klong &kl);

  void correctEnergy(Pi0 &pi);
  void correctEnergy(Klong &kl);

  void shapeChi2(Pi0 &pi);
  void shapeChi2(Klong &kl);


 private:
  static E14GNAnaFunction* s_function;

  //// for correctEnergy()
  double showerLeakage(double thre,double E,double ws,double wl);  

};

#endif
