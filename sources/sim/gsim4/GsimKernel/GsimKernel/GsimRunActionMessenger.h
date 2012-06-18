/**
 *  @file
 *  @brief  GsimRunActionMessenger
 *  $Id: GsimRunActionMessenger.h,v 1.3 2006/12/06 18:44:00 nanjo Exp $
 *  $Log: GsimRunActionMessenger.h,v $
 *  Revision 1.3  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 */

#ifndef GsimRunActionMessenger_h
#define GsimRunActionMessenger_h

// includes
#include "G4UImessenger.hh"
#include "globals.hh"
#include <string>

// forward declaration
class GsimRunAction;
class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithAnInteger;
class G4UIcmdWithAString;

/**
 *  @class GsimRunActionMessenger
 *  @brief Messenger for GsimRunAction.
 *
 *  This class provide ...
 * 
 */


class GsimRunActionMessenger : public G4UImessenger
{
public:
  /// Constructor.
  /**
   *  @param factory This parent factory class.
   */
  GsimRunActionMessenger(GsimRunAction* persistencyManager);

  /// Destructor.
  virtual ~GsimRunActionMessenger();

  /// Define action for UI
  void SetNewValue(G4UIcommand*, G4String aValue);
  
protected:

  /// parent factory class.
  GsimRunAction* m_runAction;

  /// User Interface directory. 
  G4UIdirectory*          m_runActionDir;

  /// A user Interface command under the directory.
  G4UIcmdWithAnInteger*   m_cmdSetRunIDBase;
  G4UIcmdWithAnInteger*   m_cmdSetCycleOfEventSeedStore;
  G4UIcmdWithAnInteger*   m_cmdSetSeed;
  G4UIcmdWithAString*     m_cmdDumpSeed;
  G4UIcmdWithAString*     m_cmdLoadSeed;
};

#endif //GsimRunActionMessenger_h



