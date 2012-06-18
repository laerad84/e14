// -*- C++ -*-
//
// GammaFinder.h
// gamma finding from cluster list.
// 
//
// Author:  Kazufumi Sato
// Created: Fri Aug  26 10:48:00 JST 2011
//
// $Id: GammaFinder.h,v 1.1 $
//
// $Log: GammaFinder.h,v $
//
// Revision 1.1  2011/08/26 Sato
// New for gamma finding.
//


#ifndef GAMMAFINDER_H_INCLUDED
#define GAMMAFINDER_H_INCLUDED

#include <list>
#include <vector>
#include <map>
#include "CLHEP/Vector/ThreeVector.h"
#include "gamma/Gamma.h"


class GammaFinder {
public:
  // constructor
  GammaFinder();
  
  // destructor
  ~GammaFinder();
  
  // method
  void findGamma(std::list<Cluster>const &clist,
		 std::list<Gamma>& glist, int SW = 0);

private:
  // method for gamma identifications.
  void  findGammaDefault(std::list<Cluster>const &clist,
			 std::list<Gamma>& glist);      //SW==0
  void findGammaKS(std::list<Cluster>const &clist,
		   std::list<Gamma>& glist);      //SW==1
  /// void findGammaXXXX(std::list<Cluster>const &clist,
  ///			 std::list<Gamma>& glist);      //SW==X

};

//
#endif // CLUSTERFINDER_H_INCLUDED




