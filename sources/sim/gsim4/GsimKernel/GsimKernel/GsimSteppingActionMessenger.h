/**
 *  @file
 *  @brief  GsimSteppingActionMessenger
 *  $Id: GsimSteppingActionMessenger.h,v 1.2 2006/12/06 18:44:00 nanjo Exp $ 
 *  $Log: GsimSteppingActionMessenger.h,v $
 *  Revision 1.2  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 * 
 */

#ifndef GsimSteppingActionMessenger_h
#define GsimSteppingActionMessenger_h

// includes
#include "G4UImessenger.hh"
#include "globals.hh"

// forward declaration
class GsimSteppingAction;
class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithAString;

/**
 *  @class GsimSteppingActionMessenger.
 *  @brief Messenger for GsimSteppingAction.
 *  This class is ...
 */


class GsimSteppingActionMessenger : public G4UImessenger
{
public:
  /// Constructor.
  /**
   *  @param factory This parent factory class.
   */
  
  GsimSteppingActionMessenger(GsimSteppingAction* steppingAction);

  /// Destructor.
  virtual ~GsimSteppingActionMessenger();

  /// Define action for UI
  void SetNewValue(G4UIcommand*, G4String aValue);
  
protected:

  /// eventAction
  GsimSteppingAction* m_steppingAction;

  /// User Interface directory. 
  G4UIdirectory*          m_steppingActionDir;

  /// A user Interface command under the directory.
  G4UIcmdWithAString*       m_cmdSetParticleColor;
};

#endif //GsimSteppingActionMessenger_h



