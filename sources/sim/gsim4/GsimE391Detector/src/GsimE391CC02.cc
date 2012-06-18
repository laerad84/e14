/**
 *  @file
 *  @brief  GsimE391CC02
 *  $Id: GsimE391CC02.cc,v 1.6 2006/12/06 18:58:52 nanjo Exp $ 
 *  $Log: GsimE391CC02.cc,v $
 *  Revision 1.6  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimE391Detector/GsimE391CC02.h"
#include "GsimE391Detector/GsimUserGeom.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimDetector/GsimPolyhedra2.h"
#include "GsimDetector/GsimTrap.h"
#include "GsimDetector/GsimTube.h"
#include "GsimDetector/GsimBox.h"

using namespace E391;

GsimE391CC02::GsimE391CC02(std::string name,
			   GsimDetector* motherDetector,
			   G4ThreeVector transV,G4ThreeVector rotV,
			   int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{

  m_className = "GsimE391CC02";

  int  ivol=0;

  // set Rotation Matrix 
  int irot_cc02h = grot_cc02 + 1;
  int irot_module[8]={0};

  double offset = 22.5/2.0;

  double phi1 = offset;
  double phi2 = phi1 + 90.0;
  //GSROTM( irot_cc02h, 90.0, phi1,  90.0,  phi2,  0., 0. );

  double phiMod[8];
  for ( int i=0 ; i<8 ; i++) {
    irot_module[i] = irot_cc02h + 1 + i;
    phi1 = 45.0*i + offset;
    phi2 = phi1 + 90.0;
    phiMod[i]=(45.0*i + offset)*deg;
    //GSROTM(irot_module[i],  90.0, phi1, 90.0, phi2, 0., 0.);
  }


  // set thickness
  double scint_thick = 0.5;
  double pbsb1_thick = 0.1;
  double pbsb2_thick = 0.2;
  double brass_thick = 0.0375;
  double al_thick = 1.5;
  double gap_scint = 0.005; // tentative thickness of white PET

  // 
  // CC02 mother volume
  // cc02, somwhow, inclines 22.5/2.0 degree(half module)

  double cc02_len =
    (scint_thick + 2.0*brass_thick + pbsb1_thick + gap_scint*2.0)*14.0 +
    (scint_thick + 2.0*brass_thick + pbsb2_thick + gap_scint*2.0)*29.0 +
    (al_thick*2.0 + scint_thick);

  double  cc02_rmax = 30.4;
  double  cc02_rmin = 6.35;
  float  p_cc02[] = { 0.0, 360, 16, 2,
                      -cc02_len/2,cc02_rmin,cc02_rmax,
                      cc02_len/2,cc02_rmin,cc02_rmax };

  std::vector<double> paramVec;
  paramVec.push_back(0.*deg);
  paramVec.push_back(360*deg);
  paramVec.push_back(16);
  paramVec.push_back(cc02_len*cm);
  paramVec.push_back(cc02_rmin*cm);
  paramVec.push_back(cc02_rmax*cm);

  char nam[100];
  std::sprintf(nam,"CC02");
  GsimPolyhedra2* cc02 = new GsimPolyhedra2(std::string(nam),this,
  					    G4ThreeVector(0,0,0),
  					    G4ThreeVector(0,0,phi1*deg));
  cc02->setOuterMaterial("GsimLowVacuum");
  cc02->setParameters(paramVec);
  cc02->setOuterVisibility(false);
  addDaughter(cc02);
  m_detList.push_back(cc02);

  //GSVOLU( "CC02","PGON",n_vacuum,p_cc02,sizeof(p_cc02)/sizeof(float),ivol );
  //double c_cc02_z = Fbar_Len - cc02_len/2;
  //  if ( DetUseCC02[0] ){
  //    GSPOS( "CC02", 1, "MOTH", 0,0,c_cc02_z, irot_cc02h, "ONLY" );
  //  }


  // CC2H -- outer aluminum support --

  double  cc2h_len   = cc02_len;
  double  cc2h_rmax  = 30.26;
  double  cc2h_rmin  = 29.85;
  float  p_cc2h[] = { 0.0, 360, 16, 2,
                      -cc2h_len/2,cc2h_rmin,cc2h_rmax,
                      cc2h_len/2,cc2h_rmin,cc2h_rmax };
  paramVec.clear();
  paramVec.push_back(0.*deg);
  paramVec.push_back(360.*deg);
  paramVec.push_back(16);
  paramVec.push_back(cc2h_len*cm);
  paramVec.push_back(cc2h_rmin*cm);
  paramVec.push_back(cc2h_rmax*cm);
  
  //GSVOLU( "CC2H","PGON",n_vacuum,p_cc2h,sizeof(p_cc2h)/sizeof(float),ivol );
  //if ( DetUseCC02[0] ){ //////
  //  GSPOS( "CC2H", 1, "CC02", 0,0,0, 0, "ONLY" );
  // }

  std::sprintf(nam,"CC2H");
  GsimPolyhedra2* cc2h = new GsimPolyhedra2(std::string(nam),cc02,
 					    G4ThreeVector(0,0,0),
 					    G4ThreeVector(0,0,0));
  cc2h->setOuterMaterial("G4_Al");
  cc2h->setParameters(paramVec);
  cc2h->setOuterColor("gray70");
  cc02->addDaughter(cc2h);
  m_detList.push_back(cc2h);
  
  /* -------------------------------------------------
     c
     c           <------  l4 ----------------->
     c 
     c           <----- l1 ------->
     c           __________________
     c  |   |    |                 \
     c  |   |    |                  \   SEGMENT 1
     c  |   h1   |         o(xo1,yo2)\
     c  |   |    |                    \
     c  |   |    |  <------ l2 ------> \
     c  |        -----------------------
     c  |   |    |                     /
     c  |   |    |                    /
     c  |   |    |                   /
     c  |   |    |                  /
     c  |   |    |                 /
     c  |   |    |                /
     c  |   |    |      o (xo2,yo2)         
     c  h3  |    |              /
     c  |   |    |             /       SEGMENT 2
     c  |   h2   |            /
     c  |   |    |           /
     c  |   |    |          /
     c  |   |    |         /        y
     c  |   |    |        /         
     c  |   |    |       /          |
     c  |   |    |      /           |
     c  |   |    |     /            |
     c  |   |    |    /             ------ x
     c  |   |    |   /
     c  |   |    |  /
     c  |   |    | /
     c  |   |    --
     c           l3
     --------------------------------------------------*/


  double l1 = 12.12;
  double l2 = 22.46;
  double l3 = 0.7;

  double h1 = 4.28;
  double h2 = 21.76;
  double h3 = h1 + h2;

  double l4 = h3 + l3;

  // center of segment 1
  double xo1 = (l2 + l1)*0.25 - 6.231;
  double yo1 = h2 + h1/2.0 + 3.590;

  // center of segment 2 
  double xo2 = (l3 + l2)*0.25 - 6.231;
  double yo2 = h2/2.0 + 3.590;

  double angle1 = atan((l2-l1)/(2.0*h1))*180.0/M_PI;
  double angle2 = atan((l2-l3)/(2.0*h2))*180.0/M_PI;

  float p_seg1[] = {cc02_len/2.0, 0.0,     0.0,
                    h1/2.0,       l2/2.0,  l1/2.0,  -angle1,
                    h1/2.0,       l2/2.0,  l1/2.0,  -angle1 };

  float p_seg2[] = {cc02_len/2.0, 0.0,     0.0,
                    h2/2.0,       l3/2.0,  l2/2.0,  angle2,
                    h2/2.0,       l3/2.0,  l2/2.0,  angle2 };
  
  std::vector<double> paramSEG1;
  paramSEG1.push_back(cc02_len*cm);
  paramSEG1.push_back(0.);
  paramSEG1.push_back(0.);
  paramSEG1.push_back(h1*cm);
  paramSEG1.push_back(l2*cm);
  paramSEG1.push_back(l1*cm);
  paramSEG1.push_back(-angle1*deg);
  paramSEG1.push_back(h1*cm);
  paramSEG1.push_back(l2*cm);
  paramSEG1.push_back(l1*cm);
  paramSEG1.push_back(-angle1*deg);

  std::vector<double> paramSEG2;
  paramSEG2.push_back(cc02_len*cm);
  paramSEG2.push_back(0.);
  paramSEG2.push_back(0.);
  paramSEG2.push_back(h2*cm);
  paramSEG2.push_back(l3*cm);
  paramSEG2.push_back(l2*cm);
  paramSEG2.push_back(angle2*deg);
  paramSEG2.push_back(h2*cm);
  paramSEG2.push_back(l3*cm);
  paramSEG2.push_back(l2*cm);
  paramSEG2.push_back(angle2*deg);

  

  //  GSVOLU("SEG1","TRAP",n_vacuum,p_seg1,sizeof(p_seg1)/sizeof(float),ivol);
  
  //  GSVOLU("SEG2","TRAP",n_vacuum,p_seg2,sizeof(p_seg2)/sizeof(float),ivol);

   //-- set angle--
  double x_seg1[8];
  double y_seg1[8];

  double x_seg2[8];
  double y_seg2[8];

  double r_seg1 = sqrt(xo1*xo1 +  yo1*yo1);
  double r_seg2 = sqrt(xo2*xo2 +  yo2*yo2);

  double theta1 = acos(xo1/r_seg1) + 22.5/2.0/180.0*M_PI;
  double theta2 = acos(xo2/r_seg2) + 22.5/2.0/180.0*M_PI;

  for ( int i=0 ; i<8 ; i++) {
    x_seg1[i] = r_seg1 * cos( theta1 + i*M_PI/4.0 );
    y_seg1[i] = r_seg1 * sin( theta1 + i*M_PI/4.0 );

    x_seg2[i] = r_seg2 * cos( theta2 + i*M_PI/4.0 );
    y_seg2[i] = r_seg2 * sin( theta2 + i*M_PI/4.0 );
  }

  GsimTrap* trapSEG1=0;
  GsimTrap* trapSEG2=0;
  // Segment
  {
    int icp_seg[]={3,4,5,6,7,8,1,2};  // copy no
    for ( int i=0 ; i<8 ; i++) {
      if(i==0) {
	std::sprintf(nam,"SEG1");
	trapSEG1=new GsimTrap(std::string(nam),cc02,
			      G4ThreeVector(x_seg1[i]*cm,y_seg1[i]*cm,0.0),
			      G4ThreeVector(0,0,phiMod[i]) );
	trapSEG1->setParameters(paramSEG1);
	trapSEG1->setOuterVisibility(false);
	trapSEG1->setOuterCopyNo(icp_seg[i]-1);
	cc02->addDaughter(trapSEG1);
	m_detList.push_back(trapSEG1);
	
	std::sprintf(nam,"SEG2");
	trapSEG2=new GsimTrap(std::string(nam),cc02,
			      G4ThreeVector(x_seg2[i]*cm,y_seg2[i]*cm,0.0),
			      G4ThreeVector(0,0,phiMod[i]) );
	trapSEG2->setParameters(paramSEG2);
	trapSEG2->setOuterVisibility(false);
	trapSEG2->setOuterCopyNo(icp_seg[i]-1);
	cc02->addDaughter(trapSEG2);
	m_detList.push_back(trapSEG2);
      } else {
	trapSEG1->cloneDetector(G4ThreeVector(x_seg1[i]*cm,y_seg1[i]*cm,0.0),
				G4ThreeVector(0,0,phiMod[i]),icp_seg[i]-1);
	trapSEG2->cloneDetector(G4ThreeVector(x_seg2[i]*cm,y_seg2[i]*cm,0.0),
 				G4ThreeVector(0,0,phiMod[i]),icp_seg[i]-1);
      }
      // GSPOS("SEG1",icp_seg[i],"CC02",x_seg1[i],y_seg1[i],0.0,
      //             irot_module[i],"ONLY");
      //       GSPOS("SEG2",icp_seg[i],"CC02",x_seg2[i],y_seg2[i],0.0,
      //             irot_module[i],"ONLY");
    }
  }



  GsimTrap* trapC2S1=0;
  GsimTrap* trapC2S2=0;
  GsimTrap* trapC2A1=0;
  GsimTrap* trapC2A2=0;
  GsimTrap* trapC211=0;
  GsimTrap* trapC212=0;
  GsimTrap* trapC221=0;
  GsimTrap* trapC222=0;
  GsimTrap* trapC2B1=0;
  GsimTrap* trapC2B2=0;
  
  // Layer structure
  {

    int icp_scn1 = 1;
    int icp_scn2 = 1;

    int icp_al1 = 1;
    int icp_al2 = 1;

    int icp_brass1 = 1;
    int icp_brass2 = 1;

    int icp_lead1mm_seg1 = 1;
    int icp_lead1mm_seg2 = 1;

    int icp_lead2mm_seg1 = 1;
    int icp_lead2mm_seg2 = 1;

    // c2s1, c2s2 - cc02 scintillator for segments 1 & 2
    float p_scn1[] = {scint_thick/2.0,      0.0,     0.0,
                      h1/2.0,       l2/2.0,  l1/2.0,  -angle1,
                      h1/2.0,       l2/2.0,  l1/2.0,  -angle1 };

    float p_scn2[] = {scint_thick/2.0,    0.0,     0.0,
                      h2/2.0,     l3/2.0,  l2/2.0,  angle2,
                      h2/2.0,     l3/2.0,  l2/2.0,  angle2 };

    
    std::vector<double> paramC2S1;
    paramC2S1.push_back(scint_thick*cm);
    paramC2S1.push_back(0.);
    paramC2S1.push_back(0.);
    paramC2S1.push_back(h1*cm);
    paramC2S1.push_back(l2*cm);
    paramC2S1.push_back(l1*cm);
    paramC2S1.push_back(-angle1*deg);
    paramC2S1.push_back(h1*cm);
    paramC2S1.push_back(l2*cm);
    paramC2S1.push_back(l1*cm);
    paramC2S1.push_back(-angle1*deg);

    
    std::vector<double> paramC2S2;
    paramC2S2.push_back(scint_thick*cm);
    paramC2S2.push_back(0.);
    paramC2S2.push_back(0.);
    paramC2S2.push_back(h2*cm);
    paramC2S2.push_back(l3*cm);
    paramC2S2.push_back(l2*cm);
    paramC2S2.push_back(angle2*deg);
    paramC2S2.push_back(h2*cm);
    paramC2S2.push_back(l3*cm);
    paramC2S2.push_back(l2*cm);
    paramC2S2.push_back(angle2*deg);
    
    
    // GSVOLU("C2S1","TRAP",n_scintillator,
//            p_scn1, sizeof(p_scn1)/sizeof(float),ivol);
//     GSVOLU("C2S2","TRAP",n_scintillator,
//            p_scn2, sizeof(p_scn2)/sizeof(float),ivol);

    // c2a1, c2a2 - cc02 aluminum 
    float p_al1[] = {al_thick/2.0,      0.0,     0.0,
                     h1/2.0,       l2/2.0,  l1/2.0,  -angle1,
                     h1/2.0,       l2/2.0,  l1/2.0,  -angle1 };
    float p_al2[] = {al_thick/2.0,      0.0,     0.0,
                     h2/2.0,       l3/2.0,  l2/2.0,  angle2,
                     h2/2.0,       l3/2.0,  l2/2.0,  angle2 };


    std::vector<double> paramC2A1;
    paramC2A1.push_back(al_thick*cm);
    paramC2A1.push_back(0.);
    paramC2A1.push_back(0.);
    paramC2A1.push_back(h1*cm);
    paramC2A1.push_back(l2*cm);
    paramC2A1.push_back(l1*cm);
    paramC2A1.push_back(-angle1*deg);
    paramC2A1.push_back(h1*cm);
    paramC2A1.push_back(l2*cm);
    paramC2A1.push_back(l1*cm);
    paramC2A1.push_back(-angle1*deg);

    std::vector<double> paramC2A2;
    paramC2A2.push_back(al_thick*cm);
    paramC2A2.push_back(0.);
    paramC2A2.push_back(0.);
    paramC2A2.push_back(h2*cm);
    paramC2A2.push_back(l3*cm);
    paramC2A2.push_back(l2*cm);
    paramC2A2.push_back(angle2*deg);
    paramC2A2.push_back(h2*cm);
    paramC2A2.push_back(l3*cm);
    paramC2A2.push_back(l2*cm);
    paramC2A2.push_back(angle2*deg);

    
//     GSVOLU("C2A1","TRAP",n_aluminium,
//            p_al1, sizeof(p_al1)/sizeof(float),ivol);
//     GSVOLU("C2A2","TRAP",n_aluminium,
//            p_al2, sizeof(p_al2)/sizeof(float),ivol);

    // c211, c212 - cc02 lead thickness 1mm
    float p_lead1mm_seg1[] = {pbsb1_thick/2.0,      0.0,     0.0,
                              h1/2.0,       l2/2.0,  l1/2.0,  -angle1,
                              h1/2.0,       l2/2.0,  l1/2.0,  -angle1 };
    float p_lead1mm_seg2[] = {pbsb1_thick/2.0,      0.0,     0.0,
                              h2/2.0,       l3/2.0,  l2/2.0,  angle2,
                              h2/2.0,       l3/2.0,  l2/2.0,  angle2 };

    std::vector<double> paramC211;
    paramC211.push_back(pbsb1_thick*cm);
    paramC211.push_back(0.);
    paramC211.push_back(0.);
    paramC211.push_back(h1*cm);
    paramC211.push_back(l2*cm);
    paramC211.push_back(l1*cm);
    paramC211.push_back(-angle1*deg);
    paramC211.push_back(h1*cm);
    paramC211.push_back(l2*cm);
    paramC211.push_back(l1*cm);
    paramC211.push_back(-angle1*deg);

    std::vector<double> paramC212;
    paramC212.push_back(pbsb1_thick*cm);
    paramC212.push_back(0.);
    paramC212.push_back(0.);
    paramC212.push_back(h2*cm);
    paramC212.push_back(l3*cm);
    paramC212.push_back(l2*cm);
    paramC212.push_back(angle2*deg);
    paramC212.push_back(h2*cm);
    paramC212.push_back(l3*cm);
    paramC212.push_back(l2*cm);
    paramC212.push_back(angle2*deg);
    
    // GSVOLU("C211","TRAP",n_lead_antimony,
//            p_lead1mm_seg1, sizeof(p_lead1mm_seg1)/sizeof(float),ivol);
//     GSVOLU("C212","TRAP",n_lead_antimony,
//            p_lead1mm_seg2, sizeof(p_lead1mm_seg2)/sizeof(float),ivol);

    

    // c221, c222 - cc02 lead thickness 2mm
    float p_lead2mm_seg1[] = {pbsb2_thick/2.0,      0.0,     0.0,
                              h1/2.0,       l2/2.0,  l1/2.0,  -angle1,
                              h1/2.0,       l2/2.0,  l1/2.0,  -angle1 };
    float p_lead2mm_seg2[] = {pbsb2_thick/2.0,      0.0,     0.0,
                              h2/2.0,       l3/2.0,  l2/2.0,  angle2,
                              h2/2.0,       l3/2.0,  l2/2.0,  angle2 };


    std::vector<double> paramC221;
    paramC221.push_back(pbsb2_thick*cm);
    paramC221.push_back(0.);
    paramC221.push_back(0.);
    paramC221.push_back(h1*cm);
    paramC221.push_back(l2*cm);
    paramC221.push_back(l1*cm);
    paramC221.push_back(-angle1*deg);
    paramC221.push_back(h1*cm);
    paramC221.push_back(l2*cm);
    paramC221.push_back(l1*cm);
    paramC221.push_back(-angle1*deg);

    std::vector<double> paramC222;
    paramC222.push_back(pbsb2_thick*cm);
    paramC222.push_back(0.);
    paramC222.push_back(0.);
    paramC222.push_back(h2*cm);
    paramC222.push_back(l3*cm);
    paramC222.push_back(l2*cm);
    paramC222.push_back(angle2*deg);
    paramC222.push_back(h2*cm);
    paramC222.push_back(l3*cm);
    paramC222.push_back(l2*cm);
    paramC222.push_back(angle2*deg);
    
//     GSVOLU("C221","TRAP",n_lead_antimony,
//            p_lead2mm_seg1, sizeof(p_lead2mm_seg1)/sizeof(float),ivol);
//     GSVOLU("C222","TRAP",n_lead_antimony,
//            p_lead2mm_seg2, sizeof(p_lead2mm_seg2)/sizeof(float),ivol);

    // c2b1, c2b2 - cc02 brass
    float p_brass1[] = {brass_thick/2.0,      0.0,     0.0,
                        h1/2.0,       l2/2.0,  l1/2.0,  -angle1,
                        h1/2.0,       l2/2.0,  l1/2.0,  -angle1 };
    float p_brass2[] = {brass_thick/2.0,      0.0,     0.0,
                        h2/2.0,       l3/2.0,  l2/2.0,  angle2,
                        h2/2.0,       l3/2.0,  l2/2.0,  angle2 };


    std::vector<double> paramC2B1;
    paramC2B1.push_back(brass_thick*cm);
    paramC2B1.push_back(0.);
    paramC2B1.push_back(0.);
    paramC2B1.push_back(h1*cm);
    paramC2B1.push_back(l2*cm);
    paramC2B1.push_back(l1*cm);
    paramC2B1.push_back(-angle1*deg);
    paramC2B1.push_back(h1*cm);
    paramC2B1.push_back(l2*cm);
    paramC2B1.push_back(l1*cm);
    paramC2B1.push_back(-angle1*deg);

    std::vector<double> paramC2B2;
    paramC2B2.push_back(brass_thick*cm);
    paramC2B2.push_back(0.);
    paramC2B2.push_back(0.);
    paramC2B2.push_back(h2*cm);
    paramC2B2.push_back(l3*cm);
    paramC2B2.push_back(l2*cm);
    paramC2B2.push_back(angle2*deg);
    paramC2B2.push_back(h2*cm);
    paramC2B2.push_back(l3*cm);
    paramC2B2.push_back(l2*cm);
    paramC2B2.push_back(angle2*deg);
    
//     GSVOLU("C2B1","TRAP",n_brass,
//            p_brass1, sizeof(p_brass1)/sizeof(float),ivol);
//     GSVOLU("C2B2","TRAP",n_brass,
//            p_brass2, sizeof(p_brass2)/sizeof(float),ivol);


    double x = 0.0;
    double y = 0.0;

    // Most Downstream Scintillator 
    double z = cc02_len/2.0 - scint_thick/2.0 - gap_scint;
    
    std::sprintf(nam,"C2S1");
    trapC2S1=new GsimTrap(std::string(nam),trapSEG1,
			  G4ThreeVector(x*cm,y*cm,z*cm),
			  G4ThreeVector(0,0,0) );
    trapC2S1->setParameters(paramC2S1);
    trapC2S1->setOuterColor("blue");
    trapC2S1->setSensitiveDetector("CC02",-1);
    trapSEG1->addDaughter(trapC2S1);


    std::sprintf(nam,"C2S2");
    trapC2S2=new GsimTrap(std::string(nam),trapSEG2,
			  G4ThreeVector(x*cm,y*cm,z*cm),
			  G4ThreeVector(0,0,0) );
    trapC2S2->setParameters(paramC2S2);
    trapC2S2->setOuterColor("blue");
    trapC2S2->setSensitiveDetector("CC02",-1);
    trapSEG2->addDaughter(trapC2S2);
	

    //GSPOS("C2S1",icp_scn1++,"SEG1",x, y, z, 0, "ONLY");
    //GSPOS("C2S2",icp_scn2++,"SEG2",x, y, z, 0, "ONLY");

    // Al support (downstream side )
    z -= (scint_thick/2.0 + al_thick/2.0);

    std::sprintf(nam,"C2A1");
    trapC2A1=new GsimTrap(std::string(nam),trapSEG1,
			  G4ThreeVector(x*cm,y*cm,z*cm),
			  G4ThreeVector(0,0,0) );
    trapC2A1->setParameters(paramC2A1);
    trapC2A1->setOuterMaterial("G4_Al");
    trapC2A1->setOuterColor("gray50");
    trapSEG1->addDaughter(trapC2A1);
    m_detList.push_back(trapC2A1);

    std::sprintf(nam,"C2A2");
    trapC2A2=new GsimTrap(std::string(nam),trapSEG2,
			  G4ThreeVector(x*cm,y*cm,z*cm),
			  G4ThreeVector(0,0,0) );
    trapC2A2->setParameters(paramC2A2);
    trapC2A2->setOuterMaterial("G4_Al");
    trapC2A2->setOuterColor("gray50");
    trapSEG2->addDaughter(trapC2A2);
    m_detList.push_back(trapC2A2);
    
    //GSPOS("C2A1",icp_al1++,"SEG1",x, y, z, 0, "ONLY");
    //GSPOS("C2A2",icp_al2++,"SEG2",x, y, z, 0, "ONLY");
    z -= al_thick/2.0;

    // downstream 7 layers (brass/1mm-lead/brass/scint...)

    for ( int i=0 ; i<7 ; i++) {
      z -= (scint_thick/2.0 + gap_scint);
      trapC2S1->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			      G4ThreeVector(0,0,0),-1);
      trapC2S2->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			      G4ThreeVector(0,0,0),-1);
      //GSPOS("C2S1",icp_scn1++,"SEG1",x, y, z, 0, "ONLY");
      //GSPOS("C2S2",icp_scn2++,"SEG2",x, y, z, 0, "ONLY");

      z -= ( scint_thick/2.0 + brass_thick/2.0 + gap_scint );
      
      if(!trapC2B1) {
	std::sprintf(nam,"C2B1");
	trapC2B1=new GsimTrap(std::string(nam),trapSEG1,
			      G4ThreeVector(x*cm,y*cm,z*cm),
			      G4ThreeVector(0,0,0) );
	trapC2B1->setParameters(paramC2B1);
	trapC2B1->setOuterMaterial("GsimBrass");
	trapC2B1->setOuterColor("green");
	trapSEG1->addDaughter(trapC2B1);
	m_detList.push_back(trapC2B1);
      } else {
	trapC2B1->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
				G4ThreeVector(0,0,0));
      }

      if(!trapC2B2) {
	std::sprintf(nam,"C2B2");
	trapC2B2=new GsimTrap(std::string(nam),trapSEG2,
			      G4ThreeVector(x*cm,y*cm,z*cm),
			      G4ThreeVector(0,0,0) );
	trapC2B2->setParameters(paramC2B2);
	trapC2B2->setOuterMaterial("GsimBrass");
	trapC2B2->setOuterColor("green");
	trapSEG2->addDaughter(trapC2B2);
	m_detList.push_back(trapC2B2);
      } else {
	trapC2B2->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
				G4ThreeVector(0,0,0));
      }
      //GSPOS("C2B1",icp_brass1++,"SEG1",x, y, z, 0, "ONLY");
      //GSPOS("C2B2",icp_brass2++,"SEG2",x, y, z, 0, "ONLY");

      z -= ( brass_thick/2.0 + pbsb1_thick/2.0);

      if(!trapC211) {
	std::sprintf(nam,"C211");
	trapC211=new GsimTrap(std::string(nam),trapSEG1,
			      G4ThreeVector(x*cm,y*cm,z*cm),
			      G4ThreeVector(0,0,0) );
	trapC211->setParameters(paramC211);
	trapC211->setOuterMaterial("GsimPbSb");
	trapC211->setOuterColor("gray70");
	trapSEG1->addDaughter(trapC211);
	m_detList.push_back(trapC211);
      } else {
	trapC211->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
				G4ThreeVector(0,0,0));
      }

      if(!trapC212) {
	std::sprintf(nam,"C212");
	trapC212=new GsimTrap(std::string(nam),trapSEG2,
			      G4ThreeVector(x*cm,y*cm,z*cm),
			      G4ThreeVector(0,0,0) );
	trapC212->setParameters(paramC212);
	trapC212->setOuterMaterial("GsimPbSb");
	trapC212->setOuterColor("gray70");
	trapSEG2->addDaughter(trapC212);
	m_detList.push_back(trapC212);
      } else {
	trapC212->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
				G4ThreeVector(0,0,0));
      }
      
      //GSPOS("C211",icp_lead1mm_seg1++,"SEG1",x, y, z, 0, "ONLY");
      //GSPOS("C212",icp_lead1mm_seg2++,"SEG2",x, y, z, 0, "ONLY");

      z -= ( pbsb1_thick/2.0 + brass_thick/2.0 );
      
      trapC2B1->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			      G4ThreeVector(0,0,0));
      trapC2B2->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			      G4ThreeVector(0,0,0));
      
      //GSPOS("C2B1",icp_brass1++,"SEG1",x, y, z, 0, "ONLY");
      //GSPOS("C2B2",icp_brass2++,"SEG2",x, y, z, 0, "ONLY");

      z -= brass_thick/2.0;
    }

