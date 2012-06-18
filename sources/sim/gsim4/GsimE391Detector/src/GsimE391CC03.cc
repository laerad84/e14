/**
 *  @file
 *  @brief  GsimE391CC03
 *  $Id: GsimE391CC03.cc,v 1.8 2006/12/06 18:58:52 nanjo Exp $ 
 *  $Log: GsimE391CC03.cc,v $
 *  Revision 1.8  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimE391Detector/GsimE391CC03.h"
#include "GsimE391Detector/GsimUserGeom.h"
#include "GsimDetector/GsimPolyhedra2.h"
#include "GsimDetector/GsimBox.h"
#include "GsimPersistency/GsimMessage.h"

using namespace E391;

GsimE391CC03::GsimE391CC03(std::string name,
			   GsimDetector* motherDetector,
			   G4ThreeVector transV,G4ThreeVector rotV,
			   int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{

  m_className = "GsimE391CC03";
  
  // CC03
  double  cc03_len = 55;
  double  cc03_xyo = 25;
  double  cc03_xyi = 12;

  std::vector<double> paramVec;
  paramVec.push_back(-45*deg);
  paramVec.push_back(360*deg);
  paramVec.push_back(4);
  paramVec.push_back(cc03_len*cm);
  paramVec.push_back(cc03_xyi/2.*cm);
  paramVec.push_back(cc03_xyo/2.*cm);
  
  char nam[100];
  sprintf(nam,"CC03support");
  GsimPolyhedra2* hedra = new GsimPolyhedra2(std::string(nam),this,
			     G4ThreeVector(0,0,0),
			     G4ThreeVector(0,0,0));
  hedra->setOuterMaterial("G4_Fe");
  hedra->setParameters(paramVec);
  hedra->setBriefName("CC03");
  addDaughter(hedra);
  m_detList.push_back(hedra);

  // CC03 module
  double  cc3m_wall = 0.3;
  double  cc3m_len  = cc03_len - cc3m_wall*2;
  double  cc3m_x    = 12.0;
  double  cc3m_y    = 5.9;
  float  p_cc3m[] = { cc3m_x/2, cc3m_y/2, cc3m_len/2 };
  double c_cc3m_x = (cc3m_x+cc3m_y)/2+cc3m_wall;
  double c_cc3m_y = (cc3m_x+cc3m_wall)/2;

  double xmod[6] = { c_cc3m_x, 0       ,-c_cc3m_x,-c_cc3m_x, 0       , c_cc3m_x};
  double ymod[6] = { c_cc3m_y, c_cc3m_x, c_cc3m_y,-c_cc3m_y,-c_cc3m_x,-c_cc3m_y};
  double zmod[6] = { 0       , 0       , 0       , 0       , 0       , 0 };
  double zrot[6] = { 2*M_PI*3./4.,0           ,2*M_PI*1./4.,
		     2*M_PI*1./4.,2*M_PI*2./4.,2*M_PI*3./4.};

  
  
  for(int imod=0;imod<6;imod++) {
    sprintf(nam,"CC03module%d",imod);
    GsimDetector* mod = new GsimDetector(std::string(nam),hedra,
					 G4ThreeVector(xmod[imod]*cm,ymod[imod]*cm,zmod[imod]*cm),
					 G4ThreeVector(0,0, zrot[imod]));
    hedra->addDaughter(mod);
    
    // CC03 components
    // CC03 Scintillator
    double  cc3w_thick = 0.1;  // tungsten
    double  cc3s_thick = 0.5;  // scintillator
    double  cc3s_wrap  = 0.05; // wrapping sheet of scintillator
    double  cc3s_len   = 40;
    
    
    std::vector<double> paramVecS;
    paramVecS.push_back((cc3m_x-2.*cc3s_wrap)*cm);
    paramVecS.push_back(cc3s_thick*cm);
    paramVecS.push_back((cc3s_len-2.*cc3s_wrap)*cm);
    
    
    int  cc3w_nw[] = {0,1,3,5,6,8};
    double  cc3w_d = 0;

    cc3w_d += cc3w_nw[0]*cc3w_thick;
    double  dd = cc3w_d + cc3s_wrap*2*0 + cc3s_thick*0;
    double  cy = -cc3m_y/2 + dd + cc3s_wrap + cc3s_thick/2;
    double  cz = -cc3m_len/2 + cc3s_len/2;
    
    sprintf(nam,"CC03scinti");
    GsimBox* boxS = new GsimBox(std::string(nam),mod,
				G4ThreeVector(0,cy*cm,cz*cm),
				G4ThreeVector(0,0,0));
    boxS->setOuterMaterial("G4_GLASS_LEAD");
    boxS->setParameters(paramVecS);
    boxS->setSensitiveDetector("CC03",imod);
    boxS->setBriefName("CC03");
    boxS->setOuterColor("yellow");
    mod->addDaughter(boxS);

    for( int i=1;i<6;i++ ){
      cc3w_d += cc3w_nw[i]*cc3w_thick;
      dd = cc3w_d + cc3s_wrap*2*i + cc3s_thick*i;
      cy = -cc3m_y/2 + dd + cc3s_wrap + cc3s_thick/2;
      cz = -cc3m_len/2 + cc3s_len/2;

      boxS->cloneDetector(G4ThreeVector(0,cy*cm,cz*cm),
			  G4ThreeVector(0,0,0),imod);
    }
    
    // CC03 Tungsten
    cc3w_d = 0;
    for( int i=1;i<6;i++ ){
      cc3w_d += cc3w_nw[i-1]*cc3w_thick;
      
      paramVec.clear();
      paramVec.push_back(cc3m_x*cm);
      paramVec.push_back(cc3w_nw[i]*cc3w_thick*cm);
      paramVec.push_back(cc3s_len*cm);
      
      double  dd = cc3w_d + cc3s_wrap*2*i + cc3s_thick*i;
      double  cy = -cc3m_y/2 + dd + cc3w_nw[i]*cc3w_thick/2;
      double  cz = -cc3m_len/2 + cc3s_len/2;
      
      sprintf(nam,"CC03tungsten%d",i);
      GsimBox* box = new GsimBox(std::string(nam),mod,
				 G4ThreeVector(0,cy*cm,cz*cm),
				 G4ThreeVector(0,0,0));
      box->setOuterMaterial("G4_W");
      box->setParameters(paramVec);
      box->setOuterColor("gray50");
      mod->addDaughter(box);
      m_detList.push_back(box);
    }
  }
}


GsimE391CC03::~GsimE391CC03()
{
  ;
}

void GsimE391CC03::setFastSimulationLevel(int level)
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
      (*it)->setSensitiveDetector("CC03",0);
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
