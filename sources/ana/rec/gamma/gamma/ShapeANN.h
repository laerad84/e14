/**
 *  @file   ShapeANN.h
 *  @brief  shape ANN calculator
 *  This is artificial nural net program to distinguish signal events and eta backgrounds.
 *  This code originaly made by Koji Shiomi. 
 *
 *  @author Kazufumi Sato <sato@champ.hep.sci.osaka-u.ac.jp>
 *  @date   2011.9.23
 *  $Id: ShapeANN.h,v 1.0 2011/09/23 12:38 sato Exp $
 *  $Log: ShapeANN.h,v $
 *  
 * 2011/12/23 sato
 * Porting the ANN code made by Shomi.
 */



#ifndef ShapeANN_h_
#define ShapeANN_h_

#include <cstdlib>
#include <map>
#include <string>
#include "GsimPersistency/GsimMessage.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include "gamma/Gamma.h"

class ShapeANN
{
 public:
  ShapeANN();
  bool shapeANN(Gamma &g,int CsiNumber=-1,int* CsiId=0,double *CsiEne=0);
  // ported from JetNet
  static void cnjfeed(int &ninp,int &nhid,
		      float* thre,float* weig,float* oin,
		      float &out);
 private:
  int readParameter(Gamma &g);
  int readParameter(Gamma &g,int CsiNumber,int *CsiId,double *CsiEne);
  void initANN(std::map<int,int>&XYtoIDmap,std::map<int,int>& IDtoXYmap,int* region);
  int m_ANNRegion;
  double m_ANNPara[27];
};
#endif //ShapeANN_h_
