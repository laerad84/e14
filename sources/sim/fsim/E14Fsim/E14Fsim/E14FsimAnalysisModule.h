#ifndef E14FsimAnalysisModule_h
#define E14FsimAnalysisModule_h
#include "E14Fsim/E14FsimVeto.h"
#include <list>

class E14FsimAnalysisModule
{
 public:
  E14FsimAnalysisModule();
  virtual ~E14FsimAnalysisModule();

  virtual void beginOfRun() {;}
  virtual void processEvent() {;}
  virtual void preClustering() {;}
  virtual void processOneClusterPattern(std::list<int>& ) {;}
  virtual void postClustering() {;}
  virtual void endOfEvent() {;}
  virtual void endOfRun() {;}

  static void clearVetoData();

  
protected:
  static std::list<E14FsimVeto*>      s_vetoList;
  static double  VetoWeightWithoutIneffiGamma;
  static double  VetoWeight;
};
#endif
