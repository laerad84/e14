// -*- C++ -*-
//
// Klong.h
// klong container class 
//
// Author:  Ken Sakashita
// Created: Thu Nov  4 22:28:20 JST 2004
//
// $Id: Klong.h,v 1.5 2011/10/31 16:30 sato Exp $
//
// $Log: Klong.h,v $
// Revision 1.5  2011/10/31 16:30  sato
// add methods setChisqZ and setDeltaZ
// change target and calorimeter zposition to agree with GsimE14Spectrum.
//
// Revision 1.4  2005/10/03 05:28:23  toshi
// add userFlag functions and related variables
//
// Revision 1.3  2005/09/11 22:49:52  kensh
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
// Revision 1.2  2004/11/18 16:14:16  kensh
// pi0() should return std::vector<Pi0>&
// (same return type for pi0() const)
//
// Revision 1.1  2004/11/04 13:26:09  kensh
// Klong class. Faster than recKL.
//
//
//

#include <iostream>
#include <vector>
#include <math.h>
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "pi0/Pi0.h"
#include "klong/Klong.h"


/////
Klong::Klong()
  : m_id( 0 ),
    m_v( CLHEP::Hep3Vector( 0,0,0 ) ),
    m_p3( CLHEP::Hep3Vector( 0,0,0 ) ),
    m_energy( 0.0 ),
    m_mass( 0.0 ),
    m_deltaZ( 0.0 ),
    m_chisqZ( 0.0 ),
    m_status( 0 ),
    m_sortFlag( SORT_BY_CHISQZ ),
    m_vertexFlag( VERTEX_COE_SCALE ),
    m_userFlag( 0 )   //Perdue - 20050926
{
  //
  //std::cout << "Klong::Klong()" << std::endl;
}


/////
Klong::~Klong()
{
  //
  //std::cout << "Klong::~Klong()" << std::endl;

}

/////
bool
Klong::operator<( const Klong& klong ) const 
{
  if( compare( klong ) < 0 ) {
    return( true );
  }
  return( false );

}

/////
bool
Klong::operator==( const Klong& klong ) const
{
  if( compare( klong ) == 0 ) {
    return( true );
  }
  return( false );

}

/////
void 
Klong::updateVars()
{
  //
  if( m_pi0.empty() )
    return;


  // reconstruct Vtx
  double Etot = 0.0;
  double avrX = 0.0;
  double avrY = 0.0;
  double avrZ = 0.0;
  double sig2tot = 0.0;
  for( std::vector<Pi0>::const_iterator p=m_pi0.begin();
       p!=m_pi0.end(); p++ ) {
    // weighted average
    avrZ    += p->recZ()/p->recZsig2();
    sig2tot += 1./p->recZsig2();
    
    // center of energy
    avrX += p->g1().e()*p->g1().x() + p->g2().e()*p->g2().x();
    avrY += p->g1().e()*p->g1().y() + p->g2().e()*p->g2().y();
    
    // Etotal
    Etot += p->g1().e() + p->g2().e();
  }
  avrX = avrX/Etot;
  avrY = avrY/Etot;
  avrZ = avrZ/sig2tot;

  //  double TargetZ      = -1180.;
  //  double CalorimatorZ =   610.;
  // changed by Sato (2011. Nov. 4) 
  double TargetZ      = -21000.; //mm
  double CalorimatorZ =   6148.; //mm
  
  double scaleFactor  = (avrZ-TargetZ)/(CalorimatorZ-TargetZ);
  
  avrX = avrX*scaleFactor;
  avrY = avrY*scaleFactor;

  // update Pi0 vars
  for( std::vector<Pi0>::iterator p=m_pi0.begin();
       p!=m_pi0.end(); p++ ) {
    // 
    p->setVtx( avrX,avrY,avrZ );  // set Pi0 vertex
    p->updateVars();              // and update Pi0 vars
  }


  // set klong variables
  m_chisqZ = 0.;
  CLHEP::HepLorentzVector p_kl = CLHEP::HepLorentzVector( 0.,0.,0.,0. );
  const Pi0& pi0 = m_pi0.front();
  double    maxZ = pi0.recZ();
  double    minZ = pi0.recZ();
  for( std::vector<Pi0>::iterator p=m_pi0.begin();
       p!=m_pi0.end(); p++ ) {
    // 4 momentum
    CLHEP::HepLorentzVector p_pi0( p->p3(), p->e() );
    p_kl += p_pi0;

    // z chi square
    m_chisqZ += (p->recZ()-avrZ)*(p->recZ()-avrZ)/p->recZsig2();
    
    //
    if( maxZ < p->recZ() )
      maxZ = p->recZ();
    //
    if( minZ > p->recZ() )
      minZ = p->recZ();
  }

  m_deltaZ = maxZ - minZ;
  m_v      = CLHEP::Hep3Vector( avrX,avrY,avrZ );
  m_p3     = p_kl.vect();
  m_energy = p_kl.e();
  m_mass   = p_kl.m();

}

