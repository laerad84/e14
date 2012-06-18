/**
 *  $Id: GsimFileIO.cc,v 1.4 2007/02/04 12:55:41 nanjo Exp $ 
 *  $Log: GsimFileIO.cc,v $
 *  Revision 1.4  2007/02/04 12:55:41  nanjo
 *  Fast simulation 3 is added for shower check.
 *
 *  Revision 1.3  2006/12/09 21:34:09  nanjo
 *  briefHistory is corrected and dictionary write.
 *
 *  Revision 1.2  2006/12/09 00:43:58  nanjo
 *  writeDictionary
 *
 *  Revision 1.1  2006/12/06 18:43:16  nanjo
 *  Midas I/O is added and Root I/O is separated.
 *
 */
#include "GsimPersistency/GsimFileIO.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimData/GsimTrackData.h"
#include "TH1.h"
#include "TH2.h"

#include <sstream>

GsimFileIO::GsimFileIO(const char* tfname)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(tfname==0) m_ofname="";
  else m_ofname=std::string(tfname);
    
  m_dictfn=="";
  m_runNumber=0;
  m_cycleOfEventSeedStore=1000;
  
  m_withDictionary=false;
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimFileIO::~GsimFileIO() {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimFileIO::setBranchOf(std::string,
			     std::string,
			     std::string,
			     void*)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimFileIO::setBranchOf(std::string,
			     std::string,
			     void*,
			     std::string)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimFileIO::fillTreeOf(std::string)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimFileIO::setEventBranch(std::string,
				std::string,
				void*)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimFileIO::setEventSeedBranch(std::string,
				    std::string,
				    void*)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimFileIO::addTriggerBit(unsigned int)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

std::string GsimFileIO::getDetectorFullNameByID(int detectorID)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  std::map<int,std::string>::iterator it=m_detectorIDFullName.find(detectorID);
  if(it==m_detectorIDFullName.end()) {
    std::string msg="No such detector fullName for ID, ";
    msg+=detectorID;
    msg+=".";
    GsimMessage::getInstance()
      ->report("warning",msg.c_str());
    return "";
  } else {
    return (*it).second;
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

int GsimFileIO::getDetectorIDByFullName(std::string detectorFullName)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  std::map<std::string,int>::iterator it=m_detectorFullNameID.find(detectorFullName);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  if(it==m_detectorFullNameID.end()) {
    std::string msg="No such detector ID for fullName, ";
    msg+=detectorFullName;
    msg+=".";
    GsimMessage::getInstance()
      ->report("warning",msg.c_str());
    return -1;
  } else {
    return (*it).second;
  }
}

int GsimFileIO::getDetectorBriefIDByID(int detectorID)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  std::map<int,int>::iterator it=m_detectorIDBriefID.find(detectorID);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  if(it==m_detectorIDBriefID.end()) {
    std::string msg="No such detector briefID for detectorID, ";
    msg+=detectorID;
    msg+=".";
    GsimMessage::getInstance()
      ->report("warning",msg.c_str());
    return -1;
  } else {
    return (*it).second;
  }
}

int GsimFileIO::getDetectorBriefIDByBriefName(std::string briefName)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  int out=-1;
  for(std::map<int,std::string>::iterator it=m_detectorBriefIDBriefName.begin();
      it!=m_detectorBriefIDBriefName.end();it++) {
    int id=(*it).first;
    std::string name =(*it).second;
    if(name == briefName) out=id;
  }
  if(out==-1) {
    std::string msg="No such detector briefName, ";
    msg+=briefName;
    msg+=".";
    GsimMessage::getInstance()
      ->report("warning",msg.c_str());
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return out;
}

std::string GsimFileIO::getDetectorBriefNameByBriefID(int briefID)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  std::map<int,std::string>::iterator it=m_detectorBriefIDBriefName.find(briefID);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  if(it==m_detectorBriefIDBriefName.end()) {
    std::string msg="No such detector briefName for briefID, ";
    msg+=briefID;
    msg+=".";
    GsimMessage::getInstance()
      ->report("warning",msg.c_str());
    return "";
  } else {
    return (*it).second;
  }
}

