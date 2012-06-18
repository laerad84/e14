/**
 *  @file
 *  @brief  GsimMaterialManagerMessenger
 *  $Id: GsimMaterialManagerMessenger.h,v 1.2 2006/12/06 18:44:00 nanjo Exp $ 
 *  $Log: GsimMaterialManagerMessenger.h,v $
 *  Revision 1.2  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 * 
 */

#ifndef GsimMaterialManagerMessenger_h
#define GsimMaterialManagerMessenger_h

// includes
#include "G4UImessenger.hh"
#include "globals.hh"

// forward declaration
class GsimMaterialManager;
class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithoutParameter;

/**
 *  @class GsimMaterialManagerMessenger.
 *  @brief Messenger for GsimMaterialManager.
 *  This class is ...
 */


class GsimMaterialManagerMessenger : public G4UImessenger
{
public:
  /// Constructor.
  /**
   *  @param factory This parent factory class.
   */
  
  GsimMaterialManagerMessenger(GsimMaterialManager* materialManager);

  /// Destructor.
  virtual ~GsimMaterialManagerMessenger();

  /// Define action for UI
  void SetNewValue(G4UIcommand*, G4String aValue);
  
protected:

  /// parent factory class.
  GsimMaterialManager* m_materialManager;

  /// User Interface directory. 
  G4UIdirectory*          m_materialManagerDir;

  /// A user Interface command under the directory.
  G4UIcmdWithAString*     m_cmdUseNistMaterial;
  G4UIcmdWithAString*     m_cmdMixElementByWeight;
  G4UIcmdWithAString*     m_cmdMixElementByNumber;

  G4UIcmdWithAString*      m_cmdSetProperty;
  G4UIcmdWithAString*      m_cmdSetConstProperty;
  G4UIcmdWithAString*      m_cmdDumpProperty;
  G4UIcmdWithoutParameter* m_cmdListMaterial;
};

#endif //GsimMaterialManagerMessenger_h



