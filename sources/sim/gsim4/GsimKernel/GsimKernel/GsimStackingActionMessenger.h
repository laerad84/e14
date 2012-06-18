/**
 *  @file
 *  @brief  GsimStackingActionMessenger
 *  $Id: GsimStackingActionMessenger.h,v 1.1 2007/02/04 12:14:38 nanjo Exp $
 *  $Log: GsimStackingActionMessenger.h,v $
 *  Revision 1.1  2007/02/04 12:14:38  nanjo
 *  GsimStackingAction is added.
 *
 */

#ifndef GsimStackingActionMessenger_h
#define GsimStackingActionMessenger_h

// includes
#include "G4UImessenger.hh"
#include "globals.hh"

// forward declaration
class GsimStackingAction;
class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithAString;

/**
 *  @class GsimStackingActionMessenger.
 *  @brief Messenger for GsimStackingAction.
 *  This class is ...
 */


class GsimStackingActionMessenger : public G4UImessenger
{
public:
  /// Constructor.
  GsimStackingActionMessenger(GsimStackingAction* stackingAction);

  /// Destructor.
  virtual ~GsimStackingActionMessenger();

  /// Define action for UI
  void SetNewValue(G4UIcommand*, G4String aValue);
  
protected:

  /// eventAction
  GsimStackingAction* m_stackingAction;

  /// User Interface directory. 
  G4UIdirectory*          m_stackingActionDir;

  /// A user Interface command under the directory.
  G4UIcmdWithAString*       m_cmdTriggerPrimaryEndZ;

  /// A user Interface command under the directory.
  G4UIcmdWithAString*       m_cmdSetBriefDtectorOrder;
};

#endif //GsimStackingActionMessenger_h



