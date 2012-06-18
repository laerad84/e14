/**
 *  @file
 *  @brief  GsimDetector
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimDetector.h,v 1.35 2007/02/04 12:55:41 nanjo Exp $
 *  $Log: GsimDetector.h,v $
 *  Revision 1.35  2007/02/04 12:55:41  nanjo
 *  Fast simulation 3 is added for shower check.
 *
 *  Revision 1.34  2006/12/07 18:28:58  nanjo
 *  GsimDetector userInputs are implemented.
 *
 *  Revision 1.33  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 *  Revision 1.32  2006/11/20 16:16:45  nanjo
 *  SensitiveDetectorList is kept in DetectorManager.
 *
 *  Revision 1.31  2006/10/24 15:23:07  nanjo
 *  SensitiveDetector is re-structred.
 *
 *  Revision 1.30  2006/10/19 03:28:44  nanjo
 *  GsimPersistencyManagerMessenger is replaced by GsimRunActionMessneger.
 *  Information of photonuclear interaction is not filled here.
 *  Cluster ID is filled.
 *  Now GsimPersistencyManager, GsimDigitizer, and, GsimMessage is
 *  independent of Geant4. They will be moved to different directory
 *  in order to use from ROOT analysis.
 *
 *  Revision 1.29  2006/09/08 13:53:25  nanjo
 *  Add absolute position.
 *
 *  Revision 1.28  2006/09/06 22:33:18  nanjo
 *  GsimDetectorData is added.
 *
 *  Revision 1.27  2006/08/01 05:27:55  nanjo
 *  GsimSpectrum is added. Debug print is updated. With/without Digi is implemented.
 *
 *  Revision 1.26  2006/06/22 14:22:22  nanjo
 *  Comment is added.
 *
 *  Revision 1.25  2006/06/22 11:38:57  nanjo
 *  Modifications around briefDetectorID and briefDetectorName.
 *
 *  Revision 1.24  2006/06/21 11:47:56  nanjo
 *  BriefTrajectory classes are deleted.
 *
 *  Revision 1.23  2006/06/09 17:47:01  jfiggins
 *  More comments.
 *
 *  Revision 1.22  2006/06/08 17:41:23  jfiggins
 *  Comments.
 *
 *  Revision 1.21  2006/06/04 09:50:21  nanjo
 *  Fast simulation level, 4,  is implemetned. As for the levle 5, the tracking
 *  is terminated when the step touch the volume. As for the level 4, the tracking
 *  is terminated when the step enter the volume, which is controled by UserLimits.
 *
 *  Revision 1.20  2006/06/01 06:46:27  nanjo
 *  GsimUserLimit is added.
 *
 *  Revision 1.19  2006/05/31 19:42:24  nanjo
 *  GsimDetector::getWorldDetector is added and magnetic field is implemented.
 *
 *  Revision 1.18  2006/04/24 15:48:23  nanjo
 *  GsimDetector::setHitsStoreDaughters is added by Jeremy.
 *
 *  Revision 1.17  2006/04/12 13:07:07  nanjo
 *  GsimDetector::setHitsStore method is added, which can disable to store hits information.
 *
 *  Revision 1.16  2006/04/12 12:07:17  nanjo
 *  Fix typo.
 *
 *  Revision 1.15  2006/04/11 12:39:24  nanjo
 *  Fix a bug for userEventData and GsimDetector::clearThisClone is added.
 *
 *  Revision 1.14  2006/03/17 08:02:13  nanjo
 *  Add a flag to disable GsimBreifTrajectory. Make faster for the detector loop.
 *
 *  Revision 1.13  2006/03/17 02:42:28  nanjo
 *  GsimVacuum is changed to GsimLowVacuum for some E391 detectors.
 *
 *  Revision 1.12  2006/03/15 09:29:06  nanjo
 *  A function, setThisAndDaughersOuterVisibility, is added to GsimDetector class.
 *
 *  Revision 1.11  2006/03/14 18:02:54  nanjo
 *  Fix outerMaterial of CC04 and CC05.
 *
 *  Revision 1.10  2006/03/14 16:11:51  nanjo
 *  Fix G4_Air to G4_AIR.
 *
 *  Revision 1.9  2006/03/05 13:29:46  nanjo
 *  CC02 is added. Fix a bug in GsimPolyhedra2.
 *
 *  Revision 1.8  2006/03/04 10:48:33  nanjo
 *  If a negative number, -n, is set for the detector channel, the copy number of n-th up detector is used.
 *
 *  Revision 1.7  2006/03/01 12:45:32  nanjo
 *  A member function of GsimDetector, cloneDetector, is added and used in E391Detector.
 *
 *  Revision 1.6  2006/02/21 09:09:59  nanjo
 *  Sensitive detector name and channel id can be assigned. If the same sensitive detector name is used for some detectors, these detectors are recognized as channels in one detector.
 *
 *  Revision 1.5  2006/02/02 21:54:02  nanjo
 *  E391 detector is sarted.
 *
 *  Revision 1.4  2006/01/31 22:47:08  nanjo
 *  BriefTrajectory is built from G4VUserTrakInformation.
 *
 *  Revision 1.3  2006/01/31 03:00:38  nanjo
 *  Detector ID and process ID are introduced and stored in TFile.
 *
 *  Revision 1.2  2006/01/30 02:42:07  nanjo
 *  Detector information is stored in persistencyManager.
 *
 *  Revision 1.1  2006/01/26 04:53:30  nanjo
 *  Detector and persistency classes are added.
 *
 */
