/**
 *  @file
 *  @brief  GsimKPiNuNuDecayChannel
 *  $Id: GsimKPiNuNuDecayChannel.cc,v 1.3 2006/12/06 19:25:52 nanjo Exp $
 *  $Log: GsimKPiNuNuDecayChannel.cc,v $
 *  Revision 1.3  2006/12/06 19:25:52  nanjo
 *  CVS variables.
 *
 */

#include "GsimParticle/GsimKPiNuNuDecayChannel.h"

#include "CLHEP/Random/Randomize.h"
#include "CLHEP/Vector/Rotation.h"

#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ThreeVector.hh"
#include "G4DynamicParticle.hh"
#include "G4DecayProducts.hh"

GsimKPiNuNuDecayChannel::GsimKPiNuNuDecayChannel(const G4String& theParentName,
						       G4double        theBR,
						       const G4String& thePionName1,
						       const G4String& thePionName2,
						       const G4String& thePionName3)
  :G4VDecayChannel("KPiNuNu Decay",theParentName,
		   theBR,  3,
		   thePionName1,  thePionName2,  thePionName3)
{
  pLambda  = 0.0284;// PDG 2006 (2.84+-0.04)x10^-2
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = 0;
  
  particle = particleTable->FindParticle("pi0");
  mp=particle->GetPDGMass();

  particle = particleTable->FindParticle("kaon0L");
  mk=particle->GetPDGMass();

  emax=(mk*mk+mp*mp)/(2*mk)-1.*eV;   // 1 eV below the max to avoid NAN
  emin=mp+1.*eV;                     // 1 eV above the max to avoid NAN
  wmax=GetKPi0EnergyWeight(emax/GeV); 
}
  
GsimKPiNuNuDecayChannel::~GsimKPiNuNuDecayChannel()
{
  ;
}


G4DecayProducts* GsimKPiNuNuDecayChannel::DecayIt(G4double)
{
  
  if (parent == 0) {
    FillParent();
  }

  if (daughters == 0) {
    FillDaughters();
  }
  
  double rpie=0;
  double rweight=1;
  double wfunc=0.;
  while ( rweight > wfunc ) {
    rpie = CLHEP::RandFlat::shoot(emin,emax);
    wfunc=GetKPi0EnergyWeight(rpie/GeV);
    rweight = CLHEP::RandFlat::shoot(0.,wmax);
  }

  double pi0e=rpie;
  double pi0mom=std::sqrt(pi0e*pi0e-mp*mp);

  G4ThreeVector* direction = new G4ThreeVector(1.0,0.0,0.0);
  G4DynamicParticle * parentparticle = new G4DynamicParticle( parent, *direction, 0.0);
  delete direction;

  //create G4Decayproducts
  G4DecayProducts *products = new G4DecayProducts(*parentparticle);
  delete parentparticle;

  double pnu=(mk-pi0e)/2.;
  double pnuz=-pi0mom/2.;
  double pnux=pnu*pnu-pnuz*pnuz;
  if(pnux>0) pnux=std::sqrt(pnux);
  else       pnux=0;
  G4ThreeVector momentum[3];
  
  momentum[0] =  G4ThreeVector(0,0,pi0mom);
  momentum[1] =  G4ThreeVector( pnux,0,pnuz);
  momentum[2] =  G4ThreeVector(-pnux,0,pnuz);

  double psi  =  CLHEP::RandFlat::shoot(0.,2*M_PI)*rad;
  double phi   = CLHEP::RandFlat::shoot(0.,2*M_PI)*rad;
  double theta = (std::acos(2.*CLHEP::RandFlat::shoot(0.,1.)-1.));


  CLHEP::HepRotation rot(phi,theta,psi);

  for(int k=0;k<3;k++) {
    momentum[k]=rot*momentum[k];
    G4DynamicParticle * daughterparticle 
      = new G4DynamicParticle( daughters[k], momentum[k]);
    products->PushProducts(daughterparticle);
  }
  
  return products;
}


/**********************************************************************
 pi0 energy function in Kl->pi0nunubar decay
 This function is defined in mp=0.1349766 <= x <= (mk*mk+mp*mp)/(2*mk)
                                               = .26713990553171566815
**********************************************************************/
double GsimKPiNuNuDecayChannel::GetKPi0EnergyWeight( double pi0e ){

  double MK=mk/GeV;
  double MP=mp/GeV;

  //double lp=0.032; // from Ke3 and Kmu3 experiment
  double lp=pLambda;

  //inside sqrt check;
  double q=(MK*MK+MP*MP-2*MK*pi0e);
  if(q>0) q=sqrt(q);
  else return -1;
    
  double l=((MK*MK+MP*MP-q*q)*(MK*MK+MP*MP-q*q)-4*(MK*MK)*(MP*MP));
  if(l>0) l=sqrt(l);
  else return -1;
  
  double f=1+lp*(q*q)/(MP*MP);
  //////////////////////////////////////////////////////////////////////////
  //Wrong formula intorduced by E391
  //double kpnne=l*(f*f)*((MK*MK-MP*MP-q*q)*(MK*MK-MP*MP-q*q)
  //                      -2./(q*q)*(((q*q)*(l*l))/3.+((MP*MP)*(q*q*q*q))));
  //////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////
  //Corrected formula according to PRL 53,2289,
  //  Neutrino-Mass Limits from K+->pi+nunubar Decay
  //   by N.G.Deshpande and G.Eilam 
  //double kpnne=l*(f*f)*(-2.*q*q*MP*MP+(MK*MK-MP*MP-q*q)*(MK*MK-MP*MP-q*q)
  //                      -2./(q*q)*(((q*q)*(l*l))/3.+((MP*MP)*(q*q*q*q))));
  //////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////
  //Simplified formula
  double kpnne=l*(f*f)*
    (
     +(MK*MK-MP*MP-q*q)*(MK*MK-MP*MP-q*q)
     -2.*(l*l/3.+2.*MP*MP*q*q)
     );
  //////////////////////////////////////////////////////////////////////////
  
  return kpnne;
}



