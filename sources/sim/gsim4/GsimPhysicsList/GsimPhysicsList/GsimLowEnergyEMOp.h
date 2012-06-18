/**
 *  @file
 *  @brief  GsimLowEnergyEMOp
 *  $Id: $
 *  $Log:$
 */
#ifndef GsimLowEnergyEMOp_h
#define GsimLowEnergyEMOp_h

#include "G4VUserPhysicsList.hh"
#include "G4VModularPhysicsList.hh"
#include "globals.hh"

/**
 *  @class GsimLowEnergyEMOp
 *  @brief Low energy EM and optical physics.
 *
 *  This class provides low energy EM and optical physics.
 *  LHEP is used for hadron physics. 
 */

class GsimLowEnergyEMOp: public G4VModularPhysicsList
{
public:
  GsimLowEnergyEMOp();
  ~GsimLowEnergyEMOp();


public:
  virtual void SetCuts();

protected:
  // Construct particle and physics
  virtual void ConstructParticle();
  virtual void ConstructProcess();
    
  // these methods Construct physics processes and register them
  virtual void ConstructGeneral();
  virtual void ConstructEM();
  virtual void ConstructHad();
  virtual void ConstructOp();
  virtual void AddTransportation();

private:
  G4double cutForGamma;
  G4double cutForElectron;
  G4double cutForPositron;
  G4double cutForProton;
  G4double cutForAlpha;
  G4double cutForGenericIon;

  // these methods Construct particles 
  void ConstructBosons();
  void ConstructLeptons();
  void ConstructMesons();
  void ConstructBaryons();
  void ConstructIons();
  void ConstructShortLiveds();

};
#endif //GsimLowEnergyEMOp_h