#ifndef GsimDetector_h
#define GsimDetector_h

//includes
#include "GsimKernel/GsimDetectorContainer.h"
#include "GsimData/GsimDetectorData.h"

#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4VPVParameterisation.hh"

#include <string>
#include <vector>
#include <list>
#include <map>

//forward declaration
class GsimDetectorMessenger;
class G4Event;
class G4Track;
class G4Step;
class G4LogicalVolume;
class GsimSensitiveDetector;
class G4FieldManager;
class G4UniformMagField;
class G4UserLimits;
class G4TouchableHistory;
class GsimDigitizer;

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
 *  @class GsimDetector
 *  @brief GsimDetector is the superclass of the Gsim shapes.
 *  @see GsimBox
 *  @see GsimBoxWithAHole
 *  @see GsimCone
 *  @see GsimPolyhedra2
 *  @see GsimPolycone2
 *  @see GsimTrap
 *  @see GsimTube
 */


class GsimDetector : public G4VPVParameterisation
{
 public:

  /**
   *  @function GsimDetector
   *  @brief Constructor for GsimDetector
   *  @param name The name of the volume.
   *  @param motherDetector A pointer to the mother volume.
   *  @param transV A Geant (CLHEP) translation vector.
   *  @param rotV A Geant (CLHEP) rotation vector.
   *  @param userFlag User inputs at construction.
   */
  GsimDetector(std::string name,
	       GsimDetector* motherDetector,
	       G4ThreeVector transV,
	       G4ThreeVector rotV,
	       int userFlag=0);


  /**
   *  @function GsimDetector
   *  @brief Constructor for GsimDetector
   *  @param physiWorld A pointer to the world physical placement.
   *
   *  Call this constructor only for the world volume.
   */
  GsimDetector(G4VPhysicalVolume* physiWorld);

  /**
   *  @function ~GsimDetector
   *  @brief Destructor for GsimDetector
   */
  virtual ~GsimDetector();

  /**
   *  @function setDetectorID
   *  @brief Sets the detector ID.
   *  @param id The ID.
   *
   *  The detector's ID is, by default, set to
   *  its position in the vector of detectors.
   */
  inline void setDetectorID(int id);
  /**
   *  @function getDetectorID
   *  @brief Gets the detector ID.
   *  @return The ID.
   *
   *  The detector's ID is, by default,
   *  its position in the vector of detectors.
   */
  inline int  getDetectorID();


  inline int  getBriefDetectorID();

  
  /**
   *  @function getName
   *  @brief Gets the detector's name.
   *  @return The name.
   */
  inline std::string getName();
  /**
   *  @function getFullName
   *  @brief Gets the detector's name appended to its directory name.
   *  @return The full name.
   */
  inline std::string getFullName();
  /**
   *  @function getClassName
   *  @brief Gets the name of the class.
   *  @return The name of the class.
   *
   *  The subclasses of GsimDetector change the classname to their own.
   */
  inline std::string getClassName();
  /**
   *  @function getNumberOfParameters
   *  @brief Gets the number of parameters that this detector is expecting.
   *  @return The number of parameters.
   */
  inline unsigned int getNumberOfParameters();
  
