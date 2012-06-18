// -*- C++ -*-
//
// RecKlong.h
// Klong reconstruction
//
// Author:  Ken Sakashita
// Created: Thu Nov  4 22:28:20 JST 2004
//
// $Id: RecKlong.h,v 1.4 2006/04/24 12:44:16 toshi Exp $
//
// $Log: RecKlong.h,v $
// Revision 1.4  2006/04/24 12:44:16  toshi
// gamma fusion routine for g5ana added by Gabe
//
// Revision 1.3  2005/10/03 05:28:54  toshi
// add function: recK2pi0g
//
// Revision 1.2  2005/09/11 22:49:52  kensh
// Add new vertex calculation method.
// In Klong container class, you can change the method by m_vertexFlag.
//
//    flag                 description
//  ---------------------------------------------------------------
//    VERTEX_COE_SCALE     x,y = scaled center-of-energy
//    VERTEX_FIX_XYZERO    x,y = fix to zero
//
// Also, you can change the method from RecKlong::recK3pi0, RecKlong::recK2pi0.
//
//  Old :
//   std::vector<Klong> kl = recklong.recK2pi0( g5list );
//
//  New :
//   std::vector<Klong> kl = recklong.recK2pi0( g5list,VERTEX_FIX_XYZERO );
//
//
// A default flag is VERTEX_COE_SCALE.
// Thus, if you call RecKlong::recK3pi0 and recK2pi0 without second argument,
// like
//
//   std::vector<Klong> kl = recklong.recK2pi0( g5list );
//
// , the vertex is calculated with the scaled-center-of-energy method.
//
// Revision 1.1  2004/11/04 13:26:09  kensh
// Klong class. Faster than recKL.
//
//

#ifndef RECKLONG_H_INCLUDED
#define RECKLONG_H_INCLUDED

#include <vector>
#include "CLHEP/Vector/ThreeVector.h"
#include "klong/Klong.h"
#include "pi0/Pi0.h"
#include "gamma/Gamma.h"

//
class RecKlong {
public:
  // constructor
  RecKlong( int debugLevel=0 );

  // destructor
  ~RecKlong();

  // operator

  // extractor
  std::vector<Klong>   recK2pi0( const std::list<Pi0>& pi0list, int vtxflag=VERTEX_COE_SCALE, double pi0sig2cut=40000. );
  std::vector<Klong>   recK2pi0( const std::list<Gamma>& glist, int vtxflag=VERTEX_COE_SCALE, double pi0sig2cut=40000. );

  std::vector<Klong>   recK3pi0( const std::list<Pi0>& pi0list, int vtxflag=VERTEX_COE_SCALE, double pi0sig2cut=40000. );
  std::vector<Klong>   recK3pi0( const std::list<Gamma>& glist, int vtxflag=VERTEX_COE_SCALE, double pi0sig2cut=40000. );

  //Perdue 20050926
  std::vector<Klong>   recK2pi0g( const std::list<Gamma>& glist, int vtxflag=VERTEX_COE_SCALE, double pi0sig2cut=40000. );

  //Perdue 20051006
  std::vector<Klong>   recK5gfuse( const std::list<Gamma>& glist, 
				   int vtxflag=VERTEX_COE_SCALE, 
				   double pi0sig2cut=40000. );
  
  // method

private:
  // data member
  int     m_debugLevel;
  int     m_vertexFlag;
  
  // method

};

//
#endif // RECKLONG_H_INCLUDED



