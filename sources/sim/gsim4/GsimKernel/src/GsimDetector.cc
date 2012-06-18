/**
 *  $Id: GsimDetector.cc,v 1.51 2007/02/04 12:55:41 nanjo Exp $
 *  $Log: GsimDetector.cc,v $
 *  Revision 1.51  2007/02/04 12:55:41  nanjo
 *  Fast simulation 3 is added for shower check.
 *
 *  Revision 1.50  2006/12/09 21:34:09  nanjo
 *  briefHistory is corrected and dictionary write.
 *
 *  Revision 1.49  2006/12/07 18:28:58  nanjo
 *  GsimDetector userInputs are implemented.
 *
 *  Revision 1.48  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 *  Revision 1.47  2006/12/02 07:06:11  nanjo
 *  sensitiveDetectorID, StopFlag, detID are updated.
 *
 *  Revision 1.46  2006/11/20 16:16:45  nanjo
 *  SensitiveDetectorList is kept in DetectorManager.
 *
 *  Revision 1.45  2006/11/16 13:13:00  nanjo
 *  Module id with detector depth..
 *
 *  Revision 1.44  2006/10/24 15:23:08  nanjo
 *  SensitiveDetector is re-structred.
 *
 *  Revision 1.43  2006/10/19 03:28:44  nanjo
 *  GsimPersistencyManagerMessenger is replaced by GsimRunActionMessneger.
 *  Information of photonuclear interaction is not filled here.
 *  Cluster ID is filled.
 *  Now GsimPersistencyManager, GsimDigitizer, and, GsimMessage is
 *  independent of Geant4. They will be moved to different directory
 *  in order to use from ROOT analysis.
 *
 *  Revision 1.42  2006/09/08 14:33:52  nanjo
 *  Bug fix about absolute position.
 *
 *  Revision 1.41  2006/09/08 14:29:19  nanjo
 *  Bug fix about absolute position.
 *
 *  Revision 1.40  2006/09/08 13:53:25  nanjo
 *  Add absolute position.
 *
 *  Revision 1.39  2006/09/08 08:18:10  nanjo
 *  Add warning on the number of briefName.
 *
 *  Revision 1.38  2006/09/06 22:33:18  nanjo
 *  GsimDetectorData is added.
 *
 *  Revision 1.37  2006/08/24 22:19:01  nanjo
 *  Almost all data type is changed from double to Float_t, from int to UShort_t.
 *
 *  Revision 1.36  2006/08/11 08:48:52  nanjo
 *  Clear is added for some GsimDatas
 *
 *  Revision 1.35  2006/08/11 06:13:58  nanjo
 *  SensitiveDetector is registered in SDManager.
 *
 *  Revision 1.34  2006/08/02 01:45:34  nanjo
 *  SetHitsStore and SetDigiStore is modified.
 *
 *  Revision 1.33  2006/08/02 00:39:19  nanjo
 *  A bug of multiple call of digitize is fixed.
 *
 *  Revision 1.32  2006/08/01 05:27:55  nanjo
 *  GsimSpectrum is added. Debug print is updated. With/without Digi is implemented.
 *
 *  Revision 1.31  2006/06/22 11:38:57  nanjo
 *  Modifications around briefDetectorID and briefDetectorName.
 *
 *  Revision 1.30  2006/06/21 12:27:43  nanjo
 *  setThisAndDaugterBriefName is added.
 *
 *  Revision 1.29  2006/06/21 11:47:56  nanjo
 *  BriefTrajectory classes are deleted.
 *
 *  Revision 1.28  2006/06/14 05:54:22  nanjo
 *  GsimDigitizer is added.
 *
 *  Revision 1.27  2006/06/04 09:50:21  nanjo
 *  Fast simulation level, 4,  is implemetned. As for the levle 5, the tracking
 *  is terminated when the step touch the volume. As for the level 4, the tracking
 *  is terminated when the step enter the volume, which is controled by UserLimits.
 *
 *  Revision 1.26  2006/06/01 06:46:27  nanjo
 *  GsimUserLimit is added.
 *
 *  Revision 1.25  2006/05/31 19:42:24  nanjo
 *  GsimDetector::getWorldDetector is added and magnetic field is implemented.
 *
 *  Revision 1.24  2006/04/24 15:48:23  nanjo
 *  GsimDetector::setHitsStoreDaughters is added by Jeremy.
 *
 *  Revision 1.23  2006/04/19 02:02:53  nanjo
 *  Energy deposit is the kinetic energy of the track when fastSimulationLevel is 5.
 *
 *  Revision 1.22  2006/04/12 13:57:16  nanjo
 *  Bug fix for GsimDetector::setHitsStore.
 *
 *  Revision 1.21  2006/04/12 13:07:07  nanjo
 *  GsimDetector::setHitsStore method is added, which can disable to store hits information.
 *
 *  Revision 1.20  2006/04/12 12:07:17  nanjo
 *  Fix typo.
 *
 *  Revision 1.19  2006/04/12 08:18:20  nanjo
 *  namespace of CLHEP is resolved.
 *
 *  Revision 1.18  2006/04/11 12:39:24  nanjo
 *  Fix a bug for userEventData and GsimDetector::clearThisClone is added.
 *
 *  Revision 1.17  2006/03/22 05:29:58  nanjo
 *  GSIMDEBUG message is added to GsimEventAction.
 *
 *  Revision 1.16  2006/03/17 08:02:13  nanjo
 *  Add a flag to disable GsimBreifTrajectory. Make faster for the detector loop.
 *
 *  Revision 1.15  2006/03/17 02:42:28  nanjo
 *  GsimVacuum is changed to GsimLowVacuum for some E391 detectors.
 *
 *  Revision 1.14  2006/03/15 09:29:06  nanjo
 *  A function, setThisAndDaughersOuterVisibility, is added to GsimDetector class.
 *
 *  Revision 1.13  2006/03/14 16:11:51  nanjo
 *  Fix G4_Air to G4_AIR.
 *
 *  Revision 1.12  2006/03/05 13:29:46  nanjo
 *  CC02 is added. Fix a bug in GsimPolyhedra2.
 *
 *  Revision 1.11  2006/03/04 10:48:33  nanjo
 *  If a negative number, -n, is set for the detector channel, the copy number of n-th up detector is used.
 *
 *  Revision 1.10  2006/03/02 02:56:48  nanjo
 *  A small bug fix.
 *
 *  Revision 1.9  2006/03/01 12:45:32  nanjo
 *  A member function of GsimDetector, cloneDetector, is added and used in E391Detector.
 *
 *  Revision 1.8  2006/02/21 15:54:36  nanjo
 *  The detector full name is used as a default sensitive detector name.
 *
 *  Revision 1.7  2006/02/21 09:09:59  nanjo
 *  Sensitive detector name and channel id can be assigned. If the same sensitive detector name is used for some detectors, these detectors are recognized as channels in one detector.
 *
 *  Revision 1.6  2006/02/03 05:30:54  nanjo
 *  Fast simulation level is set automatically daughter volumes.
 *
 *  Revision 1.5  2006/02/02 21:54:02  nanjo
 *  E391 detector is sarted.
 *
 *  Revision 1.4  2006/01/31 22:47:08  nanjo
 *  BriefTrajectory is built from G4VUserTrakInformation.
 *
 *  Revision 1.3  2006/01/30 02:42:07  nanjo
 *  Detector information is stored in persistencyManager.
 *
 *  Revision 1.2  2006/01/27 05:08:24  nanjo
 *  PersistencyManagerMessenger is added.
 *
 *  Revision 1.1  2006/01/26 04:53:30  nanjo
 *  Detector and persistency classes are added.
 *
 */
#include "GsimKernel/GsimDetector.h"
#include "GsimKernel/GsimDetectorMessenger.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimKernel/GsimSensitiveDetector.h"
#include "GsimPersistency/GsimPersistencyManager.h"
#include "GsimKernel/GsimTrackInformation.h"
#include "GsimKernel/GsimDigitizer.h"
#include "GsimPersistency/GsimMessage.h"



#include "G4Event.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4VSolid.hh"
#include "G4Box.hh"
#include "G4Material.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4RegionStore.hh"
#include "G4Region.hh"
#include "G4ProductionCuts.hh"
#include "G4VUserPhysicsList.hh"
#include "G4PVPlacement.hh"
#include "G4MagneticField.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4UserLimits.hh"
#include "G4SDManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4TouchableHistory.hh"

#include <algorithm>

GsimDetector* GsimDetector::s_worldDetector=0;

std::list<std::string>
GsimDetector::s_briefDetectorNameList;

