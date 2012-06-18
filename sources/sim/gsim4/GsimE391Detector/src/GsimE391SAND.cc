/**
 *  @file
 *  @brief  GsimE391SAND
 *  $Id: GsimE391SAND.cc,v 1.6 2006/12/06 18:58:52 nanjo Exp $ 
 *  $Log: GsimE391SAND.cc,v $
 *  Revision 1.6  2006/12/06 18:58:52  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimE391Detector/GsimE391SAND.h"
#include "GsimE391Detector/GsimUserGeom.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimDetector/GsimTrap.h"
#include "GsimDetector/GsimBox.h"

using namespace E391;

GsimE391SAND::GsimE391SAND(std::string name,
			   GsimDetector* motherDetector,
			   G4ThreeVector transV,G4ThreeVector rotV,
			   int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{

  m_className = "GsimE391SAND";

  int  ivol=0;
  
  // Sandwich conter (CsI outer-edge)
  const char  *sandname[] = { "SND1","SND2","SND3" };

  double  sand_top[3],sand_bot[3],sand_hi[3];
  // #a
  sand_top[0] = 1.*nm;
  sand_bot[0] = 3.86;
  sand_hi[0]  = 11.44;
  // #b
  sand_top[1] = 1.*nm;
  sand_bot[1] = 2.42;
  sand_hi[1]  = 4.16;
  // #c
  sand_top[2] = 1.*nm;
  sand_bot[2] = 5.19;
  sand_hi[2]  = 7.04;


  // scintillator
  const char  *sndsname[] = { "SNS1","SNS2","SNS3" };

  double  snds_top[3],snds_bot[3],snds_hi[3];
  // #a
  snds_top[0] = 1.*nm;
  snds_bot[0] = 3.3;
  snds_hi[0]  = 10.0;
  // #b
  snds_top[1] = 1.*nm;
  snds_bot[1] = 1.9;
  snds_hi[1]  = 3.2;
  // #c
  snds_top[2] = 1.*nm;
  snds_bot[2] = 4.6;
  snds_hi[2]  = 6.2;

  
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
    { "00000000000k...k00000000000" },  // 13
  };
  
  // ID for sandwich counter, counting from the left_bottom.
  int  sand_id[] = {
    18,19, 17,20, 16,21, 15,22, 14,23, 13,24, 
    12,1,  11,2,  10,3,   9,4,   8,5,   7,6
  };
  
  //
  char nam[100];
  int  id = 0;
  for( int y=0;y<27;y++ ){
    for( int x=0;x<27;x++ ){
      int  yy = (y<13) ? y : 26-y;
      if ( 'a' <= csiblock[yy][x] && csiblock[yy][x] < 'k'  ){
        int  cd = csiblock[yy][x] - 'a';
        id++;
        {
          int  sec = (int)( fmod( CLHEP::Hep3Vector(x-13,y-13,0).phi()+2*M_PI,2*M_PI)
                            / (M_PI/4) );
          // 
          double  c_csic_x = (x-13)*(Csic_XY + Csic_Gap);
          double  c_csic_y = (y-13)*(Csic_XY + Csic_Gap);
          double  c_csic_z = -Csir_Len/2 + 5 + Csic_Len/2;
          double  ctx = c_csic_x;
          double  cty = c_csic_y;
          double  ctz = c_csic_z;
          double  offset   = (sand_top[cd]+sand_bot[cd])/4 -Csic_XY/2;
          double  offset_h = sand_hi[cd]/2 - Csic_XY/2;
          int    rott;
          double  alpha = ( atan( (sand_top[cd]-sand_bot[cd])/2/sand_hi[cd] ) );
          rott = ( sec%2 ) ? grot_x180_z_32+(8+(sec-1)*4)%32 : grot_z_32+sec*4;
          if ( sec == 0 ){ ctx += offset;   cty += offset_h; }
          if ( sec == 1 ){ ctx += offset_h; cty += offset;   }
          if ( sec == 2 ){ ctx -= offset_h; cty += offset;   }
          if ( sec == 3 ){ ctx -= offset;   cty += offset_h; }
          if ( sec == 4 ){ ctx -= offset;   cty -= offset_h; }
          if ( sec == 5 ){ ctx -= offset_h; cty -= offset;   }
          if ( sec == 6 ){ ctx += offset_h; cty -= offset;   }
          if ( sec == 7 ){ ctx += offset;   cty -= offset_h; }
          double p_sand[]={ Csic_Len/2, 0, 0,
                           sand_hi[cd]/2,sand_bot[cd]/2,sand_top[cd]/2,alpha,
                           sand_hi[cd]/2,sand_bot[cd]/2,sand_top[cd]/2,alpha };


	  std::vector<double> paramVec;
	  paramVec.push_back(Csic_Len*cm);
	  paramVec.push_back(0.);
	  paramVec.push_back(0.);
	  paramVec.push_back(sand_hi[cd]*cm);
	  paramVec.push_back(sand_bot[cd]*cm);
	  paramVec.push_back(sand_top[cd]*cm);
	  paramVec.push_back(alpha);
	  paramVec.push_back(sand_hi[cd]*cm);
	  paramVec.push_back(sand_bot[cd]*cm);
	  paramVec.push_back(sand_top[cd]*cm);
	  paramVec.push_back(alpha);

	  G4ThreeVector rotSANDV;
	  if(sec%2) {
	    rotSANDV=G4ThreeVector(M_PI*rad,0., (2.*M_PI/32. * ((8+(sec-1)*4)%32))*rad);
	  } else {
	    rotSANDV=G4ThreeVector(0,0,(2.*M_PI/32. *sec*4)*rad);
	  }
	  
	  std::sprintf(nam,"SAND%03d",sand_id[id-1]-1);
	  GsimTrap* trap = new GsimTrap(std::string(nam),this,
					G4ThreeVector(ctx*cm,cty*cm,0),
					rotSANDV
					);
	  trap->setParameters(paramVec);
	  trap->setOuterMaterial("G4_Pb");
	  trap->setOuterColor("gray50");
	  trap->setBriefName("SAND");
	  addDaughter(trap);
	  m_detList.push_back(trap);

	  {
	    double  alpha =( atan( (snds_top[cd]-snds_bot[cd])/2/snds_hi[cd] ) );
	    double  offset_h = snds_hi[cd]/2 - sand_hi[cd]/2 + 0.2;
	    double  offset_x = snds_bot[cd]/4 - sand_bot[cd]/4 + 0.2;
	    double p_snds[]={ Csic_Len/2, 0, 0,
			     snds_hi[cd]/2,snds_bot[cd]/2,snds_top[cd]/2,alpha,
			     snds_hi[cd]/2,snds_bot[cd]/2,snds_top[cd]/2,alpha };

	    paramVec.clear();
	    paramVec.push_back(Csic_Len*cm);
	    paramVec.push_back(0.);
	    paramVec.push_back(0.);
	    paramVec.push_back(snds_hi[cd]*cm);
	    paramVec.push_back(snds_bot[cd]*cm);
	    paramVec.push_back(snds_top[cd]*cm);
	    paramVec.push_back(alpha);
	    paramVec.push_back(snds_hi[cd]*cm);
	    paramVec.push_back(snds_bot[cd]*cm);
	    paramVec.push_back(snds_top[cd]*cm);
	    paramVec.push_back(alpha);

	    std::sprintf(nam,"SNDS%03d",sand_id[id-1]-1);
	    GsimTrap* sci = new GsimTrap(std::string(nam),trap,
					 G4ThreeVector(offset_x*cm,offset_h*cm,0),
					 G4ThreeVector());
	    
	    sci->setParameters(paramVec);
	    sci->setOuterColor("yellow");
	    sci->setBriefName("SAND");
	    sci->setSensitiveDetector("SAND",sand_id[id-1]-1);
	    trap->addDaughter(sci);

	    {
	      double  b = snds_bot[cd];
	      double  bb = 0.7;
	      //std::cout << i << " : " << bb << std::endl;
	      int  idc = 0;
	      while( b - bb > 1.0 ) {
		double  l = snds_hi[cd] * (b-bb) / b;
		//std::cout << i << " : " << bb << " : " << l << std::endl;
		double  th = 0.2;
		float  p_sndl[]={ th/2, l/2, Csic_Len/2 };
		paramVec.clear();
		paramVec.push_back(th*cm);
		paramVec.push_back(l*cm);
		paramVec.push_back(Csic_Len*cm);
		
		double  offset_h = -snds_hi[cd]/2;
		double  offset_x = -snds_bot[cd]/4;
		double  cx = bb - th/2 + offset_x;
		double  cy = l/2  + offset_h;

		std::sprintf(nam,"SNDL%03d%02d",sand_id[id-1]-1,idc);
		GsimBox* box = new GsimBox(std::string(nam),sci,
					   G4ThreeVector(cx*cm,cy*cm,0),
					   G4ThreeVector());
		box->setOuterMaterial("G4_Pb");
		box->setParameters(paramVec);
		box->setOuterColor("yellow");
		box->setBriefName("SAND");
		sci->addDaughter(box);
		m_detList.push_back(box);
		idc++;
		bb += 0.7;
	      }
	    }
	  }
	}
      }
    }
  }
}


GsimE391SAND::~GsimE391SAND()
{
  ;
}


void GsimE391SAND::setFastSimulationLevel(int level)
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
      (*it)->setSensitiveDetector("SAND",0);
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