/////
void 
Klong::updateVars_fixvtx()
{
  //
  if( m_pi0.empty() )
    return;

  // reconstruct Vtx(0,0,avrZ)
  double avrZ = 0.0;
  double sig2tot = 0.0;
  for( std::vector<Pi0>::const_iterator p=m_pi0.begin();
       p!=m_pi0.end(); p++ ) {
    // weighted average
    avrZ    += p->recZ()/p->recZsig2();
    sig2tot += 1./p->recZsig2();
  }
  avrZ = avrZ/sig2tot;

  // update Pi0 vars
  for( std::vector<Pi0>::iterator p=m_pi0.begin();
       p!=m_pi0.end(); p++ ) {
    // 
    p->setVtx( 0.0, 0.0, avrZ );  // set Pi0 vertex
    p->updateVars();              // and update Pi0 vars
  }


  // set klong variables
  m_chisqZ = 0.;
  CLHEP::HepLorentzVector p_kl = CLHEP::HepLorentzVector( 0.,0.,0.,0. );
  const Pi0& pi0 = m_pi0.front();
  double    maxZ = pi0.recZ();
  double    minZ = pi0.recZ();
  for( std::vector<Pi0>::iterator p=m_pi0.begin();
       p!=m_pi0.end(); p++ ) {
    // 4 momentum
    CLHEP::HepLorentzVector p_pi0( p->p3(), p->e() );
    p_kl += p_pi0;

    // z chi square
    m_chisqZ += (p->recZ()-avrZ)*(p->recZ()-avrZ)/p->recZsig2();
    
    //
    if( maxZ < p->recZ() )
      maxZ = p->recZ();
    //
    if( minZ > p->recZ() )
      minZ = p->recZ();
  }

  m_deltaZ = maxZ - minZ;
  m_v      = CLHEP::Hep3Vector( 0.0, 0.0, avrZ );
  m_p3     = p_kl.vect();
  m_energy = p_kl.e();
  m_mass   = p_kl.m();

}

////
int 
Klong::setPi0( const Pi0& pi0a, const Pi0& pi0b, const Pi0& pi0c )
{
  m_pi0.push_back( pi0a );
  m_pi0.push_back( pi0b );
  m_pi0.push_back( pi0c );

  if( m_vertexFlag == VERTEX_FIX_XYZERO ) 
    updateVars_fixvtx();
  else
    updateVars();

  return( m_pi0.size() );
}

////
int 
Klong::setPi0( const Pi0& pi0a, const Pi0& pi0b )
{
  m_pi0.push_back( pi0a );
  m_pi0.push_back( pi0b );

  if( m_vertexFlag == VERTEX_FIX_XYZERO ) 
    updateVars_fixvtx();
  else
    updateVars();

  return( m_pi0.size() );
}

/////
std::ostream& operator<<( std::ostream& out, const Klong& klong )
{
  //
  out << "Klong::dump :       " << std::endl
      << "               ID = " << klong.m_id          << std::endl
      << "              Vtx = " << klong.m_v.x()
      << ", "                   << klong.m_v.y()
      << ", "                   << klong.m_v.z()       << std::endl
      << "               P3 = " << klong.m_p3.x()
      << ", "                   << klong.m_p3.y()
      << ", "                   << klong.m_p3.z()      << std::endl
      << "           E,M,PP = " << klong.m_energy
      << ", "                   << klong.m_mass
      << ", "                   << klong.m_p3.mag()    << std::endl
      << "           deltaZ = " << klong.m_deltaZ      << std::endl
      << "           chisqZ = " << klong.m_chisqZ      << std::endl
      << "         sortFlag = " << klong.m_sortFlag    << std::endl
      << "       vertexFlag = " << klong.m_vertexFlag  << std::endl
      << "           status = " << klong.m_status      << std::endl
      << "             npi0 = " << klong.m_pi0.size()  << std::endl;

  for(std::vector<Pi0>::const_iterator i=klong.m_pi0.begin();
      i!=klong.m_pi0.end(); i++) {
    out << *i;
  }
  out << std::endl;

  return( out );
}

/////
int 
Klong::compare( const Klong& klong ) const
{
  //
  const double mass = 0.497672;
  double thisDeltaM = sqrt( (m_mass - mass)*(m_mass - mass) );
  double compDeltaM = sqrt( (klong.m_mass - mass)*(klong.m_mass - mass) );
  
  switch ( m_sortFlag ) {
  case SORT_BY_DZ :
    // sort by DeltaZ ( short order )
    if( m_deltaZ < klong.m_deltaZ ) {
      return( -1 );
    }
    else if( m_deltaZ > klong.m_deltaZ ) {
      return( 1 );
    }
    break;

  case SORT_BY_CHISQZ :
    // sort by ChisqZ ( small order )
    if( m_chisqZ < klong.m_chisqZ ) {
      return( -1 );
    }
    else if( m_chisqZ > klong.m_chisqZ ) {
      return( 1 );
    }
    break;

  case SORT_BY_DM :
    // sort by DeltaM ( small order )
    if( thisDeltaM < compDeltaM ) {
      return( -1 );
    }
    else if( thisDeltaM > compDeltaM ) {
      return( 1 );
    }
    break;

  default :
    // sort by E ( large order )
    if( m_energy < klong.m_energy ) {
      return( 1 );
    }
    else if( m_energy > klong.m_energy ) {
      return( -1 );
    }
    break;

  }

  return( 0 ); // same
}



