/**
 *  $Id: GsimDetectorConstruction.cc,v 1.9 2006/08/01 05:27:55 nanjo Exp $
 *  $Log: GsimDetectorConstruction.cc,v $
 *  Revision 1.9  2006/08/01 05:27:55  nanjo
 *  GsimSpectrum is added. Debug print is updated. With/without Digi is implemented.
 *
 *  Revision 1.8  2006/02/21 15:54:36  nanjo
 *  The detector full name is used as a default sensitive detector name.
 *
 *  Revision 1.7  2006/02/17 04:22:57  nanjo
 *  GsimMaterialManager is added. Materials to be used hve to be decrlared before the 1st run.
 *
 *  Revision 1.6  2006/02/06 16:18:12  nanjo
 *  E391BA and E391CC00 are added.
 *
 *  Revision 1.5  2006/02/06 12:46:15  nanjo
 *  E391CC03 is added.
 *
 *  Revision 1.4  2006/01/27 00:06:26  nanjo
 *  Seeds are saved in GsimPersistencyManager
 *
 *  Revision 1.3  2006/01/26 04:50:58  nanjo
 *  Factory pattern and template method on factory and messenger classes is intorduced .
 *
 */
#include "GsimKernel/GsimDetectorConstruction.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimKernel/GsimDetectorManager.h"
#include "GsimKernel/GsimDetector.h"
#include "GsimKernel/GsimMaterialManager.h"


#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4VisAttributes.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4ThreeVector.hh"



GsimDetectorConstruction::GsimDetectorConstruction(GsimDetectorManager* dm)
  : m_DM(dm)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  m_solidWorld=0;
  m_physiWorld=0;
  m_logicWorld=0;
  m_worldVisAtt=0;
  m_materialManager = new GsimMaterialManager();
  m_isConstructed=false;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  

}

GsimDetectorConstruction::~GsimDetectorConstruction()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  // 
  //   delete m_solidWorld;
  //   delete m_physiWorld;
  //   delete m_logicWorld;
  //   delete m_worldVisAtt;
  //  ---> They are treated by detectorManager.
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}



G4VPhysicalVolume* GsimDetectorConstruction::Construct()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(m_isConstructed) return m_physiWorld;
  
  m_materialManager->defineMaterials();
  constructWorld();
  
  GsimMessage::getInstance()
    ->report("info","World is constructed.");

  m_isConstructed=true;

#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif

  return m_physiWorld;
}


G4VPhysicalVolume* GsimDetectorConstruction::constructWorld()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif


  m_solidWorld = new G4Box("/world",
			   10.*m,10.*m,20.*m);
  
  G4Material* matWorld = G4NistManager::Instance()
    ->FindOrBuildMaterial("G4_Galactic",true);
						    
  m_logicWorld
    = new G4LogicalVolume(m_solidWorld,matWorld,"/world");

  m_worldVisAtt = new G4VisAttributes(G4Color(1.,1.,1.));
  m_logicWorld->SetVisAttributes(m_worldVisAtt);
  
  m_physiWorld
    = new G4PVPlacement(0,
			G4ThreeVector(),
			"/world",
			m_logicWorld,
			0,
			false,
			0);
  
  GsimDetector* detWorld = new GsimDetector(m_physiWorld);
  m_DM->registerDetector(detWorld);
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
  return m_physiWorld;
}
