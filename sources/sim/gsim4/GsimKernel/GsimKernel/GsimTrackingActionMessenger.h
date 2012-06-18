/**
 *  $Id: GsimTrackingActionMessenger.h,v 1.5 2007/02/04 12:25:46 nanjo Exp $ 
 *  $Log: GsimTrackingActionMessenger.h,v $
 *  Revision 1.5  2007/02/04 12:25:46  nanjo
 *  SetTrackHistory is added.
 *
 *  Revision 1.4  2006/12/09 21:34:09  nanjo
 *  briefHistory is corrected and dictionary write.
 *
 *  Revision 1.3  2006/12/09 00:45:06  nanjo
 *  dump.
 *
 *  Revision 1.2  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 * 
 */

#ifndef GsimTrackingActionMessenger_h
#define GsimTrackingActionMessenger_h

// includes
#include "G4UImessenger.hh"
#include "globals.hh"

// forward declaration
class GsimTrackingAction;
class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithABool;
class G4UIcmdWithAnInteger;
class G4UIcmdWithoutParameter;

/**
 *  @class GsimTrackingActionMessenger.
 *  @brief Messenger for GsimTrackingAction.
 *  This class is ...
 */


class GsimTrackingActionMessenger : public G4UImessenger
{
public:
  /// Constructor.
  /**
   *  @param factory This parent factory class.
   */
  
  GsimTrackingActionMessenger(GsimTrackingAction* trackingAction);

  /// Destructor.
  virtual ~GsimTrackingActionMessenger();

  /// Define action for UI
  void SetNewValue(G4UIcommand*, G4String aValue);
  
protected:

  /// eventAction
  GsimTrackingAction* m_trackingAction;

  /// User Interface directory. 
  G4UIdirectory*          m_trackingActionDir;

  /// A user Interface command under the directory.
  G4UIcmdWithABool*     m_cmdSetBriefTrackStore;
  G4UIcmdWithABool*     m_cmdSetForceStorePrimary;
  G4UIcmdWithABool*     m_cmdSetTrackHistory;
  G4UIcmdWithABool*     m_cmdSetTrackDump;
  G4UIcmdWithAnInteger* m_cmdAddPIDToMonitor;
  G4UIcmdWithoutParameter* m_cmdClearPIDToMonitor;
  G4UIcmdWithAnInteger* m_cmdAddPIDToTrigger;
  G4UIcmdWithoutParameter* m_cmdClearPIDToTrigger;
  G4UIcmdWithAnInteger* m_cmdAddPIDToKill;
  G4UIcmdWithoutParameter* m_cmdClearPIDToKill;
  G4UIcmdWithABool*     m_cmdSetStoreAllTracks;
};

#endif //GsimTrackingActionMessenger_h



