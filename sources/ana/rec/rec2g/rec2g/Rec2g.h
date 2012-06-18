// -*- C++ -*-
//
// rec2g.h
// 2 gamma reconstruction
//
// Author:  Ken Sakashita
// Created: Sat May 29 16:38:46 JST 2004
//
// $Id: Rec2g.h,v 1.1 2004/05/29 08:35:09 kensh Exp $
//
// $Log: Rec2g.h,v $
// Revision 1.1  2004/05/29 08:35:09  kensh
// Add Rec2g.
//
//
//

#ifndef RECPI0_H_INCLUDED
#define RECPI0_H_INCLUDED

#include <list>
#include "CLHEP/Vector/ThreeVector.h"
#include "gamma/Gamma.h"
#include "pi0/Pi0.h"

#define REC2G_M_PI0 0.1349764*1000   // GeV to MeV
#define REC2G_M_KL  0.497672*1000    // GeV to MeV

//
class Rec2g {
public:
  // constructor
  Rec2g( int debugLevel=0 );

  // destructor
  ~Rec2g();

  // operator

  // extractor
  std::list<Pi0>  recPi0withConstM( std::list<Gamma> glist, const double Mpi0=REC2G_M_PI0 );
  
  // method
  void recVtxWithConstM( const Gamma& g1, const Gamma& g2, double Mass,
			 double* recZ, double* recZsig2 );

private:
  // data member
  int                        m_debugLevel;

  // method

};

//
#endif // RECPI0_H_INCLUDED



