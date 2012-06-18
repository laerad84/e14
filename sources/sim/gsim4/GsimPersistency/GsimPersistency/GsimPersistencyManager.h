/**
 *  @file
 *  @brief  GsimPersistencyManager
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimPersistencyManager.h,v 1.25 2007/02/04 12:54:11 nanjo Exp $
 *  $Log: GsimPersistencyManager.h,v $
 *  Revision 1.25  2007/02/04 12:54:11  nanjo
 *  Macro is stored in ROOT file.
 *
 *  Revision 1.24  2006/12/09 21:34:09  nanjo
 *  briefHistory is corrected and dictionary write.
 *
 *  Revision 1.23  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 *  Revision 1.22  2006/12/04 20:20:40  nanjo
 *  runNumber is given at PersistencyManager::preBeginOfRun.
 *
 *  Revision 1.21  2006/12/04 17:27:49  nanjo
 *  Data are kept in each class, which are registered to persistencyManger.
 *  GsimPersistencyManger::setBranchOf is added then UserEventData is removed.
 *
 *  Revision 1.20  2006/12/02 07:06:38  nanjo
 *  runTree is added.
 *
 *  Revision 1.19  2006/11/30 20:07:11  nanjo
 *  Data are re-structured.
 *
 *  Revision 1.18  2006/11/20 16:16:45  nanjo
 *  SensitiveDetectorList is kept in DetectorManager.
 *
 *  Revision 1.17  2006/11/17 12:09:40  nanjo
 *  RunIDBase is added.
 *
 *  Revision 1.16  2006/10/26 14:46:12  nanjo
 *  releaseUserEventBranch is added.
 *
 *  Revision 1.15  2006/10/24 15:23:08  nanjo
 *  SensitiveDetector is re-structred.
 *
 *  Revision 1.14  2006/10/19 03:28:44  nanjo
 *  GsimPersistencyManagerMessenger is replaced by GsimRunActionMessneger.
 *  Information of photonuclear interaction is not filled here.
 *  Cluster ID is filled.
 *  Now GsimPersistencyManager, GsimDigitizer, and, GsimMessage is
 *  independent of Geant4. They will be moved to different directory
 *  in order to use from ROOT analysis.
 *
 *  Revision 1.13  2006/10/16 01:54:21  nanjo
 *  CLHEP functions are removed from GsimPersistencyManager.
 *
 *  Revision 1.12  2006/09/06 22:33:18  nanjo
 *  GsimDetectorData is added.
 *
 *  Revision 1.11  2006/06/22 11:38:57  nanjo
 *  Modifications around briefDetectorID and briefDetectorName.
 *
 *  Revision 1.10  2006/04/11 12:39:24  nanjo
 *  Fix a bug for userEventData and GsimDetector::clearThisClone is added.
 *
 *  Revision 1.9  2006/04/09 22:19:20  nanjo
 *  UserEventData is added.
 *
 *  Revision 1.8  2006/03/01 12:45:32  nanjo
 *  A member function of GsimDetector, cloneDetector, is added and used in E391Detector.
 *
 *  Revision 1.7  2006/02/01 15:42:26  nanjo
 *  BriefTrajectory is stored in ROOT file.
 *
 *  Revision 1.6  2006/01/31 22:47:08  nanjo
 *  BriefTrajectory is built from G4VUserTrakInformation.
 *
 *  Revision 1.5  2006/01/31 03:00:38  nanjo
 *  Detector ID and process ID are introduced and stored in TFile.
 *
 *  Revision 1.4  2006/01/30 02:42:07  nanjo
 *  Detector information is stored in persistencyManager.
 *
 *  Revision 1.3  2006/01/27 05:08:24  nanjo
 *  PersistencyManagerMessenger is added.
 *
 *  Revision 1.2  2006/01/27 00:06:26  nanjo
 *  Seeds are saved in GsimPersistencyManager
 *
 *  Revision 1.1  2006/01/26 04:53:30  nanjo
 *  Detector and persistency classes are added.
 *
 */
#ifndef GsimPersistencyManager_h
#define GsimPersistencyManager_h


//includes
#include <vector>
#include <string>
#include <map>

//forward declaration
class GsimFileIO;
class TFile;
class TTree;
class TH1D;
class TH2D;


/**
 *  @class GsimPersisencyManger
 *  @brief Persistency manager.
 *
 *  This class provides ...
 */


class GsimPersistencyManager
{
public:
  GsimPersistencyManager(const char* tfname=0);
  virtual ~GsimPersistencyManager();
  static GsimPersistencyManager* getPersistencyManager();

  void preBeginOfRunAction(int treeID, int runNumber);
  void postBeginOfRunAction();
			   
  
  void endOfRunAction();
  void beginOfEventAction();
  void endOfEventAction(int eventID,bool withDataToStore);
  void close();
  

  
  
  void setBranchOf(std::string treeName,
		   std::string title,
		   std::string className,
		   void* address);

  void setBranchOf(std::string treeName,
		   std::string title,
		   void* address,
		   std::string format);
		   
  
  void fillTreeOf(std::string treeName);

  void setEventBranch(std::string title,
		      std::string className,
		      void* address);

  void setEventSeedBranch(std::string title,
			  std::string className,
			  void* address);

  void addTriggerBit(unsigned int status);
  
  void setCycleOfEventSeedStore(int nEvent);
  
  std::string getDetectorFullNameByID(int detectorID);
  int getDetectorIDByFullName(std::string detectorFullName);
  
  int getDetectorBriefIDByID(int detectorID);
  int getDetectorBriefIDByBriefName(std::string briefName);
  std::string getDetectorBriefNameByBriefID(int breifID);
  
  int getDetectorIDByPhysicalVolumeName(std::string physicalVolumeName);
  std::string getProcessNameByID(int processID);
  int getProcessIDByName(std::string processName);
  std::map<int,int> getClusterInfo(std::string sensitiveDetectorName);

  void writeDictionary(bool write);

  void readScript(const char* fname);
  void readCommand(const char* line);


  TH1D* createHistogram(char* name,char* title,
			int nbin,double xmin,double xmax);
  void  fillHistogram(char* name,double value);

  TH2D* createHistogram(char* name,char* title,
			int nbinx,double xmin,double xmax,
			int nbiny,double ymin,double ymax);
  void  fillHistogram(char* name,double xvalue,double yvalue);
  
  inline GsimFileIO* getFileIO();

private:
  static GsimPersistencyManager* s_persistencyManager;
  GsimFileIO* m_fileIO;
  
};

inline GsimFileIO* GsimPersistencyManager::getFileIO()
{
  return m_fileIO;
}

#endif // GsimPersistencyManager_h

