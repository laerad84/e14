/**
 *  $Id: GsimSteppingAction.cc,v 1.13 2007/02/04 12:29:36 nanjo Exp $
 *  $Log: GsimSteppingAction.cc,v $
 *  Revision 1.13  2007/02/04 12:29:36  nanjo
 *  trackinformation history.
 *
 *  Revision 1.12  2006/11/17 10:48:44  nanjo
 *  Particle colors can be changed.
 *
 *  Revision 1.11  2006/10/19 03:28:44  nanjo
 *  GsimPersistencyManagerMessenger is replaced by GsimRunActionMessneger.
 *  Information of photonuclear interaction is not filled here.
 *  Cluster ID is filled.
 *  Now GsimPersistencyManager, GsimDigitizer, and, GsimMessage is
 *  independent of Geant4. They will be moved to different directory
 *  in order to use from ROOT analysis.
 *
 *  Revision 1.10  2006/09/10 22:11:50  nanjo
 *  PhotoNuclear counter is re-added.
 *
 *  Revision 1.9  2006/08/01 05:27:55  nanjo
 *  GsimSpectrum is added. Debug print is updated. With/without Digi is implemented.
 *
 *  Revision 1.8  2006/06/22 11:38:57  nanjo
 *  Modifications around briefDetectorID and briefDetectorName.
 *
 *  Revision 1.7  2006/06/21 11:47:56  nanjo
 *  BriefTrajectory classes are deleted.
 *
 *  Revision 1.6  2006/06/14 05:53:19  nanjo
 *  Default particle color is changed.
 *
 *  Revision 1.5  2006/03/17 08:02:13  nanjo
 *  Add a flag to disable GsimBreifTrajectory. Make faster for the detector loop.
 *
 *  Revision 1.4  2006/03/17 02:42:28  nanjo
 *  GsimVacuum is changed to GsimLowVacuum for some E391 detectors.
 *
 *  Revision 1.3  2006/03/15 05:33:20  nanjo
 *  EventActionMessegner is added.
 *
 *  Revision 1.2  2006/01/31 22:47:08  nanjo
 *  BriefTrajectory is built from G4VUserTrakInformation.
 *
 *  Revision 1.1  2006/01/26 04:53:30  nanjo
 *  Detector and persistency classes are added.
 *
 */
#include "GsimKernel/GsimSteppingAction.h"
#include "GsimKernel/GsimSteppingActionMessenger.h"
#include "GsimKernel/GsimDetectorManager.h"
#include "GsimKernel/GsimTrackInformation.h"
#include "GsimKernel/GsimColor.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4SteppingManager.hh"
#include "G4Step.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4Polyline.hh"
#include "G4Polymarker.hh"

