/**
 *  $Id: GsimUtil.cc,v 1.11 2006/12/04 17:27:49 nanjo Exp $
 *  $Log: GsimUtil.cc,v $
 *  Revision 1.11  2006/12/04 17:27:49  nanjo
 *  Data are kept in each class, which are registered to persistencyManger.
 *  GsimPersistencyManger::setBranchOf is added then UserEventData is removed.
 *
 *  Revision 1.10  2006/10/26 14:47:35  nanjo
 *  Sensitive detector list is sorted.
 *
 *  Revision 1.9  2006/10/24 15:23:08  nanjo
 *  SensitiveDetector is re-structred.
 *
 *  Revision 1.8  2006/08/09 13:24:58  nanjo
 *  ROOT streamer is corrected and warning message in material check is suppressed.
 *
 *  Revision 1.7  2006/08/01 05:27:55  nanjo
 *  GsimSpectrum is added. Debug print is updated. With/without Digi is implemented.
 *
 *  Revision 1.6  2006/06/12 22:37:03  nanjo
 *  Add a color.
 *
 *  Revision 1.5  2006/06/09 17:47:31  jfiggins
 *  Added new colors.
 *
 *  Revision 1.4  2006/06/09 17:24:56  jfiggins
 *  Fixed a small typo.
 *
 *  Revision 1.3  2006/03/04 10:48:33  nanjo
 *  If a negative number, -n, is set for the detector channel, the copy number of n-th up detector is used.
 *
 *  Revision 1.2  2006/01/30 02:42:07  nanjo
 *  Detector information is stored in persistencyManager.
 *
 *  Revision 1.1  2006/01/26 04:53:30  nanjo
 *  Detector and persistency classes are added.
 *
 */
#include "GsimKernel/GsimUtil.h"
#include "GsimKernel/GsimDetectorConstruction.h"
#include "GsimKernel/GsimColor.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimKernel/GsimPhysicsList.h"
#include "GsimPhysicsList/GsimCerenkovPhysics.h"
#include "G4ThreeVector.hh"
#include "G4Navigator.hh"
#include "G4TouchableHandle.hh"
#include "G4TouchableHistory.hh"
#include "G4Step.hh"
#include "G4TransportationManager.hh"
#include "G4StepPoint.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4StableIsotopes.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4SDManager.hh"
#include "G4Version.hh"
#include "G4StateManager.hh"
#include "G4ApplicationState.hh"
#include "G4VModularPhysicsList.hh"


#include "CLHEP/Evaluator/Evaluator.h"

#include <sstream>
#include <algorithm>

GsimUtil* GsimUtil::s_util = 0;
bool GsimUtil::s_withCerenkov = false;


GsimUtil::~GsimUtil() {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimUtil* GsimUtil::getUtil()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(s_util) {
    return s_util;
  }
  static GsimUtil theUtil;
  s_util=&theUtil;

  s_withCerenkov=false;
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return s_util;
}




std::string GsimUtil::getVolumeName(const G4ThreeVector &vec) {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  G4Navigator* fpNavigator             = new G4Navigator();
  G4TouchableHandle fTouchableHandle   = new G4TouchableHistory();
  G4Step* fFakeStep                    = new G4Step();
  
  fpNavigator->
    SetWorldVolume(G4TransportationManager::GetTransportationManager()->
                   GetNavigatorForTracking()->GetWorldVolume());
  fpNavigator->
    LocateGlobalPointAndUpdateTouchable(vec,
                                        fTouchableHandle(),
                                        false);
  G4StepPoint* fFakePreStepPoint  = fFakeStep->GetPreStepPoint();
  fFakePreStepPoint->SetTouchableHandle(fTouchableHandle);

  G4VPhysicalVolume* physvol = fFakePreStepPoint->GetPhysicalVolume();

  std::string name = physvol->GetName();
  delete fFakeStep;
  delete fpNavigator;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return name;
}