//     // middle 29 layers (brass/2mm-lead/brass/scint...)      
    for ( int i=0 ; i<29 ; i++) {
      z -= (scint_thick/2.0 + gap_scint );

      trapC2S1->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			      G4ThreeVector(0,0,0),-1);
      trapC2S2->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			      G4ThreeVector(0,0,0),-1);
      
      // GSPOS("C2S1",icp_scn1++,"SEG1",x, y, z, 0, "ONLY");
//       GSPOS("C2S2",icp_scn2++,"SEG2",x, y, z, 0, "ONLY");

      z -= ( scint_thick/2.0 + brass_thick/2.0 + gap_scint  );

      trapC2B1->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			      G4ThreeVector(0,0,0));
      trapC2B2->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			      G4ThreeVector(0,0,0));
      // GSPOS("C2B1",icp_brass1++,"SEG1",x, y, z, 0, "ONLY");
//       GSPOS("C2B2",icp_brass2++,"SEG2",x, y, z, 0, "ONLY");

      z -= ( brass_thick/2.0 + pbsb2_thick/2.0);


      if(!trapC221) {
	std::sprintf(nam,"C221");
	trapC221=new GsimTrap(std::string(nam),trapSEG1,
			      G4ThreeVector(x*cm,y*cm,z*cm),
			      G4ThreeVector(0,0,0) );
	trapC221->setParameters(paramC221);
	trapC221->setOuterMaterial("GsimPbSb");
	trapC221->setOuterColor("gray70");
	trapSEG1->addDaughter(trapC221);
	m_detList.push_back(trapC221);
      } else {
	trapC221->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
				G4ThreeVector(0,0,0));
      }

      if(!trapC222) {
	std::sprintf(nam,"C222");
	trapC222=new GsimTrap(std::string(nam),trapSEG2,
			      G4ThreeVector(x*cm,y*cm,z*cm),
			      G4ThreeVector(0,0,0) );
	trapC222->setParameters(paramC222);
	trapC222->setOuterMaterial("GsimPbSb");
	trapC222->setOuterColor("gray70");
	trapSEG2->addDaughter(trapC222);
	m_detList.push_back(trapC222);
      } else {
	trapC222->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
				G4ThreeVector(0,0,0));
      }
      
      // GSPOS("C221",icp_lead2mm_seg1++,"SEG1",x, y, z, 0, "ONLY");
