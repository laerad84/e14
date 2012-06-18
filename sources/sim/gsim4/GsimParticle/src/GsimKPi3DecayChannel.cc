/**
 *  @file
 *  @brief  GsimKPi3DecayChannel
 *  $Id: GsimKPi3DecayChannel.cc,v 1.4 2006/12/06 19:25:52 nanjo Exp $
 *  $Log: GsimKPi3DecayChannel.cc,v $
 *  Revision 1.4  2006/12/06 19:25:52  nanjo
 *  CVS variables.
 *
 */

#include "GsimParticle/GsimKPi3DecayChannel.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4DecayProducts.hh"
#include "G4VDecayChannel.hh"
#include "Randomize.hh"
#include "G4LorentzVector.hh"
#include "G4LorentzRotation.hh"

GsimKPi3DecayChannel::GsimKPi3DecayChannel(
			const G4String& theParentName, 
			G4double        theBR,
			const G4String& thePionName1,
			const G4String& thePionName2,
			const G4String& thePionName3)
  :G4VDecayChannel("KPi3 Decay",theParentName,
		   theBR,  3,
		   thePionName1,  thePionName2,  thePionName3)
  //  thePionName3 should be "pi0"
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  //#ifdef G4VERBOSE
  //if (GetVerboseLevel()>1) {
  //  G4cout << "kPI3DecayChannel:: constructor ";
  //  G4cout << "addr[" << this << "]" << G4endl;
  //}
  //#endif
  // check modes
  if ( (theParentName == "kaon0L") && 
              ((thePionName1 == "pi+") ||(thePionName1 == "pi-"))  ){
    // K0L -> pi+  pi-  pi0 
    coeffG = 0.678;              //DATA from PDG 2004 p633
    coeffH = 0.076;
    coeffAK = 0.0099;
    norm = 1.0342;
  } else if ( (theParentName == "kaon0L") && 
              ((thePionName1 == "pi0") && (thePionName2 == "pi0"))  ){
    // K0L -> pi0  pi0  pi0 
    coeffG = 0.0;
    coeffH = -0.0050;
    coeffAK = 0.0;
    norm =0.5;
  } else {
    // set values for K0L -> pi0 pi0 pi0 temporarily
    coeffG = 0.0;
    coeffH = -0.0050;
    coeffAK = 0.0;
    norm =1;
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimKPi3DecayChannel::~GsimKPi3DecayChannel()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

G4DecayProducts* GsimKPi3DecayChannel::DecayIt(G4double) 
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  // this version neglects muon polarization 
  //              assumes the pure V-A coupling
  //              gives incorrect energy spectrum for Nutrinos
#ifdef G4VERBOSE
  if (GetVerboseLevel()>1) G4cout << "GsimKPi3DecayChannel::DecayIt " << G4endl;
#endif
  // fill parent particle and its mass
  if (parent == 0) {
    FillParent();
  }
  massK = parent->GetPDGMass();

  // fill daughter particles and their mass
  if (daughters == 0) {
    FillDaughters();
  }

  daughterM[0] = daughters[0]->GetPDGMass();
  daughterM[1] = daughters[1]->GetPDGMass();
  daughterM[2] = daughters[2]->GetPDGMass();

  // determine momentum/energy of daughters 
  //  according to DalitzDensity 
  G4double daughterP[3], daughterE[3];
  G4double w=-1.;
  G4double r=0.;
  do {
    r = G4UniformRand();
    PhaseSpace(massK, &daughterM[0], &daughterE[0], &daughterP[0]);
    w = DalitzDensity(daughterE[0],daughterE[1],daughterE[2]);
  } while ( r > w);

  // Fill Dalitz Plot
//   G4double y = (daughterE[idPi1] + daughterM[idPi1])*2/massK;
//   G4double z = (daughterE[idPi3] + daughterM[idPi3])*2/massK;
//   G4double M12 = massK*massK + daughterM[idPi3] *daughterM[idPi3]
//     -2*massK*(daughterE[idPi3] + daughterM[idPi3]);
//   G4double M23 = massK*massK + daughterM[idPi1] *daughterM[idPi1]
//     -2*massK*(daughterE[idPi1] + daughterM[idPi1]);
  
  
  // output message
#ifdef G4VERBOSE
  if (GetVerboseLevel()>1) {
    G4cout << *daughters_name[0] << ":" << daughterP[0]/GeV << "[GeV/c]" <<G4endl;
    G4cout << *daughters_name[1] << ":" << daughterP[1]/GeV << "[GeV/c]" <<G4endl;
    G4cout << *daughters_name[2] << ":" << daughterP[2]/GeV << "[GeV/c]" <<G4endl;
  }
#endif
   //create parent G4DynamicParticle at rest
  G4ThreeVector* direction = new G4ThreeVector(1.0,0.0,0.0);
  G4DynamicParticle * parentparticle = new G4DynamicParticle( parent, *direction, 0.0);
  delete direction;

  //create G4Decayproducts
  G4DecayProducts *products = new G4DecayProducts(*parentparticle);
  delete parentparticle;

  //create daughter G4DynamicParticle 
  G4double costheta, sintheta, phi, sinphi, cosphi; 
  G4double costhetan, sinthetan, phin, sinphin, cosphin;
 
  // pion1
  costheta = 2.*G4UniformRand()-1.0;
  sintheta = std::sqrt((1.0-costheta)*(1.0+costheta));
  phi  = twopi*G4UniformRand()*rad;
  sinphi = std::sin(phi);
  cosphi = std::cos(phi);
  direction = new G4ThreeVector(sintheta*cosphi,sintheta*sinphi,costheta);
  G4ThreeVector momentum0 =  (*direction)*daughterP[0]; 
  G4DynamicParticle * daughterparticle 
       = new G4DynamicParticle( daughters[0], momentum0);
  products->PushProducts(daughterparticle);

  // pion2
  costhetan = (daughterP[1]*daughterP[1]-daughterP[2]*daughterP[2]-daughterP[0]*daughterP[0])/(2.0*daughterP[2]*daughterP[0]);
  sinthetan = std::sqrt((1.0-costhetan)*(1.0+costhetan));
  phin  = twopi*G4UniformRand()*rad;
  sinphin = std::sin(phin);
  cosphin = std::cos(phin);
  direction->setX( sinthetan*cosphin*costheta*cosphi - sinthetan*sinphin*sinphi + costhetan*sintheta*cosphi); 
  direction->setY( sinthetan*cosphin*costheta*sinphi + sinthetan*sinphin*cosphi + costhetan*sintheta*sinphi); 
  direction->setZ( -sinthetan*cosphin*sintheta + costhetan*costheta);

  G4ThreeVector momentum2 =  (*direction)*daughterP[2]; 
  daughterparticle = new G4DynamicParticle( daughters[2], momentum2);
  products->PushProducts(daughterparticle);

  // pion3
  G4ThreeVector momentum1 = (momentum0 + momentum2) * (-1.0);
  daughterparticle = 
       new G4DynamicParticle( daughters[1], momentum1);
  products->PushProducts(daughterparticle);

#ifdef G4VERBOSE
  if (GetVerboseLevel()>1) {
     G4cout << "GsimKPi3DecayChannel::DecayIt ";
     G4cout << "  create decay products in rest frame " <<G4endl;
     G4cout << "  decay products address=" << products << G4endl;
     products->DumpInfo();
  }
#endif
  delete direction;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return products;
}

