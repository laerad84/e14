/**
 *  $Id: GsimMaterialManager.cc,v 1.12 2006/12/06 18:44:00 nanjo Exp $
 *  $Log: GsimMaterialManager.cc,v $
 *  Revision 1.12  2006/12/06 18:44:00  nanjo
 *  Midas I/O is added and Root I/O is separated. etc.
 *
 */
#include "GsimKernel/GsimMaterialManager.h"
#include "GsimKernel/GsimMaterialManagerMessenger.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4MaterialPropertiesTable.hh"

#include <sstream>

GsimMaterialManager::GsimMaterialManager()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_messenger = new GsimMaterialManagerMessenger(this);

  // for GsimDetectorConstruction
  useNistMaterial("G4_AIR");
  // for GsimDetector
  useNistMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif    
}

GsimMaterialManager::~GsimMaterialManager()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  delete m_messenger;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  
}

void GsimMaterialManager::useNistMaterial(std::string matname)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4Material* mat=0;
  mat = G4Material::GetMaterial(G4String(matname.c_str()),false);
  if(!mat) {
    mat = G4NistManager::Instance()
      ->FindOrBuildMaterial(G4String(matname.c_str()),true);
  }
  if(!mat) {
    {
      std::ostringstream ostr;
      ostr << "The material, "
	   << matname
	   << " ,can not be used.";
      GsimMessage::getInstance()
	->report("warning",ostr.str());
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  
}



void GsimMaterialManager::defineMaterials()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif

  // ==================================================================
  /**
   * elements...
   *   G4NistManager stores many elements and materials.
   *   You can retrieve a G4Element* as
   *         nist->FindOrBuildElement("I");
   *   or a G4Material* as
   *         nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");
   *   .
   */
  
  G4NistManager* nist = G4NistManager::Instance();

  
  // ================================================================== 
  /** materials...
   *    You should build materials which G4NistMaanger doesn't store
   *       and materials to which optical properties will be attached.
   */

  G4String name;
  G4double density, pressure,temperature;
  G4int nel,natom;

  // lead antimony (Pb includeing 6%Sb)
  density = 11.0945 *g/cm3;
  G4Material* PbSb
    = new G4Material(name="GsimPbSb",density,nel=2);
  PbSb->AddElement(nist->FindOrBuildElement("Pb"), 94.*perCent);
  PbSb->AddElement(nist->FindOrBuildElement("Sb"), 6.*perCent);

  // brass 
  density = 8.61 *g/cm3;
  G4Material* Brass
    = new G4Material(name="GsimBrass",density,nel=4);
  Brass->AddElement(nist->FindOrBuildElement("Cu"), 60.*perCent);
  Brass->AddElement(nist->FindOrBuildElement("Pb"), 2.5*perCent);
  Brass->AddElement(nist->FindOrBuildElement("Fe"), 3.5*perCent);
  Brass->AddElement(nist->FindOrBuildElement("Zn"), 34.*perCent);
    

  // sainless steel
  density = 7.8 *g/cm3;
  G4Material* SUS
    = new G4Material(name="GsimSUS",density,nel=6);
  SUS->AddElement(nist->FindOrBuildElement("Fe"), 68.*perCent);
  SUS->AddElement(nist->FindOrBuildElement("Cr"), 20.*perCent);
  SUS->AddElement(nist->FindOrBuildElement("Ni"),  9.*perCent);
  SUS->AddElement(nist->FindOrBuildElement("Mn"),  1.*perCent);
  SUS->AddElement(nist->FindOrBuildElement("Si"),  1.*perCent);
  SUS->AddElement(nist->FindOrBuildElement("C"),   1.*perCent);

  // sainless steel
  density = 7.93 *g/cm3;
  G4Material* SUS304
    = new G4Material(name="GsimSUS304",density,nel=3);
  SUS304->AddElement(nist->FindOrBuildElement("Fe"), 74*perCent);
  SUS304->AddElement(nist->FindOrBuildElement("Cr"), 18*perCent);
  SUS304->AddElement(nist->FindOrBuildElement("Ni"),  8.*perCent);

  //tungsten alloy
  density = 17.9*g/cm3;
  G4Material* WNiCu
    = new G4Material(name="GsimWNiCu",density,nel=3);
  WNiCu->AddElement(nist->FindOrBuildElement("W"), 94*perCent);
  WNiCu->AddElement(nist->FindOrBuildElement("Ni"), 4*perCent);
  WNiCu->AddElement(nist->FindOrBuildElement("Cu"), 2.*perCent);


  //CFRP
  //  Wf=66% (carbon) 
  //  RC=33% (resin) 
  //  Epoxy: C8H8O=120 density:1.85
  //  Carbon: C10 =120 density:1.81
  //-------------------------------
  //    C28H8O
  density = 1.81*g/cm3;
  G4Material* CFRP
    = new G4Material(name="GsimCFRP",density,nel=3);
  CFRP->AddElement(nist->FindOrBuildElement("C"), natom=28);
  CFRP->AddElement(nist->FindOrBuildElement("H"), natom=8);
  CFRP->AddElement(nist->FindOrBuildElement("O"), natom=1);



  // aerogel
  // n(SiO2)+2n(H2O)=SiO4H4
  density = 0.11*g/cm3;
  G4Material* Aerogel
    = new G4Material(name="GsimAerogel",density,nel=3);
  Aerogel->AddElement(nist->FindOrBuildElement("Si"), natom=1);
  Aerogel->AddElement(nist->FindOrBuildElement("H"),  natom=4);
  Aerogel->AddElement(nist->FindOrBuildElement("O"),  natom=4);


  // membrane
  // CH2
  density = 1*g/cm3;
  G4Material* Membrane
    = new G4Material(name="GsimMembrane",density,nel=2);
  Membrane->AddElement(nist->FindOrBuildElement("C"), natom=1);
  Membrane->AddElement(nist->FindOrBuildElement("H"), natom=2);
  
  /// Vacuum
  density     = universe_mean_density;    //from PhysicalConstants.h
  pressure    = 3.e-18*pascal;
  temperature = 2.73*kelvin;
  G4Material* vacuum0 = 
    new G4Material(name="GsimVacuum", density, nel=1,
		   kStateGas,temperature,pressure);
  vacuum0->AddElement(nist->FindOrBuildElement("H"), 1);
  vacuum0->GetIonisation()->SetMeanExcitationEnergy(19.2*eV);


  
  pressure    = 0.1*pascal;
  temperature = 293*kelvin;
  density     = 14./(0.082*293)*1e-3*(0.1/1e5)*g/cm3;
  G4Material* vacuumL = 
    new G4Material(name="GsimLowVacuum", density, nel=1,
		   kStateGas,temperature,pressure);
  vacuumL->AddElement(nist->FindOrBuildElement("N"), 1);

  pressure    = 1.e-5*pascal;
  temperature = 293*kelvin;
  density     = 14./(0.082*293)*1e-3*(1.e-5/1e5)*g/cm3;
  G4Material* vacuumH = 
    new G4Material(name="GsimHighVacuum", density, nel=1,
		   kStateGas,temperature,pressure);
  vacuumH->AddElement(nist->FindOrBuildElement("N"), 1);






  //Optical
  //Aerogel
  name="GsimOpticalAerogel";
  density = 0.11*g/cm3;
  G4Material* opAerogel= new G4Material(name,density,nel=3);
  // aerogel
  // n(SiO2)+2n(H2O)=SiO4H4
  opAerogel->AddElement(nist->FindOrBuildElement("Si"), natom=1);
  opAerogel->AddElement(nist->FindOrBuildElement("H"),  natom=4);
  opAerogel->AddElement(nist->FindOrBuildElement("O"),  natom=4);
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
  
  

  
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  

}