  /**
   *  @function setLocalCenterVector
   *  @brief Defines the center of the detector.
   *  @param vec A Geant (CLHEP) 3-vector.
   */
  void   setLocalCenterVector(G4ThreeVector vec);
  /**
   *  @function setTranslationVector
   *  @brief Sets the translation vector.
   *  @param vec A Geant (CLHEP) translation vector.
   */
  void   setTranslationVector(G4ThreeVector vec);
  /**
   *  @function setRotationVector
   *  @brief Sets the rotation vector.
   *  @param vec A Geant (CLHEP) rotation vector.
   */
  void   setRotationVector(G4ThreeVector vec);
  /**
   *  @function setOuterMaterial
   *  @brief Sets the material of the detector.
   *  @param name The name of the material to use.
   *  @see GsimMaterialManager
   */
  void   setOuterMaterial(std::string name);
  /**
   *  @function setOuterColor
   *  @brief Sets the color of the detector.
   *  @param colorName The name of the color to use.
   *  @see GsimColor
   */
  void   setOuterColor(std::string colorName);
  /**
   *  @function setOuterVisibility
   *  @brief Sets whether the detector is to be drawn.
   *  @param vis True, if visible.
   */
  void   setOuterVisibility(bool vis);
  /**
   *  @function setThisAndDaughterOuterVisibility
   *  @brief Sets whether the detector and its daughters are to be drawn.
   *  @param vis True, if visible.
   */
  void   setThisAndDaughterOuterVisibility(bool vis);
  /**
   *  @function setOuterCopyNo
   *  @brief Sets the copy number of the detector.
   *  @param iCopy The copy number.
   */
  void   setOuterCopyNo(int iCopy);
  
  /**
   *  @function setThisAsARootRegion
   *  @brief Sets the root region.
   *  @param regionName The region.
   *  @param productionCut The production cut.
   */
  void   setThisAsARootRegion(std::string regionName,double productionCut=-1);
  
  /**
   *  @function setParameters
   *  @brief Sets the physical parameters of a volume.
   *  @param vec A vector of the parameters.
   *  @see GsimBox
   *  @see GsimBoxWithAHole
   *  @see GsimCone
   *  @see GsimPolyhedra2
   *  @see GsimPolycone2
   *  @see GsimTrap
   *  @see GsimTube
   *
   *  The number and meaning of parameters in the vector
   *  is determined by the volume's shape. Look at the
   *  classes that inherit from GsimDetector for details.
   */
  void   setParameters(std::vector<double> vec);
  /**
   *  @function setFastSimulationLevel
   *  @brief Sets the fast simulation level.
   *  @param level 0-6.
   *
   *  - 6 for special use. (E14/E391 fast simulation.)
   *         move CV and unsensitive strucutres to far upstream.
   *  - 5 very fast simulation ... stop when a step touch the volume
   *  - 4 very fast simulation ... stop when a step enter the volume
   *  - 3 shower off(conv, eBrem, annihil)
   *  - 2 ordering detector to be processed.
   *  - 1
   *  - 0 no fast simulation
   */
  virtual void   setFastSimulationLevel(int level);

  void   setDaughterFastSimulationLevel(int level);

  /**
   *  @function setSensitiveDetector
   *  @brief Attaches a sensitive detector to the detector.
   *  @param logicalVolumeName The name of the detector.
   *  @param SDName The name of the sensitive detector.
   *  @param withHit With hit map. (Default is true.)
   *  @param withDigi With digi map. (Default is true.)
   *  @param withHitProcesser WithThisHitProcesser. (Defalut is false.)  
   *
   *  The logical volume is sensitive. Each channel ID for the physicalVolume
   *  included in the logical volume is the same as its copy number.
   */
  void   setSensitiveDetector(std::string logicalVolumeName,std::string SDName,
			      bool withHit=false, bool withDigi=true,
			      GsimDetector* hitProcesser=0,
			      GsimDigitizer* digi=0);

  /**
   *  @function setSensitiveDetector
   *  @brief Attaches a sensitive detector to the detector.
   *  @param SDName The name of the sensitive detector. (Default is "".)
   *  @param channel The channel number. (Default is -999.)
   *  @param withHit With hit map. (Default is true.)
   *  @param withDigi With digi map. (Default is true.)
   *
   *  The outer physical volume is sensitive and its copy number is the channel.
   *  Other physical volume in the logical volume have
   *  channels which is the same as the copy numbers. This detector is used for
   *  hitProcesser for the sensitive detector.
   */
  void   setSensitiveDetector(std::string SDname="",int channel=-999,
			      bool withHit=false, bool withDigi=true,
			      GsimDetector* hitProcesser=0,
			      GsimDigitizer* digi=0);

  void   unsetSensitiveDetector(std::string logicalVolumeName);
  void   unsetSensitiveDetector();

