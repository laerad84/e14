/**
 *  $Id: GsimBox.cc,v 1.3 2006/08/01 05:29:46 nanjo Exp $
 *  $Log: GsimBox.cc,v $
 *  Revision 1.3  2006/08/01 05:29:46  nanjo
 *  Debug print is updated.
 *
 *  Revision 1.2  2006/02/21 15:55:17  nanjo
 *  The detector full name is used as a solid, logical and physical volume name.
 *
 *  Revision 1.1  2006/01/26 06:11:19  nanjo
 *  Detector and data classes are added.
 *
 */
#include "GsimDetector/GsimBox.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4PVPlacement.hh"

GsimBox::GsimBox(std::string name,
		 GsimDetector* motherDetector,
		 G4ThreeVector transV,G4ThreeVector rotV,
		 int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  m_className = "GsimBox";

  m_numberOfParameters=3;
  m_parameterArray= new double[m_numberOfParameters];
  m_parameterArray[0] =10.*mm; // x length of box
  m_parameterArray[1] =10.*mm; // y length of box
  m_parameterArray[2] =10.*mm; // z length of box

  m_outerMaterialName = "G4_PLASTIC_SC_VINYLTOLUENE";
  m_outerColorName    ="blue";
  
  update();
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  
}

GsimBox::~GsimBox()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  
}

void GsimBox::constructPhysiDetector()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4VPhysicalVolume* physiMother=getMotherPhysiDetector();
  std::string fullName = getFullName();
  if(physiMother) {
    G4Box* solidDetector
      = new G4Box(G4String(fullName.c_str()),
		  m_parameterArray[0]/2.,
		  m_parameterArray[1]/2.,
		  m_parameterArray[2]/2.);
  
    G4LogicalVolume* logicDetector
      = new G4LogicalVolume(solidDetector,
			    GsimUtil::getUtil()->findMaterial(m_outerMaterialName),
			    G4String(fullName.c_str()));
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

void GsimBox::updateParametersEtc()
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
  
  G4Box* box = dynamic_cast<G4Box*>(solidDetector);
  box->SetXHalfLength(m_parameterArray[0]/2.);
  box->SetYHalfLength(m_parameterArray[1]/2.);
  box->SetZHalfLength(m_parameterArray[2]/2.);
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  
}

void GsimBox::ComputeDimensions
(G4Box& box, const G4int copyNo, const G4VPhysicalVolume*) const
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  box.SetXHalfLength(m_parameterArray[0]/2.);
  box.SetYHalfLength(m_parameterArray[1]/2.);
  box.SetZHalfLength(m_parameterArray[2]/2.);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

