// -*- C++ -*-
//
// Gamma.cc
// gamma container class 
//
// Author:  Mitsuhiro YAMAGA
// Created: Fri May  7 19:05:40 JST 2004
//
// $Id: Gamma.cc,v 1.5 2005/04/01 19:29:24 kensh Exp $
//
// $Log: Gamma.cc,v $
// Revision 1.5  2005/04/01 19:29:24  kensh
// Add new variable. (energy deposit)
//
// Revision 1.4  2005/01/13 17:31:33  kensh
// Add new variable p3 for the mometum.
//
// Revision 1.3  2004/11/18 04:26:34  kensh
// Add several veriables.
//
// Revision 1.2  2004/05/29 08:32:08  kensh
// Add useful variables.
//
// Revision 1.1  2004/05/10 15:54:42  yamaga
// New for gamma finding.
//
//

#include <iostream>
#include <list>
#include <math.h>
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "gamma/Gamma.h"

/////
Gamma::Gamma()
  : m_id( 0 ),
    m_pos( CLHEP::Hep3Vector( 0,0,0 ) ),
    m_p3(  CLHEP::Hep3Vector( 0,0,0 ) ),
    m_energy( 0.0 ),
    m_time( 0.0 ),
    m_sigmaE( 0.0 ),
    m_sigmaPos( CLHEP::Hep3Vector( 0,0,0 ) ),
    m_chisq(  0.0 ),
    m_ann(  0.0 ),
    m_status( 0 )
{
  //
  //std::cout << "Gamma::Gamma()" << std::endl;
  ;
}

Gamma::Gamma(Cluster const &cluster)
  : m_id( 0 ),
    m_p3(  CLHEP::Hep3Vector( 0,0,0 ) ),
    m_time( 0.0 ),
    m_sigmaE( 0.0 ),
    m_sigmaPos( CLHEP::Hep3Vector( 0,0,0 ) ),
    m_chisq(  0.0 ),
    m_ann(  0.0 ),
    m_status( 0 )
{
  setCluster(cluster);
  m_pos = coepos();
  m_energy = edep() ;
  m_time = cluster.t();
}


/////
Gamma::~Gamma()
{
  //
  //std::cout << "Gamma::~Gamma()" << std::endl;

}

bool
Gamma::operator<( const Gamma& gam ) const 
{
  if( compare( gam ) < 0 ) {
    return( true );
  }
  return( false );

}

/////
bool
Gamma::operator==( const Gamma& gam ) const
{
  if( compare( gam ) == 0 ) {
    return( true );
  }
  return( false );

}

/////
std::ostream& operator<<( std::ostream& out, const Gamma& gam )
{
  //
  out << "Gamma::dump : " << std::endl
      << " id       = " << gam.m_id     << std::endl
      << " status   = " << gam.m_status << std::endl
    
      << " e      = " << gam.m_energy   << std::endl
      << " x      = " << gam.m_pos.x()  << std::endl
      << " y      = " << gam.m_pos.y()  << std::endl
      << " z      = " << gam.m_pos.z()  << std::endl
      << " t      = " << gam.m_time   << std::endl
      << " px     = " << gam.m_p3.x()   << std::endl
      << " py     = " << gam.m_p3.y()   << std::endl
      << " pz     = " << gam.m_p3.z()   << std::endl
      << " sigmaE = " << gam.m_sigmaE   << std::endl 
      << " sigmaX = " << gam.m_sigmaPos.x()   << std::endl
      << " sigmaY = " << gam.m_sigmaPos.y()   << std::endl
      << " sigmaZ = " << gam.m_sigmaPos.z()   << std::endl
      << " chisq  = " << gam.m_chisq    << std::endl
      << " ann  = " << gam.m_ann    << std::endl
      << gam.m_cluster<< std::endl;
  return( out );
}

/////
int 
Gamma::compare( const Gamma& gam ) const
{
  if( m_energy < gam.m_energy ) {
    return( 1 );
  }
  else if( m_energy > gam.m_energy ) {
    return( -1 );
  }

  return( 0 ); // same
}

