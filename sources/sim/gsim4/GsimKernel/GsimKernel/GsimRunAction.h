/**
 *  @file
 *  @brief  GsimRunAction
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimRunAction.h,v 1.7 2006/12/07 04:44:59 nanjo Exp $
 *  $Log: GsimRunAction.h,v $
 *  Revision 1.7  2006/12/07 04:44:59  nanjo
 *  runTree is added and GsimRunData is filled.
 *
 *  Revision 1.6  2006/12/04 17:27:49  nanjo
 *  Data are kept in each class, which are registered to persistencyManger.
 *  GsimPersistencyManger::setBranchOf is added then UserEventData is removed.
 *
 *  Revision 1.5  2006/11/30 20:07:11  nanjo
 *  Data are re-structured.
 *
 *  Revision 1.4  2006/11/17 12:09:40  nanjo
 *  RunIDBase is added.
 *
 *  Revision 1.3  2006/10/16 01:54:22  nanjo
 *  CLHEP functions are removed from GsimPersistencyManager.
 *
 *  Revision 1.2  2006/01/27 00:06:26  nanjo
 *  Seeds are saved in GsimPersistencyManager
 *
 *  Revision 1.1  2006/01/26 04:53:30  nanjo
 *  Detector and persistency classes are added.
 *
 */
#ifndef GsimRunAction_h
#define GsimRunAction_h

//includes
#include "globals.hh"
#include "G4UserRunAction.hh"
#include "GsimData/GsimProcessData.h"
#include <vector>

//forward declaration
class GsimDetectorManager;
class G4Run;
class G4Timer;

/**
 *  @class GsimRunAction
 *  @brief RunAction.
 *
 *  This class provides methods at
 *  the beginning or end of run,
 *  which is inherited rom G4UserRunAction.
 *
 */

class GsimRunAction : public G4UserRunAction
{
public:
  /// Constructor.
  GsimRunAction(GsimDetectorManager* dm, int runNumberBase=0);

  /// Destructor.
  ~GsimRunAction();
  
public:
  /// BeginOfRunAction.
  /**
   * This is defined as a virtual method in
   * G4UserRunAction, which provide a method
   * executed at the beginning of run.
   */
  void BeginOfRunAction(const G4Run* aRun);

  /// EndOfRunAction.
  /**
   * This is defined as a virtual method in
   * G4UserRunAction, which provide a method
   * executed at the end of run.
   */
  void EndOfRunAction(const G4Run* aRun);

  void setSeed(long singleSeed);
  void setSeed(std::vector<unsigned long> seedVector);
  void setSeed(std::string tfName,int runID=0,int eventID=0);

  void setRunNumberBase(int runNumberBase);
  int  getRunNumber() const;
  int  getRunID() const;  
  
private:

  void fillProcessData();

  /// SIGINT handler.
  /**
   * Abort event and then abort run.
   */
  static void interruptHandler(int sig);

  /// If this is the first run, true.
  bool m_isFirstRun;

  /// Number of Elemens
  int  m_nElements;

  /// Timer.
  G4Timer* m_timer;

  /// Base of runNumber.
  int m_runNumberBase;

  GsimProcessData* m_processData;

  /// A pointer for Detector Manager.
  GsimDetectorManager* m_DM;
};

inline void GsimRunAction::setRunNumberBase(int runNumberBase)
{
  m_runNumberBase=runNumberBase;
}
#endif

