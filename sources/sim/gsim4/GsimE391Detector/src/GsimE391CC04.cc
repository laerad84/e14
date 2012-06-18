/**
 *  @file
 *  @brief  GsimE391CC04
 *  $Id: GsimE391CC04.cc,v 1.7 2007/02/04 12:56:46 nanjo Exp $ 
 *  $Log: GsimE391CC04.cc,v $
 *  Revision 1.7  2007/02/04 12:56:46  nanjo
 *  GsimBoxWithAHole is used.
 *
 *  Revision 1.6  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimE391Detector/GsimE391CC04.h"
#include "GsimE391Detector/GsimUserGeom.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimDetector/GsimPolyhedra2.h"
#include "GsimDetector/GsimTrap.h"
#include "GsimDetector/GsimTube.h"
#include "GsimDetector/GsimBox.h"

using namespace E391;

GsimE391CC04::GsimE391CC04(std::string name,
			   GsimDetector* motherDetector,
			   G4ThreeVector transV,G4ThreeVector rotV,
			   int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{
  
  m_className = "GsimE391CC04";

  int  ivol=0;
  
  int n_vacuum = 16; // Vacuum
  int n_cc4_sci = 99; // cc04 parameters
  int n_cc4_lead = 13;
  int n_steel = 10; // iron

  int cc04_nsci1 = 32;
  int cc04_nsci2 = 2;
  int cc04_nlead = 32; // must = cc04_nsci1

  double gap = 0.025*cm;

  double cc04_sci_len = 31.3*cm;
  double cc04_sci_wdt = 18.7*cm;
  double cc04_sci_thk = 0.5*cm;

  double cc04_lead_out = 50.*cm;
  double cc04_lead_in = 12.6*cm;
  double cc04_lead_thk = 0.2*cm;

  double cc04_xyo = 50.*cm;
  double cc04_xyi = 12.6*cm;

  double cc04_len =
    ((double)(cc04_nsci1+cc04_nsci2))*cc04_sci_thk
    + ((double)(cc04_nlead))*cc04_lead_thk
    + ((double)(2*cc04_nlead+cc04_nsci2-1))*gap;

  {
    double wid_frame = 3.*cm;
    double thk_frame = .8*cm;
    double len_frame = 54.0*cm;

    std::vector<double> paramVec;
    paramVec.push_back(-45.*deg);
    paramVec.push_back(360*deg);
    paramVec.push_back(4);
    paramVec.push_back(cc04_len+(thk_frame+wid_frame)*2.);
    paramVec.push_back(cc04_xyi/2.);
    paramVec.push_back((cc04_xyo+(len_frame-cc04_xyo))/2.);
    
    
    

    

    double csir_zmin = 609.8*cm; // See GsimUserGeom.h
    double csic_zmin = 614.8*cm; // See GsimUserGeom.h
    double csir_len = 180*cm; // See GsimUserGeom.h
    double dist_cc04 = 95.5*cm; // See GsimUserGeom.h

    double c_cc04_z = -csir_len/2.
      + (csic_zmin-csir_zmin)
      + dist_cc04
      + (cc04_len+(thk_frame+wid_frame)*2.)/2.;

    char nam[100];
    std::sprintf(nam,"CC04");
    GsimPolyhedra2* cc04 = new GsimPolyhedra2(std::string(nam),this,
					      G4ThreeVector(0,0,0),
					      G4ThreeVector(0,0,0));
    cc04->setOuterMaterial("GsimLowVacuum");
    cc04->setParameters(paramVec);
    cc04->setOuterVisibility(false);
    cc04->setBriefName(nam);
    addDaughter(cc04);
    m_detList.push_back(cc04);

    //new G4PVPlacement(0,G4ThreeVector(0,0,c_cc04_z),cc04_log,"CC04",csi_log,false,1);

    // sci sheets for different PMTs

    std::vector<double> paramC4S;
    paramC4S.push_back(cc04_sci_len);
    paramC4S.push_back(cc04_sci_wdt);
    paramC4S.push_back(cc04_sci_thk);

    // G4Box *c4s0_box = new G4Box("C4S0",cc04_sci_len/2.,cc04_sci_wdt/2.,cc04_sci_thk/2.);
    //     G4LogicalVolume *c4s0_log = new G4LogicalVolume(c4s0_box,Scintillator,"C4S0",0,0,0);
    //     c4s0_log->SetVisAttributes(cc04_att);

    
    // G4Box *c4s1_box = new G4Box("C4S1",cc04_sci_len/2.,cc04_sci_wdt/2.,cc04_sci_thk/2.);
    //     G4LogicalVolume *c4s1_log = new G4LogicalVolume(c4s1_box,Scintillator,"C4S1",0,0,0);
    //     c4s1_log->SetVisAttributes(cc04_att);
    //     G4Box *c4s2_box = new G4Box("C4S2",cc04_sci_len/2.,cc04_sci_wdt/2.,cc04_sci_thk/2.);
    //     G4LogicalVolume *c4s2_log = new G4LogicalVolume(c4s2_box,Scintillator,"C4S2",0,0,0);
    //     c4s2_log->SetVisAttributes(cc04_att);
    //     G4Box *c4s3_box = new G4Box("C4S3",cc04_sci_len/2.,cc04_sci_wdt/2.,cc04_sci_thk/2.);
    //     G4LogicalVolume *c4s3_log = new G4LogicalVolume(c4s3_box,Scintillator,"C4S3",0,0,0);
    //     c4s3_log->SetVisAttributes(cc04_att);

    // frame
    std::vector<double> paramC4F1;
    paramC4F1.push_back(thk_frame);
    paramC4F1.push_back(wid_frame);
    paramC4F1.push_back(len_frame);

    std::vector<double> paramC4F2;
    paramC4F2.push_back(wid_frame-thk_frame);
    paramC4F2.push_back(thk_frame);
    paramC4F2.push_back(len_frame);

    std::vector<double> paramC4FR;
    paramC4FR.push_back(wid_frame);
    paramC4FR.push_back(wid_frame);
    paramC4FR.push_back(len_frame);
    
    //     G4Box *c4f1_box = new G4Box("C4F1",thk_frame/2.,wid_frame/2.,len_frame/2.);
    //     G4LogicalVolume *c4f1_log = new G4LogicalVolume(c4f1_box,Iron,"C4F1",0,0,0);
    //     c4f1_log->SetVisAttributes(cc04_att);

    //     G4Box *c4f2_box = new G4Box("C4F2",wid_frame/2.-thk_frame/2.,thk_frame/2.,len_frame/2.);
    //     G4LogicalVolume *c4f2_log = new G4LogicalVolume(c4f2_box,Iron,"C4F2",0,0,0);
    //     c4f2_log->SetVisAttributes(cc04_att);

    //     G4Box *c4fr_box = new G4Box("C4FR",wid_frame/2.,wid_frame/2.,len_frame/2.);
    //     G4LogicalVolume *c4fr_log = new G4LogicalVolume(c4fr_box,Iron,"C4FR",0,0,0);
    //     c4fr_log->SetVisAttributes(cc04_att);

    double xx = 0;
    double yy = 0;
    double dz = 0;

    // frame, front side

    xx = (cc04_xyo+(len_frame-cc04_xyo))/2.-wid_frame/2.;
    yy = 0.;
    dz = (cc04_len/2.+thk_frame)-wid_frame/2.;

    GsimBox* boxC4FR = new GsimBox("C4FR",cc04,
				   G4ThreeVector(xx,yy,dz),
				   G4ThreeVector(90*deg,0,0));
    boxC4FR->setParameters(paramC4FR);
    boxC4FR->setOuterMaterial("G4_Fe");
    boxC4FR->setOuterColor("gray70");
    boxC4FR->setOuterCopyNo(1);
    boxC4FR->setBriefName("CC04");
    cc04->addDaughter(boxC4FR);
    m_detList.push_back(boxC4FR);
    

    //new G4PVPlacement(rotations[501],G4ThreeVector(xx,yy,dz),c4fr_log,"C4FR",cc04_log,false,1);



    xx = -((cc04_xyo+(len_frame-cc04_xyo))/2.-wid_frame/2.);
    yy = 0.;
    dz = (cc04_len/2.+thk_frame)-wid_frame/2.;

    boxC4FR->cloneDetector(G4ThreeVector(xx,yy,dz),
			   G4ThreeVector(90*deg,0,180*deg),2);
    //new G4PVPlacement(rotations[503],G4ThreeVector(xx,yy,dz),c4fr_log,"C4FR",cc04_log,false,2);



    xx = 0;
    yy = (cc04_xyo+(len_frame-cc04_xyo))/2.-wid_frame/2.;
    dz = (cc04_len/2.+thk_frame)+wid_frame/2.;

    boxC4FR->cloneDetector(G4ThreeVector(xx,yy,dz),
			   G4ThreeVector(0,90*deg,0),3);

    //new G4PVPlacement(rotations[502],G4ThreeVector(xx,yy,dz),c4fr_log,"C4FR",cc04_log,false,3);

    xx = 0;
    yy = -((cc04_xyo+(len_frame-cc04_xyo))/2.-wid_frame/2.);
    dz = (cc04_len/2.+thk_frame)+wid_frame/2.;

    boxC4FR->cloneDetector(G4ThreeVector(xx,yy,dz),
			   G4ThreeVector(180*deg,90*deg,0),4);

    //new G4PVPlacement(rotations[504],G4ThreeVector(xx,yy,dz),c4fr_log,"C4FR",cc04_log,false,4);

    // frame, back side

    xx = (cc04_xyo+(len_frame-cc04_xyo))/2.-wid_frame/2.;
    yy = 0.;
    dz = -((cc04_len/2.+thk_frame)-wid_frame/2.);
    
    boxC4FR->cloneDetector(G4ThreeVector(xx,yy,dz),
			   G4ThreeVector(-90*deg,0,0),5);

    //new G4PVPlacement(rotations[505],G4ThreeVector(xx,yy,dz),c4fr_log,"C4FR",cc04_log,false,5);

    xx = -((cc04_xyo+(len_frame-cc04_xyo))/2.-wid_frame/2.);
    yy = 0.;
    dz = -((cc04_len/2.+thk_frame)-wid_frame/2.);

    boxC4FR->cloneDetector(G4ThreeVector(xx,yy,dz),
			   G4ThreeVector(-90*deg,0,180*deg),6);

    //new G4PVPlacement(rotations[507],G4ThreeVector(xx,yy,dz),c4fr_log,"C4FR",cc04_log,false,6);
    
    xx = 0;
    yy = (cc04_xyo+(len_frame-cc04_xyo))/2.-wid_frame/2.;
    dz = -((cc04_len/2.+thk_frame)+wid_frame/2.);

    boxC4FR->cloneDetector(G4ThreeVector(xx,yy,dz),
			   G4ThreeVector(0,-90*deg,0),7);

    //new G4PVPlacement(rotations[506],G4ThreeVector(xx,yy,dz),c4fr_log,"C4FR",cc04_log,false,7);

    xx = 0;
    yy = -((cc04_xyo+(len_frame-cc04_xyo))/2.-wid_frame/2.);
    dz = -((cc04_len/2.+thk_frame)+wid_frame/2.);

    boxC4FR->cloneDetector(G4ThreeVector(xx,yy,dz),
			   G4ThreeVector(0,-90*deg,180*deg),8);

    //new G4PVPlacement(rotations[508],G4ThreeVector(xx,yy,dz),c4fr_log,"C4FR",cc04_log,false,8);

    //     GSROTM( 500,  90.,  90.,  90., 180.,   0.,   0. ); //+90 around Z
    //     GSROTM( 501,  90.,   0.,   0.,  90.,  90., -90. ); //-90 around X
    //     GSROTM( 503,  90., 180.,   0.,  90.,  90.,  90. ); //-90 around X +180Z
    //     GSROTM( 502, 180.,   0.,  90.,  90.,  90.,   0. ); //-90 around X +270y +90Z
    //     GSROTM( 504, 180.,   0.,  90., -90.,  90.,   0. ); //-90 around X +270y +270Z
    //     GSROTM( 505,  90.,   0., 180.,   0.,  90.,  90. ); //+90 around X
    //     GSROTM( 507,  90., 180., 180.,   0.,  90., -90. ); //+90 around X +180Z
    //     GSROTM( 506,   0.,   0.,  90.,  90.,  90., 180. ); //+90 around X +90 y +270Z
    //     GSROTM( 508,   0.,   0.,  90., -90.,  90.,   0. ); //+90 around X +90 y +90Z    


    
    xx = wid_frame/2.-thk_frame/2.;
    yy = 0;
    dz = 0;
    
    GsimBox* boxC4F1 = new GsimBox("C4F1",boxC4FR,
				   G4ThreeVector(xx,yy,dz),
				   G4ThreeVector(0,0,0));
    boxC4F1->setParameters(paramC4F1);
    boxC4F1->setOuterMaterial("G4_Fe");
    boxC4F1->setOuterColor("gray70");
    boxC4F1->setBriefName("CC04");
    boxC4FR->addDaughter(boxC4F1);
    m_detList.push_back(boxC4F1);


    //new G4PVPlacement(0,G4ThreeVector(xx,yy,dz),c4f1_log,"C4F1",c4fr_log,false,1);
    
    xx = -thk_frame/2.;
    yy = wid_frame/2.-thk_frame/2.;
    dz = 0;

    GsimBox* boxC4F2 = new GsimBox("C4F2",boxC4FR,
				   G4ThreeVector(xx,yy,dz),
				   G4ThreeVector(0,0,0));
    boxC4F2->setParameters(paramC4F2);
    boxC4F2->setOuterMaterial("G4_Fe");
    boxC4F2->setOuterColor("gray70");
    boxC4F2->setBriefName("CC04");
    boxC4FR->addDaughter(boxC4F2);
    m_detList.push_back(boxC4F2);
    
    
    //new G4PVPlacement(0,G4ThreeVector(xx,yy,dz),c4f2_log,"C4F2",c4fr_log,false,1);

    

    
    //     // lead sheet

    double c4ld_z[2] = {-cc04_lead_thk/2.,cc04_lead_thk/2.};
    double c4ld_ri[2] = {cc04_lead_in/2.,cc04_lead_in/2.};
    double c4ld_ro[2] = {cc04_lead_out/2.,cc04_lead_out/2.};

    //      G4Polyhedra *c4ld_box = new G4Polyhedra("C4LD", deg2rad(-360./4./2.), deg2rad(360.)
    // 					     , 4, 2, c4ld_z, c4ld_ri, c4ld_ro);
    //      G4LogicalVolume *c4ld_log = new G4LogicalVolume(c4ld_box, Lead, "C4LD", 0,0,0);
    //      c4ld_log->SetVisAttributes(cc04_att);

    std::vector<double> paramC4LD;
    paramC4LD.push_back((-360./4./2.)*deg);
    paramC4LD.push_back(360.*deg);
    paramC4LD.push_back(4);
    paramC4LD.push_back(cc04_lead_thk);
    paramC4LD.push_back(cc04_lead_in/2.);
    paramC4LD.push_back(cc04_lead_out/2.);
			



    // center of sheet in CC04
    double cc04m_x = cc04_xyo/2.-cc04_sci_len/2.; // 50/2-31.3/2=9.35
    double cc04m_y = cc04_xyo/2.-cc04_sci_wdt/2.; // 50/2-18.7/2=15.65

    // assemble from down side
    double posx[2] = {cc04m_x, -cc04m_x};
    double posy[2] = {cc04m_y, -cc04m_y};

    dz = -(-cc04_len/2.+cc04_sci_thk/2.);
    double step = cc04_sci_thk/2.+gap+cc04_lead_thk/2.;

    int index = 0;

    GsimBox* boxC4S=0;
    GsimPolyhedra2* hedra=0;
    for(int i=1; i<=cc04_nsci1; i++){
      xx=cc04m_x;
      yy=-posy[index];

       
      if(!boxC4S) {
	boxC4S = new GsimBox("C4S",cc04,
			     G4ThreeVector(xx,yy,dz),
			     G4ThreeVector(0,0,0));
	boxC4S->setParameters(paramC4S);
	boxC4S->setOuterColor("blue");
	boxC4S->setOuterCopyNo(3);
	boxC4S->setBriefName("CC04");
	boxC4S->setSensitiveDetector("CC04");
	cc04->addDaughter(boxC4S);

      } else {
	boxC4S->cloneDetector(G4ThreeVector(xx,yy,dz),
			      G4ThreeVector(0,0,0),3);
      }
       
      //       new G4PVPlacement(0,G4ThreeVector(xx,yy,dz),c4s3_log,"C4S3",cc04_log,false,2*i-1);


      xx=cc04m_y;
      yy=posx[index];
       

      boxC4S->cloneDetector(G4ThreeVector(xx,yy,dz),
			    G4ThreeVector(0,0,90*deg),3);
       
      //       new G4PVPlacement(rotations[500],G4ThreeVector(xx,yy,dz),c4s3_log,"C4S3",cc04_log,false,2*i);

      xx=-cc04m_x;
      yy=posy[index];
      boxC4S->cloneDetector(G4ThreeVector(xx,yy,dz),
			    G4ThreeVector(0,0,0),2);
       
      //new G4PVPlacement(0,G4ThreeVector(xx,yy,dz),c4s2_log,"C4S2",cc04_log,false,2*i-1);
       
      xx=-cc04m_y;
      yy=-posx[index];
      boxC4S->cloneDetector(G4ThreeVector(xx,yy,dz),
			    G4ThreeVector(0,0,90*deg),2);
      //new G4PVPlacement(rotations[500],G4ThreeVector(xx,yy,dz),c4s2_log,"C4S2",cc04_log,false,2*i);

      dz-=step;

      xx=0.;
      yy=0.;

      if(!hedra) {
	hedra = new GsimPolyhedra2("C4LD",cc04,
				   G4ThreeVector(xx,yy,dz),
				   G4ThreeVector(0,0,0));
	hedra->setOuterMaterial("G4_Pb");
	hedra->setParameters(paramC4LD);
	hedra->setOuterColor("gray70");
	hedra->setOuterCopyNo(i);
	hedra->setBriefName("CC04");
	addDaughter(hedra);
	m_detList.push_back(hedra);
      } else {
	hedra->cloneDetector(G4ThreeVector(xx,yy,dz),
			     G4ThreeVector(0,0,0),i);
      }
       
       
      //new G4PVPlacement(0,G4ThreeVector(xx,yy,dz),c4ld_log,"C4LD",mother_log,false,i);
       
      dz-=step;
       
      index++;
      if(index>1) index=0;
       
    }
     
    // assemble first 2 layers

    step = cc04_sci_thk+gap;

    for(int i=1; i<=cc04_nsci2; i++){
      xx=cc04m_x;
      yy=-posy[index];
      boxC4S->cloneDetector(G4ThreeVector(xx,yy,dz),
			    G4ThreeVector(0,0,0),1);
       
      //new G4PVPlacement(0,G4ThreeVector(xx,yy,dz),c4s1_log,"C4S1",cc04_log,false,2*i-1);

      xx=cc04m_y;
      yy=posx[index];
      boxC4S->cloneDetector(G4ThreeVector(xx,yy,dz),
			    G4ThreeVector(0,0,90*deg),1);
       
      //new G4PVPlacement(rotations[500],G4ThreeVector(xx,yy,dz),c4s1_log,"C4S1",cc04_log,false,2*i);

      xx=-cc04m_x;
      yy=posy[index];
      boxC4S->cloneDetector(G4ThreeVector(xx,yy,dz),
			    G4ThreeVector(0,0,0),0);
      //new G4PVPlacement(0,G4ThreeVector(xx,yy,dz),c4s0_log,"C4S0",cc04_log,false,2*i-1);

      xx=-cc04m_y;
      yy=-posx[index];
      boxC4S->cloneDetector(G4ThreeVector(xx,yy,dz),
			    G4ThreeVector(0,0,90*deg),0);
      //new G4PVPlacement(rotations[500],G4ThreeVector(xx,yy,dz),c4s0_log,"C4S0",cc04_log,false,2*i);

      dz-=step;

      index++;
      if(index>1) index=0;
    }
  }
}


GsimE391CC04::~GsimE391CC04()
{
  ;
}


void GsimE391CC04::setFastSimulationLevel(int level)
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
      (*it)->setSensitiveDetector("CC04",0);
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

