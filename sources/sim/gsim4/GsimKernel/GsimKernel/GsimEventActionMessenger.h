/**
 *  @file
 *  @brief  GsimEventActionMessenger
 *  $Id: GsimEventActionMessenger.h,v 1.10 2007/01/12 15:24:23 nanjo Exp $ 
 *  $Log: GsimEventActionMessenger.h,v $
 *  Revision 1.10  2007/01/12 15:24:23  nanjo
 *  Add flag to store empty data or not.
 *
 *  Revision 1.9  2006/12/09 21:34:09  nanjo
 *  briefHistory is corrected and dictionary write.
 *
 *  Revision 1.8  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 * 
 */

#ifndef GsimEventActionMessenger_h
#define GsimEventActionMessenger_h

// includes
#include "G4UImessenger.hh"
#include "globals.hh"

// forward declaration
class GsimEventAction;
class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithAnInteger;
class G4UIcmdWithABool;

/**
 *  @class GsimEventActionMessenger.
 *  @brief Messenger for GsimEventAction.
 *  This class is ...
 */


class GsimEventActionMessenger : public G4UImessenger
{
public:
  /// Constructor.
  /**
   *  @param factory This parent factory class.
   */
  
  GsimEventActionMessenger(GsimEventAction* eventAction);

  /// Destructor.
  virtual ~GsimEventActionMessenger();

  /// Define action for UI
  void SetNewValue(G4UIcommand*, G4String aValue);
  
protected:

  /// eventAction
  GsimEventAction* m_eventAction;

  /// User Interface directory. 
  G4UIdirectory*          m_eventActionDir;

  /// A user Interface command under the directory.
  G4UIcmdWithAnInteger*     m_cmdSetVisualizationMode;
  G4UIcmdWithAnInteger*     m_cmdSetDumpMode;
  G4UIcmdWithAnInteger*     m_cmdSetAccumulationNumber;
  G4UIcmdWithAnInteger*     m_cmdSetVerboseLevel;
  G4UIcmdWithABool*         m_cmdWriteDictionary;
  G4UIcmdWithABool*         m_cmdSetSkipEmptyData;
};

#endif //GsimEventActionMessenger_h



