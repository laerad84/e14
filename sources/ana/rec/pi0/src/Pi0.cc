// -*- C++ -*-
//
// Pi0.cc
// pi0 container class 
//
// Author:  Ken Sakashita
// Created: Sat May 29 16:38:46 JST 2004
//
// $Id: Pi0.cc,v 1.2 2005/01/13 17:32:40 kensh Exp $
//
// $Log: Pi0.cc,v $
// Revision 1.2  2005/01/13 17:32:40  kensh
// Replace (Gamma).dir() to (Gamma).p3() in the pi0 momentum calculation.
//
// Revision 1.1  2004/05/29 08:37:57  kensh
// Pi0 class.
//
//
//

#include <iostream>
#include <list>
#include <math.h>
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "gamma/Gamma.h"
#include "pi0/Pi0.h"


/////
Pi0::Pi0()
  : m_id( 0 ),
    m_v( CLHEP::Hep3Vector( 0,0,0 ) ),
    m_p3( CLHEP::Hep3Vector( 0,0,0 ) ),
    m_energy( 0.0 ),
    m_mass( 0.0 ),
    m_recZ( 0.0 ),
    m_recZsig2( 0.0 ),
    m_status( 0 )
{
  //
  //std::cout << "Pi0::Pi0()" << std::endl;

}


/////
Pi0::~Pi0()
{
  //
  //std::cout << "Pi0::~Pi0()" << std::endl;

}

/////
bool
Pi0::operator<( const Pi0& pi0 ) const 
{
  if( compare( pi0 ) < 0 ) {
    return( true );
  }
  return( false );

}

/////
bool
Pi0::operator==( const Pi0& pi0 ) const
{
  if( compare( pi0 ) == 0 ) {
    return( true );
  }
  return( false );

}

/////
void 
Pi0::updateVars()
{
  //
  // set 2 gamma momentum
  CLHEP::Hep3Vector g1_p3  =  CLHEP::Hep3Vector( m_g1.pos().x() - m_v.x(),
						 m_g1.pos().y() - m_v.y(),
						 m_g1.pos().z() - m_v.z() );
  g1_p3.setMag( m_g1.e() );

  CLHEP::Hep3Vector g2_p3  =  CLHEP::Hep3Vector( m_g2.pos().x() - m_v.x(),
						 m_g2.pos().y() - m_v.y(),
						 m_g2.pos().z() - m_v.z() );
  g2_p3.setMag( m_g2.e() );

  m_g1.setP3( g1_p3 );
  m_g2.setP3( g2_p3 );

  // set pi0 momentum & mass
  m_energy = m_g1.e()  + m_g2.e();
  m_p3     = m_g1.p3() + m_g2.p3();
  
  CLHEP::HepLorentzVector p_pi0( m_p3, m_energy );
  m_mass = p_pi0.m();

}


/////
std::ostream& operator<<( std::ostream& out, const Pi0& pi0 )
{
  //
  out << "Pi0::dump :         " << std::endl
      << "               ID = " << pi0.m_id          << std::endl
      << "              Vtx = " << pi0.m_v.x()
      << ", "                   << pi0.m_v.y()
      << ", "                   << pi0.m_v.z()       << std::endl
      << "               P3 = " << pi0.m_p3.x()
      << ", "                   << pi0.m_p3.y()
      << ", "                   << pi0.m_p3.z()      << std::endl
      << "           E,M,PP = " << pi0.m_energy
      << ", "                   << pi0.m_mass
      << ", "                   << pi0.m_p3.mag()    << std::endl
      << "          g1.id() = " << pi0.m_g1.id()
      << "          g2.id() = " << pi0.m_g2.id()
      << "             recZ = " << pi0.m_recZ        << std::endl
      << "         recZsig2 = " << pi0.m_recZsig2    << std::endl
      << "           status = " << pi0.m_status      << std::endl;

  return( out );
}

/////
int 
Pi0::compare( const Pi0& pi0 ) const
{
  if( m_energy < pi0.m_energy ) {
    return( 1 );
  }
  else if( m_energy > pi0.m_energy ) {
    return( -1 );
  }

  return( 0 ); // same
}



