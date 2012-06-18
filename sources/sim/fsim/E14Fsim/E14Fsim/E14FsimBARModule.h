#ifndef E14FsimBARModule_h
#define E14FsimBARModule_h

#include "E14Fsim/E14FsimAnalysisModule.h"

class E14FsimBARModule : public E14FsimAnalysisModule
{
 public:
  E14FsimBARModule();
  virtual ~E14FsimBARModule();

  virtual void processEvent();
  void setDetectorID(int id);

 protected:
  int    m_detID;
};

inline void E14FsimBARModule::setDetectorID(int id) {
  m_detID=id;
}
     
#endif
