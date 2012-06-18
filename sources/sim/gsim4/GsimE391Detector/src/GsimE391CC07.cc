/**
 *  @file
 *  @brief  GsimE391CC07
 *  $Id: GsimE391CC07.cc,v 1.7 2006/12/06 18:58:52 nanjo Exp $ 
 *  $Log: GsimE391CC07.cc,v $
 *  Revision 1.7  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimE391Detector/GsimE391CC07.h"
#include "GsimE391Detector/GsimUserGeom.h"
#include "GsimDetector/GsimBox.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4Box.hh"

using namespace E391;

GsimE391CC07::GsimE391CC07(std::string name,
			   GsimDetector* motherDetector,
			   G4ThreeVector transV,G4ThreeVector rotV,
			   int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{

  m_className = "GsimE391CC07";
  // CC07
  double  cc07_len  = 15.0;
  double  cc07_width = 30.0;

  std::vector<double> paramVec;
  paramVec.push_back(cc07_width*cm);
  paramVec.push_back(cc07_len*cm);
  paramVec.push_back(cc07_len*cm);

  char nam[100];

  
  //double c_cc07_z = 995 + cc07_len/2;
  double c_cc07_z = Detpos_cc07_z + cc07_len/2; // from Misha's measurement

  double c_cc07_x_offset[] = {-0.36, 0.65, -0.1, -0.1, -1.15};
  
  double c_gap_side = 0.03;
  double c_gap_top = 0.02;

  double c_cc07_y0 = -30. - c_gap_top*2.0;

  double y = c_cc07_y0 + 0.*15.0 + 0.*c_gap_top;
  double x = 15.0 + c_cc07_x_offset[0] + c_gap_side;

  sprintf(nam,"CC07");
  GsimBox* box = new GsimBox(std::string(nam),this,
			     G4ThreeVector(x*cm,y*cm,0),
			     G4ThreeVector(0,0,0));
  box->setOuterMaterial("G4_GLASS_LEAD");
  box->setParameters(paramVec);
  box->setSensitiveDetector("CC07",0);
  box->setBriefName(nam);
  addDaughter(box);
    
  
  int cnt=0;
  for ( int i=0 ; i<5 ; i++) {
    
    y = c_cc07_y0 + i*15.0 + i*c_gap_top;
    x =0.0;
    
    if ( i == 2 ) 
      x = 15.0 + 7.5 + c_cc07_x_offset[i] + c_gap_side;
    else
      x = 15.0 + c_cc07_x_offset[i] + c_gap_side;

    if(cnt!=0) {
      box->cloneDetector(G4ThreeVector(x*cm,y*cm,0),
			 G4ThreeVector(0,0,0),cnt);
    }
    cnt++;
    
    if ( i == 2 ) 
      x = -15.0 - 7.5 + c_cc07_x_offset[i] - c_gap_side;
    else
      x = -15.0 + c_cc07_x_offset[i] - c_gap_side;

    box->cloneDetector(G4ThreeVector(x*cm,y*cm,0),
		       G4ThreeVector(0,0,0),cnt);
    cnt++;
  }
}

GsimE391CC07::~GsimE391CC07()
{
  ;
}

