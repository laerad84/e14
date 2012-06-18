/**
 *  @file
 *  @brief  GsimKL3DecayChannel
 *  $Id: GsimKL3DecayChannel.h,v 1.3 2006/12/06 19:25:52 nanjo Exp $
 *  $Log: GsimKL3DecayChannel.h,v $
 *  Revision 1.3  2006/12/06 19:25:52  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimKL3DecayChannel_h
#define GsimKL3DecayChannel_h

//includes
#include "G4ios.hh"
#include "globals.hh"
#include "G4VDecayChannel.hh"

//forward declaration


/**
 *  @class GsimKL3DecayChannel
 *  @brief This class provides the pion + lepton + neutrino decay channels.
 *  @see GsimKLpi0nunu
 *  @see GsimKLpienu
 *  @see GsimKLpimunu
 *
 *  Used by the KL0->pi0 nu nu_bar, KL0->pi+ e- nu_e, and KL0->pi+ mu- nu_mu decays.
 */
class GsimKL3DecayChannel :public G4VDecayChannel
{
  public:
      /**
       *  @function GsimKL3DecayChannel
       *  @brief Constructor for GsimKL3DecayChannel
       *  @param theParentName The name of the parent.
       *  @param theBR The branching ratio.
       *  @param thePionName1 The first daughter of the decay.
       *  @param thePionName2 The second daughter of the decay.
       *  @param thePionName3 The third daughter of the decay.
       */
      GsimKL3DecayChannel(const G4String& theParentName,
			G4double        theBR,
			const G4String& thePionName,
			const G4String& theLeptonName,
			const G4String& theNutrinoName);

      /**
       *  @function ~GsimKL3DecayChannel
       *  @brief Destructor for GsimKL3DecayChannel
       */
      virtual ~GsimKL3DecayChannel();

  public: 
     /**
      *  @function DecayIt
      *  @brief Returns the decay products.
      *  @return The decay products.
      */
     virtual G4DecayProducts *DecayIt(G4double);     

  protected:
     /**
      *  @brief Assignment of daughter particle for arrays of daughters[], etc.
      */
     enum{idPi=0, idLepton=1, idNutrino=2}; 
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

  protected:
     /**
      *  @function DalitzDensity
      *  @brief The weight of this decay.
      *  @param Epi The energy of the pion.
      *  @param El The energy of the lepton.
      *  @param Enu The energy of the neutrino.
      *  @return The weight.
      *
      *  Dalitz Plot Density - see Chounet et al Phys. Rep. 4, 201.
      */
     G4double   DalitzDensity(G4double Epi, G4double El,  G4double Enu);  
  private:
     /**
      *  @brief KL0 mass.
      *
      *  Constant used in DalitzDensity().
      */
     G4double massK;
     /**
      *  @brief Linear energy dependence of f+.
      *
      *  Constant used in DalitzDensity().
      */
     G4double   pLambda;
     /**
      *  @brief f+(0)/f-.
      *
      *  Constant used in DalitzDensity().
      */
     G4double   pXi0;
     /**
      *  @brief Normalization factor
      *
      *  Constant used in DalitzDensity().
      */
     G4double   pNormalization;

  public:
     /**
      *  @function SetDalitzParameter
      *  @brief Sets the two Dalitz coefficients.
      *  @param aLambda Coefficient lambda.
      *  @param Xi Coefficient xi.
      */
     void SetDalitzParameter(G4double aLambda, G4double aXi );
     /**
      *  @function GetDalitzParameterLambda
      *  @brief Returns the Dalitz coefficient lambda.
      *  @return Coefficient lambda.
      */
     G4double GetDalitzParameterLambda() const;
     /**
      *  @function GetDalitzParameterXi
      *  @brief Returns the Dalitz coefficient xi.
      *  @return Coefficient xi.
      */
     G4double GetDalitzParameterXi() const;

     void SetDalitzParameterLambda(G4double aLambda);
};  

inline 
 void GsimKL3DecayChannel::SetDalitzParameter(G4double aLambda, G4double aXi)
{
   pLambda  = aLambda;
   pXi0      = aXi;
}

inline 
 G4double GsimKL3DecayChannel::GetDalitzParameterLambda() const
{
  return  pLambda;
}

inline 
 G4double GsimKL3DecayChannel::GetDalitzParameterXi() const
{
  return  pXi0;
}

inline void GsimKL3DecayChannel::SetDalitzParameterLambda(G4double aLambda)
{
  pLambda  = aLambda;
}

#endif //GsimKL3DecayChannel




