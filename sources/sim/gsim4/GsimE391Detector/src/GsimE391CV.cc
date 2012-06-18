/**
 *  @file
 *  @brief  GsimE391CV
 *  $Id: GsimE391CV.cc,v 1.8 2007/02/04 12:56:46 nanjo Exp $ 
 *  $Log: GsimE391CV.cc,v $
 *  Revision 1.8  2007/02/04 12:56:46  nanjo
 *  GsimBoxWithAHole is used.
 *
 *  Revision 1.7  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimE391Detector/GsimE391CV.h"
#include "GsimE391Detector/GsimUserGeom.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimDetector/GsimPolyhedra2.h"
#include "GsimDetector/GsimTrap.h"
#include "GsimDetector/GsimTube.h"
#include "GsimDetector/GsimBox.h"

using namespace E391;

GsimE391CV::GsimE391CV(std::string name,
		       GsimDetector* motherDetector,
		       G4ThreeVector transV,G4ThreeVector rotV,
		       int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{

  m_className = "GsimE391CV";






  int  ivol=0;

  // CV
  double  chv_rmax  = 99;
  double  chv_thick = 0.6; // 6 mm scintillator
  double  chv_zdiff = 1.3; // 1.3cm shifted

  // inner support
  int     chvs1_ndiv  = 4;
  double  chvs1base_len   = 1.0; // 1 cm Aluminum
  double  chvs1base_rmin  = 6;
  double  chvs1base_rmax  = 10;
  double  chvs1_thick = 0.1;     // 1 mm Aluminum
  double  chvs1_len   = 45 - chv_thick;
  double  chvs1_rmin  = 6;
  double  chvs1_rmax  = chvs1_rmin + chvs1_thick;

  
  float  p_chvs1[] = { -360./chvs1_ndiv/2, 360., 4, 4,
                       -chvs1_len/2, chvs1_rmin, chvs1_rmax,
                       +chvs1_len/2-chvs1base_len,chvs1_rmin,chvs1_rmax,
                       +chvs1_len/2-chvs1base_len,chvs1base_rmin,chvs1base_rmax,
                       +chvs1_len/2              ,chvs1base_rmin,chvs1base_rmax 
  };
  
  double c_chvs1_z = Csir_Zmin - chvs1_len/2;

  std::vector<double> paramVec;
  paramVec.push_back(-360./chvs1_ndiv/2*deg);
  paramVec.push_back(360*deg);
  paramVec.push_back(4);
  paramVec.push_back((+chvs1_len/2-chvs1base_len+chvs1_len/2)*cm);
  paramVec.push_back(chvs1_rmin*cm);
  paramVec.push_back(chvs1_rmax*cm);

  GsimPolyhedra2* hedra=0;
  char nam[100];
  std::sprintf(nam,"CVS0");
  hedra = new GsimPolyhedra2(std::string(nam),this,
			     G4ThreeVector(0,0,(-chvs1_len/2+chvs1_len/2-chvs1base_len)/2.*cm),
			     G4ThreeVector(0,0,0));
  hedra->setOuterMaterial("G4_Al");
  hedra->setParameters(paramVec);
  hedra->setOuterColor("gray50");
  hedra->setBriefName("CV");
  addDaughter(hedra);
  m_detList.push_back(hedra);
  
  
  paramVec.clear();
  paramVec.push_back(-360./chvs1_ndiv/2*deg);
  paramVec.push_back(360*deg);
  paramVec.push_back(4);
  paramVec.push_back((+chvs1_len/2-chvs1_len/2+chvs1base_len)*cm);
  paramVec.push_back(chvs1base_rmin*cm);
  paramVec.push_back(chvs1base_rmax*cm);
  std::sprintf(nam,"CVS1");
  hedra
    = new GsimPolyhedra2(std::string(nam),this,
			 G4ThreeVector(0,0,(chvs1_len/2+chvs1_len/2-chvs1base_len)/2.*cm),
			 G4ThreeVector(0,0,0));
  hedra->setOuterMaterial("G4_Al");
  hedra->setParameters(paramVec);
  hedra->setOuterColor("gray50");
  hedra->setBriefName("CV");
  addDaughter(hedra);
  m_detList.push_back(hedra);
  
  // inner part
  int     chv1_ndiv = 4;
  double  chv1_len  = 50 - chv_thick;
  double  chv1_rmin = 6 - chv_thick;
  double  chv1_rmax = chv1_rmin + chv_thick;
  float  p_chv1[] = { -360./chv1_ndiv/2, 360./chv1_ndiv, 1, 2,
                      -chv1_len/2, chv1_rmin, chv1_rmax,
                      +chv1_len/2 ,chv1_rmin, chv1_rmax };

  
  double c_chv1_z = Csic_Zmin - chv1_len/2-c_chvs1_z;

  paramVec.clear();
  paramVec.push_back(-360./chv1_ndiv/2*deg);
  paramVec.push_back(360./chv1_ndiv*deg);
  paramVec.push_back(1);
  paramVec.push_back(chv1_len*cm);
  paramVec.push_back(chv1_rmin*cm);
  paramVec.push_back(chv1_rmax*cm);

  for( int i=0;i<chv1_ndiv;i++ ){
    std::sprintf(nam,"CVI%02d",i);
    hedra
      = new GsimPolyhedra2(std::string(nam),this,
			   G4ThreeVector(0,0,c_chv1_z*cm),
			   G4ThreeVector(0,0,2.*M_PI/4.*i));
    hedra->setParameters(paramVec);
    hedra->setOuterColor("yellow");
    hedra->setBriefName("CV");
    hedra->setSensitiveDetector("CV",32+i);
    addDaughter(hedra);
  }

   // plate
  int     chv_ndiv  = 32;
  double  chv2_len  = chv_thick;
  double  chv2_rmin = chv1_rmin;
  double  chv2_rmax = chv_rmax - 45;
  double  chv2_h    = chv2_rmax - chv2_rmin;
  double  chv2_tlen = chv_rmax*tan(M_PI/32)*2-1;
  double  chv2_blen = chv2_rmin*2 * tan(M_PI/chv_ndiv) * 2;
  float  p_chv2[] = { chv2_len/2, 0, 0,
                      chv2_h/2,chv2_blen/2,chv2_tlen/2,0,
                      chv2_h/2,chv2_blen/2,chv2_tlen/2,0 };
  
  paramVec.clear();
  paramVec.push_back(chv2_len*cm);
  paramVec.push_back(0*deg);
  paramVec.push_back(0*deg);
  paramVec.push_back(chv2_h*cm);
  paramVec.push_back(chv2_blen*cm);
  paramVec.push_back(chv2_tlen*cm);
  paramVec.push_back(0*deg);
  paramVec.push_back(chv2_h*cm);
  paramVec.push_back(chv2_blen*cm);
  paramVec.push_back(chv2_tlen*cm);
  paramVec.push_back(0*deg);
  
  GsimTrap* trap=0;
  for( int i=0;i<chv_ndiv;i++ ){
    std::sprintf(nam,"CVP%02d",i);
    double c_chv2_z = Csic_Zmin - chv1_len - chv2_len/2 - (i%2)*chv_zdiff-c_chvs1_z;
    double c_chv2_x = (chv2_rmin + chv2_h/2) * cos( M_PI*2/32*i );
    double c_chv2_y = (chv2_rmin + chv2_h/2) * sin( M_PI*2/32*i );

    trap
      = new GsimTrap(std::string(nam),this,
		     G4ThreeVector(c_chv2_x*cm,c_chv2_y*cm,c_chv2_z*cm),
		     G4ThreeVector(0,0,2.*M_PI/32.*( (24+i)%32 ))
		     );
    trap->setParameters(paramVec);
    trap->setOuterColor("yellow");
    trap->setBriefName("CV");
    trap->setSensitiveDetector("CV",i);
    addDaughter(trap);
  }

  // bending part
  double  chv3_rmax  = 45; // !!!
  double  chv3_rmin  = chv3_rmax - chv_thick;
  double  chv3_len   = chv_rmax*tan(M_PI/32)*2-1;
  double  chv3_phmin = 0;
  double  chv3_phmax = 90;
  float  p_chv3[] = { chv3_rmin,chv3_rmax,chv3_len/2,
                      chv3_phmin,chv3_phmax };
  paramVec.clear();
  paramVec.push_back(chv3_rmin*cm);
  paramVec.push_back(chv3_rmax*cm);
  paramVec.push_back(chv3_len*cm);
  paramVec.push_back(chv3_phmin*deg);
  paramVec.push_back(chv3_phmax*deg);
  
  GsimTube* tube=0;
  for( int i=0;i<chv_ndiv;i++ ){
    std::sprintf(nam,"CVB%02d",i);
    CLHEP::Hep3Vector  c_chv3( chv2_rmax, 0., Csic_Zmin - 5 - (i%2)*chv_zdiff );
    c_chv3.rotateZ( 2*M_PI/chv_ndiv*i );
    
    tube = new GsimTube(std::string(nam),this,
                        G4ThreeVector(c_chv3.x()*cm,c_chv3.y()*cm,(c_chv3.z()-c_chvs1_z)*cm),
                        G4ThreeVector(0.,M_PI/2.,2.*M_PI/32.*( (24+i*(32/chv_ndiv))%32  )));
    tube->setParameters(paramVec);
    tube->setOuterColor("yellow");
    tube->setBriefName("CV");
    tube->setSensitiveDetector("CV",i);
    addDaughter(tube);
  }

  
  // outer part
  double  chv4_len  = 35;
  double  chv4_x    = chv_thick;
  double  chv4_y    = chv3_len;
  float  p_chv4[] = { chv4_x/2,chv4_y/2,chv4_len/2 };

  paramVec.clear();
  paramVec.push_back(chv4_x*cm);
  paramVec.push_back(chv4_y*cm);
  paramVec.push_back(chv4_len*cm);

  GsimBox* box=0;
  for( int i=0;i<chv_ndiv;i++ ){
    std::sprintf(nam,"CVO%02d",i);
    double c_chv4_x = (chv_rmax - chv_thick/2)*cos(2*M_PI/chv_ndiv*i);
    double c_chv4_y = (chv_rmax - chv_thick/2)*sin(2*M_PI/chv_ndiv*i);
    double c_chv4_z = Csic_Zmin - 5 + chv4_len/2 - (i%2)*chv_zdiff-c_chvs1_z;

    box = new GsimBox(std::string(nam),this,
		      G4ThreeVector(c_chv4_x*cm,c_chv4_y*cm,c_chv4_z*cm),
		      G4ThreeVector(0.,0.,2.*M_PI/32.*i));
    box->setParameters(paramVec);
    box->setOuterColor("yellow");
    box->setBriefName("CV");
    box->setSensitiveDetector("CV",i);
    addDaughter(box);
  }

  // aluminum support structure which connects outer scint. and inner scint.
  // average thickness is used (acutual structure is very complicated).
  double chvs_thick = 1.37; 

  int     chvs2_ndiv = 4;
  double  chvs2_len  = chvs_thick;
  double  chvs2_rmin = 12.3/2.0;
  double  chvs2_rmax = 17.7/2.0;
  float  p_chvs2[] = { 0.0, 360., 4, 2,
                      -chvs2_len/2, chvs2_rmin, chvs2_rmax,
                      +chvs2_len/2 ,chvs2_rmin, chvs2_rmax };

  paramVec.clear();
  paramVec.push_back(0.);
  paramVec.push_back(360*deg);
  paramVec.push_back(4);
  paramVec.push_back(chvs2_len*cm);
  paramVec.push_back(chvs2_rmin*cm);
  paramVec.push_back(chvs2_rmax*cm);

  // chv2 : plate part , chv1: inner part
  double c_chvs2_z = Csic_Zmin - chv1_len + chv2_len/2 + chvs_thick/2.0 + 0.1-c_chvs1_z;
  std::sprintf(nam,"CVS2");
  hedra = new GsimPolyhedra2(std::string(nam),this,
			     G4ThreeVector(0,0,c_chvs2_z*cm),
			     G4ThreeVector(M_PI,0,M_PI/2.+M_PI/4.));
  hedra->setOuterMaterial("G4_Pb");
  hedra->setParameters(paramVec);
  hedra->setOuterColor("gray50");
  hedra->setBriefName("CV");
  addDaughter(hedra);
  m_detList.push_back(hedra);
}


GsimE391CV::~GsimE391CV()
{
  ;
}

void GsimE391CV::setFastSimulationLevel(int level)
{
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugEnter(__PRETTY_FUNCTION__);
#endif
  //reset
  if(m_fastSimulationLevel==6) {
    for(std::list<GsimDetector*>::iterator it=m_detList.begin();
	it!=m_detList.end();it++) {
      (*it)->unsetSensitiveDetector();
    }
  }

  //set
  if(level==6) {
    for(std::list<GsimDetector*>::iterator it=m_detList.begin();
	it!=m_detList.end();it++) {
      (*it)->setSensitiveDetector("CV",0);
    }
  }

  
  {
    m_fastSimulationLevel=level;
    for(GsimDetectorContainer::iterator it=m_daughterDetectorContainer.begin();
	it!=m_daughterDetectorContainer.end();it++) {
      GsimDetector* daughter =  (*it).second;
      daughter->setFastSimulationLevel(level);
    }
  }
#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif 
}
