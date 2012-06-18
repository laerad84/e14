/**
 *  @file   ShapeChi2.h
 *  @brief  shape chi2 calculator
 *  This class provides a method to calculate shape chi2. 
 *
 *  @author Kazufumi Sato <sato@champ.hep.sci.osaka-u.ac.jp>
 *  @date   2011.9.23
 *  $Id: ShapeChi2.h,v 1.0 2011/09/23 12:38 sato Exp $
 *  $Log: ShapeChi2.h,v $
 */



#ifndef ShapeChi2_h_
#define ShapeChi2_h_

#include <cstdlib>
#include "GsimPersistency/GsimMessage.h"
#include "gamma/Gamma.h"

class ShapeChi2
{
 public:
  ShapeChi2();
  ~ShapeChi2();
  void shapeChi2(Gamma& gamma);

 private:

  void loadMap();
  void rotAndMirror(double &phi,int const &csize,double *const *csipos);
  void selectMap(double const &ene,double const &theta,
		 double const &phi,int *index,double *percentage);
  int calcRatioOfRowE(int const &csize,double const *csiedep,
		      double *const *csipos,double const *csiwidth,
		      int *index,double const *percentage);
  double compare(int const &csize,double const *csiedep,
		 double const *const *csipos,double const *csiwidth,
		 int const *index,double const *percentage,
		 int const &mode);
  
  static int const s_numEvalue=11;
  static int const s_numTvalue=11;
  static int const s_numPvalue=7;
  static int const s_numCtrBin=6;
  static int const s_mapSize=10;
  static int const s_mapCtr=4;
  int *mapNum[3*s_numEvalue*s_numTvalue*s_numPvalue*s_numCtrBin*s_numCtrBin];
  float *mapMean[3*s_numEvalue*s_numTvalue*s_numPvalue*s_numCtrBin*s_numCtrBin];
  float *mapSquare[3*s_numEvalue*s_numTvalue*s_numPvalue*s_numCtrBin*s_numCtrBin];
  //float* distRowE[2][2][11][11][7]={{{{{0}}}}};
  float* distRowE[2][2][s_numEvalue][s_numTvalue][s_numPvalue];
  
  int getMapAddress(int const &forl,int const &e,int const &t,
		    int const &p,int const &x,int const &y) const;
  ////  
};

#endif
