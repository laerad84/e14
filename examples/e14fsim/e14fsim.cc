#include "E14Fsim/E14FsimAnalysisManager.h"

#include <iostream>
#include <cstdlib>

int main(int argc, char** argv)
{
  char* ifileName=0;
  char* ofileName=0;
  
  int iCluster=-1;//all
  int iFusion=1;  //chi2
  int iSmear=3;   //all
  int nSel=-1;    //all

  if(argc>=3) {
    ifileName = argv[1];
    ofileName= argv[2];
  }

  if(argc>=4) {
    iCluster= std::atoi(argv[3]);
  }
  if(argc>=5) {
    iFusion=std::atoi(argv[4]);
  }
  if(argc>=6) {
    iSmear=std::atoi(argv[5]);
  }
  if(argc>=7) {
    nSel=std::atoi(argv[6]);
  }
  
  if(argc>=8 || argc<3) {
    std::cerr << "Argument error" << std::endl;
    std::cerr << "Usage: e14fsim inputFile outputFile" << std::endl;
    std::cerr << "               nCluster -1:all,0,.." << std::endl;
    std::cerr << "               fusionFunction 0:KAMI,1:chi2,2:RMS" << std::endl;
    std::cerr << "               smearMode 0:noSmear,1:energy,2:pos,3:both" << std::endl;
    std::cerr << "               nEvent" << std::endl;
    return 1;
  }
  
  E14FsimAnalysisManager* am
    = new E14FsimAnalysisManager(ifileName,ofileName,nSel,
				 iCluster, iFusion,iSmear);
  am->run();
  
  return 0;
}