GsimDetector::GsimDetector(std::string name,
			   GsimDetector* motherDetector,
			   G4ThreeVector transV,G4ThreeVector rotV,
			   int userFlag)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_name      = name;
  m_briefName = "";
  m_detectorID = -1;
  m_briefDetectorID=-1;
  m_motherDetector=motherDetector;
  m_className = "GsimDetector";
  m_physiDetector=0;
  m_localCenterVector=G4ThreeVector(0,0,0);
  m_translationVector=transV;
  m_rotationVector   = rotV;
  m_rotationMatrix   = new G4RotationMatrix();
  m_userFlag=userFlag;
  
  m_fieldManager=0;
  m_magneticField=0;

  m_userLimits=0;
  m_userLimitsStepMax=DBL_MAX;
  m_userLimitsTrackMax=DBL_MAX;
  m_userLimitsTimeMax=DBL_MAX;
  m_userLimitsEkinMin=0;
  m_userLimitsRangeMin=0;
  
  
  m_numberOfParameters=0;
  m_parameterArray=0;
  m_outerCopyNo=0;
  m_outerMaterialName="G4_AIR";
  m_outerColorName="gray50";
  m_isOuterVisible=true;
  m_isModified=true;
  m_fastSimulationLevel=0;

  update();

  m_messenger = new GsimDetectorMessenger(this);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


GsimDetector::GsimDetector(G4VPhysicalVolume* physiWorld) {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  
  if(physiWorld->GetName()!="/world") return;
  if(!physiWorld) return;
  if(s_worldDetector) return;
  
  m_name      = "world";
  m_briefName = "world";
  m_motherDetector=0;
  m_briefDetectorID=-1;
  m_className = "GsimDetector";
  m_physiDetector=physiWorld;
  G4LogicalVolume* logicWorld = physiWorld->GetLogicalVolume();
  G4VSolid* solidWorld = logicWorld->GetSolid();
  G4Box* box = dynamic_cast<G4Box*>(solidWorld);

  m_numberOfParameters=3;
  m_parameterArray= new double[3];
  m_parameterArray[0] =box->GetXHalfLength();
  m_parameterArray[1] =box->GetYHalfLength();
  m_parameterArray[2] =box->GetZHalfLength();

  m_localCenterVector=G4ThreeVector(0,0,0);
  m_translationVector=G4ThreeVector(0,0,0);
  m_rotationVector   =G4ThreeVector(0,0,0);
  m_rotationMatrix   = new G4RotationMatrix();
  m_fieldManager=0;
  m_magneticField =0;

  m_userLimits=0;
  m_userLimitsStepMax=DBL_MAX;
  m_userLimitsTrackMax=DBL_MAX;
  m_userLimitsTimeMax=DBL_MAX;
  m_userLimitsEkinMin=0;
  m_userLimitsRangeMin=0;
  
  
  m_outerMaterialName=logicWorld->GetMaterial()->GetName();
  m_outerColorName="";
  m_isOuterVisible=true;
  m_isModified=true;
  m_fastSimulationLevel=0;
  m_userFlag=0;
  update();
  m_messenger = new GsimDetectorMessenger(this);
  
  s_worldDetector=this;
    
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimDetector::~GsimDetector()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  delete [] m_parameterArray;
  delete m_rotationMatrix;
  delete m_magneticField;
  delete m_fieldManager;
  delete m_userLimits;
  delete m_messenger;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::setLocalCenterVector(G4ThreeVector vec)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_localCenterVector=vec;
  m_isModified=true;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::setTranslationVector(G4ThreeVector vec)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(m_name=="world") return;
  if(m_clonedPhysicalVolumeList.size()>0) {
    std::ostringstream ostr;
    ostr << "Changing the translationVector of the cloned GsimDetector, "
	 << m_name
	 << ", is forbidend.";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
    return;
  }
  
  m_translationVector=vec;
  m_isModified=true;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimDetector::setRotationVector(G4ThreeVector vec)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(m_name=="world") return;
  if(m_clonedPhysicalVolumeList.size()>0) {
    std::ostringstream ostr;
    ostr << "Changing the rotationVector of the cloned GsimDetector, "
	 << m_name
	 << ", is forbidend.";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
    return;
  }
  
  m_rotationVector=vec;
  m_isModified=true;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimDetector::setParameters(std::vector<double> vec)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(vec.size() != m_numberOfParameters) {
    {
      std::ostringstream ostr;
      ostr << "Invalid number of parameters, which shodu be "
	   << m_numberOfParameters
	   << "."; 
      GsimMessage::getInstance()
	->report("warning",ostr.str());
    }
    return; 
  }

  for(unsigned int i=0;i<m_numberOfParameters;i++) {
    m_parameterArray[i] = vec[i];
  }
  m_isModified=true;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::setOuterMaterial(std::string name)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_outerMaterialName=name;

  if(m_physiDetector) {
    G4LogicalVolume* logicDetector = m_physiDetector->GetLogicalVolume();
    if(!logicDetector) {
      GsimMessage::getInstance()
	->report("warning","No logicDetector is constructed.");
    } else {
      G4Material* material =
	GsimUtil::getUtil()->findMaterial(m_outerMaterialName);
      if(!material) {
	GsimMessage::getInstance()
	  ->report("warning","No such material is found.");
      } else {
	//logicDetector->UpdateMaterial(material);
	logicDetector->SetMaterial(material);
	G4RunManager* fRunManager = G4RunManager::GetRunManager();
	fRunManager->GeometryHasBeenModified();
      }
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif 
}

void GsimDetector::setOuterColor(std::string colorName)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_outerColorName=colorName;
  
  if(m_physiDetector) {
    G4LogicalVolume* logicDetector = m_physiDetector->GetLogicalVolume();
    if(!logicDetector) {
      GsimMessage::getInstance()
	->report("warning","No logicDetector is constructed.");
    } else {
      const G4VisAttributes* visAtt = logicDetector->GetVisAttributes();
      if(!visAtt) {
	G4VisAttributes* tmpVisAtt
	  = new G4VisAttributes(GsimUtil::getUtil()->findColor(m_outerColorName));
	tmpVisAtt->SetVisibility(m_isOuterVisible);
	logicDetector->SetVisAttributes(tmpVisAtt);
      } else {
	G4Color col
	  = GsimUtil::getUtil()->findColor(m_outerColorName);
	const_cast<G4VisAttributes*>(visAtt)
	  ->SetColor(col);
      }
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif 
}


void GsimDetector::setOuterVisibility(bool vis)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_isOuterVisible=vis;
  
  if(m_physiDetector) {
    G4LogicalVolume* logicDetector = m_physiDetector->GetLogicalVolume();
    if(!logicDetector) {
      GsimMessage::getInstance()
	->report("warning","No logicDetector is constructed.");
    } else {
      const G4VisAttributes* visAtt = logicDetector->GetVisAttributes();
      if(!visAtt) {
	G4VisAttributes* tmpVisAtt
	  = new G4VisAttributes(GsimUtil::getUtil()->findColor(m_outerColorName));
	tmpVisAtt->SetVisibility(m_isOuterVisible);
	logicDetector->SetVisAttributes(tmpVisAtt);
      } else {
	const_cast<G4VisAttributes*>(visAtt)
	  ->SetVisibility(vis);
      }
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif 
}


void GsimDetector::setThisAndDaughterOuterVisibility(bool vis)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  setOuterVisibility(vis);
  for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
      it!=m_daughterDetectorContainer.end();it++) {
    GsimDetector* daughter =  (*it).second;
    daughter->setThisAndDaughterOuterVisibility(vis);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif 
}

void GsimDetector::setOuterCopyNo(int iCopy)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_outerCopyNo=iCopy;
  if(m_physiDetector) {
    m_physiDetector->SetCopyNo(iCopy);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif 
}

void GsimDetector::setThisAsARootRegion(std::string regionName,double productionCut)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif


  if(m_name=="world") {
    G4String worldRegionName =
      GsimUtil::getUtil()->getPhysiWorld()->GetLogicalVolume()->GetRegion()->GetName();
    regionName=std::string(worldRegionName.data());
  } else {
    if(!m_motherDetector) return;
  }
  
  if(regionName=="") {
    G4String worldRegionName =
      GsimUtil::getUtil()->getPhysiWorld()->GetLogicalVolume()->GetRegion()->GetName();
    regionName=std::string(worldRegionName.data());
  }
  
  if(!m_physiDetector) {
    for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
	it!=m_daughterDetectorContainer.end();it++) {
      GsimDetector* daughter =  (*it).second;
      daughter->setThisAsARootRegion(regionName);
    }
  } else {
    G4LogicalVolume* logicDetector = m_physiDetector->GetLogicalVolume();
    if(!logicDetector) {
      GsimMessage::getInstance()
	->report("warning","No logicDetector is found.");
      return;
    }
    G4Region*  aRegion =
      G4RegionStore::GetInstance()->GetRegion(G4String(regionName.c_str()));
    if(!aRegion) {
      aRegion = new G4Region(G4String(regionName.c_str()));
    }
    if(productionCut<0) {
      G4RunManager* fRunManager = G4RunManager::GetRunManager();
      productionCut=
	fRunManager->GetUserPhysicsList()->GetDefaultCutValue();
    }
    G4ProductionCuts* cuts = aRegion->GetProductionCuts();
    if(!cuts) {
      cuts = new G4ProductionCuts();
      aRegion->SetProductionCuts(cuts);
    }
    cuts->SetProductionCut(productionCut);

    if(std::string(logicDetector->GetRegion()->GetName())!=regionName) {
      logicDetector->SetRegion(aRegion);
      aRegion->AddRootLogicalVolume(logicDetector);
    }
  }
  G4RegionStore::GetInstance()->SetWorldVolume();
  m_isModified=true;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif 

}

void GsimDetector::setFastSimulationLevel(int level)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(m_name=="world") return;
  m_fastSimulationLevel=level;
  for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
      it!=m_daughterDetectorContainer.end();it++) {
    GsimDetector* daughter =  (*it).second;
    daughter->setFastSimulationLevel(level);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif 
}

