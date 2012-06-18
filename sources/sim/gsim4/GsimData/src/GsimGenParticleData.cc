/**
 *  $Id: GsimGenParticleData.cc,v 1.5 2006/12/07 23:22:20 nanjo Exp $ 
 *  $Log: GsimGenParticleData.cc,v $
 *  Revision 1.5  2006/12/07 23:22:20  nanjo
 *  dump is added.
 *
 *  Revision 1.4  2006/12/07 13:49:47  nanjo
 *  Remove extra ;
 *
 *  Revision 1.3  2006/12/06 18:38:38  nanjo
 *  CVS variables.
 *
 */
#include "GsimData/GsimGenParticleData.h"

#if !defined(__CINT__)
ClassImp(GsimGenParticleData)
#endif

const int GsimGenParticleData::s_arraySize=50000;

GsimGenParticleData::GsimGenParticleData() : TObject()
{
  className="GsimGenParticleData";
  name="";
  briefTracks = new TClonesArray("GsimTrackData",s_arraySize);
  version=1;
}


GsimGenParticleData::~GsimGenParticleData()
{
  delete briefTracks;
}


void GsimGenParticleData::Clear(Option_t* )
{
  briefTracks->Clear("C");
}

void GsimGenParticleData::initializeDataValues()
{
  briefTracks->Clear("C");
}

void GsimGenParticleData::dump()
{
  TClonesArray* ar = briefTracks;
  int n=ar->GetEntriesFast();
  GsimTrackData* td=0;

  std::list<GsimTrackData*> tdp;
  for(int k=0;k<n;k++) {
    td = (GsimTrackData*)ar->UncheckedAt(k);
    tdp.push_back(td);
  }


  std::list<int> state;
  scanParent(-1,tdp,state);
}

void GsimGenParticleData::scanParent(int iParent,
				     std::list<GsimTrackData*>& tdp,
				     std::list<int>& state)
{
  state.push_back(1);
  for(std::list<GsimTrackData*>::iterator it=tdp.begin();
      it!=tdp.end();it++) {
    int next=0;
    if( (*it)->mother==iParent ) {
      std::list<GsimTrackData*>::iterator itt=it;
      itt++;
      for(;itt!=tdp.end();itt++) {
	if( (*itt)->mother==iParent ) {
	  next=1;
	}
      }

      if(next==0) {
	state.pop_back();
	state.push_back(0);
      }

      std::list<int> st=state;
      st.pop_front();
      (*it)->dump(st);
      
      if(next==0) {
	state.pop_back();
	state.push_back(-1);
      }
      
      scanParent( (*it)->track,tdp,state);
    }
    if(next==-1) break;
  }
  state.pop_back();
}
