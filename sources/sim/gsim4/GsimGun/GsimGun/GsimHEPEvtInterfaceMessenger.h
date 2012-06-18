/**
 *  @file
 *  @brief  GsimHEPEvtInterfaceMessenger
 *  $Id: 
 *  $Log: 
 */

#ifndef GsimHEPEvtInterfaceMessenger_h
#define GsimHEPEvtInterfaceMessenger_h

// includes
#include "G4UImessenger.hh"
#include "globals.hh"

// forward declaration
class GsimHEPEvtInterface;
class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;

/**
 *  @class GsimHEPEvtInterfaceMessenger
 *  @brief Messenger for GsimGunManager.
 */
class GsimHEPEvtInterfaceMessenger : public G4UImessenger
{
public:
  /**
   *  @function GsimHEPEvtInterfaceMessenger
   *  @brief Constructor for GsimHEPEvtInterfaceMessenger
   *  @param hepEvt Pointer to the gun manager.
   */
  GsimHEPEvtInterfaceMessenger(GsimHEPEvtInterface* hepEvt);

  /**
   *  @function ~GsimHEPEvtInterfaceMessenger
   *  @brief Destructor for GsimHEPEvtInterfaceMessenger
   */
  virtual ~GsimHEPEvtInterfaceMessenger();

  /**
   *  @function SetNewValue
   *  @brief Defines a new UI action
   *  @param command The command.
   *  @param newValue The new value.
   */
  void SetNewValue(G4UIcommand*, G4String);
  
protected:

  /**
   *  @brief Parent factory class - gun manager.
   */
  GsimHEPEvtInterface* m_hepEvtInterface;

  /**
   *  @brief User interface directory.
   */
  G4UIdirectory*                     m_dir;

  /**
   *  @brief User interface command.
   */
  G4UIcmdWithAString* m_cmdSetInputFileName;
  /**
   *  @brief User interface command.
   */
  G4UIcmdWithAString* m_cmdSetInputEventDataFileName;
  /**
   *  @brief User interface command.
   */
  G4UIcmdWithAString* m_cmdSetVertexPosition;
  /**
   *  @brief User interface command.
   */
  G4UIcmdWithAString* m_cmdSetVertexTime;
  /**
   *  @brief User interface command.
   */
  G4UIcmdWithAString* m_cmdConvertToRootFile;
  /**
   *  @brief User interface command.
   */
  G4UIcmdWithAnInteger* m_cmdGotoEventNumber;

  /**
   *  @brief User interface command.
   */
  G4UIcmdWithAString* m_cmdSetZeroPIDParticle;
  
};

#endif //GsimHEPEvtInterfaceMessenger_h