void GsimDetector::setDaughterFastSimulationLevel(int level)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(m_name=="world") return;
  for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
      it!=m_daughterDetectorContainer.end();it++) {
    GsimDetector* daughter =  (*it).second;
    daughter->setFastSimulationLevel(level);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif 
}

void GsimDetector::setSensitiveDetector(std::string logicalVolumeName,std::string SDName,
					bool withHit, bool withDigi,
					GsimDetector* hitProcesser,
					GsimDigitizer* digi)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  if(m_name=="world") return;


  G4LogicalVolume* targetLV=0;
  std::string targetName=logicalVolumeName;
  G4LogicalVolume* lv = m_physiDetector->GetLogicalVolume();
  if(std::string( lv->GetName().data() ) == targetName) {
    targetLV=lv;
  }

  if(!targetLV) {
    std::list<G4VPhysicalVolume*> pvList;
    listFirstDaughterDetectorWihtPhysi(pvList);
    int nDaughters=lv->GetNoDaughters();
    for(int k=0;k<nDaughters;k++) {
      G4VPhysicalVolume* pv=lv->GetDaughter(k);
      std::list<G4VPhysicalVolume*>::iterator itv
	= std::find(pvList.begin(),pvList.end(), pv);
      if(itv != pvList.end()) {
	//found
      }  else {
	targetLV=GsimUtil::getUtil()
	  ->findDaughterLogicalVolume(pv->GetLogicalVolume(),targetName);
	if(targetLV) break;
      }
    }
  }
  if(!targetLV) {
    std::ostringstream ostr;
    ostr << "No such LV : ";
    ostr << targetName << "." ;
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
    return;
  }

  if(SDName=="") {
    SDName=targetName;
  }
  
  GsimSensitiveDetector* sd=0;
  G4VSensitiveDetector* g4sd=targetLV->GetSensitiveDetector();
  
  if( g4sd ) {
    std::ostringstream ostr;
    ostr << "The LogicalVolume : ";
    ostr << logicalVolumeName << " was already registered as a sensitive detector," ;
    ostr << "which will be re-assigned to a sensitive detector, " ;
    ostr << SDName << ".";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
  }
  

  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  g4sd=SDman->FindSensitiveDetector(G4String(SDName.c_str()),false);
  if(g4sd==0) {
    //create sd;
    sd = new GsimSensitiveDetector(SDName);
    if(hitProcesser)
      sd->setHitProcessDetector(hitProcesser);
    if(digi) {
      sd->addDigitizer(digi);
    } else {
      sd->addDigitizer(new GsimDigitizer(SDName));
    }
    SDman->AddNewDetector( sd );
  } else {
    sd = dynamic_cast<GsimSensitiveDetector*>(g4sd);
  }
  if(sd==0) {
    std::ostringstream ostr;
    ostr << "The existing sensitive detector, ";
    ostr << SDName;
    ostr << ", is not a GsimSensitiveDetector.";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
  } else {
    targetLV->SetSensitiveDetector(sd);
    sd->storeHit(withHit);
    sd->storeDigi(withDigi);
    m_sensitiveDetectorMap.insert(std::make_pair(targetLV,sd));
  }
  m_isModified=true;
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}



