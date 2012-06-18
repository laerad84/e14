/**
 *  @file
 *  @brief  GsimKLpi0nunu
 *  $Id: GsimKLpi0nunu.cc,v 1.2 2006/12/06 19:25:52 nanjo Exp $
 *  $Log: GsimKLpi0nunu.cc,v $
 *  Revision 1.2  2006/12/06 19:25:52  nanjo
 *  CVS variables.
 *
 */

#include "GsimParticle/GsimKLpi0nunu.h"
#include "GsimParticle/GsimKPiNuNuDecayChannel.h"
#include "GsimParticle/GsimKL3DecayChannel.h"

#include "G4VDecayChannel.hh"
#include "G4ParticleTable.hh"
#include "G4DecayTable.hh"
#include "G4PhaseSpaceDecayChannel.hh"


GsimKLpi0nunu* GsimKLpi0nunu::theInstance = 0;

int    GsimKLpi0nunu::s_decayModel=0;
double GsimKLpi0nunu::s_lambdaPlus=0.0284;

GsimKLpi0nunu* GsimKLpi0nunu::Definition()
{
  if (theInstance !=0) return theInstance;
  const G4String name = "KLpi0nunu";

  s_lambdaPlus=0.0284;//PDG 2006 (2.84+-0.04)x10^-2
  s_decayModel=0;
  
  
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
              "meson",               0,             0,         10000130,
                false,         51.7*ns,          NULL,
                false,          "kaon",           10000130);

   //create Decay Table
   
   
   G4DecayTable* table = 0;
   table = new G4DecayTable();
   
   // create decay channels
   G4VDecayChannel** mode = new G4VDecayChannel*[3];
   // kaon0L -> pi0 + nu_e + anti_nu_e
   mode[0] = new GsimKPiNuNuDecayChannel("kaon0L",1./3.,"pi0","nu_e","anti_nu_e");
   // kaon0L -> pi0 + nu_mu + anti_nu_mu
   mode[1] = new GsimKPiNuNuDecayChannel("kaon0L",1./3.,"pi0","nu_mu","anti_nu_mu");
   // kaon0L -> pi0 + nu_tau + anti_nu_tau
   mode[2] = new GsimKPiNuNuDecayChannel("kaon0L",1./3.,"pi0","nu_tau","anti_nu_tau");
   
   for (G4int index=0; index <3; index++ ) {
     table->Insert(mode[index]);
   }
   delete [] mode;
   
   anInstance->SetDecayTable(table);
  }
  theInstance = reinterpret_cast<GsimKLpi0nunu*>(anInstance);
  return theInstance;
}

GsimKLpi0nunu*  GsimKLpi0nunu::KLpi0nunuDefinition()
{
  return Definition();
}

GsimKLpi0nunu*  GsimKLpi0nunu::KLpi0nunu()
{
  return Definition();
}

void GsimKLpi0nunu::setDecayModel(int iModel)
{
  s_decayModel=iModel;
  
  G4ParticleDefinition* particle = KLpi0nunuDefinition();
  
  //create Decay Table 
  G4DecayTable*   table = particle->GetDecayTable();
  if (table!=0) delete table;
  table = new G4DecayTable();
  
  // create decay channels
  G4VDecayChannel** mode = new G4VDecayChannel*[3];

  if(iModel==0) {
    // kaon0L -> pi0 + nu_e + anti_nu_e
    mode[0] = new GsimKPiNuNuDecayChannel("kaon0L",1./3.,"pi0","nu_e","anti_nu_e");
    // kaon0L -> pi0 + nu_mu + anti_nu_mu
    mode[1] = new GsimKPiNuNuDecayChannel("kaon0L",1./3.,"pi0","nu_mu","anti_nu_mu");
    // kaon0L -> pi0 + nu_tau + anti_nu_tau
    mode[2] = new GsimKPiNuNuDecayChannel("kaon0L",1./3.,"pi0","nu_tau","anti_nu_tau");
  } else if(iModel==1) {
    // kaon0L -> pi0 + nu_e + anti_nu_e
    mode[0] = new GsimKL3DecayChannel("kaon0L",1./3.,"pi0","nu_e","anti_nu_e");
    // kaon0L -> pi0 + nu_mu + anti_nu_mu
    mode[1] = new GsimKL3DecayChannel("kaon0L",1./3.,"pi0","nu_mu","anti_nu_mu");
    // kaon0L -> pi0 + nu_tau + anti_nu_tau
    mode[2] = new GsimKL3DecayChannel("kaon0L",1./3.,"pi0","nu_tau","anti_nu_tau");
  } else if(iModel==2) {
    // kaon0L -> pi0 + nu_e + anti_nu_e
    mode[0] = new G4PhaseSpaceDecayChannel("kaon0L",1./3.,3,"pi0","nu_e","anti_nu_e"); 
    // kaon0L -> pi0 + nu_mu + anti_nu_mu
    mode[1] = new G4PhaseSpaceDecayChannel("kaon0L",1./3.,3,"pi0","nu_mu","anti_nu_mu"); 
    // kaon0L -> pi0 + nu_tau + anti_nu_tau
    mode[2] = new G4PhaseSpaceDecayChannel("kaon0L",1./3.,3,"pi0","nu_tau","anti_nu_tau"); 
  }

  
  for (G4int index=0; index <3; index++ ) {
    table->Insert(mode[index]);
  }
  delete [] mode;
  
  particle->SetDecayTable(table);
  setLambdaPlus(s_lambdaPlus);
}


void   GsimKLpi0nunu::setLambdaPlus(double lambda)
{
  s_lambdaPlus=lambda;
  G4ParticleDefinition* particle = KLpi0nunuDefinition();
  G4DecayTable* table = particle->GetDecayTable();
  for(int i=0;i<3;i++) {
    G4VDecayChannel* decayChannel = table->GetDecayChannel(i);
    if(s_decayModel==0) {
      GsimKPiNuNuDecayChannel* mode
	= reinterpret_cast<GsimKPiNuNuDecayChannel*>(decayChannel);
      mode->SetDalitzParameterLambda(lambda);
    } else if(s_decayModel==1) {
      GsimKL3DecayChannel* mode
	= reinterpret_cast<GsimKL3DecayChannel*>(decayChannel);
      mode->SetDalitzParameterLambda(lambda);
    } else {
    }
  }
}

double GsimKLpi0nunu::getLambdaPlus()
{
  return s_lambdaPlus;
}
