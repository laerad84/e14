/**
 *  $Id: GsimDigitizer.cc,v 1.17 2006/12/06 18:44:00 nanjo Exp $ 
 *  $Log: GsimDigitizer.cc,v $
 *  Revision 1.17  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 */
#include "GsimKernel/GsimDigitizer.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimPersistency/GsimPersistencyManager.h"
#include "GsimData/GsimDetectorEventData.h"
#include "GsimData/GsimDetectorHitData.h"
#include "GsimData/GsimTimeData.h"
#include "GsimData/GsimDigiData.h"

GsimDigitizer::GsimDigitizer(std::string sensitiveDetectorName)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_name = "GsimDigitizer";
  m_sensitiveDetectorName=sensitiveDetectorName;
  m_sensitiveDetectorID=-1;
  m_t0=0.;
  m_tdcThresholdEnergy=0;
  //m_tdcThresholdEnergy=1.3;//MeV for CSI
  m_pileupTimeWidth=20;
  m_adcGateWidth=310e3;
  
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimDigitizer::~GsimDigitizer()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDigitizer::digitize(GsimDetectorEventData* eventData)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  buildMtimeFromHits(eventData);
  constructDigiFromMtime(eventData);
  fillHitsInformationToDigi(eventData);
  fillEnergyToDigiFromMtim(eventData);
  fillTimeToDigiFromMtim(eventData);
  buildTrigFromMtimeDigi(eventData);

#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


  
  
  


