/**
 *  @file
 *  @brief  GsimE14NCC
 *  $Id:$
 *  $Log:$
 */
#include "GsimE14Detector/GsimE14NCC.h"
#include "GsimE14Detector/GsimE14UserGeom.h"
#include "GsimPersistency/GsimMessage.h"
#include "GsimDetector/GsimPolyhedra2.h"
#include "GsimDetector/GsimTrap.h"
#include "GsimDetector/GsimTube.h"
#include "GsimDetector/GsimBox.h"


GsimE14NCC::GsimE14NCC(std::string name,
		       GsimDetector* motherDetector,
		       G4ThreeVector transV,G4ThreeVector rotV,
		       int userFlag)
  : GsimDetector(name,motherDetector,transV,rotV,userFlag)
{
  m_className = "GsimE14NCC";

  //NCC parameters

  G4double wCsI=66.0*mm;
  G4double tTeflon=0.2*mm;
  G4double tPMMA=2.1*mm;
  G4double tSUS=0.1*mm;
  G4double tCrystalMirror=1*mm;
  G4double modgap=0.0*mm;

  G4double beamholeExtension=7*mm;
  
  



  
  
  
  G4double CsIZlength[3]={148.0*mm,200.0*mm,96.0*mm};

  G4double moduleWidth=wCsI+tTeflon*2+tSUS*2+modgap*2;
  G4double moduleHeight=wCsI+tPMMA+tTeflon*2+tSUS*2+modgap*2;

  G4double moduleZlength[3];
  moduleZlength[0]=tTeflon        + CsIZlength[0] + tCrystalMirror;
  moduleZlength[1]=tCrystalMirror + CsIZlength[1] + tCrystalMirror;
  moduleZlength[2]=tCrystalMirror + CsIZlength[2] + tTeflon;

  G4double nccZlength=moduleZlength[0]+moduleZlength[1]+moduleZlength[2];
  G4double moduleZpos[3]={
    -nccZlength/2.+tTeflon+CsIZlength[0]/2.,
    -nccZlength/2.+moduleZlength[0]+tCrystalMirror+CsIZlength[1]/2.,
    -nccZlength/2.+moduleZlength[0]+moduleZlength[1]+tCrystalMirror+CsIZlength[2]/2.,
  };

  G4double CsIXpos[48];
  G4double CsIYpos[48];
  int      CsIRotN[48] = {
    //inner
    -1,0,0,0,0,+1,
    +1,2,2,2,2,-1,
    //middle
    -1,0,0,0,0,0,0,0,0,+1,
    +1,2,2,2,2,2,2,2,2,-1,
    //outer
    -1,-1,0,0,0,0,+1,+1,
    +1,+1,2,2,2,2,-1,-1
  };


  int xSign[4]={1,-1,-1,1};
  int ySign[4]={1,1,-1,-1};

  //////////////////////////
  // inner layer 3moduels x 4trun = 12 modules
  for(int i=0;i<4;i++) {
    //i          0  1  2  3
    //i%2;       0  1  0  1
    //2*(i%2)    0  2  0  2
    //1-2*(i%2)  1 -1  1 -1
    //
    // k=0 1 2
    // 2-k
    //   2 1 0
    //
    //(i%2)*2+(1-2*(i%2))*k

    CsIXpos[3*i+(i%2)*2+(1-2*(i%2))*0]=xSign[i]*(moduleWidth+beamholeExtension+moduleWidth/2.);
    CsIYpos[3*i+(i%2)*2+(1-2*(i%2))*0]=ySign[i]*(moduleWidth/2.);

    CsIXpos[3*i+(i%2)*2+(1-2*(i%2))*1]=xSign[i]*(moduleWidth+moduleWidth/2.);
    CsIYpos[3*i+(i%2)*2+(1-2*(i%2))*1]=ySign[i]*(moduleWidth+moduleWidth/2.);

    CsIXpos[3*i+(i%2)*2+(1-2*(i%2))*2]=xSign[i]*(moduleWidth/2.);
    CsIYpos[3*i+(i%2)*2+(1-2*(i%2))*2]=ySign[i]*(moduleWidth+beamholeExtension+moduleWidth/2.);
  }
  //////////////////////////

  //////////////////////////
  // middle layer  5modules x 4trun = 20 modules
  // 0 1 2 3 4
  // 4 3 2 1 0
  for(int i=0;i<4;i++) {

    CsIXpos[12+5*i+(i%2)*4+(1-2*(i%2))*0]=xSign[i]*(moduleWidth+beamholeExtension+moduleHeight+moduleWidth/2.);
    CsIYpos[12+5*i+(i%2)*4+(1-2*(i%2))*0]=ySign[i]*(moduleWidth/2.);
    
    CsIXpos[12+5*i+(i%2)*4+(1-2*(i%2))*1]=xSign[i]*(moduleWidth+moduleWidth+moduleWidth/2.);
    CsIYpos[12+5*i+(i%2)*4+(1-2*(i%2))*1]=ySign[i]*(moduleWidth+moduleWidth/2.);

    CsIXpos[12+5*i+(i%2)*4+(1-2*(i%2))*2]=xSign[i]*(moduleWidth+moduleWidth+moduleWidth/2.);
    CsIYpos[12+5*i+(i%2)*4+(1-2*(i%2))*2]=ySign[i]*(moduleWidth+moduleHeight+moduleWidth/2.);

    CsIXpos[12+5*i+(i%2)*4+(1-2*(i%2))*3]=xSign[i]*(moduleWidth+moduleWidth/2.);
    CsIYpos[12+5*i+(i%2)*4+(1-2*(i%2))*3]=ySign[i]*(moduleWidth+moduleHeight+moduleWidth/2.);
    
    CsIXpos[12+5*i+(i%2)*4+(1-2*(i%2))*4]=xSign[i]*(moduleWidth/2.);
    CsIYpos[12+5*i+(i%2)*4+(1-2*(i%2))*4]=ySign[i]*(moduleWidth+beamholeExtension+moduleHeight+moduleWidth/2.);
  }
  //////////////////////////

  //////////////////////////
  // outer layer  4modules x 4trun = 16 modules
  for(int i=0;i<4;i++) {

    CsIXpos[12+20+4*i+(i%2)*3+(1-2*(i%2))*0]=xSign[i]*(moduleWidth+beamholeExtension+moduleHeight*2+moduleWidth/2.);
    CsIYpos[12+20+4*i+(i%2)*3+(1-2*(i%2))*0]=ySign[i]*(moduleWidth/2.);
    
    CsIXpos[12+20+4*i+(i%2)*3+(1-2*(i%2))*1]=xSign[i]*(moduleWidth+moduleWidth*2+moduleWidth/2.);
    CsIYpos[12+20+4*i+(i%2)*3+(1-2*(i%2))*1]=ySign[i]*(moduleWidth+moduleWidth/2.);

    CsIXpos[12+20+4*i+(i%2)*3+(1-2*(i%2))*2]=xSign[i]*(moduleWidth+moduleWidth/2.);
    CsIYpos[12+20+4*i+(i%2)*3+(1-2*(i%2))*2]=ySign[i]*(moduleWidth+moduleHeight*2+moduleWidth/2.);
    
    CsIXpos[12+20+4*i+(i%2)*3+(1-2*(i%2))*3]=xSign[i]*(moduleWidth/2.);
    CsIYpos[12+20+4*i+(i%2)*3+(1-2*(i%2))*3]=ySign[i]*(moduleWidth+beamholeExtension+moduleHeight*2+moduleWidth/2.);
  }
  //////////////////////////


  GsimDetector* nccModule[48];
  std::vector<double> param;
  for(int i=0;i<48;i++){
    std::stringstream nccName;
    nccName<<"nccModule"<<i;
    nccModule[i] = new GsimDetector(nccName.str().c_str(),this ,G4ThreeVector(CsIXpos[i],CsIYpos[i],0),G4ThreeVector(0,0,M_PI/2*CsIRotN[i]));
    addDaughter(nccModule[i]);
  }

  GsimBox* nccCsI[48][3];
  for(int j=0;j<3;j++){
    param.clear();
    param.push_back(wCsI);
    param.push_back(wCsI);
    param.push_back(CsIZlength[j]);

    for(int i=0; i<48; i++){
      std::stringstream nccName;
      nccName<<"nccCsI"<<i<<j<<std::endl;
      nccCsI[i][j] = new GsimBox(nccName.str().c_str(),nccModule[i] ,G4ThreeVector(0,0,moduleZpos[j]),G4ThreeVector(0,0,0));
      nccCsI[i][j]->setParameters(param);
      nccCsI[i][j]->setOuterMaterial("G4_CESIUM_IODIDE");

      if(j==0) {
	nccCsI[i][j]->setOuterColor("red");
      }
      else if(j==1){
	nccCsI[i][j]->setOuterColor("blue");
      }
      else {
	nccCsI[i][j]->setOuterColor("green");
      }

      nccCsI[i][j]->setSensitiveDetector("NCC",i+j*48);
      //F:0-47
      //M:48-
      //R:96-
      
      nccModule[i]->addDaughter(nccCsI[i][j]);
    
    }
  }  

  setThisAndDaughterBriefName("NCC");
}

GsimE14NCC::~GsimE14NCC()
{
  ;
}

#ifdef GSIMDEBUG
  GsimMessage::getInstance()->debugExit(__PRETTY_FUNCTION__);
#endif 

