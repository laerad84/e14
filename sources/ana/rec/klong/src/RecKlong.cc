// -*- C++ -*-
//
// RecKlong.cc
// Klong reconstruction 
//
// Author:  Ken Sakashita
// Created: Thu Nov  4 22:28:20 JST 2004
//
// $Id: RecKlong.cc,v 1.4 2006/04/24 12:43:05 toshi Exp $
//
// $Log: RecKlong.cc,v $
// Revision 1.4  2006/04/24 12:43:05  toshi
// g5anafuse function added by Gabe
//
// Revision 1.3  2005/10/03 05:30:51  toshi
// add function: recK2pi0g
//
// Revision 1.2  2005/09/11 22:50:07  kensh
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
// Revision 1.1  2004/11/04 13:26:35  kensh
// Klong class. Faster than recKL.
//
//
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "gamma/Gamma.h"
#include "pi0/Pi0.h"
#include "rec2g/Rec2g.h"
#include "klong/RecKlong.h"

//Perdue 20051006
#define DEBUG_G5FUSE_LEVEL 0


/////
RecKlong::RecKlong( int debugLevel )
  : m_debugLevel( debugLevel )
{
  //

}

/////
RecKlong::~RecKlong()
{
  //
}

/////
std::vector<Klong> 
RecKlong::recK2pi0( const std::list<Gamma>& glist, int vtxflag, double pi0sig2cut )
{
  //
  Rec2g rec2g; // pi0 reconstruction 
  std::list<Pi0> pi0list = rec2g.recPi0withConstM( glist );

  return( recK2pi0( pi0list,vtxflag,pi0sig2cut ) );
}

/////
std::vector<Klong> 
RecKlong::recK2pi0( const std::list<Pi0>& pi0list, int vtxflag, double pi0sig2cut )
{
  //
  std::vector<Klong> k2pi0;

  for( std::list<Pi0>::const_iterator p1=pi0list.begin();
       p1!=pi0list.end(); p1++ ) {
    for( std::list<Pi0>::const_iterator p2=p1;
	 p2!=pi0list.end(); p2++ ) {
      if ( p2->g1().id() == p1->g1().id() || p2->g1().id() == p1->g2().id() ||
	   p2->g2().id() == p1->g1().id() || p2->g2().id() == p1->g2().id()  ){
	continue; // same gamma.
      }
      else {
	if( p1->status() == 1 &&
	    p2->status() == 1 &&
	    p1->recZsig2() <= pi0sig2cut &&
	    p2->recZsig2() <= pi0sig2cut ) {
	  
	  Klong klong;
	  klong.setVertexFlag( vtxflag );
	  klong.setPi0( (*p1),(*p2) );
	  klong.setSortByChisqZ();
	  
	  k2pi0.push_back( klong );
	}
      }
    }
  } 

  // sort by ChisqZ
  sort( k2pi0.begin(), k2pi0.end() );

  // set id
  int id = 0;
  for(std::vector<Klong>::iterator i=k2pi0.begin();
      i!=k2pi0.end(); i++) {
    i->setId( id );

    id++;
  }

  return( k2pi0 );
}


/////
std::vector<Klong> 
RecKlong::recK3pi0( const std::list<Gamma>& glist, int vtxflag, double pi0sig2cut )
{
  //
  Rec2g rec2g; // pi0 reconstruction 
  std::list<Pi0> pi0list = rec2g.recPi0withConstM( glist );

  return( recK3pi0( pi0list,vtxflag,pi0sig2cut ) );
}

/////
std::vector<Klong> 
RecKlong::recK3pi0( const std::list<Pi0>& pi0list, int vtxflag, double pi0sig2cut )
{
  //
  std::vector<Klong> k3pi0;

  for( std::list<Pi0>::const_iterator p1=pi0list.begin();
       p1!=pi0list.end(); p1++ ) {
    for( std::list<Pi0>::const_iterator p2=p1;
	 p2!=pi0list.end(); p2++ ) {
      if ( p2->g1().id() == p1->g1().id() || p2->g1().id() == p1->g2().id() ||
	   p2->g2().id() == p1->g1().id() || p2->g2().id() == p1->g2().id()  ){
	continue; // same gamma.
      }
      else{
	for( std::list<Pi0>::const_iterator p3=p2;
	     p3!=pi0list.end(); p3++ ){
	  if ( p3->g1().id() == p2->g1().id() || p3->g1().id() == p2->g2().id() ||
	       p3->g2().id() == p2->g1().id() || p3->g2().id() == p2->g2().id() ||
	       p3->g1().id() == p1->g1().id() || p3->g1().id() == p1->g2().id() ||
	       p3->g2().id() == p1->g1().id() || p3->g2().id() == p1->g2().id()  ){
	    continue; // same gamma.
	  }
	  else {
	    if( p1->status() == 1 &&
		p2->status() == 1 &&
		p3->status() == 1 &&
		p1->recZsig2() <= pi0sig2cut &&
		p2->recZsig2() <= pi0sig2cut &&
		p3->recZsig2() <= pi0sig2cut ) {
	      
	      Klong klong;
	      klong.setVertexFlag( vtxflag );
	      klong.setPi0( (*p1),(*p2),(*p3) );
	      klong.setSortByChisqZ();
	      
	      k3pi0.push_back( klong );
	    }
	  }
	}
      }
    }
  } 

  // sort by ChisqZ
  sort( k3pi0.begin(), k3pi0.end() );

  // set id
  int id = 0;
  for(std::vector<Klong>::iterator i=k3pi0.begin();
      i!=k3pi0.end(); i++) {
    i->setId( id );

    id++;
  }

  return( k3pi0 );
}


