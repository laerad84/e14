/**
 *  $Id: GsimEventData.cc,v 1.8 2006/12/07 13:49:47 nanjo Exp $ 
 *  $Log: GsimEventData.cc,v $
 *  Revision 1.8  2006/12/07 13:49:47  nanjo
 *  Remove extra ;
 *
 *  Revision 1.7  2006/12/06 18:38:38  nanjo
 *  CVS variables.
 *
 */
#include "GsimData/GsimEventData.h"

#if !defined(__CINT__)
ClassImp(GsimEventData)
#endif

GsimEventData::GsimEventData()
{
  className="GsimEventData";
  name="";

  expMC=0;          // exp=1,MC=2
  run_number=0;
  spill_number=0;
  event_number=0;
  trigger=TRIG_ONSPILL;
  time_stamp=0;
  status=0;
  //thisID=0;
  version=2;
}


GsimEventData::~GsimEventData()
{
  ;
}


void GsimEventData::Clear(Option_t* )
{
  ;
}

void GsimEventData::initializeDataValues()
{
  ;
}

