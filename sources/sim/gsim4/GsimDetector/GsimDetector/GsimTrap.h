/**
 *  @file
 *  @brief  GsimTrap
 *  $Id: GsimTrap.h,v 1.4 2006/12/06 19:14:30 nanjo Exp $ 
 *  $Log: GsimTrap.h,v $
 *  Revision 1.4  2006/12/06 19:14:30  nanjo
 *  CVS variables.
 * 
 */
#ifndef GsimTrap_h
#define GsimTrap_h

//includes
#include <string>
#include "GsimKernel/GsimDetector.h"

//forward declaration
class G4Trd;
class G4Trap;
class G4Cons;
class G4Orb;
class G4Sphere;
class G4Torus;
class G4Para;
class G4Hype;
class G4Tubs;
class G4Polycone;
class G4Polyhedra;
class G4Box;

/**
 *  @class GsimTrap
 *  @brief This class provides a Gsim4 wrapper around G4Trap.
 *
 *  This class is usually called by the geometry definition class to
 *  define a new daughter volume (e.g., GsimUserDetector).
 *
 *  The default material is G4_PLASTIC_SC_VINYLTOLUENE.
 *  The default color is blue.
 *  The GsimDetector::SetParameters call takes a vector of 11 doubles.
 *  They are (with default values in parenthesis):
 *  - full-length along the z-axis (1mm)
 *  - polar angle of the line joining the centres of the faces at -/+pDz
 *  (0 degrees)
 *  - azimuthal angle of the line joing the centre of the face at -pDz
 *  to the centre of the face at +pDz (0 degrees)
 *  - full-length along y of the face at -pDz (2cm)
 *  - full-length along x of the side at y=-pDy1 of the face at -pDz (1cm)
 *  - full-length along x of the side at y=+pDy1 of the face at -pDz (3cm)
 *  - angle with respect to the y axis from the centre of the side at
 *  y=-pDy1 to the centre at y=+pDy1 of the face at -pDz (0 degrees)
 *  - full-length along y of the face at +pDz (2cm)
 *  - full-length along x of the side at y=-pDy2 of the face at +pDz (1cm)
 *  - full-length along x of the side at y=+pDy2 of the face at +pDz (3cm)
 *  - angle with respect to the y axis from the centre of the side at
 *  y=-pDy2 to the centre at y=+pDy2 of the face at +pDz (0 degrees)
 *
 *  Unlike when working with Geant4 directly, any lengths should
 *  be full-lengths, not half-lengths.
 */
class GsimTrap : public GsimDetector
{
 public:
  /**
   *  @function GsimTrap
   *  @brief Constructor for GsimTrap.
   *  @param name The name of the trapezoid.
   *  @param motherDetector A pointer to the mother volume.
   *  @param transV A Geant (CLHEP) translation vector.
   *  @param rotV A Geant (CLHEP) rotation vector.
   */
  GsimTrap(std::string name,
	   GsimDetector* motherDetector,
	   G4ThreeVector transV,
	   G4ThreeVector rotV,
	   int userFlag=0);
  
  /**
   *  @function ~GsimTrap
   *  @brief Destructor for GsimTrap.
   */
  virtual ~GsimTrap();

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
   *  @function GsimTrap
   *  @brief Constructor for GsimTrap.
   */
  GsimTrap();

  virtual void ComputeDimensions(G4Box&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Trd&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Trap&,const G4int,const G4VPhysicalVolume*) const;
  virtual void ComputeDimensions (G4Cons&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Sphere&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Orb&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Torus&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Para&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Hype&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Tubs&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Polycone&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Polyhedra&,const G4int,const G4VPhysicalVolume*) const {}
};


#endif // GsimTrap_h
