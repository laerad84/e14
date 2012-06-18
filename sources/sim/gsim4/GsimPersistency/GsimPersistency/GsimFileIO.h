/**
 *  @file
 *  @brief  GsimFileIO
 *  $Id: GsimFileIO.h,v 1.4 2007/02/04 12:54:11 nanjo Exp $
 *  $Log: GsimFileIO.h,v $
 *  Revision 1.4  2007/02/04 12:54:11  nanjo
 *  Macro is stored in ROOT file.
 *
 *  Revision 1.3  2006/12/09 21:34:09  nanjo
 *  briefHistory is corrected and dictionary write.
 *
 *  Revision 1.2  2006/12/09 00:43:59  nanjo
 *  writeDictionary
 *
 *  Revision 1.1  2006/12/06 18:43:16  nanjo
 *  Midas I/O is added and Root I/O is separated.
 *
 */

#ifndef GsimFileIO_h
#define GsimFileIO_h


//includes
#include <vector>
#include <string>
#include <map>
#include <fstream>

class TH1D;
class TH2D;

//forward declaration

/**
 *  @class GsimFileIO
 *  @brief FileIO
 *
 *  This class provides ...
 */


class GsimFileIO
{
public:
  GsimFileIO(const char* tfname=0);
  virtual ~GsimFileIO();

  virtual void preBeginOfRunAction(int treeID,int runNumber)=0;
  virtual void postBeginOfRunAction()=0;
  virtual void endOfRunAction()=0;
  virtual void beginOfEventAction()=0;
  virtual void endOfEventAction(int eventID,bool withDataToStore)=0;
  virtual void close()=0;  
  
  virtual void setBranchOf(std::string treeName,
			   std::string title,
			   std::string className,
			   void* address);
  
  virtual void setBranchOf(std::string treeName,
			   std::string title,
			   void* address,
			   std::string format);
  
  
  virtual void fillTreeOf(std::string treeName);
  
  virtual void setEventBranch(std::string title,
			      std::string className,
			      void* address);
  
  virtual void setEventSeedBranch(std::string title,
				  std::string className,
				  void* address);

  virtual void addTriggerBit(unsigned int status);
				
  
  inline void setCycleOfEventSeedStore(int nEvent);
  std::string getDetectorFullNameByID(int detectorID);
  int getDetectorIDByFullName(std::string detectorFullName);
  int getDetectorBriefIDByID(int detectorID);
  int getDetectorBriefIDByBriefName(std::string briefName);
  std::string getDetectorBriefNameByBriefID(int breifID);
  int getDetectorIDByPhysicalVolumeName(std::string physicalVolumeName);
  std::string getProcessNameByID(int processID);
  int getProcessIDByName(std::string processName);
  std::map<int,int> getClusterInfo(std::string sensitiveDetectorName);
  void writeDictionary();
  void withDictionary(bool with);
  virtual void readScript(const char* fname);
  virtual void readCommand(const char* line);

  virtual TH1D* createHistogram(char* name,char* title,
				int nbin,double xmin,double xmax);
  virtual void  fillHistogram(char* name,double value);

  virtual TH2D* createHistogram(char* name,char* title,
			int nbinx,double xmin,double xmax,
			int nbiny,double ymin,double ymax);
  virtual void  fillHistogram(char* name,double xvalue,double yvalue);
  
 protected:
  std::string   m_ofname;
  std::string   m_dictfn;
  std::ofstream m_dictfo;
  int m_runNumber;
  int m_cycleOfEventSeedStore;

  bool m_withDictionary;

  //Data base
  std::map<int,std::string> m_detectorIDFullName;
  std::map<std::string,int> m_detectorFullNameID;
  
  std::map<int,int> m_detectorIDBriefID;
  std::map<int,std::string> m_detectorBriefIDBriefName;

  std::map<std::string,int> m_physicalVolumeNameDetectorID;
  std::map<int,std::string> m_processIDName;
  std::map<std::string,int> m_processNameID;

  std::map<std::string,int> m_sensitiveDetectorNameID;
  std::map<std::string,std::map<int,int> > m_sensitiveDetectorNameChannelIDClusterID;
};


inline void GsimFileIO::setCycleOfEventSeedStore(int nEvent) {
  m_cycleOfEventSeedStore=nEvent;
}

inline void GsimFileIO::withDictionary(bool with)
{
  m_withDictionary=with;
}
#endif // GsimFileIO_h

