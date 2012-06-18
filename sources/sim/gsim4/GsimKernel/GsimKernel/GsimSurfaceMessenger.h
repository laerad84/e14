/**
 *  @file
 *  @brief  GsimSurfaceMessenger
 *  $Id: $
 *  $Log:$
 */

#ifndef GsimSurfaceMessenger_h
#define GsimSurfaceMessenger_h

// includes
#include "G4UImessenger.hh"
#include "globals.hh"
#include <string>

// forward declaration
class GsimSurface;
class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithABool;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAnInteger;
/**
 *  @class GsimSurfaceMessenger
 *  @brief Messenger for GsimSurface.
 *
 *  This class is owned by GsimSurface and
 *  provide ...
 */


class GsimSurfaceMessenger : public G4UImessenger
{
public:
  /// Constructor.
  /**
   *  @param factory This parent factory class.
   */
  GsimSurfaceMessenger(GsimSurface* surface);

  /// Destructor.
  virtual ~GsimSurfaceMessenger();

  /// Define action for UI
  void SetNewValue(G4UIcommand*, G4String aValue);
  
protected:

  /// parent factory class.
  GsimSurface* m_surface;

  /// User Interface directory. 
  G4UIdirectory*          m_surfaceDir;

  /// A user Interface command under the directory.
  G4UIcmdWithAString*        m_cmdSetSurfaceProperty;
  G4UIcmdWithAString*        m_cmdSetRefractiveIndex;
  G4UIcmdWithAString*        m_cmdSetReflectivity;
  G4UIcmdWithAString*        m_cmdSetEfficiency;
  G4UIcmdWithAString*        m_cmdSetProperty;
  G4UIcmdWithoutParameter*   m_cmdDump;
};

#endif //GsimSurfaceMessenger_h



