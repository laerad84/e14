/**
 *  @file
 *  @brief  GsimE14CV
 *  $Id: GsimE14CV.cc,v 1.3 2006/12/06 19:04:45 nanjo Exp $ 
 *  $Log: GsimE14CV.cc,v $
 *  Revision 1.3  2006/12/06 19:04:45  nanjo
 *  CVS variables.
 *
 *
 */
#include "GsimE14Detector/GsimE14CV.h"
#include "GsimE14Detector/GsimE14UserGeom.h"
#include "GsimDetector/GsimBox.h"
#include "GsimDetector/GsimTube.h"
#include "GsimDetector/GsimTrap.h"
#include "GsimDetector/GsimPolyhedra2.h"
#include "GsimDetector/GsimPolyhedra2WithASquareHole.h"
#include "GsimPersistency/GsimMessage.h"

#include <vector>
#include <sstream>

using namespace E14;

GsimE14CV::GsimE14CV(std::string name,
		     GsimDetector* motherDetector,
		     G4ThreeVector transV,G4ThreeVector rotV,
		     int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{

  m_className = "GsimE14CV";
  // CV  Charged Veto
  m_mode=2;
  if(m_mode==2) {

    
    bool withMylar=false;
    bool withStructure=true;
    bool withFCV=true;
    bool withRCV=true;
    
    

    if(m_userFlag==0) {
      withMylar=false;
      withStructure=true;
      withFCV=true;
      withRCV=true;
    } else if(m_userFlag==1) {
      withMylar=false;
      withStructure=false;
      withFCV=true;
      withRCV=true;
    } else if(m_userFlag==2) {
      withMylar=false;
      withStructure=false;
      withFCV=false;
      withRCV=true;
    } else if(m_userFlag==3) {
      withMylar=false;
      withStructure=false;
      withFCV=true;
      withRCV=false;
    } else if(m_userFlag==4) {
      withMylar=true;
      withStructure=true;
      withFCV=true;
      withRCV=true;
    }
    
    std::vector<double> paramVec;
    GsimTrap* trapSC=0;
    GsimTrap* fiber=0;

    //Al frame
    //polyheadron
    double dAL=965*mm;
    double tAL=6*mm;
    double hAL=40*mm;
    double wAL=80*mm;

    //Mylar
    double tMylar=12e-3*mm;

    //CFRP
    double tCFRP=0.13*6*mm;
    
    double rearZ0=-40*mm;//rearCV downstream surface
    double frontZ0=rearZ0-250*mm;//frontCV downstream surface

    double rearBHD=77.5*mm;//half length
    double frontBHD=121*mm;//half length
        
    double rearY0=-76.5*mm;
    double rearX0=-76.35*mm;
    double frontY0=120*mm;
    double frontX0=-119.85*mm;
    double yOffset=0.15*mm;;
    

    
      
    double thick = 3*mm;
    double width=69*mm;

    if(withMylar) {
      GsimPolyhedra2WithASquareHole* rmylar =
	new GsimPolyhedra2WithASquareHole("rMylar",this,
					  G4ThreeVector(0,0,rearZ0-thick-tMylar/2.),
					  G4ThreeVector(0,0,0));
      paramVec.clear();    
      paramVec.push_back(360*deg/32.);
      paramVec.push_back(360*deg);
      paramVec.push_back(16);
      paramVec.push_back(tMylar);
      paramVec.push_back(dAL-hAL);
      paramVec.push_back(rearBHD);
      rmylar->setParameters(paramVec);
      rmylar->setOuterColor("yellow");
      rmylar->setOuterMaterial("GsimCFRP");
      addDaughter(rmylar);

      GsimPolyhedra2WithASquareHole* fmylar =
	new GsimPolyhedra2WithASquareHole("fMylar",this,
					  G4ThreeVector(0,0,frontZ0-thick-tMylar/2.),
					  G4ThreeVector(0,0,0));
      paramVec.clear();    
      paramVec.push_back(360*deg/32.);
      paramVec.push_back(360*deg);
      paramVec.push_back(16);
      paramVec.push_back(tMylar);
      paramVec.push_back(dAL);
      paramVec.push_back(frontBHD);
      fmylar->setParameters(paramVec);
      fmylar->setOuterColor("lightyellow");
      fmylar->setOuterMaterial("G4_MYLAR");
      addDaughter(fmylar);
    }
    
    if(withStructure) {

      //CFRP
      //16gon - square - recatangular hole
      GsimPolyhedra2WithASquareHole* rcfrp =
	new GsimPolyhedra2WithASquareHole("rCFRP",this,
					  G4ThreeVector(0,0,rearZ0+tCFRP/2.),
					  G4ThreeVector(0,0,0));
      paramVec.clear();    
      paramVec.push_back(360*deg/32.);
      paramVec.push_back(360*deg);
      paramVec.push_back(16);
      paramVec.push_back(tCFRP);
      paramVec.push_back(dAL);
      paramVec.push_back(rearBHD);
      
      rcfrp->setParameters(paramVec);
      rcfrp->setOuterColor("gray70");
      rcfrp->setOuterMaterial("G4_MYLAR");
    
      addDaughter(rcfrp);


      GsimPolyhedra2WithASquareHole* fcfrp =
	new GsimPolyhedra2WithASquareHole("fCFRP",this,
					  G4ThreeVector(0,0,frontZ0+tCFRP/2.),
					  G4ThreeVector(0,0,0));

      paramVec.clear();
      paramVec.push_back(360*deg/32.);
      paramVec.push_back(360*deg);
      paramVec.push_back(16);
      paramVec.push_back(tCFRP);
      paramVec.push_back(dAL);
      paramVec.push_back(121*mm);
      
      fcfrp->setParameters(paramVec);
      fcfrp->setOuterColor("gray70");
      fcfrp->setOuterMaterial("GsimCFRP");
      addDaughter(fcfrp);

    
    
      //Al frame
      //polyheadron
      

      paramVec.clear();
      paramVec.push_back(360./32.*deg);
      paramVec.push_back(360*deg);
      paramVec.push_back(16);
      paramVec.push_back(tAL);
      paramVec.push_back(dAL-hAL);
      paramVec.push_back(dAL);
      GsimPolyhedra2* frame0 = new GsimPolyhedra2("Frame0",this,
						  G4ThreeVector(0,0,frontZ0+tCFRP+tAL/2.),
						  G4ThreeVector(0,0,0));
      frame0->setParameters(paramVec);
      frame0->setOuterColor("gray25");
      frame0->setOuterMaterial("G4_Al");
      frame0->cloneDetector(G4ThreeVector(0,0,frontZ0+tCFRP+tAL+(wAL-tAL*2)+tAL/2.),
			    G4ThreeVector(0,0,0));
      frame0->cloneDetector(G4ThreeVector(0,0,rearZ0-tAL/2.),
			    G4ThreeVector(0,0,0));
      frame0->cloneDetector(G4ThreeVector(0,0,rearZ0-tAL-(wAL-tAL*2)-tAL/2.),
			    G4ThreeVector(0,0,0));
      addDaughter(frame0);


      paramVec.clear();
      paramVec.push_back(360./32.*deg);
      paramVec.push_back(360*deg);
      paramVec.push_back(16);
      paramVec.push_back(wAL-tAL*2);
      paramVec.push_back(dAL-tAL);
      paramVec.push_back(dAL);
      GsimPolyhedra2* frame1 = new GsimPolyhedra2("Frame1",this,
						  G4ThreeVector(0,0,frontZ0+tCFRP+tAL+(wAL-tAL*2)/2.),
						  G4ThreeVector(0,0,0));
      frame1->setParameters(paramVec);
      frame1->setOuterColor("gray25");
      frame1->setOuterMaterial("G4_Al");
      frame1->cloneDetector(G4ThreeVector(0,0,rearZ0-tAL-(wAL-tAL*2)/2.),
			    G4ThreeVector(0,0,0));
      addDaughter(frame1);
    }

    
    //Scintillator
    
    

    const char*  rnameList[11]={
      "R0",
      "R1",
      "R2",
      "R3",
      "R4",
      "R5",
      "R6",
      "R7",
      "R8",
      "R9",
      "R10"
    };
    int    ridList[11]={
      0,
      1,
      2,
      3,
      4,
      5,
      6,
      7,
      8,
      9,
      10
    };
    double rwList[11]=
      {
	width,
	width,
	width,
	width,
	width,
	width,
	width,
	width,
	width,
	width,
	width
      };
    double rlList[11]=
      {
	916.4*mm,
	916.4*mm,
	887.7*mm,
	859*mm,
	830.4*mm,
	801.7*mm,
	773.1*mm,
	696.2*mm,
	627*mm,
	557.9*mm,
	488.7*mm
      };


    const char*  fnameList[13]={
      "F0",
      "F1",
      "F2",
      "F3u",
      "F3d",
      "F4",
      "F5",
      "F6",
      "F7",
      "F8",
      "F9",
      "F10",
      "F11"
    };
    
      

    int    fidList[13]={
      0,
      1,
      2,
      3,
      3,
      4,
      5,
      6,
      7,
      8,
      9,
      10,
      11
    };
    double fwList[13]=
      {
	width,
	width,
	width,
	34.5*mm,
	width-34.5*mm,
	width,
	width,
	width,
	width,
	width,
	width,
	width,
	width
      };
    double fl1List[13]=
      {
	1000.4*mm,
	1000.4*mm,
	1000.4*mm,
	1000.4*mm,
	1000.4*mm,
	986*mm,
	957.4*mm,
	928.7*mm,
	862.1*mm,
	793.0*mm,
	723.8*mm,
	648.4*mm,
	723.2*mm
      };
    double fl2List[13]=
      {
	1000.4*mm,
	1000.4*mm,
	1000.4*mm,
	1000.4*mm,
	986.1*mm,
	957.4*mm,
	928.8*mm,
	862.3*mm,
	793.1*mm,
	724.0*mm,
	648.8*mm,
	481.8*mm,
	390.1*mm
      };
    double fdList[13]=
      {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	166.55*mm
      };
    
    double xCenter=0;
    double yCenter=0;
    double zCenter=0;

    
    double yBase=frontY0;

    
    for(int i=0;i<13;i++) {
      if(!withFCV) continue;
      fgetCenter(fwList[i],fl1List[i],fl2List[i],fdList[i],
		xCenter,yCenter,zCenter);
      fmakeParameter(fwList[i],fl1List[i],fl2List[i],fdList[i],paramVec);

      if(i==12) frontX0=-xCenter;
      double xPos=frontX0+xCenter;
      if(i>0) {
	if(i==4) {
	  yBase+=fwList[i-1];
	} else {
	  yBase+=fwList[i-1]+yOffset;;
	}
      }
      double yPos=yBase+yCenter;
      double zPos=frontZ0+zCenter;

      trapSC = new GsimTrap(std::string(fnameList[i]),this,
			    G4ThreeVector(xPos,yPos,zPos),
			    G4ThreeVector(0,0,0)
			    );
      trapSC->setParameters(paramVec);
      trapSC->setOuterColor("lightyellow");
      trapSC->setSensitiveDetector("CV",fidList[i]*2+12*0);
      


      double fiberL1=0;
      double fiberL2=0;
      double fiberD=0;
      if(i>=0 && i<=3) {
	fiberL1=fl1List[i];
	fiberL2=fl2List[i];
	fiberD=fdList[i];
	
	fgetFiberCenter(fiberL1,fiberL2,fiberD,
			xCenter,yCenter,zCenter);
	fmakeFiberParameter(fiberL1,fiberL2,fiberD,paramVec);

	double xfPos=(frontX0+xCenter)-xPos;
	double yfPos=(yBase+69*mm/2.-1.1*mm/2.+yCenter)-yPos;
	if(i==3) yfPos-=1.1*mm/2.-0.1*mm;//groove is on the boundary -> shift
	double zfPos=(frontZ0+zCenter)-zPos;
	
	fiber = new GsimTrap(std::string(fnameList[i])+std::string("fiber"),trapSC,
			     G4ThreeVector(xfPos,yfPos,zfPos),
			     G4ThreeVector(0,0,0)
			     );
	fiber->setParameters(paramVec);
	fiber->setOuterColor("red");
	for(int k=0;k<7;k++) {
	  if(k==3) continue;
	  if(i==3 && k>=4) continue;
	  fiber->cloneDetector(G4ThreeVector(xfPos,
					     yfPos+10*mm*(-3+k),
					     zfPos),
			       G4ThreeVector(0,0,0));
	}
	trapSC->addDaughter(fiber);
      } else if(i==4) {
	for(int k=4;k<7;k++) {
	  double offset1= -0.1*mm-1.1*mm/2.+10*mm*(k-3)-1.1/2.*mm;
	  double offset2= -0.1*mm-1.1*mm/2.+10*mm*(k-3)+1.1/2.*mm;
	  fiberL1=(fl1List[i]*(fwList[i]-offset1)+fl2List[i]*offset1)/fwList[i];
	  fiberL2=(fl1List[i]*(fwList[i]-offset2)+fl2List[i]*offset2)/fwList[i];
	  fiberD=fdList[i]/fwList[i]*1.1*mm;
	  double xoffset=fdList[i]/fwList[i]*offset1;
	  fgetFiberCenter(fiberL1,fiberL2,fiberD,
			  xCenter,yCenter,zCenter);
	  fmakeFiberParameter(fiberL1,fiberL2,fiberD,paramVec);
	  double xfPos=(frontX0+xoffset+xCenter)-xPos;
	  double yfPos=(yBase-0.1*mm-1.1*mm/2.+10*mm*(k-3)-1.1*mm/2.+yCenter)-yPos;
	  double zfPos=(frontZ0+zCenter)-zPos;


	  std::ostringstream fnam;
	  fnam << fnameList[i] << "fiber_" << k;
	  fiber = new GsimTrap(fnam.str(),trapSC,
			       G4ThreeVector(xfPos,yfPos,zfPos),
			       G4ThreeVector(0,0,0)
			       );
	  fiber->setParameters(paramVec);
	  fiber->setOuterColor("red");
	  trapSC->addDaughter(fiber);
	}
      } else if(i>4) {
	for(int k=0;k<7;k++) {
	  double offset1=4.5*mm+10*mm*k-1.1/2.*mm;
	  double offset2=4.5*mm+10*mm*k+1.1/2.*mm;
	  fiberL1=(fl1List[i]*(fwList[i]-offset1)+fl2List[i]*offset1)/fwList[i];
	  fiberL2=(fl1List[i]*(fwList[i]-offset2)+fl2List[i]*offset2)/fwList[i];
	  fiberD=fdList[i]/fwList[i]*1.1*mm;
	  double xoffset=fdList[i]/fwList[i]*offset1;
	  fgetFiberCenter(fiberL1,fiberL2,fiberD,
			  xCenter,yCenter,zCenter);
	  fmakeFiberParameter(fiberL1,fiberL2,fiberD,paramVec);
	  double xfPos=(frontX0+xoffset+xCenter)-xPos;
	  double yfPos=(yBase+69*mm/2.+10*mm*(-3+k)-1.1*mm/2.+yCenter)-yPos;
	  double zfPos=(frontZ0+zCenter)-zPos;


	  std::ostringstream fnam;
	  fnam << fnameList[i] << "fiber_" << k;
	  fiber = new GsimTrap(fnam.str(),trapSC,
			       G4ThreeVector(xfPos,yfPos,zfPos),
			       G4ThreeVector(0,0,0)
			       );
	  fiber->setParameters(paramVec);
	  fiber->setOuterColor("red");
	  trapSC->addDaughter(fiber);
	}
	
      }

      
      trapSC->cloneDetector(G4ThreeVector(-yPos,xPos,zPos),
       			    G4ThreeVector(0,0,90*deg),fidList[i]*2+12*2*1);
      trapSC->cloneDetector(G4ThreeVector(-xPos,-yPos,zPos),
       			    G4ThreeVector(0,0,180*deg),fidList[i]*2+12*2*2);
      trapSC->cloneDetector(G4ThreeVector(yPos,-xPos,zPos),
       			    G4ThreeVector(0,0,270*deg),fidList[i]*2+12*2*3);
      addDaughter(trapSC);
    }








    



    yBase=rearY0;
    for(int i=0;i<11;i++) {
      if(!withRCV) continue;
      rgetCenter(rwList[i],rlList[i],
		 xCenter,yCenter,zCenter);
      rmakeParameter(rwList[i],rlList[i],paramVec);
      
      double xPos=rearX0+xCenter;
      if(i>0) {
	yBase+=-rwList[i-1]-yOffset;;
      }
      double yPos=yBase+yCenter;
      double zPos=rearZ0+zCenter;
      
      trapSC = new GsimTrap(std::string(rnameList[i]),this,
			    G4ThreeVector(xPos,yPos,zPos),
			    G4ThreeVector(0,0,0)
			    );
      trapSC->setParameters(paramVec);
      trapSC->setOuterColor("yellow");
      trapSC->setSensitiveDetector("CV",100+ridList[i]*2+11*2*3);
      
      
      rgetFiberCenter(rlList[i],
		      xCenter,yCenter,zCenter);
      rmakeFiberParameter(rlList[i],paramVec);
      double xfPos=(rearX0+xCenter)-xPos;
      double yfPos=(yBase-69*mm/2.+1.1*mm/2.+yCenter)-yPos;
      double zfPos=(rearZ0+zCenter)-zPos;
      
      fiber = new GsimTrap(std::string(rnameList[i])+std::string("fiber"),trapSC,
			   G4ThreeVector(xfPos,yfPos,zfPos),
			   G4ThreeVector(0,0,0)
			   );
      fiber->setParameters(paramVec);
      fiber->setOuterColor("red");
      
      for(int k=0;k<7;k++) {
	if(k==3) continue;
	fiber->cloneDetector(G4ThreeVector(xfPos,
					   yfPos+10*mm*(-3+k),
					   zfPos),
			     G4ThreeVector(0,0,0));
      }
      trapSC->addDaughter(fiber);
      
      
      trapSC->cloneDetector(G4ThreeVector(-yPos,xPos,zPos),
       			    G4ThreeVector(0,0,90*deg),100+ridList[i]*2+11*2*0);
      trapSC->cloneDetector(G4ThreeVector(-xPos,-yPos,zPos),
       			    G4ThreeVector(0,0,180*deg),100+ridList[i]*2+11*2*1);
      trapSC->cloneDetector(G4ThreeVector(yPos,-xPos,zPos),
			    G4ThreeVector(0,0,270*deg),100+ridList[i]*2+11*2*2);
      
      addDaughter(trapSC);
    }
    
    
    setThisAndDaughterBriefName("CV");
  } else if(m_mode==1){
    
    double  front_bh=24;//cm
    double  rear_bh=15;//cm
    double  chv_rmax = 99;
    double  chv_thick = 0.3;   // 5 mm scintillator
    double  chv_fsp=1.;       //1.4cm fiber spacing
    int     chv_ngang=7;       // 8 ganging
    
    int     chv_nch=13;         // 8 channel/module
    int     chv_npoly=32;      //32 polygon
    
    double  z_rear=-chv_thick/2.;
    double  z_front=-25-chv_thick/2.;
    double  chv_width=chv_fsp*chv_ngang;
    double  chv_tmylar=0.0025;//cm -> 25um


    double* ychdiv = new double[chv_nch+1];
    double* xpolydiv = new double[chv_npoly/4+1];
    double* ypolydiv = new double[chv_npoly/4+1];

    double bh[2]={rear_bh,front_bh};
    for(int j=0;j<2;j++) {
      //rear and front
      
      for(int i=0;i<chv_nch;i++) {
	ychdiv[i]=chv_width*i+bh[j]/2.;
      }
      ychdiv[chv_nch]=chv_rmax;
      
      double theta=2.*M_PI/chv_npoly;
      for(int i=0;i<chv_npoly/4+1;i++) {
	double x1=chv_rmax*sin(M_PI/2.+theta/2.-i*theta);
	double y1=chv_rmax*cos(M_PI/2.+theta/2.-i*theta);
	xpolydiv[i]=x1;
	ypolydiv[i]=y1;
      }
    
    
      std::vector<double> xposv;
      std::vector<double> yposv;
      std::vector<int>    chv;
    
      
      int cnt=0;
      for(int i=0;i<chv_npoly/4+1;i++) {
      
	if(cnt>0 && xpolydiv[i]>0 && ypolydiv[i]>bh[j]) {
	  xposv.push_back(xpolydiv[i]);
	  yposv.push_back(ypolydiv[i]);
	  chv.push_back(cnt-1);
	}
      
      
	if(cnt<chv_nch+1) {
	  while(ychdiv[cnt]>ypolydiv[i] &&
		ychdiv[cnt]<ypolydiv[i+1]) {
	    yposv.push_back(ychdiv[cnt]);
	  
	  
	    double x=
	      (
	       xpolydiv[i+1]*(ychdiv[cnt]-ypolydiv[i])+
	       xpolydiv[i]*(ypolydiv[i+1]-ychdiv[cnt])
	       )/(ypolydiv[i+1]-ypolydiv[i]);
	    xposv.push_back(x);
	    chv.push_back(cnt);
	    cnt++;
	  }
	}
      }


      std::vector<double> paramVec;
      int num=xposv.size();
      for(int i=0;i<num-1;i++) {
	paramVec.clear();
	paramVec.push_back(chv_thick*cm);
	paramVec.push_back(0*deg);
	paramVec.push_back(0*deg);
	paramVec.push_back((yposv[i+1]-yposv[i])*cm-2.*chv_tmylar*cm);
	paramVec.push_back((xposv[i]+bh[j]/2.)*cm);
	paramVec.push_back((xposv[i+1]+bh[j]/2.)*cm);
	paramVec.push_back(std::atan( ((xposv[i+1]+bh[j]/2.)-(xposv[i]+bh[j]/2.))/2./(yposv[i+1]-yposv[i]) )*rad);
	paramVec.push_back((yposv[i+1]-yposv[i])*cm-2.*chv_tmylar*cm);
	paramVec.push_back((xposv[i]+bh[j]/2.)*cm);
	paramVec.push_back((xposv[i+1]+bh[j]/2.)*cm);
	paramVec.push_back(std::atan( ((xposv[i+1]+bh[j]/2.)-(xposv[i]+bh[j]/2.))/2./(yposv[i+1]-yposv[i]) )*rad);

	char nam[100];
	if(j==0) {
	  std::sprintf(nam,"CVR%d",i);
	} else {
	  std::sprintf(nam,"CVF%d",i);
	}
	double xc=(
		   (xposv[i]+bh[j]/2.+
		    xposv[i+1]+bh[j]/2.)/4.-bh[j]/2.
		   );
	double yc= (yposv[i]+yposv[i+1])/2.;
	if(j==1) {
	  xc=-xc;
	}
	double zc= 0.;
	if(j==0) {
	  zc= z_rear;
	} else {
	  zc= z_front;
	}

	GsimTrap* trapSC=0;
	if(j==0) {
	  trapSC = new GsimTrap(std::string(nam),this,
				G4ThreeVector(xc*cm,yc*cm,zc*cm),
				G4ThreeVector(0,0,0*deg)
				);
	} else {
	  trapSC = new GsimTrap(std::string(nam),this,
				G4ThreeVector(xc*cm,yc*cm,zc*cm),
				G4ThreeVector(0,180*deg,0*deg)
				);
	}
	trapSC->setParameters(paramVec);
	if(j==0) {
	  if(chv[i]%2==0) {
	    trapSC->setOuterColor("yellow");
	  } else if(chv[i]%2==1) {
	    trapSC->setOuterColor("lightyellow");
	  }
	} else {
	  if(chv[i]%2==0) {
	    trapSC->setOuterColor("lightyellow");
	  } else if(chv[i]%2==1) {
	    trapSC->setOuterColor("yellow");
	  }
	}

	double yrot=0;
	if(j==1) yrot=180*deg;
	trapSC->setSensitiveDetector("CV",chv[i]+j*4*chv_nch);
	trapSC->cloneDetector(G4ThreeVector(-yc*cm,xc*cm,zc*cm),
			      G4ThreeVector(0,yrot,90*deg),chv[i]+chv_nch+j*4*chv_nch);
	trapSC->cloneDetector(G4ThreeVector(-xc*cm,-yc*cm,zc*cm),
			      G4ThreeVector(0,yrot,180*deg),chv[i]+2*chv_nch+j*4*chv_nch);
	trapSC->cloneDetector(G4ThreeVector(yc*cm,-xc*cm,zc*cm),
			      G4ThreeVector(0,yrot,270*deg),chv[i]+3*chv_nch+j*4*chv_nch);
      
	addDaughter(trapSC);
      }
    }

    delete [] ychdiv;
    delete [] xpolydiv;
    delete [] ypolydiv;

    
    setThisAndDaughterBriefName("CV");
  } else {
    double  chv_rmax = 99;
    double  chv_width_c=10.;//cm
    double  chv_width=14.58;//cm
    double  chv_thick = 0.5;   // 5 mm scintillator
    double  chv_gap   = 0.02;  //

    // inner part
    int     chv1_ndiv = 4;
    double  chv1_len  = CV_Len;
    double  chv1_rmin = 9.9999999 - chv_thick;
    double  chv1_rmax = 9.9999999;
    double c_chv1_z = - chv1_len/2;
  
    std::vector<double> paramVec;
    paramVec.push_back(-360./chv1_ndiv/2*deg);
    paramVec.push_back(360./chv1_ndiv*deg);
    paramVec.push_back(1);
    paramVec.push_back(chv1_len*cm);
    paramVec.push_back(chv1_rmin*cm);
    paramVec.push_back(chv1_rmax*cm);

    int cnt=0;
    char nam[100];
    for( int i=0;i<chv1_ndiv;i++ ){
      std::sprintf(nam,"CVI%02d",i);
      GsimPolyhedra2* hedra
	= new GsimPolyhedra2(std::string(nam),this,
			     G4ThreeVector(0,0,c_chv1_z*cm),
			     G4ThreeVector(0,0,2.*M_PI/4.*i));
      hedra->setParameters(paramVec);
      hedra->setOuterColor("yellow");
      hedra->setSensitiveDetector("CV",cnt);
      addDaughter(hedra);
      cnt++;
    }


    // Outer
    double  chv_h_c=(chv_width+chv_gap)*6+chv_gap/2.;
    double  chv_maxh=(chv_width+chv_gap)*6.5;

    double  chv_z[2] = {0,0};
    chv_z[0]=-chv1_len+chv_thick/2.;
    chv_z[1]=chv_z[0]+(chv_thick+chv_gap);
  
    double chv_h1[6];
    double chv_h2[6];
    double chv_y[6];
    for(int i=0;i<6;i++) {
      double y1=(chv_width+chv_gap)*i+(chv_width_c+chv_gap/2.);
      double y2=(chv_width+chv_gap)*(i+1)+(chv_width_c+chv_gap/2.);
      chv_y[i]=(y1+y2)/2.;
      chv_h1[i]=std::sqrt( std::pow(chv_rmax,2)-std::pow(y1,2) );
      chv_h2[i]=std::sqrt( std::pow(chv_rmax,2)-std::pow(y2,2) );
      if(chv_h1[i]>chv_maxh) chv_h1[i]=chv_maxh;
      if(chv_h2[i]>chv_maxh) chv_h2[i]=chv_maxh;
    }
  
    double lpos=chv_width_c+chv_h_c/2.;
    double spos=chv_width_c/2.;
  
    double xpos[8] = {lpos,spos,-spos, -lpos,-lpos,-spos,spos,lpos};
    double ypos[8] = {spos,lpos,lpos, spos,-spos,-lpos,-lpos,-spos};
    double zpos[8] = {chv_z[0],chv_z[1],chv_z[1],chv_z[0],chv_z[0],chv_z[1],chv_z[1],chv_z[0]};
    double zrot[8] = {0,90,90,0,0,90,90,0};
  
    GsimBox* box=0;
    for(int k=0;k<8;k++) {
      double x=xpos[k];
      double y=ypos[k];
      double z=zpos[k];
      if(box==0) {
	paramVec.clear();
	paramVec.push_back(chv_h_c*cm);
	paramVec.push_back(chv_width_c*cm);
	paramVec.push_back(chv_thick*cm);
	sprintf(nam,"CVC");
	box = new GsimBox(std::string(nam),this,
			  G4ThreeVector(x*cm,y*cm,z*cm),
			  G4ThreeVector(0,0,0));
	box->setParameters(paramVec);
	box->setOuterColor("yellow");
	box->setOuterCopyNo(cnt);
	box->setSensitiveDetector("CV",cnt);
	addDaughter(box);
      } else {
	box->cloneDetector(G4ThreeVector(x*cm,y*cm,z*cm),
			   G4ThreeVector(0,0,zrot[k]*deg),
			   cnt);
      
      }
      cnt++;
    }

    GsimTrap* trapSC[6];
    for(int i=0;i<6;i++) {
      paramVec.clear();
      paramVec.push_back(chv_thick*cm);
      paramVec.push_back(0*deg);
      paramVec.push_back(0*deg);
      paramVec.push_back(chv_width*cm);
      paramVec.push_back(chv_h1[i]*2.*cm);
      paramVec.push_back(chv_h2[i]*2.*cm);
      paramVec.push_back(0*deg);
      paramVec.push_back(chv_width*cm);
      paramVec.push_back(chv_h1[i]*2.*cm);
      paramVec.push_back(chv_h2[i]*2.*cm);
      paramVec.push_back(0*deg);
    
      std::sprintf(nam,"CVO%d",i);
      trapSC[i]
	= new GsimTrap(std::string(nam),this,
		       G4ThreeVector(0,chv_y[i]*cm,chv_z[0]*cm),
		       G4ThreeVector(0,0,0*deg)
		       );
      trapSC[i]->setParameters(paramVec);
      trapSC[i]->setOuterColor("yellow");
      addDaughter(trapSC[i]);
    }
  
    for(int i=0;i<6;i++) {
      trapSC[i]->setSensitiveDetector("CV",cnt+18);//Y+ cannel
      trapSC[5-i]->cloneDetector(G4ThreeVector(0,-chv_y[5-i]*cm,chv_z[0]*cm),
				 G4ThreeVector(0,0,180*deg),cnt+12);//Y- channel
      trapSC[5-i]->cloneDetector(G4ThreeVector(-chv_y[5-i]*cm,0,chv_z[1]*cm),
				 G4ThreeVector(0,0,90*deg),cnt);//X- channel
      trapSC[i]->cloneDetector(G4ThreeVector(chv_y[i]*cm,0,chv_z[1]*cm),
			       G4ThreeVector(0,0,-90*deg),cnt+6);//X+ channel
      cnt++;
    }
    setThisAndDaughterBriefName("CV");
  }
}

GsimE14CV::~GsimE14CV()
{
  ;
}

void GsimE14CV::fgetCenter(double width,double l1,double l2,double d,
			   double& xCenter,double& yCenter,double& zCenter)
{
  double thick = 3*mm;
  //
  //    d             l2
  //  <----><------------------>
  //  |
  //  | width
  //  |
  //  <------------------------------->
  //                 l1

  double cx=(l1/2.+(d+l2/2.))/2.;
  double cy=width/2.;
  double cz=0;
  
  double L1=l1+thick/sqrt(3.)- (l1-l2)/width* (thick/sqrt(3.));
  if(l1==l2) {
    L1=l1+thick/sqrt(3.)+thick/sqrt(3.);
  }
  double dxR=0;
  double dxL=0;
  if(d!=0) {
    dxL=d/width* (thick/sqrt(3.));
    dxR=(l1-(d+l2))/width* (thick/sqrt(3.));
    L1=l1-dxR-dxL;
  }
  double L2=l2+thick/sqrt(3.)- (l1-(d+l2))/width* (thick/sqrt(3.));
  if(l1==l2) {
    L2=l2+thick/sqrt(3.)+thick/sqrt(3.);
  }
  if(d!=0) {
    L2=l2-dxR-dxL;
  }
  double A=-std::atan(((-thick/sqrt(3)+dxL+L1/2.)-(-thick/sqrt(3)+d+dxL+L2/2.))/width)*rad;
  double CX=(-thick/sqrt(3)+dxL+L1/2.+(-thick/sqrt(3)+d+dxL+L2/2.))/2.;
  double CY=width/2.+thick/sqrt(3.);
  double CZ=-thick;
  if(d!=0) {
    A=-std::atan(((dxL+L1/2.)-(d+dxL+L2/2.))/width)*rad;
    CX=(dxL+L1/2.+(d+dxL+L2/2.))/2.;
    CY=width/2.+thick/sqrt(3.);
    CZ=-thick;
  }
  
  xCenter=(CX+cx)/2.;
  yCenter=(CY+cy)/2.;
  zCenter=(CZ+cz)/2.;
}
  
void GsimE14CV::fmakeParameter(double width,double l1,double l2,double d,std::vector<double>& paramVec)
{
  double thick = 3*mm;
  //
  //    d             l2
  //  <----><------------------>
  //  |
  //  | width
  //  |
  //  <------------------------------->
  //                 l1
  
  double a=-std::atan((l1/2.-(d+l2/2.))/width)*rad;
  double cx=(l1/2.+(d+l2/2.))/2.;
  double cy=width/2.;
  double cz=0;
  
  double L1=l1+thick/sqrt(3.)- (l1-l2)/width* (thick/sqrt(3.));
  if(l1==l2) {
    L1=l1+thick/sqrt(3.)+thick/sqrt(3.);
  }
  double dxR=0;
  double dxL=0;
  if(d!=0) {
    dxL=d/width* (thick/sqrt(3.));
    dxR=(l1-(d+l2))/width* (thick/sqrt(3.));
    L1=l1-dxR-dxL;
  }
  double L2=l2+thick/sqrt(3.)- (l1-(d+l2))/width* (thick/sqrt(3.));
  if(l1==l2) {
    L2=l2+thick/sqrt(3.)+thick/sqrt(3.);
  }
  if(d!=0) {
    L2=l2-dxR-dxL;
  }
  double A=-std::atan(((-thick/sqrt(3)+dxL+L1/2.)-(-thick/sqrt(3)+d+dxL+L2/2.))/width)*rad;
  double CX=(-thick/sqrt(3)+dxL+L1/2.+(-thick/sqrt(3)+d+dxL+L2/2.))/2.;
  double CY=width/2.+thick/sqrt(3.);
  double CZ=-thick;
  if(d!=0) {
    A=-std::atan(((dxL+L1/2.)-(d+dxL+L2/2.))/width)*rad;
    CX=(dxL+L1/2.+(d+dxL+L2/2.))/2.;
    CY=width/2.+thick/sqrt(3.);
    CZ=-thick;
  }
    
  double dx=(cx-CX);
  double dy=(cy-CY);
  double dz=(cz-CZ);

  
  
  double theta=std::atan(sqrt(dx*dx+dy*dy)/dz)*rad;
  double phi=std::atan2(dy,dx)*rad;

  paramVec.clear();
  paramVec.push_back(thick);
  paramVec.push_back(theta);
  paramVec.push_back(phi);
  paramVec.push_back(width);
  paramVec.push_back(L1);
  paramVec.push_back(L2);
  paramVec.push_back(A);
  paramVec.push_back(width);
  paramVec.push_back(l1);
  paramVec.push_back(l2);
  paramVec.push_back(a);

  
}



void GsimE14CV::fmakeFiberParameter(double l1,double l2,double d,std::vector<double>& paramVec)
{
  double thick = 1.1*mm;
  double width = 1.1*mm;
  //
  //    d             l2
  //  <----><------------------>
  //  |
  //  | width
  //  |
  //0 <------------------------------->
  //                 l1
  
  double a=-atan((l1/2.-(d+l2/2.))/width)*rad;
  double cx=(l1/2.+(d+l2/2.))/2.;
  double cy=width/2.;
  double cz=0;
  
  double L1=l1+thick/sqrt(3.);
  if(l1==l2) {
    L1=l1+thick/sqrt(3.)+thick/sqrt(3.);
  }
  if(d!=0) {
    L1=l1;
  }
  double L2=l2+thick/sqrt(3.);
  if(l1==l2) {
    L2=l2+thick/sqrt(3.)+thick/sqrt(3.);
  }
  if(d!=0) {
    L2=l2;
  }
  double A=-atan(((-thick/sqrt(3)+L1/2.)-(-thick/sqrt(3)+L2/2.))/width)*rad;
  double CX=(-thick/sqrt(3)+L1/2.+(-thick/sqrt(3)+L2/2.))/2.;
  double CY=width/2.;
  double CZ=-thick;
  if(d!=0) {
    A=-atan(((L1/2.)-(d+L2/2.))/width)*rad;
    CX=(L1/2.+(d+L2/2.))/2.;
    CY=width/2.;
    CZ=-thick;
  }
    
  double dx=(cx-CX);
  double dy=(cy-CY);
  double dz=(cz-CZ);

  double theta=atan(sqrt(dx*dx+dy*dy)/dz)*rad;
  double phi=std::atan2(dy,dx)*rad;
    


  paramVec.clear();
  paramVec.push_back(thick);
  paramVec.push_back(theta);
  paramVec.push_back(phi);
  paramVec.push_back(width);
  paramVec.push_back(L1);
  paramVec.push_back(L2);
  paramVec.push_back(A);
  paramVec.push_back(width);
  paramVec.push_back(l1);
  paramVec.push_back(l2);
  paramVec.push_back(a);
}

void GsimE14CV::fgetFiberCenter(double l1,double l2,double d,
				double& xCenter,double& yCenter,double& zCenter)
{
  double thick = 1.1*mm;
  double width = 1.1*mm;
  //
  //    d             l2
  //  <----><------------------>
  //  |
  //  | width
  //  |
  //  <------------------------------->
  //                 l1

  double cx=(l1/2.+(d+l2/2.))/2.;
  double cy=width/2.;
  double cz=0;
  
  double L1=l1+thick/sqrt(3.);
  if(l1==l2) {
    L1=l1+thick/sqrt(3.)+thick/sqrt(3.);
  }
  if(d!=0) {
    L1=l1;
  }
  double L2=l2+thick/sqrt(3.);
  if(l1==l2) {
    L2=l2+thick/sqrt(3.)+thick/sqrt(3.);
  }
  if(d!=0) {
    L2=l2;
  }
  double A=-atan(((-thick/sqrt(3)+L1/2.)-(-thick/sqrt(3)+d+L2/2.))/width)*rad;
  double CX=(-thick/sqrt(3)+L1/2.+(-thick/sqrt(3)+d+L2/2.))/2.;
  double CY=width/2.;
  double CZ=-thick;
  if(d!=0) {
    A=-atan(((L1/2.)-(d+L2/2.))/width)*rad;
    CX=(L1/2.+(d+L2/2.))/2.;
    CY=width/2.;
    CZ=-thick;
  }
  
  xCenter=(CX+cx)/2.;
  yCenter=(CY+cy)/2.;
  zCenter=(CZ+cz)/2.;
}


void GsimE14CV::rgetCenter(double width,double l,
			   double& xCenter,double& yCenter,double& zCenter)
{
  double thick = 3*mm;
  //
  //  0               l
  //  <------------------------------->
  //  |
  //  | width
  //  |
  //  <------------------------------->
  //                 l
  
  double cx=l/2.;
  double cy=-width/2.;
  double cz=0;
  
  double L=l+thick/sqrt(3.);
  double CX=L/2.-thick/sqrt(3.);
  double CY=-width/2.-thick/sqrt(3.);
  double CZ=-thick;

  xCenter=(CX+cx)/2.;
  yCenter=(CY+cy)/2.;
  zCenter=(CZ+cz)/2.;
}
  
void GsimE14CV::rmakeParameter(double width,double l,std::vector<double>& paramVec)
{
  double thick = 3*mm;
  //
  //                 l
  //  <------------------------------->
  //  |
  //  | width
  //  |
  //  <------------------------------->
  //                 l
  
  double a=0;
  double cx=l/2.;
  double cy=-width/2.;
  double cz=0;
  
  double L=l+thick/sqrt(3.);
  double A=0;
  double CX=L/2.-thick/sqrt(3.);
  double CY=-width/2.-thick/sqrt(3.);
  double CZ=-thick;
    
  double dx=(cx-CX);
  double dy=(cy-CY);
  double dz=(cz-CZ);
  
  double theta=atan(sqrt(dx*dx+dy*dy)/dz)*rad;
  double phi=std::atan2(dy,dx)*rad;


  paramVec.clear();
  paramVec.push_back(thick);
  paramVec.push_back(theta);
  paramVec.push_back(phi);
  paramVec.push_back(width);
  paramVec.push_back(L);
  paramVec.push_back(L);
  paramVec.push_back(A);
  paramVec.push_back(width);
  paramVec.push_back(l);
  paramVec.push_back(l);
  paramVec.push_back(a);

  
}

void GsimE14CV::rmakeFiberParameter(double l,std::vector<double>& paramVec)
{
  double thick = 1.1*mm;
  double width = 1.1*mm;
  //
  //                 l
  //  <------------------------------->
  //  |
  //  | width
  //  |
  //  <------------------------------->
  //                 l
  
  double a=0;
  double cx=l/2.;
  double cy=-width/2.;
  double cz=0;
  
  double L=l+thick/sqrt(3.);
  double A=0;
  double CX=L/2.-thick/sqrt(3.);
  double CY=-width/2.;
  double CZ=-thick;
    
  double dx=(cx-CX);
  double dy=(cy-CY);
  double dz=(cz-CZ);
  
  double theta=atan(sqrt(dx*dx+dy*dy)/dz)*rad;
  double phi=std::atan2(dy,dx)*rad;


  paramVec.clear();
  paramVec.push_back(thick);
  paramVec.push_back(theta);
  paramVec.push_back(phi);
  paramVec.push_back(width);
  paramVec.push_back(L);
  paramVec.push_back(L);
  paramVec.push_back(A);
  paramVec.push_back(width);
  paramVec.push_back(l);
  paramVec.push_back(l);
  paramVec.push_back(a);

  
}
void GsimE14CV::rgetFiberCenter(double l,
				double& xCenter,double& yCenter,double& zCenter)
{
  double thick = 1.1*mm;
  double width = 1.1*mm;
  //
  //  0               l
  //  <------------------------------->
  //  |
  //  | width
  //  |
  //  <------------------------------->
  //                 l
  
  double cx=l/2.;
  double cy=-width/2.;
  double cz=0;
  
  double L=l+thick/sqrt(3.);
  double CX=L/2.-thick/sqrt(3.);
  double CY=-width/2.;
  double CZ=-thick;

  xCenter=(CX+cx)/2.;
  yCenter=(CY+cy)/2.;
  zCenter=(CZ+cz)/2.;
}
