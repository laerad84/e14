/**
 *  @file
 *  @brief  GsimX
 *  $Id: $
 *  $Log:$
 */

#include "GsimParticle/GsimX.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4PhaseSpaceDecayChannel.hh"

#include "G4VDecayChannel.hh"
#include "G4ParticleTable.hh"
#include "G4DecayTable.hh"

GsimX* GsimX::theInstance = 0;


void GsimX::initialize(double mass,double lifetime,double width,double charge,
			      bool isStable,
			      bool isShortlived
			      )
{
  const G4String name = "X";
  // search in particle table]
  G4ParticleTable* pTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* anInstance = pTable->FindParticle(name);
  if (anInstance !=0) {
    GsimMessage::getInstance()
      ->report("warning","GsimX was already initialized. Not valid.");
    return;
  }

  // create particle
  //
  //    Arguments for constructor are as follows
  //               name             mass          width         charge
  //             2*spin           parity  C-conjugation
  //          2*Isospin       2*Isospin3       G-parity
  //               type    lepton number  baryon number   PDG encoding
  //             stable         lifetime    decay table
  //             shortlived      subType    anti_encoding

  anInstance = new G4ParticleDefinition(name,    mass,  width,         charge,
					0,               0,             0,
					0,               0,             0,
					"X",             0,             0,         900022,
					isStable,        lifetime,      NULL,
					isShortlived,     "X",           900022);
  theInstance = reinterpret_cast<GsimX*>(anInstance);
}

GsimX* GsimX::Definition()
{
  
  if (theInstance !=0) {
    return theInstance;
  } else {
    //Warning
    GsimMessage::getInstance()
      ->report("warning","GsimX should be initialized at first at once.");
    return theInstance;
  }
}

GsimX*  GsimX::XDefinition()
{
  return Definition();
}

GsimX*  GsimX::X()
{
  return Definition();
}
