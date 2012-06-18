/**
 *  @file
 *  @brief  GsimE14BCV
 *  $Id: GsimE14BCV.cc,v 1.3 2006/12/06 19:04:45 nanjo Exp $ 
 *  $Log: GsimE14BCV.cc,v $
 *  Revision 1.3  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimE14Detector/GsimE14BCV.h"
#include "GsimE14Detector/GsimE14UserGeom.h"
#include "GsimDetector/GsimBox.h"
#include "GsimPersistency/GsimMessage.h"
#include "G4Box.hh"

using namespace E14;

GsimE14BCV::GsimE14BCV(std::string name,
		       GsimDetector* motherDetector,
		       G4ThreeVector transV,G4ThreeVector rotV,
		       int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{

  m_className = "GsimE14BCV";

  double  bcv_x = 0.5;
  double  bcv_y = 19.72;
  double  bcv_z = Cbar_Len;

  double  x = 100.3 + bcv_x/2;
  double  y = 0;
  double  z = 135 + Cbar_Len/2;

  std::vector<double> paramVec;
  paramVec.push_back(bcv_x*cm);
  paramVec.push_back(bcv_y*cm);
  paramVec.push_back(bcv_z*cm);

  char nam[100];
  G4ThreeVector c1ini( x*cm,         y*cm,     0 );
  G4ThreeVector c2ini( (x+0.5)*cm, (y-0.5)*cm, 0 );
  sprintf(nam,"BCV");
  GsimBox* box = new GsimBox(std::string(nam),this,
			     c1ini,
			     G4ThreeVector(0,0,0));
  box->setParameters(paramVec);
  box->setSensitiveDetector("BCV",0);
  addDaughter(box);

  
  for( int i=0;i<32;i++ ){
    G4ThreeVector c1( x*cm,         y*cm,     0 );
    G4ThreeVector c2( (x+0.5)*cm, (y-0.5)*cm, 0 );
    c1.rotateZ( 2.*M_PI*i/32 );
    c2.rotateZ( 2.*M_PI*i/32 );

    if(i!=0) {
      box->cloneDetector(c1,
			 G4ThreeVector(0,0,2.*M_PI*i/32),i);
    }
    
    box->cloneDetector(c2,
		       G4ThreeVector(0,0,2.*M_PI*i/32),i);
  }
  setThisAndDaughterBriefName("BCV");
}

GsimE14BCV::~GsimE14BCV()
{
  ;
}
