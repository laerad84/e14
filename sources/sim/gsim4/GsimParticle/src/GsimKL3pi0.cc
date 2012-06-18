/**
 *  @file
 *  @brief  GsimKL3pi0
 *  $Id: GsimKL3pi0.cc,v 1.2 2006/12/06 19:25:52 nanjo Exp $
 *  $Log: GsimKL3pi0.cc,v $
 *  Revision 1.2  2006/12/06 19:25:52  nanjo
 *  CVS variables.
 *
 */

#include "GsimParticle/GsimKL3pi0.h"
#include "GsimParticle/GsimKPi3DecayChannel.h"


#include "G4VDecayChannel.hh"
#include "G4ParticleTable.hh"
#include "G4DecayTable.hh"

GsimKL3pi0* GsimKL3pi0::theInstance = 0;

GsimKL3pi0* GsimKL3pi0::Definition()
{
  if (theInstance !=0) return theInstance;
  const G4String name = "KL3pi0";
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
              "meson",               0,             0,         300130,
                false,         51.7*ns,          NULL,
                false,          "kaon",           300130);

   //create Decay Table
   
   
   G4DecayTable* table = 0;
   table = new G4DecayTable();
   
   // create decay channels
   G4VDecayChannel** mode = new G4VDecayChannel*[1];
   // kaon0L -> pi0 + pi0 + pi0
   mode[0] = new GsimKPi3DecayChannel("kaon0L",1.,"pi0","pi0","pi0");

   for (G4int index=0; index <1; index++ ) {
     table->Insert(mode[index]);
   }
   delete [] mode;
   
   anInstance->SetDecayTable(table);
  }
  theInstance = reinterpret_cast<GsimKL3pi0*>(anInstance);
  return theInstance;
}

GsimKL3pi0*  GsimKL3pi0::KL3pi0Definition()
{
  return Definition();
}

GsimKL3pi0*  GsimKL3pi0::KL3pi0()
{
  return Definition();
}

