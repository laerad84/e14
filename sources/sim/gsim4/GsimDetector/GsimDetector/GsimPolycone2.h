/**
 *  @file
 *  @brief  GsimPolycone2
 *  $Id: GsimPolycone2.h,v 1.2 2006/12/06 19:14:30 nanjo Exp $ 
 *  $Log: GsimPolycone2.h,v $
 *  Revision 1.2  2006/12/06 19:14:30  nanjo
 *  CVS variables.
 * 
 */
#ifndef GsimPolycone2_h
#define GsimPolycone2_h

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
 *  @class GsimPolycone2
 *  @brief This class provides a Gsim4 wrapper around GsimPolycone
 *  @see GsimDetector
 *
 *  This class is usually called by the geometry definition class to
 *  define a new daughter volume (e.g., GsimUserDetector).
 *
 *  The default material is G4_PLASTIC_SC_VINYLTOLUENE.
 *  The default color is blue.
 *  The GsimDetector::SetParameters call takes a vector of 7 doubles.
 *  They are (with default values in parenthesis):
 *  - start phi (0 degrees)
 *  - opening angle (360 degrees)
 *  - total z length (20mm)
 *  - tangent distance to inner surface at -z(10mm)
 *  - tangent distance to outer surface at -z(20mm)
 *  - tangent distance to inner surface at +z(15mm)
 *  - tangent distance to outer surface at +z(20mm)
 *
 *  Unlike when working with Geant4 directly, any lengths should
 *  be full-lengths, not half-lengths.
 */

class GsimPolycone2 : public GsimDetector
{
 public:
  /**
   *  @function GsimPolycone2
   *  @brief Constructor for GsimPolycone2
   *  @param name The name of the polycone.
   *  @param motherDetector A pointer to the mother volume.
   *  @param transV A Geant (CLHEP) translation vector.
   *  @param rotV A Geant (CLHEP) rotation vector.
   */
  GsimPolycone2(std::string name,
		GsimDetector* motherDetector,
		G4ThreeVector transV,
		G4ThreeVector rotV,
		int userFlag=0);
  
  /**
   *  @function ~GsimPolycone2
   *  @brief Destructor for GsimPolycone2.
   */
  virtual ~GsimPolycone2();

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
   *  @function GsimPolycone2
   *  @brief Constructor for GsimPolycone2.
   */

  void setDimension(G4Polycone* cone,
		    double p0,double p1,double p2,
		    double p3,double p4,double p5,double p6)  const;
  
  GsimPolycone2();

  virtual void ComputeDimensions(G4Box&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Trd&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Trap&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Cons&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Sphere&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Orb&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Torus&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Para&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Hype&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Tubs&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Polycone&,const G4int,const G4VPhysicalVolume*) const;
  virtual void ComputeDimensions (G4Polyhedra&,const G4int,const G4VPhysicalVolume*) const {}
};


#endif // GsimPolycone2_h
