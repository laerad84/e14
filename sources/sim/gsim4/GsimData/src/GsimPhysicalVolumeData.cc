/**
 *  $Id: GsimPhysicalVolumeData.cc,v 1.3 2006/12/07 13:49:47 nanjo Exp $
 *  $Log: GsimPhysicalVolumeData.cc,v $
 *  Revision 1.3  2006/12/07 13:49:47  nanjo
 *  Remove extra ;
 *
 *  Revision 1.2  2006/12/06 18:38:38  nanjo
 *  CVS variables.
 *
 */
#include "GsimData/GsimPhysicalVolumeData.h"

#if !defined(__CINT__)
ClassImp(GsimPhysicalVolumeData)
#endif

GsimPhysicalVolumeData::GsimPhysicalVolumeData() : TObject()
{
  pvName="";
  pvCopyNo=-1;
  detID=-1;
  detFullName="";
  detBriefName="";
  
  sdFlag=0;
  sdName="";
  sdID=-1;
  sdNch=0;
  sdChID=new Int_t[16380];
  sdClID=new Int_t[16380];
}

GsimPhysicalVolumeData::GsimPhysicalVolumeData(const GsimPhysicalVolumeData& right) :
  TObject(right),
  pvName(right.pvName),
  pvCopyNo(-1),
  detID(right.detID),
  detFullName(right.detFullName),
  detBriefName(right.detBriefName),
  sdFlag(right.sdFlag),
  sdName(right.sdName),
  sdID(right.sdID),
  sdNch(right.sdNch)
{
  for(int k=0;k<16380;k++) {
    sdChID[k]=right.sdChID[k];
    sdClID[k]=right.sdClID[k];
  }
}



GsimPhysicalVolumeData::~GsimPhysicalVolumeData()
{
  delete [] sdChID;
  delete [] sdClID;
}


void GsimPhysicalVolumeData::Clear(Option_t* )
{
  ;
}

void GsimPhysicalVolumeData::initializeDataValues()
{
  ;
}


GsimPhysicalVolumeData& GsimPhysicalVolumeData::operator=(const  GsimPhysicalVolumeData& right)
{
  if (this != &right) {
    pvName=right.pvName;
    pvCopyNo=right.pvCopyNo;
    detID=right.detID;
    detFullName=right.detFullName;
    detBriefName=right.detBriefName;
    sdFlag=right.sdFlag;
    sdName=right.sdName;
    sdID=right.sdID;
    sdNch=right.sdNch;
    for(int k=0;k<16380;k++) {
      sdChID[k]=right.sdChID[k];
      sdClID[k]=right.sdClID[k];
    }
  }
  return *this;
}

