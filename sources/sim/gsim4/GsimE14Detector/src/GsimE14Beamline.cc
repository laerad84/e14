/**
 *  @file
 *  @brief  GsimE14Beamline
 *  $Id: $ 
 *  $Log:$
 */
#include "GsimE14Detector/GsimE14Beamline.h"
#include "GsimE14Detector/GsimE14UserGeom.h"
#include "GsimPersistency/GsimMessage.h"

#include "GsimDetector/GsimTube.h"
#include "GsimDetector/GsimBox.h"

using namespace E14;

GsimE14Beamline::GsimE14Beamline(std::string name,
				 GsimDetector* motherDetector,
				 G4ThreeVector transV,G4ThreeVector rotV,
				 int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{

  m_className = "GsimE14Beamline";
  
  G4bool ON = true;
  G4bool OFF = false;
  
  G4bool flag_vwin_t1  = OFF;
  G4bool flag_t1_air   = ON; 
  //G4bool flag_t1_air   = OFF;
  G4bool flag_c1       = OFF;
  G4bool flag_d1       = OFF;
  G4bool flag_wall     = OFF;
  G4bool flag_flange   = OFF;
  G4bool flag_q1       = OFF;
  G4bool flag_gabs_mag = OFF;
  G4bool flag_q1_air   = ON; 
  //G4bool flag_q1_air   = OFF;
  if ( flag_gabs_mag) flag_q1_air = OFF;
  
  G4bool flag_gabs     = ON;
  //G4bool flag_gabs     = OFF;
  G4bool flag_femag_gabs     = OFF;
  G4bool flag_gabs_air = OFF; //
  
  G4bool flag_q2        = OFF;
  G4bool flag_q2_air    = ON; 
  //G4bool flag_q2_air    = OFF;
  G4bool flag_q1q2duct1 = OFF;
  G4bool flag_d2duct    = OFF;
  G4bool flag_d2        = OFF;
  G4bool flag_vwin_kl   = OFF;
  G4bool flag_air_K11q2duct_vwin = ON; 
  //G4bool flag_air_K11q2duct_vwin = OFF;
  
  G4bool flag_KL_magnet         = ON;
  G4bool flag_KL_magnetic_field = ON;
  
  
  //---------------------------------------------
  // ALL Materials betw. T1 and KL collimator ON
  //---------------------------------------------
  // G4bool ALL_ON = false;
  G4bool ALL_ON = true;
  
  if ( ALL_ON ) {
    
    flag_vwin_t1  = ON;
    flag_t1_air   = ON;
    flag_c1       = ON;
    flag_d1       = ON;
    flag_wall     = ON;
    flag_flange   = ON;
    flag_q1       = ON;
    flag_gabs_mag = OFF;
    flag_q1_air   = ON;
    if ( flag_gabs_mag) flag_q1_air = OFF;
    
    flag_gabs     = ON;
    flag_gabs_air = OFF;
    flag_femag_gabs = OFF;
    
    flag_q2        = ON;
    flag_q2_air    = ON;
    flag_q1q2duct1 = ON;
    flag_d2duct = ON;
    flag_d2        = ON;
    flag_vwin_kl   = ON;
    flag_air_K11q2duct_vwin = ON;
    
    
    flag_KL_magnet         = ON;
    flag_KL_magnetic_field = ON;
    
  }    
  
  G4bool flag_output_error    = OFF;
  G4bool flag_machining_error = OFF;


  G4cout << " --------------------------------------------" << G4endl;
  G4cout << " Geometry Description (1=ON,0=OFF)  " << G4endl;
  G4cout << "    T1 Vacuum Windosw(Be)       : " << flag_vwin_t1 <<  G4endl; 
  G4cout << "    T1 Air Volume               : " <<  flag_t1_air <<  G4endl;
  G4cout << "    T1-1st Collimator (Cu)      : " << flag_c1  <<  G4endl;
  G4cout << "    K1.1D1 yoke (Fe)            : " << flag_d1  <<  G4endl;
  G4cout << "    Wall of Vacuum chamber(SUS) : " << flag_wall  <<  G4endl;
  G4cout << "    Flange of K1.1Q1Q2duct(SUS) : " << flag_flange  <<  G4endl;
  G4cout << "    K1.1Q1 yoke or coil (Cu)    : " << flag_q1  <<  G4endl;
  G4cout << "    K1.1Q1 Air                  : " << flag_q1_air  <<  G4endl;
  G4cout << "    Gamma absorber (Pb)         : " << flag_gabs  <<  G4endl;
  G4cout << "    K1.1Q2 yoke or coil (Cu)    : " << flag_q2  <<  G4endl;
  G4cout << "    K1.1Q2 Air                  : " << flag_q2_air  <<  G4endl;
  G4cout << "    Mag field before absorber   : " << flag_gabs_mag  <<  G4endl;
  G4cout << "    K1.1 Q1Q2 duct (SUS)        : " << flag_q1q2duct1 <<  G4endl;
  G4cout << "    K1.1 D2 duct (SUS)          : " << flag_d2duct  <<  G4endl;
  G4cout << "    Air betw. K1.1D1-KL window  : " << flag_air_K11q2duct_vwin  <<  G4endl;
  G4cout << "    KL Vacuum Window            : " <<  flag_vwin_kl <<  G4endl;
  G4cout << "    KL Sweeping magnet (Fe)     : " <<  flag_KL_magnet <<  G4endl;
  G4cout << "    Magnetic Field (vacuum)     : " <<  flag_KL_magnetic_field <<  G4endl;
  G4cout << "    Machining Erorr             : " <<  flag_machining_error <<  G4endl;

  G4cout << " --------------------------------------------" << G4endl;
 

  GsimTube* tube=0;
  GsimBox* box=0;
  char nam[100];
  std::vector<double> paramVec;
  
  
  // --- add by nabe---(070516)---
  // ----------------------------
  // T1 Vacuum window made of Be
  // ----------------------------
  G4double window_z = 15.20*cm;
  G4double be_zlength = 0.225*cm;
  const G4double angle1= -16.*deg;
  G4RotationMatrix* rotWindow= new G4RotationMatrix;
  rotWindow-> rotateY(angle1);

  if ( flag_vwin_t1 ) {
    G4double be_rin = 0.0*cm;
    G4double be_rout = 20.0*cm;
    G4double be_phiin = 0.0*rad;
    G4double be_phiout = 2.0*pi*rad;
    

    paramVec.clear();
    paramVec.push_back(be_rin);
    paramVec.push_back(be_rout);
    paramVec.push_back(be_zlength*2.);
    paramVec.push_back(be_phiin);
    paramVec.push_back(be_phiout);
    std::sprintf(nam,"Window");
    tube = new GsimTube(std::string(nam),this,
			G4ThreeVector(0*cm,0*cm,window_z),
			G4ThreeVector(0,-angle1,0));
    tube->setOuterMaterial("G4_Be");
    tube->setParameters(paramVec);
    tube->setOuterColor("red");
    addDaughter(tube);
  }

  // ----------------------------
  // T1 Air Volume
  // ----------------------------
  if (flag_t1_air ){
    G4double t1_air_rin = 0.0*cm;
    G4double t1_air_rout = 20.0*cm;
    G4double t1_air_zlength = 10.0*cm;
    G4double t1_air_phiin = 0.0*rad;
    G4double t1_air_phiout = 2.0*pi*rad;
    G4double zp_t1_air = window_z - t1_air_zlength - be_zlength - 0.5*cm;

  
    paramVec.clear();
    paramVec.push_back(t1_air_rin);
    paramVec.push_back(t1_air_rout);
    paramVec.push_back(t1_air_zlength*2.);
    paramVec.push_back(t1_air_phiin);
    paramVec.push_back(t1_air_phiout);
    std::sprintf(nam,"T1Air");
    tube = new GsimTube(std::string(nam),this,
			G4ThreeVector(0*cm,0*cm,zp_t1_air),
			G4ThreeVector(0,-angle1,0));
    tube->setOuterMaterial("G4_AIR");
    tube->setParameters(paramVec);
    tube->setOuterColor("gray70");
    addDaughter(tube);
  }

  // ------------------------------
  // 1st Collimator just behind T1
  // ------------------------------
  if ( flag_c1 ){  
    G4double c1_rin = 1.5*cm;
    G4double c1_rout = 7.5*cm;
    G4double c1_zlength = 20.8*cm;
    G4double c1_phiin = 0.0*rad;
    G4double c1_phiout = 2.0*pi*rad;



    paramVec.clear();
    paramVec.push_back(c1_rin);
    paramVec.push_back(c1_rout);
    paramVec.push_back(c1_zlength*2.);
    paramVec.push_back(c1_phiin);
    paramVec.push_back(c1_phiout);
    std::sprintf(nam,"C1");
    tube = new GsimTube(std::string(nam),this,
			G4ThreeVector(0*cm,0*cm,74.6*cm),
			G4ThreeVector(0,0,0));
    tube->setOuterMaterial("G4_Cu");
    tube->setParameters(paramVec);
    tube->setOuterColor("green");
    addDaughter(tube);
  }

  // ------------------------------
  // K1.1 D1 Iron yoke
  // ------------------------------
  if ( flag_d1 ) {
    G4double d1_rin = 1.5*cm;
    G4double d1_rout = 15.0*cm;
    G4double d1_zlength = 34.4*cm;
    G4double d1_phiin = 0.0*rad;
    G4double d1_phiout = 2.0*pi*rad;

    paramVec.clear();
    paramVec.push_back(d1_rin);
    paramVec.push_back(d1_rout);
    paramVec.push_back(d1_zlength*2.);
    paramVec.push_back(d1_phiin);
    paramVec.push_back(d1_phiout);
    std::sprintf(nam,"D1");
    tube = new GsimTube(std::string(nam),this,
			G4ThreeVector(0*cm,0*cm,234.1*cm),
			G4ThreeVector(0,0,0));
    tube->setOuterMaterial("G4_Fe");
    tube->setParameters(paramVec);
    tube->setOuterColor("red");
    addDaughter(tube);
  }
  // --------------------------------------------
  // Wall of Central Vacuum Chamber made of SUS
  // --------------------------------------------
  if ( flag_wall ) {
    G4double wall_rin = 24.0*cm;
    G4double wall_rout = 36.0*cm;
    G4double wall_zlength = 5.3*cm;
    G4double wall_phiin = 0.0*rad;
    G4double wall_phiout = 2.0*pi*rad;
    const G4double angle2= 8.*deg;

    paramVec.clear();
    paramVec.push_back(wall_rin);
    paramVec.push_back(wall_rout);
    paramVec.push_back(wall_zlength*2.);
    paramVec.push_back(wall_phiin);
    paramVec.push_back(wall_phiout);
    std::sprintf(nam,"Wall");
    tube = new GsimTube(std::string(nam),this,
			G4ThreeVector(20.37*cm, 0.0*cm, 307.2*cm),
			G4ThreeVector(0,angle2,0));
    tube->setOuterMaterial("GsimSUS304");
    tube->setParameters(paramVec);
    tube->setOuterColor("red");
    addDaughter(tube);
  }

  //-----------------------------------
  //  Flange of K1.1 Q1-Q2 vacuum duct
  //-----------------------------------
  if ( flag_flange ) {
    G4double flange_rin = 0.0*cm;
    G4double flange_rout = 36.0*cm;
    G4double flange_zlength = 1.0*cm;
    G4double flange_phiin = 0.0*rad;
    G4double flange_phiout = 2.0*pi*rad;
    const G4double angle_flange= 8.*deg;
    
    paramVec.clear();
    paramVec.push_back(flange_rin);
    paramVec.push_back(flange_rout);
    paramVec.push_back(flange_zlength*2.);
    paramVec.push_back(flange_phiin);
    paramVec.push_back(flange_phiout);
    std::sprintf(nam,"Flange");
    tube = new GsimTube(std::string(nam),this,
			G4ThreeVector(19.51*cm, 0.0*cm, 314.6*cm),
			G4ThreeVector(0,-angle_flange,0));
    tube->setOuterMaterial("GsimSUS304");
    tube->setParameters(paramVec);
    tube->setOuterColor("gray70");
    addDaughter(tube);
  }

  //-----------------------------
  //  K1.1 Q1 yoke ( or coil) (NQ)
  //-----------------------------
  if ( flag_q1 ) {
    G4double q1_rin = 1.5*cm;
    G4double q1_rout = 15.0*cm;
    G4double q1_zlength = 25.0*cm;
    G4double q1_phiin = 0.0*rad;
    G4double q1_phiout = 2.0*pi*rad;

    paramVec.clear();
    paramVec.push_back(q1_rin);
    paramVec.push_back(q1_rout);
    paramVec.push_back(q1_zlength*2.);
    paramVec.push_back(q1_phiin);
    paramVec.push_back(q1_phiout);
    std::sprintf(nam,"Q1");
    tube = new GsimTube(std::string(nam),this,
			G4ThreeVector(0.0*cm, 0.0*cm, 340.5*cm),
			G4ThreeVector(0,0,0));
    tube->setOuterMaterial("G4_Cu");
    tube->setParameters(paramVec);
    tube->setOuterColor("green");
    addDaughter(tube);
  }
  //-------------------------------------
  //  Air volume of hole in K1.1 Q1 yoke
  //-------------------------------------
  if ( flag_q1_air ){ 

    G4double air_q1_rin = 0.0*cm;
    G4double air_q1_rout = 1.49*cm;
    if ( flag_q1==OFF) air_q1_rout = 100.0*cm;

    G4double air_q1_zlength = 28.7*cm;
    G4double air_q1_phiin = 0.0*rad;
    G4double air_q1_phiout = 2.0*pi*rad;

    G4double zpos=344.25*cm;
    if ( flag_femag_gabs )  zpos = 335.25*cm;


    paramVec.clear();
    paramVec.push_back(air_q1_rin);
    paramVec.push_back(air_q1_rout);
    paramVec.push_back(air_q1_zlength*2.);
    paramVec.push_back(air_q1_phiin);
    paramVec.push_back(air_q1_phiout);
    std::sprintf(nam,"AIRQ1");
    tube = new GsimTube(std::string(nam),this,
			G4ThreeVector(0.0*cm, 0.0*cm, zpos),
			G4ThreeVector(0,0,0));
    tube->setOuterMaterial("G4_AIR");
    tube->setParameters(paramVec);
    tube->setOuterColor("gray70");
    addDaughter(tube);
  }

  //----------------------------------------------------------------------
  //   Magnetic Field for charged particle sweeper before gamma absrober
  //----------------------------------------------------------------------  
  if ( flag_gabs_mag ) {
    G4double mair_x = 10.0*cm;
    G4double mair_y = 10.0*cm;
    G4double mair_z = 30.0*cm;

    paramVec.clear();
    paramVec.push_back(mair_x);
    paramVec.push_back(mair_y);
    paramVec.push_back(mair_z);
    
    std::sprintf(nam,"MAir");
    box = new GsimBox(std::string(nam),this,
		      G4ThreeVector(0.0*cm, 0.0*cm, 340.*cm),
		      G4ThreeVector(0,0,0));
    box->setOuterMaterial("G4_AIR");
    box->setParameters(paramVec);
    box->setOuterColor("gray70");
    addDaughter(box);
    
    box->setThisMagneticField(G4ThreeVector(0,-1.0*tesla,0));
  }

  //----------------------------------------------------------------------
  //   Magnetic Field for charged particle sweeper before gamma absrober
  //----------------------------------------------------------------------  
  if ( flag_femag_gabs ) {
    G4double mfe_x = 10.0*cm;
    G4double mfe_y = 10.0*cm;
    G4double mfe_z = 20.0*cm;

    paramVec.clear();
    paramVec.push_back(mfe_x);
    paramVec.push_back(mfe_y);
    paramVec.push_back(mfe_z);
    
    std::sprintf(nam,"MFe");
    box = new GsimBox(std::string(nam),this,
		      G4ThreeVector(0.0*cm, 0.0*cm, 376.5*cm),
		      G4ThreeVector(0,0,0));
    box->setOuterMaterial("G4_AIR");
    box->setParameters(paramVec);
    box->setOuterColor("gray70");
    addDaughter(box);

    box->setThisMagneticField(G4ThreeVector(0,-1.0*tesla,0));
  }

  
  //-------------------------------------
  //  Gamma Absorber
  //-------------------------------------    

  G4double abs_rout = 2.5*cm;
  //  G4double abs_rout = 20.0*cm;

  if ( flag_gabs ) {
    
    if ( flag_femag_gabs) {
      G4cout << " Error: Fe-mag gamma absorber on against Lead absorber on " << G4endl;
      std::exit(1);
    }
    G4double abs_rin = 0.0*cm;
    G4double abs_zlength = 3.5*cm;
    G4double abs_phiin = 0.0*rad;
    G4double abs_phiout = 2.0*pi*rad;


    paramVec.clear();
    paramVec.push_back(abs_rin);
    paramVec.push_back(abs_rout);
    paramVec.push_back(abs_zlength*2.);
    paramVec.push_back(abs_phiin);
    paramVec.push_back(abs_phiout);
    std::sprintf(nam,"Absorber");
    tube = new GsimTube(std::string(nam),this,
			G4ThreeVector(0.0*cm, 0.0*cm, 376.5*cm),
			G4ThreeVector(0,0,0));
    tube->setOuterMaterial("G4_Pb");
    tube->setParameters(paramVec);
    tube->setOuterColor("red");
    addDaughter(tube);
  }

  //-------------------------------------
  //  Air volume outside Gamma Absorber
  //  If no absorber case, inside is also air
  //-------------------------------------    

  if ( flag_gabs_air ) {
    G4double abs_air_rin = abs_rout+0.1*cm;
    if ( flag_gabs==OFF ) abs_air_rin = 0.0*cm;
    
    G4double abs_air_rout = 100.0*cm;
    G4double abs_air_zlength = 3.5*cm;
    G4double abs_air_phiin = 0.0*rad;
    G4double abs_air_phiout = 2.0*pi*rad;


    paramVec.clear();
    paramVec.push_back(abs_air_rin);
    paramVec.push_back(abs_air_rout);
    paramVec.push_back(abs_air_zlength*2.);
    paramVec.push_back(abs_air_phiin);
    paramVec.push_back(abs_air_phiout);
    std::sprintf(nam,"AirAbsorber");
    tube = new GsimTube(std::string(nam),this,
			G4ThreeVector(0.0*cm, 0.0*cm, 376.5*cm),
			G4ThreeVector(0,0,0));
    tube->setOuterMaterial("G4_AIR");
    tube->setParameters(paramVec);
    tube->setOuterColor("gray70");
    addDaughter(tube);
  }


  //-------------------------------------
  //  Air volume in K1.1 Q2 yoke-hole
  //-------------------------------------    

  if ( flag_q2 ) {

    G4double q2_rin = 1.5*cm;
    G4double q2_rout = 15.0*cm;
    G4double q2_zlength = 9.7*cm;
    G4double q2_phiin = 0.0*rad;
    G4double q2_phiout = 2.0*pi*rad;

    paramVec.clear();
    paramVec.push_back(q2_rin);
    paramVec.push_back(q2_rout);
    paramVec.push_back(q2_zlength*2.);
    paramVec.push_back(q2_phiin);
    paramVec.push_back(q2_phiout);
    std::sprintf(nam,"Q2");
    tube = new GsimTube(std::string(nam),this,
			G4ThreeVector(0.0*cm, 0.0*cm, 408.5*cm),
			G4ThreeVector(0,0,0));
    tube->setOuterMaterial("G4_Cu");
    tube->setParameters(paramVec);
    tube->setOuterColor("green");
    addDaughter(tube);
  }

  //-------------------------------------
  //  Air volume of hole in K1.1 Q2 yoke
  //-------------------------------------    
  if ( flag_q2_air ){
    G4double air_q2_rin = 0.0*cm;
    G4double air_q2_rout = 1.49*cm;
    if ( flag_q2==OFF) air_q2_rout = 100.0*cm;

    G4double air_q2_zlength = 19.0*cm;
    G4double air_q2_phiin = 0.0*rad;
    G4double air_q2_phiout = 2.0*pi*rad;

    G4double zpos=399.1*cm;
    if ( flag_femag_gabs ) {
      zpos = 410*cm;
    }

    paramVec.clear();
    paramVec.push_back(air_q2_rin);
    paramVec.push_back(air_q2_rout);
    paramVec.push_back(air_q2_zlength*2.);
    paramVec.push_back(air_q2_phiin);
    paramVec.push_back(air_q2_phiout);
    std::sprintf(nam,"AIRQ2");
    tube = new GsimTube(std::string(nam),this,
			G4ThreeVector(0.0*cm, 0.0*cm, zpos),
			G4ThreeVector(0,0,0));
    tube->setOuterMaterial("G4_AIR");
    tube->setParameters(paramVec);
    tube->setOuterColor("green");
    addDaughter(tube);
  }

  //-------------------------------------
  //  K1.1 Q1-Q2 Duct
  //-------------------------------------    
  if ( flag_q1q2duct1 ) {

    G4double duct1_rin = 0.0*cm;
    G4double duct1_rout = 12.0*cm;
    G4double duct1_zlength = 0.25*cm;
    G4double duct1_phiin = 0.0*rad;
    G4double duct1_phiout = 2.0*pi*rad;
    const G4double angle3= -82.*deg;
    
    paramVec.clear();
    paramVec.push_back(duct1_rin);
    paramVec.push_back(duct1_rout);
    paramVec.push_back(duct1_zlength*2.);
    paramVec.push_back(duct1_phiin);
    paramVec.push_back(duct1_phiout);
    std::sprintf(nam,"Duct1");
    tube = new GsimTube(std::string(nam),this,
			G4ThreeVector(0.0*cm, 0.0*cm, 431.4*cm),
			G4ThreeVector(0,-angle3,0));
    tube->setOuterMaterial("GsimSUS304");
    tube->setParameters(paramVec);
    tube->setOuterColor("gray70");
    addDaughter(tube);
  }

  //-------------------------------------
  //  K1.1 D2 Duct
  //-------------------------------------    
  if ( flag_d2duct ) {

    G4double duct2_rin = 0.0*cm;
    G4double duct2_rout = 5.0*cm;
    G4double duct2_zlength = 0.25*cm;
    G4double duct2_phiin = 0.0*rad;
    G4double duct2_phiout = 2.0*pi*rad;
    const G4double angle4= -62*deg;

    paramVec.clear();
    paramVec.push_back(duct2_rin);
    paramVec.push_back(duct2_rout);
    paramVec.push_back(duct2_zlength*2.);
    paramVec.push_back(duct2_phiin);
    paramVec.push_back(duct2_phiout);
    std::sprintf(nam,"Duct2");
    tube = new GsimTube(std::string(nam),this,
			G4ThreeVector(0.0*cm, 0.0*cm, 560.8*cm),
			G4ThreeVector(0,-angle4,0));
    tube->setOuterMaterial("GsimSUS304");
    tube->setParameters(paramVec);
    tube->setOuterColor("gray70");
    addDaughter(tube);
  }

  //-------------------------------------
  //  K1.1 D2 yoke 
  //-------------------------------------   
  if ( flag_d2 ) {
    G4double d2_rin = 1.5*cm;
    G4double d2_rout = 17.0*cm;
    G4double d2_zlength = 18.5*cm;
    G4double d2_phiin = 0.0*rad;
    G4double d2_phiout = 2.0*pi*rad;



    paramVec.clear();
    paramVec.push_back(d2_rin);
    paramVec.push_back(d2_rout);
    paramVec.push_back(d2_zlength*2.);
    paramVec.push_back(d2_phiin);
    paramVec.push_back(d2_phiout);
    std::sprintf(nam,"D2");
    tube = new GsimTube(std::string(nam),this,
			G4ThreeVector(0.0*cm, 0.0*cm, 585.7*cm),
			G4ThreeVector(0,0,0));
    tube->setOuterMaterial("G4_Cu");
    tube->setParameters(paramVec);
    tube->setOuterColor("green");
    addDaughter(tube);
  }

  //-------------------------------------
  //  Air volume inside K1.1 D2 yoke-hole
  //-------------------------------------   

  if (flag_air_K11q2duct_vwin ) {
    G4double air_d2_rin = 0.0*cm;
    G4double air_d2_rout = 1.49*cm;
    if ( (flag_d2duct==OFF)&&(flag_d2==OFF) ) air_d2_rout = 100.0*cm;

    //    G4double air_d2_zlength = 36.3*cm;
    G4double air_d2_zlength = 33.3*cm; // for tagging before collimator
    G4double air_d2_phiin = 0.0*rad;
    G4double air_d2_phiout = 2.0*pi*rad;


    paramVec.clear();
    paramVec.push_back(air_d2_rin);
    paramVec.push_back(air_d2_rout);
    paramVec.push_back(air_d2_zlength*2.);
    paramVec.push_back(air_d2_phiin);
    paramVec.push_back(air_d2_phiout);
    std::sprintf(nam,"AIRD2");
    tube = new GsimTube(std::string(nam),this,
			G4ThreeVector(0.0*cm, 0.0*cm, 603.5*cm),
			G4ThreeVector(0,0,0));
    tube->setOuterMaterial("G4_AIR");
    tube->setParameters(paramVec);
    tube->setOuterColor("gray70");
    addDaughter(tube);
  }

  //-------------------------------------
  //  KL vacuum window
  //-------------------------------------   
  if ( flag_vwin_kl ) {

    G4double vwin_rin = 0.0*cm;
    G4double vwin_rout = 2.5*cm;
    G4double vwin_zlength = 0.005*cm;
    G4double vwin_phiin = 0.0*rad;
    G4double vwin_phiout = 2.0*pi*rad;


    paramVec.clear();
    paramVec.push_back(vwin_rin);
    paramVec.push_back(vwin_rout);
    paramVec.push_back(vwin_zlength*2.);
    paramVec.push_back(vwin_phiin);
    paramVec.push_back(vwin_phiout);
    std::sprintf(nam,"Vwindow");
    tube = new GsimTube(std::string(nam),this,
			G4ThreeVector(0.0*cm, 0.0*cm, 640.*cm),
			G4ThreeVector(0,0,0));
    tube->setOuterMaterial("GsimSUS304");
    tube->setParameters(paramVec);
    tube->setOuterColor("gray70");
    addDaughter(tube);
  }

  // ----------------------
  //  Tagging volume
  //-----------------------
  G4double tag_rin = 0.0*cm;
  G4double tag_rout = 150.0*cm;
  G4double tag_zlength = 2.5*cm;
  G4double tag_phiin = 0.0*rad;
  G4double tag_phiout = 2.0*pi*rad;


  paramVec.clear();
  paramVec.push_back(tag_rin);
  paramVec.push_back(tag_rout);
  paramVec.push_back(tag_zlength*2.);
  paramVec.push_back(tag_phiin);
  paramVec.push_back(tag_phiout);
  std::sprintf(nam,"Tag");
  tube = new GsimTube(std::string(nam),this,
		      G4ThreeVector(0.0*cm, 0.0*cm, (1402.5+700)*cm),
		      G4ThreeVector(0,0,0));
  tube->setOuterMaterial("G4_Galactic");
  tube->setParameters(paramVec);
  tube->setOuterColor("cyan");
  addDaughter(tube);
  tube->setSensitiveDetector("cal");

  // ---------------------------------------
  // Tagging volume in front of collimator
  // ---------------------------------------
  G4double coltag_rin = 0.0*cm;
  G4double coltag_rout = 150.0*cm;
  G4double coltag_zlength = 0.5*cm;
  G4double coltag_phiin = 0.0*rad;
  G4double coltag_phiout = 2.0*pi*rad;

  paramVec.clear();
  paramVec.push_back(coltag_rin);
  paramVec.push_back(coltag_rout);
  paramVec.push_back(coltag_zlength*2.);
  paramVec.push_back(coltag_phiin);
  paramVec.push_back(coltag_phiout);
  std::sprintf(nam,"Coltag");
  tube = new GsimTube(std::string(nam),this,
		      G4ThreeVector(0.0*cm, 0.0*cm, (638.5)*cm),
		      G4ThreeVector(0,0,0));
  tube->setOuterMaterial("G4_Galactic");
  tube->setParameters(paramVec);
  tube->setOuterColor("red");
  addDaughter(tube);
  
  //--------------------------------------------------------
  // 1st stage of Iron shield outside tungsten colliamtor
  //-------------------------------------------------------
  
  //== Inner Part==
  G4double fe1_rin = 3.011*cm; 
  G4double fe1_rout = 200.0*cm;
  G4double fe1_zlength = 230.0*cm;
  G4double fe1_phiin = 0.0*rad;
  G4double fe1_phiout = 2.0*pi*rad;

  paramVec.clear();
  paramVec.push_back(fe1_rin);
  paramVec.push_back(fe1_rout);
  paramVec.push_back(fe1_zlength*2.);
  paramVec.push_back(fe1_phiin);
  paramVec.push_back(fe1_phiout);
  std::sprintf(nam,"Fe1");
  tube = new GsimTube(std::string(nam),this,
		      G4ThreeVector(0.0*cm, 0.0*cm, (225.0+650)*cm),
		      G4ThreeVector(0,0,0));
  tube->setOuterMaterial("G4_Fe");
  tube->setParameters(paramVec);
  tube->setOuterColor("red");
  addDaughter(tube);

  
  //----------------------------------------------------------
  // 2nd stage of Iron shield outside tungsten colliamtor
  //----------------------------------------------------------
  //== Inner Part==
  G4double fe2_rin = 6.011*cm;
  G4double fe2_rout = 200.0*cm;
  G4double fe2_zlength = 205.0*cm;
  G4double fe2_phiin = 0.0*rad;
  G4double fe2_phiout = 2.0*pi*rad;

  paramVec.clear();
  paramVec.push_back(fe2_rin);
  paramVec.push_back(fe2_rout);
  paramVec.push_back(fe2_zlength*2.);
  paramVec.push_back(fe2_phiin);
  paramVec.push_back(fe2_phiout);
  std::sprintf(nam,"Fe2");
  tube = new GsimTube(std::string(nam),this,
		      G4ThreeVector(0.0*cm, 0.0*cm, (1100.0+700)*cm),
		      G4ThreeVector(0,0,0));
  tube->setOuterMaterial("G4_Fe");
  tube->setParameters(paramVec);
  tube->setOuterColor("red");
  addDaughter(tube);


  //------------------------------------------------
  // Collimaotor "Zero" Z=650-700cm in 1st stage
  //------------------------------------------------

  
  G4double coll0_rin_upstream   = 1.49*cm;
  G4double coll0_rin_downstream = 1.18*cm;
  G4double coll0_rout           = 3.0*cm;
  G4double coll0_zlength        = 50.0*cm;
  G4double coll0_phiin          = 0.0*rad;
  G4double coll0_phiout         = 2.0*pi*rad;

  
  
  for (int i=0; i<10; i++){
    G4double r0_disk = i*(coll0_rin_downstream - coll0_rin_upstream)/9.0
      + coll0_rin_upstream;
    r0_disk = roundThis(r0_disk);
    G4double z0_disk = coll0_zlength / 10/2;

    G4double pos0xe=0.0*cm;
    G4double pos0ye=0.0*cm;
    double pos0x, pos0y, pos0z;
    pos0x = pos0xe;
    pos0y = pos0ye;
    pos0z = 650.0*cm + (i+0.5)*coll0_zlength/10;

    paramVec.clear();
    paramVec.push_back(r0_disk);
    paramVec.push_back(coll0_rout);
    paramVec.push_back(z0_disk*2.);
    paramVec.push_back(coll0_phiin);
    paramVec.push_back(coll0_phiout);

    std::sprintf(nam,"Col-zer%d",i);
    tube = new GsimTube(std::string(nam),this,
			G4ThreeVector(pos0x, pos0y, pos0z),
			G4ThreeVector(0,0,0));
    tube->setOuterMaterial("G4_W");
    tube->setParameters(paramVec);
    tube->setOuterColor("blue");
    addDaughter(tube);
    tube->setSensitiveDetector("collimator");
  }


  //------------------------------------------------
  // Collimaotor "One" Z=700-750cm in 1st stage
  //------------------------------------------------
  G4double coll1_rin_upstream   = 1.18*cm;
  G4double coll1_rin_downstream = 1.33*cm;
  G4double coll1_rout           = 3.0*cm;
  G4double coll1_zlength        = 50.0*cm;
  G4double coll1_phiin          = 0.0*rad;
  G4double coll1_phiout         = 2.0*pi*rad;

  for (int i=0; i<10; i++){
    G4double r1_disk = i*(coll1_rin_downstream - coll1_rin_upstream)/9.0
      + coll1_rin_upstream;
    r1_disk = roundThis(r1_disk);
    G4double z1_disk = coll1_zlength / 10/2;

    G4double pos1xe=0.0*cm;
    G4double pos1ye=0.0*cm;
    double pos1x, pos1y, pos1z;
    pos1x = pos1xe;
    pos1y = pos1ye;
    pos1z = 700.0*cm + (i+0.5)*coll1_zlength/10;

    paramVec.clear();
    paramVec.push_back(r1_disk);
    paramVec.push_back(coll1_rout);
    paramVec.push_back(z1_disk*2.);
    paramVec.push_back(coll1_phiin);
    paramVec.push_back(coll1_phiout);

    std::sprintf(nam,"Col-1st%d",i);
    tube = new GsimTube(std::string(nam),this,
			G4ThreeVector(pos1x, pos1y, pos1z),
			G4ThreeVector(0,0,0));
    tube->setOuterMaterial("G4_W");
    tube->setParameters(paramVec);
    tube->setOuterColor("blue");
    addDaughter(tube);
    tube->setSensitiveDetector("collimator");
  }

  //--------------------------------------------------
  // Collimaotor "Second" Z=750-1100cm  in 1st stage
  //--------------------------------------------------
  G4double coll2_rin_upstream   = 1.33*cm;
  G4double coll2_rin_downstream = 2.38*cm;
  G4double coll2_rout           = 3.0*cm;
  G4double coll2_zlength        = 350.0*cm;
  G4double coll2_phiin          = 0.0*rad;
  G4double coll2_phiout         = 2.0*pi*rad;

  for (int i=0; i<70; i++){
    G4double r2_disk = i*(coll2_rin_downstream - coll2_rin_upstream)/69.0
      + coll2_rin_upstream;
    G4double z2_disk = coll2_zlength / 70/2;

    G4double pos2xe=0.0*cm;
    G4double pos2ye=0.0*cm;
    double pos2x, pos2y, pos2z;
    pos2x = pos2xe;
    pos2y = pos2ye;
    pos2z = 750*cm + (i+0.5)*coll2_zlength/70;

    paramVec.clear();
    paramVec.push_back(r2_disk);
    paramVec.push_back(coll2_rout);
    paramVec.push_back(z2_disk*2.);
    paramVec.push_back(coll2_phiin);
    paramVec.push_back(coll2_phiout);

    std::sprintf(nam,"Col-2nd%d",i);
    tube = new GsimTube(std::string(nam),this,
			G4ThreeVector(pos2x, pos2y, pos2z),
			G4ThreeVector(0,0,0));
    tube->setOuterMaterial("G4_W");
    tube->setParameters(paramVec);
    tube->setOuterColor("blue");
    addDaughter(tube);
    tube->setSensitiveDetector("collimator");
  }

  //--------------------------------------------------
  // Collimaotor "Third" Z=1600-2000cm  in 2nd stage
  //--------------------------------------------------
  G4double coll3_rin_upstream   = 3.88*cm;
  G4double coll3_rin_downstream = 5.08*cm;
  G4double coll3_rout           = 6.0*cm;
  G4double coll3_zlength        = 400.0*cm;
  G4double coll3_phiin          = 0.0*rad;
  G4double coll3_phiout         = 2.0*pi*rad;

  for (int i=0; i<80; i++){
    G4double r3_disk = i*(coll3_rin_downstream - coll3_rin_upstream)/79.0
      + coll3_rin_upstream;
    G4double z3_disk = coll3_zlength / 80/2;

    G4double pos3xe=0.0*cm;
    G4double pos3ye=0.0*cm;
    double pos3x, pos3y, pos3z;
    pos3x = pos3xe;
    pos3y = pos3ye;
    pos3z = 700.0*cm + 900.0*cm + (i+0.5)*coll3_zlength/80;
    
    paramVec.clear();
    paramVec.push_back(r3_disk);
    paramVec.push_back(coll3_rout);
    paramVec.push_back(z3_disk*2.);
    paramVec.push_back(coll3_phiin);
    paramVec.push_back(coll3_phiout);

    std::sprintf(nam,"Col-3rd%d",i);
    tube = new GsimTube(std::string(nam),this,
			G4ThreeVector(pos3x, pos3y, pos3z),
			G4ThreeVector(0,0,0));
    tube->setOuterMaterial("G4_W");
    tube->setParameters(paramVec);
    tube->setOuterColor("blue");
    addDaughter(tube);
    tube->setSensitiveDetector("collimator");
  }

  // ----------------------------
  //   KL Magnet Iron Yoke (K0D2)
  //-----------------------------
  if ( flag_KL_magnet) {
    G4double magnet_x = 109.0*cm;
    G4double magnet_y = 86.0*cm;
    G4double magnet_z = 150.0*cm;


    paramVec.clear();
    paramVec.push_back(magnet_x);
    paramVec.push_back(magnet_y);
    paramVec.push_back(magnet_z);
    
    std::sprintf(nam,"Magnet");
    GsimBox* mag = new GsimBox(std::string(nam),this,
			       G4ThreeVector(0.0*cm, 0.0*cm, (575.0+700)*cm),
			       G4ThreeVector(0,0,0));
    mag->setOuterMaterial("G4_Fe");
    mag->setParameters(paramVec);
    mag->setOuterColor("red");
    addDaughter(mag);


    
    
    //   KL Magnetic Field (K0D2)
    if ( flag_KL_magnetic_field) {
      G4double mvac_x = 30.0*cm;
      G4double mvac_y = 12.0*cm;
      G4double mvac_z = 150.0*cm;

      paramVec.clear();
      paramVec.push_back(mvac_x);
      paramVec.push_back(mvac_y);
      paramVec.push_back(mvac_z);
    
      std::sprintf(nam,"Magneticfield");
      if ( flag_KL_magnet ){
	box = new GsimBox(std::string(nam),mag,
			  G4ThreeVector(0.0*cm, 0.0*cm, 0.0*cm),
			  G4ThreeVector(0,0,0));
	box->setOuterMaterial("G4_Galactic");
	box->setParameters(paramVec);
	box->setOuterColor("cyan");
	mag->addDaughter(box);
      } else {
	box = new GsimBox(std::string(nam),this,
			  G4ThreeVector(0.0*cm, 0.0*cm, (575.0+700)*cm),
			  G4ThreeVector(0,0,0));
	box->setOuterMaterial("G4_Galactic");
	box->setParameters(paramVec);
	box->setOuterColor("cyan");
	addDaughter(box);
      }
      
      box->setThisAndDaughterMagneticField(G4ThreeVector(0.0,-2.0*tesla,0.0));
    }
  }
  
  setThisAndDaughterBriefName("Beamline");
  update();
}

GsimE14Beamline::~GsimE14Beamline()
{
  ;
}


double GsimE14Beamline::roundThis(double val)
{
  double a ;
  int b ;
  b = (int)round(val/0.1);
  a=b*0.1;
  return a;
}
