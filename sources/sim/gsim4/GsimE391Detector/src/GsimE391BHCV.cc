/**
 *  @file
 *  @brief  GsimE391BHCV
 *  $Id: GsimE391BHCV.cc,v 1.5 2006/12/06 18:58:52 nanjo Exp $ 
 *  $Log: GsimE391BHCV.cc,v $
 *  Revision 1.5  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimE391Detector/GsimE391BHCV.h"
#include "GsimE391Detector/GsimUserGeom.h"
#include "GsimDetector/GsimBox.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4Box.hh"

using namespace E391;


GsimE391BHCV::GsimE391BHCV(std::string name,
			   GsimDetector* motherDetector,
			   G4ThreeVector transV,G4ThreeVector rotV,
			   int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{

  m_className = "GsimE391BHCV";
  // BHCV

  // Charged Veto
  double c_bhcv_z = Detpos_bhcv_z + 7.0 + 5.0;

  double  s_width  = 12.0;
  double  s_height =  6.0;
  double  s_thick  =  0.3; // 3 mmt  plastic scintillator

  std::vector<double> paramVec;
  paramVec.push_back(s_width*cm);
  paramVec.push_back(s_height*cm);
  paramVec.push_back(s_thick*cm);

  double overlap_v = 1.0;
  double overlap_h = 1.0;

  double xn = s_width/2.0 - overlap_h/2.0;
  double y1 = s_height*1.5 - overlap_v/2.0;
  double y2 = s_height*1.5 - overlap_v;
  double y3 = s_height*0.5;
  double y4 = s_height*0.5 - overlap_v/2.0;
  double z1 = s_thick*1.5;
  double z2 = s_thick*0.5;
  double x[] = { -xn, xn, -xn, xn, -xn, xn, -xn, xn};
  double y[] = { -y1, -y2, -y3, -y4, y4, y3, y2, y1};
  double z[] = { -z1, z1, z2, -z2, -z1, z1, z2, -z2};
  char nam[100];

  sprintf(nam,"BHCV");
  GsimBox* box = new GsimBox(std::string(nam),this,
			     G4ThreeVector(x[0]*cm,y[0]*cm,z[0]*cm),
			     G4ThreeVector(0,0,0));
  box->setParameters(paramVec);
  box->setSensitiveDetector("BHCV",0);
  box->setBriefName(nam);
  addDaughter(box);
  
  for ( int i=1; i<8; i++ ){

    box->cloneDetector(G4ThreeVector(x[i]*cm,y[i]*cm,z[i]*cm),
		       G4ThreeVector(0,0,0),
		       i);
  }
}

GsimE391BHCV::~GsimE391BHCV()
{
  ;
}

