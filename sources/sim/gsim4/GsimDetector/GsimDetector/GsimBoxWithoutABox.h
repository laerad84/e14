/**
 *  @file
 *  @brief  GsimBoxWithoutABox
 *  $Id: GsimBoxWithoutABox.h, toru matsumura
 *  $Log: GsimBoxWithoutABox.h,v $
 *  Revision 1.4  2006/12/06 19:14:30  nanjo
 *  CVS variables.
 * 
 */
#ifndef GsimBoxWithoutABox_h
#define GsimBoxWithoutABox_h

//includes
#include <string>
#include "GsimKernel/GsimDetector.h"


//forward declaration

/**
 *  @class GsimBoxWithoutABox
 *  @brief This class provides a Gsim4 wrapper around G4Box with a G4Box subtracted.
 *
 *  This class is usually called by the geometry definition class to
 *  define a new daughter volume (e.g., GsimUserDetector).
 *
 *  The default material is G4_PLASTIC_SC_VINYLTOLUENE.
 *  The default color is yellow.
 *  The GsimDetector::SetParameters call takes a vector of 8 doubles.
 *  They are (with default values in parenthesis):
 *  - total x length (10mm)
 *  - total y length (10mm)
 *  - total z length (10mm)
 *  - total x length of the false box (3mm)
 *  - total y length of the false box (3mm)
 *  - x position of the false box (0mm)
 *  - y position of the false box (0mm)
 *  - rotation angle of the false box (0 deg)
 *
 *  Unlike when working with Geant4 directly, any lengths should
 *  be full-lengths, not half-lengths.
 */
class GsimBoxWithoutABox : public GsimDetector
{
 public:
  /**
   *  @function GsimBoxWithoutABox
   *  @brief Constructor for GsimBoxWithoutABox
   *  @param name The name of the box.
   *  @param motherDetector A pointer to the mother volume.
   *  @param transV A Geant (CLHEP) translation vector.
   *  @param rotV A Geant (CLHEP) rotation vector.
   */
  GsimBoxWithoutABox(std::string name,
	  GsimDetector* motherDetector,
	  G4ThreeVector transV,
	  G4ThreeVector rotV,
          int nParameterized=-1);
  
  /**
   *  @function ~GsimBoxWithoutABox
   *  @brief Destructor for GsimBox.
   */
  virtual ~GsimBoxWithoutABox();

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
   *  @function GsimBoxWithoutABox
   *  @brief Constructor for GsimBoxWithoutABox
   */
  GsimBoxWithoutABox();
};


#endif // GsimBoxWithoutABox_h
