/**
 *  @file
 *  @brief  GsimTubeWithAHole
 *  $Id: $ 
 *  $Log: $
 */
#include "GsimDetector/GsimTubeWithAHole.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4PVPlacement.hh"

GsimTubeWithAHole::GsimTubeWithAHole(std::string name,
				     GsimDetector* motherDetector,
				     G4ThreeVector transV,G4ThreeVector rotV,
				     int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  m_className = "GsimTubeWithAHole";

  m_numberOfParameters=6;
  m_parameterArray= new double[m_numberOfParameters];
  m_parameterArray[0] =10.*mm; // r of tube
  m_parameterArray[1] =10.*mm; // z of tube
  m_parameterArray[2] =0.*mm; // x pos of box
  m_parameterArray[3] =0.*mm;  // y pos of box
  m_parameterArray[4] =3.*mm;  // x of box
  m_parameterArray[5] =4.*mm;  // y of box

  m_outerMaterialName = "G4_PLASTIC_SC_VINYLTOLUENE";
  m_outerColorName    ="yellow";

  
  
  update();
  

#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimTubeWithAHole::~GsimTubeWithAHole()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimTubeWithAHole::constructPhysiDetector()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4VPhysicalVolume* physiMother=getMotherPhysiDetector();
  std::string fullName = getFullName();
  if(physiMother) {
    G4Tubs* solidTube = new G4Tubs(G4String( (fullName+"_tube").c_str()), // name
				   0., // min r
				   m_parameterArray[0], // max r
				   m_parameterArray[1]/2., // z
				   0.*deg, // sPhi
				   360.*deg); // dPhi
    
    G4Box* solidBox = new G4Box(G4String((fullName+"_box").c_str()), // name
				m_parameterArray[4]/2., // x
				m_parameterArray[5]/2., // y
				m_parameterArray[1]/2); // z
    
    G4SubtractionSolid* solidDetector
      = new G4SubtractionSolid( G4String(fullName.c_str()),
				solidTube,
				solidBox,
				0,
				G4ThreeVector(-m_parameterArray[2],-m_parameterArray[3],0.) );

    
    G4LogicalVolume* logicDetector
      = new G4LogicalVolume(solidDetector,
			    GsimUtil::getUtil()->findMaterial(m_outerMaterialName),
			    G4String(fullName.c_str()));
    G4VisAttributes* visAtt
      = new G4VisAttributes(GsimUtil::getUtil()->findColor(m_outerColorName));
    logicDetector->SetVisAttributes(visAtt);
    
    m_physiDetector = 
      new G4PVPlacement(m_rotationMatrix,
			G4ThreeVector(),
			G4String(fullName.c_str()),
			logicDetector,
			physiMother,
			false,0
			);

  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimTubeWithAHole::updateParametersEtc()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(!m_physiDetector) return;
  
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


  delete solidDetector;
  solidDetector=0;
  
  std::string fullName = getFullName();

  G4Tubs* solidTube = new G4Tubs(G4String( (fullName+"_tube").c_str()), // name
				 0., // min r
				 m_parameterArray[0], // max r
				 m_parameterArray[1]/2., // z
				 0.*deg, // sPhi
				 360.*deg); // dPhi
  
  G4Box* solidBox = new G4Box(G4String((fullName+"_box").c_str()), // name
			      m_parameterArray[4]/2., // x
			      m_parameterArray[5]/2., // y
			      m_parameterArray[1]/2); // z
  
  solidDetector
    = new G4SubtractionSolid( G4String(fullName.c_str()),
			      solidTube,
			      solidBox,
			      0,
			      G4ThreeVector(-m_parameterArray[2],-m_parameterArray[3],0.) );
  
  logicDetector->SetSolid(solidDetector);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}



