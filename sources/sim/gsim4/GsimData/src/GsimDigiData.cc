/**
 *  $Id: GsimDigiData.cc,v 1.13 2006/12/09 21:33:44 nanjo Exp $
 *  $Log: GsimDigiData.cc,v $
 *  Revision 1.13  2006/12/09 21:33:44  nanjo
 *  briefHistory is corrected.
 *
 *  Revision 1.12  2006/12/09 00:42:57  nanjo
 *  dump.
 *
 *  Revision 1.11  2006/12/07 13:49:47  nanjo
 *  Remove extra ;
 *
 *  Revision 1.10  2006/12/06 18:38:38  nanjo
 *  CVS variables.
 *
 */
#include "GsimData/GsimDigiData.h"
#include <iostream>
#include <iomanip>

#if !defined(__CINT__)
ClassImp(GsimDigiData)
#endif

GsimDigiData::GsimDigiData() : TObject()
{
  initializeDataValues();
}


GsimDigiData::~GsimDigiData()
{
  ;
}

void GsimDigiData::Clear(Option_t* )
{
  initializeDataValues();
}
  
void GsimDigiData::initializeDataValues()
{
  detID=0;
  modID=0;
  energy=0;
  time=-999;
  thisID=0;
  track=0;
  status=0;
  mtimeEntry=0;
  mtimeSize=0;
}


void GsimDigiData::dump(int imode)
{
  std::cout << std::setw(4) << thisID;
  std::cout << std::setw(4) << modID;
  std::cout << std::setw(6) << track;
  std::cout << std::setw(6)
	    << std::setprecision(2)
	    << energy; 
  std::cout << std::setw(6)
	    << std::setprecision(2)
	    << time;
  std::cout << std::setw(4) << mtimeSize;
  if(imode!=0)
    std::cout << std::endl;
}
