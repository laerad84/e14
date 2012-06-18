/**
 *  @file
 *  @brief  GsimKLBetaDecayChannel
 *  $Id: 
 *  $Log: 
 */
#ifndef GsimKLBetaDecayChannel_h
#define GsimKLBetaDecayChannel_h

//includes
#include "TGenPhaseSpace.h"
#include "TLorentzVector.h"

#include "G4VDecayChannel.hh"
#include "G4ios.hh"
#include "globals.hh"

//forward declaration


/**
 *  @class GsimKLBetaDecayChannel
 */
class GsimKLBetaDecayChannel : public G4VDecayChannel
{
public:
  /**
   *  @function GsimKLBetaDecayChannel
   *  @brief Constructor for GsimKLBetaDecayChannel
   */
  GsimKLBetaDecayChannel(const G4String& theParentName,
			     G4double        theBR,
			     const G4String& theKname,
			     const G4String& theEname,
			     const G4String& theNuname
			     );
  /**
   *  @function ~GsimKLBetaDecayChannel
   *  @brief Destructor for GsimKLBetaDecayChannel
   */
  virtual ~GsimKLBetaDecayChannel();

  /**
   *  @function DecayIt
   *  @brief Returns the decay products.
   *  @return The decay products.
   */  
  virtual G4DecayProducts *DecayIt(G4double);
  
protected:
  
  TGenPhaseSpace* m_event;
  Double_t m_wmax;

  void generate();
};

#endif // GsimKLBetaDecayChannel_h
