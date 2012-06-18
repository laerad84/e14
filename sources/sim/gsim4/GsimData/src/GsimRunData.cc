/**
 *  $Id: GsimRunData.cc,v 1.2 2006/12/07 13:49:47 nanjo Exp $
 *  $Log: GsimRunData.cc,v $
 *  Revision 1.2  2006/12/07 13:49:47  nanjo
 *  Remove extra ;
 *
 *  Revision 1.1  2006/12/07 04:44:29  nanjo
 *  GsimRunData is added.
 *
 */
#include "GsimData/GsimRunData.h"

#if !defined(__CINT__)
ClassImp(GsimRunData)
#endif

GsimRunData::GsimRunData() : TObject()
{
  initializeDataValues();
}


GsimRunData::~GsimRunData()
{
  ;
}

void GsimRunData::Clear(Option_t*)
{
  initializeDataValues();
}

void GsimRunData::initializeDataValues()
{
  runNumber=0;
  runID=0;
  nEventsRequested=0;
  nEventsProcessed=0;
  nEventsStored=0;
  version=0;
}


