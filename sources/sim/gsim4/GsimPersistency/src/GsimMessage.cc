/**
 *  $Id: GsimMessage.cc,v 1.7 2006/09/29 08:21:56 nanjo Exp $
 *  $Log: GsimMessage.cc,v $
 *  Revision 1.7  2006/09/29 08:21:56  nanjo
 *  Total number of event is automatically stored.
 *
 *  Revision 1.6  2006/09/29 05:15:52  nanjo
 *  The memory usage at the end of run is printed.
 *
 *  Revision 1.5  2006/08/24 17:39:00  nanjo
 *  Event processing status is printed in batch mode.
 *
 *  Revision 1.4  2006/05/30 07:50:51  nanjo
 *  New debug message with __PRETTY_FUNCTION__ is experimentally added.
 *
 *  Revision 1.3  2006/05/25 12:29:33  nanjo
 *  Default verbose level is changed to warning from error.
 *
 *  Revision 1.2  2006/01/26 04:50:58  nanjo
 *  Factory pattern and template method on factory and messenger classes is intorduced .
 *
 */
#include "GsimPersistency/GsimMessage.h"

#include <sstream>
extern "C" {
#include <time.h>
#include <unistd.h>
}

GsimMessage* GsimMessage::s_message=0;

GsimMessage* GsimMessage::getInstance()
{
  if(s_message) {
    return s_message;
  }
  static GsimMessage theMessage;
  s_message=&theMessage;
  
  return s_message;
}

GsimMessage::~GsimMessage()
{
  if(m_outputFileStream) {
    m_outputFileStream.close();
    m_outputFileStream.clear();
  }
}

void GsimMessage::report(int iThisMsgLevel,std::string msg)
{
  if(!(iThisMsgLevel <= m_verboseLevel)) return;
  
  std::string sLevel = convertToStringLevel(iThisMsgLevel);
  std::ostream* outputStream=&m_outputFileStream;
  if(!m_outputFileStream) outputStream=&std::cerr;

  (*outputStream) << "[";
  (*outputStream)<< sLevel;
  int nSpace=7-sLevel.size();
  for(int i=0;i<nSpace;++i) {
    (*outputStream) << " ";
  }
  (*outputStream) << "] ";

  
#ifdef GSIMDEBUG
  addSystemInfo();
#endif
  
  (*outputStream) << msg << std::endl;
  
}

void GsimMessage::addSystemInfo()
{
  std::ostream* outputStream=&m_outputFileStream;
  if(!m_outputFileStream) outputStream=&std::cerr;

  /// Aquire current time.
  time_t timer;
  std::string sTime=ctime(&(timer=time(0)));

  /// Output current time.
  (*outputStream) << " [";
  (*outputStream) << std::string(sTime,0,sTime.size()-1);
  (*outputStream) << "] ";


  if(m_isProc) {
    /// Aquire statm file, /proc/pid/statm.
    
    std::ostringstream ostr;
    ostr << processId;
    
    
    std::string finame = "/proc/";
    finame+=ostr.str();
    finame+="/statm";
    std::ifstream fi;
    fi.open(finame.c_str());
    
    if(!fi.is_open()) {
      std::string msg="No such files : ";
      msg += finame;
      msg += " memory info is not reported .";
      report(0,msg);
    } else {
      
      /// Aquire memory info. from /proc/pid/statm.
      int memoryInfo[7];
      /**
       *   - size
       *   - resident Rsident Set Size
       *   - share
       *   - trs      text
       *   - drs      data/stack
       *   - lrs      library
       *   - dt       darty 
       */
      int tmpval;
      for(int i=0;i<7;++i) {
	fi >> tmpval;
	memoryInfo[i]=tmpval;
      }
      fi.close();


      /// Output memory info.
      (*outputStream) << " [";
      (*outputStream) << "MemSize = ";
      (*outputStream) << std::setw(8) << memoryInfo[0];
      (*outputStream) << " | RES = ";
      (*outputStream) << std::setw(8) << memoryInfo[1];
      (*outputStream) << " | SHR = ";
      (*outputStream) << std::setw(8) << memoryInfo[2];
      (*outputStream) << "] ";
    }
  }
}
  
