/**
 *  @file
 *  @brief  GsimE14CC03
 *  $Id: 
 *  $Log: 
 */
#include "GsimE14Detector/GsimE14CC03.h"
#include "GsimE14Detector/GsimE14UserGeom.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimDetector/GsimBox.h"

using namespace E14;

GsimE14CC03::GsimE14CC03(std::string name,
			 GsimDetector* motherDetector,
			 G4ThreeVector transV,G4ThreeVector rotV,
			 int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{
  
  m_className = "GsimE14CC03";
  m_model=4;
  //model
  //0:20cm beamhole 2.5cm
  //1:15cm beamhole 2.5cm
  //2:15cm beamhole 1.25cm
  //3:15.6cm beamhole 2.2cm
  //4:16.4cmx16.4cm hole , 17.9mmx45.4mm crystal
  //  made by Odani.

  if(m_model==4) {
    const int nBlock=16;
    double    CC03_HoleXY=16.4;//[cm];
    double    pos[nBlock][2];
    double    dim[nBlock][2];
    
    for(int i=0;i<nBlock;i++) {
    double x=0;
    double y=0;
    double dx=0;
    double dy=0;
    if(i>=0 && i<=3) {
      x=(-CC03_HoleXY/2.+0.5*CC03_X+(((i)*CC03_X+(i+1)*0.01)))*cm;
      y=(+CC03_HoleXY/2.+0.5*CC03_Y+CC03_YGap)*cm;
      dx=CC03_X*cm;
      dy=CC03_Y*cm;
    }
    else if(i>=4 && i<= 7) {
      x=(+CC03_HoleXY/2.+0.5*CC03_Y+CC03_YGap)*cm;
      y=(+CC03_HoleXY/2.-0.5*CC03_X-(((i-4)*CC03_X+(i-4+1)*0.01)))*cm;
      dx=CC03_Y*cm;
      dy=CC03_X*cm;
    }
    else if(i>=8 && i<= 11) {
      x=(+CC03_HoleXY/2.-0.5*CC03_X-(((i-8)*CC03_X+(i-8+1)*0.01)))*cm;
      y=(-CC03_HoleXY/2.-0.5*CC03_Y-CC03_YGap)*cm;
      dx=CC03_X*cm;
      dy=CC03_Y*cm;
    }
    else if(i>=12 && i<=15) {
      x=(-CC03_HoleXY/2.-0.5*CC03_Y-CC03_YGap)*cm;
      y=(-CC03_HoleXY/2.+0.5*CC03_X+(((i-12)*CC03_X+(i-12+1)*0.01)))*cm;
      dx=CC03_Y*cm;
      dy=CC03_X*cm;
    }
    else {
    }
    pos[i][0]=x;
    pos[i][1]=y;
    dim[i][0]=dx;
    dim[i][1]=dy;
    }
    std::vector<double> paramVec;
    
    
    
    GsimBox* boxSX=0;
    GsimBox* boxSY=0;
    
    char nam[100];
    for(int i=0;i<nBlock;i++) {
      paramVec.clear();
      
      
      if(std::abs(dim[i][0]-CC03_X*cm)<1e-6 &&
	 std::abs(dim[i][1]-CC03_Y*cm)<1e-6) {
	if(boxSX==0) {
	  paramVec.push_back(dim[i][0]);
	  paramVec.push_back(dim[i][1]);
	  paramVec.push_back(CC03_Len*cm);
	  std::sprintf(nam,"CC03boxSX");
	  boxSX = new GsimBox(std::string(nam),this,
			      G4ThreeVector(pos[i][0],
					    pos[i][1],
					    0.*cm),
			      G4ThreeVector(0,0,0)
			      );
	  boxSX->setOuterMaterial("G4_CESIUM_IODIDE");
	  boxSX->setParameters(paramVec);
	  boxSX->setOuterColor("magenta");
	  boxSX->setSensitiveDetector("CC03",i);
	  addDaughter(boxSX);
	} else {
	  boxSX->cloneDetector(G4ThreeVector(pos[i][0],
					     pos[i][1],
					     0.*cm),
			       G4ThreeVector(0,0,0),i
			       );
	}
      } else if(std::abs(dim[i][0]-CC03_Y*cm)<1e-6 &&
		std::abs(dim[i][1]-CC03_X*cm)<1e-6) {
	if(boxSY==0) {
	  paramVec.push_back(dim[i][0]);
	  paramVec.push_back(dim[i][1]);
	  paramVec.push_back(CC03_Len*cm);
	  std::sprintf(nam,"CC03boxSY");
	  boxSY = new GsimBox(std::string(nam),this,
			      G4ThreeVector(pos[i][0],
					    pos[i][1],
					    0.*cm),
			      G4ThreeVector(0,0,0)
			      );
	  boxSY->setOuterMaterial("G4_CESIUM_IODIDE");
	  boxSY->setParameters(paramVec);
	  boxSY->setOuterColor("magenta");
	  boxSY->setSensitiveDetector("CC03",i);
	  addDaughter(boxSY);
	} else {
	  boxSY->cloneDetector(G4ThreeVector(pos[i][0],
					     pos[i][1],
					     0.*cm),
			       G4ThreeVector(0,0,0),i
			       );
	}
      } else {
	;
      }
    }
    setThisAndDaughterBriefName("CC03");

  } else if(m_model==0) {
    std::vector<double> paramVec;
    paramVec.push_back(CC03_XY*cm);
    paramVec.push_back(CC03_XY*cm);
    paramVec.push_back(CC03_Len*cm);
    
    GsimBox* box=0;
    int nBlock=10;
    int nBeamHole=10;
    char nam[100];
    int id=0;
    for(int i=0;i<nBlock;i++) {
      double YBlock=
	(CC03_XY+CC03_Gap)*(i-nBlock/2.)
	+(CC03_XY+CC03_Gap)/2.;
      
      for(int j=0;j<nBlock;j++) {
	{

	  double XBlock=
	    (CC03_XY+CC03_Gap)*(j-nBlock/2.)
	    +(CC03_XY+CC03_Gap)/2.;
	  
	  if( i== 0) {

	  } else if(i==nBlock-1) {
	    
	  } else {
	    if( ! (j==0 || j==nBlock-1) ) continue;
	  }
	    
	  if(box==0) {
	    std::sprintf(nam,"CC03box");
	    box = new GsimBox(std::string(nam),this,
			      G4ThreeVector(XBlock*cm,
					    YBlock*cm,
					    0.*cm),
			      G4ThreeVector(0,0,0)
			      );
	    box->setOuterMaterial("G4_PbWO4");
	    box->setParameters(paramVec);
	    box->setOuterColor("magenta");
	    box->setSensitiveDetector("CC03",id);
	    addDaughter(box);
	  } else {
	    box->cloneDetector(G4ThreeVector(XBlock*cm,
					     YBlock*cm,
					     0.*cm),
			       G4ThreeVector(0,0,0),id);
	  }
	  id++;
	}
      }
    }
    setThisAndDaughterBriefName("CC03");
  } else if(m_model==1) {
    std::vector<double> paramVec;
    paramVec.push_back(CC03_XY*cm);
    paramVec.push_back(CC03_XY*cm);
    paramVec.push_back(CC03_Len*cm);
    
    GsimBox* box=0;
    int nBlock=8;
    int nBeamHole=8;
    char nam[100];
    int id=0;
    for(int i=0;i<nBlock;i++) {
      double YBlock=
	(CC03_XY+CC03_Gap)*(i-nBlock/2.)
	+(CC03_XY+CC03_Gap)/2.;
      
      for(int j=0;j<nBlock;j++) {
	{

	  double XBlock=
	    (CC03_XY+CC03_Gap)*(j-nBlock/2.)
	    +(CC03_XY+CC03_Gap)/2.;
	  
	  if( i== 0) {

	  } else if(i==nBlock-1) {
	    
	  } else {
	    if( ! (j==0 || j==nBlock-1) ) continue;
	  }
	    
	  if(box==0) {
	    std::sprintf(nam,"CC03box");
	    box = new GsimBox(std::string(nam),this,
			      G4ThreeVector(XBlock*cm,
					    YBlock*cm,
					    0.*cm),
			      G4ThreeVector(0,0,0)
			      );
	    box->setOuterMaterial("G4_PbWO4");
	    box->setParameters(paramVec);
	    box->setOuterColor("magenta");
	    box->setSensitiveDetector("CC03",id);
	    addDaughter(box);
	  } else {
	    box->cloneDetector(G4ThreeVector(XBlock*cm,
					     YBlock*cm,
					     0.*cm),
			       G4ThreeVector(0,0,0),id);
	  }
	  id++;
	}
      }
    }
    setThisAndDaughterBriefName("CC03");
  } else if(m_model==2) {
    std::vector<double> paramVec;
    paramVec.push_back(CC03_XY/2.*cm);
    paramVec.push_back(CC03_XY/2.*cm);
    paramVec.push_back(CC03_Len*cm);
    
    GsimBox* box=0;
    int nBlock=16;
    int nBeamHole=12;
    char nam[100];
    int id=0;
    for(int i=0;i<nBlock;i++) {
      double YBlock=
	(CC03_XY+CC03_Gap)*0.5*(i-nBlock/2.)
	+CC03_XY*0.5/2.;
      
      for(int j=0;j<nBlock;j++) {
	{
	  //beam hole
	  if( i>=(nBlock-nBeamHole)/2. &&
	      i<(nBlock-nBeamHole)/2.+nBeamHole &&
	      j>=(nBlock-nBeamHole)/2. &&
	      j<(nBlock-nBeamHole)/2.+nBeamHole )
	    continue;
	  
	  double XBlock=
	    (CC03_XY+CC03_Gap)*0.5*(j-nBlock/2.)
	    +CC03_XY*0.5/2.;
	  
	  if(box==0) {
	    std::sprintf(nam,"CC03box");
	    box = new GsimBox(std::string(nam),this,
			      G4ThreeVector(XBlock*cm,
					    YBlock*cm,
					    0.*cm),
			      G4ThreeVector(0,0,0)
			      );
	    box->setOuterMaterial("G4_PbWO4");
	    box->setParameters(paramVec);
	    box->setOuterColor("magenta");
	    box->setSensitiveDetector("CC03",id);
	    addDaughter(box);
	  } else {
	    box->cloneDetector(G4ThreeVector(XBlock*cm,
					     YBlock*cm,
					     0.*cm),
			       G4ThreeVector(0,0,0),id);
	  }
	  id++;
	}
      }
    }
    setThisAndDaughterBriefName("CC03");
  } else if(m_model==3) {
    std::vector<double> paramVec;
    paramVec.push_back(CC03_XY_NEW*cm);
    paramVec.push_back(CC03_XY_NEW*cm);
    paramVec.push_back(CC03_Len_NEW*cm);
    
    GsimBox* box=0;
    int nBlock=9;
    int nBeamHole=7;
    char nam[100];
    int id=0;
    for(int i=0;i<nBlock;i++) {
      double YBlock=
	(CC03_XY_NEW+CC03_Gap_NEW)*(i-(nBlock-1)/2.);
      for(int j=0;j<nBlock;j++) {
	{
	  //beam hole
	  if( i>=(nBlock-nBeamHole)/2. &&
	      i<(nBlock-nBeamHole)/2.+nBeamHole &&
	      j>=(nBlock-nBeamHole)/2. &&
	      j<(nBlock-nBeamHole)/2.+nBeamHole )
	    continue;
	  
	  double XBlock=
	    (CC03_XY_NEW+CC03_Gap_NEW)*(j-(nBlock-1)/2.);
	  
	  if(box==0) {
	    std::sprintf(nam,"CC03box");
	    box = new GsimBox(std::string(nam),this,
			      G4ThreeVector(XBlock*cm,
					    YBlock*cm,
					    0.*cm),
			      G4ThreeVector(0,0,0)
			      );
	    box->setOuterMaterial("G4_CESIUM_IODIDE");
	    box->setParameters(paramVec);
	    box->setOuterColor("magenta");
	    box->setSensitiveDetector("CC03",id);
	    addDaughter(box);
	  } else {
	    box->cloneDetector(G4ThreeVector(XBlock*cm,
					     YBlock*cm,
					     0.*cm),
			       G4ThreeVector(0,0,0),id);
	  }
	  id++;
	}
      }
    }
    setThisAndDaughterBriefName("CC03");
  } else {
    ;
  }
}


GsimE14CC03::~GsimE14CC03()
{
  ;
}

