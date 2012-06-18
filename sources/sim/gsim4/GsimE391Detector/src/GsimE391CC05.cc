/**
 *  @file
 *  @brief  GsimE391CC05
 *  $Id: GsimE391CC05.cc,v 1.6 2007/02/04 12:56:46 nanjo Exp $
 *  $Log: GsimE391CC05.cc,v $
 *  Revision 1.6  2007/02/04 12:56:46  nanjo
 *  GsimBoxWithAHole is used.
 *
 *  Revision 1.5  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimE391Detector/GsimE391CC05.h"
#include "GsimE391Detector/GsimUserGeom.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimDetector/GsimPolyhedra2.h"
#include "GsimDetector/GsimTrap.h"
#include "GsimDetector/GsimTube.h"
#include "GsimDetector/GsimBox.h"

using namespace E391;

GsimE391CC05::GsimE391CC05(std::string name,
			   GsimDetector* motherDetector,
			   G4ThreeVector transV,G4ThreeVector rotV,
			   int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{

  m_className = "GsimE391CC05";


  
  int ivol;
  
  int n_cc5_sci4;
  int n_cc5_sci5;
  
  int n_vacuum = 16;  //vac
  int n_steel = 10;  //fe
  int n_cc5_sci = 99;  //sci
  int n_cc5_lead = 13;  //pb
  
  int cc05_nsci1 = 30;
  int cc05_nsci2 = 2;
  int cc05_nsci0 = 2;
  int cc05_nlead = 32;  // must = cc05_nsci1+cc05_nsci2
  
  double gap = 0.025*cm;
  
  double cc05_sci_len = 31.3*cm;
  double cc05_sci_wdt = 18.7*cm;
  double cc05_sci_thk = 0.5*cm;
  double cc05_lead_out = 50.*cm;
  double cc05_lead_in = 12.6*cm;
  double cc05_lead_thk = 0.2*cm;
  double cc05_xyo = 50.*cm;
  double cc05_xyi = 12.6*cm;
  
  double cc05_len =
    ((double)(cc05_nsci1+cc05_nsci2+cc05_nsci0))*cc05_sci_thk
    + ((double)(cc05_nlead))*cc05_lead_thk
    + ((double)(2*cc05_nlead+cc05_nsci0-1*cm))*gap;

  {
    double wid_frame = 3.*cm;
    double thk_frame = .8*cm;
    double len_frame = 54.0*cm;

    std::vector<double> paramVec;
    paramVec.push_back(-45.*deg);
    paramVec.push_back(360*deg);
    paramVec.push_back(4);
    paramVec.push_back(cc05_len+(thk_frame+wid_frame)*2.);
    paramVec.push_back(cc05_xyi/2.);
    paramVec.push_back(cc05_xyo+(len_frame-cc05_xyo));

    
    

    // mother volume for CC5
    // G4Box *cc05_box = new G4Box("CC05",
// 				(cc05_xyo+(len_frame-cc05_xyo))/2.,
// 				(cc05_xyo+(len_frame-cc05_xyo))/2.,
// 				(cc05_len+(thk_frame+wid_frame)*2.)/2.); //include frame
//     G4LogicalVolume *cc05_log = new G4LogicalVolume(cc05_box, Vacuum, "CC05", 0,0,0);
//     cc05_log->SetVisAttributes(cc05_att);

    double csic_zmin = 614.8*cm;  // See GsimUserGeom.h
    double dist_cc05 = 259.3*cm;  // See GsimUserGeom.h

    double c_cc05_z = csic_zmin + dist_cc05 + (cc05_len+(thk_frame+wid_frame)*2.)/2.;
    

    char nam[100];
    std::sprintf(nam,"CC05");
    GsimPolyhedra2* cc05 = new GsimPolyhedra2(std::string(nam),this,
					      G4ThreeVector(0,0,0),
					      G4ThreeVector(0,0,0));
    cc05->setOuterMaterial("G4_AIR");
    cc05->setParameters(paramVec);
    cc05->setOuterVisibility(false);
    cc05->setBriefName(nam);
    addDaughter(cc05);
    m_detList.push_back(cc05);
    
    //new G4PVPlacement(0,G4ThreeVector(0,0,c_cc05_z),cc05_log,"CC05",mother_log,false,1);
    
    // sci sheets for different PMTs

    std::vector<double> paramC5S;
    paramC5S.push_back(cc05_sci_len);
    paramC5S.push_back(cc05_sci_wdt);
    paramC5S.push_back(cc05_sci_thk);
    

    // G4Box *c5s0_box = new G4Box("C5S0",cc05_sci_len/2.,cc05_sci_wdt/2.,cc05_sci_thk/2.);
//     G4LogicalVolume *c5s0_log = new G4LogicalVolume(c5s0_box,Scintillator,"C5S0",0,0,0);
//     c5s0_log->SetVisAttributes(cc05_att);
                
//     G4Box *c5s1_box = new G4Box("C5S1",cc05_sci_len/2.,cc05_sci_wdt/2.,cc05_sci_thk/2.);
//     G4LogicalVolume *c5s1_log = new G4LogicalVolume(c5s1_box,Scintillator,"C5S1",0,0,0);
//     c5s1_log->SetVisAttributes(cc05_att);
                
//     G4Box *c5s2_box = new G4Box("C5S2",cc05_sci_len/2.,cc05_sci_wdt/2.,cc05_sci_thk/2.);
//     G4LogicalVolume *c5s2_log = new G4LogicalVolume(c5s2_box,Scintillator,"C5S2",0,0,0);
//     c5s2_log->SetVisAttributes(cc05_att);
                
//     G4Box *c5s3_box = new G4Box("C5S3",cc05_sci_len/2.,cc05_sci_wdt/2.,cc05_sci_thk/2.);
//     G4LogicalVolume *c5s3_log = new G4LogicalVolume(c5s3_box,Scintillator,"C5S3",0,0,0);
//     c5s3_log->SetVisAttributes(cc05_att);
                
//     G4Box *c5s4_box = new G4Box("C5S4",cc05_sci_len/2.,cc05_sci_wdt/2.,cc05_sci_thk/2.);
//     G4LogicalVolume *c5s4_log = new G4LogicalVolume(c5s4_box,Scintillator,"C5S4",0,0,0);
//     c5s4_log->SetVisAttributes(cc05_att);
                
//     G4Box *c5s5_box = new G4Box("C5S5",cc05_sci_len/2.,cc05_sci_wdt/2.,cc05_sci_thk/2.);
//     G4LogicalVolume *c5s5_log = new G4LogicalVolume(c5s5_box,Scintillator,"C5S5",0,0,0);
//     c5s5_log->SetVisAttributes(cc05_att);




    // frame
    std::vector<double> paramC5F1;
    paramC5F1.push_back(thk_frame);
    paramC5F1.push_back(wid_frame);
    paramC5F1.push_back(len_frame);

    std::vector<double> paramC5F2;
    paramC5F2.push_back(wid_frame-thk_frame);
    paramC5F2.push_back(thk_frame);
    paramC5F2.push_back(len_frame);

    std::vector<double> paramC5FR;
    paramC5FR.push_back(wid_frame);
    paramC5FR.push_back(wid_frame);
    paramC5FR.push_back(len_frame);
    

//     G4Box *c5f1_box = new G4Box("C5F1",thk_frame/2.,wid_frame/2.,len_frame/2.);
//     G4LogicalVolume *c5f1_log = new G4LogicalVolume(c5f1_box,Iron,"C5F1",0,0,0);
//     c5f1_log->SetVisAttributes(cc05_att);

//     G4Box *c5f2_box = new G4Box("C5F2",wid_frame/2.-thk_frame/2.,thk_frame/2.,len_frame/2.);
//     G4LogicalVolume *c5f2_log = new G4LogicalVolume(c5f2_box,Iron,"C5F2",0,0,0);
//     c5f2_log->SetVisAttributes(cc05_att);

//     G4Box *c5fr_box = new G4Box("C5FR",wid_frame/2.,wid_frame/2.,len_frame/2.);
//     G4LogicalVolume *c5fr_log = new G4LogicalVolume(c5fr_box,Iron,"C5FR",0,0,0);
//     c5fr_log->SetVisAttributes(cc05_att);

    double xx = 0;
    double yy = 0;
    double dz = 0;

    // frame, front side

    xx = (cc05_xyo+(len_frame-cc05_xyo))/2. - wid_frame/2.;
    yy = 0;
    dz = (cc05_len/2.+thk_frame)-wid_frame/2.;

    GsimBox* boxC5FR = new GsimBox("C5FR",cc05,
				   G4ThreeVector(xx,yy,dz),
				   G4ThreeVector(90*deg,0,0));
    boxC5FR->setParameters(paramC5FR);
    boxC5FR->setOuterMaterial("G4_Fe");
    boxC5FR->setOuterColor("gray70");
    boxC5FR->setOuterCopyNo(11);
    boxC5FR->setBriefName("CC05");
    cc05->addDaughter(boxC5FR);
    m_detList.push_back(boxC5FR);

    //new G4PVPlacement(rotations[501],G4ThreeVector(xx,yy,dz),c5fr_log,"C5FR",cc05_log,false,11);

    xx = -((cc05_xyo+(len_frame-cc05_xyo))/2. - wid_frame/2.);
    yy = 0;
    dz = (cc05_len/2.+thk_frame)-wid_frame/2.;

    boxC5FR->cloneDetector(G4ThreeVector(xx,yy,dz),
			   G4ThreeVector(90*deg,0,180*deg),12);

    //new G4PVPlacement(rotations[503],G4ThreeVector(xx,yy,dz),c5fr_log,"C5FR",cc05_log,false,12);

    xx = 0;
    yy = (cc05_xyo+(len_frame-cc05_xyo))/2. - wid_frame/2.;
    dz = (cc05_len/2.+thk_frame)+wid_frame/2.;

    boxC5FR->cloneDetector(G4ThreeVector(xx,yy,dz),
			   G4ThreeVector(0,90*deg,0),13);
    
    //new G4PVPlacement(rotations[502],G4ThreeVector(xx,yy,dz),c5fr_log,"C5FR",cc05_log,false,13);

    xx = 0;
    yy = -((cc05_xyo+(len_frame-cc05_xyo))/2. - wid_frame/2.);
    dz = (cc05_len/2.+thk_frame)+wid_frame/2.;
    
    boxC5FR->cloneDetector(G4ThreeVector(xx,yy,dz),
			   G4ThreeVector(180*deg,90*deg,0),14);
    //new G4PVPlacement(rotations[504],G4ThreeVector(xx,yy,dz),c5fr_log,"C5FR",cc05_log,false,14);

    // frame, back side

    xx = (cc05_xyo+(len_frame-cc05_xyo))/2. - wid_frame/2.;
    yy = 0;
    dz = -((cc05_len/2.+thk_frame)-wid_frame/2.);

    boxC5FR->cloneDetector(G4ThreeVector(xx,yy,dz),
			   G4ThreeVector(-90*deg,0,0),15);

    //new G4PVPlacement(rotations[505],G4ThreeVector(xx,yy,dz),c5fr_log,"C5FR",cc05_log,false,15);

    xx = -((cc05_xyo+(len_frame-cc05_xyo))/2. - wid_frame/2.);
    yy = 0;
    dz = -((cc05_len/2.+thk_frame)-wid_frame/2.);

    boxC5FR->cloneDetector(G4ThreeVector(xx,yy,dz),
			   G4ThreeVector(-90*deg,0,180*deg),16);

    //new G4PVPlacement(rotations[507],G4ThreeVector(xx,yy,dz),c5fr_log,"C5FR",cc05_log,false,16);

    xx = 0;
    yy = (cc05_xyo+(len_frame-cc05_xyo))/2. - wid_frame/2.;
    dz = -((cc05_len/2.+thk_frame)+wid_frame/2.);

    boxC5FR->cloneDetector(G4ThreeVector(xx,yy,dz),
			   G4ThreeVector(0,-90*deg,0),17);

    //new G4PVPlacement(rotations[506],G4ThreeVector(xx,yy,dz),c5fr_log,"C5FR",cc05_log,false,17);

    xx = 0;
    yy = -((cc05_xyo+(len_frame-cc05_xyo))/2. - wid_frame/2.);
    dz = -((cc05_len/2.+thk_frame)+wid_frame/2.);

    boxC5FR->cloneDetector(G4ThreeVector(xx,yy,dz),
			   G4ThreeVector(0,-90*deg,180*deg),18);

    //new G4PVPlacement(rotations[508],G4ThreeVector(xx,yy,dz),c5fr_log,"C5FR",cc05_log,false,18);



    xx = wid_frame/2. - thk_frame/2.;
    yy = 0;
    dz = 0;

    GsimBox* boxC5F1 = new GsimBox("C5F1",boxC5FR,
				   G4ThreeVector(xx,yy,dz),
				   G4ThreeVector(0,0,0));
    boxC5F1->setParameters(paramC5F1);
    boxC5F1->setOuterMaterial("G4_Fe");
    boxC5F1->setOuterColor("gray70");
    boxC5F1->setBriefName("CC05");
    boxC5FR->addDaughter(boxC5F1);
    m_detList.push_back(boxC5F1);
    
    //new G4PVPlacement(0,G4ThreeVector(xx,yy,dz),c5f1_log,"C5F1",c5fr_log,false,1);

    xx = -thk_frame/2.;
    yy = wid_frame/2. - thk_frame/2.;
    dz = 0;

    GsimBox* boxC5F2 = new GsimBox("C5F2",boxC5FR,
				   G4ThreeVector(xx,yy,dz),
				   G4ThreeVector(0,0,0));
    boxC5F2->setParameters(paramC5F2);
    boxC5F2->setOuterMaterial("G4_Fe");
    boxC5F2->setOuterColor("gray70");
    boxC5F2->setBriefName("CC05");
    boxC5FR->addDaughter(boxC5F2);
    m_detList.push_back(boxC5F2);

    //new G4PVPlacement(0,G4ThreeVector(xx,yy,dz),c5f2_log,"C5F2",c5fr_log,false,1);

    
    // lead sheet

    double c5ld_z[2] = {-cc05_lead_thk/2., cc05_lead_thk/2.};
    double c5ld_ri[2] = {cc05_lead_out/2., cc05_lead_out/2.};
    double c5ld_ro[2] = {cc05_lead_in/2., cc05_lead_in/2.};

    // G4Polyhedra *c5ld_box = new G4Polyhedra("C5LD",deg2rad(-360./4./2.),deg2rad(360.),4,2,c5ld_z,c5ld_ri,c5ld_ro);
//     G4LogicalVolume *c5ld_log = new G4LogicalVolume(c5ld_box,Lead,"C5LD",0,0,0);
//     c5ld_log->SetVisAttributes(cc05_att);
    
    std::vector<double> paramC5LD;
    paramC5LD.push_back((-360./4./2.)*deg);
    paramC5LD.push_back(360.*deg);
    paramC5LD.push_back(4);
    paramC5LD.push_back(cc05_lead_thk);
    paramC5LD.push_back(cc05_lead_in/2.);
    paramC5LD.push_back(cc05_lead_out/2.);

    // center of sheet in CC05
    double cc05m_x = cc05_xyo/2.-cc05_sci_len/2.;  // 50/2-31.3/2=9.35
    double cc05m_y = cc05_xyo/2.-cc05_sci_wdt/2.;  // 50/2-18.7/2=15.65
    
    // assemble from down side
    double posx[2] = {cc05m_x,-cc05m_x};
    double posy[2] = {cc05m_y,-cc05m_y};
    
    dz = -(-cc05_len/2. + cc05_sci_thk/2.);
    double step = cc05_sci_thk/2.+gap+cc05_lead_thk/2.;
    
    int index = 0;


    GsimBox* boxC5S=0;
    GsimPolyhedra2* hedra=0;
    for(int i=1; i<=cc05_nsci2; i++){  // last 2 layers
      xx=cc05m_x;
      yy=-posy[index];

      if(!boxC5S) {
	boxC5S = new GsimBox("C5S",cc05,
			     G4ThreeVector(xx,yy,dz),
			     G4ThreeVector(0,0,0));
	boxC5S->setParameters(paramC5S);
	boxC5S->setOuterColor("blue");
	boxC5S->setOuterCopyNo(5);
	boxC5S->setBriefName("CC05");
	boxC5S->setSensitiveDetector("CC05");
	cc05->addDaughter(boxC5S);

      } else {
	boxC5S->cloneDetector(G4ThreeVector(xx,yy,dz),
			      G4ThreeVector(0,0,0),5);
      }
      //new G4PVPlacement(0,G4ThreeVector(xx,yy,dz),c5s5_log,"C5S5",cc05_log,false,2*i-1);
      
      xx=cc05m_y;
      yy=posx[index];
      boxC5S->cloneDetector(G4ThreeVector(xx,yy,dz),
			    G4ThreeVector(0,0,90*deg),5);
      //new G4PVPlacement(rotations[500],G4ThreeVector(xx,yy,dz),c5s5_log,"C5S5",cc05_log,false,2*i);
      
      xx=-cc05m_x;
      yy=posy[index];
      boxC5S->cloneDetector(G4ThreeVector(xx,yy,dz),
			    G4ThreeVector(0,0,0),4);
      //new G4PVPlacement(0,G4ThreeVector(xx,yy,dz),c5s4_log,"C5S4",cc05_log,false,2*i-1);
      
      xx=-cc05m_y;
      yy=-posx[index];
      boxC5S->cloneDetector(G4ThreeVector(xx,yy,dz),
			    G4ThreeVector(0,0,90*deg),4);
      //new G4PVPlacement(rotations[500],G4ThreeVector(xx,yy,dz),c5s4_log,"C5S4",cc05_log,false,2*i);
      
      dz-=step;
      
      xx=0;
      yy=0;

      if(!hedra) {
	hedra = new GsimPolyhedra2("C5LD",cc05,
				   G4ThreeVector(xx,yy,dz),
				   G4ThreeVector(0,0,0));
	hedra->setOuterMaterial("G4_Pb");
	hedra->setParameters(paramC5LD);
	hedra->setOuterColor("gray70");
	hedra->setOuterCopyNo(i);
	hedra->setBriefName("CC05");
	addDaughter(hedra);
	m_detList.push_back(hedra);
      } else {
	hedra->cloneDetector(G4ThreeVector(xx,yy,dz),
			     G4ThreeVector(0,0,0),i);
      }
      //new G4PVPlacement(0,G4ThreeVector(xx,yy,dz),c5ld_log,"C5LD",cc05_log,false,i);
      
      dz-=step;
      
      index++;
      
      if(index>1) index=0;
      
    }

    for(int i=1; i<=cc05_nsci1; i++){  // assemble the calorimeter part
      xx = cc05m_x;
      yy = -posy[index];
      boxC5S->cloneDetector(G4ThreeVector(xx,yy,dz),
			    G4ThreeVector(0,0,0),3);
      //new G4PVPlacement(0,G4ThreeVector(xx,yy,dz),c5s3_log,"C5S3",cc05_log,false,2*i-1);
      
      xx = cc05m_y;
      yy = posx[index];
      boxC5S->cloneDetector(G4ThreeVector(xx,yy,dz),
			    G4ThreeVector(0,0,90*deg),3);
      //new G4PVPlacement(rotations[500],G4ThreeVector(xx,yy,dz),c5s3_log,"C5S3",cc05_log,false,2*i);
      
      xx = -cc05m_x;
      yy = posy[index];
      boxC5S->cloneDetector(G4ThreeVector(xx,yy,dz),
			    G4ThreeVector(0,0,0),2);
      //new G4PVPlacement(0,G4ThreeVector(xx,yy,dz),c5s2_log,"C5S2",cc05_log,false,2*i-1);
      
      xx = -cc05m_y;
      yy = -posx[index];
      boxC5S->cloneDetector(G4ThreeVector(xx,yy,dz),
			    G4ThreeVector(0,0,90*deg),2);
      //new G4PVPlacement(rotations[500],G4ThreeVector(xx,yy,dz),c5s2_log,"C5S2",cc05_log,false,2*i);
      
      dz-=step;
      
      xx=0;
      yy=0;
      hedra->cloneDetector(G4ThreeVector(xx,yy,dz),
			   G4ThreeVector(0,0,0),i+cc05_nsci2);
      //new G4PVPlacement(0,G4ThreeVector(xx,yy,dz),c5ld_log,"C5LD",cc05_log,false,i+cc05_nsci2);
      
      dz-=step;
      
      index++;
      
      if(index>1) index = 0;
      
    }
    
    
    // assemble the first 2 layers
    
    step = cc05_sci_thk+gap;
    
    for(int i=1; i<=cc05_nsci0; i++){
      xx = cc05m_x;
      yy = -posy[index];
      boxC5S->cloneDetector(G4ThreeVector(xx,yy,dz),
			    G4ThreeVector(0,0,0),1);
      //new G4PVPlacement(0,G4ThreeVector(xx,yy,dz),c5s1_log,"C5S1",cc05_log,false,2*i-1);
      
      xx = cc05m_y;
      yy = posx[index];
      boxC5S->cloneDetector(G4ThreeVector(xx,yy,dz),
			    G4ThreeVector(0,0,90*deg),1);
       //new G4PVPlacement(rotations[500],G4ThreeVector(xx,yy,dz),c5s1_log,"C5S1",cc05_log,false,2*i);
      
      xx = -cc05m_x;
      yy = posy[index];
      boxC5S->cloneDetector(G4ThreeVector(xx,yy,dz),
			    G4ThreeVector(0,0,0),0);
      //new G4PVPlacement(0,G4ThreeVector(xx,yy,dz),c5s0_log,"C5S0",cc05_log,false,2*i-1);
      
      xx = -cc05m_y;
      yy = -posx[index];
      boxC5S->cloneDetector(G4ThreeVector(xx,yy,dz),
			    G4ThreeVector(0,0,90*deg),0);
      //new G4PVPlacement(rotations[500],G4ThreeVector(xx,yy,dz),c5s0_log,"C5S0",cc05_log,false,2*i);
      
      dz-=step;
      
      index++;
      
      if(index>1) index = 0;
      
    }
    
  }

  
}


GsimE391CC05::~GsimE391CC05()
{
  ;
}



void GsimE391CC05::setFastSimulationLevel(int level)
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
      (*it)->setSensitiveDetector("CC05",0);
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
