/**
 *  $Id: $
 *  $Log:$
 */
#include "GsimKernel/GsimSurface.h"
#include "GsimKernel/GsimSurfaceMessenger.h"
#include "GsimKernel/GsimDetector.h"
#include "GsimKernel/GsimUtil.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4VPhysicalVolume.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4MaterialPropertiesTable.hh"

#include <sstream>
#include <cmath>

GsimSurface::GsimSurface(std::string name,
			 GsimDetector* vol1Detector,
			 GsimDetector* vol2Detector)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_name=name;
  if(vol1Detector==0 || vol2Detector==0) {
    std::ostringstream ostr;
    ostr << "No GsimDetector.";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
    return;
  }
  
  m_vol1=vol1Detector->getPhysiDetector();
  m_vol2=vol2Detector->getPhysiDetector();

  if(m_vol1==0) {
    std::ostringstream ostr;
    ostr << "No physical volume is associated to the  GsimDetector, "
	 << vol1Detector->getFullName() << ".";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
    return;
  }

  if(m_vol2==0) {
    std::ostringstream ostr;
    ostr << "No physical volume is associated to the  GsimDetector, "
	 << vol2Detector->getFullName() << ".";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
    return;
  }
  m_opticalSurface = new G4OpticalSurface(G4String(name.c_str()));
  new G4LogicalBorderSurface(G4String(name.c_str()),m_vol1,m_vol2,m_opticalSurface);


  //m_opticalSurface->SetMaterialPropertiesTable(G4MaterialPropertiesTable *anMPT)
    
  m_messenger = new GsimSurfaceMessenger(this);
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


GsimSurface::~GsimSurface()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  delete m_messenger;
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}


void GsimSurface::setSurfaceProperty(G4SurfaceType type,
				     G4OpticalSurfaceFinish finish,
				     G4OpticalSurfaceModel model,
				     double param)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  m_opticalSurface->SetType(type);
  m_opticalSurface->SetFinish(finish);
  m_opticalSurface->SetModel(model);
  if(model==glisur) {
    m_opticalSurface->SetPolish(param);
  } else if(model==unified) {
    m_opticalSurface->SetSigmaAlpha(param);
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}
  
void GsimSurface::setRefractiveIndex(std::vector<double> photonWaveLengthVector,
				     std::vector<double> refractiveIndexVector)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(photonWaveLengthVector.size() !=refractiveIndexVector.size()) {
    std::ostringstream ostr;
    ostr << "Vector sizes are different. ";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
    return;
  }

  G4MaterialPropertiesTable* MPT=m_opticalSurface->GetMaterialPropertiesTable();
  if(MPT==0) {
    MPT= new G4MaterialPropertiesTable();
    m_opticalSurface->SetMaterialPropertiesTable(MPT);
  }
  
  int num=photonWaveLengthVector.size();
  if(num>0) {
    double* pe = new double[num];
    double* re = new double[num];
    for(int i=0;i<num;i++) {
      pe[i] = 2.*M_PI*197.326/photonWaveLengthVector[i]*eV;
      re[i] = refractiveIndexVector[i];
    }
    MPT->AddProperty("RINDEX",pe,re,num);
    delete [] pe;
    delete [] re;
  } else {
    MPT->RemoveProperty("RINDEX");
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimSurface::setReflectiveity(std::vector<double> photonWaveLengthVector,
				   std::vector<double> reflectivityVector)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(photonWaveLengthVector.size() !=reflectivityVector.size()) {
    std::ostringstream ostr;
    ostr << "Vector sizes are different. ";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
    return;
  }

  G4MaterialPropertiesTable* MPT=m_opticalSurface->GetMaterialPropertiesTable();
  if(MPT==0) {
    MPT= new G4MaterialPropertiesTable();
    m_opticalSurface->SetMaterialPropertiesTable(MPT);
  }
  
  int num=photonWaveLengthVector.size();
  if(num>0) {
    double* pe = new double[num];
    double* re = new double[num];
    for(int i=0;i<num;i++) {
      pe[i] = 2.*M_PI*197.326/photonWaveLengthVector[i]*eV;
      re[i] = reflectivityVector[i];
    }
    MPT->AddProperty("REFLECTIVITY",pe,re,num);
    delete [] pe;
    delete [] re;
  } else {
    MPT->RemoveProperty("REFLECTIVITY");
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}



void GsimSurface::setEfficiency(std::vector<double> photonWaveLengthVector,
				std::vector<double> efficiencyVector)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(photonWaveLengthVector.size() !=efficiencyVector.size()) {
    std::ostringstream ostr;
    ostr << "Vector sizes are different. ";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
    return;
  }

  G4MaterialPropertiesTable* MPT=m_opticalSurface->GetMaterialPropertiesTable();
  if(MPT==0) {
    MPT= new G4MaterialPropertiesTable();
    m_opticalSurface->SetMaterialPropertiesTable(MPT);
  }
  int num=photonWaveLengthVector.size();
  if(num>0) {
    double* pe = new double[num];
    double* re = new double[num];
    for(int i=0;i<num;i++) {
      pe[i] = 2.*M_PI*197.326/photonWaveLengthVector[i]*eV;
      re[i] = efficiencyVector[i];
    }
    
    MPT->AddProperty("EFFICIENCY",pe,re,num);
    delete [] pe;
    delete [] re;
  } else {
    MPT->RemoveProperty("EFFICIENCY");
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}

void GsimSurface::setProperty(std::string type,
			      std::vector<double> photonWaveLengthVector,
			      std::vector<double> propertyVector)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(photonWaveLengthVector.size() !=propertyVector.size()) {
    std::ostringstream ostr;
    ostr << "Vector sizes are different. ";
    GsimMessage::getInstance()
      ->report("warning",ostr.str());
    return;
  }

  

  G4MaterialPropertiesTable* MPT=m_opticalSurface->GetMaterialPropertiesTable();
  if(MPT==0) {
    MPT= new G4MaterialPropertiesTable();
    m_opticalSurface->SetMaterialPropertiesTable(MPT);
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
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}
			      
				
void GsimSurface::dump()
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  if(m_vol1 && m_vol2) {
    G4cout << m_vol1->GetName() << "\t" << m_vol2->GetName() << G4endl;
  }
  G4LogicalBorderSurface::DumpInfo();
  if(m_opticalSurface) {
    m_opticalSurface->DumpInfo();
    G4MaterialPropertiesTable* MPT
      =m_opticalSurface->GetMaterialPropertiesTable();
    if(MPT) MPT->DumpTable();
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif
}
