/**
 *  $Id: GsimTube.cc,v 1.4 2006/08/01 05:29:46 nanjo Exp $
 *  $Log: GsimTube.cc,v $
 *  Revision 1.4  2006/08/01 05:29:46  nanjo
 *  Debug print is updated.
 *
 *  Revision 1.3  2006/02/21 15:55:17  nanjo
 *  The detector full name is used as a solid, logical and physical volume name.
 *
 *  Revision 1.2  2006/02/06 16:18:12  nanjo
 *  E391BA and E391CC00 are added.
 *
 *  Revision 1.1  2006/01/26 06:11:19  nanjo
 *  Detector and data classes are added.
 *
 */
#include "GsimDetector/GsimTube.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4PVPlacement.hh"

GsimTube::GsimTube(std::string name,
		   GsimDetector* motherDetector,
		   G4ThreeVector transV,G4ThreeVector rotV,
		   int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  m_className = "GsimTube";

  m_numberOfParameters=5;
  m_parameterArray= new double[m_numberOfParameters];
  m_parameterArray[0] =0.*mm; // r minimum
  m_parameterArray[1] =10.*mm; // r maximum
  m_parameterArray[2] =10.*mm; // z length of tube
  m_parameterArray[3] =0.*rad; // start angle
  m_parameterArray[4] =2.*M_PI*rad; // opening angle

  m_outerMaterialName = "G4_PLASTIC_SC_VINYLTOLUENE";
  m_outerColorName    ="red";

  
  
  update();
  

#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimTube::~GsimTube()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimTube::constructPhysiDetector()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4VPhysicalVolume* physiMother=getMotherPhysiDetector();
  std::string fullName = getFullName();
  if(physiMother) {
    G4Tubs* solidDetector
      = new G4Tubs(G4String(fullName.c_str()),
		   m_parameterArray[0],
		   m_parameterArray[1],
		   m_parameterArray[2]/2.,
		   m_parameterArray[3],
		   m_parameterArray[4]);
    
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

void GsimTube::updateParametersEtc()
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
  
  G4Tubs* tube = dynamic_cast<G4Tubs*>(solidDetector);
  tube->SetInnerRadius(m_parameterArray[0]);
  tube->SetOuterRadius(m_parameterArray[1]);
  tube->SetZHalfLength(m_parameterArray[2]/2.);
  tube->SetStartPhiAngle(m_parameterArray[3]);
  tube->SetDeltaPhiAngle(m_parameterArray[4]);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif

}


void GsimTube::ComputeDimensions
(G4Tubs& tube, const G4int copyNo, const G4VPhysicalVolume*) const
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  tube.SetInnerRadius(m_parameterArray[0]);
  tube.SetOuterRadius(m_parameterArray[1]);
  tube.SetZHalfLength(m_parameterArray[2]/2.);
  tube.SetStartPhiAngle(m_parameterArray[3]);
  tube.SetDeltaPhiAngle(m_parameterArray[4]);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}
