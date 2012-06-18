/**
 *  @file
 *  @brief  GsimKLpimunugamma
 *  $Id: GsimKLpimunugamma.cc,v 1.2 2006/12/06 19:25:52 nanjo Exp $
 *  $Log: GsimKLpimunugamma.cc,v $
 *  Revision 1.2  2006/12/06 19:25:52  nanjo
 *  CVS variables.
 *
 */

#include "GsimParticle/GsimKLpimunugamma.h"

#include "G4PhaseSpaceDecayChannel.hh"
#include "G4VDecayChannel.hh"
#include "G4ParticleTable.hh"
#include "G4DecayTable.hh"

GsimKLpimunugamma* GsimKLpimunugamma::theInstance = 0;

GsimKLpimunugamma* GsimKLpimunugamma::Definition()
{
  if (theInstance !=0) return theInstance;
  const G4String name = "KLpimunugamma";
  // search in particle table]
  G4ParticleTable* pTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* anInstance = pTable->FindParticle(name);
  if (anInstance ==0)
  {
  // create particle
  //
  //    Arguments for constructor are as follows
  //               name             mass          width         charge
  //             2*spin           parity  C-conjugation
  //          2*Isospin       2*Isospin3       G-parity
  //               type    lepton number  baryon number   PDG encoding
  //             stable         lifetime    decay table
  //             shortlived      subType    anti_encoding

   anInstance = new G4ParticleDefinition(
                 name,    0.497672*GeV,  1.273e-14*MeV,         0.0,
                    0,              -1,             0,
                    1,               0,             0,
              "meson",               0,             0,         800130,
                false,         51.7*ns,          NULL,
                false,          "kaon",           800130);

   //create Decay Table
   
   
   G4DecayTable* table = 0;
   table = new G4DecayTable();
   
   // create decay channels
   G4VDecayChannel** mode = new G4VDecayChannel*[2];
   // kaon0L -> pi- + mu+ + nu_mu + gamma
   mode[0] = new G4PhaseSpaceDecayChannel("kaon0L",0.5,4,"pi+","mu+","nu_mu","gamma");
   // kaon0L -> pi+ + mu- + anti_nu_mu + gamma
   mode[1] = new G4PhaseSpaceDecayChannel("kaon0L",0.5,4,"pi-","mu-","anti_nu_mu","gamma");
   
   for (G4int index=0; index <2; index++ ) {
     table->Insert(mode[index]);
   }
   delete [] mode;
   
   anInstance->SetDecayTable(table);
  }
  theInstance = reinterpret_cast<GsimKLpimunugamma*>(anInstance);
  return theInstance;
}

GsimKLpimunugamma*  GsimKLpimunugamma::KLpimunugammaDefinition()
{
  return Definition();
}

GsimKLpimunugamma*  GsimKLpimunugamma::KLpimunugamma()
{
  return Definition();
}

