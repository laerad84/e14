/**
 *  @file
 *  @brief  GsimBox
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimBox.h,v 1.3 2006/06/08 18:18:48 jfiggins Exp $
 *  $Log: GsimBox.h,v $
 *  Revision 1.3  2006/06/08 18:18:48  jfiggins
 *  Updated comments.
 *
 *  Revision 1.2  2006/06/05 16:54:36  jfiggins
 *  Inserted JavaDoc-style comments.
 *
 *  Revision 1.1  2006/01/26 06:11:19  nanjo
 *  Detector and data classes are added.
 *
 */
#ifndef GsimBox_h
#define GsimBox_h

//includes
#include <string>
#include "GsimKernel/GsimDetector.h"
#include "G4VPVParameterisation.hh"

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

//forward declaration

/**
 *  @class GsimBox
 *  @brief This class provides a Gsim4 wrapper around G4Box.
 *
 *  This class is usually called by the geometry definition class to
 *  define a new daughter volume (e.g., GsimUserDetector).
 *
 *  The default material is G4_PLASTIC_SC_VINYLTOLUENE.
 *  The default color is blue.
 *  The GsimDetector::SetParameters call takes a vector of 3 doubles.
 *  They are (with default values in parenthesis):
 *  - total x length (10mm)
 *  - total y length (10mm)
 *  - total z length (10mm)
 *
 *  Unlike when working with Geant4 directly, any lengths should
 *  be full-lengths, not half-lengths.
 */

class GsimBox : public GsimDetector
{
 public:
  /**
   *  @function GsimBox
   *  @brief Constructor for GsimBox.
   *  @param name The name of the box.
   *  @param motherDetector A pointer to the mother volume.
   *  @param transV A Geant (CLHEP) translation vector.
   *  @param rotV A Geant (CLHEP) rotation vector.
   */
  GsimBox(std::string name,
	  GsimDetector* motherDetector,
	  G4ThreeVector transV,
	  G4ThreeVector rotV,
	  int userFlag=0);
	  
  
  /**
   *  @function ~GsimBox
   *  @brief Destructor for GsimBox.
   */
  virtual ~GsimBox();

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
   *  @function GsimBox
   *  @brief Constructor for GsimBox.
   */
  GsimBox();

  virtual void ComputeDimensions(G4Box& box, const G4int copyNo, const G4VPhysicalVolume*) const;
  virtual void ComputeDimensions (G4Trd&,const G4int,const G4VPhysicalVolume*) const {}
  virtual void ComputeDimensions (G4Trap&,const G4int,const G4VPhysicalVolume*) const {}
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


#endif // GsimBox_h
