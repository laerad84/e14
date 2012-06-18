/**
 *  @file
 *  @brief  GsimMessage
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimMessage.h,v 1.5 2006/09/29 08:21:56 nanjo Exp $
 *  $Log: GsimMessage.h,v $
 *  Revision 1.5  2006/09/29 08:21:56  nanjo
 *  Total number of event is automatically stored.
 *
 *  Revision 1.4  2006/09/29 05:15:52  nanjo
 *  The memory usage at the end of run is printed.
 *
 *  Revision 1.3  2006/05/30 07:50:51  nanjo
 *  New debug message with __PRETTY_FUNCTION__ is experimentally added.
 *
 *  Revision 1.2  2006/01/26 04:34:22  nanjo
 *  Factory pattern and template method on factory and messenger class is intorduced .
 *
 */

#ifndef GsimMessage_h
#define GsimMessage_h

// includes
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

// forward declaration 

/**
 *  @class GsimMessage
 *  @brief singleton class for message reporting.
 *
 *  This class provide features to report messages
 *  to a std::cerr or a file according to
 *  a verbose level of this class.
 *  This class is a singleton class,
 *  so it can be used from anywhere.
 *  The verbose levels are as follows.
 *    - debug   == 4 (controlled by GSIMDEBUG macro)
 *    - info    == 3
 *    - warning == 2
 *    - error   == 1 (default)
 *    - off     == 0
 *  If you want debug messages,
 *  define GSIMDEBUG macro.
 *  This class is completely independent
 *  from Geant4 framework. So no messenger is 
 *  attached to this class.
 *  The properties of this class might be
 *  set thorough an UImessenger of another class.
 *
 */

class GsimMessage 
{
public:

  /// Get instance.
  static GsimMessage* getInstance();

  /// Destructor.
  virtual ~GsimMessage();

  /// Report a message. (level is selected with integer.)
  /**
   *  @param  iThisMsgLevel  verbose level of this message. (0..4)
   *  @param  msg            message to report.
   *
   */
  void report(int iThisMsgLevel,std::string msg);

  /// Report a message. (level is selected with string.)
  /**
   *  @param  sThisMsgLevel  verbose level of this message. (off,info,warning,error,debug)
   *  @param  msg            message to report. 
   *
   */
  void report(std::string sThisMsgLevel,std::string msg);

  void debugEnter(const char* prettyFunction);
  void debugExit(const char* prettyFunction);

  /// Set verbose level with integer .
  void setVervoseLevel(int         iVerboseLevel);
  
  /// Set verbose level with string.
  void setVervoseLevel(std::string sVerboseLevel);
  
  /// Set output file name.
  /**
   *  If outputFileName is "", the output stream is set to std::cerr.
   *  Overwriting an existing file is forbiddened.
   *  If a file of outputFileName exist,
   *  the output stream is set to std::cerr.
   *
   *  @param  outputFileName output file name. ("" set std::cerr as output stream.)
   */
  void setReportOutputFileName(std::string outputFileName);

  void addSystemInfo();
  void outputSystemInfo(std::string msg);

  
 private:
  /// Hidden constructor.
  GsimMessage();

  /// Hidden copy constructor.
  GsimMessage(const GsimMessage& msg);

  /// Convert string verbose level to integer.
  int convertToIntegerLevel(std::string sLevel);

  /// Convert integer verbose level to string.
  std::string convertToStringLevel(int iLevel);

  /// GsimMessage instance.
  static GsimMessage* s_message;

  /// Verbose level.
  /**
   *  Verbose levels are
   *    - debug   == 4-> controlled by GSIMDEBUG macro
   *    - info    == 3
   *    - warning == 2
   *    - error   == 1
   *    - off     == 0
   *  If you want debug messages,
   *  define GSIMDEBUG macro.
   *    (#define GSIMDEBUG)
   *  Default level is error.
   */
  int m_verboseLevel;

  /// Output file name for reporing.
  /**
   *  If m_outputFileName=="",
   *  output messages to std::cerr.
   */
  std::string m_outputFileName;

  /// Output stream;
  std::ofstream m_outputFileStream;

  /// proc file system?
  bool m_isProc;

  /// memory page size for memory debuging.
  int pageSize;

  /// process id for memory debuging.
  int processId;

};

#endif // GsimMessage_h