void GsimMessage::outputSystemInfo(std::string msg)
{

  std::ostream* outputStream=&m_outputFileStream;
  if(!m_outputFileStream) outputStream=&std::cerr;

  (*outputStream) << "[info   ]";
  addSystemInfo();
  (*outputStream) << msg;
  (*outputStream) << std::endl;
}


void GsimMessage::report(std::string thisMsgLevel,std::string msg)
{
  int iLevel=convertToIntegerLevel(thisMsgLevel);
  report(iLevel,msg);
}

void GsimMessage::debugEnter(const char* prettyFunction)
{
  std::string msg="enter ";
  msg+=prettyFunction;
  report("debug",msg);
}

void GsimMessage::debugExit(const char* prettyFunction)
{
  std::string msg="exit  ";
  msg+=prettyFunction;
  report("debug",msg);
}

void GsimMessage::setVervoseLevel(int iVerboseLevel)
{
  if(! (iVerboseLevel>=0 && iVerboseLevel<=4) ) {
    report(0,"Verbose level should be 0, 1, 2, 3, or 4.");
  }
    
#ifdef GSIMDEBUG
  if(iVerboseLevel!=4) {
    report(0,"GSIMDEBUG is defined and verbose level is 4.");
  }
  return;
#else
  if(iVerboseLevel==4) {
    report(0,"GSIMDEBUG is not defined and verbose level can't be 4.");
    return;
  }
#endif
  m_verboseLevel=iVerboseLevel;
}

void GsimMessage::setVervoseLevel(std::string sVerboseLevel)
{
  int iLevel=convertToIntegerLevel(sVerboseLevel);
  setVervoseLevel(iLevel);
}

void GsimMessage::setReportOutputFileName(std::string outputFileName)
{
  if(outputFileName=="") {
    if(m_outputFileStream) {
      m_outputFileStream.close();
      m_outputFileStream.clear();
    }
    m_outputFileName="";
  } else {
    std::ifstream fi;
    fi.open(outputFileName.c_str());
    if(fi.is_open()) {
      std::string msg="File, ";
      msg+=outputFileName;
      msg+=", exists.";
      report(0,msg);
      fi.close();
      return;
    }
    fi.close();
    fi.clear();
    
    m_outputFileName=outputFileName;
    m_outputFileStream.open(m_outputFileName.c_str());
  }
  
}


GsimMessage::GsimMessage()
{
  m_verboseLevel=3;
#ifdef GSIMDEBUG
  m_verboseLevel=4;
#endif
  m_outputFileName="";
  pageSize = getpagesize();
  processId = getpid();

  m_isProc=true;
  std::string finame = "/proc/version";
  std::ifstream fi;
  fi.open(finame.c_str());
  if(fi.fail()) {
    m_isProc=false;
    report("info","There is no proc file system.");
  }
  
}

int GsimMessage::convertToIntegerLevel(std::string sLevel)
{
  int iLevel=1;
  if(sLevel=="debug") {
    iLevel=4;
  } else if(sLevel=="info") {
    iLevel=3;
  } else if(sLevel=="warning") {
    iLevel=2;
  } else if(sLevel=="error") {
    iLevel=1;
  } else if(sLevel=="off") {
    iLevel=0;
  } else {
    std::string msg="Level, ";
    msg+=sLevel;
    msg+=", is requested, but ";
    msg+="Level should be debug, info, warning, error, or off.";
    report(0,msg);
  }

  return iLevel;
}


std::string GsimMessage::convertToStringLevel(int iLevel)
{
  std::string sLevel="error";
  if(iLevel==4) {
    sLevel="debug";
  } else if(iLevel==3) {
    sLevel="info";
  } else if(iLevel==2) {
    sLevel="warning";
  } else if(iLevel==1) {
    sLevel="error";
  } else if(iLevel==0) {
    sLevel="off";
  } else {
    std::string msg="Level, ";
    msg+=iLevel;
    msg+=", is requested, but ";
    msg+="Level should be 0, 1, 2, 3, or 4.";
    report(0,msg);
  }
  return sLevel;
}