void GsimDetector::setSensitiveDetector(std::string SDname,int channel,
					bool withHit, bool withDigi,
					GsimDetector* hitProcesser,
					GsimDigitizer* digi)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  if(m_name=="world") return;
  
  if(!m_physiDetector) return;
  
  if(channel!=-999) {
    m_physiDetector->SetCopyNo(channel);
    m_outerCopyNo=channel;
  }
  G4String tmpname = m_physiDetector->GetLogicalVolume()->GetName();
  std::string logicalVolumeName=std::string(tmpname.data());
  setSensitiveDetector(logicalVolumeName,SDname,withHit,withDigi,hitProcesser,digi);
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::unsetSensitiveDetector(std::string logicalVolumeName)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  if(m_name=="world") return;


  G4LogicalVolume* targetLV=0;
  std::string targetName=logicalVolumeName;
  G4LogicalVolume* lv = m_physiDetector->GetLogicalVolume();
  if(std::string( lv->GetName().data() ) == targetName) {
    targetLV=lv;
  }

  if(!targetLV) {
    std::list<G4VPhysicalVolume*> pvList;
    listFirstDaughterDetectorWihtPhysi(pvList);
    int nDaughters=lv->GetNoDaughters();
    for(int k=0;k<nDaughters;k++) {
      G4VPhysicalVolume* pv=lv->GetDaughter(k);
      std::list<G4VPhysicalVolume*>::iterator itv
	= std::find(pvList.begin(),pvList.end(), pv);
      if(itv != pvList.end()) {
	//found
      }  else {
	targetLV=GsimUtil::getUtil()
	  ->findDaughterLogicalVolume(pv->GetLogicalVolume(),targetName);
	if(targetLV) break;
      }
    }
  }
  if(!targetLV) {
    std::ostringstream ostr;
    ostr << "No such LV : ";
    ostr << targetName << "." ;
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
    return;
  }

  targetLV->SetSensitiveDetector(0);
  
  std::map<G4LogicalVolume*,GsimSensitiveDetector*>::iterator it
    =m_sensitiveDetectorMap.find(targetLV);
  if(it!=m_sensitiveDetectorMap.end()) {
    m_sensitiveDetectorMap.erase(it);
  }

  m_isModified=true;
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimDetector::unsetSensitiveDetector()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  if(m_name=="world") return;
  
  if(!m_physiDetector) return;
  
  G4String tmpname = m_physiDetector->GetLogicalVolume()->GetName();
  std::string logicalVolumeName=std::string(tmpname.data());
  unsetSensitiveDetector(logicalVolumeName);
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::setHitsStore(std::string logicalVolumeName,bool withHit)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  for(std::map<G4LogicalVolume*,GsimSensitiveDetector*>::iterator
	it=m_sensitiveDetectorMap.begin();
      it!=m_sensitiveDetectorMap.end();it++) {
    if(std::string( ((*it).first)->GetName().data())==logicalVolumeName) {
      ((*it).second)->storeHit(withHit);
      m_isModified=true;
      return;
    }
  }

  {
    std::ostringstream ostr;
    ostr << "No such LV name: ";
    ostr << logicalVolumeName << " is setHitStore.";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimDetector::setHitsStore(bool withHit)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  for(std::map<G4LogicalVolume*,GsimSensitiveDetector*>::iterator
	it=m_sensitiveDetectorMap.begin();
      it!=m_sensitiveDetectorMap.end();it++) {
    G4String tmpname = ((*it).first)->GetName();
    std::string logicalVolumeName=std::string(tmpname.data());
    setHitsStore(logicalVolumeName,withHit);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::setHitsStoreDaughters(bool withHit)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
      it!=m_daughterDetectorContainer.end();it++) {
    GsimDetector* daughter =  (*it).second;
    daughter->setHitsStore(withHit);
    daughter->setHitsStoreDaughters(withHit);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimDetector::setThisAndDaughterHitsStore(bool withHit)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  setHitsStore(withHit);
  setHitsStoreDaughters(withHit);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimDetector::setDigiStore(std::string logicalVolumeName,bool withDigi)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  for(std::map<G4LogicalVolume*,GsimSensitiveDetector*>::iterator
	it=m_sensitiveDetectorMap.begin();
      it!=m_sensitiveDetectorMap.end();it++) {
    if(std::string( ((*it).first)->GetName().data())==logicalVolumeName) {
      ((*it).second)->storeDigi(withDigi);
      m_isModified=true;
      return;
    }
  }

  {
    std::ostringstream ostr;
    ostr << "No such LV name: ";
    ostr << logicalVolumeName << " is setDigiStore.";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::setDigiStore(bool withDigi)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  for(std::map<G4LogicalVolume*,GsimSensitiveDetector*>::iterator
	it=m_sensitiveDetectorMap.begin();
      it!=m_sensitiveDetectorMap.end();it++) {
    G4String tmpname = ((*it).first)->GetName();
    std::string logicalVolumeName=std::string(tmpname.data());
    setDigiStore(logicalVolumeName,withDigi);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::setDigiStoreDaughters(bool withDigi)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
      it!=m_daughterDetectorContainer.end();it++) {
    GsimDetector* daughter =  (*it).second;
    daughter->setDigiStore(withDigi);
    daughter->setDigiStoreDaughters(withDigi);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::setThisAndDaughterDigiStore(bool withDigi)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  setDigiStore(withDigi);
  setDigiStoreDaughters(withDigi);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimDetector::setThisMagneticField(G4ThreeVector magneticFieldVector)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_magneticFieldVector=magneticFieldVector;
  m_isModified=true;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimDetector::setThisAndDaughterMagneticField(G4ThreeVector magneticFieldVector)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_magneticFieldVector=magneticFieldVector;
  m_isModified=true;
  for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
      it!=m_daughterDetectorContainer.end();it++) {
    GsimDetector* daughter =  (*it).second;
    daughter->setThisAndDaughterMagneticField(magneticFieldVector);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::updateField()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  //please call only from world detector;
  if(m_physiDetector) {
    if(m_magneticFieldVector==G4ThreeVector(0,0,0)) {
      delete m_magneticField;
      delete m_fieldManager;
      m_fieldManager=0;
      m_magneticField=0;
    } else {
      if(!m_fieldManager)  m_fieldManager = new G4FieldManager();
      if(!m_magneticField) m_magneticField = new G4UniformMagField(m_magneticFieldVector);
      else m_magneticField->SetFieldValue(m_magneticFieldVector);
      m_fieldManager->SetDetectorField(m_magneticField);
      m_fieldManager->CreateChordFinder(m_magneticField);
    }
    if(m_physiDetector->GetLogicalVolume())
      m_physiDetector->GetLogicalVolume()->SetFieldManager(m_fieldManager,true);
  }
  for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
      it!=m_daughterDetectorContainer.end();it++) {
    GsimDetector* daughter =  (*it).second;
    daughter->updateField();
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimDetector::setThisUserStepMax(double cut)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_userLimitsStepMax = cut;
  m_isModified=true;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::setThisUserTrackMax(double cut)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_userLimitsTrackMax = cut;
  m_isModified=true;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::setThisUserTimeMax(double cut)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_userLimitsTimeMax = cut;
  m_isModified=true;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::setThisUserEkinMin(double cut)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_userLimitsEkinMin = cut;
  m_isModified=true;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::setThisUserRangeMin(double cut)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_userLimitsRangeMin = cut;
  m_isModified=true;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::resetThisUserLimits()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_userLimitsStepMax=DBL_MAX;
  m_userLimitsTrackMax=DBL_MAX;
  m_userLimitsTimeMax=DBL_MAX;
  m_userLimitsEkinMin=0;
  m_userLimitsRangeMin=0;
  m_isModified=true;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::setThisAndDaughterUserStepMax(double cut)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_userLimitsStepMax = cut;
  m_isModified=true;
  for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
      it!=m_daughterDetectorContainer.end();it++) {
    GsimDetector* daughter =  (*it).second;
    daughter->setThisAndDaughterUserStepMax(cut);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::setThisAndDaughterUserTrackMax(double cut)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_userLimitsTrackMax = cut;
  m_isModified=true;
  for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
      it!=m_daughterDetectorContainer.end();it++) {
    GsimDetector* daughter =  (*it).second;
    daughter->setThisAndDaughterUserTrackMax(cut);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::setThisAndDaughterUserTimeMax(double cut)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_userLimitsTimeMax=cut;
  m_isModified=true;
  for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
      it!=m_daughterDetectorContainer.end();it++) {
    GsimDetector* daughter =  (*it).second;
    daughter->setThisAndDaughterUserTimeMax(cut);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::setThisAndDaughterUserEkinMin(double cut)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_userLimitsEkinMin=cut;
  m_isModified=true;
  for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
      it!=m_daughterDetectorContainer.end();it++) {
    GsimDetector* daughter =  (*it).second;
    daughter->setThisAndDaughterUserEkinMin(cut);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::setThisAndDaughterUserRangeMin(double cut)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_userLimitsRangeMin=cut;
  m_isModified=true;
  for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
      it!=m_daughterDetectorContainer.end();it++) {
    GsimDetector* daughter =  (*it).second;
    daughter->setThisAndDaughterUserRangeMin(cut);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::resetThisAndDaughterUserLimits()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_userLimitsStepMax=DBL_MAX;
  m_userLimitsTrackMax=DBL_MAX;
  m_userLimitsTimeMax=DBL_MAX;
  m_userLimitsEkinMin=0;
  m_userLimitsRangeMin=0;
  m_isModified=true;

  for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
      it!=m_daughterDetectorContainer.end();it++) {
    GsimDetector* daughter =  (*it).second;
    daughter->resetThisAndDaughterUserLimits();
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::updateUserLimits()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  //please call only from world detector;
  if(m_physiDetector) {
    if(m_fastSimulationLevel==4) {
      if(!m_userLimits)
	{
	  m_userLimits = new G4UserLimits(m_userLimitsStepMax,
					  0,
					  m_userLimitsTimeMax,
					  m_userLimitsEkinMin,
					  m_userLimitsRangeMin
					  );
	}
      else
	{
	  m_userLimits->SetMaxAllowedStep(m_userLimitsStepMax);
	  m_userLimits->SetUserMaxTrackLength(0);
	  m_userLimits->SetUserMaxTime(m_userLimitsTimeMax);
	  m_userLimits->SetUserMinEkine(m_userLimitsEkinMin);
	  m_userLimits->SetUserMinRange(m_userLimitsRangeMin);
	}
    } else {
      if(
	 m_userLimitsStepMax==DBL_MAX &&
	 m_userLimitsTrackMax==DBL_MAX &&
	 m_userLimitsTimeMax==DBL_MAX &&
	 m_userLimitsEkinMin==0 &&
	 m_userLimitsRangeMin==0 ) {
	delete m_userLimits;
	m_userLimits=0;
      } else {
	if(!m_userLimits)
	  {
	    m_userLimits = new G4UserLimits(m_userLimitsStepMax,
					    m_userLimitsTrackMax,
					    m_userLimitsTimeMax,
					    m_userLimitsEkinMin,
					    m_userLimitsRangeMin
					    );
	  }
	else
	  {
	    m_userLimits->SetMaxAllowedStep(m_userLimitsStepMax);
	    m_userLimits->SetUserMaxTrackLength(m_userLimitsTrackMax);
	    m_userLimits->SetUserMaxTime(m_userLimitsTimeMax);
	    m_userLimits->SetUserMinEkine(m_userLimitsEkinMin);
	    m_userLimits->SetUserMinRange(m_userLimitsRangeMin);
	  }
      }
    }

    G4LogicalVolume* lv= m_physiDetector->GetLogicalVolume();
    if(lv) {
      lv->SetUserLimits(m_userLimits);
      int NoDaughters = lv->GetNoDaughters();
      while ( (NoDaughters--)>0 ) {
	G4LogicalVolume* DaughterLogVol; 
	DaughterLogVol = lv->GetDaughter(NoDaughters)->GetLogicalVolume();
	if ( (DaughterLogVol->GetUserLimits() == 0) ) {
	  DaughterLogVol->SetUserLimits(m_userLimits);
	}
      }
    }
  }
  for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
      it!=m_daughterDetectorContainer.end();it++) {
    GsimDetector* daughter =  (*it).second;
    daughter->updateUserLimits();
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimDetector* GsimDetector::getWorldDetector()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return s_worldDetector;
}


void GsimDetector::print()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4cout << "----------------------------------------------------" << G4endl;
  
  G4cout << "name               : " << m_name << G4endl;
  G4cout << "full name          : " << getFullName() << G4endl;
  G4cout << "class name         : " << m_className << G4endl;
  G4cout << "mother full name   : ";
  if(m_motherDetector) G4cout << m_motherDetector->getFullName() << G4endl;
  else                 G4cout << "/" << G4endl;
  
  if(m_physiDetector) {
    G4cout << "physical volume    : " << m_physiDetector->GetName() << G4endl;
    if(getMotherPhysiDetector())
      G4cout << "mother physi.volume: " << getMotherPhysiDetector()->GetName() << G4endl;
    else
      G4cout << "mother physi.volume: " << "none" << G4endl;
    
  }
  std::ios::fmtflags f = G4cout.flags();
  G4cout << "local center       : " << m_localCenterVector << G4endl;
  G4cout << "translation        : "
	 << G4BestUnit(m_translationVector.x(),"Length") << " "
	 << G4BestUnit(m_translationVector.y(),"Length") << " "
	 << G4BestUnit(m_translationVector.z(),"Length") << " "
	 << G4endl;
  G4cout.precision(3);
  G4cout << "rotation           : "
	 << m_rotationVector.x()/deg << " "
	 << m_rotationVector.y()/deg << " "
	 << m_rotationVector.z()/deg << " " << "[deg]"
	 << G4endl;
  G4cout.flags(f);
  if(m_physiDetector) {
    G4cout << "outer material     : " << m_outerMaterialName << G4endl;
    G4cout << "outer color        : " << m_outerColorName << G4endl;
    if(m_isOuterVisible) 
      G4cout << "visibility         : " << "visible" << G4endl;
    else 
      G4cout << "visibility         : " << "invisible" << G4endl;
    G4Region* aRegion = m_physiDetector->GetLogicalVolume()->GetRegion();
    G4ProductionCuts* cuts = aRegion->GetProductionCuts();
    G4cout << "region name        : " << aRegion->GetName() << G4endl;
    G4cout << "production cuts    :"
           << " gamma " << G4BestUnit(cuts->GetProductionCut("gamma"),"Length")
           << "    e- " << G4BestUnit(cuts->GetProductionCut("e-"),"Length")
           << "    e+ " << G4BestUnit(cuts->GetProductionCut("e+"),"Length")
           << G4endl;
  } else {
    G4cout << "physical vol       : " << "0" << G4endl;
  }
  
  G4cout << "number of parameter: " << m_numberOfParameters << G4endl;
  for(unsigned int i=0;i<m_numberOfParameters;i++) {
    G4cout << "parameters         : " << m_parameterArray[i] << G4endl;
  }
  if(m_isModified) {
    G4cout << "modification status: " << "modified" << G4endl;
  } else {
    G4cout << "modification status: " << "updated" << G4endl;
  }
  G4cout << "number of parameter: " << m_numberOfParameters << G4endl;
  G4cout << "fast simu. level   : " << m_fastSimulationLevel << G4endl;
  G4cout << "userFlag           : " << m_userFlag << G4endl;
  G4cout << "sensitive volume   : " << m_sensitiveDetectorMap.size() << G4endl;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimDetector::update()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  G4VPhysicalVolume* motherPhysi = getMotherPhysiDetector();

  if(!m_physiDetector && motherPhysi) {
    constructPhysiDetector();
    if(m_physiDetector) {
      setOuterColor(m_outerColorName);
      setOuterVisibility(m_isOuterVisible);
    }
  }

  if(m_physiDetector && m_name!="world") {
    setupSensitiveDetector();
  }
  
  computeRealRotationMatrixFromMotherPhysi();
  if(m_physiDetector) {
    setRealTranslationFromMotherPhysi();
  }
  updateParametersEtc();

  if(m_name=="world") {
    return;
  }
  
  
  if(motherPhysi) {
    for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
	it!=m_daughterDetectorContainer.end();it++) {
      GsimDetector* daughter =  (*it).second;
      daughter->update();
    }
  }

  if(motherPhysi) {
    doCloneDetector();
    setRealTranslationFromMotherPhysi();
  }
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimDetector::deleteMessenger()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  delete m_messenger;
  m_messenger=0;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::newMessenger()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(!m_messenger)
    m_messenger = new GsimDetectorMessenger(this);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::placeDetector(GsimDetector* motherDetector,
				 G4ThreeVector transV,
				 G4ThreeVector rotV)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(! (m_physiDetector==0 && m_motherDetector==0) ) {
    std::ostringstream ostr;
    ostr << "Placement is not allowed, because ";
    if(m_physiDetector)
      ostr << "physiDetector has already built, ";
    if(m_motherDetector)
      ostr << "this is not at the top of detector tree, ";
    ostr << "and placement is not performed.";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
    return;
  }
  m_motherDetector=motherDetector;
  setTranslationVector(transV);
  setRotationVector(rotV);
  motherDetector->addDaughter(this);
  m_isModified=true;
  update();
  delete m_messenger;
  m_messenger = 0;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

bool GsimDetector::isCloneable()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif  
  if(m_className=="GsimDetector") {
    std::ostringstream ostr;
    ostr << "GsimDetector, " << m_name
	 << ", (w/o physiDetector) can't be cloned.";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
    return false;
  }
  
  std::list<GsimDetector*> detList;
  listDaughterDetector(detList);
  for(std::list<GsimDetector*>::iterator it=detList.begin();
      it!=detList.end();it++) {
    if((*it)->getClassName() == "GsimDetector") {
      std::ostringstream ostr;
      ostr << (*it)->getName()
	   << " can't be cloned, since it has a GsimDetector in its daughter lists.";
      GsimMessage::getInstance()
	->report("warning",ostr.str());
      return false;
    }
  }
  return true;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  
}

void GsimDetector::cloneDetector(G4ThreeVector transV,
				 G4ThreeVector rotV,
				 int copyNo)
				 
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if( isCloneable() ) {
    m_clonedPhysicalVolumeList.push_back(0);
    m_clonedCopyNoList.push_back(copyNo);
    m_clonedTranslationVectorList.push_back(transV);
    m_clonedRotationVectorList.push_back(rotV);
    m_clonedRotationMatrixList.push_back(new G4RotationMatrix());
  }
  m_isModified=true;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::doCloneDetector() {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if (m_clonedPhysicalVolumeList.size()==0) return;

  if(!m_physiDetector) {
    std::ostringstream ostr;
    ostr << "Cloning of the GsimDetector (w/o physiDetector), "
	 << m_name
	 << ", is forbidend.";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
    return;
  }

  for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
      it!=m_daughterDetectorContainer.end();it++) {
    GsimDetector* daughter =  (*it).second;
    daughter->doCloneDetector();
  }
  
  if(m_physiDetector) {
    G4String pvName = m_physiDetector->GetName();
    G4LogicalVolume* thisLogical = m_physiDetector->GetLogicalVolume();
    G4LogicalVolume* motherLogical = m_physiDetector->GetMotherLogical();

    std::list<G4VPhysicalVolume*>::iterator pvIt = m_clonedPhysicalVolumeList.begin();
    std::list<int>::iterator cnIt= m_clonedCopyNoList.begin();
    std::list<G4ThreeVector>::iterator tvIt = m_clonedTranslationVectorList.begin();
    std::list<G4ThreeVector>::iterator rvIt = m_clonedRotationVectorList.begin();
    std::list<G4RotationMatrix*>::iterator rmIt=m_clonedRotationMatrixList.begin();

    for(;pvIt!=m_clonedPhysicalVolumeList.end();pvIt++,cnIt++,tvIt++,rvIt++,rmIt++) {
      if( (*pvIt) != 0) continue;

      if( (*cnIt) == -999) {
	(*cnIt)=0;
	for(std::list<int>::iterator it =m_clonedCopyNoList.begin();
	    it!=m_clonedCopyNoList.end();it++) {
	  if ( (*it) > (*cnIt) ) (*cnIt)=(*it);
	}
	(*cnIt)+=1;
      }

      G4VPhysicalVolume* clonedPV = 
	new G4PVPlacement( (*rmIt),
			   (*tvIt),
			   thisLogical,
			   pvName,
			   motherLogical,
			   false,
			   (*cnIt),
			   false);
      (*pvIt)=clonedPV;
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::clearThisClone()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  std::list<G4VPhysicalVolume*>::iterator pvIt = m_clonedPhysicalVolumeList.begin();
  std::list<G4RotationMatrix*>::iterator rmIt=m_clonedRotationMatrixList.begin();
  
  for(;pvIt!=m_clonedPhysicalVolumeList.end();pvIt++,rmIt++) {
    delete (*pvIt);
    delete (*rmIt);
  }

  m_clonedPhysicalVolumeList.clear();
  m_clonedRotationMatrixList.clear();
  m_clonedCopyNoList.clear();
  m_clonedTranslationVectorList.clear();
  m_clonedRotationVectorList.clear();
  m_isModified=true;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::setBriefName(std::string briefname)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  std::list<std::string>::iterator itf
    =find(s_briefDetectorNameList.begin(),
	  s_briefDetectorNameList.end(),
	  briefname);
  if(itf==s_briefDetectorNameList.end()) {
    if(s_briefDetectorNameList.size()>=31) {
      std::ostringstream ostr;
      ostr << "The number of brief detector exceeds 31. "
	   << "The brief name," 
	   << briefname
	   << ", is not apperaed in brief detector history.";
      GsimMessage::getInstance()
	->report("warning",ostr.str());
    } else {
      s_briefDetectorNameList.push_back(briefname);
    }
  }
  m_briefName=briefname;

  int cnt=0;
  for(std::list<std::string>::iterator  it=s_briefDetectorNameList.begin();
      it!=s_briefDetectorNameList.end();it++,cnt++) {
    if((*it)==briefname) break;
  }
  m_briefDetectorID=cnt;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::setThisAndDaughterBriefName(std::string briefname)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  setBriefName(briefname);
  for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
      it!=m_daughterDetectorContainer.end();it++) {
    (*it).second->setThisAndDaughterBriefName(briefname);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::constructPhysiDetector() {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

			  
void GsimDetector::updateParametersEtc()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(m_name=="world") {
    G4LogicalVolume* logicDetector = m_physiDetector->GetLogicalVolume();
    if(!logicDetector) {
      GsimMessage::getInstance()
	->report("warning","No logicDetector is constructed.");
      return; 
    }
    G4VSolid* solidDetector = logicDetector->GetSolid();
    if(!solidDetector) {
      GsimMessage::getInstance()
	->report("warning","No solidDetector is constructed.");
      return;
    }
  
    G4Box* box = dynamic_cast<G4Box*>(solidDetector);
    box->SetXHalfLength(m_parameterArray[0]/2.);
    box->SetYHalfLength(m_parameterArray[1]/2.);
    box->SetZHalfLength(m_parameterArray[2]/2.);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::defaultBeginOfRunAction()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  for(std::map<G4LogicalVolume*,GsimSensitiveDetector*>::iterator
	it=m_sensitiveDetectorMap.begin();
      it!=m_sensitiveDetectorMap.end();it++) {
    (*it).second->setFastSimulationLevel(m_fastSimulationLevel);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::defaultEndOfRunAction()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

bool GsimDetector::defaultBeginOfEventAction(const G4Event* )
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif

  return false;
}

bool GsimDetector::defaultEndOfEventAction(const G4Event* )
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return false;
}

bool GsimDetector::defaultSteppingAction(const G4Step* theStep)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(!m_physiDetector) return false;
  if(m_name=="world") return false;
  switch (m_fastSimulationLevel) {
  case 6:
    {
      //a step touch the volume
      G4Track * theTrack = theStep->GetTrack();
      if(theTrack->GetTrackStatus()!=fAlive)  return true;
      
      G4String thisOuterDetectorName=m_physiDetector->GetName();
      G4StepPoint * thePostPoint = theStep->GetPostStepPoint();
      G4VPhysicalVolume * thePostPV = thePostPoint->GetPhysicalVolume();
      G4String thePostPVname = thePostPV->GetName();
      
      if(thePostPVname==thisOuterDetectorName)
      {
	//boundary
	int nSD=0;
	GsimSensitiveDetector* sd=countSensitiveDetectorUnderThisDetector(nSD);
	if(nSD==0) {
	  theTrack->SetTrackStatus(fStopAndKill);
	} else  {
	  G4Step dummyStep;
	  dummyStep.SetTrack(theTrack);
	  G4StepPoint* dummyPrePoint = dummyStep.GetPreStepPoint();
	  *(dummyPrePoint)=*(thePostPoint);
	  dummyStep.SetTotalEnergyDeposit(theTrack->GetKineticEnergy());
	  theTrack->SetTrackStatus(fStopAndKill);
	  sd->processHitsDetector(&dummyStep,0);
	  sd->process(&dummyStep,0);
	}
      }
      return true;
      break;
    }
  case 5:
    {
      //a step touch the volume
      G4Track * theTrack = theStep->GetTrack();
      if(theTrack->GetTrackStatus()!=fAlive)  return true;
      
      G4String thisOuterDetectorName=m_physiDetector->GetName();
      G4StepPoint * thePostPoint = theStep->GetPostStepPoint();
      G4VPhysicalVolume * thePostPV = thePostPoint->GetPhysicalVolume();
      G4String thePostPVname = thePostPV->GetName();
      
      if(thePostPVname==thisOuterDetectorName)
      {
	//boundary
	int nSD=0;
	GsimSensitiveDetector* sd=countSensitiveDetectorUnderThisDetector(nSD);
	if(nSD==0) {
	  theTrack->SetTrackStatus(fStopAndKill);
	} else  {
	  G4Step dummyStep;
	  dummyStep.SetTrack(theTrack);
	  G4StepPoint* dummyPrePoint = dummyStep.GetPreStepPoint();
	  *(dummyPrePoint)=*(thePostPoint);
	  dummyStep.SetTotalEnergyDeposit(theTrack->GetKineticEnergy());
	  theTrack->SetTrackStatus(fStopAndKill);
	  sd->processHitsDetector(&dummyStep,0);
	  sd->process(&dummyStep,0);
	}
      }
      return true;
      break;
    }
  case 4:
    {
      //Controled by UserLimits.
      return false;
      break;
    }
  case 3:
    {
      //treated in defaultPreTrackingAction(const G4Track* theTrack)
      return false;
      break;
    }
  case 2:
    {
      G4Track * theTrack = theStep->GetTrack();
      if(theTrack->GetTrackStatus()!=fAlive)  return true;

      GsimTrackInformation* trackInformation
	= dynamic_cast<GsimTrackInformation*>(theTrack->GetUserInformation());
      if(trackInformation) {
	int curBriefID=trackInformation->getCurrentBriefDetectorID();
	int preBriefID=trackInformation->getPreviousBriefDetectorID();
	if(curBriefID==m_briefDetectorID &&
	   curBriefID!=preBriefID) {
	  theTrack->SetTrackStatus(fSuspend);
	}
      }
      return true;
      break;
    }
  default:
    return false;
    break;
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

bool GsimDetector::defaultPreTrackingAction(const G4Track* theTrack)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(!m_physiDetector) return false;
  if(m_name=="world") return false;
  if(m_fastSimulationLevel!=3) return false;

  if(theTrack->GetTrackStatus()!=fAlive)  return true;

  GsimTrackInformation* trackInformation
    = dynamic_cast<GsimTrackInformation*>(theTrack->GetUserInformation());
  if(trackInformation->getShowerFlag()<=0) return true;

  
  
  G4String thisOuterDetectorName=m_physiDetector->GetName();
  G4String thePVname = theTrack->GetVolume()->GetName();
  
  if(thePVname!=thisOuterDetectorName) return true;

  int nSD=0;
  GsimSensitiveDetector* sd=countSensitiveDetectorUnderThisDetector(nSD);

  G4Track* aTrack = const_cast<G4Track*>(theTrack);
  if(nSD==0) {
    aTrack->SetTrackStatus(fStopAndKill);
  } else {
    G4Step dummyStep;
    //assign track
    //assign preStepPoint-->pos,time,kin,mom
    //assing Edep
    dummyStep.SetTrack(aTrack);
    G4StepPoint* dummyPrePoint = dummyStep.GetPreStepPoint();
    dummyPrePoint->SetPosition( theTrack->GetPosition() );
    dummyPrePoint->SetGlobalTime( theTrack->GetGlobalTime() );
    dummyPrePoint->SetKineticEnergy( theTrack->GetKineticEnergy() );
    dummyPrePoint->SetMomentumDirection( theTrack->GetMomentumDirection() );
    dummyPrePoint->SetMass( theTrack->GetDynamicParticle()->GetMass() );
    dummyPrePoint->SetTouchableHandle( theTrack->GetTouchableHandle() );
    
    dummyStep.SetTotalEnergyDeposit(theTrack->GetKineticEnergy());
    aTrack->SetTrackStatus(fStopAndKill);
    sd->process(&dummyStep,0);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return true;
}

bool GsimDetector::defaultPostTrackingAction(const G4Track* )
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return false;
}


void GsimDetector::beginOfRunAction()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::endOfRunAction()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

bool GsimDetector::beginOfEventAction(const G4Event* )
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return false;
}

bool GsimDetector::endOfEventAction(const G4Event* )
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return false;

}

bool GsimDetector::steppingAction(const G4Step* )
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return false;
}

bool GsimDetector::preTrackingAction(const G4Track* )
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return false;
}

