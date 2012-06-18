/**
 *  @file
 *  @brief  GsimTrap
 *  $Id: GsimTrap.cc,v 1.3 2006/12/06 19:14:30 nanjo Exp $ 
 *  $Log: GsimTrap.cc,v $
 *  Revision 1.3  2006/12/06 19:14:30  nanjo
 *  CVS variables.
 *
 */
#include "GsimDetector/GsimTrap.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4Trap.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4PVPlacement.hh"

GsimTrap::GsimTrap(std::string name,
		   GsimDetector* motherDetector,
		   G4ThreeVector transV,G4ThreeVector rotV,
		   int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  m_className = "GsimTrap";

  m_numberOfParameters=11;
  //      pDz     Full-length along the z-axis
  //      pTheta  Polar angle of the line joining the centres of the faces
  //              at -/+pDz
  //      pPhi    Azimuthal angle of the line joing the centre of the face at
  //              -pDz to the centre of the face at +pDz
  //      pDy1    Full-length along y of the face at -pDz
  //      pDx1    Full-length along x of the side at y=-pDy1 of the face at -pDz
  //      pDx2    Full-length along x of the side at y=+pDy1 of the face at -pDz
  //      pAlp1   Angle with respect to the y axis from the centre of the side
  //              at y=-pDy1 to the centre at y=+pDy1 of the face at -pDz
  //
  //      pDy2    Full-length along y of the face at +pDz
  //      pDx3    Full-length along x of the side at y=-pDy2 of the face at +pDz
  //      pDx4    Full-length along x of the side at y=+pDy2 of the face at +pDz
  //      pAlp2   Angle with respect to the y axis from the centre of the side
  //              at y=-pDy2 to the centre at y=+pDy2 of the face at +pDz
  //
  m_parameterArray= new double[m_numberOfParameters];
  m_parameterArray[0] =1.*mm;
  m_parameterArray[1] =0*deg;
  m_parameterArray[2] =0*deg;
  m_parameterArray[3] =2.*cm;
  m_parameterArray[4] =1.*cm;
  m_parameterArray[5] =3.*cm;
  m_parameterArray[6] =0.*deg;
  m_parameterArray[7] =2.*cm;
  m_parameterArray[8] =1.*cm;
  m_parameterArray[9] =3.*cm;
  m_parameterArray[10] =0.*deg;

  m_outerMaterialName = "G4_PLASTIC_SC_VINYLTOLUENE";
  m_outerColorName    ="blue";
  
  update();

#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimTrap::~GsimTrap()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimTrap::constructPhysiDetector()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4VPhysicalVolume* physiMother=getMotherPhysiDetector();
  std::string fullName = getFullName();
  if(physiMother) {
    G4Trap* solidDetector
      = new G4Trap( G4String(fullName.c_str()),
		    m_parameterArray[0]/2.,
		    m_parameterArray[1],m_parameterArray[2],
		    m_parameterArray[3]/2.,m_parameterArray[4]/2.,m_parameterArray[5]/2.,
		    m_parameterArray[6],
		    m_parameterArray[7]/2.,m_parameterArray[8]/2.,m_parameterArray[9]/2.,
		    m_parameterArray[10]);
  
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

void GsimTrap::updateParametersEtc()
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
  
  G4Trap* trap = dynamic_cast<G4Trap*>(solidDetector);

  trap->SetAllParameters(m_parameterArray[0]/2.,
			 m_parameterArray[1],m_parameterArray[2],
			 m_parameterArray[3]/2.,m_parameterArray[4]/2.,m_parameterArray[5]/2.,
			 m_parameterArray[6],
			 m_parameterArray[7]/2.,m_parameterArray[8]/2.,m_parameterArray[9]/2.,
			 m_parameterArray[10]);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimTrap::ComputeDimensions
(G4Trap& trap, const G4int copyNo, const G4VPhysicalVolume*) const
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  trap.SetAllParameters(m_parameterArray[0]/2.,
			m_parameterArray[1],m_parameterArray[2],
			m_parameterArray[3]/2.,m_parameterArray[4]/2.,m_parameterArray[5]/2.,
			m_parameterArray[6],
			m_parameterArray[7]/2.,m_parameterArray[8]/2.,m_parameterArray[9]/2.,
			m_parameterArray[10]);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}
