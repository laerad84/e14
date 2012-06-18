// -*- C++ -*-
//
// Pi0.h
// pi0 container class 
//
// Author:  Ken Sakashita
// Created: Sat May 29 16:38:46 JST 2004
//
// $Id: Pi0.h,v 1.2 2005/02/06 16:57:55 kensh Exp $
//
// $Log: Pi0.h,v $
// Revision 1.2  2005/02/06 16:57:55  kensh
// Fix a minor bugs in setVtx() definition.
//
// Revision 1.1  2004/05/29 08:37:36  kensh
// Pi0 class.
//
//
//

#ifndef PI0_H_INCLUDED
#define PI0_H_INCLUDED

#include <list>
#include "CLHEP/Vector/ThreeVector.h"
#include "gamma/Gamma.h"

//
class Pi0 {
public:
  // constructor
  Pi0();

  // destructor
  ~Pi0();

  // operator
  bool    operator<( const Pi0& ) const;
  bool    operator==( const Pi0& ) const;

  // extractor
  int                      id()     const { return m_id; }
  const CLHEP::Hep3Vector&        v()      const { return m_v; }
  CLHEP::Hep3Vector&              v()            { return m_v; }
  const CLHEP::Hep3Vector&        p3()     const { return m_p3; }
  CLHEP::Hep3Vector&              p3()           { return m_p3; }
  double                   vx()     const { return m_v.x(); }
  double                   vy()     const { return m_v.y(); }
  double                   vz()     const { return m_v.z(); }
  double                   e()      const { return m_energy; }
  double                   m()      const { return m_mass; }
  int                      status() const { return m_status; }

  double                   recZ()   const { return m_recZ; }
  double                   recZsig2() const { return m_recZsig2; }

  const Gamma&             g1()     const { return m_g1; }
  Gamma&                   g1()           { return m_g1; }
  const Gamma&             g2()     const { return m_g2; }
  Gamma&                   g2()           { return m_g2; }
  

  // method
  void  setId( int id ) { m_id = id; }

  void  setEnergy( double energy ) { m_energy = energy; }
  void  setMass( double mass ) { m_mass = mass; }
  void  setVtx( const CLHEP::Hep3Vector& v ) { m_v = v; }
  void  setVtx( double x, double y, double z ) { m_v = CLHEP::Hep3Vector( x,y,z ); }
  void  setP3( const CLHEP::Hep3Vector& p3 ) { m_p3 = p3; }
  void  setP3( double px, double py, double pz ) { m_p3 = CLHEP::Hep3Vector( px,py,pz ); }
  
  void  setGamma( const Gamma& g1, const Gamma& g2 ) { m_g1 = g1; m_g2 = g2; }
  void  setRecZ( double recZ) { m_recZ = recZ; }
  void  setRecZsig2( double recZsig2 ) { m_recZsig2 = recZsig2; }

  void  setStatus( int status ) { m_status = status; }

  void  updateVars();

  // friend functions
  friend std::ostream& operator<<( std::ostream& out, const Pi0& pi0 );

private:
  int            m_id;
  CLHEP::Hep3Vector     m_v;
  CLHEP::Hep3Vector     m_p3;
  double         m_energy;
  double         m_mass;

  double         m_recZ;
  double         m_recZsig2;

  int            m_status;

  Gamma          m_g1;
  Gamma          m_g2;

  // method
  int     compare( const Pi0& pi0 ) const;


};

//
#endif // PI0_H_INCLUDED

