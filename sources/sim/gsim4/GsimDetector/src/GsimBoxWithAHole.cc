/**
 *  @file
 *  @brief  GsimBoxWithAHole
 *  $Id: GsimBoxWithAHole.cc,v 1.3 2006/12/06 19:14:30 nanjo Exp $ 
 *  $Log: GsimBoxWithAHole.cc,v $
 *  Revision 1.3  2006/12/06 19:14:30  nanjo
 *  CVS variables.
 * 
 */
#include "GsimDetector/GsimBoxWithAHole.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4IntersectionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4PVPlacement.hh"

GsimBoxWithAHole::GsimBoxWithAHole(std::string name,
				   GsimDetector* motherDetector,
				   G4ThreeVector transV,G4ThreeVector rotV,
				   int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  m_className = "GsimBoxWithAHole";

  m_numberOfParameters=6;
  m_parameterArray= new double[m_numberOfParameters];
  m_parameterArray[0] =10.*mm; // x of box
  m_parameterArray[1] =10.*mm; // y of box
  m_parameterArray[2] =10.*mm; // z of box
  m_parameterArray[3] =0.*mm;  // x pos of tube
  m_parameterArray[4] =0.*mm;  // y pos of tube
  m_parameterArray[5] =3.*mm;  // r of tube

  m_outerMaterialName = "G4_PLASTIC_SC_VINYLTOLUENE";
  m_outerColorName    ="yellow";

  
  
  update();
  

#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

GsimBoxWithAHole::~GsimBoxWithAHole()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimBoxWithAHole::constructPhysiDetector()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4VPhysicalVolume* physiMother=getMotherPhysiDetector();
  std::string fullName = getFullName();
  if(physiMother) {
    
    double hx=m_parameterArray[0]/2.;
    double hy=m_parameterArray[1]/2.;
    double px=m_parameterArray[3];
    double py=m_parameterArray[4];
    double dist[4];
    dist[0]=std::sqrt(std::pow(+hx-px,2.)+std::pow(+hy-py,2.));
    dist[1]=std::sqrt(std::pow(+hx-px,2.)+std::pow(-hy-py,2.));
    dist[2]=std::sqrt(std::pow(-hx-px,2.)+std::pow(+hy-py,2.));
    dist[3]=std::sqrt(std::pow(-hx-px,2.)+std::pow(-hy-py,2.));
    double rmax=dist[0];
    for(int k=1;k<4;k++) {
      if(dist[k]>rmax) rmax=dist[k];
    }
    rmax=rmax*1.01;
    
    G4Tubs* solidTube = new G4Tubs(G4String( (fullName+"_tube").c_str()),
				   m_parameterArray[5],
				   rmax,
				   m_parameterArray[2]/2.,
				   0,2.*M_PI*rad);
    
    G4Box* solidBox = new G4Box(G4String((fullName+"_box").c_str()),
				m_parameterArray[0]/2.,
				m_parameterArray[1]/2.,
				m_parameterArray[2]/2.*1.01);
    
    
    G4IntersectionSolid* solidDetector
      = new G4IntersectionSolid( G4String(fullName.c_str()),
				 solidTube,
				 solidBox,
				 0,
				 G4ThreeVector(-m_parameterArray[3],-m_parameterArray[4],0.) );
    
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

void GsimBoxWithAHole::updateParametersEtc()
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

  double hx=m_parameterArray[0]/2.;
  double hy=m_parameterArray[1]/2.;
  double px=m_parameterArray[3];
  double py=m_parameterArray[4];
  double dist[4];
  dist[0]=std::sqrt(std::pow(+hx-px,2.)+std::pow(+hy-py,2.));
  dist[1]=std::sqrt(std::pow(+hx-px,2.)+std::pow(-hy-py,2.));
  dist[2]=std::sqrt(std::pow(-hx-px,2.)+std::pow(+hy-py,2.));
  dist[3]=std::sqrt(std::pow(-hx-px,2.)+std::pow(-hy-py,2.));
  double rmax=dist[0];
  for(int k=1;k<4;k++) {
    if(dist[k]>rmax) rmax=dist[k];
  }
  rmax=rmax*1.01;
  
  G4Box* solidBox = new G4Box(G4String( (fullName+"_box").c_str()),
			      m_parameterArray[0]/2.,
			      m_parameterArray[1]/2.,
			      m_parameterArray[2]/2.*1.01);
  
  G4Tubs* solidTube = new G4Tubs(G4String((fullName+"_tube").c_str()),
				 m_parameterArray[5],
				 rmax,
				 m_parameterArray[2]/2.,
				 0,2.*M_PI*rad);
  
  solidDetector
    = new G4IntersectionSolid( G4String(fullName.c_str()),
			       solidTube,
			       solidBox,
			       0,
			       G4ThreeVector(-m_parameterArray[3],-m_parameterArray[4],0.) );
  
  logicDetector->SetSolid(solidDetector);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