//Perdue 20050926
/////
std::vector<Klong> 
RecKlong::recK2pi0g( const std::list<Gamma>& glist, int vtxflag, double pi0sig2cut )
{


  //
  RecKlong recklong_inner;

  // k2pi0g - the "final" Kaon
  // kl[j]  - the jth Kaon, where j <-> glist4[j] and identifies the 
  // gamma removed from glist.
  //
  std::vector<Klong> k2pi0g;
  std::vector<Klong> kl[5];

  // 
  // Set up new gamma lists.
  // -------------------------
  // 4-gamma lists indexed by ij where i = # of gammas in list
  // and j = id # of gamma removed from glist.  These lists are 
  // used to make two pi0 reconstructions to find the vertex.
  std::list<Gamma> glist4[5];

  // Create 5 copies of glist4 -> glist4j.
  // Remove different gammas each time, label acoording to
  // missing gamma: 
  //    1, 2, 3, 4 - 40
  //    2, 3, 4, 0 - 41
  //    3, 4, 0, 1 - 42
  //    4, 0, 1, 2 - 43
  //    0, 1, 2, 3 - 44
  // For each copy, do a "2pi0" reconstruction.
  // Also store gamma (x,y,z) and E for future work on the spare gamma.
  double gx[5], gy[5], gz[5], gE[5];

  for ( unsigned int i = 0; i < 5; i++ ) {
    glist4[i] = glist;
    std::list<Gamma>::iterator oddgammaout = glist4[i].begin();
    for ( unsigned int j = 0; j < i; j++ ) {
      oddgammaout++;
    }
    gx[i] = oddgammaout->x();
    gy[i] = oddgammaout->y();
    gz[i] = oddgammaout->z();
    gE[i] = oddgammaout->e();
    glist4[i].erase( oddgammaout );
  }

  // Here, the four gammas from each set are used to try to 
  // reconstruct a pair of pi0's.  Begin with a fixed vertex for 
  // the 2pi0 (x,y) => update to include the 5th gamma after pairing.
  for ( unsigned int i = 0; i < 5; i++) {
    kl[i] = recklong_inner.recK2pi0( glist4[i], 
				     VERTEX_FIX_XYZERO, 
				     pi0sig2cut );
    if (kl[i].size() > 0) { 
      for (std::vector<Klong>::iterator k = kl[i].begin();
	   k != kl[i].end();
	   k++) {
	k->setUserFlag( i );
	k2pi0g.push_back( (*k) );
      }
    }
  }

  // sort by ChisqZ
  sort( k2pi0g.begin(), k2pi0g.end() );

  // set id & update klong variables (account for 5th gamma)
  //****
  int id = 0;
  for(std::vector<Klong>::iterator i = k2pi0g.begin();
      i != k2pi0g.end(); 
      i++) {
    // Id
    i->setId( id );
    id++;

    // Construct Kaon for COE Vertex
    // 
    if ( vtxflag == VERTEX_COE_SCALE ) { 

      // reconstruct Vtx - Special Update Vars for 5 gamma events.
      double Etot = 0.0;
      double avrX = 0.0;
      double avrY = 0.0;
      double avrZ = i->vz();
      double sig2tot = 0.0;
      for( unsigned int gnum = 0; gnum < 5; gnum++ ) {
	// center of energy
	avrX += gx[gnum]*gE[gnum];
	avrY += gy[gnum]*gE[gnum];
	
	// Etotal
	Etot += gE[gnum];
      }
      avrX = avrX/Etot;
      avrY = avrY/Etot;

      double TargetZ      = -1180.;
      double CalorimatorZ =   610.;
      double scaleFactor  = ( avrZ - TargetZ )/( CalorimatorZ - TargetZ );
  
      avrX = avrX*scaleFactor;
      avrY = avrY*scaleFactor;

      // update Pi0 vars      
      for( std::vector<Pi0>::iterator p=i->pi0().begin();
	   p!=i->pi0().end(); p++ ) {
	// 
	p->setVtx( avrX, avrY, avrZ );  // set Pi0 vertex
	p->updateVars();                // and update Pi0 vars
      }  

      // klong vars
      CLHEP::HepLorentzVector p_kl = CLHEP::HepLorentzVector( 0.,0.,0.,0. );
      CLHEP::Hep3Vector gspare_p3  = CLHEP::Hep3Vector( gx[i->userFlag()] - i->vx(), 
					  gy[i->userFlag()] - i->vy(), 
					  gz[i->userFlag()] - i->vz()
					  ); 
      gspare_p3.setMag( gE[i->userFlag()] );
      CLHEP::HepLorentzVector p_gspare( gspare_p3, gE[i->userFlag()] );
      p_kl += p_gspare;
      for( std::vector<Pi0>::iterator p=i->pi0().begin();
	   p!=i->pi0().end(); p++ ) {
	// 4 momentum
	CLHEP::HepLorentzVector p_pi0( p->p3(), p->e() );
	p_kl += p_pi0;
      }      
      i->setVtx( avrX,avrY,avrZ );
      i->setP3( p_kl.vect() );
      i->setEnergy( p_kl.e() );
      i->setMass( p_kl.m() );

    } else { // Construct Kaon for Fixed Vertex

    // klong vars
      CLHEP::Hep3Vector gspare_p3 = CLHEP::Hep3Vector( gx[i->userFlag()] - i->vx(), 
					 gy[i->userFlag()] - i->vy(), 
					 gz[i->userFlag()] - i->vz()
					 ); 
      gspare_p3.setMag( gE[i->userFlag()] );
      CLHEP::HepLorentzVector p_gspare( gspare_p3, gE[i->userFlag()] );
      CLHEP::HepLorentzVector p_kl = CLHEP::HepLorentzVector( i->p3(), i->e() );
      p_kl += p_gspare;
      i->setP3( p_kl.vect() );
      i->setEnergy( p_kl.e() );
      i->setMass( p_kl.m() );

    }
  }    

#if DEBUG_LEVEL > 0 
  {
    unsigned int i = 0;
    for(std::vector<Klong>::iterator k = k2pi0g.begin();
	k != k2pi0g.end(); 
	k++) {
      std::cout<<"id = "<<k2pi0g[i].id()<<std::endl;
      std::cout<<"userFlag = "<<k2pi0g[i].userFlag()<<std::endl;
      for( std::vector<Pi0>::const_iterator p=k2pi0g[i].pi0().begin();
	   p!=k2pi0g[i].pi0().end(); p++ ) {
	std::cout<<"pion id = "<<p->id()<<std::endl;
	std::cout<<"  g1 id = "<<p->g1().id()<<std::endl;
	std::cout<<"  g2 id = "<<p->g2().id()<<std::endl;
      }
      i++;
      std::cout<<std::endl;
    }
  }
#endif

  return( k2pi0g );
}


