/**
 *  @file
 *  @brief  GsimE391BA
 *  $Id: GsimE391BA.cc,v 1.8 2006/12/06 18:58:52 nanjo Exp $ 
 *  $Log: GsimE391BA.cc,v $
 *  Revision 1.8  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimE391Detector/GsimE391BA.h"
#include "GsimE391Detector/GsimUserGeom.h"
#include "GsimDetector/GsimBox.h"
#include "GsimPersistency/GsimMessage.h"

#include "G4Box.hh"

using namespace E391;

GsimE391BA::GsimE391BA(std::string name,
		       GsimDetector* motherDetector,
		       G4ThreeVector transV,G4ThreeVector rotV,
		       int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{

  m_className = "GsimE391BA";






  int  ivol=0;

  // BA
  double  ba_len  = 51.0;
  double  ba_width = 25.0;
  double  ba_hight = ba_width;
  float  p_ba[] = { ba_width/2.0, ba_hight/2.0, ba_len/2.0 };

  std::vector<double> paramBA;
  paramBA.push_back(ba_width*cm);
  paramBA.push_back(ba_hight*cm);
  paramBA.push_back(ba_len*cm);

  GsimBox* BA = new GsimBox("BA",this,
                            G4ThreeVector(0,0,0),
                            G4ThreeVector(0,0,0));
  BA->setOuterMaterial("G4_AIR");
  BA->setParameters(paramBA);
  BA->setOuterVisibility(false);
  BA->setBriefName("BA");
  addDaughter(BA);
  m_detList.push_back(BA);
  
  //double  c_ba_z = 1040 + ba_len/2;
  double  c_ba_z;
  int Dataset=2;
  if ( Dataset == 1) {
    c_ba_z = Detpos_ba_z + ba_len/2; // from Misha's measurement
  }else{
    c_ba_z = Detpos_ba_z + ba_len/2 + 10.0 ; // runII
  }
  
  double s_thick = 0.5;
  double s_width = 24.5;

  // lead
  double lead_thick = 0.2;
  double lead_width = s_width;

  // aluminium
  double al_thick = 0.15;
  double al_width = s_width;

  // quartz
  double q_thick = 3.0;
  double q_width = s_width;
  double q_height = 3.5;
  
  std::vector<double> paramBAS;
  paramBAS.push_back(s_width*cm);
  paramBAS.push_back(s_width*cm);
  paramBAS.push_back(s_thick*cm);

  std::vector<double> paramBAL;
  paramBAL.push_back(lead_width*cm);
  paramBAL.push_back(lead_width*cm);
  paramBAL.push_back(lead_thick*cm);

  std::vector<double> paramBAQ;
  paramBAQ.push_back(q_width*cm);
  paramBAQ.push_back(q_height*cm);
  paramBAQ.push_back(q_thick*cm);

  std::vector<double> paramBAAL;
  paramBAAL.push_back(al_width*cm);
  paramBAAL.push_back(al_width*cm);
  paramBAAL.push_back(al_thick*cm);

  {
    double z = - ba_len/2.0 + 0.1;
    double gap_scinti = 0.02;
    double gap_quartz = 0.01;
    double gap_module = 0.1;

    int icp_al = 0;
    int icp_lead = 0;
    int icp_s = 0;
    int icp_q = 0;
    
    char nam[100];
    GsimBox* boxBAAL=0;
    GsimBox* boxBAL=0;
    GsimBox* boxBAS=0;
    GsimBox* boxBAQ=0;
    for ( int i=0 ; i<6 ; i++) {
      z += al_thick/2.0;
      icp_al++;
      if(i==0) {
	sprintf(nam,"BAAL");
	boxBAAL = new GsimBox(std::string(nam),BA,
			      G4ThreeVector(0,0,z*cm),
			      G4ThreeVector(0,0,0));
	boxBAAL->setOuterMaterial("G4_Al");
	boxBAAL->setParameters(paramBAAL);
	boxBAAL->setOuterColor("gray50");
	boxBAAL->setBriefName("BA");
	BA->addDaughter(boxBAAL);
	m_detList.push_back(boxBAAL);
      } else {
	boxBAAL->cloneDetector(G4ThreeVector(0,0,z*cm),
			       G4ThreeVector(0,0,0));
      }
      
      z += al_thick/2.0;

      // lead + scinti
      for ( int j=0 ; j<6 ; j++ ) {
        z += lead_thick/2.0;
	icp_lead++;
	if(i==0 && j==0) {
	  sprintf(nam,"BAL");
	  boxBAL = new GsimBox(std::string(nam),BA,
			       G4ThreeVector(0,0,z*cm),
			       G4ThreeVector(0,0,0));
	  boxBAL->setOuterMaterial("G4_Pb");
	  boxBAL->setParameters(paramBAL);
	  boxBAL->setOuterColor("gray70");
	  boxBAL->setBriefName("BA");
	  BA->addDaughter(boxBAL);
	  m_detList.push_back(boxBAL);
	} else {
	  boxBAL->cloneDetector(G4ThreeVector(0,0,z*cm),
				G4ThreeVector(0,0,0));
	}

        z += s_thick/2.0 + lead_thick/2.0 + gap_scinti;
	if(i==0 && j==0) {
	  sprintf(nam,"BAS");
	  boxBAS = new GsimBox(std::string(nam),BA,
			       G4ThreeVector(0,0,z*cm),
			       G4ThreeVector(0,0,0));
	  boxBAS->setParameters(paramBAS);
	  boxBAS->setOuterColor("yellow");
	  boxBAS->setSensitiveDetector("BAS",icp_s);
	  boxBAS->setBriefName("BA");
	  BA->addDaughter(boxBAS);
	} else {
	  boxBAS->cloneDetector(G4ThreeVector(0,0,z*cm),
				G4ThreeVector(0,0,0),icp_s);
	}
	icp_s++;
        z += s_thick/2.0 + gap_scinti;
      }

      z += al_thick/2.0;
      
      icp_al++;
      boxBAAL->cloneDetector(G4ThreeVector(0,0,z*cm),
			     G4ThreeVector(0,0,0));
      
      z += gap_module;

      // quartz part
      z += al_thick/2.0;

      icp_al++;
      boxBAAL->cloneDetector(G4ThreeVector(0,0,z*cm),
			     G4ThreeVector(0,0,0));
      
      z += al_thick/2.0 + gap_quartz + q_thick/2.0;


      // second term is from difference base height of scinti and quartz
      double yq = -s_width/2.0 - gap_scinti;

      for ( int k=0 ; k<7 ; k++ ){
        yq += q_height/2.0 + gap_quartz;

	
	if(i==0 && k==0) {
	  sprintf(nam,"BAQ");
	  boxBAQ = new GsimBox(std::string(nam),BA,
			       G4ThreeVector(0,yq*cm,z*cm),
			       G4ThreeVector(0,0,0));
	  boxBAQ->setOuterMaterial("G4_SILICON_DIOXIDE");
	  boxBAQ->setParameters(paramBAQ);
	  boxBAQ->setOuterColor("blue");
	  boxBAQ->setSensitiveDetector("BAQ",icp_q);
	  boxBAQ->setBriefName("BA");
	  BA->addDaughter(boxBAQ);
	} else {
	  boxBAQ->cloneDetector(G4ThreeVector(0,yq*cm,z*cm),
				G4ThreeVector(0,0,0),icp_q);
	}
	icp_q++;
	yq += q_height/2.0 + gap_quartz;
      }

      z += q_thick/2.0 + gap_quartz + al_thick/2.0;


      icp_al++;
      boxBAAL->cloneDetector(G4ThreeVector(0,0,z*cm),
			     G4ThreeVector(0,0,0));
      
      z += al_thick/2.0 + gap_module;
    }
  }
}


GsimE391BA::~GsimE391BA()
{
  ;
}

void GsimE391BA::setFastSimulationLevel(int level)
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
      (*it)->setSensitiveDetector("BHPV",0);
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