bool GsimDetector::postTrackingAction(const G4Track* )
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return false;
}


void GsimDetector::processHits(const G4Step* ,G4TouchableHistory* )
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

std::string GsimDetector::getDirectoryName() {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  std::string dirName="";
  GsimDetector* mo = getMotherDetector();
  while(mo) {
    std::string add=mo->getName()+"/";
    dirName=add+dirName;
    mo = mo->getMotherDetector();
  }
  dirName="/"+dirName;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return dirName;
}

G4VPhysicalVolume* GsimDetector::getMotherPhysiDetector() {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  GsimDetector* mo = getMotherDetector();
  if(mo==0) {
    return 0;
  }
  G4VPhysicalVolume* movol=mo->getPhysiDetector();
  
  while(movol==0) {
    if(mo->getName()=="world") {
      G4VPhysicalVolume* physiWorld
	= GsimUtil::getUtil()->getPhysiWorld();
      return physiWorld;
    }
    mo = mo->getMotherDetector();
    if(mo==0) return 0;
    movol=mo->getPhysiDetector();
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return movol;
}

G4ThreeVector GsimDetector::
getRealTranslationVectorFromMotherPhysi(G4ThreeVector thisTraV)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4ThreeVector realTransVec(0,0,0);
  if(!m_physiDetector) return realTransVec;


  ///-----------------------------------------------
  G4VPhysicalVolume* movol=0;
  GsimDetector* mo = getMotherDetector();
  if(!mo) return realTransVec;


  
  std::list<G4ThreeVector> rotVStore;
  std::list<G4ThreeVector> traVStore;
  G4ThreeVector traV              = thisTraV;
  G4ThreeVector motherLocalCenter = mo->getLocalCenterVector();
  
  movol=mo->getPhysiDetector();
  while(movol==0) {
    G4ThreeVector rotV=mo->getRotationVector();
    rotVStore.push_back(rotV);
    traVStore.push_back(traV);
    
    traV     = mo->getTranslationVector();
    
    mo = mo->getMotherDetector();
    motherLocalCenter =G4ThreeVector(0,0,0);
    if(mo==0) break;
    motherLocalCenter = mo->getLocalCenterVector();
    movol=mo->getPhysiDetector();
  }
  G4ThreeVector lastTraV = traV;
  
  std::list<G4ThreeVector>::iterator rvsIt=rotVStore.begin();
  std::list<G4ThreeVector>::iterator tvsIt=traVStore.begin();
  for(;rvsIt!=rotVStore.end();rvsIt++,tvsIt++) {
    realTransVec+=(*tvsIt);
    realTransVec.rotateX((*rvsIt).x());
    realTransVec.rotateY((*rvsIt).y());
    realTransVec.rotateZ((*rvsIt).z());
  }
  realTransVec+=lastTraV;
  realTransVec+=motherLocalCenter;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return realTransVec;
}

