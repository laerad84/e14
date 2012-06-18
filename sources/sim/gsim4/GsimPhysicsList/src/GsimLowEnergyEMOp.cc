#include "GsimPhysicsList/GsimLowEnergyEMOp.h"

#include "G4DataQuestionaire.hh"
#include "G4ProductionCutsTable.hh"

#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"

#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4BosonConstructor.hh"

#include "G4Version.hh"

#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GsimLowEnergyEMOp::GsimLowEnergyEMOp():  G4VUserPhysicsList()
{

  G4DataQuestionaire it(photon, lowenergy, no, radioactive);
  G4cout << "You are using GsimLowEnergyEMOp"<<G4endl;
  G4cout <<G4endl<<G4endl;
  this->defaultCutValue     = 1.0*micrometer; //
  cutForGamma         = this->defaultCutValue;
  cutForElectron      = 1.0*nanometer;
  cutForPositron      = this->defaultCutValue;
  cutForProton        = this->defaultCutValue;
  cutForAlpha         = 1.0*nanometer;
  cutForGenericIon    = 1.0*nanometer;

  this->SetVerboseLevel(0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GsimLowEnergyEMOp::~GsimLowEnergyEMOp()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GsimLowEnergyEMOp::ConstructParticle()
{
  ConstructBosons();
  ConstructLeptons();
  ConstructMesons();
  ConstructBaryons();
  ConstructIons();
  ConstructShortLiveds();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GsimLowEnergyEMOp::ConstructBosons()
{
  G4BosonConstructor pConstructor;
  pConstructor.ConstructParticle();
}

void GsimLowEnergyEMOp::ConstructLeptons()
{
  G4LeptonConstructor pConstructor;
  pConstructor.ConstructParticle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GsimLowEnergyEMOp::ConstructMesons()
{
  G4MesonConstructor pConstructor;
  pConstructor.ConstructParticle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GsimLowEnergyEMOp::ConstructBaryons()
{
  G4BaryonConstructor pConstructor;
  pConstructor.ConstructParticle();
}

void GsimLowEnergyEMOp::ConstructIons()
{
  G4IonConstructor pConstructor;
  pConstructor.ConstructParticle();
}

void GsimLowEnergyEMOp::ConstructShortLiveds()
{
  G4ShortLivedConstructor pConstructor;
  pConstructor.ConstructParticle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GsimLowEnergyEMOp::ConstructProcess()
{
  AddTransportation();
  ConstructEM();
  ConstructOp();
  ConstructHad();
  ConstructGeneral();
  
  G4PhysConstVector::iterator itr;
  for (itr = physicsVector->begin(); itr!= physicsVector->end(); ++itr) {
    (*itr)->ConstructProcess();
  }

}

#include "MaxTimeCuts.hh"
#include "MinEkineCuts.hh"


void GsimLowEnergyEMOp::AddTransportation()
{
  G4VUserPhysicsList::AddTransportation();
}


#if ( G4VERSION_NUMBER < 950 )
// all charged particles
#if ( G4VERSION_NUMBER < 930 )
#include "G4MultipleScattering.hh"
#else
#include "G4eMultipleScattering.hh"
#include "G4MuMultipleScattering.hh"
#include "G4hMultipleScattering.hh"
#endif
  
// gamma
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4LowEnergyRayleigh.hh" 
#include "G4LowEnergyPhotoElectric.hh"
#include "G4LowEnergyCompton.hh"  
#include "G4LowEnergyGammaConversion.hh" 


// e-
#include "G4LowEnergyIonisation.hh" 
#include "G4LowEnergyBremsstrahlung.hh" 

// e+
#include "G4eIonisation.hh" 
#include "G4eBremsstrahlung.hh" 
#include "G4eplusAnnihilation.hh"


// alpha and GenericIon and deuterons, triton, He3:
#include "G4hLowEnergyIonisation.hh"
#include "G4EnergyLossTables.hh"
// hLowEnergyIonisation uses Ziegler 1988 as the default


//muon:
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"
#include "G4MuonMinusCaptureAtRest.hh"



void GsimLowEnergyEMOp::ConstructEM()
{

  G4LowEnergyPhotoElectric* lowePhot = new G4LowEnergyPhotoElectric();
  G4LowEnergyIonisation* loweIon  = new G4LowEnergyIonisation();
  G4LowEnergyBremsstrahlung* loweBrem = new G4LowEnergyBremsstrahlung();
  
  G4double fluorcut = 250*eV;
  lowePhot->SetCutForLowEnSecPhotons(fluorcut);
  loweIon->SetCutForLowEnSecPhotons(fluorcut);
  loweBrem->SetCutForLowEnSecPhotons(fluorcut);


  lowePhot->ActivateAuger(true);
  loweIon->ActivateAuger(true);


  
  this->theParticleIterator->reset();
  
  while( (*(this->theParticleIterator))() ){
    G4ParticleDefinition* particle = this->theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
    G4String particleType = particle->GetParticleType();
    G4double charge = particle->GetPDGCharge();
    if (particleName == "gamma") {
      // gamma
      pmanager->AddDiscreteProcess(new G4LowEnergyRayleigh());
      pmanager->AddDiscreteProcess(lowePhot);
      pmanager->AddDiscreteProcess(new G4LowEnergyCompton());
      pmanager->AddDiscreteProcess(new G4LowEnergyGammaConversion());
      
      //pmanager->AddDiscreteProcess(new G4PhotoElectricEffect);
      //pmanager->AddDiscreteProcess(new G4ComptonScattering);
      //pmanager->AddDiscreteProcess(new G4GammaConversion);
      
    } else if (particleName == "e-") {
      //electron
      // process ordering: AddProcess(name, at rest, along step, post step)
      // -1 = not implemented, then ordering
#if ( G4VERSION_NUMBER < 930 )
      G4MultipleScattering* aMultipleScattering = new G4MultipleScattering();
#else
      G4eMultipleScattering* aMultipleScattering = new G4eMultipleScattering();
#endif
      pmanager->AddProcess(aMultipleScattering,     -1, 1, 1);
      pmanager->AddProcess(loweIon,                 -1, 2, 2);
      pmanager->AddProcess(loweBrem,                -1,-1, 3);
    } else if (particleName == "e+") {
      //positron
#if ( G4VERSION_NUMBER < 930 )
      pmanager->AddProcess(new G4MultipleScattering(),-1, 1, 1);
#else
      pmanager->AddProcess(new G4eMultipleScattering(),-1, 1, 1);
#endif
      pmanager->AddProcess(new G4eIonisation(),       -1, 2, 2);
      pmanager->AddProcess(new G4eBremsstrahlung(),   -1,-1, 3);
      pmanager->AddProcess(new G4eplusAnnihilation(),  0,-1, 4);      
    } else if( particleName == "mu+" || 
               particleName == "mu-"    ) {
      //muon
#if ( G4VERSION_NUMBER < 930 )      
      pmanager->AddProcess(new G4MultipleScattering,-1, 1,1);
#else
      pmanager->AddProcess(new G4MuMultipleScattering,-1, 1,1);
#endif
      pmanager->AddProcess(new G4MuIonisation,      -1, 2,2);
      pmanager->AddProcess(new G4MuBremsstrahlung,  -1, 3,3);
      pmanager->AddProcess(new G4MuPairProduction,  -1, 4,4);
      if( particleName == "mu-" )
	pmanager->AddProcess(new G4MuonMinusCaptureAtRest(), 0,-1,-1);
    } else if (particleName == "proton"     ||
	       particleName == "alpha"      ||
	       particleName == "deuteron"   ||
	       particleName == "triton"     ||
	       particleName == "He3"        ||
	       particleName == "GenericIon" || 
	       (particleType == "nucleus" && charge != 0)) 
      {
	// OBJECT may be dynamically created as either a GenericIon or nucleus
	// G4Nucleus exists and therefore has particle type nucleus
	// genericIon:
#if ( G4VERSION_NUMBER < 930 )
	G4MultipleScattering* aMultipleScattering = new G4MultipleScattering();
#else
        G4hMultipleScattering* aMultipleScattering = new G4hMultipleScattering();
#endif
        G4hLowEnergyIonisation* ahadronLowEIon = new G4hLowEnergyIonisation();
	ahadronLowEIon->ActivateAugerElectronProduction(true);
	pmanager->AddProcess(aMultipleScattering,-1,1,1);
	pmanager->AddProcess(ahadronLowEIon,-1,2,2); 
        // ahadronLowEIon->SetNuclearStoppingOff() ;
	//        ahadronLowEIon->SetNuclearStoppingPowerModel("ICRU_R49") ;
	//        ahadronLowEIon->SetNuclearStoppingOn() ;
	
        //fluorescence switch off for hadrons (for now) PIXE:
        ahadronLowEIon->SetFluorescence(false);
      } else if ((!particle->IsShortLived()) &&
		 (particle->GetPDGCharge() != 0.0) && 
		 (particle->GetParticleName() != "chargedgeantino")) {
	
	//all others charged particles except geantino
#if ( G4VERSION_NUMBER < 930 )
        G4MultipleScattering* aMultipleScattering = new G4MultipleScattering();
#else
	G4hMultipleScattering* aMultipleScattering = new G4hMultipleScattering();
#endif
	G4hLowEnergyIonisation* ahadronLowEIon = new G4hLowEnergyIonisation();
	ahadronLowEIon->ActivateAugerElectronProduction(true);
	pmanager->AddProcess(aMultipleScattering,-1,1,1);
	pmanager->AddProcess(ahadronLowEIon,       -1,2,2);      
	//      pmanager->AddProcess(new G4hIonisation(),       -1,2,2);      
      }
  }
}
#else
//G4VERSION_NUMBER>=950

// all charged particle
#include "G4eMultipleScattering.hh"
#include "G4MuMultipleScattering.hh"
#include "G4hMultipleScattering.hh"
  
// gamma. Use Livermore models
#include "G4PhotoElectricEffect.hh"
#include "G4LivermorePhotoElectricModel.hh"
#include "G4ComptonScattering.hh"
#include "G4LivermoreComptonModel.hh"
#include "G4GammaConversion.hh"
#include "G4LivermoreGammaConversionModel.hh"
#include "G4RayleighScattering.hh" 
#include "G4LivermoreRayleighModel.hh"


// e-
#include "G4eMultipleScattering.hh"
#include "G4UniversalFluctuation.hh"
#include "G4UrbanMscModel93.hh"

#include "G4eIonisation.hh"
#include "G4LivermoreIonisationModel.hh"

#include "G4eBremsstrahlung.hh"
#include "G4LivermoreBremsstrahlungModel.hh"

// e+
#include "G4eplusAnnihilation.hh"


// alpha and GenericIon and deuterons, triton, He3:
#include "G4ionIonisation.hh"
#include "G4hIonisation.hh"
#include "G4hBremsstrahlung.hh"
//
#include "G4IonParametrisedLossModel.hh"
#include "G4NuclearStopping.hh"
#include "G4EnergyLossTables.hh"

// msc models
#include "G4UrbanMscModel93.hh"

//muon:
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"
#include "G4MuonMinusCaptureAtRest.hh"


void GsimLowEnergyEMOp::ConstructEM()
{

  // models & processes:
  // Use Livermore models up to 20 MeV, and standard 
  // models for higher energy
  G4double LivermoreHighEnergyLimit = 20*MeV;
  
  this->theParticleIterator->reset();
  
  while( (*(this->theParticleIterator))() ){
    G4ParticleDefinition* particle = this->theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
    G4String particleType = particle->GetParticleType();
    G4double charge = particle->GetPDGCharge();
    if (particleName == "gamma") {
      // gamma
      G4PhotoElectricEffect* thePhotoElectricEffect = new G4PhotoElectricEffect();
      G4LivermorePhotoElectricModel* theLivermorePhotoElectricModel = 
        new G4LivermorePhotoElectricModel();
      theLivermorePhotoElectricModel->SetHighEnergyLimit(LivermoreHighEnergyLimit);
      thePhotoElectricEffect->AddEmModel(0, theLivermorePhotoElectricModel);
      pmanager->AddDiscreteProcess(thePhotoElectricEffect);
      
      G4ComptonScattering* theComptonScattering = new G4ComptonScattering();
      G4LivermoreComptonModel* theLivermoreComptonModel = 
        new G4LivermoreComptonModel();
      theLivermoreComptonModel->SetHighEnergyLimit(LivermoreHighEnergyLimit);
      theComptonScattering->AddEmModel(0, theLivermoreComptonModel);
      pmanager->AddDiscreteProcess(theComptonScattering);
      
      G4GammaConversion* theGammaConversion = new G4GammaConversion();
      G4LivermoreGammaConversionModel* theLivermoreGammaConversionModel = 
        new G4LivermoreGammaConversionModel();
      theLivermoreGammaConversionModel->SetHighEnergyLimit(LivermoreHighEnergyLimit);
      theGammaConversion->AddEmModel(0, theLivermoreGammaConversionModel);
      pmanager->AddDiscreteProcess(theGammaConversion);
      
      G4RayleighScattering* theRayleigh = new G4RayleighScattering();
      G4LivermoreRayleighModel* theRayleighModel = new G4LivermoreRayleighModel();
      theRayleighModel->SetHighEnergyLimit(LivermoreHighEnergyLimit);
      theRayleigh->AddEmModel(0, theRayleighModel);
      pmanager->AddDiscreteProcess(theRayleigh);

    } else if (particleName == "e-") {
      
      //electron
      // process ordering: AddProcess(name, at rest, along step, post step)
      // -1 = not implemented, then ordering
      G4eMultipleScattering* msc = new G4eMultipleScattering();     
      msc->AddEmModel(0, new G4UrbanMscModel93());
      msc->SetStepLimitType(fUseDistanceToBoundary);
      pmanager->AddProcess(msc,                   -1, 1, 1);
      
      // Ionisation
      G4eIonisation* eIoni = new G4eIonisation();
      G4LivermoreIonisationModel* theIoniLivermore = new
        G4LivermoreIonisationModel();
      theIoniLivermore->SetHighEnergyLimit(1*MeV); 
      eIoni->AddEmModel(0, theIoniLivermore, new G4UniversalFluctuation() );
      eIoni->SetStepFunction(0.2, 100*um); //     
      pmanager->AddProcess(eIoni,                 -1, 2, 2);
      
      // Bremsstrahlung
      G4eBremsstrahlung* eBrem = new G4eBremsstrahlung();
      G4LivermoreBremsstrahlungModel* theBremLivermore = new
        G4LivermoreBremsstrahlungModel();
      theBremLivermore->SetHighEnergyLimit(LivermoreHighEnergyLimit);
      eBrem->AddEmModel(0, theBremLivermore);
      pmanager->AddProcess(eBrem, -1,-3, 3);
    } else if (particleName == "e+") {
      //positron
      G4eMultipleScattering* msc = new G4eMultipleScattering();
      msc->AddEmModel(0, new G4UrbanMscModel93());      
      msc->SetStepLimitType(fUseDistanceToBoundary);
      pmanager->AddProcess(msc,                   -1, 1, 1);
      G4eIonisation* eIoni = new G4eIonisation();
      eIoni->SetStepFunction(0.2, 100*um);      
      pmanager->AddProcess(eIoni,                 -1, 2, 2);
      pmanager->AddProcess(new G4eBremsstrahlung, -1,-3, 3);      
      pmanager->AddProcess(new G4eplusAnnihilation,0,-1, 4);

    } else if( particleName == "mu+" || 
               particleName == "mu-"    ) {
      //muon  
      G4MuMultipleScattering* aMultipleScattering = new G4MuMultipleScattering();
      pmanager->AddProcess(aMultipleScattering,           -1, 1, 1);
      pmanager->AddProcess(new G4MuIonisation(),          -1, 2, 2);
      pmanager->AddProcess(new G4MuBremsstrahlung(),      -1,-1, 3);
      pmanager->AddProcess(new G4MuPairProduction(),      -1,-1, 4);
      if( particleName == "mu-" )
        pmanager->AddProcess(new G4MuonMinusCaptureAtRest(), 0,-1,-1);
    } else if (particleName == "GenericIon") {
      pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
      G4ionIonisation* ionIoni = new G4ionIonisation();
      ionIoni->SetEmModel(new G4IonParametrisedLossModel());
      ionIoni->SetStepFunction(0.1, 10*um);
      pmanager->AddProcess(ionIoni,                   -1, 2, 2);
      pmanager->AddProcess(new G4NuclearStopping(),   -1, 3,-1);        
    } else if (particleName == "alpha" || particleName == "He3") {
      //MSC, ion-Ionisation, Nuclear Stopping
      pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
      
      G4ionIonisation* ionIoni = new G4ionIonisation();
      ionIoni->SetStepFunction(0.1, 20*um);
      pmanager->AddProcess(ionIoni,                   -1, 2, 2);
      pmanager->AddProcess(new G4NuclearStopping(),   -1, 3,-1);
    } else if (particleName == "proton"     ||    
               particleName == "deuteron"   ||
               particleName == "triton"     ||
               particleName == "pi+" ||
               particleName == "pi-" ||
               particleName == "kaon+" ||
               particleName == "kaon-") {
      //MSC, h-ionisation, bremsstrahlung
      pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);      
      G4hIonisation* hIoni = new G4hIonisation();
      hIoni->SetStepFunction(0.2, 50*um);
      pmanager->AddProcess(hIoni,                     -1, 2, 2);      
      pmanager->AddProcess(new G4hBremsstrahlung,     -1,-3, 3);    
    } else if ((!particle->IsShortLived()) &&
               (particle->GetPDGCharge() != 0.0) && 
               (particle->GetParticleName() != "chargedgeantino")) {
      pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4hIonisation,         -1, 2, 2);
    }
  }
}

//G4VERSION_NUMBER>=950
#endif

// Optical Process
#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4OpWLS.hh"

void GsimLowEnergyEMOp::ConstructOp()
{

  G4Cerenkov* theCerenkovProcess = new G4Cerenkov("Cerenkov");
  theCerenkovProcess->SetMaxNumPhotonsPerStep(300); // which limit the step size
  theCerenkovProcess->SetTrackSecondariesFirst(true); // for firster memory release
    
  
  G4Scintillation* theScintProcessDef
    = new G4Scintillation("Scintillation");
  theScintProcessDef->SetTrackSecondariesFirst(true);
  theScintProcessDef->SetScintillationYieldFactor(1.0); //
  theScintProcessDef->SetScintillationExcitationRatio(0.0); //

  G4Scintillation* theScintProcessAlpha = new G4Scintillation("Scintillation");
  theScintProcessAlpha->SetTrackSecondariesFirst(true);
  theScintProcessAlpha->SetScintillationYieldFactor(1.1);
  theScintProcessAlpha->SetScintillationExcitationRatio(1.0);

  G4Scintillation* theScintProcessNuc = new G4Scintillation("Scintillation");
  theScintProcessNuc->SetTrackSecondariesFirst(true);
  theScintProcessNuc->SetScintillationYieldFactor(0.2);
  theScintProcessNuc->SetScintillationExcitationRatio(1.0);

  G4OpAbsorption* theAbsorptionProcess     = new G4OpAbsorption();
  G4OpRayleigh* theRayleighScatteringProcess = new G4OpRayleigh();

  G4OpBoundaryProcess* theBoundaryProcess  = new G4OpBoundaryProcess();
  G4OpticalSurfaceModel themodel = unified;
  theBoundaryProcess->SetModel(themodel);
  theBoundaryProcess->SetVerboseLevel(0);

  G4OpWLS* theWLSProcess=new G4OpWLS();
  theWLSProcess->SetVerboseLevel(0);

  this->theParticleIterator->reset();
  while( (*(this->theParticleIterator))() ) {
    G4ParticleDefinition* particle = this->theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
    
    if(theCerenkovProcess) {
      if (theCerenkovProcess->IsApplicable(*particle)) {
#if ( G4VERSION_NUMBER >= 910 )
	pmanager->AddProcess(theCerenkovProcess);
        pmanager->SetProcessOrdering(theCerenkovProcess,idxPostStep);
#else
	pmanager->AddContinuousProcess(theCerenkovProcess);
#endif
      }
    }
    if (theScintProcessDef->IsApplicable(*particle)) {
      if(particle->GetParticleName() == "GenericIon") {
	pmanager->AddProcess(theScintProcessNuc); // AtRestDiscrete
	pmanager->SetProcessOrderingToLast(theScintProcessNuc,idxAtRest);
	pmanager->SetProcessOrderingToLast(theScintProcessNuc,idxPostStep);
      } else if(particle->GetParticleName() == "alpha") {
	pmanager->AddProcess(theScintProcessAlpha);
	pmanager->SetProcessOrderingToLast(theScintProcessAlpha,idxAtRest);
	pmanager->SetProcessOrderingToLast(theScintProcessAlpha,idxPostStep);
      } else {
	pmanager->AddProcess(theScintProcessDef);
	pmanager->SetProcessOrderingToLast(theScintProcessDef,idxAtRest);
	pmanager->SetProcessOrderingToLast(theScintProcessDef,idxPostStep);
      }
    }
    
    if (particleName == "opticalphoton") {
      pmanager->AddDiscreteProcess(theAbsorptionProcess);
      pmanager->AddDiscreteProcess(theRayleighScatteringProcess);
      pmanager->AddDiscreteProcess(theBoundaryProcess);
      pmanager->AddDiscreteProcess(theWLSProcess);
    }
  }
}

// Hadronic processes ////////////////////////////////////////////////////////

#include "G4HadronElasticProcess.hh"
#include "G4HadronFissionProcess.hh"
#include "G4HadronCaptureProcess.hh"

// Inelastic processes:
#include "G4PionPlusInelasticProcess.hh"
#include "G4PionMinusInelasticProcess.hh"
#include "G4KaonPlusInelasticProcess.hh"
#include "G4KaonZeroSInelasticProcess.hh"
#include "G4KaonZeroLInelasticProcess.hh"
#include "G4KaonMinusInelasticProcess.hh"
#include "G4ProtonInelasticProcess.hh"
#include "G4AntiProtonInelasticProcess.hh"
#include "G4NeutronInelasticProcess.hh"
#include "G4AntiNeutronInelasticProcess.hh"
#include "G4DeuteronInelasticProcess.hh"
#include "G4TritonInelasticProcess.hh"
#include "G4AlphaInelasticProcess.hh"

// Low-energy Models: < 20GeV
#include "G4LElastic.hh"
#include "G4LEPionPlusInelastic.hh"
#include "G4LEPionMinusInelastic.hh"
#include "G4LEKaonPlusInelastic.hh"
#include "G4LEKaonZeroSInelastic.hh"
#include "G4LEKaonZeroLInelastic.hh"
#include "G4LEKaonMinusInelastic.hh"
#include "G4LEProtonInelastic.hh"
#include "G4LEAntiProtonInelastic.hh"
#include "G4LENeutronInelastic.hh"
#include "G4LEAntiNeutronInelastic.hh"
#include "G4LEDeuteronInelastic.hh"
#include "G4LETritonInelastic.hh"
#include "G4LEAlphaInelastic.hh"

// High-energy Models: >20 GeV
#include "G4HEPionPlusInelastic.hh"
#include "G4HEPionMinusInelastic.hh"
#include "G4HEKaonPlusInelastic.hh"
#include "G4HEKaonZeroInelastic.hh"
#include "G4HEKaonZeroInelastic.hh"
#include "G4HEKaonMinusInelastic.hh"
#include "G4HEProtonInelastic.hh"
#include "G4HEAntiProtonInelastic.hh"
#include "G4HENeutronInelastic.hh"
#include "G4HEAntiNeutronInelastic.hh"

// Neutron high-precision models: <20 MeV
#include "G4LCapture.hh"
#include "G4LFission.hh"

// Stopping processes
#include "G4PiMinusAbsorptionAtRest.hh"
#include "G4KaonMinusAbsorptionAtRest.hh"
#include "G4AntiProtonAnnihilationAtRest.hh"
#include "G4AntiNeutronAnnihilationAtRest.hh"


// ConstructHad()
// Makes discrete physics processes for the hadrons, at present limited
// to those particles with GHEISHA interactions (INTRC > 0).
// The processes are: Elastic scattering and Inelastic scattering.

void GsimLowEnergyEMOp::ConstructHad() 
{
  G4HadronElasticProcess* theElasticProcess = new G4HadronElasticProcess;
  G4LElastic* theElasticModel = new G4LElastic;
  theElasticProcess->RegisterMe(theElasticModel);
  
  this->theParticleIterator->reset();
  while ((*(this->theParticleIterator))()) 
    {
      G4ParticleDefinition* particle = this->theParticleIterator->value();
      G4ProcessManager* pmanager = particle->GetProcessManager();
      G4String particleName = particle->GetParticleName();

      if (particleName == "pi+") 
	{
	  pmanager->AddDiscreteProcess(theElasticProcess);
	  G4PionPlusInelasticProcess* theInelasticProcess = 
	    new G4PionPlusInelasticProcess("inelastic");
	  G4LEPionPlusInelastic* theLEInelasticModel = 
	    new G4LEPionPlusInelastic;
	  theInelasticProcess->RegisterMe(theLEInelasticModel);
	  G4HEPionPlusInelastic* theHEInelasticModel = 
	    new G4HEPionPlusInelastic;
	  theInelasticProcess->RegisterMe(theHEInelasticModel);
	  pmanager->AddDiscreteProcess(theInelasticProcess);
	} 

      else if (particleName == "pi-") 
	{
	  pmanager->AddDiscreteProcess(theElasticProcess);
	  G4PionMinusInelasticProcess* theInelasticProcess = 
	    new G4PionMinusInelasticProcess("inelastic");
	  G4LEPionMinusInelastic* theLEInelasticModel = 
	    new G4LEPionMinusInelastic;
	  theInelasticProcess->RegisterMe(theLEInelasticModel);
	  G4HEPionMinusInelastic* theHEInelasticModel = 
	    new G4HEPionMinusInelastic;
	  theInelasticProcess->RegisterMe(theHEInelasticModel);
	  pmanager->AddDiscreteProcess(theInelasticProcess);
	  G4String prcNam;
	  pmanager->AddRestProcess(new G4PiMinusAbsorptionAtRest, ordDefault);
	}
      
      else if (particleName == "kaon+") 
	{
	  pmanager->AddDiscreteProcess(theElasticProcess);
	  G4KaonPlusInelasticProcess* theInelasticProcess = 
	    new G4KaonPlusInelasticProcess("inelastic");
	  G4LEKaonPlusInelastic* theLEInelasticModel = 
	    new G4LEKaonPlusInelastic;
	  theInelasticProcess->RegisterMe(theLEInelasticModel);
	  G4HEKaonPlusInelastic* theHEInelasticModel = 
	    new G4HEKaonPlusInelastic;
	  theInelasticProcess->RegisterMe(theHEInelasticModel);
	  pmanager->AddDiscreteProcess(theInelasticProcess);
	}
      
      else if (particleName == "kaon0S") 
	{
	  pmanager->AddDiscreteProcess(theElasticProcess);
	  G4KaonZeroSInelasticProcess* theInelasticProcess = 
	    new G4KaonZeroSInelasticProcess("inelastic");
	  G4LEKaonZeroSInelastic* theLEInelasticModel = 
	    new G4LEKaonZeroSInelastic;
	  theInelasticProcess->RegisterMe(theLEInelasticModel);
	  G4HEKaonZeroInelastic* theHEInelasticModel = 
	    new G4HEKaonZeroInelastic;
	  theInelasticProcess->RegisterMe(theHEInelasticModel);
	  pmanager->AddDiscreteProcess(theInelasticProcess);
	}

      else if (particleName == "kaon0L") 
	{
	  pmanager->AddDiscreteProcess(theElasticProcess);
	  G4KaonZeroLInelasticProcess* theInelasticProcess = 
	    new G4KaonZeroLInelasticProcess("inelastic");
	  G4LEKaonZeroLInelastic* theLEInelasticModel = 
	    new G4LEKaonZeroLInelastic;
	  theInelasticProcess->RegisterMe(theLEInelasticModel);
	  G4HEKaonZeroInelastic* theHEInelasticModel = 
	    new G4HEKaonZeroInelastic;
	  theInelasticProcess->RegisterMe(theHEInelasticModel);
	  pmanager->AddDiscreteProcess(theInelasticProcess);
	}

      else if (particleName == "kaon-") 
	{
	  pmanager->AddDiscreteProcess(theElasticProcess);
	  G4KaonMinusInelasticProcess* theInelasticProcess = 
	    new G4KaonMinusInelasticProcess("inelastic");
	  G4LEKaonMinusInelastic* theLEInelasticModel = 
	    new G4LEKaonMinusInelastic;
	  theInelasticProcess->RegisterMe(theLEInelasticModel);
	  G4HEKaonMinusInelastic* theHEInelasticModel = 
	    new G4HEKaonMinusInelastic;
	  theInelasticProcess->RegisterMe(theHEInelasticModel);
	  pmanager->AddDiscreteProcess(theInelasticProcess);
	  pmanager->AddRestProcess(new G4KaonMinusAbsorptionAtRest, ordDefault);
	}

      else if (particleName == "proton") 
	{
	  pmanager->AddDiscreteProcess(theElasticProcess);
	  G4ProtonInelasticProcess* theInelasticProcess = 
	    new G4ProtonInelasticProcess("inelastic");
	  G4LEProtonInelastic* theLEInelasticModel = new G4LEProtonInelastic;
	  theInelasticProcess->RegisterMe(theLEInelasticModel);
	  G4HEProtonInelastic* theHEInelasticModel = new G4HEProtonInelastic;
	  theInelasticProcess->RegisterMe(theHEInelasticModel);
	  pmanager->AddDiscreteProcess(theInelasticProcess);
	}

      else if (particleName == "anti_proton") 
	{
	  pmanager->AddDiscreteProcess(theElasticProcess);
	  G4AntiProtonInelasticProcess* theInelasticProcess = 
	    new G4AntiProtonInelasticProcess("inelastic");
	  G4LEAntiProtonInelastic* theLEInelasticModel = 
	    new G4LEAntiProtonInelastic;
	  theInelasticProcess->RegisterMe(theLEInelasticModel);
	  G4HEAntiProtonInelastic* theHEInelasticModel = 
	    new G4HEAntiProtonInelastic;
	  theInelasticProcess->RegisterMe(theHEInelasticModel);
	  pmanager->AddDiscreteProcess(theInelasticProcess);
	}

      else if (particleName == "neutron") {
	// elastic scattering
	pmanager->AddDiscreteProcess(theElasticProcess);
	// inelastic scattering
	G4NeutronInelasticProcess* theInelasticProcess =
	  new G4NeutronInelasticProcess("inelastic");
	G4LENeutronInelastic* theLENeutronModel = new G4LENeutronInelastic;
	theInelasticProcess->RegisterMe(theLENeutronModel);
	G4HENeutronInelastic* theHENeutronModel = new G4HENeutronInelastic();
	theInelasticProcess->RegisterMe(theHENeutronModel);
	pmanager->AddDiscreteProcess(theInelasticProcess);
	// capture
	G4HadronCaptureProcess* theCaptureProcess =
	  new G4HadronCaptureProcess;
	G4LCapture* theCaptureModel = new G4LCapture;
	theCaptureProcess->RegisterMe(theCaptureModel);
	pmanager->AddDiscreteProcess(theCaptureProcess);
	//fission
	G4HadronFissionProcess* theFissionProcess =
	  new G4HadronFissionProcess;
        G4LFission* theFissionModel = new G4LFission;
        theFissionProcess->RegisterMe(theFissionModel);
        pmanager->AddDiscreteProcess(theFissionProcess);
      }
      else if (particleName == "anti_neutron") 
	{
	  pmanager->AddDiscreteProcess(theElasticProcess);
	  G4AntiNeutronInelasticProcess* theInelasticProcess = 
	    new G4AntiNeutronInelasticProcess("inelastic");
	  G4LEAntiNeutronInelastic* theLEInelasticModel = 
	    new G4LEAntiNeutronInelastic;
	  theInelasticProcess->RegisterMe(theLEInelasticModel);
	  G4HEAntiNeutronInelastic* theHEInelasticModel = 
	    new G4HEAntiNeutronInelastic;
	  theInelasticProcess->RegisterMe(theHEInelasticModel);
	  pmanager->AddDiscreteProcess(theInelasticProcess);
	}

      else if (particleName == "deuteron") 
	{
	  pmanager->AddDiscreteProcess(theElasticProcess);
	  G4DeuteronInelasticProcess* theInelasticProcess = 
	    new G4DeuteronInelasticProcess("inelastic");
	  G4LEDeuteronInelastic* theLEInelasticModel = 
	    new G4LEDeuteronInelastic;
	  theInelasticProcess->RegisterMe(theLEInelasticModel);
	  pmanager->AddDiscreteProcess(theInelasticProcess);
	}
      
      else if (particleName == "triton") 
	{
	  pmanager->AddDiscreteProcess(theElasticProcess);
	  G4TritonInelasticProcess* theInelasticProcess = 
	    new G4TritonInelasticProcess("inelastic");
	  G4LETritonInelastic* theLEInelasticModel = 
	    new G4LETritonInelastic;
	  theInelasticProcess->RegisterMe(theLEInelasticModel);
	  pmanager->AddDiscreteProcess(theInelasticProcess);
	}

      else if (particleName == "alpha") 
	{
	  pmanager->AddDiscreteProcess(theElasticProcess);
	  G4AlphaInelasticProcess* theInelasticProcess = 
	    new G4AlphaInelasticProcess("inelastic");
	  G4LEAlphaInelastic* theLEInelasticModel = 
	    new G4LEAlphaInelastic;
	  theInelasticProcess->RegisterMe(theLEInelasticModel);
	  pmanager->AddDiscreteProcess(theInelasticProcess);
	}
      
    }
}


#include "G4Decay.hh"
#include "G4RadioactiveDecay.hh"
#include "G4IonTable.hh"
#include "G4Ions.hh"

void GsimLowEnergyEMOp::ConstructGeneral()
{
  // Add Decay Process
  G4Decay* theDecayProcess = new G4Decay();
  this->theParticleIterator->reset();
  while( (*(this->theParticleIterator))() ) {
    G4ParticleDefinition* particle = this->theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    if (theDecayProcess->IsApplicable(*particle)) { 
      pmanager ->AddProcess(theDecayProcess);
      // set ordering for PostStepDoIt and AtRestDoIt
      pmanager ->SetProcessOrdering(theDecayProcess, idxPostStep);
      pmanager ->SetProcessOrdering(theDecayProcess, idxAtRest);
    }
  }

  // Declare radioactive decay to the GenericIon in the IonTable.
  const G4IonTable *theIonTable = 
    G4ParticleTable::GetParticleTable()->GetIonTable();
  G4RadioactiveDecay *theRadioactiveDecay = new G4RadioactiveDecay();

  for (G4int i=0; i<theIonTable->Entries(); i++) {
    G4String particleName = theIonTable->GetParticle(i)->GetParticleName();
    G4String particleType = theIonTable->GetParticle(i)->GetParticleType();
    if (particleName == "GenericIon") {
      G4ProcessManager* pmanager = 
	theIonTable->GetParticle(i)->GetProcessManager();
      pmanager ->AddProcess(theRadioactiveDecay);
      pmanager ->SetProcessOrdering(theRadioactiveDecay, idxPostStep);
      pmanager ->SetProcessOrdering(theRadioactiveDecay, idxAtRest);
    } 
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GsimLowEnergyEMOp::SetCuts()
{
  //special for low energy physics
  G4double lowlimit=250*eV;  
  G4ProductionCutsTable * aPCTable = G4ProductionCutsTable::GetProductionCutsTable();
  aPCTable->SetEnergyRange(lowlimit,100*GeV);
   
  // set cut values for gamma at first and for e- second and next for e+,
  // because some processes for e+/e- need cut values for gamma 
  this->SetCutValue(cutForGamma, "gamma");
  this->SetCutValue(cutForElectron, "e-");
  this->SetCutValue(cutForPositron, "e+");
  
  //G4VUserPhysicsList::SetCutsWithDefault method sets 
  //the default cut value for all particle types 
  //
  SetCutsWithDefault();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

