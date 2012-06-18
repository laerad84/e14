/**
 *  @file
 *  @brief  GsimPolycone2
 *  $Id: GsimPolycone2.cc,v 1.3 2006/12/06 19:14:30 nanjo Exp $
 *  $Log: GsimPolycone2.cc,v $
 *  Revision 1.3  2006/12/06 19:14:30  nanjo
 *  CVS variables.
 *
 */
#include "GsimDetector/GsimPolycone2.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4Polycone.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4PVPlacement.hh"
#include "G4Polyhedron.hh"

GsimPolycone2::GsimPolycone2(std::string name,
			     GsimDetector* motherDetector,
			     G4ThreeVector transV,G4ThreeVector rotV,
			     int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_className = "GsimPolycone2";

  m_numberOfParameters=7;//startPhi, openingAngel,numSide, Z  Rmin1 Rmax1  Rmin2 Rmax2 
  m_parameterArray= new double[m_numberOfParameters];
  m_parameterArray[0] =0; // startPhi
  m_parameterArray[1] =360*deg; // openingAngle
  m_parameterArray[2] =20.*mm; // z length
  m_parameterArray[3] =10.*mm; // rmin1
  m_parameterArray[4] =20.*mm; // rmax1
  m_parameterArray[5] =15.*mm; // rmin2
  m_parameterArray[6] =20.*mm; // rmax2

  m_outerMaterialName = "G4_PLASTIC_SC_VINYLTOLUENE";
  m_outerColorName    ="blue";
  
  update();
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  
}

GsimPolycone2::~GsimPolycone2()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimPolycone2::constructPhysiDetector()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4VPhysicalVolume* physiMother=getMotherPhysiDetector();
  std::string fullName = getFullName();
  if(physiMother) {
    double z[2] = {-m_parameterArray[2]/2.,m_parameterArray[2]/2.};
    double rmin[2] = {m_parameterArray[3],m_parameterArray[5]};
    double rmax[2] = {m_parameterArray[4],m_parameterArray[6]};
    G4Polycone* solidDetector
      = new G4Polycone(G4String(fullName.c_str()),
		       m_parameterArray[0],m_parameterArray[1],
		       2,
		       z,rmin,rmax);
    
  
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

void GsimPolycone2::updateParametersEtc()
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
  G4Polycone* cone = dynamic_cast<G4Polycone*>(solidDetector);
  setDimension(cone,
	       m_parameterArray[0],m_parameterArray[1],m_parameterArray[2],
	       m_parameterArray[3],m_parameterArray[4],m_parameterArray[5],
	       m_parameterArray[6]);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimPolycone2::setDimension(G4Polycone* cone,
				 double p0,double p1,double p2,
				 double p3,double p4,double p5,double p6) const
{
  G4PolyconeHistorical* originalParam = cone->GetOriginalParameters();

  originalParam->Start_angle=p0;
  originalParam->Opening_angle=p1;
  originalParam->Z_values[0]=-p2/2.;
  originalParam->Z_values[1]= p2/2.;

  originalParam->Rmin[0]=p3;
  originalParam->Rmax[0]=p4;
  originalParam->Rmin[1]=p5;
  originalParam->Rmax[1]=p6;
  cone->Reset();

  //some effect in updating visualization
  cone->GetPolyhedron();
}


void GsimPolycone2::ComputeDimensions
(G4Polycone& cone, const G4int copyNo, const G4VPhysicalVolume*) const
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  setDimension(&cone,
	       m_parameterArray[0],m_parameterArray[1],m_parameterArray[2],
	       m_parameterArray[3],m_parameterArray[4],m_parameterArray[5],
	       m_parameterArray[6]);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}
