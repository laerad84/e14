/**
 *  @file
 *  @brief  GsimUtil
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimUtil.h,v 1.6 2006/12/04 17:27:49 nanjo Exp $
 *  $Log: GsimUtil.h,v $
 *  Revision 1.6  2006/12/04 17:27:49  nanjo
 *  Data are kept in each class, which are registered to persistencyManger.
 *  GsimPersistencyManger::setBranchOf is added then UserEventData is removed.
 *
 *  Revision 1.5  2006/10/24 15:23:08  nanjo
 *  SensitiveDetector is re-structred.
 *
 *  Revision 1.4  2006/06/09 17:46:30  jfiggins
 *  Added Javadoc-style Doxygen comments.
 *
 *  Revision 1.3  2006/03/04 10:48:33  nanjo
 *  If a negative number, -n, is set for the detector channel, the copy number of n-th up detector is used.
 *
 *  Revision 1.2  2006/01/30 02:42:07  nanjo
 *  Detector information is stored in persistencyManager.
 *
 *  Revision 1.1  2006/01/26 04:53:30  nanjo
 *  Detector and persistency classes are added.
 *
 */

#ifndef GsimUtil_h
#define GsimUtil_h

//includes
#include "G4ThreeVector.hh"
#include "G4Color.hh"
#include <string>
#include <list>

//forward declarations
class G4VPhysicalVolume;
class G4VSensitiveDetector;
class G4LogicalVolume;
class G4Material;

/**
 *  @class GsimUtil
 *  @brief Provides some common utilities.
 */
class GsimUtil
{
public:
  /**
   *  @function ~GsimUtil
   *  @brief Destructor for GsimUtil
   */
  virtual ~GsimUtil();
  /**
   *  @function getUtil
   *  @brief Returns a pointer to this.
   *  @return The instance of this.
   */
  static GsimUtil* getUtil();

  /**
   *  @function getVolumeName
   *  @brief Gets the name of the volume at the specified point.
   *  @param vec A Geant4 (CLHEP) 3-vector defining the point.
   *  @return The name of the volume at the point.
   */
  static std::string getVolumeName(const G4ThreeVector &vec);

  /**
   *  @function tail
   *  @brief Removes trailing whitespace from a string.
   *  @param lin The string.
   */
  void tail(G4String& lin);
  /**
   *  @function head
   *  @brief Removes leading whitespace from a string.
   *  @param lin The string.
   *
   *  The input string is modified.
   */
  void head(G4String& lin);
  /**
   *  @function shift
   *  @brief Takes the first token (whitespace separated) from a string.
   *  @param lin The input string. The first token is removed.
   *  @param out The first token of lin.
   *  @return True, if lin is non-empty, otherwise out is unmodified.
   *
   *  Both input strings are modified.
   */
  bool shift(G4String& lin, G4String& out);
  /**
   *  @function interpret
   *  @brief Takes a mathematical expression (string) and returns its value.
   *  @param word The math expression.
   *  @return The value of the expression.
   *
   *  Uses CLHEP's Evaluator to evaluate the expression. The system of units
   *  used is meter, kilogram, second, ampere, Kelvin, mole, candela.
   */
  double interpret(G4String word); 
  
  /**
   *  @function getPhysiWorld
   *  @brief Gets the physical placement of the world.
   *  @return The physical volume pointer.
   */
  G4VPhysicalVolume* getPhysiWorld();

  /**
   *  @function findColor
   *  @brief Gets the color.
   *  @return The color.
   *  @see GsimColor
   */
  G4Color       findColor(std::string colorName);
  /**
   *  @function findMaterial
   *  @brief Gets the material.
   *  @return The material.
   *  @see GsimMaterialManager
   */
  G4Material*   findMaterial(std::string matname,bool isVerbose=true);
  
  /**
   *  @function scanDaughterLogicalVolume
   *  @brief Pushes the logical volume and its daughters onto the list.
   *  @param lv The logical volume.
   *  @param lvl The list.
   */
  void scanDaughterLogicalVolume(G4LogicalVolume* lv,
				 std::list<G4LogicalVolume*>& lvl);
  /**
   *  @function scanDaughterPhysicalVolume
   *  @brief Pushes the physical volume and its daughters onto the list.
   *  @param pv The physical volume.
   *  @param pvl The list.
   */
  void scanDaughterPhysicalVolume(G4VPhysicalVolume* pv,
				  std::list<G4VPhysicalVolume*>& pvl);

  /**
   *  @function findDaughterLogicalVolume
   *  @brief Finds the daughter of a logical volume.
   *  @param lv The parent.
   *  @param name The name of the daughter.
   *  @return The daughter.
   */
  G4LogicalVolume* findDaughterLogicalVolume(G4LogicalVolume* lv,std::string name);

  G4VSensitiveDetector* getSensitiveDetector(std::string sdName);
  
  void fillPhysicalVolumeRelation(G4VPhysicalVolume* pv,
				  std::map<G4VPhysicalVolume*,G4VPhysicalVolume*>& pvr,
				  std::list<G4VPhysicalVolume*>& pvend);
  void fillPhysicalVolumeRelationFromWorld(std::map<G4VPhysicalVolume*,G4VPhysicalVolume*>& pvr,
					   std::list<G4VPhysicalVolume*>& pvend);
  void fillPhysicalVolumeRelationFromWorld(std::map<G4VPhysicalVolume*,G4VPhysicalVolume*>& pvr);

  /// add Cerenkov process. (default: no Cerenkov)
  /**
   * This can be called before the 1st run in PreInit state.
   */
  void addCerenkov();

  /// add GsimUserLimits process.  (default: with GsimUserLimits)
  /**
   * This can be called before the 1st run in PreInit state.
   */
  void withUserLimits(bool withUL);
 private:
  /**
   *  @function GsimUtil
   *  @brief Constructor for GsimUtil
   */
  GsimUtil();
  /**
   *  The instance of this.
   */
  static GsimUtil* s_util;


  static bool s_withCerenkov;
};


#endif // GsimUtil_h