int GsimFileIO::getDetectorIDByPhysicalVolumeName(std::string physicalVolumeName)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  std::map<std::string,int>::iterator it=m_physicalVolumeNameDetectorID.find(physicalVolumeName);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  if(it==m_physicalVolumeNameDetectorID.end()) {
    std::string msg="No such detector ID for physical volume name, ";
    msg+=physicalVolumeName;
    msg+=".";
    GsimMessage::getInstance()
      ->report("warning",msg.c_str());
    return -1;
  } else {
    return (*it).second;
  }
}

std::string GsimFileIO::getProcessNameByID(int processID)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  std::map<int,std::string>::iterator it=m_processIDName.find(processID);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  if(it==m_processIDName.end()) {
    std::ostringstream ostr;
    
    ostr << "No such process name for process id, ";
    ostr << processID << ".";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
    return "";
  } else {
    return (*it).second;
  }
}

int GsimFileIO::getProcessIDByName(std::string processName)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  std::map<std::string,int>::iterator it=m_processNameID.find(processName);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  if(it==m_processNameID.end()) {
    std::string msg="No such process ID for process name, ";
    msg+=processName;
    msg+=".";
    GsimMessage::getInstance()
      ->report("warning",msg.c_str());
    return -1;
  } else {
    return (*it).second;
  }
}


std::map<int,int> GsimFileIO::getClusterInfo(std::string sensitiveDetectorName)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  std::map<int,int> chcl;
  std::map<std::string,std::map<int,int> >::iterator it
    =m_sensitiveDetectorNameChannelIDClusterID.find(sensitiveDetectorName);
  if(it!=m_sensitiveDetectorNameChannelIDClusterID.end()) {
    chcl=(*it).second;
  }

#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return chcl;
}


void GsimFileIO::writeDictionary()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(m_withDictionary==false) return;
  
  if(m_dictfn=="") {
    m_dictfn=m_ofname;
    m_dictfn+=".dict";
    m_dictfo.open(m_dictfn.c_str());
  }
  m_dictfo << "Run number : " << m_runNumber << std::endl;
  m_dictfo << "Process ID" << std::endl;
  
  for(std::map<int,std::string>::iterator
	it=m_processIDName.begin();
      it!=m_processIDName.end();it++) {
    m_dictfo << (*it).first << "\t"
	     << (*it).second << std::endl;
  }
  
  m_dictfo << "Sensitive detector ID" << std::endl;
  std::map<int,std::string> tmpmap;
  for(std::map<std::string,int>::iterator
	it=m_sensitiveDetectorNameID.begin();
      it!=m_sensitiveDetectorNameID.end();it++) {
    tmpmap.insert( std::make_pair((*it).second,
				  (*it).first) );
  }
  for(std::map<int,std::string>::iterator
	it=tmpmap.begin();it!=tmpmap.end();it++) {
    m_dictfo << (*it).first << "\t"
	     << (*it).second << std::endl;
  }

  m_dictfo << "Brief detector ID" << std::endl;
  for(std::map<int,std::string>::iterator it
	=m_detectorBriefIDBriefName.begin();
      it!=m_detectorBriefIDBriefName.end();it++) {
    m_dictfo << (*it).first << "\t"
	     << GsimTrackData::dtop( (*it).first ) << "\t"
	     << (*it).second << std::endl;
  }

  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}



void GsimFileIO::readScript(const char*)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimFileIO::readCommand(const char*)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


TH1D* GsimFileIO::
createHistogram(char* ,char* ,int ,double ,double )
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return 0;
}

void  GsimFileIO::
fillHistogram(char* ,double )
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


TH2D* GsimFileIO::
createHistogram(char* ,char* ,
		int ,double ,double ,
		int ,double ,double )
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return 0;
}

void  GsimFileIO::
fillHistogram(char* ,double ,double )
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}
