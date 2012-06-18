/**
 *  $Id: GsimProcessData.cc,v 1.3 2006/12/07 13:49:47 nanjo Exp $
 *  $Log: GsimProcessData.cc,v $
 *  Revision 1.3  2006/12/07 13:49:47  nanjo
 *  Remove extra ;
 *
 *  Revision 1.2  2006/12/06 18:38:38  nanjo
 *  CVS variables.
 *
 */
#include "GsimData/GsimProcessData.h"

#if !defined(__CINT__)
ClassImp(GsimProcessData)
#endif

GsimProcessData::GsimProcessData() : TObject()
{
  processID=0;
  processName="";
}

GsimProcessData::GsimProcessData(const GsimProcessData& right) :
  TObject(right),
  processID(right.processID),
  processName(right.processName)
{
  ;
}



GsimProcessData::~GsimProcessData()
{
  ;
}


void GsimProcessData::Clear(Option_t* )
{
  ;
}

void GsimProcessData::initializeDataValues()
{
  ;
}


GsimProcessData& GsimProcessData::operator=(const  GsimProcessData& right)
{
  if (this != &right) {
    processID=right.processID;
    processName=right.processName;
  }
  return *this;
}

bool GsimProcessData::operator == (const GsimProcessData& right) const
{
  return
    processID == right.processID &&
    processName == right.processName;
}

bool GsimProcessData::operator != (const GsimProcessData& right) const
{
  return !(operator==(right));
}
