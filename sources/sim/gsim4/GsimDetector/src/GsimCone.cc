/**
 *  $Id: GsimCone.cc,v 1.4 2006/12/06 19:14:30 nanjo Exp $ 
 *  $Log: GsimCone.cc,v $
 *  Revision 1.4  2006/12/06 19:14:30  nanjo
 *  CVS variables.
 * 
 */
#include "GsimDetector/GsimCone.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4PVPlacement.hh"

GsimCone::GsimCone(std::string name,
		   GsimDetector* motherDetector,
		   G4ThreeVector transV,G4ThreeVector rotV,
		   int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  m_className = "GsimCone";

  m_numberOfParameters=3;
  m_parameterArray= new double[m_numberOfParameters];
  m_parameterArray[0] =5.*mm; // r1
  m_parameterArray[1] =10.*mm; // r2
  m_parameterArray[2] =10.*mm; // z length of cone

  m_outerMaterialName = "G4_PLASTIC_SC_VINYLTOLUENE";
  m_outerColorName    ="red";
  
  update();
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimCone::~GsimCone()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimCone::constructPhysiDetector()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4VPhysicalVolume* physiMother=getMotherPhysiDetector();
  std::string fullName = getFullName();
  if(physiMother) {
    G4Cons* solidDetector
      = new G4Cons(G4String(fullName.c_str()),
		   0,m_parameterArray[0],
		   0,m_parameterArray[1],
		   m_parameterArray[2]/2.,
		   0,2.*M_PI*rad);
    
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

void GsimCone::updateParametersEtc()
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
  
  G4Cons* cone = dynamic_cast<G4Cons*>(solidDetector);
  cone->SetInnerRadiusMinusZ( 0. );
  cone->SetOuterRadiusMinusZ(m_parameterArray[0]);
  cone->SetInnerRadiusPlusZ (0.);
  cone->SetOuterRadiusPlusZ(m_parameterArray[1]);
  cone->SetZHalfLength(m_parameterArray[2]/2.);
  cone->SetStartPhiAngle(0.);
  cone->SetDeltaPhiAngle(2.*M_PI*rad);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimCone::ComputeDimensions
(G4Cons& cone, const G4int copyNo, const G4VPhysicalVolume*) const
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  cone.SetInnerRadiusMinusZ( 0. );
  cone.SetOuterRadiusMinusZ(m_parameterArray[0]);
  cone.SetInnerRadiusPlusZ (0.);
  cone.SetOuterRadiusPlusZ(m_parameterArray[1]);
  cone.SetZHalfLength(m_parameterArray[2]/2.);
  cone.SetStartPhiAngle(0.);
  cone.SetDeltaPhiAngle(2.*M_PI*rad);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