void GsimKPi3DecayChannel::PhaseSpace(G4double parentM,
				   const G4double* M,
				   G4double*       E,
				   G4double*       P )
// algorism of this code is originally written in GDECA3 of GEANT3
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  
  //sum of daughters'mass
  G4double sumofdaughtermass = 0.0;
  G4int index;
  for (index=0; index<3; index++){
    sumofdaughtermass += M[index];
  }

  //calculate daughter momentum
  //  Generate two 
  G4double rd1, rd2, rd;
  G4double momentummax=0.0, momentumsum = 0.0;
  G4double energy;

  do {
    rd1 = G4UniformRand();
    rd2 = G4UniformRand();
    if (rd2 > rd1) {
      rd  = rd1;
      rd1 = rd2;
      rd2 = rd;
    } 
    momentummax = 0.0;
    momentumsum = 0.0;
    // daughter 0
    energy = rd2*(parentM - sumofdaughtermass);
    P[0] = std::sqrt(energy*energy + 2.0*energy*M[0]);
    E[0] = energy;
    if ( P[0] >momentummax )momentummax =  P[0];
    momentumsum  +=  P[0];
    // daughter 1
    energy = (1.-rd1)*(parentM - sumofdaughtermass);
    P[1] = std::sqrt(energy*energy + 2.0*energy*M[1]);
    E[1] = energy;
    if ( P[1] >momentummax )momentummax =  P[1];
    momentumsum  +=  P[1];
    // daughter 2
    energy = (rd1-rd2)*(parentM - sumofdaughtermass);
    P[2] = std::sqrt(energy*energy + 2.0*energy*M[2]);
    E[2] = energy;
    if ( P[2] >momentummax )momentummax =  P[2];
    momentumsum  +=  P[2];
  } while (momentummax >  momentumsum - momentummax );

#ifdef G4VERBOSE
  if (GetVerboseLevel()>2) {
     G4cout << "GsimKPi3DecayChannel::PhaseSpace    ";
     G4cout << "Kon mass:" << parentM/GeV << "GeV/c/c" << G4endl;
     for (index=0; index<3; index++){
       G4cout << index << " : " << M[index]/GeV << "GeV/c/c  ";
       G4cout << " : " << E[index]/GeV << "GeV  ";
       G4cout << " : " << P[index]/GeV << "GeV/c " << G4endl;
     }
  }
#endif
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


G4double GsimKPi3DecayChannel::DalitzDensity(G4double Tpi1, G4double Tpi2, G4double Tpi3)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  // KPI3 decay   Dalitz Plot Density
  //               see PDG 2004 p616

  // mass of daughters
  // Pi3: odd Pi-on

  G4double massPi1 = daughterM[0];
  G4double massPi2 = daughterM[1]; 
  G4double massPi3 = daughterM[2];


  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle("pi+");

  G4double PiPlusMass = particle->GetPDGMass();
  
  G4double PIN = 1./PiPlusMass /PiPlusMass;       
  
  G4double  S0=(massK*massK + massPi1*massPi1 + massPi2*massPi2 + massPi3*massPi3 )/3 ;
  G4double  S12=(Tpi1-Tpi2)*massK*2 ;
  G4double  S12SQ=S12*S12*PIN*PIN ;
  G4double  S3=(massK-massPi3)*(massK-massPi3) - 2.*massK*Tpi3 ;
  G4double  S30=(S3-S0)*PIN ;


  G4double Tau0=(1. + coeffG *S30 + coeffH * S30*S30 + coeffAK * S12SQ)/2.0;

  //  G4cout << "Tau0 : " << Tau0 << "Daughter Mass : "
  //         << massPi1 << "  ,  "
  //         << massPi2 << "  ,  "
  //         << massPi3 << G4endl;

#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return (Tau0/norm);
}