void GsimMaterialManager::mixElement(std::string name,
				     double density,
				     double pressure,
				     double temperature,
				     std::vector<std::string> elementVec,
				     std::vector<double> weightVec)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4NistManager* nist = G4NistManager::Instance();
  
  int nEle=elementVec.size();
  if(nEle!=int(weightVec.size())) {
    std::ostringstream ostr;
    ostr << "The material, "
	 << name
	 << " ,is not created due to invalid number.";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
    return;
  }

  double totW=0;
  for(std::vector<double>::iterator itW=weightVec.begin();
      itW!=weightVec.end();itW++) {
    totW+=(*itW);
  }
  if(std::abs(totW-1.)>0.001) {
    std::ostringstream ostr;
    ostr << "The material, "
	 << name
	 << " ,is not created due to total fraction error.";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
    return; 
  }

  for(std::vector<std::string>::iterator itN=elementVec.begin();
      itN!=elementVec.end();itN++) {
    G4Element* elm=nist->FindOrBuildElement((*itN).c_str());
    if(!elm) {
      std::ostringstream ostr;
      ostr << "The material, "
	   << name
	   << " ,is not created due to unknown element,"
	   << (*itN)
	   << ".";
      GsimMessage::getInstance()
	->report("warning",ostr.str());
      return; 
    }
  }
  
  
  G4String matName=name.c_str();
  G4Material* mat
    = new G4Material(matName,density,nEle,
		     kStateUndefined,temperature,pressure);

  std::vector<std::string>::iterator itN=elementVec.begin();
  std::vector<double>::iterator      itW=weightVec.begin();
  
  for(;itN!=elementVec.end();itN++,itW++) {
    mat->AddElement(nist->FindOrBuildElement((*itN).c_str()), (*itW));
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  
}