void GsimDetector::setRealTranslationFromMotherPhysi()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(!m_physiDetector) return;

  GsimDetector* mo = getMotherDetector();
  if(!mo) return;

  G4ThreeVector traV              = getTranslationVector();
  
  G4ThreeVector realTraV
    = getRealTranslationVectorFromMotherPhysi(traV);
  m_physiDetector->SetTranslation(realTraV);

  std::list<G4VPhysicalVolume*>::iterator pvIt = m_clonedPhysicalVolumeList.begin();
  std::list<G4ThreeVector>::iterator tvIt = m_clonedTranslationVectorList.begin();

  for(;pvIt!=m_clonedPhysicalVolumeList.end();pvIt++,tvIt++) {

    if(!(*pvIt)) continue;

    realTraV
      = getRealTranslationVectorFromMotherPhysi((*tvIt));
    (*pvIt)->SetTranslation(realTraV);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimDetector::computeRealRotationMatrixFromMotherPhysi()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  CLHEP::HepRep3x3 unit(  1,0,0,
			  0,1,0,
			  0,0,1 );
  m_rotationMatrix->set(unit);
  
  std::list<G4ThreeVector>::iterator rvIt= m_clonedRotationVectorList.begin();
  std::list<G4RotationMatrix*>::iterator rmIt=m_clonedRotationMatrixList.begin();
  for(;rvIt!=m_clonedRotationVectorList.end();rvIt++,rmIt++) {
    (*rmIt)->set(unit);
  }

  G4VPhysicalVolume* movol=0;
  GsimDetector* mo = getMotherDetector();
  if(!mo) return;

  std::list<G4ThreeVector> rotVStore;
  
  movol=mo->getPhysiDetector();
  while(movol==0) {
    G4ThreeVector rotV=mo->getRotationVector();
    rotVStore.push_back(rotV);
    mo = mo->getMotherDetector();
    
    if(mo==0) break;
    movol=mo->getPhysiDetector();
  }

  

  for(std::list<G4ThreeVector>::reverse_iterator rIt=rotVStore.rbegin();
      rIt!=rotVStore.rend();rIt++) {
    m_rotationMatrix->rotateZ(-(*rIt).z());
    m_rotationMatrix->rotateY(-(*rIt).y());
    m_rotationMatrix->rotateX(-(*rIt).x());

    std::list<G4VPhysicalVolume*>::iterator pvIt
      = m_clonedPhysicalVolumeList.begin();
    for(rmIt=m_clonedRotationMatrixList.begin();
	rmIt!=m_clonedRotationMatrixList.end();rmIt++,pvIt++) {
      (*rmIt)->rotateZ(-(*rIt).z());
      (*rmIt)->rotateY(-(*rIt).y());
      (*rmIt)->rotateX(-(*rIt).x());
    }
  }

  m_rotationMatrix->rotateZ(-m_rotationVector.z());
  m_rotationMatrix->rotateY(-m_rotationVector.y());
  m_rotationMatrix->rotateX(-m_rotationVector.x());

  rvIt= m_clonedRotationVectorList.begin();
  rmIt=m_clonedRotationMatrixList.begin();
  
  for(;rvIt!=m_clonedRotationVectorList.end();rvIt++,rmIt++) {
    (*rmIt)->rotateZ(-(*rvIt).z());
    (*rmIt)->rotateY(-(*rvIt).y());
    (*rmIt)->rotateX(-(*rvIt).x());
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return;
}

G4ThreeVector GsimDetector::getAbsolutePosition(G4ThreeVector relativePosition)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  G4ThreeVector absolutePos=G4ThreeVector(0,0,0);

  std::list<G4ThreeVector> rotVStore;
  std::list<G4ThreeVector> traVStore;

  traVStore.push_back(relativePosition);

  GsimDetector* mo = getMotherDetector();

  while(mo) {
    traVStore.push_back(mo->getTranslationVector());
    rotVStore.push_back(mo->getRotationVector());
    mo = mo->getMotherDetector();
  }

  std::list<G4ThreeVector>::iterator rvsIt=rotVStore.begin();
  std::list<G4ThreeVector>::iterator tvsIt=traVStore.begin();
  
  for(;rvsIt!=rotVStore.end();rvsIt++,tvsIt++) {
    absolutePos+=(*tvsIt);
    absolutePos.rotateX((*rvsIt).x());
    absolutePos.rotateY((*rvsIt).y());
    absolutePos.rotateZ((*rvsIt).z());
  }
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return absolutePos;
}


