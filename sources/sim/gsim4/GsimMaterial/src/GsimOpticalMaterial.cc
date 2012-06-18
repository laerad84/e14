/**
 *  @file
 *  @brief  GsimOpticalMaterial
 *  $Id: $ 
 *  $Log: $
 */
#include "GsimMaterial/GsimOpticalMaterial.h"
#include "GsimKernel/GsimUtil.h"

#include "G4Material.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4NistManager.hh"



GsimOpticalMaterial::GsimOpticalMaterial()
  : GsimMaterial()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif


  GsimUtil* util=GsimUtil::getUtil();

  
  G4Material* mat=0;
  
  std::string name;
  G4NistManager* nist = G4NistManager::Instance();
  int nel,natom;

  double density=0.;
  double pressure=0.;
  double temperature=0.;

  //BC400
  name="GsimOpticalBC400";
  mat=util->findMaterial(name,false);
  G4Material* BC400=0;
  if(!mat) {
    density=  1.032*g/cm3;
    BC400
      = new G4Material(name, density,nel=2);
    BC400->AddElement(nist->FindOrBuildElement("H"), 0.085); //(H, 1103)
    BC400->AddElement(nist->FindOrBuildElement("C"), 0.915); //(C, 1000)
  }
  
  
  
  // CsI
  name="GsimOpticalCsI";
  mat=util->findMaterial(name,false);
  G4Material* CsI=0;
  if(!mat) {
    density=  4.51*g/cm3;
    CsI
      = new G4Material(name, density,nel=2);
    CsI->AddElement( nist->FindOrBuildElement("I"), 0.488451);
    CsI->AddElement( nist->FindOrBuildElement("Cs"),0.511549);
    CsI->GetIonisation()->SetMeanExcitationEnergy(553.1*eV);
  }
  
  // SiCookie n=1.465
  // Si2C9H14O2
  name="GsimOpticalSiCookie";
  mat=util->findMaterial(name,false);
  G4Material* SiCookie=0;
  if(!mat) {
    density=  4.51*g/cm3;
    SiCookie
      = new G4Material(name, density,nel=4);
    SiCookie->AddElement( nist->FindOrBuildElement("H"), 14);
    SiCookie->AddElement( nist->FindOrBuildElement("O"),  2);
    SiCookie->AddElement( nist->FindOrBuildElement("C"),  9);
    SiCookie->AddElement( nist->FindOrBuildElement("Si"), 2);
  }
  
  
  // Grease
  name="GsimOpticalGrease";
  mat=util->findMaterial(name,false);
  G4Material* Grs=0;
  if(!mat) {
    Grs = new G4Material(name, density= 1.29*mg/cm3, nel=2);
    Grs->AddElement(nist->FindOrBuildElement("O"), 30*perCent);
    Grs->AddElement(nist->FindOrBuildElement("N"), 70*perCent);
  }

  // cmnt
  name="GsimOpticalCement";
  mat=util->findMaterial(name,false);
  G4Material* Cmnt=0; 
  if(!mat) {
    Cmnt = new G4Material(name, density= 1.29*mg/cm3, nel=2);
    Cmnt->AddElement(nist->FindOrBuildElement("O"), 30*perCent);
    Cmnt->AddElement(nist->FindOrBuildElement("N"), 70*perCent);
  }

  // Vacuum
  name="GsimOpticalVacuum";
  mat=util->findMaterial(name,false);
  G4Material* vacuum = 0;
  if(!mat) {
    density     = universe_mean_density;    //from PhysicalConstants.h
    pressure    = 3.e-18*pascal;
    temperature = 2.73*kelvin;
    vacuum = 
      new G4Material(name, density, nel=1,
		     kStateGas,temperature,pressure);
    vacuum->AddElement(nist->FindOrBuildElement("H"), 1);
    vacuum->GetIonisation()->SetMeanExcitationEnergy(19.2*eV);
  }

  
  // Air
  name="GsimOpticalAir";
  mat=util->findMaterial(name,false);
  G4Material* air =0;
  if(!mat) {
    density=  0.00120479*g/cm3;
    air =
      new G4Material(name, density,nel=4, kStateGas);
    air->AddElement( nist->FindOrBuildElement("C"), 0.000124);
    air->AddElement( nist->FindOrBuildElement("N"), 0.755267);
    air->AddElement( nist->FindOrBuildElement("O"), 0.231781);
    air->AddElement( nist->FindOrBuildElement("Ar"), 0.012827);
    air->GetIonisation()->SetMeanExcitationEnergy(85.7*eV);
  }

  //Aerogel
  name="GsimOpticalAerogel";
  mat=util->findMaterial(name,false);
  G4Material* opAerogel=0;
  if(!mat) {
    // aerogel
    // n(SiO2)+2n(H2O)=SiO4H4
    density = 0.11*g/cm3;
    opAerogel
      = new G4Material(name,density,nel=3);
    opAerogel->AddElement(nist->FindOrBuildElement("Si"), natom=1);
    opAerogel->AddElement(nist->FindOrBuildElement("H"),  natom=4);
    opAerogel->AddElement(nist->FindOrBuildElement("O"),  natom=4);
  }
  
  
  
  
  // glass
  name="GsimOpticalGlass";
  mat=util->findMaterial(name,false);
  G4Material* opGlass=0;
  if(!mat) {
    density = 2.23*g/cm3;
    opGlass
      = new G4Material(name,density,nel=6);
    opGlass->AddElement(nist->FindOrBuildElement("B"), 0.040064);
    opGlass->AddElement(nist->FindOrBuildElement("O"), 0.539562);
    opGlass->AddElement(nist->FindOrBuildElement("Na"), 0.028191);
    opGlass->AddElement(nist->FindOrBuildElement("Al"), 0.011644);
    opGlass->AddElement(nist->FindOrBuildElement("Si"), 0.37722 );
    opGlass->AddElement(nist->FindOrBuildElement("K"), 0.003321);
  }

  
  // photo cathode
  name="GsimOpticalPhotoCathode";
  mat=util->findMaterial(name,false);
  G4Material* opPC =0;
  if(!mat) {
    density     = universe_mean_density;    //from PhysicalConstants.h
    pressure    = 3.e-18*pascal;
    temperature = 2.73*kelvin;
    opPC =
      new G4Material(name, density, nel=1,
		     kStateGas,temperature,pressure);
    opPC->AddElement(nist->FindOrBuildElement("H"), 1);
    opPC->GetIonisation()->SetMeanExcitationEnergy(19.2*eV);
  }

  // PMMA
  name="GsimOpticalPMMA";
  mat=util->findMaterial(name,false);
  G4Material* opPMMA =0;
  if(!mat) {
    density     = 1.19*g/cm3;
    opPMMA =
      new G4Material(name, density, nel=3);
    opPMMA->AddElement(nist->FindOrBuildElement("C"), 5);
    opPMMA->AddElement(nist->FindOrBuildElement("O"), 1);
    opPMMA->AddElement(nist->FindOrBuildElement("H"), 8);
  }



  if(BC400) {
    //BC400
    const G4int nEntries=62;
    G4double PhotonWaveLength[nEntries] = {
      100.0,
      350.0, 360.0, 370.0, 380.0, 390.0,
      400.3, 403.3, 405.8, 409.4, 411.9,
      413.0, 413.8, 414.9, 416.6, 418.8,
      421.0, 421.5, 423.5, 424.6, 425.4,
      426.2, 427.3, 428.7, 430.4, 431.8,
      433.1, 435.1, 437.3, 439.8, 442.5,
      445.6, 448.1, 450.0, 451.1, 452.5,
      455.2, 458.6, 462.2, 466.9, 473.2,
      480.4, 485.9, 490.1, 494.2, 499.7,
      500.0, 510.0, 520.0, 530.0, 540.0,
      550.0, 560.0, 570.0, 580.0, 590.0,
      600.0, 610.0, 620.0, 630.0, 640.0,
      1000.0
    };//[nm]
    G4double PhotonEnergy[nEntries];
    for(int i=0;i<nEntries;i++) {
      PhotonEnergy[i]=2.*M_PI*197.326/PhotonWaveLength[i]*eV;
    }
    G4double RefractiveIndex[nEntries];
    G4double AttenuationLength[nEntries];
    G4double Scintillation[nEntries] = {
      0.000 ,
      0.000 ,  0.012 ,  0.058 ,  0.266 ,  1.229 ,
      5.263 ,  9.418 , 14.404 , 23.823 , 34.903 ,
      43.767 , 54.571 , 70.637 , 81.440 , 90.305 ,
      96.122 , 98.237 , 99.723 , 99.446 , 98.892 ,
      96.953 , 91.413 , 85.596 , 80.332 , 75.069 ,
      72.853 , 71.191 , 70.914 , 70.360 , 68.698 ,
      64.543 , 59.003 , 55.125 , 50.416 , 47.091 ,
      42.382 , 37.119 , 32.964 , 28.255 , 23.269 ,
      18.559 , 15.789 , 13.850 , 12.465 , 10.526 ,
      9.660 ,  6.931 ,  4.974 ,  3.569 ,  2.561 ,
      1.837 ,  1.318 ,  0.946 ,  0.679 ,  0.487 ,
      0.349 ,  0.251 ,  0.180 ,  0.129 ,  0.000 ,
      0.000
    };
    for(int i=0;i<nEntries;i++) {
      RefractiveIndex[i]=1.58;
      //      AttenuationLength[i]=50*cm;// always
      //      AttenuationLength[i]=150*cm;// 
      AttenuationLength[i]=100*m;
    }

    G4MaterialPropertiesTable* MPT = new G4MaterialPropertiesTable();
    MPT->AddProperty("RINDEX",       PhotonEnergy, RefractiveIndex,nEntries);
    MPT->AddProperty("ABSLENGTH",    PhotonEnergy, AttenuationLength,nEntries);
    MPT->AddProperty("FASTCOMPONENT",PhotonEnergy, Scintillation,nEntries);
    
    MPT->AddConstProperty("SCINTILLATIONYIELD",1./(10.0*keV)); // Dec 3
    MPT->AddConstProperty("RESOLUTIONSCALE",1.0);
    MPT->AddConstProperty("FASTTIMECONSTANT", 2.4*ns);
    MPT->AddConstProperty("YIELDRATIO",1.);
    BC400->SetMaterialPropertiesTable(MPT);
  }


  
  if(CsI){
    //CsI
    const G4int nEntries=47;
    G4double PhotonWaveLength[nEntries] = {
      100,  150, 200,
      220 , 230 , 239.751 , 248.447 , 257.143 ,
      262.112 , 264.596 , 269.565 , 275.777 , 283.229 ,
      291.925 , 294.41 , 298.137 , 301.863 , 304.669 ,
      308.075 , 314.286 , 318.013 , 321.739 , 326.708 ,
      332.92 , 339.13 , 346.584 , 351.553 , 361.491 ,
      368.944 , 386.336 , 400 , 417.391 , 440.994 ,
      455.9 , 480.745 , 498.136 , 516.77 , 536.646 ,
      557.764 , 575.155 , 593.789 , 598.758 , 603.727 ,
      616.149 , 630, 800, 1000
    };//[nm]
    G4double PhotonEnergy[nEntries];
    for(int i=0;i<nEntries;i++) {
      PhotonEnergy[i]=2.*M_PI*197.326/PhotonWaveLength[i]*eV;
    }
    
    G4double RefractiveIndex[nEntries] = {
      9.84344 , 5.55591 , 3.2097,
      2.68155 , 2.48637 , 2.3342 , 2.22666 , 2.14242 ,
      2.10354 , 2.08638 , 2.05628 , 2.02579 , 1.99818 ,
      1.97582 , 1.97097 , 1.96472 , 1.95946 , 1.956 ,
      1.95223 , 1.94594 , 1.94214 , 1.93803 , 1.93194 ,
      1.92362 , 1.91492 , 1.90455 , 1.898 , 1.88624 ,
      1.87846 , 1.86292 , 1.85247 , 1.84088 , 1.82804 ,
      1.82157 , 1.81311 , 1.80763 , 1.8011 , 1.79499 ,
      1.79007 , 1.78698 , 1.78444 , 1.78386 , 1.78332 ,
      1.78208 , 1.78085 , 1.7668  , 1.758 
    };
    G4double Scintillation[nEntries] = {
      0. , 0. , 0.,
      0. , 0. , 0.00718089 , 0.0143618 , 0.0394929 ,
      0.064624 , 0.118476 , 0.19746 , 0.333888 , 0.531347 ,
      0.746759 , 0.872414 , 0.958579 , 0.9873 , 1 ,
      0.998071 , 0.97294 , 0.919087 , 0.818562 , 0.678545 ,
      0.538528 , 0.391331 , 0.283624 , 0.226183 , 0.157969 ,
      0.125657 , 0.0861653 , 0.0682137 , 0.064624 , 0.064624 ,
      0.0718035 , 0.0789844 , 0.0825742 , 0.0753946 , 0.0753946 ,
      0.0574431 , 0.0359018 , 0.0179516 , 0.00718089 , 0.00359112 ,
      0 , 0 , 0, 0
    };
    G4double AttenuationLength[nEntries];
    for(int i=0;i<nEntries;i++) {
      AttenuationLength[i]=1*m;
    }

    G4MaterialPropertiesTable* MPT = new G4MaterialPropertiesTable();
    MPT->AddProperty("RINDEX",       PhotonEnergy, RefractiveIndex,nEntries);
    MPT->AddProperty("ABSLENGTH",    PhotonEnergy, AttenuationLength,nEntries);
    MPT->AddProperty("FASTCOMPONENT",PhotonEnergy, Scintillation,nEntries);
    MPT->AddProperty("SLOWCOMPONENT",PhotonEnergy, Scintillation,nEntries);
  
    MPT->AddConstProperty("SCINTILLATIONYIELD",1./(500*eV));
    //MPT->AddConstProperty("SCINTILLATIONYIELD",1./(10.*MeV));
    //MPT->AddConstProperty("SCINTILLATIONYIELD",1./(1.*MeV));
    MPT->AddConstProperty("FASTTIMECONSTANT", 6.*ns);
    MPT->AddConstProperty("SLOWTIMECONSTANT", 35.*ns);
    MPT->AddConstProperty("YIELDRATIO",0.291);
    MPT->AddConstProperty("RESOLUTIONSCALE",1.0);
    
    CsI->SetMaterialPropertiesTable(MPT);
  }

  if(SiCookie){
    // SiCookie
    const G4int nEntries=35;
    G4double PhotonWaveLength[nEntries] = {
      100,    200,    290,    291,    300,    
      310,    320,    330,    340,    350,    
      360,    370,    380,    390,    400,    
      410,    420,    430,    440,    450,    
      460,    470,    480,    490,    500,    
      550,    600,    650,    700,    750,    
      800,    850,    900,    950,    1000
    };//[nm]
    G4double PhotonEnergy[nEntries];
    for(int i=0;i<nEntries;i++) {
      PhotonEnergy[i]=2.*M_PI*197.326/PhotonWaveLength[i]*eV;
    }
    G4double RefractiveIndex[nEntries] = {
      1,              1,              1,             10,              1.62822,        
      1.59625,        1.57122,        1.55146,        1.53573,        1.5231, 
      1.51289,        1.50455,        1.4977,         1.49202,        1.48727,        
      1.48327,        1.47987,        1.47696,        1.47444,        1.47225,       
      1.47033,        1.46863,        1.46711,        1.46575,        1.46452,       
      1.45975,        1.45639,        1.45381,        1.45173,        1.44999,       
      1.44851,        1.44724,        1.44614,        1.44517,        1.44433
    };
    G4MaterialPropertiesTable* MPT = new G4MaterialPropertiesTable();
    MPT->AddProperty("RINDEX",       PhotonEnergy, RefractiveIndex,nEntries);
    SiCookie->SetMaterialPropertiesTable(MPT);
  }
  
  
  if(Grs) {
    //Grease
    const G4int nEntries=2;
    G4double PhotonWaveLength[nEntries] = {
      100.0,
      1000.0
    };//[nm]
    G4double PhotonEnergy[nEntries];
    for(int i=0;i<nEntries;i++) {
      PhotonEnergy[i]=2.*M_PI*197.326/PhotonWaveLength[i]*eV;
    }
    G4double RefractiveIndex[nEntries];
    for(int i=0;i<nEntries;i++) {
      RefractiveIndex[i]=1.404;
    }
    
    G4MaterialPropertiesTable* MPT = new G4MaterialPropertiesTable();
    MPT->AddProperty("RINDEX",       PhotonEnergy, RefractiveIndex,nEntries);
    Grs->SetMaterialPropertiesTable(MPT);
  }
  
  if(Cmnt) {
    //Cement
    const G4int nEntries=2;
    G4double PhotonWaveLength[nEntries] = {
      100.0,
      1000.0
    };//[nm]
    G4double PhotonEnergy[nEntries];
    for(int i=0;i<nEntries;i++) {
      PhotonEnergy[i]=2.*M_PI*197.326/PhotonWaveLength[i]*eV;
    }
    G4double RefractiveIndex[nEntries];
    for(int i=0;i<nEntries;i++) {
      RefractiveIndex[i]=1.57;
    }
    
    G4MaterialPropertiesTable* MPT = new G4MaterialPropertiesTable();
    MPT->AddProperty("RINDEX",       PhotonEnergy, RefractiveIndex,nEntries);
    Cmnt->SetMaterialPropertiesTable(MPT);
  }
  

  if(vacuum){
    /// optical properties of Vacuum
    /**
     *   one value for refractive index
     */
    const G4int nEntries=2;
    G4double photonWaveLength[nEntries] = {
      100.0,
      1000.0
    };//[nm]
    G4double photonEnergy[nEntries];
    for(int i=0;i<nEntries;i++) {
      photonEnergy[i]=2.*M_PI*197.326/photonWaveLength[i]*eV;
    }
    G4double refractiveIndex[nEntries];
    for(int i=0;i<nEntries;i++) {
      refractiveIndex[i]=1.;
    }
    G4MaterialPropertiesTable* mpt = new G4MaterialPropertiesTable();
    mpt->AddProperty("RINDEX",       photonEnergy, refractiveIndex,nEntries);
    vacuum->SetMaterialPropertiesTable(mpt);
  }
  
  if(air) {
    /// optical properties of Air
    /**
     *   one representative value for refractive index
     */
    const G4int nEntries=2;
    G4double photonWaveLength[nEntries] = {
      100.0,
      1000.0
    };//[nm]
    G4double photonEnergy[nEntries];
    for(int i=0;i<nEntries;i++) {
      photonEnergy[i]=2.*M_PI*197.326/photonWaveLength[i]*eV;
    }
    G4double refractiveIndex[nEntries];
    for(int i=0;i<nEntries;i++) {
      refractiveIndex[i]=1.;
    }
    G4MaterialPropertiesTable* mpt = new G4MaterialPropertiesTable();
    mpt->AddProperty("RINDEX",       photonEnergy, refractiveIndex,nEntries);
    air->SetMaterialPropertiesTable(mpt);
  }

  if(opAerogel) {
    /// optical properties of Aerogel
    /**
     *   one representative value for refractive index
     */
    const G4int nEntries=2;
    G4double photonWaveLength[nEntries] = {
      300.0,
      700.0
    };//[nm]
    G4double photonEnergy[nEntries];
    for(int i=0;i<nEntries;i++) {
      photonEnergy[i]=2.*M_PI*197.326/photonWaveLength[i]*eV;
    }
    G4double refractiveIndex[nEntries];
    for(int i=0;i<nEntries;i++) {
      refractiveIndex[i]=1.05;
      //refractiveIndex[i]=1.046;
    }
    G4MaterialPropertiesTable* mpt = new G4MaterialPropertiesTable();
    mpt->AddProperty("RINDEX",       photonEnergy, refractiveIndex,nEntries);
    opAerogel->SetMaterialPropertiesTable(mpt);
  }

  if(opGlass) {
    /// glass                                                                                                                                                                        
    const G4int nEntries=2;
    G4double photonWaveLength[nEntries] = {
      100.0,
      1000.0
    };//[nm]                                                                                                                                                                         
    G4double photonEnergy[nEntries];
    for(int i=0;i<nEntries;i++) {
      photonEnergy[i]=2.*M_PI*197.326/photonWaveLength[i]*eV;
    }
    G4double refractiveIndex[nEntries];
    for(int i=0;i<nEntries;i++) {
      refractiveIndex[i]=1.5;
    }
    G4MaterialPropertiesTable* mpt = new G4MaterialPropertiesTable();
    mpt->AddProperty("RINDEX",       photonEnergy, refractiveIndex,nEntries);
    opGlass->SetMaterialPropertiesTable(mpt);
  }

  if(opPC) {
    /// photo cathode                                                                                                                                                                
    /**                                                                                                                                                                              
     *   Used as a detector                                                                                                                                                          
     *   Vacuum (no interaction)                                                                                                                                                     
     *   Glass RINDEX                                                                                                                                                                
     *   Set dielectric-metal boundary                                                                                                                                               
     *     between backing material.                                                                                                                                                 
     *   Edep in the front material.                                                                                                                                                 
     *   Efficiency can be used as Q.E.                                                                                                                                              
     */
    const G4int nEntries=2;
    G4double photonWaveLength[nEntries] = {
      100.0,
      1000.0
    };//[nm]                                                                                                                                                                         
    G4double photonEnergy[nEntries];
    for(int i=0;i<nEntries;i++) {
      photonEnergy[i]=2.*M_PI*197.326/photonWaveLength[i]*eV;
    }
    G4double refractiveIndex[nEntries];
    for(int i=0;i<nEntries;i++) {
      refractiveIndex[i]=1.5;
    }
    G4MaterialPropertiesTable* mpt = new G4MaterialPropertiesTable();
    mpt->AddProperty("RINDEX",       photonEnergy, refractiveIndex,nEntries);
    opPC->SetMaterialPropertiesTable(mpt);
  }

  if(opPMMA) {
    
    const G4int nEntries=16;
    G4double photonWaveLength[nEntries] = {
      260.,
      280.,
      300.,
      320.,
      340.,
      360.,
      380.,
      400.,
      450.,
      500.,
      550.,
      600.,
      700.,
      800.,
      1000.,
      1200.
    };//[nm]                                                                                                                                                                         
    G4double photonEnergy[nEntries];
    for(int i=0;i<nEntries;i++) {
      photonEnergy[i]=2.*M_PI*197.326/photonWaveLength[i]*eV;
    }

    double a=1.491;
    double b=3.427e-3;
    double c=1.819e-4;
    
    G4double refractiveIndex[nEntries];
    for(int i=0;i<nEntries;i++) {
      double x=photonWaveLength[i]*1e-3;
      double nn=
	a+
	b*std::pow(x,-2.)+
	c*std::pow(x,-4.);
      refractiveIndex[i]=nn;
    }
    G4MaterialPropertiesTable* mpt = new G4MaterialPropertiesTable();
    mpt->AddProperty("RINDEX",       photonEnergy, refractiveIndex,nEntries);
    opPMMA->SetMaterialPropertiesTable(mpt);
  }
  
  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


GsimOpticalMaterial::~GsimOpticalMaterial()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  ;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}