void GsimMaterialManager::mixElement(std::string name,
				     double density,
				     double pressure,
				     double temperature,
				     std::vector<std::string> elementVec,
				     std::vector<int> numVec)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  G4NistManager* nist = G4NistManager::Instance();
  
  int nEle=elementVec.size();
  if(nEle!=int(numVec.size())) {
    std::ostringstream ostr;
    ostr << "The material, "
	 << name
	 << " ,is not created due to invalid number.";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
    return;
  }

  for(std::vector<std::string>::iterator itN=elementVec.begin();
      itN!=elementVec.end();itN++) {
    G4Element* elm=nist->FindOrBuildElement((*itN).c_str());
    if(!elm) {
      std::ostringstream ostr;
      ostr << "The material, "
	   << name
	   << " ,is not created due to unknown element,"
	   << (*itN)
	   << ".";
      GsimMessage::getInstance()
	->report("warning",ostr.str());
      return; 
    }
  }
  
  
  G4String matName=name.c_str();
  G4Material* mat
    = new G4Material(matName,density,nEle,
		     kStateUndefined,temperature,pressure);

  std::vector<std::string>::iterator itN=elementVec.begin();
  std::vector<int>::iterator         itW=numVec.begin();
  
  for(;itN!=elementVec.end();itN++,itW++) {
    mat->AddElement(nist->FindOrBuildElement((*itN).c_str()), (*itW));
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif  
}


void GsimMaterialManager::setProperty(std::string matName,std::string type,
				      std::vector<double> photonWaveLengthVector,
				      std::vector<double> propertyVector)
{
  G4Material* mat=0;
  mat = G4Material::GetMaterial(G4String(matName.c_str()),false);
  if(!mat) {
    std::ostringstream ostr;
    ostr << "No such material : " << matName << ".";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
    return;
  }

  G4MaterialPropertiesTable* MPT=mat->GetMaterialPropertiesTable();
  if(!MPT) {
    MPT = new G4MaterialPropertiesTable();
    mat->SetMaterialPropertiesTable(MPT);
  }
  

  if(photonWaveLengthVector.size() !=propertyVector.size()) {
    std::ostringstream ostr;
    ostr << "Vector sizes are different. ";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
    return;
  }

  int num=photonWaveLengthVector.size();
  if(num>0) {
    double* pe = new double[num];
    double* re = new double[num];
    for(int i=0;i<num;i++) {
      pe[i] = 2.*M_PI*197.326/photonWaveLengthVector[i]*eV;
      re[i] = propertyVector[i];
    }
    MPT->AddProperty(type.c_str(),pe,re,num);
    delete [] pe;
    delete [] re;
  } else {
    MPT->RemoveProperty(type.c_str());
  }
}



void GsimMaterialManager::setConstProperty(std::string matName,std::string type,
					   double value)
{
  G4Material* mat=0;
  mat = G4Material::GetMaterial(G4String(matName.c_str()),false);
  if(!mat) {
    std::ostringstream ostr;
    ostr << "No such material : " << matName << ".";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
    return;
  }

  G4MaterialPropertiesTable* MPT=mat->GetMaterialPropertiesTable();
  if(!MPT) {
    MPT = new G4MaterialPropertiesTable();
    mat->SetMaterialPropertiesTable(MPT);
  }
  
  if(value!=-999) {
    MPT->AddConstProperty(type.c_str(),value);
  } else {
    MPT->RemoveConstProperty(type.c_str());
  }
}


void GsimMaterialManager::dumpProperty(std::string matName)
{
  G4Material* mat=0;
  mat = G4Material::GetMaterial(G4String(matName.c_str()),false);
  if(!mat) {
    std::ostringstream ostr;
    ostr << "No such material : " << matName << ".";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
    return;
  }

  G4MaterialPropertiesTable* MPT=mat->GetMaterialPropertiesTable();
  if(MPT) MPT->DumpTable();
}

void GsimMaterialManager::listMaterial()
{
  G4cout << "--- Materials ---" << G4endl;
  const G4MaterialTable* tab=G4Material::GetMaterialTable();
  for(G4MaterialTable::const_iterator it=tab->begin();
      it!=tab->end();it++) {
    G4cout << (*it)->GetName() << G4endl;
  }
  G4cout << "--- -------------" << G4endl;
}
