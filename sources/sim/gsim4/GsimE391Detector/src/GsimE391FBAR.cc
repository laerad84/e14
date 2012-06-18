/**
 *  @file
 *  @brief  GsimE391FBAR
 *  $Id: GsimE391FBAR.cc,v 1.9 2006/12/06 18:58:52 nanjo Exp $ 
 *  $Log: GsimE391FBAR.cc,v $
 *  Revision 1.9  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimE391Detector/GsimE391FBAR.h"
#include "GsimE391Detector/GsimUserGeom.h"
#include "GsimDetector/GsimPolyhedra2.h"
#include "GsimDetector/GsimTrap.h"
#include "GsimDetector/GsimTube.h"
#include "GsimDetector/GsimBox.h"
#include "GsimKernel/GsimSensitiveDetector.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"

using namespace E391;

GsimE391FBAR::GsimE391FBAR(std::string name,
			   GsimDetector* motherDetector,
			   G4ThreeVector transV,G4ThreeVector rotV,
			   int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{

  m_className = "GsimE391FBAR";

  int  ivol=0;

  // Front Barrel
  double  fbar_height = 41.3084;
  double  fbar_len    = Fbar_Len;
  double  fbar_rmin   = Fbar_Rmin;
  double  fba1_height = 37.8204;
  double  fba1_bottom = 12.16;
  double  fba1_top    = fba1_bottom + fba1_height*tan( M_PI/8 );
  double  fba1_alpha  = -atan( (fba1_top-fba1_bottom)/2/fba1_height );

  std::vector<double> paramVec;
  paramVec.push_back(fbar_len*cm);
  paramVec.push_back(0*rad);
  paramVec.push_back(0*rad);
  paramVec.push_back(fba1_height*cm);
  paramVec.push_back(fba1_bottom*cm);
  paramVec.push_back(fba1_top*cm);
  paramVec.push_back(fba1_alpha*rad);
  paramVec.push_back(fba1_height*cm);
  paramVec.push_back(fba1_bottom*cm);
  paramVec.push_back(fba1_top*cm);
  paramVec.push_back(fba1_alpha*rad);

  
  char nam[100];
  
  GsimTrap* trapFBA1=0;
  std::sprintf(nam,"FBA1");
  
  for( int i=0;i<16;i++ ){
    double  x = fbar_rmin + fba1_height/2;
    double  y = -fba1_bottom/2 + (fba1_top+fba1_bottom)/4;
    double  z = fbar_len/2;
    CLHEP::Hep3Vector c( x,y,z );
    c.rotateZ( 2*M_PI*i/16 );
    int  rotm = grot_z_32+(24+i*2)%32;


    if(i==0) {
      trapFBA1 = new GsimTrap(std::string(nam),this,
			      G4ThreeVector(c.x()*cm,c.y()*cm,0),
			      G4ThreeVector(0.,0,1.*((24+i*2)%32)/32.*2.*M_PI)
			      );
      trapFBA1->setOuterMaterial("GsimLowVacuum");
      trapFBA1->setParameters(paramVec);
      trapFBA1->setOuterVisibility(false);
      trapFBA1->setBriefName("FBAR");
      addDaughter(trapFBA1);
      m_detList.push_back(trapFBA1);
    } else {
      trapFBA1->cloneDetector(G4ThreeVector(c.x()*cm,c.y()*cm,0),
			      G4ThreeVector(0.,0,1.*((24+i*2)%32)/32.*2.*M_PI),i);
			      
    }
  }

  double  fba2_height = fbar_height - fba1_height;
  double  fba2_bottom = fba1_top;
  double  fba2_top    = 14.05;
  double  fba2_alpha  = -atan( (fba2_top-fba2_bottom)/2/fba2_height );

  paramVec.clear();
  paramVec.push_back(fbar_len*cm);
  paramVec.push_back(0*rad);
  paramVec.push_back(0*rad);
  paramVec.push_back(fba2_height*cm);
  paramVec.push_back(fba2_bottom*cm);
  paramVec.push_back(fba2_top*cm);
  paramVec.push_back(fba2_alpha*rad);
  paramVec.push_back(fba2_height*cm);
  paramVec.push_back(fba2_bottom*cm);
  paramVec.push_back(fba2_top*cm);
  paramVec.push_back(fba2_alpha*rad);

  GsimTrap* trapFBA2=0;
  std::sprintf(nam,"FBA2");
  
  for( int i=0;i<16;i++ ){
    double  x = fbar_rmin + fbar_height - fba2_height/2;
    double  y = -fba1_bottom/2 + (fba2_top+fba2_bottom)/4;
    double  z = fbar_len/2;
    CLHEP::Hep3Vector c( x,y,z );
    c.rotateZ( 2*M_PI*i/16 );
    int  rotm = grot_z_32+(24+i*2)%32;

    if(i==0) {
      trapFBA2 = new GsimTrap(std::string(nam),this,
			      G4ThreeVector(c.x()*cm,c.y()*cm,0),
			      G4ThreeVector(0.,0,1.*((24+i*2)%32)/32.*2.*M_PI)
			      );
      trapFBA2->setOuterMaterial("GsimLowVacuum");
      trapFBA2->setParameters(paramVec);
      trapFBA2->setOuterVisibility(false);
      trapFBA2->setBriefName("FBAR");
      addDaughter(trapFBA2);
      m_detList.push_back(trapFBA2);
    } else {
      trapFBA2->cloneDetector(G4ThreeVector(c.x()*cm,c.y()*cm,0),
			      G4ThreeVector(0.,0,1.*((24+i*2)%32)/32.*2.*M_PI),i);
			      
    }
  }


  // SUS plate
  double  fbsu_height   = 0.3;
  double  fbsu_len      = fbar_len;
  double  fbsu_bottom   = fba1_bottom;
  double  fbsu_top      = fbsu_bottom + fbsu_height*tan( 2*M_PI/16 );
  double  fbsu_alpha    = -atan( (fbsu_top-fbsu_bottom)/2/fbsu_height );
  
  paramVec.clear();
  paramVec.push_back(fbsu_len*cm);
  paramVec.push_back(0*rad);
  paramVec.push_back(0*rad);
  paramVec.push_back(fbsu_height*cm);
  paramVec.push_back(fbsu_bottom*cm);
  paramVec.push_back(fbsu_top*cm);
  paramVec.push_back(fbsu_alpha*rad);
  paramVec.push_back(fbsu_height*cm);
  paramVec.push_back(fbsu_bottom*cm);
  paramVec.push_back(fbsu_top*cm);
  paramVec.push_back(fbsu_alpha*rad);

  double  fbsu_x = (fba1_top+fba1_bottom)/4 -(fbsu_bottom+fbsu_top)/4;
  double  fbsu_y = -fba1_height/2 + fbsu_height/2;
  double  fbsu_z = 0;
  GsimTrap* trap=0;
  std::sprintf(nam,"FBSU");
  trap = new GsimTrap(std::string(nam),trapFBA1,
		      G4ThreeVector(fbsu_x*cm,fbsu_y*cm,fbsu_z*cm),
		      G4ThreeVector(0,0,0)
		      );
  trap->setOuterMaterial("G4_Fe");
  trap->setParameters(paramVec);
  trap->setOuterColor("gray70");
  trap->setBriefName("FBAR");
  trapFBA1->addDaughter(trap);
  m_detList.push_back(trap);
  
  // Front Barrel Backbone
  double  fbbb_rmin = fbar_rmin + 41.4; // > fbar_rmin + fbar_height
  double  fbbb_rmax = fbbb_rmin + 2.2;
  float  p_fbbb[] = { -360./16/2, 360, 16, 2,
                      -fbar_len/2, fbbb_rmin, fbbb_rmax,
                      +fbar_len/2, fbbb_rmin, fbbb_rmax };

  paramVec.clear();
  paramVec.push_back(( -360./16./2.)*deg);
  paramVec.push_back(360*deg);
  paramVec.push_back(16);
  paramVec.push_back(fbar_len*cm);
  paramVec.push_back(fbbb_rmin*cm);
  paramVec.push_back(fbbb_rmax*cm);

  
  double c_fbbb_z = fbar_len/2;
  sprintf(nam,"FBBB");
  GsimPolyhedra2* hedra = new GsimPolyhedra2(std::string(nam),this,
					     G4ThreeVector(0,0,(c_fbbb_z-fbar_len/2)*cm),
					     G4ThreeVector(0,0,0));
  hedra->setOuterMaterial("G4_Fe");
  hedra->setParameters(paramVec);
  hedra->setBriefName("FBAR");
  addDaughter(hedra);
  m_detList.push_back(hedra);
  

  

  // Layer structure

  double  fbar_lead_thick = 0.15;
  double  fbar_sci_thick  = 0.5;
  double  fbar_sci_sheet  = 0.0188 + 0.005;
    
  // Scintillator
  for( int i=0;i<54;i++ ){
    double  fbsc_height  = fbar_sci_thick + fbar_sci_sheet*2;
    double  fbsc_hpos    = fbsu_height + fbsc_height*i + fbar_sci_sheet
      + fbar_lead_thick*i;
    double  fbsc_len     = fbar_len; 
    double  fbsc_bottom  = fba1_bottom + fbsc_hpos*tan( 2*M_PI/16 );
    double  fbsc_top     = fbsc_bottom + fbar_sci_thick*tan( 2*M_PI/16 );
    double  fbsc_alpha   = -atan( (fbsc_top-fbsc_bottom)/2/fbar_sci_thick );


    paramVec.clear();
    paramVec.push_back(fbsc_len*cm);
    paramVec.push_back(0*rad);
    paramVec.push_back(0*rad);
    paramVec.push_back(fbar_sci_thick*cm);
    paramVec.push_back(fbsc_bottom*cm);
    paramVec.push_back(fbsc_top*cm);
    paramVec.push_back(fbsc_alpha*rad);
    paramVec.push_back(fbar_sci_thick*cm);
    paramVec.push_back(fbsc_bottom*cm);
    paramVec.push_back(fbsc_top*cm);
    paramVec.push_back(fbsc_alpha*rad);

    double  fbsc_x = (fba1_top+fba1_bottom)/4 - (fbsc_bottom+fbsc_top)/4;
    double  fbsc_y = -fba1_height/2 + fbsc_hpos + fbar_sci_thick/2;
    double  fbsc_z = 0;

    std::sprintf(nam,"FBSC1%02d",i);
    trap = new GsimTrap(std::string(nam),trapFBA1,
			G4ThreeVector(fbsc_x*cm,fbsc_y*cm,fbsc_z*cm),
			G4ThreeVector(0,0,0)
			);
    trap->setParameters(paramVec);
    trap->setOuterColor("yellow");
    trap->setBriefName("FBAR");
    if(i<27) {
      trap->setSensitiveDetector("FBAR",0);
    } else {
      trap->setSensitiveDetector("FBAR",1);
    }
    trapFBA1->addDaughter(trap);
  }
  for( int i=0;i<5;i++ ){
    double  fbsc_height  = fbar_sci_thick + fbar_sci_sheet*2;
    double  fbsc_hpos    = fbsc_height*i + fbar_sci_sheet
      + fbar_lead_thick*i;
    double  fbsc_len     = fbar_len; 
    double  fbsc_top     = fba2_top
      + (fba2_bottom-fba2_top)*(fbsc_hpos/fba2_height);
    double  fbsc_bottom  = fbsc_top + fbar_sci_thick*tan( 2*M_PI/16 );
    double  fbsc_alpha   = atan( -(fbsc_top-fbsc_bottom)/2/fbar_sci_thick );

    paramVec.clear();
    paramVec.push_back(fbsc_len*cm);
    paramVec.push_back(0*rad);
    paramVec.push_back(0*rad);
    paramVec.push_back(fbar_sci_thick*cm);
    paramVec.push_back(fbsc_bottom*cm);
    paramVec.push_back(fbsc_top*cm);
    paramVec.push_back(fbsc_alpha*rad);
    paramVec.push_back(fbar_sci_thick*cm);
    paramVec.push_back(fbsc_bottom*cm);
    paramVec.push_back(fbsc_top*cm);
    paramVec.push_back(fbsc_alpha*rad);
    
    double  fbsc_x = (fba2_top+fba2_bottom)/4 - (fbsc_bottom+fbsc_top)/4;
    double  fbsc_y = fba2_height/2 - fbsc_hpos - fbar_sci_thick/2;
    double  fbsc_z = 0;

    std::sprintf(nam,"FBSC2%02d",i);
    trap = new GsimTrap(std::string(nam),trapFBA2,
			G4ThreeVector(fbsc_x*cm,fbsc_y*cm,fbsc_z*cm),
			G4ThreeVector(0,0,0)
			);
    trap->setParameters(paramVec);
    trap->setOuterColor("orange");
    trap->setBriefName("FBAR");
    trap->setSensitiveDetector("FBAR",1);
    trapFBA2->addDaughter(trap);
  }


  // LEAD plate
  for( int i=1;i<54;i++ ){
    double  fbld_hschinti = (fbar_sci_thick + fbar_sci_sheet*2);
    double  fbld_height   = fbar_lead_thick;
    double  fbld_hpos     = fbsu_height + fbld_hschinti*i
      + fbar_lead_thick*(i-1);
    double  fbld_len      = fbar_len;
    double  fbld_bottom   = fba1_bottom
      + (fba1_top-fba1_bottom)*(fbld_hpos/fba1_height);
    float  p_fbld[] = { fbld_bottom/2, fbld_height/2, fbld_len/2 };

    paramVec.clear();
    paramVec.push_back(fbld_bottom*cm);
    paramVec.push_back(fbld_height*cm);
    paramVec.push_back(fbld_len*cm);
      
    double  fbld_x = (fba1_top+fba1_bottom)/4 - fbld_bottom/2;
    double  fbld_y = -fba1_height/2 + fbld_hpos + fbld_height/2;
    double  fbld_z = 0;

    std::sprintf(nam,"FBLD1%02d",i);
    GsimBox *box = new GsimBox(std::string(nam),trapFBA1,
			       G4ThreeVector(fbld_x*cm,fbld_y*cm,fbld_z*cm),
			       G4ThreeVector(0,0,0)
			       );
    box->setOuterMaterial("G4_Pb");
    box->setParameters(paramVec);
    box->setOuterColor("gray50");
    box->setBriefName("FBAR");
    trapFBA1->addDaughter(box);
    m_detList.push_back(box);
  }
  
  for( int i=0;i<5;i++ ){
    double  fbld_hschinti = (fbar_sci_thick + fbar_sci_sheet*2);
    double  fbld_height   = fbar_lead_thick;
    double  fbld_hpos     = fbld_hschinti*(i+1) + fbar_lead_thick*i;
    double  fbld_len      = fbar_len;
    double  fbld_bottom   = fba2_top
      + (fba2_bottom-fba2_top)*(fbld_hpos/fba2_height);
    float  p_fbld[] = { fbld_bottom/2, fbld_height/2, fbld_len/2 };
    paramVec.clear();
    paramVec.push_back(fbld_bottom*cm);
    paramVec.push_back(fbld_height*cm);
    paramVec.push_back(fbld_len*cm);
    
    double  fbld_x = (fba2_top+fba2_bottom)/4 - fbld_bottom/2;
    double  fbld_y = fba2_height/2 - fbld_hpos - fbld_height/2;
    double  fbld_z = 0;

    std::sprintf(nam,"FBLD2%02d",i);
    GsimBox *box = new GsimBox(std::string(nam),trapFBA2,
			       G4ThreeVector(fbld_x*cm,fbld_y*cm,fbld_z*cm),
			       G4ThreeVector(0,0,0)
			       );
    box->setOuterMaterial("G4_Pb");
    box->setParameters(paramVec);
    box->setOuterColor("gray50");
    box->setBriefName("FBAR");
    trapFBA2->addDaughter(box);
    m_detList.push_back(box);
  }
  GsimSensitiveDetector* sd =
    dynamic_cast<GsimSensitiveDetector*>(GsimUtil::getUtil()->getSensitiveDetector("FBAR"));
  sd->setThisCopyNoFactor(16);
}


GsimE391FBAR::~GsimE391FBAR()
{
  ;
}


void GsimE391FBAR::setFastSimulationLevel(int level)
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
    GsimSensitiveDetector* sd =
      dynamic_cast<GsimSensitiveDetector*>(GsimUtil::getUtil()->getSensitiveDetector("FBAR"));
    sd->setThisCopyNoFactor(16);
  }

  //set
  if(level==6) {
    for(std::list<GsimDetector*>::iterator it=m_detList.begin();
	it!=m_detList.end();it++) {
      (*it)->setSensitiveDetector("FBAR",0);
    }
    GsimSensitiveDetector* sd =
      dynamic_cast<GsimSensitiveDetector*>(GsimUtil::getUtil()->getSensitiveDetector("FBAR"));
    sd->setThisCopyNoFactor(-1);
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

