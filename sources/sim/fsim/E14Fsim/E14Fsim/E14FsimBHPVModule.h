#ifndef E14FsimBHPVModule_h
#define E14FsimBHPVModule_h

#include "E14Fsim/E14FsimAnalysisModule.h"

class E14FsimBHPVModule : public E14FsimAnalysisModule
{
 public:
  E14FsimBHPVModule();
  virtual ~E14FsimBHPVModule();

  virtual void processEvent();
  
 protected:
  double catcherIneff(double Egamma);
  int    m_detID;
};
#endif
