/**
 *  @file
 *  @brief  GsimDetectorConstruction
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimDetectorConstruction.h,v 1.3 2006/02/17 04:22:57 nanjo Exp $
 *  $Log: GsimDetectorConstruction.h,v $
 *  Revision 1.3  2006/02/17 04:22:57  nanjo
 *  GsimMaterialManager is added. Materials to be used hve to be decrlared before the 1st run.
 *
 *  Revision 1.2  2006/01/26 04:34:22  nanjo
 *  Factory pattern and template method on factory and messenger class is intorduced .
 *
 */

#ifndef GsimDetectorConstruction_h
#define GsimDetectorConstruction_h

// includes
#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4RunManager.hh"
#include "G4VisAttributes.hh"
#include "G4Box.hh"
#include "globals.hh"

// forward declaration
class G4VPhysicalVolume;
class G4Material;
class G4VSolid;
class GsimDetectorManager;
class GsimMaterialManager;



/**
 * @class GsimDetectorConstruction
 * @brief Mandatory DetectorConstruction class
 *
 * This class is a Geant4 mandatory class 
 * inherited from G4VUserDetectorConstruction. 
 * It provides G4VPhysicalVolume* for the World volume
 * to G4RunManager with its member function,
 * G4VPhysicalVolume* Construct().
 *
 */

class GsimDetectorConstruction : public G4VUserDetectorConstruction

{
public:

  /// Constructor.
  GsimDetectorConstruction(GsimDetectorManager* dm);
  
  /// Destructor.
  ~GsimDetectorConstruction();
  
  /// Construct World and give it to G4RunManager.
  /**
   *  Define materials at first.
   *  Construct World volume and
   *  give its G4VPhysicalVolume* to G4RunManager.
   *  This is a pure virtual method in G4VUserDetectorConstruction.
   */
  G4VPhysicalVolume* Construct();

  /// Provide G4VPhysicalVolume* of World.
  inline const G4VPhysicalVolume* getPhysiWorld();

  /// Set world material.
  inline void setWorldMaterial(G4Material* material);

  /// Set world size.
  inline void setWorldSize(G4ThreeVector vec);

  /// Set world material.
  inline void setWorldVisibility(bool isVisible);

  
 private:

  /// Construct the World volume.
  G4VPhysicalVolume* constructWorld();

  /// G4VPhysicalVolume* of the World
  G4VPhysicalVolume* m_physiWorld;

  /// G4LogicalVolume* of the World
  G4LogicalVolume*   m_logicWorld;

  /// G4VSolid* (G4Box*) of the World.
  G4Box*          m_solidWorld;

  /// G4VisAttributes* of the World
  G4VisAttributes*   m_worldVisAtt;

  /// DetectorManager.
  GsimDetectorManager* m_DM;
  GsimMaterialManager* m_materialManager;

  bool m_isConstructed;
};


inline const G4VPhysicalVolume* GsimDetectorConstruction::getPhysiWorld()
{
  return m_physiWorld;
}


#endif // GsimDetectorConstruction_h

