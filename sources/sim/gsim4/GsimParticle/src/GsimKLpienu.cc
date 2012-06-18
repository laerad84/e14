/**
 *  @file
 *  @brief  GsimKLpienu
 *  $Id: GsimKLpienu.cc,v 1.2 2006/12/06 19:25:52 nanjo Exp $
 *  $Log: GsimKLpienu.cc,v $
 *  Revision 1.2  2006/12/06 19:25:52  nanjo
 *  CVS variables.
 *
 */

#include "GsimParticle/GsimKLpienu.h"
#include "GsimParticle/GsimKL3DecayChannel.h"

#include "G4VDecayChannel.hh"
#include "G4ParticleTable.hh"
#include "G4DecayTable.hh"

GsimKLpienu* GsimKLpienu::theInstance = 0;

GsimKLpienu* GsimKLpienu::Definition()
{
  if (theInstance !=0) return theInstance;
  const G4String name = "KLpienu";
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
              "meson",               0,             0,         100130,
                false,         51.7*ns,          NULL,
                false,          "kaon",           100130);

   //create Decay Table
   
   
   G4DecayTable* table = 0;
   table = new G4DecayTable();
   
   // create decay channels
   G4VDecayChannel** mode = new G4VDecayChannel*[2];
   // kaon0L -> pi+ + e+ nu_e
   mode[0] = new GsimKL3DecayChannel("kaon0L",0.5,"pi-","e+","nu_e");
   // kaon0L -> pi- + e- + anti_nu_e
   mode[1] = new GsimKL3DecayChannel("kaon0L",0.5,"pi+","e-","anti_nu_e");

   
   for (G4int index=0; index <2; index++ ) {
     table->Insert(mode[index]);
   }
   delete [] mode;
   
   anInstance->SetDecayTable(table);
  }
  theInstance = reinterpret_cast<GsimKLpienu*>(anInstance);
  return theInstance;
}

GsimKLpienu*  GsimKLpienu::KLpienuDefinition()
{
  return Definition();
}

GsimKLpienu*  GsimKLpienu::KLpienu()
{
  return Definition();
}

