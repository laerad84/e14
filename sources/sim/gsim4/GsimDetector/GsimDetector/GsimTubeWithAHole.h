/**
 *  @file
 *  @brief  GsimTubeWithAHole
 *  $Id: $ 
 *  $Log: $
 */
#ifndef GsimTubeWithAHole_h
#define GsimTubeWithAHole_h

//includes
#include <string>
#include "GsimKernel/GsimDetector.h"


//forward declaration

/**
 *  @class GsimTubeWithAHole
 *  @brief This class provides a Gsim4 wrapper around G4Tube with a G4Box subtracted.
 *
 *  This class is usually called by the geometry definition class to
 *  define a new daughter volume (e.g., GsimUserDetector).
 *
 *  The default material is G4_PLASTIC_SC_VINYLTOLUENE.
 *  The default color is yellow.
 *  The GsimDetector::SetParameters call takes a vector of 6 doubles.
 *  They are (with default values in parenthesis):
 *  - total x length (10mm)
 *  - total y length (10mm)
 *  - total z length (10mm)
 *  - x position of the tube (0mm)
 *  - y position of the tube (0mm)
 *  - outer radius of the tube (3mm)
 *
 *  Unlike when working with Geant4 directly, any lengths should
 *  be full-lengths, not half-lengths.
 */
class GsimTubeWithAHole : public GsimDetector
{
 public:
  /**
   *  @function GsimTubeWithAHole
   *  @brief Constructor for GsimTubeWithAHole
   *  @param name The name of the box.
   *  @param motherDetector A pointer to the mother volume.
   *  @param transV A Geant (CLHEP) translation vector.
   *  @param rotV A Geant (CLHEP) rotation vector.
   */
  GsimTubeWithAHole(std::string name,
		    GsimDetector* motherDetector,
		    G4ThreeVector transV,
		    G4ThreeVector rotV,
		    int userFlag=0);
  
  /**
   *  @function ~GsimTubeWithAHole
   *  @brief Destructor for GsimBox.
   */
  virtual ~GsimTubeWithAHole();

 protected:
  /**
   * @function constructPhysiDetector
   * @brief Creates a physical volume.
   */
  virtual void constructPhysiDetector();
  /**
   * @function updateParametersEtc
   * @brief Updates the parameters.
   */
  virtual void updateParametersEtc();
  /**
   *  @function GsimTubeWithAHole
   *  @brief Constructor for GsimTubeWithAHole
   */
  GsimTubeWithAHole();
};


#endif // GsimTubeWithAHole_h
