#ifndef E14FsimMcGamma_h
#define E14FsimMcGamma_h

#include <iostream>
#include <list>
#include "TVector3.h"

//
class E14FsimMcGamma {
public:

  E14FsimMcGamma();
  ~E14FsimMcGamma();

  int            m_gammaID;
  int            m_parentID;
  TVector3       m_pos;
  TVector3       m_mome;
  double         m_energy;
  double         m_time;
};

//
#endif // E14FsimMcGamma_h

