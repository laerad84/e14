#ifndef E14FsimGenParticleModule_h
#define E14FsimGenParticleModule_h

#include "E14Fsim/E14FsimAnalysisModule.h"

class E14FsimGenParticleModule : public E14FsimAnalysisModule
{
 public:
  E14FsimGenParticleModule();
  virtual ~E14FsimGenParticleModule();

  virtual void initialize();
  virtual void beginOfRun();

  virtual void processEvent();

  virtual void endOfRun();
  virtual void terminate();

 protected:
  double KDecayMome[3];
  double KDecayPos[3];
  double KDecayTime;

  //Pi0 information
  int    Pi0number;
  double Pi0Mome[5][3];
  double Pi0Pos[5][3];
  double Pi0Time[5];
};
#endif
