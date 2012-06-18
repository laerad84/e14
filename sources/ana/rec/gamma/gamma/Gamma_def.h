
#ifndef GAMMA_H_INCLUDED
#define GAMMA_H_INCLUDED

#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include "GsimPersistency/GsimMessage.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "cluster/Cluster.h"
#include "E14Fsim/E14FsimFunction.h"

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
  void  setSigmaPos( const CLHEP::Hep3Vector& pos ){m_sigmaPos = pos;}
  void  setSigmaPos(double x,double y, double z ){ setSigmaPos(CLHEP::Hep3Vector( x,y,z ));}
  void  setSigmaE(double sigma ){ m_sigmaE = sigma; }
  void  setEnergy( double energy ){ m_energy = energy;}
  void  setTime( double time ){m_time = time;}
  void  setPos( const CLHEP::Hep3Vector& pos ){m_pos = pos;}
  void  setPos( double x, double y, double z ) { setPos(CLHEP::Hep3Vector( x,y,z )); }
  void  setP3( const CLHEP::Hep3Vector& p3 ) { m_p3 = p3; }
  void  setP3( double px, double py, double pz ) { setP3(CLHEP::Hep3Vector( px,py,pz )); }
  void  setChisq( double c2 ) { m_chisq = c2; }
  void  setId( int id ) { m_id = id; }
  void  setStatus( int status ) { m_status = status; }

  void setCluster( Cluster const &cluster){m_cluster = cluster;}
  // friend functions
  friend std::ostream& operator<<( std::ostream& out, const Gamma& clus );

  double  calcSigmaE();
  CLHEP::Hep3Vector calcSigmaPos();

private:
  int            m_id;
  CLHEP::Hep3Vector     m_pos;
  CLHEP::Hep3Vector     m_p3;
  double         m_energy;
  double         m_time;

  double         m_sigmaE;
  CLHEP::Hep3Vector     m_sigmaPos;
  double         m_chisq;
  int            m_status;

  Cluster       m_cluster;
  
  // method
  
  int     compare( const Gamma& ) const;

private:
  static std::list<Cluster> s_clusList;
};


#endif // GAMMA_H_INCLUDED

