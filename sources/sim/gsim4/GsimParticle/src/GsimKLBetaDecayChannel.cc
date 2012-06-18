/**
 *  @file
 *  @brief  GsimKLBetaDecayChannel
 *  $Id: 
 *  $Log: 
 */

#include "GsimParticle/GsimKLBetaDecayChannel.h"

#include "CLHEP/Random/Randomize.h"
#include "CLHEP/Vector/Rotation.h"

#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ThreeVector.hh"
#include "G4DynamicParticle.hh"
#include "G4DecayProducts.hh"

GsimKLBetaDecayChannel::GsimKLBetaDecayChannel(const G4String& theParentName,
						       G4double        theBR,
					       const G4String& theKname,
					       const G4String& theEname,
					       const G4String& theNuname)
  :G4VDecayChannel("KLbeta Decay",theParentName,
		   theBR,  3,
		   theKname,  theEname,  theNuname)
{
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = 0;

  particle = particleTable->FindParticle("kaon0L");
  double mKL=particle->GetPDGMass();
  
  particle = particleTable->FindParticle("kaon+");
  double mKP=particle->GetPDGMass();
  
  particle = particleTable->FindParticle("e-");
  double mE=particle->GetPDGMass();
  
  particle = particleTable->FindParticle("nu_e");
  double mNu=particle->GetPDGMass();


  m_event = new TGenPhaseSpace();
  
  Double_t masses[3];
  masses[0]= mKP/GeV;
  masses[1]= mE/GeV;
  masses[2]= mNu/GeV;
  TLorentzVector W(0,0,0,mKL/GeV);
  m_event->SetDecay(W, 3, masses);

  m_wmax=2.18;
}
  
GsimKLBetaDecayChannel::~GsimKLBetaDecayChannel()
{
  delete m_event;
}


G4DecayProducts* GsimKLBetaDecayChannel::DecayIt(G4double)
{
  
  if (parent == 0) {
    FillParent();
  }

  if (daughters == 0) {
    FillDaughters();
  }
  
  generate();

  G4ThreeVector* direction = new G4ThreeVector(1.0,0.0,0.0);
  G4DynamicParticle * parentparticle = new G4DynamicParticle( parent, *direction, 0.0);
  delete direction;

  //create G4Decayproducts
  G4DecayProducts *products = new G4DecayProducts(*parentparticle);
  delete parentparticle;


  for(int k=0;k<3;k++) {
    TLorentzVector *lv = m_event->GetDecay(k);
    G4ThreeVector momentum =  G4ThreeVector(
					    lv->Px()*GeV,
					    lv->Py()*GeV,
					    lv->Pz()*GeV
					    );
    G4DynamicParticle * daughterparticle 
      = new G4DynamicParticle( daughters[k], momentum);
    products->PushProducts(daughterparticle);
  }
  
  return products;
}




void GsimKLBetaDecayChannel::generate()
{
  Double_t weight=0;
  Double_t rW=1;
  
  while(rW>weight) {
    weight = m_event->Generate();
    TLorentzVector *pe = m_event->GetDecay(1);
    TLorentzVector *pnu= m_event->GetDecay(2);
    
    Double_t ang=pnu->Angle(pe->Vect());
    Double_t proj=pe->Beta()*TMath::Cos(ang);
    Double_t me=pe->E()*1e3*pnu->E()*1e3*(1+proj);
    
    weight=weight*me;

    if(weight>m_wmax) {
      //Warning
    }
    
    rW=CLHEP::RandFlat::shoot(0.,m_wmax);
  }
}
