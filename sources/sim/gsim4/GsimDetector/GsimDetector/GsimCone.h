/**
 *  @file
 *  @brief  GsimCone
 *  $Id: GsimCone.h,v 1.4 2006/12/06 19:14:30 nanjo Exp $
 *  $Log: GsimCone.h,v $
 *  Revision 1.4  2006/12/06 19:14:30  nanjo
 *  CVS variables.
 *
 */
#ifndef GsimCone_h
#define GsimCone_h

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
 *  @class GsimCone
 *  @brief This class provides a Gsim4 wrapper around G4Cone.
 *
 *  This class is usually called by the geometry definition class to
 *  define a new daughter volume (e.g., GsimUserDetector).
 *
 *  The default material is G4_PLASTIC_SC_VINYLTOLUENE.
 *  The default color is red.
 *  The GsimDetector::SetParameters call takes a vector of 3 doubles.
 *  They are (with default values in parenthesis):
 *  - radius at the small end (5mm)
 *  - radius at the big end (10mm)
 *  - total z length (10mm)
 *
 *  Unlike when working with Geant4 directly, any lengths should
 *  be full-lengths, not half-lengths.
 */
class GsimCone : public GsimDetector
{
 public:
  /**
   *  @function GsimCone
   *  @brief Constructor for GsimCone
   *  @param name The name of the cone.
   *  @param motherDetector A pointer to the mother volume.
   *  @param transV A Geant (CLHEP) translation vector.
   *  @param rotV A Geant (CLHEP) rotation vector.
   */
  GsimCone(std::string name,
	   GsimDetector* motherDetector,
	   G4ThreeVector transV,
	   G4ThreeVector rotV,
	   int userFlag=0);
  
  
  /**
   *  @function ~GsimCone
   *  @brief Destructor for GsimCone
   */
  virtual ~GsimCone();

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
   *  @function GsimCone
   *  @brief Constructor for GsimCone
   */
  GsimCone();

  virtual void ComputeDimensions(G4Box&, const G4int, const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Trd&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Trap&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Cons&,const G4int,const G4VPhysicalVolume*) const;
  virtual void ComputeDimensions (G4Sphere&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Orb&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Torus&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Para&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Hype&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Tubs&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Polycone&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Polyhedra&,const G4int,const G4VPhysicalVolume*) const {}
};


#endif // GsimCone_h
