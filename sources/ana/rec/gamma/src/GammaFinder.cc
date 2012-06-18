// -*- C++ -*-

#include <iostream>
#include <list>
#include "E14Fsim/E14FsimFunction.h"
#include "gnana/E14GNAnaFunction.h"
#include "gamma/GammaFinder.h"


GammaFinder::GammaFinder( )
{
  ;
}


/////
GammaFinder::~GammaFinder()
{
  ;
}

void 
GammaFinder::findGamma(std::list<Cluster> const &clist ,
		       std::list<Gamma>& glist ,int mode){
  if(mode == 0)
    findGammaDefault(clist,glist);
  else if(mode == 1) // for cluster made by findClusterKS(shiomi's method). 
    findGammaKS(clist,glist);
  //  else if(mode == XX)
  //    return findGamma_YYYY(clist);
  else  findGammaDefault(clist,glist);
}

void
GammaFinder::findGammaDefault(std::list<Cluster> const &clist,
			      std::list<Gamma>& glist )
{
  glist.clear();

  for(std::list<Cluster>::const_iterator it = clist.begin();
      it != clist.end();it++){
    double edep = it->e();
    if( edep>20 ){
      Gamma gam(*it);
      glist.push_back(gam);
    }
  }
  int id=0;
  for( std::list<Gamma>::iterator gam=glist.begin();
       gam!=glist.end(); gam++ ){
    gam->setId(id++);

    E14GNAnaFunction::getFunction()->correctEnergy(*gam);
    
    double sigmaE
      =E14FsimFunction::getFunction()->csiEnergyRes(gam->e()/1000.)*1000.;
    gam->setSigmaE(sigmaE);
    
    double sigmaXY 
      =E14FsimFunction::getFunction()->csiPosRes(gam->e()/1000.); //mm
    gam->setSigmaPos(sigmaXY,sigmaXY,0);
  }

}


void
GammaFinder::findGammaKS(std::list<Cluster> const &clist,
			 std::list<Gamma>& glist )
{
  glist.clear();

  for(std::list<Cluster>::const_iterator it = clist.begin();
      it != clist.end();it++){
    Gamma gam(*it);
    glist.push_back(gam);
  }
  int id=0;
  for( std::list<Gamma>::iterator gam=glist.begin();
       gam!=glist.end(); gam++ ){
    gam->setId(id++);

    double edep = gam->e();
    double f = 1+0.06334+0.01815/sqrt(edep/1000.)-0.01634*log(edep/1000.);
    gam->setEnergy(f*edep);
    
    double sigmaE
      =E14FsimFunction::getFunction()->csiEnergyRes(gam->e()/1000.)*1000.;
    gam->setSigmaE(sigmaE);
    
    double sigmaXY 
      =E14FsimFunction::getFunction()->csiPosRes(gam->e()/1000.); //mm
    gam->setSigmaPos(sigmaXY,sigmaXY,0);
  }
}




  



