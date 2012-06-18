#include <iostream>
#include <list>
#include <math.h>
#include "E14Fsim/E14FsimVeto.h"

/////
E14FsimVeto::E14FsimVeto()
  : m_detid( 0 ),
    m_pos( TVector3( 0,0,0 ) ),
    m_mome(  TVector3( 0,0,0 ) ),
    m_energy( 0.0 ),
    m_time( 0.0 ),
    m_ineffi(0.0)    
{
  ;
}


/////
E14FsimVeto::~E14FsimVeto()
{
  ;
}


//////
void
E14FsimVeto::setEnergy( double energy )
{
  //
  m_energy = energy;
}
//////
void
E14FsimVeto::setTime( double time )
{
  //
  m_time = time;

  //
}
/////

bool
E14FsimVeto::operator<( const E14FsimVeto& clus ) const
{
  if( compare( clus ) < 0 ) {
    return( true );
  }
  return( false );

}

/////
bool
E14FsimVeto::operator==( const E14FsimVeto& clus ) const
{
  if( compare( clus ) == 0 ) {
    return( true );
  }
  return( false );

}

/////
std::ostream& operator<<( std::ostream& out, const E14FsimVeto& clus )
{
  //
  out << "E14FsimVeto::dump : " << std::endl
      << " detid  = " << clus.m_detid     << std::endl
      << " e      = " << clus.m_energy   << std::endl
      << " x      = " << clus.m_pos.x()  << std::endl
      << " y      = " << clus.m_pos.y()  << std::endl
      << " z      = " << clus.m_pos.z()  << std::endl
      << " px     = " << clus.m_mome.x()   << std::endl
      << " py     = " << clus.m_mome.y()   << std::endl
      << " pz     = " << clus.m_mome.z()   << std::endl;
  return( out );
}

/////
int
E14FsimVeto::compare( const E14FsimVeto& clus ) const
{
  if( m_energy < clus.m_energy ) {
    return( 1 );
  }
  else if( m_energy > clus.m_energy ) {
    return( -1 );
  }

  return( 0 ); // same
}
