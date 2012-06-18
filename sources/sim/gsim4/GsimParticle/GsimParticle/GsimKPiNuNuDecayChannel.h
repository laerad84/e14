/**
 *  @file
 *  @brief  GsimKPiNuNuDecayChannel
 *  $Id: GsimKPiNuNuDecayChannel.h,v 1.3 2006/12/06 19:25:52 nanjo Exp $
 *  $Log: GsimKPiNuNuDecayChannel.h,v $
 *  Revision 1.3  2006/12/06 19:25:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimKPiNuNuDecayChannel_h
#define GsimKPiNuNuDecayChannel_h

//includes
#include "G4VDecayChannel.hh"
#include "G4ios.hh"
#include "globals.hh"

//forward declaration


/**
 *  @class GsimKPiNuNuDecayChannel
 *  @brief This class provides the pi nu nu decay channel.
 *
 *  Used by the KL0->pi0 nu anti_nu decays.
 */
class GsimKPiNuNuDecayChannel : public G4VDecayChannel
{
public:
  /**
   *  @function GsimKPiNuNuDecayChannel
   *  @brief Constructor for GsimKPiNuNuDecayChannel
   *  @param theParentName The name of the parent.
   *  @param theBR The branching ratio.
   *  @param thePionName1 The first daughter of the decay.
   *  @param thePionName2 The second daughter of the decay.
   *  @param thePionName3 The third daughter of the decay.
   */
  GsimKPiNuNuDecayChannel(const G4String& theParentName,
			     G4double        theBR,
			     const G4String& thePionName1,
			     const G4String& thePionName2,
			     const G4String& thePionName3
			     );
  //  thePionName1 should be "pi0"
  //  thePionName2,3 should be "nu_e","anti_nu_e",
  //                           "nu_mu","anti_nu_mu",
  //                           "nu_tau","anti_nu_tau",
  
  
  /**
   *  @function ~GsimKPiNuNuDecayChannel
   *  @brief Destructor for GsimKPiNuNuDecayChannel
   */
  virtual ~GsimKPiNuNuDecayChannel();

  /**
   *  @function DecayIt
   *  @brief Returns the decay products.
   *  @return The decay products.
   */  
  virtual G4DecayProducts *DecayIt(G4double);
  
  void SetDalitzParameterLambda(G4double aLambda);
protected:

  /**
   *  @function GetKPi0EnergyWeight
   *  @brief The pi0 energy function.
   *  @param pi0e ?
   *  @return The weight.
   */
  double GetKPi0EnergyWeight( double pi0e );

  /**
   *  @brief The mass of the pi0.
   */
  double mp;
  /**
   *  @brief The mass of the KL0.
   */
  double mk;

  double pLambda;

  double emax;
  double emin;
  double wmax;
};

inline void GsimKPiNuNuDecayChannel::SetDalitzParameterLambda(G4double aLambda)
{
  pLambda  = aLambda;
  wmax=GetKPi0EnergyWeight(emax/GeV - 1.0e-9 ); // 1 eV below the max
}

#endif // GsimKPiNuNuDecayChannel_h
