/**
 *  @file
 *  @brief  GsimTube
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimTube.h,v 1.3 2006/06/08 18:18:48 jfiggins Exp $
 *  $Log: GsimTube.h,v $
 *  Revision 1.3  2006/06/08 18:18:48  jfiggins
 *  Updated comments.
 *
 *  Revision 1.2  2006/06/05 17:02:10  jfiggins
 *  Inserted JavaDoc-style comments.
 *
 *  Revision 1.1  2006/01/26 06:11:19  nanjo
 *  Detector and data classes are added.
 *
 */
#ifndef GsimTube_h
#define GsimTube_h

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
 *  @class GsimTube
 *  @brief This class provides a Gsim4 wrapper around G4Tube.
 *
 *  This class is usually called by the geometry definition class to
 *  define a new daughter volume (e.g., GsimUserDetector).
 *
 *  The default material is G4_PLASTIC_SC_VINYLTOLUENE.
 *  The default color is red.
 *  The GsimDetector::SetParameters call takes a vector of 5 doubles.
 *  They are (with default values in parenthesis):
 *  - inner radius (0mm)
 *  - outer radius (10mm)
 *  - total z length (10mm)
 *  - start phi (0 degrees)
 *  - opening angle (360 degrees)
 *
 *  Unlike when working with Geant4 directly, any lengths should
 *  be full-lengths, not half-lengths.
 */

class GsimTube : public GsimDetector
{
 public:
  /**
   *  @function GsimTube
   *  @brief Constructor for GsimTube.
   *  @param name The name of the tube.
   *  @param motherDetector A pointer to the mother volume.
   *  @param transV A Geant (CLHEP) translation vector.
   *  @param rotV A Geant (CLHEP) rotation vector.
   */
  GsimTube(std::string name,
	   GsimDetector* motherDetector,
	   G4ThreeVector transV,
	   G4ThreeVector rotV,
	   int userFlag=0);
  
  /**
   *  @function ~GsimTube
   *  @brief Destructor for GsimTube.
   */
  virtual ~GsimTube();

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
   *  @function GsimTube
   *  @brief Constructor for GsimTube.
   */
  GsimTube();

  virtual void ComputeDimensions(G4Box&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Trd&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Trap&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Cons&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Sphere&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Orb&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Torus&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Para&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Hype&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Tubs&,const G4int,const G4VPhysicalVolume*) const;
  virtual void ComputeDimensions (G4Polycone&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Polyhedra&,const G4int,const G4VPhysicalVolume*) const {}
};


#endif // GsimTube_h
