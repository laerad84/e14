/**
 *  @file
 *  @brief  GsimDetectorMessenger
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimDetectorMessenger.h,v 1.13 2006/12/07 18:28:58 nanjo Exp $
 *  $Log: GsimDetectorMessenger.h,v $
 *  Revision 1.13  2006/12/07 18:28:58  nanjo
 *  GsimDetector userInputs are implemented.
 *
 *  Revision 1.12  2006/08/01 05:27:55  nanjo
 *  GsimSpectrum is added. Debug print is updated. With/without Digi is implemented.
 *
 *  Revision 1.11  2006/06/21 11:47:56  nanjo
 *  BriefTrajectory classes are deleted.
 *
 *  Revision 1.10  2006/06/01 06:46:27  nanjo
 *  GsimUserLimit is added.
 *
 *  Revision 1.9  2006/05/31 19:42:24  nanjo
 *  GsimDetector::getWorldDetector is added and magnetic field is implemented.
 *
 *  Revision 1.8  2006/04/24 15:48:23  nanjo
 *  GsimDetector::setHitsStoreDaughters is added by Jeremy.
 *
 *  Revision 1.7  2006/04/12 13:07:07  nanjo
 *  GsimDetector::setHitsStore method is added, which can disable to store hits information.
 *
 *  Revision 1.6  2006/04/11 16:10:57  nanjo
 *  Add GsimDetector::clearThisClone function to the messenger.
 *
 *  Revision 1.5  2006/03/15 09:29:06  nanjo
 *  A function, setThisAndDaughersOuterVisibility, is added to GsimDetector class.
 *
 *  Revision 1.4  2006/03/01 12:45:32  nanjo
 *  A member function of GsimDetector, cloneDetector, is added and used in E391Detector.
 *
 *  Revision 1.3  2006/02/21 09:09:59  nanjo
 *  Sensitive detector name and channel id can be assigned. If the same sensitive detector name is used for some detectors, these detectors are recognized as channels in one detector.
 *
 *  Revision 1.2  2006/01/31 22:47:08  nanjo
 *  BriefTrajectory is built from G4VUserTrakInformation.
 *
 *  Revision 1.1  2006/01/26 04:53:30  nanjo
 *  Detector and persistency classes are added.
 *
 */

#ifndef GsimDetectorMessenger_h
#define GsimDetectorMessenger_h

// includes
#include "G4UImessenger.hh"
#include "globals.hh"
#include <string>

// forward declaration
class GsimDetector;
class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithABool;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAnInteger;
/**
 *  @class GsimDetectorMessenger
 *  @brief Messenger for GsimDetector.
 *
 *  This class is owned by GsimDetector and
 *  provide ...
 */


class GsimDetectorMessenger : public G4UImessenger
{
public:
  /// Constructor.
  /**
   *  @param factory This parent factory class.
   */
  GsimDetectorMessenger(GsimDetector* detector);

  /// Destructor.
  virtual ~GsimDetectorMessenger();

  /// Define action for UI
  void SetNewValue(G4UIcommand*, G4String aValue);
  
protected:

  /// parent factory class.
  GsimDetector* m_detector;

  /// User Interface directory. 
  G4UIdirectory*          m_detectorDir;

  /// A user Interface command under the directory.
  G4UIcmdWithAString*        m_cmdSetLocalCenterVector;
  G4UIcmdWithAString*        m_cmdSetTranslationVector;
  G4UIcmdWithAString*        m_cmdSetRotationVector;
  G4UIcmdWithAString*        m_cmdSetThisMagneticField;
  G4UIcmdWithAString*        m_cmdSetThisAndDaughterMagneticField;

  G4UIcmdWithAString*        m_cmdSetThisUserStepMax;
  G4UIcmdWithAString*        m_cmdSetThisUserTrackMax;
  G4UIcmdWithAString*        m_cmdSetThisUserTimeMax;
  G4UIcmdWithAString*        m_cmdSetThisUserEkinMin;
  G4UIcmdWithAString*        m_cmdSetThisUserRangeMin;
  G4UIcmdWithoutParameter*   m_cmdResetThisUserLimits;
  G4UIcmdWithAString*        m_cmdSetThisAndDaughterUserStepMax;
  G4UIcmdWithAString*        m_cmdSetThisAndDaughterUserTrackMax;
  G4UIcmdWithAString*        m_cmdSetThisAndDaughterUserTimeMax;
  G4UIcmdWithAString*        m_cmdSetThisAndDaughterUserEkinMin;
  G4UIcmdWithAString*        m_cmdSetThisAndDaughterUserRangeMin;
  G4UIcmdWithoutParameter*   m_cmdResetThisAndDaughterUserLimits;
  
  G4UIcmdWithAString*        m_cmdSetOuterMaterial;
  G4UIcmdWithAString*        m_cmdSetOuterColor;
  G4UIcmdWithABool*          m_cmdSetOuterVisibility;
  G4UIcmdWithABool*          m_cmdSetThisAndDaughterOuterVisibility;
  G4UIcmdWithAString*        m_cmdSetParameters;
  G4UIcmdWithAString*        m_cmdSetThisAsARootRegion;
  G4UIcmdWithAnInteger*      m_cmdSetFastSimulationLevel;
  G4UIcmdWithAnInteger*      m_cmdSetDaughterFastSimulationLevel;
  G4UIcmdWithAString*        m_cmdSetSensitiveVolume;
  G4UIcmdWithoutParameter*   m_cmdSetSensitiveDetector;
  G4UIcmdWithAString*        m_cmdSetSensitiveDetectorWithName;
  G4UIcmdWithABool*          m_cmdSetHitsStore;
  G4UIcmdWithABool*          m_cmdSetThisAndDaughterHitsStore;
  G4UIcmdWithABool*          m_cmdSetDigiStore;
  G4UIcmdWithABool*          m_cmdSetThisAndDaughterDigiStore;
  G4UIcmdWithAString*        m_cmdPlaceDetector;
  G4UIcmdWithAString*        m_cmdCloneDetector;
  G4UIcmdWithoutParameter*   m_cmdClearThisClone;
  G4UIcmdWithAString*        m_cmdSetThisAndDaughterBriefName;
  G4UIcmdWithoutParameter*   m_cmdPrint;
  G4UIcmdWithoutParameter*   m_cmdUpdate;
};

#endif //GsimDetectorMessenger_h



