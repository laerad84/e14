/**
 *  @file
 *  @brief  GsimPolyhedra2WithASquareHole
 *  $Id: GsimPolyhedra2WithASquareHole.cc
 *  $Log:
 */
#include "GsimDetector/GsimPolyhedra2WithASquareHole.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4Polyhedra.hh"
#include "G4IntersectionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4PVPlacement.hh"
#include "G4Polyhedron.hh"

GsimPolyhedra2WithASquareHole::GsimPolyhedra2WithASquareHole(std::string name,
							     GsimDetector* motherDetector,
							     G4ThreeVector transV,G4ThreeVector rotV,
							     int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_className = "GsimPolyhedra2WithASquareHole";

  m_numberOfParameters=6;//startPhi, openingAngel,numSide, Z  Rmin Rmax 
  m_parameterArray= new double[m_numberOfParameters];
  m_parameterArray[0] =0; // startPhi
  m_parameterArray[1] =360*deg; // openingAngle
  m_parameterArray[2] =8; // numSide
  m_parameterArray[3] =20.*mm; // z length
  m_parameterArray[4] =20.*mm; // rmax
  m_parameterArray[5] =10.*mm; // rmin

  m_outerMaterialName = "G4_PLASTIC_SC_VINYLTOLUENE";
  m_outerColorName    ="blue";
  
  update();
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimPolyhedra2WithASquareHole::~GsimPolyhedra2WithASquareHole()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimPolyhedra2WithASquareHole::constructPhysiDetector()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4VPhysicalVolume* physiMother=getMotherPhysiDetector();
  std::string fullName = getFullName();
  if(physiMother) {
    double z[2] = {-m_parameterArray[3]/2.,m_parameterArray[3]/2.};
    double rmin[2] = {0,0};
    double rmax[2] = {m_parameterArray[4],m_parameterArray[4]};
    G4Polyhedra* solidMain
      = new G4Polyhedra(G4String((fullName+"_main").c_str()),
			m_parameterArray[0],m_parameterArray[1],
			int(m_parameterArray[2]),2,
			z,rmin,rmax);
    
    
    double rmin2[2] = {m_parameterArray[5],m_parameterArray[5]};
    double rmax2[2] = {m_parameterArray[4]*std::sqrt(2.)*1.01,m_parameterArray[4]*std::sqrt(2.)*1.01};
    G4Polyhedra* solidSub
      = new G4Polyhedra(G4String((fullName+"_sub").c_str()),
			45*deg,360*deg,
			4,2,
			z,rmin2,rmax2);
    
    G4IntersectionSolid* solidDetector
      = new G4IntersectionSolid( G4String(fullName.c_str()),
				 solidMain,
				 solidSub,
				 0,
				 G4ThreeVector(0,0,0.) );
    
  
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

void GsimPolyhedra2WithASquareHole::updateParametersEtc()
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

  double z[2] = {-m_parameterArray[3]/2.,m_parameterArray[3]/2.};
  double rmin[2] = {0,0};
  double rmax[2] = {m_parameterArray[4],m_parameterArray[4]};
  G4Polyhedra* solidMain
    = new G4Polyhedra(G4String((fullName+"_main").c_str()),
		      m_parameterArray[0],m_parameterArray[1],
		      int(m_parameterArray[2]),2,
		      z,rmin,rmax);
  
  
  double rmin2[2] = {m_parameterArray[5],m_parameterArray[5]};
  double rmax2[2] = {m_parameterArray[4]*std::sqrt(2.)*1.01,m_parameterArray[4]*std::sqrt(2.)*1.01};
  double z2[2] = {-m_parameterArray[3]/2.*1.01,m_parameterArray[3]/2.*1.01};
  G4Polyhedra* solidSub
    = new G4Polyhedra(G4String((fullName+"_sub").c_str()),
		      45*deg,360*deg,
		      4,2,
		      z2,rmin2,rmax2);
  
  solidDetector
    = new G4IntersectionSolid( G4String(fullName.c_str()),
			       solidMain,
			       solidSub,
			       0,
			       G4ThreeVector(0,0,0.) );
  
  logicDetector->SetSolid(solidDetector);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

