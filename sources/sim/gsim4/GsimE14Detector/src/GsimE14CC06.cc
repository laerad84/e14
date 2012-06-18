/**
 *  @file
 *  @brief  GsimE14CC06
 *  $Id: GsimE14CC06.cc,v 1.3 2006/12/06 19:04:45 nanjo Exp $ 
 *  $Log: GsimE14CC06.cc,v $
 *  Revision 1.3  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimE14Detector/GsimE14CC06.h"
#include "GsimE14Detector/GsimE14UserGeom.h"
#include "GsimDetector/GsimBox.h"
#include "GsimPersistency/GsimMessage.h"

using namespace E14;

GsimE14CC06::GsimE14CC06(std::string name,
			 GsimDetector* motherDetector,
			 G4ThreeVector transV,G4ThreeVector rotV,
			 int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{
  
  m_className = "GsimE14CC06";
  // CC06
  char nam[100];
  
  double cc06_len  = Csic_Len;
  double cc06_width = Csic_XY;

  double c_cc06_x_offset[3] = {-0.3, 0,0.3};
  double c_cc06_y_offset[3] = {-0.3, 0,0.3};

  double c_cc06_gap = Csic_Gap;
  double c_cc06_y0 = -(cc06_width+c_cc06_gap)*3.5;
  double c_cc06_z0 = -(cc06_width+c_cc06_gap)*1;
  double c_cc06_x[2] = { -(cc06_len+c_cc06_gap)*0.5,
			 (cc06_len+c_cc06_gap)*0.5 };

  int cnt=0;
  GsimBox* box =0;
  for(int iz=0;iz<3;iz++) {
    for(int iy=0;iy<8;iy++) {
      for(int ix=0;ix<2;ix++) {
	
	double z = c_cc06_z0+(cc06_width+c_cc06_gap)*iz;
	double y = c_cc06_y0+(cc06_width+c_cc06_gap)*iy+c_cc06_y_offset[iz];
	double x=c_cc06_x[ix]+c_cc06_x_offset[iz];
	if(iy==3 || iy==4) {
	  if(ix==0) x-=7;
	  else      x+=7;
	}
	sprintf(nam,"CC06CSI");
	if(box==0) {
	  
	  std::vector<double> paramVec;
	  paramVec.push_back(cc06_len*cm);
	  paramVec.push_back(cc06_width*cm);
	  paramVec.push_back(cc06_width*cm);
	  
	  box = new GsimBox(std::string(nam),this,
			    G4ThreeVector(x*cm,y*cm,z*cm),
			    G4ThreeVector(0,0,0));
	  box->setOuterMaterial("G4_CESIUM_IODIDE");
	  box->setParameters(paramVec);
	  box->setSensitiveDetector("CC06",cnt);
	  addDaughter(box);
	} else {
	  box->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			     G4ThreeVector(0,0,0),cnt);
	}
	cnt++;
      }
    }
  }
  setThisAndDaughterBriefName("CC06");
}

GsimE14CC06::~GsimE14CC06()
{
  ;
}

double GsimE14CC06::getCC06Length() {
  double cc06_width = Csic_XY;
  double c_cc06_gap = Csic_Gap;
  return (cc06_width+c_cc06_gap)*3.;
}