//       GSPOS("C222",icp_lead2mm_seg2++,"SEG2",x, y, z, 0, "ONLY");

      z -= ( pbsb2_thick/2.0 + brass_thick/2.0 );


      trapC2B1->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			      G4ThreeVector(0,0,0));
      trapC2B2->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			      G4ThreeVector(0,0,0));
      
      //GSPOS("C2B1",icp_brass1++,"SEG1",x, y, z, 0, "ONLY");
      //GSPOS("C2B2",icp_brass2++,"SEG2",x, y, z, 0, "ONLY");

      z -= brass_thick/2.0;
    }

//     // upstream 7 layers (brass/1mm-lead/brass/scint...)
    for ( int i=0 ; i<7 ; i++) {
      z -= (scint_thick/2.0 + gap_scint );
      trapC2S1->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			      G4ThreeVector(0,0,0),-1);
      trapC2S2->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			      G4ThreeVector(0,0,0),-1);
      //GSPOS("C2S1",icp_scn1++,"SEG1",x, y, z, 0, "ONLY");
      //GSPOS("C2S2",icp_scn2++,"SEG2",x, y, z, 0, "ONLY");

      z -= ( scint_thick/2.0 + brass_thick/2.0  + gap_scint);

      trapC2B1->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			      G4ThreeVector(0,0,0));
      trapC2B2->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			      G4ThreeVector(0,0,0));
      
      //GSPOS("C2B1",icp_brass1++,"SEG1",x, y, z, 0, "ONLY");
      //GSPOS("C2B2",icp_brass2++,"SEG2",x, y, z, 0, "ONLY");

      z -= ( brass_thick/2.0 + pbsb1_thick/2.0);
      trapC211->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			      G4ThreeVector(0,0,0));
      trapC212->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			      G4ThreeVector(0,0,0));
      //GSPOS("C211",icp_lead1mm_seg1++,"SEG1",x, y, z, 0, "ONLY");
      //GSPOS("C212",icp_lead1mm_seg2++,"SEG2",x, y, z, 0, "ONLY");

      z -= ( pbsb1_thick/2.0 + brass_thick/2.0 );
      trapC2B1->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			      G4ThreeVector(0,0,0));
      trapC2B2->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			      G4ThreeVector(0,0,0));
      //GSPOS("C2B1",icp_brass1++,"SEG1",x, y, z, 0, "ONLY");
      //GSPOS("C2B2",icp_brass2++,"SEG2",x, y, z, 0, "ONLY");

      z -= brass_thick/2.0;
    }
    // Al support (upstream side )
    z -= al_thick/2.0;
    trapC2A1->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			    G4ThreeVector(0,0,0));
    trapC2A2->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			    G4ThreeVector(0,0,0));
    
//     GSPOS("C2A1",icp_al1++,"SEG1",x, y, z, 0, "ONLY");
//     GSPOS("C2A2",icp_al2++,"SEG2",x, y, z, 0, "ONLY");

    // debug...
    //cout << " copy no.:" << icp_scn1 << " " << icp_scn2 << endl;
    //cout << " copy no.:" << icp_al1 << " " << icp_al2 << endl;
    //cout << " copy no.:" << icp_brass1 << " " << icp_brass2 << endl;
    //cout << " copy no.:" << icp_lead1mm_seg1 << " " 
    //     << icp_lead1mm_seg2 << endl;
    //cout << " copy no.:" << icp_lead2mm_seg1 << " " 
    //   << icp_lead2mm_seg2 << endl;
  }
  setThisAndDaughterBriefName("CC02");
}


GsimE391CC02::~GsimE391CC02()
{
  ;
}

void GsimE391CC02::setFastSimulationLevel(int level)
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
      (*it)->setSensitiveDetector("CC02",0);
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
