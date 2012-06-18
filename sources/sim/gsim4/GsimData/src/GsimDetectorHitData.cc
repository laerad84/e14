/**
 *  $Id: GsimDetectorHitData.cc,v 1.15 2006/12/09 21:33:44 nanjo Exp $
 *  $Log: GsimDetectorHitData.cc,v $
 *  Revision 1.15  2006/12/09 21:33:44  nanjo
 *  briefHistory is corrected.
 *
 *  Revision 1.14  2006/12/09 00:42:57  nanjo
 *  dump.
 *
 *  Revision 1.13  2006/12/07 13:49:47  nanjo
 *  Remove extra ;
 *
 *  Revision 1.12  2006/12/04 15:46:56  nanjo
 *  Variable names are changed for GsimData.
 *
 *  Revision 1.11  2006/11/30 20:06:22  nanjo
 *  Data are re-structured.
 *
 *  Revision 1.10  2006/08/24 22:19:01  nanjo
 *  Almost all data type is changed from double to Float_t, from int to UShort_t.
 *
 *  Revision 1.9  2006/08/11 08:48:52  nanjo
 *  Clear is added for some GsimDatas
 *
 *  Revision 1.8  2006/08/02 17:04:20  nanjo
 *  Timing information is filled at digitization.
 *
 *  Revision 1.7  2006/08/01 15:29:46  nanjo
 *  DetectorIDHistory is modified.
 *
 *  Revision 1.6  2006/06/22 12:08:32  nanjo
 *  briefDetectorIDHistory is added.
 *
 *  Revision 1.5  2006/06/14 03:34:17  nanjo
 *  Sort is enalbed (ordered by hitChannel, then by time.).
 *
 *  Revision 1.4  2006/06/04 10:14:02  nanjo
 *  mass is removed.
 *
 *  Revision 1.3  2006/06/04 10:08:34  nanjo
 *  mass is added.
 *
 *  Revision 1.2  2006/01/31 02:59:16  nanjo
 *  TString is not used for Root I/O.
 *
 *  Revision 1.1  2006/01/26 06:11:19  nanjo
 *  Detector and data classes are added.
 *
 */
#include "GsimData/GsimDetectorHitData.h"
#include <iostream>
#include <iomanip>

#if !defined(__CINT__)
ClassImp(GsimDetectorHitData)
#endif


GsimDetectorHitData::GsimDetectorHitData()  : TObject()
{
  Clear();
}


GsimDetectorHitData::~GsimDetectorHitData() {
  ;
}


void GsimDetectorHitData::Clear(Option_t*)
{
  thisID=0;
  track=0;
  stop=0;
  hitChannel=0;

  time=-999;
  edep=-999;
  pid=-999;
  r=TVector3(-999,-999,-999);
  ek=-999;
  p=TVector3(-999,-999,-999);
}

Bool_t GsimDetectorHitData::IsSortable() const
{
  return true;
}

Int_t GsimDetectorHitData::Compare(const TObject* obj) const
{
  TObject* co = const_cast<TObject*>(obj);
  GsimDetectorHitData* hd = dynamic_cast<GsimDetectorHitData*>(co);
  int compCh=hd->hitChannel;
  if(hitChannel<compCh) return -1;
  else if(hitChannel>compCh) return 1;
  else {
    double compTime=hd->time;
    if(time<compTime) return -1;
    else if(time>compTime) return 1;
    else {
      double compEne=hd->edep;
      if(edep<compEne) return -1;
      else if(edep>compEne) return 1;
      else return 0;
    }
  }
}

void GsimDetectorHitData::dump()
{
  std::cout << std::setw(4) << thisID;
  std::cout << std::setw(4) << track;
  std::cout << std::setw(5) << pid;
  
  std::cout << std::setw(6)
	    << std::setprecision(2)
	    << edep << std::endl;
  
  std::cout << std::setw(6)
	    << std::setprecision(2)
	    << r.X() << std::endl;
  
  std::cout << std::setw(6)
	    << std::setprecision(2)
	    << r.Y() << std::endl;
  
  std::cout << std::setw(6)
	    << std::setprecision(2)
	    << r.Z() << std::endl;
  
  std::cout << std::setw(6)
	    << std::setprecision(2)
	    << time << std::endl;
}
