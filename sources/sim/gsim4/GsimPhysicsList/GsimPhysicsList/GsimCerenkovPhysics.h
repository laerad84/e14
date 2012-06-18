/**
 *  @file
 *  @brief  GsimCerenkovPhysics
 *  $Id: $
 *  $Log:$
 */
#ifndef GsimCerenkovPhysics_h
#define GsimCerenkovPhysics_h

#include "globals.hh"
#include "G4VPhysicsConstructor.hh"

class G4Cerenkov;

class GsimCerenkovPhysics : public G4VPhysicsConstructor
{
public: 
  GsimCerenkovPhysics();
  virtual ~GsimCerenkovPhysics();

public: 
  virtual void ConstructParticle();
  virtual void ConstructProcess();

private:
  ///Even if Cerenkov is not applied one charged particle, return false.
  bool isCerenkovAdded();

  ///Find G4Cerenkov
  G4Cerenkov* findCerenkov();
  
};

#endif //GsimCerenkovPhysics_h
