/**
 *  @file
 *  @brief  GsimE14BHCV
 *  $Id: GsimE14BHCV.cc,v 1.3 2006/12/06 19:04:45 nanjo Exp $ 
 *  $Log: GsimE14BHCV.cc,v $
 *  Revision 1.3  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimE14Detector/GsimE14BHCV.h"
#include "GsimE14Detector/GsimE14UserGeom.h"
#include "GsimDetector/GsimBox.h"
#include "GsimPersistency/GsimMessage.h"

using namespace E14;

GsimE14BHCV::GsimE14BHCV(std::string name,
			 GsimDetector* motherDetector,
			 G4ThreeVector transV,G4ThreeVector rotV,
			 int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{
  
  m_className = "GsimE14BHCV";
  // BHCV

  // Charged Veto
  double c_bhcv_z = Detpos_bhcv_z + 7.0 + 5.0;

  double  s_width  = 10.5;
  double  s_height =  3.0;
  double  s_thick  =  0.3; // 3 mmt  plastic scintillator

  std::vector<double> paramVec;
  paramVec.push_back(s_width*cm);
  paramVec.push_back(s_height*cm);
  paramVec.push_back(s_thick*cm);

  double overlap_v = 0.5;
  double overlap_h = 0.5;

  double y_offset=-s_height*3.5+overlap_v*3;
  
  char nam[100];
  sprintf(nam,"BHCV");
  GsimBox* box=0;
  int cnt=0;
  for (int iy=0; iy<8; iy++ ){
    double y=y_offset+(s_height-overlap_v)*iy;
    for(int ix=0;ix<2;ix++) {
      double x=-(s_width/2. - overlap_h/2.);
      if(ix==1) {
	x=(s_width/2. - overlap_h/2.);
	y+=overlap_v/2.;
      }
      
      double z=0;
      int iz=cnt%4;
      if(iz==0) {
	z=-s_thick*1.5;
      } else if(iz==1) {
	z=s_thick*1.5;
      } else if(iz==2) {
	z=s_thick*0.5;
      } else {
	z=-s_thick*0.5;
      }
      
      if(box==0) {
	box = new GsimBox(std::string(nam),this,
			  G4ThreeVector(x*cm,y*cm,z*cm),
			  G4ThreeVector(0,0,0));
	box->setParameters(paramVec);
	box->setSensitiveDetector("BHCV",cnt);
	addDaughter(box);
      } else {
	box->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			   G4ThreeVector(0,0,0),
			   cnt);
      }
      cnt++;
    }
  }
  setThisAndDaughterBriefName("BHCV");
}

GsimE14BHCV::~GsimE14BHCV()
{
  ;
}

double GsimE14BHCV::getBHCVLength() {
  double  s_thick  =  0.3; // 3 mmt  plastic scintillator
  return s_thick*4;
}