GsimDetector* GsimDetector::getMotherDetectorWithPhysi() {
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  GsimDetector* mo = getMotherDetector();
  if(mo==0) {
    return 0;
  }
  G4VPhysicalVolume* movol=mo->getPhysiDetector();
  
  while(movol==0) {
    mo = mo->getMotherDetector();
    if(mo==0) {
      return 0;
    }
    movol=mo->getPhysiDetector();
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return mo;
}


bool GsimDetector::addDaughter(GsimDetector* daughter)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  bool isInserted = m_daughterDetectorContainer.insert(daughter);
  if(isInserted) {
    if(m_physiDetector) {
      G4RegionStore::GetInstance()->UpdateMaterialList(m_physiDetector);
    } else {
      G4VPhysicalVolume* pv =getMotherPhysiDetector();
      if(pv)
	G4RegionStore::GetInstance()->UpdateMaterialList(pv);
    }
  } else {
    std::ostringstream ostr;
    ostr << "Detector, "
	 << daughter->getName()
	 << ", is not Inserted as daughter."; 
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return isInserted;
}

GsimDetector* GsimDetector::findDetectorFromThis(std::string fullName)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(getFullName()==fullName) return this;
  for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
      it!=m_daughterDetectorContainer.end();it++) {
    if((*it).second->getFullName()==fullName) return (*it).second;
    GsimDetector* det = (*it).second->findDetectorFromThis(fullName);
    if(det) return det;
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return 0;
}


GsimDetector* GsimDetector::findDetectorFromWorld(std::string fullName)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(!s_worldDetector) return 0;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return s_worldDetector->findDetectorFromThis(fullName);
}

void GsimDetector::
listDaughterDetector(std::list<GsimDetector*>& detList)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
      it!=m_daughterDetectorContainer.end();it++) {
    detList.push_back ( (*it).second );
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}
  
void GsimDetector::
listFirstDaughterDetectorWihtPhysi(std::list<G4VPhysicalVolume*>& pvList)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
      it!=m_daughterDetectorContainer.end();it++) {
    GsimDetector* daughter=(*it).second;
    G4VPhysicalVolume* pv=daughter->getPhysiDetector();
    if(pv) {
      pvList.push_back(pv);
      std::list<G4VPhysicalVolume*> clonedList = daughter->getClonedPhysicalVolumeList();
      for(std::list<G4VPhysicalVolume*>::iterator clit=clonedList.begin();
          clit!=clonedList.end();clit++) {
        pvList.push_back((*clit));
      }
    } else {
      daughter->listFirstDaughterDetectorWihtPhysi(pvList);
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimSensitiveDetector* GsimDetector::countSensitiveDetectorUnderThisDetector(int& counter)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  GsimSensitiveDetector* sd=0;
  counter+=m_sensitiveDetectorMap.size();
  if(m_sensitiveDetectorMap.size()>0) sd=(m_sensitiveDetectorMap.begin())->second;
  for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
      it!=m_daughterDetectorContainer.end();it++) {
    GsimDetector* daughter=(*it).second;
    GsimSensitiveDetector* sdd=daughter->countSensitiveDetectorUnderThisDetector(counter);
    if(sd==0) sd=sdd;
  }
  return sd;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimDetector::setupSensitiveDetector()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}




