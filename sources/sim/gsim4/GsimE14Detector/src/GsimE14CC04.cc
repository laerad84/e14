/**
 *  @file
 *  @brief  GsimE14CC04
 *  $Id: GsimE14CC04.cc,v 1.3 2006/12/06 19:04:45 nanjo Exp $ 
 *  $Log: GsimE14CC04.cc,v $
 *  Revision 1.3  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimE14Detector/GsimE14CC04.h"
#include "GsimE14Detector/GsimE14UserGeom.h"
#include "GsimDetector/GsimBox.h"
#include "GsimPersistency/GsimMessage.h"

using namespace E14;

GsimE14CC04::GsimE14CC04(std::string name,
			 GsimDetector* motherDetector,
			 G4ThreeVector transV,G4ThreeVector rotV,
			 int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{
  
  m_className = "GsimE14CC04";
  // CC04
  char nam[100];
  m_model=1;


  if(m_model==0) {
    double cc04_len  = Csic_Len;
    double cc04_width = Csic_XY;
    double c_cc04_gap = Csic_Gap;
    double cc04_sci_thk = 0.5;//cm

    double c_cc04_sci_z0 =
      -(cc04_len+c_cc04_gap)*0.5
      -(cc04_sci_thk+c_cc04_gap)*1.5;
    double c_cc04_sci_x_offset[2] = {-0.3, 0.3};
    double c_cc04_sci_y_offset[2] = {-0.3, 0.3};


    int cnt=0;
    GsimBox* box =0;
    GsimBox* box2 =0;

    for(int iz=0;iz<2;iz++) {
      for(int iy=0;iy<13;iy++) {
	for(int ix=0;ix<2;ix++) {
	  double z = c_cc04_sci_z0+(cc04_sci_thk+c_cc04_gap)*iz;
	  double y = (cc04_width+c_cc04_gap)*(iy-6)
	    +c_cc04_sci_y_offset[iz];
	  if(iy>=5 && iy<=7) {
	    sprintf(nam,"CC04SCII");
	    double len=(cc04_width+c_cc04_gap)*(10.*0.5);
	    double off=(cc04_width+c_cc04_gap)*(3.*0.5);
	    double x = (len+off*2.)*(ix-0.5)
	      +c_cc04_sci_x_offset[iz];
	    if(box2==0) {
	      std::vector<double> paramVec;
	      paramVec.push_back(len*cm);
	      paramVec.push_back(cc04_width*cm);
	      paramVec.push_back(cc04_sci_thk*cm);
	      box2 = new GsimBox(std::string(nam),this,
				 G4ThreeVector(x*cm,y*cm,z*cm),
				 G4ThreeVector(0,0,0));
	      box2->setParameters(paramVec);
	      box2->setOuterColor("yellow");
	      box2->setSensitiveDetector("CC04",cnt);
	      addDaughter(box2);
	    } else {
	      box2->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
				  G4ThreeVector(0,0,0),cnt);
	    }
	  } else {
	    sprintf(nam,"CC04SCIO");
	    double len=(cc04_width+c_cc04_gap)*(13.*0.5);
	    double off=0;
	    double x = (len+off*2.)*(ix-0.5)
	      +c_cc04_sci_x_offset[iz];
	    if(box==0) {
	      std::vector<double> paramVec;
	      paramVec.push_back(len*cm);
	      paramVec.push_back(cc04_width*cm);
	      paramVec.push_back(cc04_sci_thk*cm);
	      box = new GsimBox(std::string(nam),this,
				G4ThreeVector(x*cm,y*cm,z*cm),
				G4ThreeVector(0,0,0));
	      box->setParameters(paramVec);
	      box->setOuterColor("yellow");
	      box->setSensitiveDetector("CC04",cnt);
	      addDaughter(box);
	    } else {
	      box->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
				 G4ThreeVector(0,0,0),cnt);
	    }
	  }
	  cnt++;
	}
      }
    }
      
    
    
    cnt=0;
    box =0;
    for(int ix=0;ix<13;ix++) {
      for(int iy=0;iy<13;iy++) {

	if(ix>=5 && ix<=7 &&
	   iy>=5 && iy<=7 ) continue;

	
	double z = 0;
	double x = (cc04_width+c_cc04_gap)*(ix-6);
	double y = (cc04_width+c_cc04_gap)*(iy-6);
	sprintf(nam,"CC04CSI");
	if(box==0) {
	  std::vector<double> paramVec;
	  paramVec.push_back(cc04_width*cm);
	  paramVec.push_back(cc04_width*cm);
	  paramVec.push_back(cc04_len*cm);
	  
	  box = new GsimBox(std::string(nam),this,
			    G4ThreeVector(x*cm,y*cm,z*cm),
			    G4ThreeVector(0,0,0));
	  box->setOuterMaterial("G4_CESIUM_IODIDE");
	  box->setParameters(paramVec);
	  box->setSensitiveDetector("CC04",cnt);
	  addDaughter(box);
	} else {
	  box->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			     G4ThreeVector(0,0,0),cnt);
	}
	cnt++;
      }
    }
    
  } else {

  
    double cc04_len  = Csic_Len;
    double cc04_width = Csic_XY;
    double cc04_sci_thk = 0.5;//cm

    double c_cc04_x_offset[3] = {-0.3, 0,0.3};
    double c_cc04_y_offset[3] = {-0.3, 0,0.3};
    double c_cc04_sci_x_offset[2] = {-0.3, 0.3};
    double c_cc04_sci_y_offset[2] = {-0.3, 0.3};

    double c_cc04_gap = Csic_Gap;
    double c_cc04_y0 = -(cc04_width+c_cc04_gap)*3.5;
    double c_cc04_z0 = -(cc04_width+c_cc04_gap)*1;
    double c_cc04_x[2] = { -(cc04_len+c_cc04_gap)*0.5,
			   (cc04_len+c_cc04_gap)*0.5 };

    double c_cc04_sci_z0 =
      -(cc04_width+c_cc04_gap)*1.5
      -(cc04_sci_thk+c_cc04_gap)*1.5;
  
    int cnt=0;
    GsimBox* box =0;
    for(int iz=0;iz<2;iz++) {
      cnt=0;
      for(int iy=0;iy<8;iy++) {
	for(int ix=0;ix<2;ix++) {
	  double z = c_cc04_sci_z0+(cc04_sci_thk+c_cc04_gap)*iz;
	  double y = c_cc04_y0+(cc04_width+c_cc04_gap)*iy+c_cc04_sci_y_offset[iz];
	  double x=c_cc04_x[ix]+c_cc04_sci_x_offset[iz];
	  if(iy==3 || iy==4) {
	    if(ix==0) x-=7;
	    else      x+=7;
	  }
	  sprintf(nam,"CC04SCI");
	  if(box==0) {
	  
	    std::vector<double> paramVec;
	    paramVec.push_back(cc04_len*cm);
	    paramVec.push_back(cc04_width*cm);
	    paramVec.push_back(cc04_sci_thk*cm);
	  
	    box = new GsimBox(std::string(nam),this,
			      G4ThreeVector(x*cm,y*cm,z*cm),
			      G4ThreeVector(0,0,0));
	    box->setParameters(paramVec);
	    box->setOuterColor("yellow");
	    box->setSensitiveDetector("CC04",cnt);
	    addDaughter(box);
	  } else {
	    box->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			       G4ThreeVector(0,0,0),cnt);
	  }
	  cnt++;
	}
      }
    }

    box=0;
    for(int iz=0;iz<3;iz++) {
      for(int iy=0;iy<8;iy++) {
	for(int ix=0;ix<2;ix++) {
	
	  double z = c_cc04_z0+(cc04_width+c_cc04_gap)*iz;
	  double y = c_cc04_y0+(cc04_width+c_cc04_gap)*iy+c_cc04_y_offset[iz];
	  double x=c_cc04_x[ix]+c_cc04_x_offset[iz];
	  if(iy==3 || iy==4) {
	    if(ix==0) x-=7;
	    else      x+=7;
	  }
	  sprintf(nam,"CC04CSI");
	  if(box==0) {
	  
	    std::vector<double> paramVec;
	    paramVec.push_back(cc04_len*cm);
	    paramVec.push_back(cc04_width*cm);
	    paramVec.push_back(cc04_width*cm);
	  
	    box = new GsimBox(std::string(nam),this,
			      G4ThreeVector(x*cm,y*cm,z*cm),
			      G4ThreeVector(0,0,0));
	    box->setOuterMaterial("G4_CESIUM_IODIDE");
	    box->setParameters(paramVec);
	    box->setSensitiveDetector("CC04",cnt);
	    addDaughter(box);
	  } else {
	    box->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			       G4ThreeVector(0,0,0),cnt);
	  }
	  cnt++;
	}
      }
    }
  }
  setThisAndDaughterBriefName("CC04");
}

GsimE14CC04::~GsimE14CC04()
{
  ;
}

double GsimE14CC04::getCC04Length() {
  double cc04_width = Csic_XY;
  double c_cc04_gap = Csic_Gap;
  return (cc04_width+c_cc04_gap)*3.;
}
