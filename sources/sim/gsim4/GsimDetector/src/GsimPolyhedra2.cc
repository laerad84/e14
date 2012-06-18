/**
 *  @file
 *  @brief  GsimPolyhedra2
 *  $Id: GsimPolyhedra2.cc,v 1.7 2006/12/06 19:14:30 nanjo Exp $
 *  $Log: GsimPolyhedra2.cc,v $
 *  Revision 1.7  2006/12/06 19:14:30  nanjo
 *  CVS variables.
 *
 */
#include "GsimDetector/GsimPolyhedra2.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4Polyhedra.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4PVPlacement.hh"
#include "G4Polyhedron.hh"

GsimPolyhedra2::GsimPolyhedra2(std::string name,
			       GsimDetector* motherDetector,
			       G4ThreeVector transV,G4ThreeVector rotV,
			       int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_className = "GsimPolyhedra2";

  m_numberOfParameters=6;//startPhi, openingAngel,numSide, Z  Rmin Rmax 
  m_parameterArray= new double[m_numberOfParameters];
  m_parameterArray[0] =0; // startPhi
  m_parameterArray[1] =360*deg; // openingAngle
  m_parameterArray[2] =8; // numSide
  m_parameterArray[3] =20.*mm; // z length
  m_parameterArray[4] =10.*mm; // rmin
  m_parameterArray[5] =20.*mm; // rmax

  m_outerMaterialName = "G4_PLASTIC_SC_VINYLTOLUENE";
  m_outerColorName    ="blue";
  
  update();
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimPolyhedra2::~GsimPolyhedra2()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimPolyhedra2::constructPhysiDetector()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4VPhysicalVolume* physiMother=getMotherPhysiDetector();
  std::string fullName = getFullName();
  if(physiMother) {
    double z[2] = {-m_parameterArray[3]/2.,m_parameterArray[3]/2.};
    double rmin[2] = {m_parameterArray[4],m_parameterArray[4]};
    double rmax[2] = {m_parameterArray[5],m_parameterArray[5]};
    G4Polyhedra* solidDetector
      = new G4Polyhedra(G4String(fullName.c_str()),
			m_parameterArray[0],m_parameterArray[1],
			int(m_parameterArray[2]),2,
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

void GsimPolyhedra2::updateParametersEtc()
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
  G4Polyhedra* hedra = dynamic_cast<G4Polyhedra*>(solidDetector);
  setDimension(hedra,
	       m_parameterArray[0],m_parameterArray[1],m_parameterArray[2],
	       m_parameterArray[3],m_parameterArray[4],m_parameterArray[5]);

#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimPolyhedra2::setDimension(G4Polyhedra* hedra,
				  double p0,double p1,double p2,
				  double p3,double p4,double p5) const
{
  G4PolyhedraHistorical* originalParam = hedra->GetOriginalParameters();
  originalParam->Start_angle=p0;
  originalParam->Opening_angle=p1;
  originalParam->numSide=int(p2);
  originalParam->Z_values[0]=-p3/2.;
  originalParam->Z_values[1]= p3/2.;
  
  G4double phiTotal = p1;
  if ( (phiTotal <=0) || (phiTotal >= twopi*(1-DBL_EPSILON)) )
    phiTotal = twopi;
  G4double convertRad = std::cos(0.5*phiTotal/originalParam->numSide);

  originalParam->Rmin[0]=p4/convertRad;
  originalParam->Rmax[0]=p5/convertRad;
  originalParam->Rmin[1]=p4/convertRad;
  originalParam->Rmax[1]=p5/convertRad;
  hedra->Reset();
  //some effect in updating visualization
  hedra->GetPolyhedron();

  /////////////////////////////////////////////////////
  // Befor geant4.8.2.p01
  // Scale originalParam by 1/convertRad temporally
  // after Reset() due to Geant4.8.0.p01 code.
  // This will be fixed in the future Geant4 release.
  //originalParam->Rmin[0]=p4;
  //originalParam->Rmax[0]=p5;
  //originalParam->Rmin[1]=p4;
  //originalParam->Rmax[1]=p5;
  //hedra->Reset();
  //originalParam->Rmin[0]=p4/convertRad;
  //originalParam->Rmax[0]=p5/convertRad;
  //originalParam->Rmin[1]=p4/convertRad;
  //originalParam->Rmax[1]=p5/convertRad;
  //
  //some effect in updating visualization
  //hedra->GetPolyhedron();
  /////////////////////////////////////////////////////
}

void GsimPolyhedra2::ComputeDimensions
(G4Polyhedra& hedra, const G4int copyNo, const G4VPhysicalVolume*) const
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  setDimension(&hedra,
	       m_parameterArray[0],m_parameterArray[1],m_parameterArray[2],
	       m_parameterArray[3],m_parameterArray[4],m_parameterArray[5]);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}
