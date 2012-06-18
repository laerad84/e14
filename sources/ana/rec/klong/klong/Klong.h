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

#ifndef KLONG_H_INCLUDED
#define KLONG_H_INCLUDED

#include <vector>
#include "CLHEP/Vector/ThreeVector.h"
#include "pi0/Pi0.h"

// sort Flags
enum {
  SORT_BY_E=1, SORT_BY_DZ, SORT_BY_CHISQZ, SORT_BY_DM
};

// vertex Flags
enum {
  VERTEX_COE_SCALE=1, VERTEX_FIX_XYZERO
};


//
class Klong {
public:
  // constructor
  Klong();

  // destructor
  ~Klong();

  // operator
  bool    operator<( const Klong& ) const;
  bool    operator==( const Klong& ) const;

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

  double                   deltaZ() const { return m_deltaZ; }
  double                   chisqZ() const { return m_chisqZ; }

  const std::vector<Pi0>&  pi0()    const { return m_pi0; }
  std::vector<Pi0>&        pi0()          { return m_pi0; }

  int                      sortFlag()   const { return m_sortFlag; }
  int                      vertexFlag() const { return m_vertexFlag; }

  int                      userFlag() const { return m_userFlag; }//Perdue
  
  // method
  void  setId( int id ) { m_id = id; }

  void  setEnergy( double energy ) { m_energy = energy; }
  void  setMass( double mass ) { m_mass = mass; }
  void  setVtx( const CLHEP::Hep3Vector& v );
  void  setVtx( double x, double y, double z ) { m_v = CLHEP::Hep3Vector( x,y,z ); }
  void  setP3( const CLHEP::Hep3Vector& p3 ) { m_p3 = p3; }
  void  setP3( double px, double py, double pz ) { m_p3 = CLHEP::Hep3Vector( px,py,pz ); }
  
  int   setPi0( const Pi0& pi0a, const Pi0& pi0b, const Pi0& pi0c );
  int   setPi0( const Pi0& pi0a, const Pi0& pi0b );

  void  setDeltaZ(double  deltaZ){m_deltaZ = deltaZ;}
  void  setChisqZ(double  chisqZ){m_chisqZ = chisqZ;}

  void  setStatus( int status ) { m_status = status; }

  void  setSortFlag( int flag ) { m_sortFlag = flag; }
  void  setSortByDeltaZ() { m_sortFlag = SORT_BY_DZ; }
  void  setSortByChisqZ() { m_sortFlag = SORT_BY_CHISQZ; }
  void  setSortByDeltaM() { m_sortFlag = SORT_BY_DM; }

  void  setVertexFlag( int flag ) { m_vertexFlag = flag; }
  void  setVertexCoeScale() { m_vertexFlag = VERTEX_COE_SCALE; }
  void  setVertexFixXYzero() { m_vertexFlag = VERTEX_FIX_XYZERO; }

  void  updateVars();
  void  updateVars_fixvtx();

  void  setUserFlag( int flag ) { m_userFlag = flag; } //Perdue 20050926

  // friend functions
  friend std::ostream& operator<<( std::ostream& out, const Klong& Klong );

private:
  int            m_id;
  CLHEP::Hep3Vector     m_v;
  CLHEP::Hep3Vector     m_p3;
  double         m_energy;
  double         m_mass;

  double         m_deltaZ;
  double         m_chisqZ;

  int            m_status;
  int            m_sortFlag;
  int            m_vertexFlag;

  int            m_userFlag; // Perdue 20050926

  std::vector<Pi0> m_pi0;

  // method
  int     compare( const Klong& Klong ) const;


};

//
#endif // KLONG_H_INCLUDED

