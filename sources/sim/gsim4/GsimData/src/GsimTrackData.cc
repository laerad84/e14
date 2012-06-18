/**
 *  $Id: GsimTrackData.cc,v 1.11 2006/12/09 21:33:44 nanjo Exp $
 *  $Log: GsimTrackData.cc,v $
 *  Revision 1.11  2006/12/09 21:33:44  nanjo
 *  briefHistory is corrected.
 *
 *  Revision 1.10  2006/12/09 00:42:57  nanjo
 *  dump.
 *
 *  Revision 1.9  2006/12/07 23:22:20  nanjo
 *  dump is added.
 *
 *  Revision 1.8  2006/12/07 13:49:47  nanjo
 *  Remove extra ;
 *
 *  Revision 1.7  2006/12/06 18:38:38  nanjo
 *  CVS variables.
 *
 */
#include "GsimData/GsimTrackData.h"
#include "TDatabasePDG.h"
#include <iostream>
#include <cstdio>

#if !defined(__CINT__)
ClassImp(GsimTrackData)
#endif


GsimTrackData::GsimTrackData()  :
  TObject(),
  track(0),
  mother(0),
  pid(-999),
  p(-999,-999,-999),
  ek(-999),
  mass(-999),
  time(-999),
  v(-999,-999,-999),
  end_p(-999,-999,-999),
  end_ek(-999),
  end_time(-999),
  end_v(-999,-999,-999),
  mech(0),
  status(0),
  thisID(0),
  history(0xffffffffffffffffULL)
{
  
}


GsimTrackData::GsimTrackData(const GsimTrackData& right):
  TObject(right),
  track(right.track),
  mother(right.mother),
  pid(right.pid),
  p(right.p),
  ek(right.ek),
  mass(right.mass),
  time(right.time),
  v(right.v),
  end_p(right.end_p),
  end_ek(right.end_ek),
  end_time(right.end_time),
  end_v(right.end_v),
  mech(right.mech),
  status(right.status),
  thisID(right.thisID),
  history(right.history)
{
  ;
}


GsimTrackData::~GsimTrackData()
{
  ;
}

void GsimTrackData::Clear(Option_t*)
{
  ;
}

GsimTrackData& GsimTrackData::operator=(const GsimTrackData& right)
{
  if (this != &right) {
    track=right.track;
    mother=right.mother;
    pid=right.pid;
    p=right.p;
    ek=right.ek;
    mass=right.mass;
    time=right.time;
    v=right.v;
    end_p=right.end_p;
    end_ek=right.end_ek;
    end_time=right.end_time;
    end_v=right.end_v;
    mech=right.mech;
    status=right.status;
    thisID=right.thisID;
    history=right.history;
  }
  return *this;
}


void GsimTrackData::dump(std::list<int>& state)
{
  TDatabasePDG* pdg = TDatabasePDG::Instance();
  for(std::list<int>::iterator
	it=state.begin();it!=state.end();it++) {
    if((*it)==-1) {
      std::cout << "    ";
    } else if ((*it)==0) {
      std::cout << "`-- ";
    } else if ((*it)==1) {
      std::list<int>::iterator ite=state.end();
      ite--;
      if(it==ite) {
	std::cout << "|-- ";
      } else {
	std::cout << "|   ";
      }
    }
  }


  std::string name ="ion?";
  TParticlePDG* particle = pdg->GetParticle(pid);
  if(particle) name=particle->GetName();
  
  std::cout << name;
  int num=41-(int(name.size())+4*(state.size()));
  if(num>0) {
    for(int k=0;k<num;k++) {
      std::cout << " ";
    }
  }

  std::string hs=convert5(history);
  
  char li[1000];
  std::sprintf(li,"%5d %4d %4d %4d %7.0f %7.0f %7.0f %7.2f %7.2f %7.2f %6.2f %7.2f %s",
	       pid,track,mother,mech,
               v.X(),v.Y(),v.Z(),
               ek,p.Mag(),p.CosTheta(),p.Phi(),time,hs.c_str());
	       
  std::cout << li << std::endl;
}

std::string GsimTrackData::convert5(unsigned long long targ)
{
  targ=targ>>4;
  int pent[12];
  for(int i=0;i<12;i++) {
    pent[i]=targ&0x1f;
    targ=targ>>5;
  }

  std::string sh;
  for(int i=0;i<12;i++) {
    std::string o=dtop( pent[i] );
    if(o!="v" && o!="z") {
      sh+=o;
    }
  }
  return sh;
}

int GsimTrackData::ptod(std::string p)
{
  if(p.size()!=1) return -1;

  for(int i=0;i<32;i++) {
    std::string c=dtop(i);
    if(c==p) return i;
  }
  return -1;
}

std::string GsimTrackData::dtop(int d)
{
  std::string out;
  if(d>=0 && d<=9) {
    char c[10];
    sprintf(c,"%d",d);
    out=c;
  } else if(d>=0 && d<=31) {
    out=char(97+d-10);
  } else {
    out="z";
  }
  return out;
}
