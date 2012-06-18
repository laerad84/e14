/**
 *  @file
 *  @brief  GsimKLbeta
 *  $Id: 
 *  $Log: 
 */

#include "GsimParticle/GsimKLbeta.h"
#include "GsimParticle/GsimKLBetaDecayChannel.h"

#include "G4VDecayChannel.hh"
#include "G4ParticleTable.hh"
#include "G4DecayTable.hh"


GsimKLbeta* GsimKLbeta::theInstance = 0;

GsimKLbeta* GsimKLbeta::Definition()
{
  if (theInstance !=0) return theInstance;
  const G4String name = "KLbeta";

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
              "meson",               0,             0,         1000130,
                false,         51.7*ns,          NULL,
                false,          "kaon",           1000130);

   //create Decay Table
   
   
   G4DecayTable* table = 0;
   table = new G4DecayTable();
   
   // create decay channels
   G4VDecayChannel** mode = new G4VDecayChannel*[2];
   mode[0] = new GsimKLBetaDecayChannel("kaon0L",1./2.,"kaon+","e-","anti_nu_e");
   mode[1] = new GsimKLBetaDecayChannel("kaon0L",1./2.,"kaon-","e+","nu_e");

   for (G4int index=0; index <2; index++ ) {
     table->Insert(mode[index]);
   }
   delete [] mode;
   
   anInstance->SetDecayTable(table);
  }
  theInstance = reinterpret_cast<GsimKLbeta*>(anInstance);
  return theInstance;
}

GsimKLbeta*  GsimKLbeta::KLbetaDefinition()
{
  return Definition();
}

GsimKLbeta*  GsimKLbeta::KLbeta()
{
  return Definition();
}
