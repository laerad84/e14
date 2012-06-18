/**
 *  @file
 *  @brief  GsimSteppingAction
 *  @author Hajime Nanjo <nanjo@scphys.kyoto-u.ac.jp>
 *  @date   2005.10.5
 *  $Id: GsimSteppingAction.h,v 1.4 2006/11/17 10:48:44 nanjo Exp $
 *  $Log: GsimSteppingAction.h,v $
 *  Revision 1.4  2006/11/17 10:48:44  nanjo
 *  Particle colors can be changed.
 *
 *  Revision 1.3  2006/06/14 05:53:19  nanjo
 *  Default particle color is changed.
 *
 *  Revision 1.2  2006/03/15 05:33:20  nanjo
 *  EventActionMessegner is added.
 *
 *  Revision 1.1  2006/01/26 04:53:30  nanjo
 *  Detector and persistency classes are added.
 *
 */
#ifndef GsimSteppingAction_h
#define GsimSteppingAction_h

//includes
#include "G4UserSteppingAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4Color.hh"
#include "globals.hh"

#include <string>
#include <map>

//forward declaration
class GsimDetectorManager;
class GsimSteppingActionMessenger;
class G4Step;

/**
 *  @class GsimSteppingAction
 *  @brief SteppingAction
 *
 *  This class provides ...
 */

class GsimSteppingAction : public G4UserSteppingAction
{
public:
  GsimSteppingAction(GsimDetectorManager* dm);
  virtual ~GsimSteppingAction();
  virtual void UserSteppingAction(const G4Step*);

  void setVisualizationMode(int visualizationMode);
  void setTrackColor(std::string particleName,std::string colorName);
  void setTrackColor(int pdgCode,std::string colorName);
  
private:
  void drawTrajectory(const G4Step* theStep);

  /// Messenger.
  GsimSteppingActionMessenger* m_messenger;
  
  GsimDetectorManager* m_DM;

  /// Visualization mode.
  /**
   *   - 0 no visualization
   *   - 1 draw trajectory
   *   - 2 draw trajectory+hit 
   */
  int m_visualizationMode;

  std::map<G4ParticleDefinition*,G4Color> m_particleColorMap;
};

inline void GsimSteppingAction::setVisualizationMode(int visualizationMode) {
  m_visualizationMode=visualizationMode;
}

#endif // GsimSteppingAction_h