  void   setHitsStore(std::string logicalVolumeName,bool withHit);
  void   setHitsStore(bool withHit);
  void   setHitsStoreDaughters(bool withHit);
  void   setThisAndDaughterHitsStore(bool withHit);

  void   setDigiStore(std::string logicalVolumeName,bool withDigi);
  void   setDigiStore(bool withDigi);
  void   setDigiStoreDaughters(bool withDigi);
  void   setThisAndDaughterDigiStore(bool withDigi);

  void   setThisAndDaughterMagneticField(G4ThreeVector magneticFieldVector);
  void   setThisMagneticField(G4ThreeVector magneticFieldVector);

  
  void   setThisUserStepMax(double cut);
  void   setThisUserTrackMax(double cut);
  void   setThisUserTimeMax(double cut);
  void   setThisUserEkinMin(double cut);
  void   setThisUserRangeMin(double cut);
  void   resetThisUserLimits();
  void   setThisAndDaughterUserStepMax(double cut);
  void   setThisAndDaughterUserTrackMax(double cut);
  void   setThisAndDaughterUserTimeMax(double cut);
  void   setThisAndDaughterUserEkinMin(double cut);
  void   setThisAndDaughterUserRangeMin(double cut);
  void   resetThisAndDaughterUserLimits();
  
  /**
   *  @function print
   *  @brief Prints the status of the detector.
   */  
  void   print();
  void   update();
  void   updateField();
  void   updateUserLimits();

  static GsimDetector* getWorldDetector();

  
  void   deleteMessenger();
  void   newMessenger();
  
  void   placeDetector(GsimDetector* motherDetector,
		       G4ThreeVector transV,
		       G4ThreeVector rotV);
  
  void   cloneDetector(G4ThreeVector transV,
		       G4ThreeVector rotV,
		       int copyNo=-999);

  inline std::string getBriefName();
  void setBriefName(std::string briefname);
  void setThisAndDaughterBriefName(std::string briefname);
  
  void defaultBeginOfRunAction();
  void defaultEndOfRunAction();
  bool defaultBeginOfEventAction(const G4Event* evt);
  bool defaultEndOfEventAction(const G4Event* evt);
  /// default stepping action
  /**
   *  default stepping action for the detector at psotStep.
   *  Currently treatment of the fast simulation is done.
   */
  bool defaultSteppingAction(const G4Step* theStep);
  bool defaultPreTrackingAction(const G4Track* aTrack);
  bool defaultPostTrackingAction(const G4Track* aTrack);
  
  
  
  virtual void beginOfRunAction();
  virtual void endOfRunAction();
  
  virtual bool beginOfEventAction(const G4Event* evt);
  virtual bool endOfEventAction(const G4Event* evt);
  
  virtual bool steppingAction(const G4Step* theStep);

  virtual bool preTrackingAction(const G4Track* aTrack);
  virtual bool postTrackingAction(const G4Track* aTrack);

  virtual void processHits(const G4Step* aStep,G4TouchableHistory* ROhist);

  inline GsimDetector*      getMotherDetector();
  inline G4VPhysicalVolume* getPhysiDetector();

  std::string                getDirectoryName();
  G4VPhysicalVolume*         getMotherPhysiDetector();

  G4ThreeVector getRealTranslationVectorFromMotherPhysi(G4ThreeVector thisTraV);
  void          setRealTranslationFromMotherPhysi();
  void          computeRealRotationMatrixFromMotherPhysi();
  
  GsimDetector*              getMotherDetectorWithPhysi();
  inline G4ThreeVector       getLocalCenterVector();
  inline G4ThreeVector       getTranslationVector();
  inline G4ThreeVector       getRotationVector();

  G4ThreeVector              getAbsolutePosition(G4ThreeVector relativePosition);

  inline bool isModified();
  inline void modificationDone();
  bool addDaughter(GsimDetector* daughter);
  GsimDetector* findDetectorFromThis(std::string fullName);
  GsimDetector* findDetectorFromWorld(std::string fullName);
  void listDaughterDetector(std::list<GsimDetector*>& detList);
  void listFirstDaughterDetectorWihtPhysi(std::list<G4VPhysicalVolume*>& pvList);
  GsimSensitiveDetector* countSensitiveDetectorUnderThisDetector(int& counter);
  inline std::list<G4VPhysicalVolume*> getClonedPhysicalVolumeList();
  void clearThisClone();

  void fillDetectorData(GsimDetectorData& data);

  std::list<GsimSensitiveDetector*> getSensitiveDetectorList();
  std::list<GsimSensitiveDetector*> getThisAndDaughterSensitiveDetectorList();  
  
