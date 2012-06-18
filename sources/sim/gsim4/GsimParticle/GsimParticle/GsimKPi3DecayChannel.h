/**
 *  @file
 *  @brief  GsimKPi3DecayChannel
 *  $Id: GsimKPi3DecayChannel.h,v 1.3 2006/12/06 19:25:52 nanjo Exp $
 *  $Log: GsimKPi3DecayChannel.h,v $
 *  Revision 1.3  2006/12/06 19:25:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimKPi3DecayChannel_h
#define GsimKPi3DecayChannel_h

//includes
#include "G4VDecayChannel.hh"
#include "G4ios.hh"
#include "globals.hh"

//forward declaration


/**
 *  @class GsimKPi3DecayChannel
 *  @brief This class provides the 3pi decay channels.
 *
 *  Used by the KL0->pi+pi-pi0 and KL0->3pi0 decays.
 */
class GsimKPi3DecayChannel :public G4VDecayChannel
{
  public:
  /**
   *  @function GsimKPi3DecayChannel
   *  @brief Constructor for GsimKPi3DecayChannel
   *  @param theParentName The name of the parent.
   *  @param theBR The branching ratio.
   *  @param thePionName1 The first daughter of the decay.
   *  @param thePionName2 The second daughter of the decay.
   *  @param thePionName3 The third daughter of the decay.
   *
   *  "thePionName3" should be "pi0".
   */
  GsimKPi3DecayChannel(const G4String& theParentName,
		       G4double        theBR,
                       const G4String& thePionName1,
                       const G4String& thePionName2,
                       const G4String& thePionName3
                       );
  //  thePionName3 should be "pi0"

  /**
   *  @function ~GsimKPi3DecayChannel
   *  @brief Destructor for GsimKPi3DecayChannel
   */
  virtual ~GsimKPi3DecayChannel();

  /**
   *  @function DecayIt
   *  @brief Returns the decay products.
   *  @return The decay products.
   */
  virtual G4DecayProducts *DecayIt(G4double);

  /**
   *  @function SetDalitzParameter
   *  @brief Sets the three Dalitz coefficients.
   *  @param G Coefficient G.
   *  @param H Coefficient H.
   *  @param AK Coefficient AK.
   */
  inline void     SetDalitzParameter(G4double G, G4double H, G4double AK );
 /**
   *  @function GetDalitzParameterG
   *  @brief Returns the Dalitz coefficient G.
   *  @return Coefficient G.
   */
  inline G4double GetDalitzParameterG() const;
  /**
   *  @function GetDalitzParameterH
   *  @brief Returns the Dalitz coefficient H.
   *  @return Coefficient H.
   */
  inline G4double GetDalitzParameterH() const;
  /**
   *  @function GetDalitzParameterAK
   *  @brief Returns the Dalitz coefficient AK.
   *  @return Coefficient AK.
   */
  inline G4double GetDalitzParameterAK() const;

protected:
  /**
   *  @brief Masses of the three daughters.
   */
  G4double daughterM[3];
  
protected:
  /**
   *  @function PhaseSpace
   *  @brief Calculates the momenta of the daughters.
   *  @parameter Mparent The mass of the parent.
   *  @parameter Mdaughter The masses of the daughters.
   *  @parameter Edaughter The energies of the daughters.
   *  @parameter Pdaughter The momenta of the daughters.
   *
   *  The results are stored in Edaughter[3] and Pdaughter[3].
   */
  void PhaseSpace(G4double Mparent,
		  const G4double* Mdaughter,
		  G4double*       Edaughter,
		  G4double*       Pdaughter);
  
  /**
   *  @function DalitzDensity
   *  @brief The weight of this decay.
   *  @param Tpi1 The kinetic energy of the first pion.
   *  @param Tpi2 The kinetic energy of the second pion.
   *  @param Tpi3 The kinetic energy of the third pion.
   *  @return The weight.
   *
   *  Dalitz Plot Density - see PDG 2004 p616.
   */
  G4double   DalitzDensity(G4double Tpi1, G4double Tpi2,  G4double Tpi3);  
  
private:
  /**
   *  @brief KL0 mass.
   *
   *  Constant used in DalitzDensity().
   */
  G4double massK;
  /**
   *  @brief Coefficient G.
   *
   *  Constant used in DalitzDensity().
   */
  G4double   coeffG;
  /**
   *  @brief Coefficient H.
   *
   *  Constant used in DalitzDensity().
   */
  G4double   coeffH;
  /**
   *  @brief Coefficient AK.
   *
   *  Constant used in DalitzDensity().
   */
  G4double   coeffAK;
  /**
   *  @brief Normalization.
   *
   *  To avoid tau0 > 1. Constant used in DalitzDensity().
   */
  G4double   norm; // to aviod tau0 > 1
  
};  

inline 
void GsimKPi3DecayChannel::SetDalitzParameter(G4double G, G4double H, G4double AK)
{
  coeffG      = G;
  coeffH      = H;
  coeffAK     = AK;
}

inline 
G4double GsimKPi3DecayChannel::GetDalitzParameterG() const
{
  return  coeffG;
}
inline 
G4double GsimKPi3DecayChannel::GetDalitzParameterH() const
{
  return  coeffH;
}
inline 
G4double GsimKPi3DecayChannel::GetDalitzParameterAK() const
{
  return  coeffAK;
}



#endif

