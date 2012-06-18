/**
 *  @file
 *  @brief  GsimE14CC05
 *  $Id: GsimE14CC05.cc,v 1.3 2006/12/06 19:04:45 nanjo Exp $ 
 *  $Log: GsimE14CC05.cc,v $
 *  Revision 1.3  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimE14Detector/GsimE14CC05.h"
#include "GsimE14Detector/GsimE14UserGeom.h"
#include "GsimDetector/GsimBox.h"
#include "GsimPersistency/GsimMessage.h"

using namespace E14;

GsimE14CC05::GsimE14CC05(std::string name,
			 GsimDetector* motherDetector,
			 G4ThreeVector transV,G4ThreeVector rotV,
			 int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{
  
  m_className = "GsimE14CC05";
  // CC05
  char nam[100];
  
  double cc05_len  = Csic_Len;
  double cc05_width = Csic_XY;
  double cc05_sci_thk = 0.5;//cm

  double c_cc05_x_offset[3] = {-0.3, 0,0.3};
  double c_cc05_y_offset[3] = {-0.3, 0,0.3};
  double c_cc05_sci_x_offset[2] = {-0.3, 0.3};
  double c_cc05_sci_y_offset[2] = {-0.3, 0.3};

  double c_cc05_gap = Csic_Gap;
  double c_cc05_y0 = -(cc05_width+c_cc05_gap)*3.5;
  double c_cc05_z0 = -(cc05_width+c_cc05_gap)*1;
  double c_cc05_x[2] = { -(cc05_len+c_cc05_gap)*0.5,
			 (cc05_len+c_cc05_gap)*0.5 };

  double c_cc05_sci_z0 =
    +(cc05_width+c_cc05_gap)*1.5
    +(cc05_sci_thk+c_cc05_gap)*0.5;
  
  int cnt=0;
  GsimBox* box =0;
  for(int iz=0;iz<3;iz++) {
    for(int iy=0;iy<8;iy++) {
      for(int ix=0;ix<2;ix++) {
	
	double z = c_cc05_z0+(cc05_width+c_cc05_gap)*iz;
	double y = c_cc05_y0+(cc05_width+c_cc05_gap)*iy+c_cc05_y_offset[iz];
	double x=c_cc05_x[ix]+c_cc05_x_offset[iz];
	if(iy==3 || iy==4) {
	  if(ix==0) x-=7;
	  else      x+=7;
	}
	sprintf(nam,"CC05CSI");
	if(box==0) {
	  
	  std::vector<double> paramVec;
	  paramVec.push_back(cc05_len*cm);
	  paramVec.push_back(cc05_width*cm);
	  paramVec.push_back(cc05_width*cm);
	  
	  box = new GsimBox(std::string(nam),this,
			    G4ThreeVector(x*cm,y*cm,z*cm),
			    G4ThreeVector(0,0,0));
	  box->setOuterMaterial("G4_CESIUM_IODIDE");
	  box->setParameters(paramVec);
	  box->setSensitiveDetector("CC05",cnt);
	  addDaughter(box);
	} else {
	  box->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			     G4ThreeVector(0,0,0),cnt);
	}
	cnt++;
      }
    }
  }

  int cntNow=cnt;

  box=0;
  for(int iz=0;iz<2;iz++) {
    cnt=cntNow;
    for(int iy=0;iy<8;iy++) {
      for(int ix=0;ix<2;ix++) {
	double z = c_cc05_sci_z0+(cc05_sci_thk+c_cc05_gap)*iz;
	double y = c_cc05_y0+(cc05_width+c_cc05_gap)*iy+c_cc05_sci_y_offset[iz];
	double x=c_cc05_x[ix]+c_cc05_sci_x_offset[iz];
	if(iy==3 || iy==4) {
	  if(ix==0) x-=7;
	  else      x+=7;
	}
	sprintf(nam,"CC05SCI");
	if(box==0) {
	  
	  std::vector<double> paramVec;
	  paramVec.push_back(cc05_len*cm);
	  paramVec.push_back(cc05_width*cm);
	  paramVec.push_back(cc05_sci_thk*cm);
	  
	  box = new GsimBox(std::string(nam),this,
				     G4ThreeVector(x*cm,y*cm,z*cm),
				     G4ThreeVector(0,0,0));
	  box->setParameters(paramVec);
	  box->setOuterColor("yellow");
	  box->setSensitiveDetector("CC05",cnt);
	  addDaughter(box);
	} else {
	  box->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			     G4ThreeVector(0,0,0),cnt);
	}
	cnt++;
      }
    }
  }
  setThisAndDaughterBriefName("CC05");
}

GsimE14CC05::~GsimE14CC05()
{
  ;
}

double GsimE14CC05::getCC05Length() {
  double cc05_width = Csic_XY;
  double c_cc05_gap = Csic_Gap;
  return (cc05_width+c_cc05_gap)*3.;
}
