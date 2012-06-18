#ifndef E14FsimVeto_h
#define E14FsimVeto_h

#include <iostream>
#include <list>
#include <TVector3.h>

//
class E14FsimVeto {
 public:
  // constructor
  E14FsimVeto();

  // destructor
  ~E14FsimVeto();

  // operator
  bool    operator<( const E14FsimVeto& ) const;
  bool    operator==( const E14FsimVeto& ) const;

  // extractor
  int                      detid()       const { return m_detid; }
  int                      pid()       const { return m_pid; }
  const TVector3&          pos()    const { return m_pos; }
  TVector3&                pos() { return m_pos; }
  const TVector3&          mome()     const { return m_mome; }
  TVector3&                mome() { return m_mome; }
  double                   x()      const { return m_pos.x(); }
  double                   y()      const { return m_pos.y(); }
  double                   z()      const { return m_pos.z(); }
  double                   e()      const { return m_energy; }
  double                   t()      const { return m_time; }
  double                  ineffi()  const { return m_ineffi; }

  // method
  void  setDetID(int detid) { m_detid = detid; }
  void  setPID(int pid) { m_pid = pid; }
  void  setEnergy( double energy );
  void  setTime( double time );
  void  setIneffi( double ineffi ) { m_ineffi = ineffi; }
  void  setPos( const TVector3& pos ){ m_pos = pos; };
  void  setPos( double x, double y, double z ) { setPos(TVector3( x,y,z )); }
  void  setMome( const TVector3& mome ) { m_mome = mome; }
  void  setMome( double px, double py, double pz ) { setMome(TVector3( px,py,pz )); }

  // friend functions
  friend std::ostream& operator<<( std::ostream& out, const E14FsimVeto& clus );

 private:
  int          m_detid;
  int          m_pid;
  TVector3     m_pos;
  TVector3     m_mome;
  double       m_energy;
  double       m_time;
  double       m_ineffi;
  
  // method
  
  int     compare( const E14FsimVeto& ) const;

};

//
#endif // E14FsimVeto_h
