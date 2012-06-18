/**
 *  @file
 *  @brief  GsimBoxWithAHole
 *  $Id: GsimBoxWithAHole.h,v 1.4 2006/12/06 19:14:30 nanjo Exp $ 
 *  $Log: GsimBoxWithAHole.h,v $
 *  Revision 1.4  2006/12/06 19:14:30  nanjo
 *  CVS variables.
 * 
 */
#ifndef GsimBoxWithAHole_h
#define GsimBoxWithAHole_h

//includes
#include <string>
#include "GsimKernel/GsimDetector.h"


//forward declaration

/**
 *  @class GsimBoxWithAHole
 *  @brief This class provides a Gsim4 wrapper around G4Box with a G4Tube subtracted.
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
class GsimBoxWithAHole : public GsimDetector
{
 public:
  /**
   *  @function GsimBoxWithAHole
   *  @brief Constructor for GsimBoxWithAHole
   *  @param name The name of the box.
   *  @param motherDetector A pointer to the mother volume.
   *  @param transV A Geant (CLHEP) translation vector.
   *  @param rotV A Geant (CLHEP) rotation vector.
   */
  GsimBoxWithAHole(std::string name,
		   GsimDetector* motherDetector,
		   G4ThreeVector transV,
		   G4ThreeVector rotV,
		   int userFlag=0);
  
  /**
   *  @function ~GsimBoxWithAHole
   *  @brief Destructor for GsimBox.
   */
  virtual ~GsimBoxWithAHole();

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
   *  @function GsimBoxWithAHole
   *  @brief Constructor for GsimBoxWithAHole
   */
  GsimBoxWithAHole();
};


#endif // GsimBoxWithAHole_h