GsimSteppingAction::GsimSteppingAction(GsimDetectorManager* dm) {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_DM=dm;
  
  m_messenger = new GsimSteppingActionMessenger(this);
  
  m_particleColorMap.insert(std::make_pair(G4OpticalPhoton::OpticalPhotonDefinition(),
					   GsimColor::lightyellow));
  m_particleColorMap.insert(std::make_pair(G4Gamma::GammaDefinition(),
					   GsimColor::yellow));
  m_particleColorMap.insert(std::make_pair(G4Electron::ElectronDefinition(),
					   GsimColor::red));
  m_particleColorMap.insert(std::make_pair(G4Positron::PositronDefinition(),
					   GsimColor::red));
  m_particleColorMap.insert(std::make_pair(G4MuonPlus::Definition(),
					   GsimColor::deeppink));
  m_particleColorMap.insert(std::make_pair(G4MuonMinus::Definition(),
					   GsimColor::deeppink));
  m_particleColorMap.insert(std::make_pair(G4KaonZeroLong::Definition(),
					   GsimColor::purple4));
  m_particleColorMap.insert(std::make_pair(G4KaonPlus::Definition(),
					   GsimColor::lightskyblue));
  m_particleColorMap.insert(std::make_pair(G4KaonMinus::Definition(),
					   GsimColor::lightskyblue));
  m_particleColorMap.insert(std::make_pair(G4PionZero::Definition(),
					   GsimColor::orange));
  m_particleColorMap.insert(std::make_pair(G4PionPlus::Definition(),
					   GsimColor::magenta));
  m_particleColorMap.insert(std::make_pair(G4PionMinus::Definition(),
					   GsimColor::magenta));
  m_particleColorMap.insert(std::make_pair(G4Proton::ProtonDefinition(),
					   GsimColor::blue));
  m_particleColorMap.insert(std::make_pair(G4Neutron::NeutronDefinition(),
					   GsimColor::green));
  m_particleColorMap.insert(std::make_pair(G4NeutrinoE::NeutrinoEDefinition(),
					   GsimColor::white));
  m_particleColorMap.insert(std::make_pair(G4NeutrinoMu::NeutrinoMuDefinition(),
					   GsimColor::white));
  m_particleColorMap.insert(std::make_pair(G4NeutrinoTau::NeutrinoTauDefinition(),
					   GsimColor::white));
  m_particleColorMap.insert(std::make_pair(G4AntiNeutrinoE::AntiNeutrinoEDefinition(),
					   GsimColor::white));
  m_particleColorMap.insert(std::make_pair(G4AntiNeutrinoMu::AntiNeutrinoMuDefinition(),
					   GsimColor::white));
  m_particleColorMap.insert(std::make_pair(G4AntiNeutrinoTau::AntiNeutrinoTauDefinition(),
					   GsimColor::white));

  
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimSteppingAction::~GsimSteppingAction() {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimSteppingAction::UserSteppingAction(const G4Step * theStep) {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  G4Track* track = theStep->GetTrack();
  GsimTrackInformation* trackInformation
    = dynamic_cast<GsimTrackInformation*>(track->GetUserInformation());
  if(trackInformation) {
    trackInformation->processStepHistory(theStep);
  }
  
  m_DM->steppingAction(theStep);

  if(m_visualizationMode>0) {
    drawTrajectory(theStep);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimSteppingAction::drawTrajectory(const G4Step* theStep) {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if (!pVVisManager) return;
  
  G4ParticleDefinition* fpParticleDefinition
    = theStep->GetTrack()->GetDefinition();
  
  G4Polyline pPolyline;
  pPolyline.push_back(theStep->GetPreStepPoint()->GetPosition());
  pPolyline.push_back(theStep->GetPostStepPoint()->GetPosition());
  
  G4Polymarker stepPoints;
  stepPoints.push_back(theStep->GetPreStepPoint()->GetPosition());
  
  G4VisAttributes::LineStyle lineStyle;
  lineStyle=G4VisAttributes::unbroken;

  G4Color color = GsimColor::gray70;
  for(std::map<G4ParticleDefinition*,G4Color>::iterator it=m_particleColorMap.begin();
      it!=m_particleColorMap.end();it++) {
    if(fpParticleDefinition==(*it).first) {
      color = (*it).second;
    }
  }
  
  //---------------------------------------------------
  if( ! ( color!=GsimColor::white) ) return;
  
  if(m_visualizationMode>=1) {
    G4VisAttributes attribs(color);
    attribs.SetLineStyle(lineStyle);
    pPolyline.SetVisAttributes(attribs);
    pVVisManager->Draw(pPolyline);
  }
  
  //---------------------------------------------------
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimSteppingAction::setTrackColor(std::string particleName,std::string colorName)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4Color color = GsimUtil::getUtil()->findColor(colorName);
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle =
    particleTable->FindParticle(G4String(particleName.c_str()));
  if(particle) {
    std::map<G4ParticleDefinition*,G4Color>::iterator it 
      = m_particleColorMap.find(particle);
    if( it!=m_particleColorMap.end()) {
      m_particleColorMap.erase(it);
    }
    m_particleColorMap.insert(std::make_pair(particle,color));
  } else {
    std::ostringstream ostr;
    ostr << "No such particle with name, "
         << particleName
         << ", is forbidend.";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimSteppingAction::setTrackColor(int pdgCode,std::string colorName)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4Color color = GsimUtil::getUtil()->findColor(colorName);
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle(pdgCode);
  if(particle) {
    std::map<G4ParticleDefinition*,G4Color>::iterator it 
      = m_particleColorMap.find(particle);
    if( it!=m_particleColorMap.end()) {
      m_particleColorMap.erase(it);
    }
    m_particleColorMap.insert(std::make_pair(particle,color));
  } else {
    std::ostringstream ostr;
    ostr << "No such particle with PDG code, "
         << pdgCode
         << ", is forbidend.";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
    
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}