void GsimUtil::tail(G4String& lin) {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(lin.size()>0) {
    while(std::string(lin,lin.size()-1,lin.size()) == " ") {
      lin.replace(lin.size()-1,1,"");
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimUtil::head(G4String& lin) {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(lin.size()>0) {
    while(std::string(lin,0,1) == " ") {
      lin.replace(0,1,"");
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

  
bool GsimUtil::shift(G4String& lin, G4String& out) {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4String s1,s2;
  
  head(lin);
  tail(lin);
  if(lin.size()<=0)  return false;
  
  int num = lin.find(" ");
  if(num<=0) {
    out = lin;
    lin = "";
    return true;
  }
  
  s1=std::string(lin.begin(),lin.begin()+num);
  head(s1);
  tail(s1);
  s2=std::string(lin.begin()+num+1,lin.end());
  head(s2);
  tail(s2);
  
  lin = s2;
  out = s1;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return true;
}


double GsimUtil::interpret(G4String word) 
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  HepTool::Evaluator eval;
  eval.setStdMath();
  eval.setSystemOfUnits(
                        1.e+3,               //   meter 
                        1./1.60217733e-25,   //   kilogram
                        1.e+9,               //   second
                        1./1.60217733e-10,   //   ampere
                        1.0,                 //   Kelvin
                        1.0,                 //   mole
                        1.0                  //   candela
                        );
  
  double val = eval.evaluate(word.data());
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return val;
}




G4VPhysicalVolume* GsimUtil::getPhysiWorld()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4RunManager* fRunManager = G4RunManager::GetRunManager();
  const G4VUserDetectorConstruction* udc =
    fRunManager->GetUserDetectorConstruction();
  if(!udc) return 0;
  
  GsimDetectorConstruction *dc=dynamic_cast<GsimDetectorConstruction *>
    ( const_cast<G4VUserDetectorConstruction*>(udc) );
  if(!dc) return 0;
  
  const G4VPhysicalVolume* physiWorld
    = dc->getPhysiWorld();
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return const_cast<G4VPhysicalVolume*>(physiWorld);
}

G4Color GsimUtil::findColor(std::string colorName) {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4Color col;
  if(colorName=="white") {
    col=GsimColor::white;
  } else if(colorName=="gray50") {
    col=GsimColor::gray50;
  } else if(colorName=="black") {
    col=GsimColor::black;
  } else if(colorName=="red") {
    col=GsimColor::red;
  } else if(colorName=="green") {
    col=GsimColor::green;
  } else if(colorName=="blue") {
    col= GsimColor::blue;
  } else if(colorName=="cyan") {
    col= GsimColor::cyan;
  } else if(colorName=="magenta") {
    col= GsimColor::magenta;
  } else if(colorName=="yellow") {
    col= GsimColor::yellow;
  } else if(colorName=="gray25") {
    col= GsimColor::gray25;
  } else if(colorName=="gray75") {
    col= GsimColor::gray75;
  } else if(colorName=="gray70") {
    col= GsimColor::gray70;
  } else if(colorName=="purple4") {
    col= GsimColor::purple4;
  } else if(colorName=="lightyellow") {
    col= GsimColor::lightyellow;
  } else if(colorName=="lightskyblue") {
    col= GsimColor::lightskyblue;
  } else if(colorName=="deeppink") {
    col= GsimColor::deeppink;
  } else if(colorName=="orange") {
    col= GsimColor::orange;
  } else if(colorName=="violet") {
    col= GsimColor::violet;
  } else if(colorName=="purple") {
    col= GsimColor::purple;
  } else {
    {
      std::ostringstream ostr;
      ostr << "The color name, " << colorName;
      ostr << ", is not defined. The gray50 is used.";
      GsimMessage::getInstance()
	->report("warning",ostr.str());
    }
    col= GsimColor::gray50;
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return col;
}

G4Material* GsimUtil::findMaterial(std::string matname,bool isVerbose)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4Material* mat=0;
  mat = G4Material::GetMaterial(G4String(matname.c_str()),false);
  if(!mat) {
    mat = G4NistManager::Instance()
      ->FindOrBuildMaterial(G4String(matname.c_str()),true);
			    
  }
  if(!mat) {
    if(isVerbose) {
      std::ostringstream ostr;
      ostr << "No such material, "
	   << matname
	   << "."; 
      GsimMessage::getInstance()
	->report("warning",ostr.str());
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return mat;
}

void GsimUtil::scanDaughterLogicalVolume(G4LogicalVolume* lv,
					 std::list<G4LogicalVolume*>& lvl)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  lvl.push_back(lv);
  int n = lv->GetNoDaughters();
  for(int k=0;k<n;k++) {
    G4VPhysicalVolume* pv=lv->GetDaughter(k);
    if(!pv) continue;
    G4LogicalVolume* dlv=pv->GetLogicalVolume();
    if(!dlv) continue;
    scanDaughterLogicalVolume(dlv,lvl);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimUtil::scanDaughterPhysicalVolume(G4VPhysicalVolume* pv,
					  std::list<G4VPhysicalVolume*>& pvl)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  pvl.push_back(pv);
  G4LogicalVolume* lv=pv->GetLogicalVolume();
  int n = lv->GetNoDaughters();
  for(int k=0;k<n;k++) {
    G4VPhysicalVolume* dpv=lv->GetDaughter(k);
    if(!dpv) continue;
    scanDaughterPhysicalVolume(dpv,pvl);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

G4LogicalVolume* GsimUtil::
findDaughterLogicalVolume(G4LogicalVolume* lv,std::string name)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(!lv) return 0;
  if( (std::string(lv->GetName()).data())==name) return lv;
  
  int n = lv->GetNoDaughters();
  for(int k=0;k<n;k++) {
    G4VPhysicalVolume* pv=lv->GetDaughter(k);
    if(!pv) continue;
    G4LogicalVolume* dlv=pv->GetLogicalVolume();
    G4LogicalVolume* outlv=findDaughterLogicalVolume(dlv,name);
    if(outlv) return outlv;
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return 0;
}

G4VSensitiveDetector* GsimUtil::getSensitiveDetector(std::string sdName)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  G4VSensitiveDetector* g4sd=SDman->FindSensitiveDetector(G4String(sdName.c_str()),false);
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return g4sd;
}


void GsimUtil::fillPhysicalVolumeRelation(G4VPhysicalVolume* pv,
					  std::map<G4VPhysicalVolume*,G4VPhysicalVolume*>& pvr,
					  std::list<G4VPhysicalVolume*>& pvend)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  G4LogicalVolume* lv=pv->GetLogicalVolume();
  G4int nd=lv->GetNoDaughters();
  if(nd==0) {
    pvend.push_back(pv);
  }
  for(int k=0;k<nd;k++) {
    G4VPhysicalVolume* dpv=lv->GetDaughter(k);
    pvr.insert( std::make_pair( dpv,pv ) );
    fillPhysicalVolumeRelation(dpv,pvr,pvend);
  }
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimUtil::fillPhysicalVolumeRelationFromWorld(std::map<G4VPhysicalVolume*,G4VPhysicalVolume*>& pvr,
						   std::list<G4VPhysicalVolume*>& pvend)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  pvr.clear();
  G4VPhysicalVolume* dummy=0;
  G4VPhysicalVolume* pv=getPhysiWorld();
  pvr.insert(std::make_pair(pv,dummy));
  G4LogicalVolume* lv=pv->GetLogicalVolume();
  G4int nd=lv->GetNoDaughters();
  if(nd==0) {
    pvend.push_back(pv);
  }
  for(int k=0;k<nd;k++) {
    G4VPhysicalVolume* dpv=lv->GetDaughter(k);
    pvr.insert( std::make_pair( dpv,pv ) );
    fillPhysicalVolumeRelation(dpv,pvr,pvend);
  }

#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimUtil::fillPhysicalVolumeRelationFromWorld(std::map<G4VPhysicalVolume*,G4VPhysicalVolume*>& pvr)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  std::list<G4VPhysicalVolume*> pvend;
  fillPhysicalVolumeRelationFromWorld(pvr,pvend);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimUtil::addCerenkov()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  
  if(s_withCerenkov) {
    GsimMessage::getInstance()->report("warning","Cerenkov is already added.");
    return;
  }
  
  G4StateManager* sm = G4StateManager::GetStateManager();
  if(!sm) {
    GsimMessage::getInstance()->report("warning","No StateManager. Cerenkov is not added.");
    return;
  }
  
  G4ApplicationState state=sm->GetCurrentState();
  if(state!=G4State_PreInit ) {
    GsimMessage::getInstance()->report("warning","State should be PreInit. Cerenkov is not added.");
    return;
  }
  
  G4RunManager* fRunManager = G4RunManager::GetRunManager();
  if(!fRunManager) {
    GsimMessage::getInstance()
      ->report("warning","No runManager. Cerenkovs is not added.");
    return;
  }

  const G4Run* run = fRunManager->GetCurrentRun();
  if(run) {
    GsimMessage::getInstance()
      ->report("warning","Should be called before the 1st run. Cerenkov is not added.");
    return;
  }

  G4VUserPhysicsList* pl = const_cast<G4VUserPhysicsList*>(fRunManager->GetUserPhysicsList());
  if(!pl) {
    GsimMessage::getInstance()
      ->report("warning","No physicsList. Cerenkov is not added.");
    return;
  }

  
  GsimPhysicsList* gpl= dynamic_cast<GsimPhysicsList*>(pl);
  if(gpl) {
    gpl->addCerenkov();
    s_withCerenkov=true;
    return;
  }
  G4VModularPhysicsList* mpl= dynamic_cast<G4VModularPhysicsList*>(pl);
  if(mpl) {
    mpl->RegisterPhysics(new GsimCerenkovPhysics());
    s_withCerenkov=true;
  } else {
    std::string msg="Cerenkov is not registered, since PhysicsList is not a G4VModularPhysicsList.";
    GsimMessage::getInstance()->report("warning",msg);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimUtil::withUserLimits(bool withUL)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  
  G4StateManager* sm = G4StateManager::GetStateManager();
  if(!sm) {
    GsimMessage::getInstance()->report("warning","No StateManager. GsimUserLimtis:on(default)");
    return;
  }
  
  G4ApplicationState state=sm->GetCurrentState();
  if(! (state==G4State_PreInit || state== G4State_Idle) ) {
    GsimMessage::getInstance()->report("warning","State should be PreInit or Idle. GsimUserLimtis:on(default).");
    return;
  }
  
  G4RunManager* fRunManager = G4RunManager::GetRunManager();
  if(!fRunManager) {
    GsimMessage::getInstance()
      ->report("warning","No runManager. GsimUserLimtis:on(default).");
    return;
  }

  const G4Run* run = fRunManager->GetCurrentRun();
  if(run) {
    GsimMessage::getInstance()
      ->report("warning","Should be called before the 1st run. GsimUserLimtis:on(default).");
    return;
  }
    
  G4VUserPhysicsList* pl = const_cast<G4VUserPhysicsList*>(fRunManager->GetUserPhysicsList());
  if(!pl) {
    GsimMessage::getInstance()
      ->report("warning","No physicsList. GsimUserLimtis:on(default).");
    return;
  }


  GsimPhysicsList* gpl= dynamic_cast<GsimPhysicsList*>(pl);
  if(gpl) {
    gpl->withUserLimits(withUL);
    return;
  } else {
    std::string msg="GsimUserLimits:on(default). If you watn to turn it off, call before PL assignment.";
    GsimMessage::getInstance()->report("warning",msg);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}




GsimUtil::GsimUtil()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

