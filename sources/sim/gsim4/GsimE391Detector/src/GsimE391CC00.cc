/**
 *  @file
 *  @brief  GsimE391CC00
 *  $Id: GsimE391CC00.cc,v 1.9 2007/02/04 12:56:46 nanjo Exp $ 
 *  $Log: GsimE391CC00.cc,v $
 *  Revision 1.9  2007/02/04 12:56:46  nanjo
 *  GsimBoxWithAHole is used.
 *
 *  Revision 1.8  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimE391Detector/GsimE391CC00.h"
#include "GsimE391Detector/GsimUserGeom.h"
#include "GsimDetector/GsimBox.h"
#include "GsimDetector/GsimTube.h"
#include "GsimDetector/GsimBoxWithAHole.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4Box.hh"

using namespace E391;


GsimE391CC00::GsimE391CC00(std::string name,
			   GsimDetector* motherDetector,
			   G4ThreeVector transV,G4ThreeVector rotV,
			   int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{

  m_className = "GsimE391CC00";






  int  ivol=0;

  // CC00

  // tungsten heavy alloy
  double  w_thick = 2.0;
  double  w_rmax  = 40.0/2.0;
  double  w_rmin  = 8.2/2.0;
  // scintillator  
  double  s_thick  = 0.5;
  double  s_width  = 42.0;
  double  s_height = w_rmax;
  double  s_rmin   = w_rmin;

  double  gap = 0.1; // gap between W and S
  // CC00 MOTH
  double  cc00_width  = s_width;
  double  cc00_height = s_height*2.0;
  double  ll          = s_thick + w_thick + gap; // 1 layer length
  double  cc00_len    = ll*10 + s_thick;


  float  p_cc00[] = { cc00_width/2.0, cc00_height/2.0, cc00_len/2.0};
  double c_cc00_z = Detpos_cc00_z-cc00_len/2.0;

  // stainless pipe
  //
  double  p_len   = cc00_len;
  double  p_rmax  = 8.2/2.0;
  double  p_rmin  = 8.0/2.0;
  float p_cc0p[] = { p_rmin, p_rmax, p_len/2.0};
  

  std::vector<double> paramCC00;
  paramCC00.push_back(cc00_width*cm);
  paramCC00.push_back(cc00_height*cm);
  paramCC00.push_back(cc00_len*cm);

  paramCC00.push_back(0*cm);
  paramCC00.push_back(0*cm);
  paramCC00.push_back(p_rmin*cm);
  GsimBoxWithAHole* CC00 = new GsimBoxWithAHole("CC00",this,
						G4ThreeVector(0,0,0),
						G4ThreeVector(0,0,0));
  CC00->setOuterMaterial("GsimLowVacuum");
  CC00->setParameters(paramCC00);
  CC00->setOuterVisibility(false);
  CC00->setBriefName("CC00");
  addDaughter(CC00);
  m_detList.push_back(CC00);
  
  // scintillator -- main : upper and lower half
  std::vector<double> paramCC0SL;
  paramCC0SL.push_back(s_width*cm);
  paramCC0SL.push_back(s_height*cm);
  paramCC0SL.push_back(s_thick*cm);
  paramCC0SL.push_back(0.*cm);
  paramCC0SL.push_back(s_height/2.*cm);
  paramCC0SL.push_back(s_rmin*cm);

  std::vector<double> paramCC0SU;
  paramCC0SU.push_back(s_width*cm);
  paramCC0SU.push_back(s_height*cm);
  paramCC0SU.push_back(s_thick*cm);
  paramCC0SU.push_back(0.*cm);
  paramCC0SU.push_back(-s_height/2.*cm);
  paramCC0SU.push_back(s_rmin*cm);


  // tungsten
  std::vector<double> paramCC0W;
  paramCC0W.push_back(w_rmin*cm);
  paramCC0W.push_back(w_rmax*cm);
  paramCC0W.push_back(w_thick*cm);
  paramCC0W.push_back(0.*deg);
  paramCC0W.push_back(360.*deg);


  char nam[100];

  double zs, zw;

  GsimTube *tube=0;
  GsimBoxWithAHole* boxu=0;
  GsimBoxWithAHole* boxl=0;
  for ( int i =0; i<11; i++ ) {
    zs = -cc00_len/2.0 + (s_thick+gap)/2.0 + ll*i;
    zw = -cc00_len/2.0 + s_thick + gap + w_thick/2.0 + ll*i;

    if(i!=10) {
      if(i==0) {
	sprintf(nam,"CC0W");
	tube = new GsimTube(std::string(nam),CC00,
			    G4ThreeVector(0,0,zw*cm),
			    G4ThreeVector(0,0,0));
	tube->setOuterMaterial("G4_W");
	tube->setParameters(paramCC0W);
	tube->setOuterColor("blue");
	tube->setBriefName("CC00");
	CC00->addDaughter(tube);
	m_detList.push_back(tube);
      } else {
	tube->cloneDetector(G4ThreeVector(0,0,zw*cm),
			    G4ThreeVector(0,0,0));
      }
    }

    if(i==0) {
      sprintf(nam,"CC0SU");
      boxu = new GsimBoxWithAHole(std::string(nam),CC00,
				  G4ThreeVector(0,0,zs*cm),
				  G4ThreeVector(0,0,0));
      boxu->setParameters(paramCC0SU);
      boxu->setOuterColor("yellow");
      boxu->setSensitiveDetector("CC00",0);
      boxu->setBriefName("CC00");
      CC00->addDaughter(boxu);
    } else {
      boxu->cloneDetector(G4ThreeVector(0,0,zs*cm),
			  G4ThreeVector(0,0,0),0);
    }

    if(i==0) {
      sprintf(nam,"CC0SL");
      boxl = new GsimBoxWithAHole(std::string(nam),CC00,
				  G4ThreeVector(0,0,zs*cm),
				  G4ThreeVector(0,0,0));
      boxl->setParameters(paramCC0SL);
      boxl->setOuterColor("yellow");
      boxl->setSensitiveDetector("CC00",2);
      boxl->setBriefName("CC00");
      CC00->addDaughter(boxl);
    } else {
      boxl->cloneDetector(G4ThreeVector(0,0,zs*cm),
			  G4ThreeVector(0,0,0),2);
    }
    
  }
  // stainless pipe
  //
  std::vector<double> paramCC0P;
  paramCC0P.push_back(p_rmin*cm);
  paramCC0P.push_back(p_rmax*cm);
  paramCC0P.push_back(p_len*cm);
  paramCC0P.push_back(0.*deg);
  paramCC0P.push_back(360.*deg);

  sprintf(nam,"CC0P");
  tube = new GsimTube(std::string(nam),CC00,
		      G4ThreeVector(0,0,0),
		      G4ThreeVector(0,0,0));
  tube->setOuterMaterial("GsimSUS304");
  tube->setParameters(paramCC0P);
  tube->setOuterColor("gray50");
  tube->setBriefName("CC00");
  CC00->addDaughter(tube);
  m_detList.push_back(tube);
}


GsimE391CC00::~GsimE391CC00()
{
  ;
}

void GsimE391CC00::setFastSimulationLevel(int level)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  //reset
  if(m_fastSimulationLevel==6) {
    for(std::list<GsimDetector*>::iterator it=m_detList.begin();
	it!=m_detList.end();it++) {
      (*it)->unsetSensitiveDetector();
    }
  }

  //set
  if(level==6) {
    for(std::list<GsimDetector*>::iterator it=m_detList.begin();
	it!=m_detList.end();it++) {
      (*it)->setSensitiveDetector("CC00",0);
    }
  }

  
  {
    m_fastSimulationLevel=level;
    for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
	it!=m_daughterDetectorContainer.end();it++) {
      GsimDetector* daughter =  (*it).second;
      daughter->setFastSimulationLevel(level);
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif 
}
