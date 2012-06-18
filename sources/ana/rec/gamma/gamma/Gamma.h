// -*- C++ -*-
//
// Gamma.h
// gamma container class 
//
// Author:  Mitsuhiro YAMAGA
// Created: Fri May  7 19:05:40 JST 2004
//
// $Id: Gamma.h,v 1.9 2011/11/24 15:42 sato Exp $
//
// $Log: Gamma.h,v $
// Revision 1.9  2011/11/24 15:42 sato
// Add new member class Cluster, and remove memvers overlapping with Cluster.
// remove some members needless for KOTO.
//
// Revision 1.8  2006/05/30 12:01:55  kensh
// Add new variables: .hub(), .pe(), .pecorr().
//
// Revision 1.7  2005/10/06 13:27:37  yamaga
// iostream needed for AIX xlC.
//
// Revision 1.6  2005/04/01 19:25:26  kensh
// Add new variable & function.
//
// Revision 1.5  2005/01/13 17:30:55  kensh
// Add new variable p3 for the mometum.
//
// Revision 1.4  2004/11/18 04:26:49  kensh
// Add several variables.
//
// Revision 1.3  2004/10/26 12:59:06  kensh
// Add new variables.
//
// Revision 1.2  2004/05/29 08:30:51  kensh
// Add useful variables.
//
// Revision 1.1  2004/05/10 15:54:42  yamaga
// New for gamma finding.
//
//

#ifndef GAMMA_H_INCLUDED
#define GAMMA_H_INCLUDED

#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include "GsimPersistency/GsimMessage.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "cluster/Cluster.h"


//
class Gamma {
public:
  // constructor
  Gamma();
  Gamma(Cluster const &cluster);

  // destructor
  ~Gamma();

  // operator
  bool    operator<( const Gamma& ) const;
  bool    operator==( const Gamma& ) const;

  // extractor
  int                      id()     const { return m_id; }
  const CLHEP::Hep3Vector&        pos()    const { return m_pos; }
  CLHEP::Hep3Vector&              pos()          { return m_pos; }
  const CLHEP::Hep3Vector&        p3()     const { return m_p3; }
  CLHEP::Hep3Vector&              p3()           { return m_p3; }
  double                   x()      const { return m_pos.x(); }
  double                   y()      const { return m_pos.y(); }
  double                   z()      const { return m_pos.z(); }
  double                   e()      const { return m_energy; }
  double                   t()      const { return m_time; }
  int                      status() const { return m_status; }

  double                   sigmaE() const { return m_sigmaE; }
  const CLHEP::Hep3Vector& sigmaPos()    const { return m_sigmaPos; }
  double                   sigmaX()      const { return m_sigmaPos.x(); }
  double                   sigmaY()      const { return m_sigmaPos.y(); }
  double                   sigmaZ()      const { return m_sigmaPos.z(); }
  double                   chisq()  const { return m_chisq;  }
  double                   ann()  const { return m_ann;  }

  Cluster const &          cluster()const { return m_cluster;}
  const CLHEP::Hep3Vector& coepos() const { return m_cluster.pos();}
  double                   coex()   const { return m_cluster.x();}
  double                   coey()   const { return m_cluster.y();}
  double                   coez()   const { return m_cluster.z();}
  double                   edep()   const { return m_cluster.e();}
  double                   rms()   const { return m_cluster.rms();}

  const std::vector<int>&    clusterIdVec() const { return m_cluster.clusterIdVec(); }
  const std::vector<double>& clusterEVec() const { return m_cluster.clusterEVec(); }
  const std::vector<double>& clusterTimeVec() const { return m_cluster.clusterTimeVec(); }

  // method
  void  setEnergy( double energy ){m_energy = energy;}
  void  setTime( double time ){m_time = time;}
  void  setPos( const CLHEP::Hep3Vector& pos ){m_pos = pos;}
  void  setPos( double x, double y, double z ) { setPos(CLHEP::Hep3Vector( x,y,z )); }
  void  setP3( const CLHEP::Hep3Vector& p3 ) { m_p3 = p3; }
  void  setP3( double px, double py, double pz ) { setP3(CLHEP::Hep3Vector( px,py,pz )); }
  void  setChisq( double c2 ) { m_chisq = c2; }
  void  setAnn( double ann ) { m_ann = ann; }
  void  setSigmaE( double sigmaE ) { m_sigmaE = sigmaE; }
  void  setSigmaX( double sigmaX ) { m_sigmaPos.setX(sigmaX); }
  void  setSigmaY( double sigmaY ) { m_sigmaPos.setY(sigmaY); } 
  void  setSigmaZ( double sigmaZ ) { m_sigmaPos.setZ(sigmaZ); }
  void  setSigmaPos( const CLHEP::Hep3Vector& pos ){m_sigmaPos = pos;}
  void  setSigmaPos(double x,double y, double z ){ setSigmaPos(CLHEP::Hep3Vector( x,y,z ));}
  void  setId( int id ) { m_id = id; }
  void  setStatus( int status ) { m_status = status; }
  void  setCluster( Cluster const &cluster ) { m_cluster = cluster; }

  // friend functions
  friend std::ostream& operator<<( std::ostream& out, const Gamma& clus );

private:
  int            m_id;
  CLHEP::Hep3Vector     m_pos;
  CLHEP::Hep3Vector     m_p3;
  double         m_energy;
  double         m_time;

  double         m_sigmaE;
  CLHEP::Hep3Vector     m_sigmaPos;
  double         m_chisq;
  double         m_ann;
  int            m_status;
  Cluster        m_cluster;

  // method
  int     compare( const Gamma& ) const;

  //for MC
public:
  int                      mcThisID() const { return m_mcThisID; }
  int                      mcParentID() const { return m_mcParentID; }
  void  setMcThisID( int id ) { m_mcThisID=id; }
  void  setMcParentID( int id ) { m_mcParentID=id; }
private:
  int            m_mcThisID;
  int            m_mcParentID;
};

//
#endif // GAMMA_H_INCLUDED

