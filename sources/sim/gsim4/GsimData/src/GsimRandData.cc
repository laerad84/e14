/**
 *  $Id: GsimRandData.cc,v 1.4 2006/12/07 13:49:47 nanjo Exp $ 
 *  $Log: GsimRandData.cc,v $
 *  Revision 1.4  2006/12/07 13:49:47  nanjo
 *  Remove extra ;
 *
 *  Revision 1.3  2006/12/06 18:38:38  nanjo
 *  CVS variables.
 *
 */
#include "GsimData/GsimRandData.h"
#include "TFile.h"
#include "TTree.h"
#include "TEventList.h"

#include <iostream>
#include <cstdio>

#if !defined(__CINT__)
ClassImp(GsimRandData)
#endif

GsimRandData::GsimRandData() : TObject()
{
  className="GsimRandData";
  name="";


  run_number=0;
  event_number=0;
  engineID=0;
  for(int i=0;i<624;i++) {
    seed[i]=0;
  }
  count=0;
  version=1;
}


GsimRandData::~GsimRandData()
{
  ;
}


void GsimRandData::Clear(Option_t* )
{
  ;
}

void GsimRandData::initializeDataValues()
{
  ;
}


bool GsimRandData::getSeed(std::string tfName,int treeID,int eventID,
			   std::vector<unsigned long>& seedVector)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  seedVector.clear();
  TFile* tf = new TFile(tfName.c_str());
  if(!tf) return false;
  
  char tit[100];
  std::sprintf(tit,"eventSeedTree%02d",treeID);
  TTree* tr = (TTree*)tf->Get(tit);
  if(!tr) {
    std::cerr << "GsimRootIO::getSeed, No such tree." << std::endl;
    tf->Close();
    return false;
  }

  GsimRandData* rd = new GsimRandData();
  tr->SetBranchAddress("Rand.",&rd);

  char cu[1000];
  std::sprintf(cu,"event_number==%d",eventID);
  tr->Draw(">>gsimeventlist",cu,"goff");
  TEventList* elis = (TEventList*)gDirectory->Get("gsimeventlist");

  if(elis->GetN()==0) {
    delete elis;
    tf->Close();
    std::cerr << "GsimRootIO::getSeed, No such eventID for random seed." << std::endl;
    return false;
  }

  Long64_t entry=elis->GetEntry(0);
  tr->GetEntry(entry);

  seedVector.push_back(static_cast<unsigned long>(rd->engineID));
  for(int j=0;j<624;j++) {
    seedVector.push_back(static_cast<unsigned long>(rd->seed[j]));
  }
  seedVector.push_back(static_cast<unsigned long>(rd->count));
  
  delete elis;
  tf->Close();

  return true;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}
