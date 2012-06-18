/**
 *  @file
 *  @brief  GsimE391Beamline
 *  $Id: $ 
 *  $Log: $
 */
#include "GsimE391Detector/GsimE391Beamline.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimDetector/GsimPolyhedra2.h"
#include "GsimDetector/GsimPolycone2.h"
#include "GsimDetector/GsimTrap.h"
#include "GsimDetector/GsimTube.h"
#include "GsimDetector/GsimBox.h"

GsimE391Beamline::GsimE391Beamline(std::string name,
				   GsimDetector* motherDetector,
				   G4ThreeVector transV,G4ThreeVector rotV,
				   int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{

  m_className = "GsimE391Beamline";

  double  shldc[9]={0., 360., 2,
		    80.,  10.01,  16., 
		    750.,  10.01,  16.};
  
  double  rcol1[20]={26.57, 26.01, 25.45, 24.88, 24.32,
		     23.76, 23.19, 22.63, 22.07, 21.51,
		     20.94, 20.38, 19.82, 19.25, 18.69,
		     18.13, 17.56, 17.00, 16.44, 15.88 };

  double  rcol2[13]={9.4,  9.6,  9.8, 10.0, 10.2, 
		     10.4, 10.6, 10.8, 11.0, 11.2,
		     11.4, 11.6, 11.8};

  double  rcol3[35]={12.8, 13.0, 13.2, 13.4, 13.6, 
		     13.8, 14.0, 14.2, 14.4, 14.6, 
		     14.8, 15.0, 15.2, 15.4, 15.6, 
		     15.8, 16.0, 16.2, 16.4, 16.6, 
		     16.8, 17.0, 17.2, 17.4, 17.6, 
		     17.8, 18.0, 18.2, 18.4, 18.6, 
		     18.8, 19.0, 19.2, 19.4, 19.6};

  double  rcol5[18]={35.44, 35.72, 36.01, 36.30, 36.59, 
		     36.88, 37.16, 37.45, 37.74, 38.03, 
		     38.32, 38.60, 38.89, 39.18, 39.47, 
		     39.76, 40.04, 40.33};

  double  rcol6[11]={43.20, 43.80, 44.10, 44.40, 44.70, 
		     44.90, 45.20, 45.50, 45.80, 46.10, 
		     46.40};

  double  rcol6w[13]={47.10, 47.40, 47.80, 48.20,
		      49.00, 49.30, 49.70, 50.10,
		      50.50, 51.20, 51.60, 52.00,
		      52.40};

  double  rcol6s[14]={47.10, 47.40, 47.80, 48.20, 
		      49.00, 49.30, 49.70, 50.10, 50.50, 
		      51.20, 51.60, 52.00, 52.40, 
		      53.00};


  double par[20], x,y,z;
  int i,c;

  GsimTube* tube=0;
  GsimTube* tube2=0; 
  char nam[100];
  std::vector<double> paramVec;

  par[0]=0.;
  par[1]=110.;
  par[2]=700.;
  paramVec.clear();
  paramVec.push_back(par[0]*cm);
  paramVec.push_back(par[1]*cm);
  paramVec.push_back(par[2]*2.*cm);
  paramVec.push_back(0.);
  paramVec.push_back(360.*deg);
  std::sprintf(nam,"MOTH");
  GsimTube* moth = new GsimTube(std::string(nam),this,
				G4ThreeVector(0*cm,0*cm,500*cm),
				G4ThreeVector(0,0,0));
  moth->setOuterMaterial("G4_Galactic");
  moth->setParameters(paramVec);
  moth->setOuterColor("gray70");
  addDaughter(moth);
  
  
  {
    par[0] = 6.01;
    par[1] = 100.0;
    par[2] = ((760.0-80.0)/2.0+3.0);
    x = 0.;
    y = 0.;
    z = -500. + par[2]+70.0-6.0;
    
    paramVec.clear();
    paramVec.push_back(par[0]*cm);
    paramVec.push_back(par[1]*cm);
    paramVec.push_back(par[2]*2.*cm);
    paramVec.push_back(0.);
    paramVec.push_back(360.*deg);
    
    std::sprintf(nam,"SHLD");
    tube = new GsimTube(std::string(nam),moth,
			G4ThreeVector(x*cm,y*cm,z*cm),
			G4ThreeVector(0,0,0));
    tube->setOuterMaterial("G4_AIR");
    tube->setParameters(paramVec);
    tube->setOuterColor("gray70");
    moth->addDaughter(tube);
  }

  
  par[0]=0.;
  par[1]=6.;
  par[2]=(300.-65.)/2.;
  
  x = 0.;
  y = 0.;
  z = -500 + 65 + par[2];
  
  
  paramVec.clear();
  paramVec.push_back(par[0]*cm);
  paramVec.push_back(par[1]*cm);
  paramVec.push_back(par[2]*2.*cm);
  paramVec.push_back(0.);
  paramVec.push_back(360.*deg);
  
  std::sprintf(nam,"MF1");
  GsimTube* mf1 = new GsimTube(std::string(nam),moth,
			       G4ThreeVector(x*cm,y*cm,z*cm),
			       G4ThreeVector(0,0,0));
  mf1->setOuterMaterial("G4_AIR");
  mf1->setParameters(paramVec);
  mf1->setOuterColor("gray70");
  moth->addDaughter(mf1);

//   const char* nl[6] = {"C1WB","C2WB","C3WB","C4WB","C5WB","C6SB"};
//   const char* ml[6] = {"G4_W","G4_W","G4_W","G4_W","G4_W","G4_PLASTIC_SC_VINYLTOLUENE"};
//   for(int i=0;i<6;i++) {
//     std::sprintf(nam,nl[i]);
//     tube = new GsimTube(std::string(nam),moth,
// 			G4ThreeVector(x*cm,y*cm,z*cm),
// 			G4ThreeVector(0,0,0));
//     tube->setOuterMaterial(ml[i]);
//     tube->setParameters(paramVec);
//     tube->setOuterColor("gray70");
//     moth->addDaughter(tube);
//   }
    
  

  //------------- Collimator_1 ---------------------
  par[0] = 0.;
  par[1] = 4./2.;
  par[2] = 100./2.;
  x = 0;
  y = 0;
  z = -65.-(300.-65.)/2. + 80 + par[2] ;

  paramVec.clear();
  paramVec.push_back(par[0]*cm);
  paramVec.push_back(par[1]*cm);
  paramVec.push_back(par[2]*2.*cm);
  paramVec.push_back(0.);
  paramVec.push_back(360.*deg);
  
  std::sprintf(nam,"COL1");
  GsimTube* col1 = new GsimTube(std::string(nam),mf1,
				G4ThreeVector(x*cm,y*cm,z*cm),
				G4ThreeVector(0,0,0));
  col1->setOuterMaterial("G4_AIR");
  col1->setParameters(paramVec);
  col1->setOuterColor("gray70");
  mf1->addDaughter(col1);
  
  //     shield of outside of Tungsten collimator 
  par[0] = 4./2.0;
  par[1] = 6.0;
  par[2] = 100./2.;
  x = 0;
  y = 0;
  z = -65.-(300.-65.)/2. + 80 + par[2] ;

  paramVec.clear();
  paramVec.push_back(par[0]*cm);
  paramVec.push_back(par[1]*cm);
  paramVec.push_back(par[2]*2.*cm);
  paramVec.push_back(0.);
  paramVec.push_back(360.*deg);
  
  std::sprintf(nam,"C1SH");
  tube = new GsimTube(std::string(nam),mf1,
		      G4ThreeVector(x*cm,y*cm,z*cm),
		      G4ThreeVector(0,0,0));
  tube->setOuterMaterial("G4_Fe");
  tube->setParameters(paramVec);
  tube->setOuterColor("gray70");
  mf1->addDaughter(tube);

  for(int i=1;i<=20;i++) {
    par[0] = rcol1[i-1]/20.;     // mm->cm
    par[1] = 4./2.;
    par[2] = 3.5/2.;
    x = 0.;
    y = 0.;
    z = -100./2. + 5.*i - par[2];

    paramVec.clear();
    paramVec.push_back(par[0]*cm);
    paramVec.push_back(par[1]*cm);
    paramVec.push_back(par[2]*2.*cm);
    paramVec.push_back(0.);
    paramVec.push_back(360.*deg);

    std::sprintf(nam,"C1WB_%d",i);
    tube = new GsimTube(std::string(nam),col1,
			G4ThreeVector(x*cm,y*cm,z*cm),
			G4ThreeVector(0,0,0));
    tube->setOuterMaterial("G4_W");
    tube->setParameters(paramVec);
    tube->setOuterColor("gray70");
    col1->addDaughter(tube);
  }



  // ---------- Air between Collimator 1 and 2------------------
  par[0] = 0.;
  par[1] = 6.;
  par[2] = 50./2.;
  x=0.0;
  y=0.;
  z = 22.5;

  paramVec.clear();
  paramVec.push_back(par[0]*cm);
  paramVec.push_back(par[1]*cm);
  paramVec.push_back(par[2]*2.*cm);
  paramVec.push_back(0.);
  paramVec.push_back(360.*deg);
  std::sprintf(nam,"C12A");
  GsimTube* c12a = new GsimTube(std::string(nam),mf1,
				G4ThreeVector(x*cm,y*cm,z*cm),
				G4ThreeVector(0,0,0));
  c12a->setOuterMaterial("G4_AIR");
  c12a->setParameters(paramVec);
  c12a->setOuterColor("gray70");
  mf1->addDaughter(c12a);
  
  // ----- Be_lod--------
  {
    par[0] = 0.;
    par[1] = 1./2.;
    par[2] = 30./2.;
    x = 0;
    y = 0;
    z = -5.5; // in C12A

    paramVec.clear();
    paramVec.push_back(par[0]*cm);
    paramVec.push_back(par[1]*cm);
    paramVec.push_back(par[2]*2.*cm);
    paramVec.push_back(0.);
    paramVec.push_back(360.*deg);
    std::sprintf(nam,"BELD");
    tube = new GsimTube(std::string(nam),c12a,
			G4ThreeVector(x*cm,y*cm,z*cm),
			G4ThreeVector(0,0,0));
    tube->setOuterMaterial("G4_Be");
    tube->setParameters(paramVec);
    tube->setOuterColor("gray70");
    c12a->addDaughter(tube);
  }
      
  // ----- Pb_lod ------
  {
    par[0] = 0.;
    par[1] = 1./2.;
    par[2] = 5./2.;
    x = 0;
    y = 0;
    z = 17.5;

    paramVec.clear();
    paramVec.push_back(par[0]*cm);
    paramVec.push_back(par[1]*cm);
    paramVec.push_back(par[2]*2.*cm);
    paramVec.push_back(0.);
    paramVec.push_back(360.*deg);
    std::sprintf(nam,"PBLD");
    tube = new GsimTube(std::string(nam),c12a,
			G4ThreeVector(x*cm,y*cm,z*cm),
			G4ThreeVector(0,0,0));
    tube->setOuterMaterial("G4_Pb");
    tube->setParameters(paramVec);
    tube->setOuterColor("gray70");
    c12a->addDaughter(tube);
  }



  // ---------- Collimator_2------------------
  par[0] = 0.;
  par[1] = 4./2.;
  par[2] = 70./2.;
  x = 0;
  y = 0;
  z = -65.-(300.-65.)/2. + 80 + 100 + 50 + par[2];

  paramVec.clear();
  paramVec.push_back(par[0]*cm);
  paramVec.push_back(par[1]*cm);
  paramVec.push_back(par[2]*2.*cm);
  paramVec.push_back(0.);
  paramVec.push_back(360.*deg);
  std::sprintf(nam,"COL2");
  GsimTube* col2 = new GsimTube(std::string(nam),mf1,
				G4ThreeVector(x*cm,y*cm,z*cm),
				G4ThreeVector(0,0,0));
  col2->setOuterMaterial("G4_AIR");
  col2->setParameters(paramVec);
  col2->setOuterColor("gray70");
  mf1->addDaughter(col2);
    
  //     IRON shield outside of collimator2
  par[0] = 4./2.;
  par[1] = 6.;
  par[2] = 70./2.;
  x = 0;
  y = 0;
  z = -65.-(300.-65.)/2. + 80 + 100 + 50 + par[2];

  paramVec.clear();
  paramVec.push_back(par[0]*cm);
  paramVec.push_back(par[1]*cm);
  paramVec.push_back(par[2]*2.*cm);
  paramVec.push_back(0.);
  paramVec.push_back(360.*deg);
  std::sprintf(nam,"C2SH");
  tube = new GsimTube(std::string(nam),mf1,
		      G4ThreeVector(x*cm,y*cm,z*cm),
		      G4ThreeVector(0,0,0));
  tube->setOuterMaterial("G4_Fe");
  tube->setParameters(paramVec);
  tube->setOuterColor("gray70");
  mf1->addDaughter(tube);

  
  for(int i=1;i<=13;i++) {
    par[0] = rcol2[i-1]/20.;  // mm->cm
    par[1] = 4./2.;
    par[2] = 5./2.;
    x = 0.;
    y = 0.;
    z = -70./2. + 5.*i - par[2];


    paramVec.clear();
    paramVec.push_back(par[0]*cm);
    paramVec.push_back(par[1]*cm);
    paramVec.push_back(par[2]*2.*cm);
    paramVec.push_back(0.);
    paramVec.push_back(360.*deg);
    std::sprintf(nam,"C2WB_%d",i);
    tube = new GsimTube(std::string(nam),col2,
			G4ThreeVector(x*cm,y*cm,z*cm),
			G4ThreeVector(0,0,0));
    tube->setOuterMaterial("G4_W");
    tube->setParameters(paramVec);
    tube->setOuterColor("gray70");
    col2->addDaughter(tube);
  }
      
  //-------- Collimator_3----------------------------
  par[0] = 0.;
  par[1] = 5./2.;
  par[2] = 185./2.;
  x = 0;
  y = 0;
  z = -500 + 80 + 100 + 50 + 70 + 10 + par[2];

  paramVec.clear();
  paramVec.push_back(par[0]*cm);
  paramVec.push_back(par[1]*cm);
  paramVec.push_back(par[2]*2.*cm);
  paramVec.push_back(0.);
  paramVec.push_back(360.*deg);
  std::sprintf(nam,"COL3");
  GsimTube* col3 = new GsimTube(std::string(nam),moth,
				G4ThreeVector(x*cm,y*cm,z*cm),
				G4ThreeVector(0,0,0));
  col3->setOuterMaterial("G4_AIR");
  col3->setParameters(paramVec);
  col3->setOuterColor("gray70");
  moth->addDaughter(col3);

  par[0] = 5./2.;
  par[1] = 6.;
  par[2] = 185./2.;
  x = 0;
  y = 0;
  z = -500 + 80 + 100 + 50 + 70 + 10 + par[2];

  paramVec.clear();
  paramVec.push_back(par[0]*cm);
  paramVec.push_back(par[1]*cm);
  paramVec.push_back(par[2]*2.*cm);
  paramVec.push_back(0.);
  paramVec.push_back(360.*deg);
  std::sprintf(nam,"C3SH");
  tube = new GsimTube(std::string(nam),moth,
		      G4ThreeVector(x*cm,y*cm,z*cm),
		      G4ThreeVector(0,0,0));
  tube->setOuterMaterial("G4_Fe");
  tube->setParameters(paramVec);
  tube->setOuterColor("gray70");
  moth->addDaughter(tube);
      
  for(int i=1;i<=35;i++) {
    par[0] = rcol3[i-1]/20.;  // mm->cm
    par[1] = 5./2.;
    par[2] = 5./2.;
    x = 0.;
    y = 0.;
    z = -185./2. + 5. + 5.*i - par[2];

    paramVec.clear();
    paramVec.push_back(par[0]*cm);
    paramVec.push_back(par[1]*cm);
    paramVec.push_back(par[2]*2.*cm);
    paramVec.push_back(0.);
    paramVec.push_back(360.*deg);
    std::sprintf(nam,"C3WB_%d",i);
    tube = new GsimTube(std::string(nam),col3,
			G4ThreeVector(x*cm,y*cm,z*cm),
			G4ThreeVector(0,0,0));
    tube->setOuterMaterial("G4_W");
    tube->setParameters(paramVec);
    tube->setOuterColor("gray70");
    col3->addDaughter(tube);
  }


  //  --------------- Collimator 4----------------------
  // Air with Magnetic field 2
  // Vacuum with Magnetic field 2
  par[0]=0.;
  par[1]=12.0/2.0;
  par[2]=255./2.;
  x = 0.;
  y = 0.;
  z = -500. + 495. + par[2];


  paramVec.clear();
  paramVec.push_back(par[0]*cm);
  paramVec.push_back(par[1]*cm);
  paramVec.push_back(par[2]*2.*cm);
  paramVec.push_back(0.);
  paramVec.push_back(360.*deg);
  std::sprintf(nam,"MF2");
  GsimTube* mf2 = new GsimTube(std::string(nam),moth,
			       G4ThreeVector(x*cm,y*cm,z*cm),
			       G4ThreeVector(0,0,0));
  mf2->setOuterMaterial("G4_Galactic");
  mf2->setParameters(paramVec);
  mf2->setOuterColor("gray70");
  moth->addDaughter(mf2);
  

  //     collimator 4 in Vacuum with Magnetic field

  
  

  
  

  x = 0.;
  y = 0.;
  z =  -255./2. + 50.;   // in MF2 coordinate
      
  for(int i=1;i<=29;i++) {
    z=z+5.;
    if(i==1) {
      par[0]=4.0;
      par[1]=6.0;
      par[2]=5.0/2.0;

      paramVec.clear();
      paramVec.push_back(par[0]*cm);
      paramVec.push_back(par[1]*cm);
      paramVec.push_back(par[2]*2.*cm);
      paramVec.push_back(0.);
      paramVec.push_back(360.*deg);
      std::sprintf(nam,"C4OU");
      tube = new GsimTube(std::string(nam),mf2,
			  G4ThreeVector(x*cm,y*cm,z*cm),
			  G4ThreeVector(0,0,0));
      tube->setOuterMaterial("G4_Fe");
      tube->setParameters(paramVec);
      tube->setOuterColor("gray70");
      mf2->addDaughter(tube);
    } else {
      tube->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			  G4ThreeVector(0,0,0),i-1);
    }

    double zb=z+2.5/2.0;
    if(i==1) {
      par[0]=2.3;
      par[1]=4.0;
      par[2]=2.5/2.0;

      paramVec.clear();
      paramVec.push_back(par[0]*cm);
      paramVec.push_back(par[1]*cm);
      paramVec.push_back(par[2]*2.*cm);
      paramVec.push_back(0.);
      paramVec.push_back(360.*deg);
      std::sprintf(nam,"C4IN");
      tube2 = new GsimTube(std::string(nam),mf2,
			   G4ThreeVector(x*cm,y*cm,zb*cm),
			   G4ThreeVector(0,0,0));
      tube2->setOuterMaterial("G4_Fe");
      tube2->setParameters(paramVec);
      tube2->setOuterColor("gray70");
      mf2->addDaughter(tube2);
    } else {
      tube2->cloneDetector(G4ThreeVector(x*cm,y*cm,zb*cm),
			   G4ThreeVector(0,0,0),i-1);
    }
  }

  // Vacuum chamber (SUS)
  {
    par[0]=0.;//sphi
    par[1]=360.;//oa
    par[2]=2;//nzplane
    par[3]=-0.01/2.;//z1
    par[4]=0.;//minir
    par[5]=5./2.;//maxr
    par[6]=0.01/2.;//z2
    par[7]=0.;//minr
    par[8]=5./2.;//maxr
    x = 0.;
    y = 0.;
    z = -495.-255./2. + 495. + 0.01/2. + 5.0;

    paramVec.clear();
    paramVec.push_back(par[0]*deg);
    paramVec.push_back(par[1]*deg);
    paramVec.push_back(par[3]*cm);
    paramVec.push_back(par[4]*cm);
    paramVec.push_back(par[5]*cm);
    paramVec.push_back(par[7]*cm);
    paramVec.push_back(par[8]*cm);
    std::sprintf(nam,"VCH1");
    GsimPolycone2* pc = new GsimPolycone2(std::string(nam),mf2,
					  G4ThreeVector(x*cm,y*cm,z*cm),
					  G4ThreeVector(0,0,0));
    pc->setOuterMaterial("G4_Fe");
    pc->setParameters(paramVec);
    pc->setOuterColor("gray70");
    mf2->addDaughter(pc);
  }

  // Collimator_5
  par[0] = 0.;
  par[1] = 8./2.;
  par[2] = 100./2.;
  
  x = 0;
  y = 0;
  z = -500 + 80 + 100 + 50 + 70 + 10 + 185 + 255 + par[2];


  paramVec.clear();
  paramVec.push_back(par[0]*cm);
  paramVec.push_back(par[1]*cm);
  paramVec.push_back(par[2]*2.*cm);
  paramVec.push_back(0.);
  paramVec.push_back(360.*deg);
  std::sprintf(nam,"COL5");
  GsimTube* col5 = new GsimTube(std::string(nam),moth,
				G4ThreeVector(x*cm,y*cm,z*cm),
				G4ThreeVector(0,0,0));
  col5->setOuterMaterial("G4_Galactic");
  col5->setParameters(paramVec);
  col5->setOuterColor("gray70");
  moth->addDaughter(col5);
      
  par[0] = 8./2.;
  par[1] = 100.;
  par[2] = 100./2.;
  x = 0;
  y = 0;
  z = -500 + 80 + 100 + 50 + 70 + 10 + 185 + 255 + par[2];

  paramVec.clear();
  paramVec.push_back(par[0]*cm);
  paramVec.push_back(par[1]*cm);
  paramVec.push_back(par[2]*2.*cm);
  paramVec.push_back(0.);
  paramVec.push_back(360.*deg);
  std::sprintf(nam,"C5SH");
  tube = new GsimTube(std::string(nam),moth,
		      G4ThreeVector(x*cm,y*cm,z*cm),
		      G4ThreeVector(0,0,0));
  tube->setOuterMaterial("G4_Fe");
  tube->setParameters(paramVec);
  tube->setOuterColor("gray70");
  moth->addDaughter(tube);

  for(int i=1;i<=18;i++) {
    par[0] = rcol5[i-1]/20.;  // mm->cm
    par[1] = 8./2.;
    par[2] = 5./2.;
    x = 0.;
    y = 0.;
    z = -100./2. + 5. + 5.*i - par[2];

    paramVec.clear();
    paramVec.push_back(par[0]*cm);
    paramVec.push_back(par[1]*cm);
    paramVec.push_back(par[2]*2.*cm);
    paramVec.push_back(0.);
    paramVec.push_back(360.*deg);
    std::sprintf(nam,"C5WB_%d",i);
    tube = new GsimTube(std::string(nam),col5,
			G4ThreeVector(x*cm,y*cm,z*cm),
			G4ThreeVector(0,0,0));
    tube->setOuterMaterial("G4_W");
    tube->setParameters(paramVec);
    tube->setOuterColor("gray70");
    col5->addDaughter(tube);
  }

  //     shield between C5 and C6
  par[0] = 12./2.;
  par[1] = 100.;
  par[2] = 40./2.;
  x = 0;
  y = 0;
  z = -500 + (890.+850.)/2.0;

  paramVec.clear();
  paramVec.push_back(par[0]*cm);
  paramVec.push_back(par[1]*cm);
  paramVec.push_back(par[2]*2.*cm);
  paramVec.push_back(0.);
  paramVec.push_back(360.*deg);
  std::sprintf(nam,"C56S");
  tube = new GsimTube(std::string(nam),moth,
		      G4ThreeVector(x*cm,y*cm,z*cm),
		      G4ThreeVector(0,0,0));
  tube->setOuterMaterial("G4_Fe");
  tube->setParameters(paramVec);
  tube->setOuterColor("gray70");
  moth->addDaughter(tube);
  
  // Collimator_6
  par[0] = 0.;
  par[1] = 12./2.;
  par[2] = 105./2.;
  
  x = 0;
  y = 0;
  z = -500 + 80 + 100 + 50 + 70 + 10 + 185 + 255 
    + 100 + 40 + par[2];
  
  paramVec.clear();
  paramVec.push_back(par[0]*cm);
  paramVec.push_back(par[1]*cm);
  paramVec.push_back(par[2]*2.*cm);
  paramVec.push_back(0.);
  paramVec.push_back(360.*deg);
  std::sprintf(nam,"COL6");
  GsimTube* col6 = new GsimTube(std::string(nam),moth,
				G4ThreeVector(x*cm,y*cm,z*cm),
				G4ThreeVector(0,0,0));
  col6->setOuterMaterial("G4_Galactic");
  col6->setParameters(paramVec);
  col6->setOuterColor("gray70");
  moth->addDaughter(col6);
  
  //        --- Iron shield outside of tungsten  --
  par[0] = 12./2.;
  par[1] = 100.;
  par[2] = 105./2.;
  x = 0.;
  y = 0.;
  z = -500 + 80 + 100 + 50 + 70 + 10 + 185 + 255 
    + 100 + 40 + par[2];

  paramVec.clear();
  paramVec.push_back(par[0]*cm);
  paramVec.push_back(par[1]*cm);
  paramVec.push_back(par[2]*2.*cm);
  paramVec.push_back(0.);
  paramVec.push_back(360.*deg);
  std::sprintf(nam,"C6SH");
  tube = new GsimTube(std::string(nam),moth,
		      G4ThreeVector(x*cm,y*cm,z*cm),
		      G4ThreeVector(0,0,0));
  tube->setOuterMaterial("G4_Fe");
  tube->setParameters(paramVec);
  tube->setOuterColor("gray70");
  moth->addDaughter(tube);
  
  //     -- shield --
  
  
      
  for(int i=1;i<=11;i++) {
    par[0] = rcol6[i-1]/20.;  // mm->cm
    par[1] = 9./2.;
    par[2] = 5./2.;
    x = 0.;
    y = 0.;
    z = -105./2. + 5. + 5.*i - par[2];
      
    paramVec.clear();
    paramVec.push_back(par[0]*cm);
    paramVec.push_back(par[1]*cm);
    paramVec.push_back(par[2]*2.*cm);
    paramVec.push_back(0.);
    paramVec.push_back(360.*deg);
    std::sprintf(nam,"C6WB_%d",i);
    tube = new GsimTube(std::string(nam),col6,
			G4ThreeVector(x*cm,y*cm,z*cm),
			G4ThreeVector(0,0,0));
    tube->setOuterMaterial("G4_W");
    tube->setParameters(paramVec);
    tube->setOuterColor("gray70");
    col6->addDaughter(tube);
    

    //        -- shield --
    
    x = 0.;
    y = 0.;
    z = -105./2. + 5. + 5.*i - par[2];
    

    if(i==1) {
      par[0] = 9./2.;
      par[1] = 12./2.;
      par[2] = 5./2.;
      paramVec.clear();
      paramVec.push_back(par[0]*cm);
      paramVec.push_back(par[1]*cm);
      paramVec.push_back(par[2]*2.*cm);
      paramVec.push_back(0.);
      paramVec.push_back(360.*deg);
      std::sprintf(nam,"C6S1");
      tube2 = new GsimTube(std::string(nam),col6,
			   G4ThreeVector(x*cm,y*cm,z*cm),
			   G4ThreeVector(0,0,0));
      tube2->setOuterMaterial("G4_Fe");
      tube2->setParameters(paramVec);
      tube2->setOuterColor("gray70");
      col6->addDaughter(tube2);
    }  else {
      tube2->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			   G4ThreeVector(0,0,0),i-1);
    }
  }


  // col6 tungsten2

  for(int i=1;i<=13;i++) {
    par[0] = rcol6w[i-1]/20.;  // mm->cm
    par[1] = 10.8/2.;
    par[2] = 2./2.;
    x = 0.;
    y = 0.;
    z = -105./2. + 60 + 3.0*(i-1) + par[2] + 1.0;


    paramVec.clear();
    paramVec.push_back(par[0]*cm);
    paramVec.push_back(par[1]*cm);
    paramVec.push_back(par[2]*2.*cm);
    paramVec.push_back(0.);
    paramVec.push_back(360.*deg);
    std::sprintf(nam,"C6WB_%d",i+11);
    tube = new GsimTube(std::string(nam),col6,
			G4ThreeVector(x*cm,y*cm,z*cm),
			G4ThreeVector(0,0,0));
    tube->setOuterMaterial("G4_W");
    tube->setParameters(paramVec);
    tube->setOuterColor("gray70");
    col6->addDaughter(tube);
  }


  // col6 scintillator
  for(int i=1;i<=14;i++) {
    par[0] = rcol6s[i-1]/20.;  // mm->cm
    par[1] = 10.8/2.;
    par[2] = 1.0/2.;
    x = 0.;
    y = 0.;
    z = -105./2. + 60 + 3.0*(i-1) - par[2] + 1.0;


    paramVec.clear();
    paramVec.push_back(par[0]*cm);
    paramVec.push_back(par[1]*cm);
    paramVec.push_back(par[2]*2.*cm);
    paramVec.push_back(0.);
    paramVec.push_back(360.*deg);
    std::sprintf(nam,"C6SB_%d",i+11);
    tube = new GsimTube(std::string(nam),col6,
			G4ThreeVector(x*cm,y*cm,z*cm),
			G4ThreeVector(0,0,0));
    tube->setOuterMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    tube->setParameters(paramVec);
    tube->setOuterColor("gray70");
    col6->addDaughter(tube);
  }

  {
    // Hodoscope
    par[0]=0.;
    par[1]=100.;
    par[2]=1./2.;
    x = 0.;
    y = 0.;
    z = -500. + 995. + 1. + par[2];

    paramVec.clear();
    paramVec.push_back(par[0]*cm);
    paramVec.push_back(par[1]*cm);
    paramVec.push_back(par[2]*2.*cm);
    paramVec.push_back(0.);
    paramVec.push_back(360.*deg);
    std::sprintf(nam,"HDSC");
    tube = new GsimTube(std::string(nam),moth,
			G4ThreeVector(x*cm,y*cm,z*cm),
			G4ThreeVector(0,0,0));
    tube->setOuterMaterial("G4_AIR");
    tube->setParameters(paramVec);
    tube->setOuterColor("gray70");
    moth->addDaughter(tube);
  }

  mf1->setThisAndDaughterMagneticField(G4ThreeVector(0,0,-20*kilogauss));
  mf2->setThisAndDaughterMagneticField(G4ThreeVector(0,0,-20*kilogauss));

  setThisAndDaughterBriefName("Beamline");
  update();

}


GsimE391Beamline::~GsimE391Beamline()
{
  ;
}

void GsimE391Beamline::setFastSimulationLevel(int level)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif 
}



