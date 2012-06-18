/**
 *  @file
 *  @brief  GsimKLpimunu
 *  $Id: GsimKLpimunu.cc,v 1.2 2006/12/06 19:25:52 nanjo Exp $
 *  $Log: GsimKLpimunu.cc,v $
 *  Revision 1.2  2006/12/06 19:25:52  nanjo
 *  CVS variables.
 *
 */

#include "GsimParticle/GsimKLpimunu.h"
#include "GsimParticle/GsimKL3DecayChannel.h"

#include "G4VDecayChannel.hh"
#include "G4ParticleTable.hh"
#include "G4DecayTable.hh"

GsimKLpimunu* GsimKLpimunu::theInstance = 0;

GsimKLpimunu* GsimKLpimunu::Definition()
{
  if (theInstance !=0) return theInstance;
  const G4String name = "KLpimunu";
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
              "meson",               0,             0,         200130,
                false,         51.7*ns,          NULL,
                false,          "kaon",           200130);

   //create Decay Table
   
   
   G4DecayTable* table = 0;
   table = new G4DecayTable();
   
   // create decay channels
   G4VDecayChannel** mode = new G4VDecayChannel*[2];
   // kaon0L -> pi- + mu+ + nu_mu
   mode[0] = new GsimKL3DecayChannel("kaon0L",0.5,"pi-","mu+","nu_mu");
   // kaon0L -> pi- +  mu- + anti_nu_mu
   mode[1] = new GsimKL3DecayChannel("kaon0L",0.5,"pi+","mu-","anti_nu_mu");
   
   for (G4int index=0; index <2; index++ ) {
     table->Insert(mode[index]);
   }
   delete [] mode;
   
   anInstance->SetDecayTable(table);
  }
  theInstance = reinterpret_cast<GsimKLpimunu*>(anInstance);
  return theInstance;
}

GsimKLpimunu*  GsimKLpimunu::KLpimunuDefinition()
{
  return Definition();
}

GsimKLpimunu*  GsimKLpimunu::KLpimunu()
{
  return Definition();
}

