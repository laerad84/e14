/**
 *  @file
 *  @brief  GsimDetectorManagerMessenger
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimDetectorManagerMessenger.h,v 1.2 2006/03/14 18:02:54 nanjo Exp $
 *  $Log: GsimDetectorManagerMessenger.h,v $
 *  Revision 1.2  2006/03/14 18:02:54  nanjo
 *  Fix outerMaterial of CC04 and CC05.
 *
 *  Revision 1.1  2006/01/26 04:53:30  nanjo
 *  Detector and persistency classes are added.
 *
 */

#ifndef GsimDetectorManagerMessenger_h
#define GsimDetectorManagerMessenger_h

// includes
#include "G4UImessenger.hh"
#include "globals.hh"
#include <string>

// forward declaration
class GsimDetectorManager;
class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithoutParameter;
/**
 *  @class GsimDetectorManagerMessenger
 *  @brief Messenger for GsimDetector.
 *
 *  This class is owned by GsimDetector and
 *  provide ...
 */


class GsimDetectorManagerMessenger : public G4UImessenger
{
public:
  /// Constructor.
  /**
   *  @param factory This parent factory class.
   */
  GsimDetectorManagerMessenger(GsimDetectorManager* detectorManager);

  /// Destructor.
  virtual ~GsimDetectorManagerMessenger();

  /// Define action for UI
  void SetNewValue(G4UIcommand*, G4String aValue);
  
protected:

  /// parent factory class.
  GsimDetectorManager* m_detectorManager;

  /// User Interface directory. 
  G4UIdirectory*          m_detectorManagerDir;

  /// A user Interface command under the directory.
  G4UIcmdWithoutParameter*   m_cmdPrint;
  G4UIcmdWithoutParameter*   m_cmdUpdate;
  G4UIcmdWithoutParameter*   m_cmdRedraw;
  G4UIcmdWithoutParameter*   m_cmdRenewMessenger;
};

#endif //GsimDetectorManagerMessenger_h



