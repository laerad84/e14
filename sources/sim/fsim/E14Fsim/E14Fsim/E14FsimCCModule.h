#ifndef E14FsimCCModule_h
#define E14FsimCCModule_h

#include "E14Fsim/E14FsimAnalysisModule.h"

class E14FsimCCModule : public E14FsimAnalysisModule
{
 public:
  E14FsimCCModule();
  virtual ~E14FsimCCModule();

  virtual void processEvent();
  
  void setDetectorID(int id);

 protected:
  int    m_detID;
};

inline void E14FsimCCModule::setDetectorID(int id) {
  m_detID=id;
}
     
#endif
