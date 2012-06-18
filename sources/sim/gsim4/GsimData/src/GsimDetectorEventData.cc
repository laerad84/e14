/**
 *  $Id: GsimDetectorEventData.cc,v 1.11 2006/12/09 00:42:57 nanjo Exp $
 *  $Log: GsimDetectorEventData.cc,v $
 *  Revision 1.11  2006/12/09 00:42:57  nanjo
 *  dump.
 *
 *  Revision 1.10  2006/12/08 04:09:21  nanjo
 *  Remove extra ;
 *
 *  Revision 1.9  2006/12/04 15:46:56  nanjo
 *  Variable names are changed for GsimData.
 *
 *  Revision 1.8  2006/10/16 02:38:01  nanjo
 *  hardwareID is replaced by clusterID.
 *
 *  Revision 1.7  2006/10/11 03:35:33  nanjo
 *  GsimTriggerData is removed.
 *
 *  Revision 1.6  2006/10/11 01:51:30  nanjo
 *  GsimTriggerData is added.
 *
 *  Revision 1.5  2006/08/11 08:48:52  nanjo
 *  Clear is added for some GsimDatas
 *
 *  Revision 1.4  2006/08/08 11:15:04  nanjo
 *  GsimTimeData is introduced and TRefArray is used.
 *
 *  Revision 1.3  2006/06/14 14:58:28  nanjo
 *  The size of TClonesArray is defined by a private static const member
 *
 *  Revision 1.2  2006/06/14 03:35:54  nanjo
 *  GsimDigiData is added and size of TClonesArray is expanded.
 *
 *  Revision 1.1  2006/01/26 06:11:19  nanjo
 *  Detector and data classes are added.
 *
 */
#include "GsimData/GsimDetectorEventData.h"
#include <iostream>
#include <iomanip>

#if !defined(__CINT__)
ClassImp(GsimDetectorEventData)
#endif

const int GsimDetectorEventData::s_arraySize=50000;

GsimDetectorEventData::GsimDetectorEventData()  : TObject()
{
  className="GsimDetectorEventData";
  name="";
  status=0;
  nHit=0;
  nDigi=0;
  nTrig=0;
  totalEnergy=0;
  firstHitTime=-999;
  lastHitTime=-999;
  hits = new TClonesArray("GsimDetectorHitData",s_arraySize);
  mtime = new TClonesArray("GsimTimeData",s_arraySize);
  digi = new TClonesArray("GsimDigiData",s_arraySize);
  trig = new TClonesArray("GsimTimeData",s_arraySize);

  t1=0;
  t2=0;
}


GsimDetectorEventData::~GsimDetectorEventData()
{
  delete hits;
  delete digi;
  delete mtime;
  delete trig;
}

void GsimDetectorEventData::Clear(Option_t*)
{
  status=0;
  nHit=0;
  nDigi=0;
  nTrig=0;
  totalEnergy=0;
  firstHitTime=-999;
  lastHitTime=-999;
  hits->Clear("C");
  digi->Clear("C");
  mtime->Clear("C");
  trig->Clear("C");
}

void GsimDetectorEventData::initializeDataValues()
{
  status=0;
  nHit=0;
  nDigi=0;
  nTrig=0;
  totalEnergy=0;
  firstHitTime=-999;
  lastHitTime=-999;
  hits->Clear("C");
  digi->Clear("C");
  mtime->Clear("C");
  trig->Clear("C");
}


void GsimDetectorEventData::clearHitData()
{
  hits->Clear("C");
}

void GsimDetectorEventData::dumpHits()
{
  int n=hits->GetEntriesFast();
  GsimDetectorHitData* hd=0;
  for(int k=0;k<n;k++) {
    hd = (GsimDetectorHitData*)hits->UncheckedAt(k);
    hd->dump();
  }
}

void GsimDetectorEventData::dumpDigi()
{
  int n=digi->GetEntriesFast();
  GsimDigiData* dd=0;
  GsimTimeData* td=0;
  for(int k=0;k<n;k++) {
    dd = (GsimDigiData*)digi->UncheckedAt(k);
    dd->dump(0);
    int ib=dd->mtimeEntry;
    int ie=ib+dd->mtimeSize;
    for(int l=ib;l<ie;l++) {
      td = (GsimTimeData*)mtime->UncheckedAt(l);
      td->dump(0);
    }
    std::cout << std::endl;
  }
}