 protected:
  virtual void updateParametersEtc();
  virtual void constructPhysiDetector();
  
  GsimDetector();

  void setupSensitiveDetector();

  bool isCloneable();
  
  void doCloneDetector();
  

  GsimDetectorMessenger* m_messenger;
  std::string m_name;
  std::string m_briefName;
  std::string m_className;

  /**
   *  @brief This ID is assigned by the detector manager.
   *  @see GsimDetectorManager
   */
  int         m_detectorID;

  int         m_briefDetectorID;

  GsimDetector* m_motherDetector;
  G4VPhysicalVolume* m_physiDetector;
  G4ThreeVector m_localCenterVector;
  G4ThreeVector m_translationVector;
  G4ThreeVector m_rotationVector;
  G4RotationMatrix* m_rotationMatrix;

  G4FieldManager*    m_fieldManager;
  G4UniformMagField* m_magneticField;
  G4ThreeVector      m_magneticFieldVector;

  G4UserLimits* m_userLimits;
  double m_userLimitsStepMax;
  double m_userLimitsTrackMax;
  double m_userLimitsTimeMax;
  double m_userLimitsEkinMin;
  double m_userLimitsRangeMin;
  

  int         m_outerCopyNo;
  std::string m_outerMaterialName;
  std::string m_outerColorName;
  bool        m_isOuterVisible;
  

  unsigned int m_numberOfParameters;
  double* m_parameterArray;
  bool    m_isModified;
  
  /**
   *  @brief The fast simulation level.
   *
   *  5 very fast simulation ... stop when a step touch the volume
   *  4 very fast simulation ... stop when a step enter the volume
   *  3
   *  2
   *  1
   *  0 no fast simulation
   */
  int     m_fastSimulationLevel;

  /**
   *  @user flag
   *
   */
  int     m_userFlag;
  
  
  GsimDetectorContainer m_daughterDetectorContainer;
  static GsimDetector* s_worldDetector;

  /**
   *  @brief logicalVolume -> GsimSensitiveDetectorName*
   */
  std::map<G4LogicalVolume*,GsimSensitiveDetector*> m_sensitiveDetectorMap;
  
  static std::list<std::string> s_briefDetectorNameList;

  std::list<G4VPhysicalVolume*>   m_clonedPhysicalVolumeList;
  std::list<int>                  m_clonedCopyNoList;
  std::list<G4ThreeVector>        m_clonedTranslationVectorList;
  std::list<G4ThreeVector>        m_clonedRotationVectorList;
  std::list<G4RotationMatrix*>    m_clonedRotationMatrixList;

  void scanThisAndDaughterSensitiveDetector(std::list<GsimSensitiveDetector*>& allList);


  virtual void ComputeTransformation(const G4int copyNo, G4VPhysicalVolume* physVol) const;
  virtual void ComputeDimensions(G4Box&, const G4int, const G4VPhysicalVolume*) const {}
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


inline void GsimDetector::setDetectorID(int id) {
  m_detectorID  = id;
}

inline int GsimDetector::getDetectorID() {
  return m_detectorID;
}

inline int GsimDetector::getBriefDetectorID() {
  return m_briefDetectorID;
}


inline std::string GsimDetector::getName() {
  return m_name;
}

inline std::string GsimDetector::getClassName() {
  return m_className;
}

inline std::string GsimDetector::getFullName() {
  std::string fullname = getDirectoryName();
  fullname += m_name;
  return fullname;
}

inline std::string GsimDetector::getBriefName() {
  return m_briefName;
}
     

inline unsigned int GsimDetector::getNumberOfParameters() {
  return m_numberOfParameters;
}

inline GsimDetector* GsimDetector::getMotherDetector() {
  return m_motherDetector;
}

inline G4VPhysicalVolume* GsimDetector::getPhysiDetector() {
  return m_physiDetector;
}

inline G4ThreeVector GsimDetector::getLocalCenterVector() {
  return m_localCenterVector;
}

inline G4ThreeVector GsimDetector::getTranslationVector() {
  return m_translationVector;
}

inline G4ThreeVector GsimDetector::getRotationVector() {
  return m_rotationVector;
}

inline bool GsimDetector::isModified() {
  return m_isModified;
}

inline void GsimDetector::modificationDone() {
  m_isModified=false;
}

inline std::list<G4VPhysicalVolume*> GsimDetector::getClonedPhysicalVolumeList()
{
  return m_clonedPhysicalVolumeList;
}

#endif // GsimDetector_h
