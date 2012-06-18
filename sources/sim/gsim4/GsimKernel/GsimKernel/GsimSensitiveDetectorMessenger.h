/**
 *  @file
 *  @brief  GsimSensitiveDetectorMessenger
 *  $Id: GsimSensitiveDetectorMessenger.h,v 1.4 2007/02/04 12:55:41 nanjo Exp $
 *  $Log: GsimSensitiveDetectorMessenger.h,v $
 *  Revision 1.4  2007/02/04 12:55:41  nanjo
 *  Fast simulation 3 is added for shower check.
 *
 *  Revision 1.3  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 */

#ifndef GsimSensitiveDetectorMessenger_h
#define GsimSensitiveDetectorMessenger_h

// includes
#include "G4UImessenger.hh"
#include "globals.hh"
#include <string>

// forward declaration
class GsimSensitiveDetector;
class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithAnInteger;
class G4UIcmdWithABool;
class G4UIcmdWithAString;

/**
 *  @class GsimSensitiveDetectorMessenger
 *  @brief Messenger for GsimRunAction.
 *
 *  This class provide ...
 * 
 */


class GsimSensitiveDetectorMessenger : public G4UImessenger
{
public:
  /// Constructor.
  /**
   *  @param factory This parent factory class.
   */
  GsimSensitiveDetectorMessenger(GsimSensitiveDetector* sensitiveDetector);

  /// Destructor.
  virtual ~GsimSensitiveDetectorMessenger();

  /// Define action for UI
  void SetNewValue(G4UIcommand*, G4String aValue);
  
protected:

  /// parent factory class.
  GsimSensitiveDetector* m_sensitiveDetector;

  /// User Interface directory. 
  G4UIdirectory*          m_sensitiveDetectorDir;

  /// A user Interface command under the directory.
  G4UIcmdWithAnInteger*   m_cmdSetSensitiveMode;
  G4UIcmdWithABool*       m_cmdStoreHit;
  G4UIcmdWithABool*       m_cmdStoreDigi;
  G4UIcmdWithAnInteger*   m_cmdSetThisCopyNoFactor;
  G4UIcmdWithAnInteger*   m_cmdSetDeepCopyNoFactor;
  G4UIcmdWithAString*     m_cmdSetClusterID;
  G4UIcmdWithAString*     m_cmdSetOnlineVetoThreshold;
  G4UIcmdWithAString*     m_cmdSetTdcThreshold;
};

#endif //GsimSensitiveDetectorMessenger_h



