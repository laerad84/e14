/**
 * @file CsiMap.h
 * @brief CsiMap
 * This Class provides functions to get the position and width of CsI crystal.
 *
 * CsI configuration are read from $E14_TOP_DIR/share/ngana/csi_dettree.root
 *
 *  usage : CsiMap::getCsiMap()->getXXX(xxx);
 *
 * @author Kazufumi Sato < sato@champ.hep.sci.osaka-u.ac.jp >
 * @date Oct. 27 16:54 JST 2011
 * $Id: CsiMap.h,v 1.1 2011/10/27 16:54 sato $
 * $Log: CsiMap.h,v $
 */

#ifndef CsiMap_h
#define CsiMap_h
//includes
#include <string>
#include <iostream>
#include <cstdlib>
#include "GsimPersistency/GsimMessage.h"



class CsiMap
{
 public:
  static CsiMap* getCsiMap();
  ~CsiMap();
  void getXYW(int const &ID,double &x,double &y,double &w) const;
  void getXYWarray(int const &nDigi,int const *ID,double *x,double *y,double *w) const;
  int getN() const { return m_nCsI;}
  double getX(int const &ID) const;
  double getY(int const &ID) const;
  double getZSurface(int const &ID) const;
  double getW(int const &ID) const;
  void readCsiConfig(std::string mapFile="");  
 private:
  CsiMap();
  static CsiMap* s_CsiMap;
  static int const s_arrSize = 5000;
  int m_nCsI;
  double m_Xarray[s_arrSize];
  double m_Yarray[s_arrSize];
  double m_Zarray[s_arrSize];
  double m_Warray[s_arrSize];
};



#endif //CsiMap_h