void GsimDigitizer::buildMtimeFromHits(GsimDetectorEventData* eventData)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  TClonesArray &arHits = *(eventData->hits);
  TClonesArray &arMtime = *(eventData->mtime);
  
  if(arMtime.GetEntriesFast()>0) {
    eventData->mtime->Clear("C");
  }
  
  for(int i=0;i<arHits.GetEntriesFast();i++) {
    GsimDetectorHitData* hitData =
      (GsimDetectorHitData*)arHits[i];
    int ch=hitData->hitChannel;
    GsimTimeData* timeData = new (arMtime[i]) GsimTimeData();
    timeData->initializeDataValues();
    timeData->modID=ch;
    timeData->energy=hitData->edep;
    timeData->time=hitData->time-m_t0;
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDigitizer::constructDigiFromMtime(GsimDetectorEventData* eventData)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  TClonesArray &arMtime = *(eventData->mtime);
  TClonesArray &arDigi = *(eventData->digi);

  if(arDigi.GetEntriesFast()>0) {
    eventData->digi->Clear("C");
  }
  
  GsimDigiData* digiData=0;
  int digiCount=0;
  int prevch=-9999;

  //create digiData and fill modID
  for(int i=0;i<arMtime.GetEntriesFast();i++) {
    GsimTimeData* timeData = (GsimTimeData*)arMtime[i];
    int ch=timeData->modID;
    if(ch>prevch) {
      digiData = new (arDigi[digiCount]) GsimDigiData();
      digiData->initializeDataValues();
      digiData->thisID=digiCount;
      digiData->detID=m_sensitiveDetectorID;
      digiData->modID=ch;
      digiData->mtimeEntry=i;
      digiData->mtimeSize=0;
      digiCount++;
    }
    digiData->mtimeSize++;
    prevch=ch;
  }
  eventData->nDigi=digiCount;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDigitizer::fillHitsInformationToDigi(GsimDetectorEventData* eventData)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  TClonesArray &arHits = *(eventData->hits);
  TClonesArray &arDigi = *(eventData->digi);

  GsimDigiData* digiData=0;
  int digiCount=0;
  int prevch=-9999;
  double eneMax=-999;

  for(int i=0;i<arHits.GetEntriesFast();i++) {
    GsimDetectorHitData* hitData =
      (GsimDetectorHitData*)arHits[i];
    int ch=hitData->hitChannel;
    if(ch>prevch) {
      digiData =(GsimDigiData*)arDigi[digiCount];
      digiCount++;
      eneMax=-999;
    }
    double ene=hitData->edep;
    if(ene>eneMax) {
      digiData->track=hitData->track;
      digiData->status=hitData->stop;
      eneMax=ene;
    }
    prevch=ch;
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDigitizer::fillEnergyToDigiFromMtim(GsimDetectorEventData* eventData)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  TClonesArray &arMtime = *(eventData->mtime);
  TClonesArray &arDigi = *(eventData->digi);
  
  //fill energy for digiData with timeData
  GsimDigiData* digiData=0;
  int digiCount=0;
  int prevch=-9999;
  for(int i=0;i<arMtime.GetEntriesFast();i++) {
    GsimTimeData* timeData = (GsimTimeData*)arMtime[i];
    int ch=timeData->modID;
    if(ch>prevch) {
      digiData =(GsimDigiData*)arDigi[digiCount];
      digiCount++;
    }
    double time=timeData->time;//t0 is already subtracted here
    if(time>=0 && time<=m_adcGateWidth) {
      double ene=timeData->energy;
      digiData->energy+=ene;
    }
    prevch=ch;
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDigitizer::fillTimeToDigiFromMtim(GsimDetectorEventData* eventData)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  std::list<GsimTimeData*> channelTimeList;
  TClonesArray &arMtime = *(eventData->mtime);
  TClonesArray &arDigi = *(eventData->digi);
  
  //fill timing for digiData with timeData
  GsimDigiData* digiData=0;
  int digiCount=0;
  int prevch=-9999;
  for(int i=0;i<arMtime.GetEntriesFast();i++) {
    GsimTimeData* timeData = (GsimTimeData*)arMtime[i];
    int ch=timeData->modID;
    if(ch>prevch) {
      fillTiming(digiData,channelTimeList);
      channelTimeList.clear();
      digiData =(GsimDigiData*)arDigi[digiCount];
      digiCount++;
    }
    channelTimeList.push_back(timeData);
    prevch=ch;
  }
  fillTiming(digiData,channelTimeList);
  channelTimeList.clear();
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDigitizer::fillTiming(GsimDigiData* digiData,
			       std::list<GsimTimeData*>& channelTimeList)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  if(!digiData) return;
  std::list<GsimTimeData*>::iterator it0=channelTimeList.begin();
  
  double  esum = 0;
  bool isTriggered = false;
  double  hitTime   = 9999;

  for(std::list<GsimTimeData*>::iterator it=channelTimeList.begin();
      it!=channelTimeList.end();it++) {
    if(isTriggered) continue;
    
    while( (*it0)->time < (*it)->time - m_pileupTimeWidth ){ 
      double  e0 = (*it0)->energy;
      esum -= e0;
      it0++;
    }
    double  e = (*it)->energy;
    esum += e;
    if ( esum > m_tdcThresholdEnergy ){
      // Threhold for TDC
      hitTime = (*it)->time;
      isTriggered=true;
    }
  }
  digiData->time = hitTime;
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}





void GsimDigitizer::buildTrigFromMtimeDigi(GsimDetectorEventData* eventData)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  TClonesArray &arMtime = *(eventData->mtime);
  TClonesArray &arTrig = *(eventData->trig);
  TClonesArray &arDigi = *(eventData->digi);

  if(arTrig.GetEntriesFast()>0) {
    eventData->trig->Clear("C");
  }
  
  std::multimap<int,GsimTimeData*> clDataMap;
  for(int i=0;i<arMtime.GetEntriesFast();i++) {
    GsimTimeData* timeData = (GsimTimeData*)arMtime[i];
    int ch=timeData->modID;
    int cl=getClusterID(ch);
    if(cl>=0) {
      clDataMap.insert( std::make_pair(cl,timeData) );
    }
  }

  GsimTimeData* trigData=0;
  int prevcl=-1;
  int prevch=-1;
  int cnt=0;

  for(std::multimap<int,GsimTimeData*>::iterator it=clDataMap.begin();
      it!=clDataMap.end();it++) {
    GsimTimeData* timeData=(*it).second;
    int cl=(*it).first;
    int ch=timeData->modID;

    if(cl>prevcl) {
      trigData = new (arTrig[cnt]) GsimTimeData();
      trigData->initializeDataValues();
      trigData->modID=cl;
      cnt++;
    }

    if(ch>prevch) {
      for(int k=0;k<arDigi.GetEntriesFast();k++) {
	GsimDigiData* digiData = (GsimDigiData*)arDigi[k];
	if(digiData->modID==ch && digiData->time<trigData->time) {
	  trigData->time=digiData->time;
	}
      }
    }
    
    if(timeData->time>0) {
      trigData->energy+=timeData->energy;
    }
    
    prevcl=cl;
    prevch=ch;
  }

#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}




void GsimDigitizer::setClusterID(int channelID,int clusterID)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  std::pair<std::map<int,int>::iterator,bool> ok
    =m_channelIDClusterID.insert(std::make_pair(channelID,clusterID));
  if(!ok.second) {
    //overwrite
    m_channelIDClusterID[channelID]=clusterID;
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

int GsimDigitizer::getClusterID(int channelID)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  int clid=-1;
  std::map<int,int>::iterator itm=m_channelIDClusterID.find(channelID);
  if(itm!=m_channelIDClusterID.end()) {
    clid=(*itm).second;
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return clid;
}


void GsimDigitizer::importDigitizerInformation()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  GsimPersistencyManager* persistencyManager
    =GsimPersistencyManager::getPersistencyManager();
  m_channelIDClusterID=persistencyManager->getClusterInfo(m_sensitiveDetectorName);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}