//Perdue 20060401
/////
std::vector<Klong> 
RecKlong::recK5gfuse( const std::list<Gamma>& glist, 
		      int vtxflag, 
		      double pi0sig2cut )
{
#if DEBUG_G5FUSE_LEVEL > 0
  std::cout<<"Entering recK5gfuse...\n";
#endif
  // Reconstruction object internal to recK5gfuse
  RecKlong recklong_inner;

  // k5g - the "final" Kaon
  // kl[k]  - the jth Kaon, where k <-> glist6[i,j] and identifies the 
  // "split" gamma and the way the energy was shared.
  //
  std::vector<Klong> k5g;
  std::vector<Klong> kl[25];

  // 
  // Set up new gamma lists.
  // -------------------------
  // "6"-gamma lists indexed by ij where i = identifies the "split" gamma 
  // and j identifies how the energy was shared.  These lists are used to 
  // make 3pi0 reconstructions.
  std::list<Gamma> glist6[5][5];

  // Create 5 copies of glist6 -> glist6i.
  // Split different gammas each time, & label acoording to
  // the split gamma id: 
  //    1, 2, 3, 4 - 40 => split 0
  //    2, 3, 4, 0 - 41 => split 1
  //    3, 4, 0, 1 - 42 => split 2
  //    4, 0, 1, 2 - 43 => split 3
  //    0, 1, 2, 3 - 44 => split 4
  // Do 5 different energy splittings (10%,90%), (20%,80%), (30%,70%), 
  // (40%,60%), and (50%,50%) => second index (j)
  // For each copy, do a "3pi0" reconstruction.

  for ( unsigned int i = 0; i < 5; i++ ) {
    for ( unsigned int j = 0; j < 5; j++ ) { 
      glist6[i][j] = glist;
      std::list<Gamma>::iterator splitgamma = glist6[i][j].begin();
      for ( unsigned int k = 0; k < i; k++ ) {
	splitgamma++;
      }
      Gamma gamma_new1, gamma_new2;
      //      gamma_new1 = GammaCopy( *splitgamma );
      //      gamma_new2 = GammaCopy( *splitgamma );
      gamma_new1 = *splitgamma ;
      gamma_new2 = *splitgamma ;
      glist6[i][j].erase( splitgamma );
      gamma_new1.setId( 5 );  
      double factor = ( (float) (j + 1) )/10.0;
      double tempe1 = factor * gamma_new1.e();
      double tempe2 = (1 - factor) * gamma_new2.e();
      gamma_new1.setEnergy( tempe1 );
      gamma_new2.setEnergy( tempe2 );
      glist6[i][j].push_back( gamma_new1 );
      glist6[i][j].push_back( gamma_new2 );
      glist6[i][j].sort();  // Sort by Energy
      {
	int k = 0;
	for ( std::list<Gamma>::iterator p = glist6[i][j].begin();
	      p != glist6[i][j].end(); 
	      p++ ) {
	  p->setId( k );   // Re-index
	  k++;
	}    
      }
    } 
  } // End gamma splitting & energy modification

#if DEBUG_G5FUSE_LEVEL > 0
  for ( unsigned int i = 0; i < 5; i++ ) {
    for ( unsigned int j = 0; j < 5; j++ ) { 
      std::cout<<"glist6["<<i<<"]["<<j<<"].e()'s: ";
      for ( std::list<Gamma>::iterator p = glist6[i][j].begin();
      	    p != glist6[i][j].end(); 
      	    p++ ) {
      	std::cout<<" "<<p->e();
      }    
      std::cout<<std::endl;
    } 
  } 
#endif

  // Here, the six gammas from each set are used to try to 
  // reconstruct 3pi0s.  
  for ( unsigned int i = 0; i < 5; i++) {
    for ( unsigned int j = 0; j < 5; j++) {
      unsigned int index = 5*i + j;
      kl[index] = 
	recklong_inner.recK3pi0( glist6[i][j], vtxflag, pi0sig2cut );
#if DEBUG_G5FUSE_LEVEL > 0
      std::cout<<std::endl;
      std::cout<<"glist6["<<i<<"]["<<j<<"].e()'s: ";
      for ( std::list<Gamma>::iterator p = glist6[i][j].begin();
	    p != glist6[i][j].end(); 
	    p++ ) {
	std::cout<<" "<<p->e();
      }    
      std::cout<<std::endl;
      std::cout<<"kl["<<index<<" = "<<i<<"]["<<j<<"].size() = "
	       <<kl[index].size()<<std::endl;
#endif
      if (kl[index].size() > 0) { 
#if DEBUG_G5FUSE_LEVEL > 0
	unsigned int count = 0;
#endif
	for (std::vector<Klong>::iterator kaon = kl[index].begin();
	     kaon != kl[index].end();
	     kaon++) {
	  kaon->setUserFlag( i );
#if DEBUG_G5FUSE_LEVEL > 0
	  std::cout<<"kl["<<index<<"],#"<<count<<".chisqZ() = "
		   <<kaon->chisqZ()<<std::endl;
	  count++;
#endif
	  k5g.push_back( (*kaon) );
	}
      }
    }
  } // End 3pi0 Recons
#if DEBUG_G5FUSE_LEVEL > 0
  std::cout<<"k5g.size() = "<<k5g.size()<<std::endl;
#endif

  // sort by ChisqZ
  sort( k5g.begin(), k5g.end() );

#if DEBUG_G5FUSE_LEVEL > 0
  if (k5g.size() > 0) { 
      unsigned int j = 0;
      for (std::vector<Klong>::iterator k = k5g.begin();
	   k != k5g.end();
	   k++) {
	std::cout<<"k5g#"<<j<<".chisqZ() = "<<k->chisqZ()<<std::endl;
	j++;
      }
    }
  std::cout<<"Exiting recK5gfuse...\n\n";
#endif

  return( k5g );
}
