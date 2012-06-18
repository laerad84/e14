/**
 *  @file
 *  @brief  GsimSpectrumMessenger
 *  $Id: GsimSpectrumMessenger.h,v 1.2 2006/12/06 18:44:00 nanjo Exp $ 
 *  $Log: GsimSpectrumMessenger.h,v $
 *  Revision 1.2  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 * 
 */

#ifndef GsimSpectrumMessenger_h
#define GsimSpectrumMessenger_h

// includes
#include "G4UImessenger.hh"
#include "globals.hh"

// forward declaration
class GsimSpectrum;
class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithoutParameter;

/**
 *  @class GsimSpectrumMessenger.
 *  @brief Messenger for GsimSpectrum.
 *  This class is ...
 */


class GsimSpectrumMessenger : public G4UImessenger
{
public:
  /// Constructor.
  /**
   *  @param factory This parent factory class.
   */
  
  GsimSpectrumMessenger(GsimSpectrum* spectrum);

  /// Destructor.
  virtual ~GsimSpectrumMessenger();

  /// Define action for UI
  void SetNewValue(G4UIcommand*, G4String aValue);
  
protected:

  /// parent factory class.
  GsimSpectrum* m_spectrum;

  /// User Interface directory. 
  G4UIdirectory*          m_spectrumDir;

  /// A user Interface command under the directory.
  G4UIcmdWithAString*      m_cmdAddSpectrum;
  G4UIcmdWithAString*      m_cmdSetParameter;
  G4UIcmdWithoutParameter* m_cmdClear;
};

#endif //GsimSpectrumMessenger_h



