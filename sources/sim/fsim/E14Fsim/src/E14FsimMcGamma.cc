#include "E14Fsim/E14FsimMcGamma.h"

E14FsimMcGamma::E14FsimMcGamma()
  : m_gammaID( -999 ),
    m_parentID( -999 ),
    m_pos( TVector3(-999,-999,-999) ),
    m_mome( TVector3(-999,-999,-999) ),
    m_energy( -999 ),
    m_time( -999 )
{
  ;
}

E14FsimMcGamma::~E14FsimMcGamma()
{
  
}
