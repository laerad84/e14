/**
 *  @file
 *  @brief  GsimE14LCV
 *  $Id$
 *  $Log$
 */
#include "GsimE14Detector/GsimE14LCV.h"
#include "GsimE14Detector/GsimE14UserGeom.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimDetector/GsimBox.h"

using namespace E14;

GsimE14LCV::GsimE14LCV(std::string name,
		       GsimDetector* motherDetector,
		       G4ThreeVector transV,G4ThreeVector rotV,
		       int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{
  
  m_className = "GsimE14LCV";
  m_model=0;
  if(m_model==0) {
    //double bh=13.8;//cm
    //double th=0.4;//cm
    double bh=14.0;//cm
    double th=0.3;//cm
    
    
    std::vector<double> paramVec;
    paramVec.push_back((bh+th)*cm);
    paramVec.push_back(th*cm);
    paramVec.push_back(CC03_Len_NEW*cm);
    
    GsimBox* box=0;
    box = new GsimBox("LCVbox",this,
		      G4ThreeVector(th/2.*cm,
				    (bh/2.+th/2.)*cm,
				    0.*cm),
		      G4ThreeVector(0,0,0)
		      );
    
    box->setParameters(paramVec);
    box->setOuterColor("yellow");
    box->setSensitiveDetector("LCV",0);
    addDaughter(box);

    box->cloneDetector(G4ThreeVector((bh/2.+th/2.)*cm,
				     -th/2.*cm,
				     0.*cm),
		       G4ThreeVector(0,0,90*deg),1);

    box->cloneDetector(G4ThreeVector(-th/2.*cm,
				     -(bh/2.+th/2.)*cm,
				     0.*cm),
		       G4ThreeVector(0,0,0),2);

    box->cloneDetector(G4ThreeVector(-(bh/2.+th/2.)*cm,
				     th/2.*cm,
				     0.*cm),
		       G4ThreeVector(0,0,90*deg),3);
    
    setThisAndDaughterBriefName("LCV");
  } else {
    ;
  }
}

GsimE14LCV::~GsimE14LCV()
{
  ;
}

