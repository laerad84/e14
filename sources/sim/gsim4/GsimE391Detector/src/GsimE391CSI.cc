/**
 *  @file
 *  @brief  GsimE391CSI
 *  $Id: GsimE391CSI.cc,v 1.12 2007/02/04 12:56:46 nanjo Exp $ 
 *  $Log: GsimE391CSI.cc,v $
 *  Revision 1.12  2007/02/04 12:56:46  nanjo
 *  GsimBoxWithAHole is used.
 *
 *  Revision 1.11  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimE391Detector/GsimE391CSI.h"
#include "GsimE391Detector/GsimUserGeom.h"
#include "GsimKernel/GsimTrackInformation.h"
#include "GsimKernel/GsimSensitiveDetector.h"
#include "GsimPersistency/GsimPersistencyManager.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimDetector/GsimTrap.h"
#include "GsimDetector/GsimTube.h"
#include "GsimDetector/GsimBox.h"
#include "GsimData/GsimEventData.h"

#include "G4Track.hh"
#include "G4VProcess.hh"

using namespace E391;

GsimE391CSI::GsimE391CSI(std::string name,
			 GsimDetector* motherDetector,
			 G4ThreeVector transV,G4ThreeVector rotV,
			 int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{

  m_className = "GsimE391CSI";
  m_totEThreshold=0;

  int  ivol=0;

  // CsI crystal
  // deformed CsI crystals
  
  double csdt_top[8],csdt_bot[8],csdt_hi[8],csdb_y[8];
  // #1
  csdt_top[1] = 6.52;
  csdt_bot[1] = 7;
  csdt_hi[1]  = 7;
  // #2
  csdt_top[2] = 5.47;
  csdt_bot[2] = 6.52;
  csdt_hi[2]  = 7;
  // #3
  csdt_top[3] = 3.87;
  csdt_bot[3] = 5.47;
  csdt_hi[3]  = 7;
  // #4
  csdt_top[4] = 4.48;
  csdt_bot[4] = 7;
  csdt_hi[4]  = 7-5.92;
  csdb_y[4]   = 5.92;
  // #5
  csdt_top[5] = 2.44;
  csdt_bot[5] = 5.91;
  csdt_hi[5]  = 7;
  // #6
  csdt_top[6] = 4.21;
  csdt_bot[6] = 7;
  csdt_hi[6]  = 7-5.21;
  csdb_y[6]   = 5.21;
  // #7
  csdt_top[7] = 0.78;
  csdt_bot[7] = 7;
  csdt_hi[7]  = 7;


  GsimTube* tube=0;
  
  // CsI region
  double  csir_len  = Csir_Len; // CsI region
  double  csir_rmin = 0;
  double  csir_rmax = 97.3;
  float  p_csir[] = { csir_rmin,csir_rmax, Csir_Len/2 };

  char nam[100];
  // CsI Cylinder
  double  cscl_thick = 2.0; // 20 mm thick SUS
  double  cscl_len  = Csir_Len - 5;
  double  cscl_rmax = csir_rmax;
  double  cscl_rmin = cscl_rmax - cscl_thick;
  float  p_cscl[] = { cscl_rmin,cscl_rmax, cscl_len/2 };
  std::vector<double> paramVec;
  paramVec.push_back(cscl_rmin*cm);
  paramVec.push_back(cscl_rmax*cm);
  paramVec.push_back(cscl_len*cm);
  paramVec.push_back(0.*deg);
  paramVec.push_back(360.*deg);

  sprintf(nam,"CSCL");
  tube = new GsimTube(std::string(nam),this,
		      G4ThreeVector(0*cm,0*cm,2.5*cm),
		      G4ThreeVector(0,0,0));
  tube->setOuterMaterial("G4_Fe");
  tube->setParameters(paramVec);
  tube->setOuterColor("gray70");
  addDaughter(tube);
  m_detMoveList.push_back(tube);
  
  // CsI Cylinder Endcap 
  double  csec_thick = 2.0; // 20 mm thick SUS
  double  csec_rmax = csir_rmax - cscl_thick;
  double  csec_rmin = 20;
  float  p_csec[] = { csec_rmin,csec_rmax, csec_thick/2 };
  paramVec.clear();
  paramVec.push_back(csec_rmin*cm);
  paramVec.push_back(csec_rmax*cm);
  paramVec.push_back(csec_thick*cm);
  paramVec.push_back(0.*deg);
  paramVec.push_back(360.*deg);
  
  sprintf(nam,"CSEC");
  GsimTube* ecap = new GsimTube(std::string(nam),this,
				G4ThreeVector(0*cm,0*cm,(Csir_Len/2-cscl_thick/2)*cm),
				G4ThreeVector(0,0,0));
  ecap->setOuterMaterial("G4_Fe");
  ecap->setParameters(paramVec);
  ecap->setOuterColor("gray70");
  addDaughter(ecap);
  m_detMoveList.push_back(ecap);
  

  // CsI Dummy Inner Compartment 1,2
  
  double  csh1_len = KtevCsic_Len;
  double  csh1_xyo = (Csic_XY + Csic_Gap)*13;
  double  csh1_xyi = (KtevCsic_XY + KtevCsic_Gap)*5;
  float  p_csh1[] = { -360./4/2, 360, 4, 2,
                      -csh1_len/2, csh1_xyi/2, csh1_xyo/2,
                      +csh1_len/2, csh1_xyi/2, csh1_xyo/2 };
  paramVec.clear();
  paramVec.push_back(( -360./4./2.)*deg);
  paramVec.push_back(360*deg);
  paramVec.push_back(4);
  paramVec.push_back(csh1_len*cm);
  paramVec.push_back(csh1_xyi/2.*cm);
  paramVec.push_back(csh1_xyo/2.*cm);
  
  double c_csh1_z = -Csir_Len/2 + 5 + csh1_len/2;

  sprintf(nam,"CSH1");
  GsimDetector* csh1
    = new GsimDetector(std::string(nam),this,
		       G4ThreeVector(0,0,c_csh1_z*cm),
		       G4ThreeVector(0,0,0));
  addDaughter(csh1);
  
  double  csh2_len = KtevCsic_Len;
  double  csh2_xyo = (Csic_XY + Csic_Gap)*19;
  double  csh2_xyi = (Csic_XY + Csic_Gap)*13;
  float  p_csh2[] = { -360./4/2, 360, 4, 2,
                      -csh2_len/2, csh2_xyi/2, csh2_xyo/2,
                      +csh2_len/2, csh2_xyi/2, csh2_xyo/2 };
  paramVec.clear();
  paramVec.push_back(( -360./4./2.)*deg);
  paramVec.push_back(360*deg);
  paramVec.push_back(4);
  paramVec.push_back(csh2_len*cm);
  paramVec.push_back(csh2_xyi/2.*cm);
  paramVec.push_back(csh2_xyo/2.*cm);
  
  double c_csh2_z = -Csir_Len/2 + 5 + csh2_len/2;

  sprintf(nam,"CSH2");
  GsimDetector* csh2
    = new GsimDetector(std::string(nam),this,
		       G4ThreeVector(0,0,c_csh2_z*cm),
		       G4ThreeVector(0,0,0));
  addDaughter(csh2);


  std::vector<double> paramKEK;
  paramKEK.push_back(Csic_XY*cm);
  paramKEK.push_back(Csic_XY*cm);
  paramKEK.push_back(Csic_Len*cm);
  
  std::vector<double> paramKTEV;
  paramKTEV.push_back(KtevCsic_XY*cm);
  paramKTEV.push_back(KtevCsic_XY*cm);
  paramKTEV.push_back(KtevCsic_Len*cm);

  GsimBox* boxKTEV=0;
  GsimBox* boxKEK1=0;
  GsimBox* boxKEK2=0;
  GsimBox* boxKEK3=0;
  GsimBox* box=0;
  GsimTrap* trap;

  
  // CsI Crystal position
  char  csiblock[][28] = {
    // 012345678901234567890123456      
    { ".........a3210123a........." },  //  0
    { "......b5400000000045b......" },  //  1
    { ".....c600000000000006c....." },  //  2
    { "....7000000000000000007...." },  //  3
    { "...700000000000000000007..." },  //  4
    { "..c000000000000000000000c.." },  //  5
    { ".b60000000000000000000006b." },  //  6
    { ".5000000000000000000000005." },  //  7
    { ".4000000000000000000000004." },  //  8
    { "a0000000000000000000000000a" },  //  9
    { "300000000000000000000000003" },  // 10
    { "20000000000kkkkk00000000002" },  // 11
    { "10000000000k...k00000000001" },  // 12
    { "00000000000k...k00000000000" } };// 13

  int  id = 0;
  for( int y=0;y<27;y++ ){
    for( int x=0;x<27;x++ ){
      int  yy = (y<13) ? y : 26-y;
      if ( 11<=x && x<=15 && 11<=y && y<=15 ){
        // KTeV CsI
        if ( x == 11 ){
          int  *kx,*ky;
          int  nk = 0;
          if ( y == 11 ){
            static int  kxcsi[] = { -3,-2,-1, 0, 1, 2, 3 }; 
            static int  kycsi[] = { -3,-3,-3,-3,-3,-3,-3 };
            kx = kxcsi;
            ky = kycsi;
            nk = 7;
          }
          else if ( y == 12 ){
            static int  kxcsi[] = { -3,-3, 3, 3 }; 
            static int  kycsi[] = { -2,-1,-2,-1 };
            kx = kxcsi;
            ky = kycsi;
            nk = 4;
          }
          else if ( y == 13 ){
            static int  kxcsi[] = { -3, 3 }; 
            static int  kycsi[] = {  0, 0 };
            kx = kxcsi;
            ky = kycsi;
            nk = 2;
          }
          else if ( y == 14 ){
            static int  kxcsi[] = { -3,-3, 3, 3 }; 
            static int  kycsi[] = {  1, 2, 1, 2 };
            kx = kxcsi;
            ky = kycsi;
            nk = 4;
          }
          else if ( y == 15 ){
            static int  kxcsi[] = { -3,-2,-1, 0, 1, 2, 3 }; 
            static int  kycsi[] = {  3, 3, 3, 3, 3, 3, 3 };
            kx = kxcsi;
            ky = kycsi;
            nk = 7;
          }
          for( int ki=0;ki<nk;ki++ ){
            float  p_csic[] = { KtevCsic_XY/2, KtevCsic_XY/2, KtevCsic_Len/2 };
            double c_csic_x = kx[ki]*(KtevCsic_XY + KtevCsic_Gap);
            double c_csic_y = ky[ki]*(KtevCsic_XY + KtevCsic_Gap);
            double c_csic_z = -csh1_len/2 + KtevCsic_Len/2;
            id++;
	    
	    if(boxKTEV==0) {
	      std::sprintf(nam,"KTEVCSI");
	      boxKTEV = new GsimBox(std::string(nam),csh1,
				    G4ThreeVector(c_csic_x*cm,c_csic_y*cm,c_csic_z*cm),
				    G4ThreeVector(0,0,0)
				    );
	      boxKTEV->setOuterMaterial("G4_CESIUM_IODIDE");
	      boxKTEV->setParameters(paramKTEV);
	      boxKTEV->setOuterColor("lightskyblue");
	      boxKTEV->setSensitiveDetector("CSI",id-1);
	      csh1->addDaughter(boxKTEV);
	    } else {
	      boxKTEV->cloneDetector(G4ThreeVector(c_csic_x*cm,c_csic_y*cm,c_csic_z*cm),
				     G4ThreeVector(0,0,0),id-1);
	    }
	    
          }
        }
      }
      else{
        double c_csic_x = (x-13)*(Csic_XY + Csic_Gap);
        double c_csic_y = (y-13)*(Csic_XY + Csic_Gap);
        double c_csic_z = -Csir_Len/2 + 5 + Csic_Len/2;
        if ( csiblock[yy][x] == '0' ){
          float  p_csic[] = { Csic_XY/2, Csic_XY/2, Csic_Len/2 };
          id++;
          { //////
            if ( 13-6<=x && x<=13+6 && 13-6<=y && y<=13+6 ){
              c_csic_z = -csh1_len/2 + Csic_Len/2;
	      
	      if(boxKEK1==0) {
		std::sprintf(nam,"KEKCSI1");
		boxKEK1 = new GsimBox(std::string(nam),csh1,
				      G4ThreeVector(c_csic_x*cm,c_csic_y*cm,c_csic_z*cm),
				      G4ThreeVector(0,0,0)
				      );
		boxKEK1->setOuterMaterial("G4_CESIUM_IODIDE");
		boxKEK1->setParameters(paramKEK);
		boxKEK1->setOuterColor("lightskyblue");
		boxKEK1->setSensitiveDetector("CSI",id-1);
		csh1->addDaughter(boxKEK1);
	      } else {
		boxKEK1->cloneDetector(G4ThreeVector(c_csic_x*cm,c_csic_y*cm,c_csic_z*cm),
				       G4ThreeVector(0,0,0),id-1);
	      }
            }
            else if ( 13-9<=x && x<=13+9 && 13-9<=y && y<=13+9 ){
              c_csic_z = -csh2_len/2 + Csic_Len/2;

	      if(boxKEK2==0) {
		std::sprintf(nam,"KEKCSI2");
		boxKEK2 = new GsimBox(std::string(nam),csh2,
				      G4ThreeVector(c_csic_x*cm,c_csic_y*cm,c_csic_z*cm),
				      G4ThreeVector(0,0,0)
				      );
		boxKEK2->setOuterMaterial("G4_CESIUM_IODIDE");
		boxKEK2->setParameters(paramKEK);
		boxKEK2->setOuterColor("lightskyblue");
		boxKEK2->setSensitiveDetector("CSI",id-1);
		csh2->addDaughter(boxKEK2);
	      } else {
		boxKEK2->cloneDetector(G4ThreeVector(c_csic_x*cm,c_csic_y*cm,c_csic_z*cm),
				       G4ThreeVector(0,0,0),id-1);
	      }
            }
            else{
	      
	      if(boxKEK3==0) {
		std::sprintf(nam,"KEKCSI3");
		boxKEK3 = new GsimBox(std::string(nam),this,
				      G4ThreeVector(c_csic_x*cm,c_csic_y*cm,c_csic_z*cm),
				      G4ThreeVector(0,0,0)
				      );
		boxKEK3->setOuterMaterial("G4_CESIUM_IODIDE");
		boxKEK3->setParameters(paramKEK);
		boxKEK3->setOuterColor("lightskyblue");
		boxKEK3->setSensitiveDetector("CSI",id-1);
		addDaughter(boxKEK3);
	      } else {
		boxKEK3->cloneDetector(G4ThreeVector(c_csic_x*cm,c_csic_y*cm,c_csic_z*cm),
				       G4ThreeVector(0,0,0),id-1);
	      }
            }
          }
        }
        else if ( '0' < csiblock[yy][x] && csiblock[yy][x] <= '9'  ){
          int  cd = csiblock[yy][x] - '0';
          id++;
          { //////
            int  sec = (int)( fmod( CLHEP::Hep3Vector(x-13,y-13,0).phi()+2*M_PI,2*M_PI)
                              / (M_PI/4) );
            // 
            if ( cd == 4 || cd == 6 ){
              double  cbx = c_csic_x;
              double  cby = c_csic_y;
              double  cbz = c_csic_z;
              double  offset = Csic_XY/2-csdb_y[cd]/2;
              int  rotb;
              if ( sec % 2 == 0 ){
                rotb = (24+sec*4) % 32;
                if ( sec == 0 ) cbx -= offset;
                if ( sec == 2 ) cby -= offset;
                if ( sec == 4 ) cbx += offset;
                if ( sec == 6 ) cby += offset;
              }
              else{
                rotb = (sec-1)*4;
                if ( sec == 1 ) cby -= offset;
                if ( sec == 3 ) cbx += offset;
                if ( sec == 5 ) cby += offset;
                if ( sec == 7 ) cbx -= offset;
              }
              float  p_csdb[] = { Csic_XY/2,csdb_y[cd]/2,Csic_Len/2 };
	      paramVec.clear();
	      paramVec.push_back(Csic_XY*cm);
	      paramVec.push_back(csdb_y[cd]*cm);
	      paramVec.push_back(Csic_Len*cm);
	      std::sprintf(nam,"CSIDB%03d",id);
	      box = new GsimBox(std::string(nam),this,
				G4ThreeVector(cbx*cm,cby*cm,cbz*cm),
				G4ThreeVector(0,0,(rotb/32.*2.*M_PI))
				);
	      box->setOuterMaterial("G4_CESIUM_IODIDE");
	      box->setParameters(paramVec);
	      box->setOuterColor("lightskyblue");
	      box->setSensitiveDetector("CSI",id-1);
	      addDaughter(box);
            }
            //
            double  ctx = c_csic_x;
            double  cty = c_csic_y;
            double  ctz = c_csic_z;
            double  offset   = Csic_XY/2-(csdt_top[cd]+csdt_bot[cd])/4;
            double  offset_h = Csic_XY/2-csdt_hi[cd]/2;
            int    rott;
	    int    irot;
            double alpha = ( atan( (csdt_top[cd]-csdt_bot[cd])/2/csdt_hi[cd] ) );
            if ( !(cd == 4 || cd == 6) ){
	      irot = ( sec%2 ) ? (24+(sec-1)*4)%32 : sec*4;
              rott = ( sec%2 ) ? grot_z_32+(24+(sec-1)*4)%32 : grot_z_32+sec*4;
              alpha = ( sec%2 ) ? -alpha : alpha;
              if ( sec == 0 ) ctx -= offset;
              if ( sec == 1 ) cty -= offset;
              if ( sec == 2 ) cty -= offset;
              if ( sec == 3 ) ctx += offset;
              if ( sec == 4 ) ctx += offset;
              if ( sec == 5 ) cty += offset;
              if ( sec == 6 ) cty += offset;
              if ( sec == 7 ) ctx -= offset;
            }
            else {
	      irot = ( sec%2 ) ?  (sec-1)*4 : (24+sec*4)%32;
              rott = ( sec%2 ) ?  grot_z_32+(sec-1)*4 : grot_z_32+(24+sec*4)%32;
              alpha = ( sec%2 ) ? alpha : -alpha;
              if ( sec == 0 ){ ctx += offset_h; cty -= offset;   }
              if ( sec == 1 ){ ctx -= offset;   cty += offset_h; }
              if ( sec == 2 ){ ctx += offset;   cty += offset_h; }
              if ( sec == 3 ){ ctx -= offset_h; cty -= offset;   }
              if ( sec == 4 ){ ctx -= offset_h; cty += offset;   }
              if ( sec == 5 ){ ctx += offset;   cty -= offset_h; }
              if ( sec == 6 ){ ctx -= offset;   cty -= offset_h; }
              if ( sec == 7 ){ ctx += offset_h; cty += offset;   }
            }
            float p_csdt[]={ Csic_Len/2, 0, 0,
                             csdt_hi[cd]/2,csdt_bot[cd]/2,csdt_top[cd]/2,alpha,
                             csdt_hi[cd]/2,csdt_bot[cd]/2,csdt_top[cd]/2,alpha };
	    paramVec.clear();
	    paramVec.push_back(Csic_Len*cm);
	    paramVec.push_back(0*deg);
	    paramVec.push_back(0*deg);
	    paramVec.push_back(csdt_hi[cd]*cm);
	    paramVec.push_back(csdt_bot[cd]*cm);
	    paramVec.push_back(csdt_top[cd]*cm);
	    paramVec.push_back(alpha*rad);
	    paramVec.push_back(csdt_hi[cd]*cm);
	    paramVec.push_back(csdt_bot[cd]*cm);
	    paramVec.push_back(csdt_top[cd]*cm);
	    paramVec.push_back(alpha*rad);
	    std::sprintf(nam,"CSDT%03d",id);
	    trap = new GsimTrap(std::string(nam),this,
				G4ThreeVector(ctx*cm,cty*cm,ctz*cm),
				G4ThreeVector(0,0,(irot/32.*2.*M_PI))
				);
	    trap->setOuterMaterial("G4_CESIUM_IODIDE");
	    trap->setParameters(paramVec);
	    trap->setOuterColor("lightskyblue");
	    trap->setSensitiveDetector("CSI",id-1);
	    addDaughter(trap);
          }
        }
      }
    }
  }
  setThisAndDaughterBriefName("CSI");
  ecap->setThisAndDaughterBriefName("ECAP");
  update();
}


GsimE391CSI::~GsimE391CSI()
{
  ;
}


bool GsimE391CSI::beginOfEventAction(const G4Event* )
{
  return false;
}


bool GsimE391CSI::endOfEventAction(const G4Event* )
{
  std::list<GsimSensitiveDetector*> sdList
    =getThisAndDaughterSensitiveDetectorList();
  for(std::map<G4LogicalVolume*,GsimSensitiveDetector*>::iterator
	it=m_sensitiveDetectorMap.begin();
      it!=m_sensitiveDetectorMap.end();it++) {
    GsimSensitiveDetector* sd=(*it).second;
    sdList.push_back(sd);
  }
  sdList.sort();
  sdList.unique();

  double totE=0;
  for(std::list<GsimSensitiveDetector*>::iterator
	it=sdList.begin();it!=sdList.end();it++) {
    totE+=(*it)->getTotalEnergy();
  }
  GsimPersistencyManager* pm=GsimPersistencyManager::getPersistencyManager();

  if(totE>m_totEThreshold) {
    pm->addTriggerBit(TRIG_NCLUS);
  }
  
  return true;
}



bool GsimE391CSI::postTrackingAction(const G4Track* aTrack) {
  return false;
}





void GsimE391CSI::setFastSimulationLevel(int level)
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
    
    for(std::list<GsimDetector*>::iterator it=m_detMoveList.begin();
	it!=m_detMoveList.end();it++) {
      G4ThreeVector pos=(*it)->getTranslationVector();
      double z=pos.getZ();
      pos.setZ(z+29*m);
      (*it)->setTranslationVector(pos);
      (*it)->setOuterVisibility(true);
    }
  }

  //set
  if(level==6) {
    for(std::list<GsimDetector*>::iterator it=m_detList.begin();
	it!=m_detList.end();it++) {
      (*it)->setSensitiveDetector("CSI",0);
    }
    for(std::list<GsimDetector*>::iterator it=m_detMoveList.begin();
	it!=m_detMoveList.end();it++) {
      G4ThreeVector pos=(*it)->getTranslationVector();
      double z=pos.getZ();
      pos.setZ(z-29*m);
      (*it)->setTranslationVector(pos);
      (*it)->setOuterVisibility(false);
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
