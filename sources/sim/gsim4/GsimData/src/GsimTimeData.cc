/**
 *  $Id: GsimTimeData.cc,v 1.8 2006/12/09 00:42:57 nanjo Exp $
 *  $Log: GsimTimeData.cc,v $
 *  Revision 1.8  2006/12/09 00:42:57  nanjo
 *  dump.
 *
 *  Revision 1.7  2006/12/07 13:49:47  nanjo
 *  Remove extra ;
 *
 *  Revision 1.6  2006/12/06 18:38:38  nanjo
 *  CVS variables.
 *
 */
#include "GsimData/GsimTimeData.h"
#include <iostream>
#include <iomanip>

#if !defined(__CINT__)
ClassImp(GsimTimeData)
#endif

GsimTimeData::GsimTimeData() : TObject()
{
  initializeDataValues();
}


GsimTimeData::~GsimTimeData()
{
  ;
}

void GsimTimeData::Clear(Option_t*)
{
  initializeDataValues();
}

void GsimTimeData::initializeDataValues()
{
  modID=0;
  energy=0;
  time=-999;
}


void GsimTimeData::dump(int imode)
{
  std::cout << " (";
  std::cout << std::setw(6)
	    << std::setprecision(2)
	    << energy;
  std::cout << ",";
  std::cout << std::setw(6)
	    << std::setprecision(2)
	    << time;
  std::cout << ")";
  if(imode!=0)
    std::cout << std::endl;
}
