#include "E14Fsim/E14FsimAnalysisModule.h"

std::list<E14FsimVeto*> E14FsimAnalysisModule::s_vetoList;
double  E14FsimAnalysisModule::VetoWeightWithoutIneffiGamma;
double  E14FsimAnalysisModule::VetoWeight;

E14FsimAnalysisModule::E14FsimAnalysisModule()
{
  ;
}

E14FsimAnalysisModule::~E14FsimAnalysisModule()
{
  ;
}


void E14FsimAnalysisModule::clearVetoData()
{
  for(std::list<E14FsimVeto*>::iterator it=s_vetoList.begin();
      it!=s_vetoList.end();it++) {
    delete (*it);
  }
  s_vetoList.clear();
}

