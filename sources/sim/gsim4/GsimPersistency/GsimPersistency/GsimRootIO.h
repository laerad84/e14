/**
 *  @file
 *  @brief  GsimRootIO
 *  $Id: GsimRootIO.h,v 1.3 2007/02/04 12:54:46 nanjo Exp $
 *  $Log: GsimRootIO.h,v $
 *  Revision 1.3  2007/02/04 12:54:46  nanjo
 *  Macro is stored in ROOT file.
 *
 *  Revision 1.2  2006/12/07 04:44:59  nanjo
 *  runTree is added and GsimRunData is filled.
 *
 *  Revision 1.1  2006/12/06 18:43:16  nanjo
 *  Midas I/O is added and Root I/O is separated.
 *
 */

#ifndef GsimRootIO_h
#define GsimRootIO_h


//includes
#include "GsimPersistency/GsimFileIO.h"
#include <vector>
#include <string>
#include <map>
#include <list>

//forward declaration
class TFile;
class TTree;
class TH1D;
class TH2D;

/**
 *  @class GsimRootIO
 *  @brief RootIO
 *
 *  This class provides ...
 */


class GsimRootIO : public GsimFileIO
{
public:
  GsimRootIO(const char* tfname=0);
  virtual ~GsimRootIO();

  virtual void preBeginOfRunAction(int treeID,int runNumber);
  virtual void postBeginOfRunAction();
  virtual void endOfRunAction();
  virtual void beginOfEventAction();
  virtual void endOfEventAction(int eventID,bool withDataToStore);
  virtual void close();
  
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
  
  virtual void readScript(const char* fname);
  virtual void readCommand(const char* line);

  virtual TH1D* createHistogram(char* name,char* title,
				int nbin,double xmin,double xmax);
  virtual void  fillHistogram(char* name,double value);

  TH2D* createHistogram(char* name,char* title,
			int nbinx,double xmin,double xmax,
			int nbiny,double ymin,double ymax);
  void  fillHistogram(char* name,double xvalue,double yvalue);
  
 protected:
  
  void   constructAllTree(int treeID);
  void   writeAndDestructRunTree();
  void   writeAndDestructEventTree();
  void   fillDetectorDB();
  void   fillProcessDB();
  void   fillPhysicalVolumeDB();
  TTree* getTree(std::string treeName);
  void   headtail(std::string &line);
  
  TFile* m_tfile;

  TTree* m_commandTree;
  TTree* m_runTree;
  TTree* m_detectorTree;
  TTree* m_physicalVolumeTree;
  TTree* m_processTree;

  TTree* m_eventSeedTree;
  TTree* m_eventTree;
  
  int m_treeID;
  int m_eventID;
  int m_eventFillCount;
  char* m_commandBuffer;

  std::list<TH1D*> m_histList;
  std::list<TH2D*> m_histList2;
};

#endif // GsimRootIO_h

