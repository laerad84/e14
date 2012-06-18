/**
 *  @file
 *  @brief  GsimE14CBAR
 *  $Id: GsimE14CBAR.cc,v 1.4 2006/12/06 19:04:45 nanjo Exp $ 
 *  $Log: GsimE14CBAR.cc,v $
 *  Revision 1.4  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimE14Detector/GsimE14CBAR.h"
#include "GsimE14Detector/GsimE14UserGeom.h"
#include "GsimDetector/GsimPolyhedra2.h"
#include "GsimDetector/GsimTrap.h"
#include "GsimDetector/GsimTube.h"
#include "GsimDetector/GsimBox.h"
#include "GsimKernel/GsimSensitiveDetector.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"

using namespace E14;

GsimE14CBAR::GsimE14CBAR(std::string name,
			 GsimDetector* motherDetector,
			 G4ThreeVector transV,G4ThreeVector rotV,
			 int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{

  m_className = "GsimE14CBAR";


  int  ivol=0;

  // Central Barrel
  double  cbar_height   = 31.492 + 0.3 + 1.93;
  double  cbar_len_bot  = Cbar_Len;
  double  cbar_len_top  = Cbar_Len - 20.;
  double  cbar_bottom   = 20.05;
  double  cbar_top      = cbar_bottom + cbar_height*tan( 2*M_PI/32 );
  double  cbar_rmin     = 100.3 + 1.6;
  double  cbar_trap_th  = -atan( (cbar_top-cbar_bottom)/2/cbar_height );
  
  

  std::vector<double> paramVec;
  paramVec.push_back(cbar_height*cm);
  paramVec.push_back(cbar_trap_th*rad);
  paramVec.push_back(0*rad);
  paramVec.push_back(cbar_len_top*cm);
  paramVec.push_back(cbar_top*cm);
  paramVec.push_back(cbar_top*cm);
  paramVec.push_back(0*deg);
  paramVec.push_back(cbar_len_bot*cm);
  paramVec.push_back(cbar_bottom*cm);
  paramVec.push_back(cbar_bottom*cm);
  paramVec.push_back(0*deg);

  double  add_height = 5.188;
  double  add_len_bot  = Csic_Zmin-Fbar_Len;
  double  add_len_top  = add_len_bot;
  double  add_bottom   = cbar_top;
  double  add_top      = add_bottom + add_height*tan( 2*M_PI/32 );
  double  add_rmin     = 100.3 + 1.6;
  double  add_trap_th  = -atan( (add_top-add_bottom)/2/add_height );

  std::vector<double> paramAddVec;
  paramAddVec.push_back(add_height*cm);
  paramAddVec.push_back(add_trap_th*rad);
  paramAddVec.push_back(0*rad);
  paramAddVec.push_back(add_len_top*cm);
  paramAddVec.push_back(add_top*cm);
  paramAddVec.push_back(add_top*cm);
  paramAddVec.push_back(0*deg);
  paramAddVec.push_back(add_len_bot*cm);
  paramAddVec.push_back(add_bottom*cm);
  paramAddVec.push_back(add_bottom*cm);
  paramAddVec.push_back(0*deg);

  GsimTrap* trapCBAR=0;
  GsimTrap* trapCBARadd=0;
  char nam[100];
  
  for( int i=0;i<32;i++ ){
    double  x = cbar_rmin + cbar_height/2;
    double  y = cbar_bottom/2 - (cbar_top+cbar_bottom)/4;
    //double  z = 135 + cbar_len_bot/2;
    double  z = Detpos_cbar_z + cbar_len_bot/2;

    double  xadd = cbar_rmin + cbar_height + add_height/2.;
    double  yadd = y
      -(add_top+add_bottom)/4+(cbar_top+cbar_bottom)/4;
    
    double  zadd = Fbar_Len+add_len_bot/2.;

    
    CLHEP::Hep3Vector c( x,y,z );
    c.rotateZ( 2*M_PI*i/32 );

    CLHEP::Hep3Vector cadd( xadd,yadd,zadd );
    cadd.rotateZ( 2*M_PI*i/32 );

    
    if(i==0) {
      std::sprintf(nam,"CBAR");
      trapCBAR = new GsimTrap(std::string(nam),this,
			      G4ThreeVector(c.x()*cm,c.y()*cm,0),
			      G4ThreeVector(M_PI/2.,0,1.*((24+i)%32)/32.*2.*M_PI)
			      );
      trapCBAR->setOuterMaterial("G4_Galactic");
      trapCBAR->setParameters(paramVec);
      trapCBAR->setOuterVisibility(false);
      addDaughter(trapCBAR);
      m_detList.push_back(trapCBAR);

      std::sprintf(nam,"CBARadd");
      trapCBARadd = new GsimTrap(std::string(nam),this,
				 G4ThreeVector(cadd.x()*cm,cadd.y()*cm,
					       (zadd-z)*cm),
				 G4ThreeVector(M_PI/2.,0,1.*((24+i)%32)/32.*2.*M_PI)
				 );
      trapCBARadd->setOuterMaterial("G4_Galactic");
      trapCBARadd->setParameters(paramAddVec);
      trapCBARadd->setOuterVisibility(false);
      addDaughter(trapCBARadd);
      m_detList.push_back(trapCBARadd);


      
    } else {
      trapCBAR->cloneDetector(G4ThreeVector(c.x()*cm,c.y()*cm,0),
      G4ThreeVector(M_PI/2.,0,1.*((24+i)%32)/32.*2.*M_PI),i);
      trapCBARadd->cloneDetector(G4ThreeVector(cadd.x()*cm,cadd.y()*cm,(zadd-z)*cm),
      G4ThreeVector(M_PI/2.,0,1.*((24+i)%32)/32.*2.*M_PI),i);
    }
  }




  // SUS plate
  double  cbsu_height   = 0.3;
  double  cbsu_len_bot  = cbar_len_bot;
  double  cbsu_len_top  = cbsu_len_bot + (cbar_len_top - cbar_len_bot) * 
    (cbsu_height / cbar_height);
  double  cbsu_bottom   = cbar_bottom;
  double  cbsu_top      = cbsu_bottom + cbsu_height*tan( 2*M_PI/32 );
  double  cbsu_trap_th  = -atan( (cbsu_top-cbsu_bottom)/2/cbsu_height );
  


  paramVec.clear();
  paramVec.push_back(cbsu_height*cm);
  paramVec.push_back(cbsu_trap_th*rad);
  paramVec.push_back(0*rad);
  paramVec.push_back(cbsu_len_top*cm);
  paramVec.push_back(cbsu_top*cm);
  paramVec.push_back(cbsu_top*cm);
  paramVec.push_back(0*deg);
  paramVec.push_back(cbsu_len_bot*cm);
  paramVec.push_back(cbsu_bottom*cm);
  paramVec.push_back(cbsu_bottom*cm);
  paramVec.push_back(0*deg);

  double  cbsu_x = (cbsu_bottom+cbsu_top)/4 - (cbar_top+cbar_bottom)/4;
  double  cbsu_y = 0;
  double  cbsu_z = cbar_height/2 - cbsu_height/2;

  GsimTrap* trap=0;
  std::sprintf(nam,"CBSU");
  trap = new GsimTrap(std::string(nam),trapCBAR,
		      G4ThreeVector(cbsu_x*cm,cbsu_y*cm,cbsu_z*cm),
		      G4ThreeVector(0,0,0)
		      );
  trap->setOuterMaterial("G4_Fe");
  trap->setParameters(paramVec);
  trap->setOuterColor("gray70");
  trapCBAR->addDaughter(trap);
  m_detList.push_back(trap);
  
  // Back bone
  double  cbbb_height   = 1.93;
  double  cbbb_len_bot  = cbar_len_top;
  double  cbbb_len_top  = cbbb_len_bot;
  double  cbbb_top      = cbar_top;
  double  cbbb_bottom   = cbbb_top - cbbb_height*tan( 2*M_PI/32 );
  double  cbbb_trap_th  = -atan( (cbbb_top-cbbb_bottom)/2/cbbb_height );
  


  paramVec.clear();
  paramVec.push_back(cbbb_height*cm);
  paramVec.push_back(cbbb_trap_th*rad);
  paramVec.push_back(0*rad);
  paramVec.push_back(cbbb_len_top*cm);
  paramVec.push_back(cbbb_top*cm);
  paramVec.push_back(cbbb_top*cm);
  paramVec.push_back(0*deg);
  paramVec.push_back(cbbb_len_bot*cm);
  paramVec.push_back(cbbb_bottom*cm);
  paramVec.push_back(cbbb_bottom*cm);
  paramVec.push_back(0*deg);

  
  double  cbbb_x = (cbbb_bottom+cbbb_top)/4 - (cbar_top+cbar_bottom)/4;
  double  cbbb_y = 0;
  double  cbbb_z = -cbar_height/2 + cbbb_height/2;

  std::sprintf(nam,"CBBB");
  trap = new GsimTrap(std::string(nam),trapCBAR,
		      G4ThreeVector(cbbb_x*cm,cbbb_y*cm,cbbb_z*cm),
		      G4ThreeVector(0,0,0)
		      );
  trap->setOuterMaterial("G4_Fe");
  trap->setParameters(paramVec);
  trap->setOuterColor("gray70");
  trapCBAR->addDaughter(trap);
  m_detList.push_back(trap);
  
  // Layer structure
  {
    double  cbar_lead1_thick = 0.1;
    double  cbar_lead2_thick = 0.2;
    int     cbar_nlead1      = 15;
    int     cbar_nlead2      = 29;
    double  cbar_sci_thick   = 0.5;
    double  cbar_sci_sheet   = 0.0188;
    
    // Scintillator
    for( int i=0;i<45;i++ ){
      double  cbsc_height   = cbar_sci_thick + cbar_sci_sheet*2;
      double  cbsc_hpos     = cbsu_height + cbsc_height*i + cbar_sci_sheet
        + cbar_lead1_thick * ( (i<cbar_nlead1) ? i : 15 )
        + cbar_lead2_thick * ( (i>cbar_nlead1) ? (i - cbar_nlead1) : 0 );
      double  cbsc_len_bot  = cbar_len_bot 
        + (cbar_len_top - cbar_len_bot) * (cbsc_hpos / cbar_height);
      double  cbsc_len_top  = cbsc_len_bot 
        + (cbar_len_top - cbar_len_bot) * (cbar_sci_thick / cbar_height);
      double  cbsc_bottom   = cbar_bottom + cbsc_hpos  *tan( 2*M_PI/32 );
      double  cbsc_top      = cbsc_bottom + cbar_sci_thick*tan( 2*M_PI/32 );
      double  cbsc_trap_th  = -atan( (cbsc_top-cbsc_bottom)/2/cbar_sci_thick );
      
      paramVec.clear();
      paramVec.push_back(cbar_sci_thick*cm);
      paramVec.push_back(cbsc_trap_th*rad);
      paramVec.push_back(0*rad);
      paramVec.push_back(cbsc_len_top*cm);
      paramVec.push_back(cbsc_top*cm);
      paramVec.push_back(cbsc_top*cm);
      paramVec.push_back(0*deg);
      paramVec.push_back(cbsc_len_bot*cm);
      paramVec.push_back(cbsc_bottom*cm);
      paramVec.push_back(cbsc_bottom*cm);
      paramVec.push_back(0*deg);

      
      double  cbsc_x = (cbsc_bottom+cbsc_top)/4 - (cbar_top+cbar_bottom)/4;
      double  cbsc_y = 0;
      double  cbsc_z = cbar_height/2 - cbsc_hpos - cbar_sci_thick/2;

      
      std::sprintf(nam,"CBSC%02d",i);
      trap = new GsimTrap(std::string(nam),trapCBAR,
			  G4ThreeVector(cbsc_x*cm,cbsc_y*cm,cbsc_z*cm),
			  G4ThreeVector(0,0,0)
			  );
      trap->setParameters(paramVec);
      trap->setOuterColor("yellow");
      if(i<15) {
	trap->setSensitiveDetector("CBAR",0);
      } else {
	trap->setSensitiveDetector("CBAR",1);
      }
      trapCBAR->addDaughter(trap);
    }
    // LEAD plate
    for( int i=0;i<44;i++ ){
      double  cbld_hschinti = (cbar_sci_thick + cbar_sci_sheet*2);
      double  cbld_height   = (i<cbar_nlead1) ? 
        cbar_lead1_thick : cbar_lead2_thick;
      double  cbld_hpos     = cbsu_height + cbld_hschinti*(i+1)
        + cbar_lead1_thick * ( (i<cbar_nlead1) ? i : 15 )
        + cbar_lead2_thick * ( (i>cbar_nlead1) ? (i - cbar_nlead1) : 0 );
      double  cbld_len_bot  = cbar_len_bot 
        + (cbar_len_top - cbar_len_bot) * (cbld_hpos / cbar_height);
      double  cbld_bottom   = cbar_bottom + cbld_hpos*tan( 2*M_PI/32 );
      float  p_cbld[] = { cbld_bottom/2, cbld_len_bot/2, cbld_height/2 };

      paramVec.clear();
      paramVec.push_back(cbld_bottom*cm);
      paramVec.push_back(cbld_len_bot*cm);
      paramVec.push_back(cbld_height*cm);
      
      double  cbld_x = cbld_bottom/2 - (cbar_top+cbar_bottom)/4;
      double  cbld_y = 0;
      double  cbld_z = cbar_height/2 - cbld_hpos - cbld_height/2;

      std::sprintf(nam,"CBLD%02d",i);
      GsimBox *box = new GsimBox(std::string(nam),trapCBAR,
				 G4ThreeVector(cbld_x*cm,cbld_y*cm,cbld_z*cm),
				 G4ThreeVector(0,0,0)
				 );
      box->setOuterMaterial("G4_Pb");
      box->setParameters(paramVec);
      box->setOuterColor("gray50");
      trapCBAR->addDaughter(box);
      m_detList.push_back(box);
    }
  }

  {
    double  cbar_lead3_thick = 0.5;
    int     cbar_nlead3      = 5;
    double  cbar_sci_thick   = 0.5;
    double  cbar_sci_sheet   = 0.0188;
    
    // Scintillator
    for( int i=0;i<5;i++ ){
      double  cbsc_height   = cbar_sci_thick + cbar_sci_sheet*2;
      double  cbsc_hpos     = cbsc_height*i + cbar_sci_sheet
        + cbar_lead3_thick * i;
      
      double  cbsc_len_bot  = add_len_bot 
        + (add_len_top - add_len_bot) * (cbsc_hpos / add_height);
      double  cbsc_len_top  = cbsc_len_bot 
        + (add_len_top - add_len_bot) * (cbar_sci_thick / add_height);
      double  cbsc_bottom   = add_bottom + cbsc_hpos  *tan( 2*M_PI/32 );
      double  cbsc_top      = cbsc_bottom + cbar_sci_thick*tan( 2*M_PI/32 );
      double  cbsc_trap_th  = -atan( (cbsc_top-cbsc_bottom)/2/cbar_sci_thick );
      
      paramVec.clear();
      paramVec.push_back(cbar_sci_thick*cm);
      paramVec.push_back(cbsc_trap_th*rad);
      paramVec.push_back(0*rad);
      paramVec.push_back(cbsc_len_top*cm);
      paramVec.push_back(cbsc_top*cm);
      paramVec.push_back(cbsc_top*cm);
      paramVec.push_back(0*deg);
      paramVec.push_back(cbsc_len_bot*cm);
      paramVec.push_back(cbsc_bottom*cm);
      paramVec.push_back(cbsc_bottom*cm);
      paramVec.push_back(0*deg);

      
      double  cbsc_x = (cbsc_bottom+cbsc_top)/4 - (add_top+add_bottom)/4;
      double  cbsc_y = 0;
      double  cbsc_z = add_height/2 - cbsc_hpos - cbar_sci_thick/2;

      
      std::sprintf(nam,"CBSCADD%02d",i);
      trap = new GsimTrap(std::string(nam),trapCBARadd,
			  G4ThreeVector(cbsc_x*cm,cbsc_y*cm,cbsc_z*cm),
			  G4ThreeVector(0,0,0)
			  );
      trap->setParameters(paramVec);
      trap->setOuterColor("yellow");
      trap->setSensitiveDetector("CBAR",2);
      trapCBARadd->addDaughter(trap);
    }
    // LEAD plate
    for( int i=0;i<5;i++ ){
      double  cbld_hschinti = (cbar_sci_thick + cbar_sci_sheet*2);
      double  cbld_height   = cbar_lead3_thick;
      double  cbld_hpos     = cbld_hschinti*(i+1)
        + cbar_lead3_thick * i;
      double  cbld_len_bot  = add_len_bot 
        + (add_len_top - add_len_bot) * (cbld_hpos / add_height);
      double  cbld_bottom   = add_bottom + cbld_hpos*tan( 2*M_PI/32 );
      float  p_cbld[] = { cbld_bottom/2, cbld_len_bot/2, cbld_height/2 };

      paramVec.clear();
      paramVec.push_back(cbld_bottom*cm);
      paramVec.push_back(cbld_len_bot*cm);
      paramVec.push_back(cbld_height*cm);
      
      double  cbld_x = cbld_bottom/2 - (add_top+add_bottom)/4;
      double  cbld_y = 0;
      double  cbld_z = add_height/2 - cbld_hpos - cbld_height/2;

      std::sprintf(nam,"CBLDADD%02d",i);
      GsimBox *box = new GsimBox(std::string(nam),trapCBARadd,
				 G4ThreeVector(cbld_x*cm,cbld_y*cm,cbld_z*cm),
				 G4ThreeVector(0,0,0)
				 );
      box->setOuterMaterial("G4_Pb");
      box->setParameters(paramVec);
      box->setOuterColor("gray50");
      trapCBARadd->addDaughter(box);
      m_detList.push_back(box);
    }
  }
  GsimSensitiveDetector* sd =
    dynamic_cast<GsimSensitiveDetector*>(GsimUtil::getUtil()->getSensitiveDetector("CBAR"));
  sd->setThisCopyNoFactor(32);
  
  setThisAndDaughterBriefName("CBAR");
}

void GsimE14CBAR::setFastSimulationLevel(int level)
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
    dynamic_cast<GsimSensitiveDetector*>(GsimUtil::getUtil()->getSensitiveDetector("CBAR"));
    sd->setThisCopyNoFactor(32);
  }

  //set
  if(level==6) {
    for(std::list<GsimDetector*>::iterator it=m_detList.begin();
	it!=m_detList.end();it++) {
      (*it)->setSensitiveDetector("CBAR",0);
    }
    GsimSensitiveDetector* sd =
    dynamic_cast<GsimSensitiveDetector*>(GsimUtil::getUtil()->getSensitiveDetector("CBAR"));
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



GsimE14CBAR::~GsimE14CBAR()
{
  ;
}

