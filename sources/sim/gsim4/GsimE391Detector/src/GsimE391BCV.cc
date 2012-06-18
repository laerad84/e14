/**
 *  @file
 *  @brief  GsimE391BCV
 *  $Id: GsimE391BCV.cc,v 1.7 2006/12/06 18:58:52 nanjo Exp $ 
 *  $Log: GsimE391BCV.cc,v $
 *  Revision 1.7  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimE391Detector/GsimE391BCV.h"
#include "GsimE391Detector/GsimUserGeom.h"
#include "GsimDetector/GsimBox.h"
#include "GsimPersistency/GsimMessage.h"
#include "G4Box.hh"

using namespace E391;


GsimE391BCV::GsimE391BCV(std::string name,
			 GsimDetector* motherDetector,
			 G4ThreeVector transV,G4ThreeVector rotV,
			 int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{

  m_className = "GsimE391BCV";

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
  box->setBriefName(nam);
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
}

GsimE391BCV::~GsimE391BCV()
{
  ;
}