void GsimDetector::fillDetectorData(GsimDetectorData& data)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  data.Clear();
  
  data.m_fullName=getFullName().c_str();
  data.m_briefName=m_briefName.c_str();
  data.m_className=m_className.c_str();
  data.m_detectorID=m_detectorID;
  data.m_briefDetectorID=m_briefDetectorID;

  if(m_motherDetector)
    data.m_motherDetectorID=m_motherDetector->getDetectorID();
  else
    data.m_motherDetectorID=-1;
  
  if(m_physiDetector)
    data.m_physiDetector=1;
  else
    data.m_physiDetector=0;
  
  
  data.m_localCenterVector.SetXYZ(m_localCenterVector.x(),
				  m_localCenterVector.y(),
				  m_localCenterVector.z());
  data.m_translationVector.SetXYZ(m_translationVector.x(),
				  m_translationVector.y(),
				  m_translationVector.z());
  data.m_rotationVector.SetXYZ(m_rotationVector.x(),
			       m_rotationVector.y(),
			       m_rotationVector.z());

  G4ThreeVector pos = getAbsolutePosition(m_translationVector);

  data.m_position.SetXYZ(pos.x(),
			 pos.y(),
			 pos.z());

  data.m_magneticFieldVector.SetXYZ(m_magneticFieldVector.x(),
				    m_magneticFieldVector.y(),
				    m_magneticFieldVector.z());

  
  
  data.m_userLimitsStepMax=m_userLimitsStepMax;
  data.m_userLimitsTrackMax=m_userLimitsTrackMax;
  data.m_userLimitsTimeMax=m_userLimitsTimeMax;
  data.m_userLimitsEkinMin=m_userLimitsEkinMin;
  data.m_userLimitsRangeMin=m_userLimitsRangeMin;
  
  
  data.m_outerMaterialName=m_outerMaterialName;
  data.m_outerColorName=m_outerColorName;
  if(m_isOuterVisible)
    data.m_isOuterVisible=1;
  else
    data.m_isOuterVisible=0;
  
  data.m_numberOfParameters=m_numberOfParameters;
  data.m_parameterArray = new Double_t[data.m_numberOfParameters];
  for(int k=0;k<data.m_numberOfParameters;k++) {
    data.m_parameterArray[k] = m_parameterArray[k];
  }

  data.m_fastSimulationLevel=m_fastSimulationLevel;
  data.m_userFlag=m_userFlag;
  
  data.m_nDaughter = m_daughterDetectorContainer.size();
  data.m_daughterIDArray = new Int_t[data.m_nDaughter];
  
  GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
  for(int k=0;k<data.m_nDaughter;it++,k++) {
    data.m_daughterIDArray[k]=(it->second)->getDetectorID();
  }

  data.m_numberOfSensitiveDetector=m_sensitiveDetectorMap.size();
  if(m_sensitiveDetectorMap.size()>0) {
    GsimSensitiveDetector* sd=((*(m_sensitiveDetectorMap.begin())).second);
    data.m_sensitiveDetectorName=sd->getName();
    if( sd->isStoreHit() )
      data.m_sensitiveDetectorWithHit=1;
    else
      data.m_sensitiveDetectorWithHit=0;
    if( sd->isStoreDigi() ) 
      data.m_sensitiveDetectorWithDigi=1;
    else
      data.m_sensitiveDetectorWithDigi=0;
  } else {
    data.m_sensitiveDetectorName="";
    data.m_sensitiveDetectorWithHit=0;
    data.m_sensitiveDetectorWithDigi=0;
  }

  data.m_copyNo = m_outerCopyNo;
  data.m_nClone = m_clonedPhysicalVolumeList.size();
  data.m_clonedCopyNoArray = new Int_t[data.m_nClone];
  
  data.m_clonedTranslationXArray = new Double_t[data.m_nClone];
  data.m_clonedTranslationYArray = new Double_t[data.m_nClone];
  data.m_clonedTranslationZArray = new Double_t[data.m_nClone];
  data.m_clonedRotationVectorXArray = new Double_t[data.m_nClone];
  data.m_clonedRotationVectorYArray = new Double_t[data.m_nClone];
  data.m_clonedRotationVectorZArray = new Double_t[data.m_nClone];
  data.m_clonedPositionXArray = new Double_t[data.m_nClone];
  data.m_clonedPositionYArray = new Double_t[data.m_nClone];
  data.m_clonedPositionZArray = new Double_t[data.m_nClone];

  std::list<int>::iterator itCNL=m_clonedCopyNoList.begin();
  std::list<G4ThreeVector>::iterator itTVL = m_clonedTranslationVectorList.begin();
  std::list<G4ThreeVector>::iterator itRVL = m_clonedRotationVectorList.begin();
  for(int k=0;k<data.m_nClone;k++,itCNL++,itTVL++,itRVL++) {
    data.m_clonedCopyNoArray[k] = (*itCNL);
    data.m_clonedTranslationXArray[k] = (*itTVL).x();
    data.m_clonedTranslationYArray[k] = (*itTVL).y();
    data.m_clonedTranslationZArray[k] = (*itTVL).z();
    data.m_clonedRotationVectorXArray[k] = (*itRVL).x();
    data.m_clonedRotationVectorYArray[k] = (*itRVL).y();
    data.m_clonedRotationVectorZArray[k] = (*itRVL).z();

    G4ThreeVector clpos = getAbsolutePosition( (*itTVL) );
    data.m_clonedPositionXArray[k] = clpos.x();
    data.m_clonedPositionYArray[k] = clpos.y();
    data.m_clonedPositionZArray[k] = clpos.z();
  }

#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


std::list<GsimSensitiveDetector*> GsimDetector::getSensitiveDetectorList()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  std::list<GsimSensitiveDetector*> lis;
  for(std::map<G4LogicalVolume*,GsimSensitiveDetector*>::iterator it
	=m_sensitiveDetectorMap.begin();
      it!=m_sensitiveDetectorMap.end();it++) {
    lis.push_back( (*it).second );
  }
  lis.sort();
  lis.unique();
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return lis;
}

void GsimDetector::scanThisAndDaughterSensitiveDetector(std::list<GsimSensitiveDetector*>& allList)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  std::list<GsimSensitiveDetector*> lis;
  for(std::map<G4LogicalVolume*,GsimSensitiveDetector*>::iterator it
	=m_sensitiveDetectorMap.begin();
      it!=m_sensitiveDetectorMap.end();it++) {
    lis.push_back( (*it).second );
  }
  allList.merge(lis);
  for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
      it!=m_daughterDetectorContainer.end();it++) {
    GsimDetector* daughter =  (*it).second;
    daughter->scanThisAndDaughterSensitiveDetector(allList);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

std::list<GsimSensitiveDetector*> GsimDetector::getThisAndDaughterSensitiveDetectorList()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  std::list<GsimSensitiveDetector*> allList;
  scanThisAndDaughterSensitiveDetector(allList);
  allList.sort();
  allList.unique();
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return allList;
}

void GsimDetector::ComputeTransformation
(const G4int copyNo, G4VPhysicalVolume* physVol) const
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(copyNo==m_outerCopyNo) {
    physVol->SetTranslation(m_translationVector);
    physVol->SetRotation(m_rotationMatrix);
  } else {
    std::list<int>::const_iterator cnIt= m_clonedCopyNoList.begin();
    std::list<G4ThreeVector>::const_iterator tvIt = m_clonedTranslationVectorList.begin();
    std::list<G4RotationMatrix*>::const_iterator rmIt=m_clonedRotationMatrixList.begin();
    bool isFound=false;
    for(;cnIt!=m_clonedCopyNoList.end();cnIt++,tvIt++,rmIt++) {
      if((*cnIt) == copyNo) {
	physVol->SetTranslation((*tvIt));
	physVol->SetRotation((*rmIt));
	isFound=true;
	break;
      }
    }
    if(isFound==false) {
      physVol->SetTranslation(G4ThreeVector(0,0,0));
      physVol->SetRotation(0);
      std::ostringstream ostr;
      ostr << "The copyNo, " << copyNo << ", is not found.";
      GsimMessage::getInstance()
	->report("warning",ostr.str());
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}
